//
//  router.c
//  Partiel_C_System
//
//  Created by Valérian Acier on 12/02/2018.
//  Copyright © 2018 Valérian Acier. All rights reserved.
//

#include "router.h"
#include "log.h"

extern FILE* logFile;
extern route *router;
extern void (*notFoundHandler)(request*);


void registerRoute(route** router, char* method, char* url, int argc, void (*controllerAction)(request*)){
    if(*router == NULL){
        *router = (route*)malloc(sizeof(route));
        (*router)->url = url;
        (*router)->method = method;
        (*router)->controllerAction = controllerAction;
        (*router)->argc = argc;
        (*router)->next = NULL;
        return;
    }
    
    route* current = *router;
    
    while(current->next != NULL){
        current = current->next;
    }
    current->next = (route*)malloc(sizeof(route));
    current->next->url = url;
    current->next->method = method;
    current->next->controllerAction = controllerAction;
    current->next->argc = argc;
    current->next->next = NULL;
}

void callControllerAction(route *router, request *request){
    route* current = router;
    bool found = false;
    while(current != NULL){
        if(strstr(request->url, current->url) == request->url && strcmp(current->method, request->method) == 0){
            found = true;
            request->argv = malloc(sizeof(char*) * current->argc);
            char *cp = malloc(255);
            memcpy(cp, request->url, strlen(request->url)+1);
            cp = strchr(cp, '/')+1;
            for(int i = 0 ; i < current->argc ; i++){
                char *end = strchr(cp, '/');
                if(i == current->argc-1)
                    end = NULL;
                if(end != NULL)
                    *end = '\0';
                size_t len = strlen(cp);
                request->argv[i] = malloc(sizeof(char) * len);
                
                memcpy(request->argv[i], cp, len+1);
                cp = (end+1);
            }
            
            char logContent[255] = "";
            sprintf(logContent, "Calling action for route %s %s (url is %s)\n",current->method, current->url, request->url);
            log_ecrire(logFile, logContent);
            current->controllerAction(request);
        }
        current = current->next;
    }
    if(!found)
        notFoundHandler(request);
}



void clientConnected(int socket){
    dup2(socket, 1);
    request *re = readRequest(socket);
    write(socket, HTTP, strlen(HTTP));
    callControllerAction(router, re);
    cleanRequest(re);
    free(re);
    _Exit(0);
}
