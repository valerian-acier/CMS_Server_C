//
//  main.c
//  CryptDecrypt
//
//  Created by Valérian Acier on 11/10/2017.
//  Copyright © 2017 Valérian Acier. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



void _crypt(char *data, int len){
    for(int i = 0 ; i < len ; i++){
        data[i] = data[i]+1;
    }
}

void _uncrypt(char *data, int len){
    for(int i = 0 ; i < len ; i++){
        data[i] = data[i]-1;
    }
}

void _cryptFile(char *data){
    int fd = open(data, O_RDONLY);
    int r = 1;
    char buffer[255] = "";
    while (r > 0){
        r = read(fd, buffer, 255);
        _crypt(buffer, r);
        write(1, buffer, r);
    }
    close(fd);
}

void _uncryptFile(char *data){
    int fd = open(data, O_RDONLY);
    int r = 1;
    char buffer[255] = "";
    while (r > 0){
        r = read(fd, buffer, 255);
        _uncrypt(buffer, r);
        write(1, buffer, r);
    }
    close(fd);
}


int main(int argc, const char * argv[]) {
    if(argc == 3){
        char buffer[1024];
        strcpy(buffer, argv[2]);
        
       if( access(buffer, F_OK ) != -1 ){
           if(strcmp(argv[1], "crypt") == 0){
               _cryptFile(buffer);
           }
           else{
               _uncryptFile(buffer);
               
           }
        }
       else{
           if(strcmp(argv[1], "crypt") == 0){
               _crypt(buffer, strlen(buffer));
           }
           else{
               _uncrypt(buffer, strlen(buffer));
               
           }
           printf(buffer);
       }
        
        
        
    }else{
        printf("Error");
    }
    return 0;
}
