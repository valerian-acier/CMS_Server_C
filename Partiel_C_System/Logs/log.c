//
//  log.c
//  C_system
//
//  Created by Valérian Acier on 26/09/2017.
//  Copyright © 2017 Valérian Acier. All rights reserved.
//

#include "log.h"
#include <time.h>

FILE * log_ouvrir(const char* path){
    FILE *f = fopen(path, "w");
    fprintf(f, "\n\n\n");
    return f;
}

int log_ecrire(FILE *f, char* content){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(f, "LOG [%d-%d-%d %d:%d:%d] : %s\n", tm.tm_mday, tm.tm_mon+1,tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, content);
    log_write_to_disk(f);
    return 1;
}


void log_write_to_disk(FILE *f){
    fflush(f);
}


int log_fermer(FILE *f){
    fclose(f);
    return 1;
}

