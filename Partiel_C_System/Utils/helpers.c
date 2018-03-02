//
//  helpers.c
//  Partiel_C_System
//
//  Created by Valérian Acier on 28/02/2018.
//  Copyright © 2018 Valérian Acier. All rights reserved.
//


#include <fcntl.h>
#include <unistd.h>
#include "helpers.h"
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

#define BUFFLEN 1024

void readToWrite(int readFiledes, int writeFiledes){
    size_t r = 1;
    char buffer[BUFFLEN];
    while(r > 0){
        r = read(readFiledes, buffer, BUFFLEN);
        write(writeFiledes, buffer, r);
        if(r != BUFFLEN)
            break;
    }
}

void toFile(int filedes, char* filename){
    int fd = open(filename, O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
    readToWrite(filedes, fd);
    close(fd);
}


void uniqid(char *str){
    
    //FROM PHP uniqid();
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int sec  = (int) tv.tv_sec;
    int usec = (int) (tv.tv_usec % 0x100000);
    sprintf(str, "%08x%05x", sec, usec);
    
}

void cryptExec(char *data)
{
    pid_t pid;
    if((pid = fork()) == 0){
    #ifdef EXECLP
        execlp("./CryptDecrypt", "./CryptDecrypt", "crypt", data, NULL);
    #else
        execl("./CryptDecrypt", "./CryptDecrypt", "crypt", data, NULL);
    #endif
    _Exit(0);
    }
    else{
        waitpid(pid, NULL, 0);
    }
}

void decryptExec(char *data){
    pid_t pid;
    if((pid = fork()) == 0){
    #ifdef EXECLP
        execlp("./CryptDecrypt", "./CryptDecrypt", "decrypt", data, NULL);
    #else
        execl("./CryptDecrypt", "./CryptDecrypt", "decrypt", data, NULL);
    #endif
        _Exit(0);
    }
    else{
        waitpid(pid, NULL, 0);
    }
}

