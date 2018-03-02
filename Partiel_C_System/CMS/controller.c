
#include "controller.h"
#include "helpers.h"

extern char tmpFolder[255];


void cryptMot(request *re){
    cryptExec(re->argv[0]);
}

void decryptMot(request *re){
    decryptExec(re->argv[0]);
}

void cryptMotPost(request *re){
    cryptExec(re->postData);
}

void decryptMotPost(request *re){
    decryptExec(re->postData);
}

void cryptFile(request *re){
    char filename[32] = "";
    uniqid(filename);
    toFile(re->socket, filename);
    cryptExec(filename);
    unlink(filename);
}

void decryptFile(request *re){
    char filename[32] = "";
    uniqid(filename);
    toFile(re->socket, filename);
    decryptExec(filename);
    unlink(filename);
}


void searchForFile(request *re){
    
    if( access( re->url, F_OK ) == -1 )
    {
        printf("<html><head></head><body>404 Not found !</body></html>");
        return;
    }
    // IMPORTANT SECURITY VULNERABILITY !
    int file = open(re->url, O_RDONLY);
    
    //1 = stdout -> dup2 -> socket
    readToWrite(file, 1);
}



void stockImage(request *re){
    char filename[255] = "", filepath[255] = "", filechunk[255] = "";
    
    uniqid(filename);
    
    sprintf(filechunk, "%s%s.chunk", tmpFolder, filename);
    sprintf(filepath, "%s%s", tmpFolder, filename);
    
    printf("%s", filename);
    
    toFile(re->socket, filechunk);
    
    pid_t base64encoderPid;
    if((base64encoderPid = fork()) == 0){
        int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
        dup2(fd, 1);
        #ifdef EXECLP
            execlp("base64", "base64", filechunk, NULL);
        #else
            execlp("base64", "base64", filechunk, NULL);
        #endif
        close(fd);
        _Exit(0);
    }
    else{
        waitpid(base64encoderPid, NULL, 0);
        unlink(filechunk);
    }
    
}

void displayImage(request *re){
    printf("<html><div><img src=\"data:image/jpeg;base64, ");
    fflush(stdout);
    char filepath[255] = "";
    sprintf(filepath, "%s%s",tmpFolder, re->argv[0]);
    
    int fd = open(filepath, O_RDONLY);
    
    readToWrite(fd, re->socket);
    
    printf("\"/></div></html>\r\n");
    fflush(stdout);
}


void stockFile(request *re){
    char filename[255] = "", filepath[255] = "", filechunk[255] = "";
    
    uniqid(filename);
    
    sprintf(filechunk, "%s%s", tmpFolder, re->argv[0]);
    sprintf(filepath, "%s%s.tar.gz", tmpFolder, filename);
    
    printf("%s", filename);
    
    toFile(re->socket, filechunk);
    
    pid_t compresserPid;
    if((compresserPid = fork()) == 0){
        int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
        #ifdef EXECLP
            execlp("tar", "tar", "czvf", filepath, filechunk, NULL);
        #else
            execl("tar", "tar", "czvf", filepath, filechunk, NULL);
        #endif
        
        close(fd);
        _Exit(0);
    }
    else{
        waitpid(compresserPid, NULL, 0);
        unlink(filechunk);
    }
}

void getFile(request *re){
    char filepath[255] = "";
    
    sprintf(filepath, "%s%s.tar.gz", tmpFolder, re->argv[0]);
    int fd = open(filepath, O_RDONLY);
    readToWrite(fd, re->socket);
    close(fd);
    
}

void displayFiles(request *re){
    printf("<html><body><h2>ID des fichiers</h2>");
    fflush(stdout);
    DIR *d;
    struct dirent *dir;
    d = opendir(tmpFolder);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("<p>%s</p>\n", dir->d_name);
        }
        closedir(d);
    }
    printf("</body></html>");
}

