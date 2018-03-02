//
//  testing.c
//  Partiel_C_System
//
//  Created by Valérian Acier on 13/02/2018.
//  Copyright © 2018 Valérian Acier. All rights reserved.
//

#include "testing.h"
#include "helpers.h"

int initiateLocalTCP(){
    int clientSock = socket(AF_INET, SOCK_STREAM, 0);
    if ( clientSock < 0 )
    {
        return -1;
    }
    
    struct timeval timeout;
    timeout.tv_sec = 30;
    timeout.tv_usec = 0;
    
    if (setsockopt (clientSock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0){
        printf("Error setsockopt !\n");
        return -1;
    }
    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9090);
    
    if(inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return -1;
    }
    
    int rc = connect(clientSock, (const struct sockaddr *)&addr ,  sizeof(addr));
    if (rc < 0)
    {
        printf("Error rc !\n");
        return -1;
    }
    return clientSock;
}

char *get(char *url){

    int clientSock = getRequest(url);
    char *result = readAll(clientSock);
    char search[] = "\r\n\r\n";
    return strstr(result, search) + strlen(search);
}

int getRequest(char *url){
    
    int clientSock = initiateLocalTCP();
    
    char getRequest[255] = "";
    sprintf(getRequest, "GET %s HTTP/1.1\r\n\r\n", url);
    write(clientSock, getRequest, strlen(getRequest));
    sleep(1);
    return clientSock;
}


char *post(char *url, char *data){
    
    int clientSock = initiateLocalTCP();
    
    char postRequest[255] = "";
    sprintf(postRequest, "POST %s HTTP/1.1\r\n\r\n", url);
    write(clientSock, postRequest, strlen(postRequest));
    write(clientSock, data, strlen(data));
    sleep(1);
    char *result = readAll(clientSock);
    if(result == NULL)
        return NULL;
    
    char search[] = "\r\n\r\n";
    return strstr(result, search) + strlen(search);
}

int upload(char *url, char *filename){
    
    int clientSock = initiateLocalTCP();
    
    char uploadRequest[255] = "";
    sprintf(uploadRequest, "UPLOAD %s HTTP/1.1\r\n\r\n", url);
    write(clientSock, uploadRequest, strlen(uploadRequest));
    
   
    int fd = open(filename, O_RDONLY);
    readToWrite(fd, clientSock);
    close(fd);
    
    sleep(1);
    if(extractHeadersFromSocket(clientSock) == NULL){
        printf("Error client have not sended the headers !\n");
        exit(0);
    }
    
    return clientSock;
}

char *uploadAndGetResult(char *url, char* filename){
    int socket = upload(url, filename);
    return readAll(socket);
}

void uploadAndDownloadResult(char *url, char *filename, char* resultfilename){
    int socket = upload(url, filename);
    
    ////// TODO : DEBUG - STRANGE BEHAVIOR
    // if using toFile() function, the file is not fully downloaded
    // copying and renaming buffer to buffer_ seems to correct this problem
    // probably memory problem somewhere
    // stack overflow : https://stackoverflow.com/questions/9839969/strange-global-variable-behaviour-once-variable-name-is-changed-issue-disappear
    
    char buffer_[BUFFLEN];
    
    int fd = open(resultfilename, O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
    size_t r = 1;
    while(r > 0){
        r = read(socket, buffer_, BUFFLEN);
        write(fd, buffer_, r);
    }
    close(fd);
    close(socket);
}

void getAndDownloadResult(char *url, char* resultfilename){
    int socket = getRequest(url);
    extractHeadersFromSocket(socket);
    
    toFile(socket, resultfilename);
    close(socket);
}


