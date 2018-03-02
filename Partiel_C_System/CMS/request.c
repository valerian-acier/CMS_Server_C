//
//  request.c
//  Partiel_C_System
//
//  Created by Valérian Acier on 18/02/2018.
//  Copyright © 2018 Valérian Acier. All rights reserved.
//

#include "request.h"

char* extractHeadersFromSocket(int socket){
    char headersEnd[] = "\r\n\r\n";
    size_t size = strlen(headersEnd);
    char c;
    int currentIndex = 0;
    size_t r = 1;
    char *headers = malloc(sizeof(char) * 255);
    int i = 0;
    while(r > 0){
        r = read(socket, &c, 1);
        headers[i] = c;
        i++;
        if(c == headersEnd[currentIndex]){
            currentIndex++;
            if(currentIndex >= size){
                return headers;
            }
        }
        else{
            currentIndex = 0;
        }
    }
    return NULL;
}


request *readRequest(int socket){
    
    char *headers = extractHeadersFromSocket(socket);
    request *re = malloc(sizeof(request));
    sscanf(headers, "%s /%s HTTP/1.1", re->method, re->url);
    re->socket = socket;
    re->postData = NULL;
    re->argv = NULL;
    
    if(strcmp(re->method, "POST") == 0){
        char *buffer = readAll(socket);
        re->postData = buffer;
    }
    return re;
}



char *readAll(int std){
    int size;
    ioctl(std, FIONREAD, &size);
     
    if(size <= 0)
     return NULL;
     
    char *result = malloc((size+1) * sizeof(char));
     
    read(std, result, size);
    //in the case of string
    result[size] = '\0';
    
    /*
     FIRST VERSION WITHOUT IOCTL
     
    int r = 1;
    int totalSize = 0;
    char *result = NULL;
    char buffer[BUFFLEN];
    while(r > 0){
        r = read(std, buffer, BUFFLEN);
        if(r > 0){
            totalSize += r;
            if(result == NULL){
                result = malloc(sizeof(char) * (totalSize+1));
                sprintf(result, buffer);
            }
            else{
                result = realloc(result, sizeof(char) * (totalSize+1));
                sprintf(result, "%s%s", result, buffer);
            }
        }
        if(r != BUFFLEN)
            break;
    }
    if(result == NULL)
        return NULL;
    
    result[totalSize] = '\0';*/
    
    return result;
}

void cleanRequest(request *re){
    if(re->postData != NULL)
        free(re->postData);
    if(re->argv != NULL)
        free(re->argv);
    close(re->socket);
}

