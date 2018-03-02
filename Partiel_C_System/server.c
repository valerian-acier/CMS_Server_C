//
//  server.c
//  Partiel_C_System
//
//  Created by Valérian Acier on 11/02/2018.
//  Copyright © 2018 Valérian Acier. All rights reserved.
//

#include "server.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


extern int client_pid;

void createServer(void (*clientConnected)(int)){
    
    int listeningSocket;
    
    if((listeningSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("Error ecoute");
        exit(-1);
    }
    
    int defaultPort = 9090;
    struct sockaddr_in listeningSocketSettings;
    do{
        listeningSocketSettings.sin_family = AF_INET;
        listeningSocketSettings.sin_port = htons(defaultPort);
        listeningSocketSettings.sin_addr.s_addr=INADDR_ANY;
        
        if(bind(listeningSocket, (const struct sockaddr *)&listeningSocketSettings ,  sizeof(listeningSocketSettings)) != -1){
            break;
        }
        defaultPort++;
    }while(1);
    
    printf("Port : %d\n", defaultPort);
    
    
    if(listen(listeningSocket, 5) == -1){
        printf("Error listen");
        exit(-1);
    }
    
    struct sockaddr_in clientSocketSettings;
    socklen_t sizeClientSocketSettings = sizeof(clientSocketSettings);
    clientSocketSettings.sin_family = AF_INET;
    
    for(;;){
        int clientSocket = accept(listeningSocket, (struct sockaddr *)&clientSocketSettings, &sizeClientSocketSettings);
        if((client_pid = fork()) == 0)
            clientConnected(clientSocket);
        else{
            waitpid(client_pid, NULL, 0);
            kill(client_pid, SIGTERM);
        }
        
        close(clientSocket);
    }
}
