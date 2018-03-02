//
//  asserting.c
//  Partiel_C_System
//
//  Created by Valérian Acier on 02/03/2018.
//  Copyright © 2018 Valérian Acier. All rights reserved.
//

#include "asserting.h"
#include <signal.h>

extern pid_t pid;

void assertHTMLEquals(char *title, char *expected, char *actual){
    char realExpected[1024] = "";
    sprintf(realExpected, "%s%s%s%s", HTTP, "<html><head></head><body>", expected, "</body></html>\r\n");
    if(strcmp(realExpected, actual) != 0){
        printf("\x1b[31;40mAssert error on %s !\nExpected (%lu) :\n%s\nHave (%lu) :\n%s\n\x1b[0m", title, strlen(realExpected), realExpected, strlen(actual), actual);
        _Exit(0);
    }
    printf("Assert OK : %s\n", title);
}

void assertFileEquals(char *title, char *original, char *crypted_uncrypted){
    int or = open(original, O_RDONLY);
    int ex = open(crypted_uncrypted, O_RDONLY);
    char bufferOr[BUFFLEN] = "", bufferEx[BUFFLEN] = "";
    size_t r = 1;
    while(r > 0){
        r = read(or, bufferOr, BUFFLEN);
        if(r != read(ex, bufferEx, BUFFLEN) || memcmp(bufferOr, bufferEx, r) != 0){
            printf("\x1b[31;40mAssert error on %s !\n File : %s is not equal to %s\n\x1b[0m", title, original, crypted_uncrypted);
            kill(pid, SIGTERM);
            _Exit(0);
        }
    }
    close(or);
    close(ex);
    printf("Assert OK : %s\n", title);
}



void assertEquals(char *title, char *expected, char *actual){
    if(actual == NULL && expected != NULL){
        printf("\x1b[31;40mAssert error on %s !\nExpected :\n%s\nHave :\n%s\n\x1b[0m", title, expected, actual);
        kill(pid, SIGTERM);
        _Exit(0);
    }
    
    if(strcmp(expected, actual) != 0){
        size_t expectedSize = strlen(expected);
        size_t actualSize = strlen(actual);
        if(expectedSize > 100 || actualSize > 100)
        {
            printf("\x1b[31;40mAssert error on %s !\nExpected (%lu)\nHave (%lu)\n\x1b[0m", title, expectedSize, actualSize);
        }
        else{
            printf("\x1b[31;40mAssert error on %s !\nExpected (%lu) :\n%s\nHave (%lu) :\n%s\n\x1b[0m", title, expectedSize, expected, actualSize, actual);
        }
        
        kill(pid, SIGTERM);
        _Exit(0);
    }
    printf("Assert OK : %s\n", title);
}
