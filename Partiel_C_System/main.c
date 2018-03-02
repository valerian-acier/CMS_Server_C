#include "main.h"


int main(int argc, char **argv){
    
    signalDefinitions();
    
    initGlobalVariables();
    
    routesRegistering();
    

#ifndef UNIT_TESTING
    log_ecrire(logFile, "Starting server without unit testing !");
    if((pid = fork()) == 0){
        //daemon server
        setsid();
        createServer(clientConnected);
    }
    exit(0);
#else
    log_ecrire(logFile, "Starting server with unit testing !");
    if((pid = fork()) == 0){
        createServer(clientConnected);
    }
    sleep(3);
    executeTesting();
    
#endif
}

void signalDefinitions(){
    if(signal(SIGTERM, end) == SIG_ERR){
        printf("Can't catch SIGTERM\n");
        exit(0);
    }
    
    if(signal(SIGUSR1, setTmpFileStorage) == SIG_ERR){
        printf("Can't catch SIGUSR1\n");
        exit(0);
    }
}


void routesRegistering(){
    
    //Proto :
    // void registerRouter
    // first argument is the router
    // second is the http method (GET / POST / UPLOAD / PUT / DELETE etc...)
    // third is the route url -> http://localhost:9090/{route_url}
    // fourth is the number of arguments of the route ex :
    //      GET http://localhost:9090/route/value1/value2/value3
    //      if nb_arg = 3 -> ["value1", "value2", "value3"]
    //      if nb_arg = 2 -> ["value1", "value2/value3"]
    // fifth is the function to callback when the route is called
    
    //TP GROUPE 1
    
    registerRoute(&router, "UPLOAD", "stockImage", 0, stockImage);
    registerRoute(&router, "GET", "displayImage", 1, displayImage);
    
    //TP GROUPE 2
    
    registerRoute(&router, "GET", "cryptMot.html", 1, cryptMot);
    registerRoute(&router, "GET", "decryptMot.html", 1, decryptMot);
    
    registerRoute(&router, "POST", "cryptMot.html", 0, cryptMotPost);
    registerRoute(&router, "POST", "decryptMot.html", 0, decryptMotPost);
    
    registerRoute(&router, "UPLOAD", "cryptFile.html", 0, cryptFile);
    registerRoute(&router, "UPLOAD", "decryptFile.html", 0, decryptFile);
    
    //TP GROUPE 3
    
    registerRoute(&router, "UPLOAD", "stockFile", 1, stockFile);
    registerRoute(&router, "GET", "getFile", 1, getFile);
    registerRoute(&router, "GET", "displayFiles", 0, displayFiles);
    
    
    // When no route found call searchForFile()
    notFoundHandler = searchForFile;
}

void initGlobalVariables(){
    sprintf(tmpFolder, "tmp/");
    logFile = log_ouvrir("log.txt");
    router = NULL;
}

void end(int signo){
    exit(0);
}

void setTmpFileStorage(int signo){
    printf("Storage path : ");
    fflush(stdout);
    scanf("%s", tmpFolder);
    printf("Storage path set to : %s\n", tmpFolder);
}

void executeTesting(){
    
    printf("Starting unit testing ...\n");
    
    //TP GROUPE 2
    assertEquals("GET aaa->bbb", "bbb", get("/cryptMot.html/aaa"));
    assertEquals("GET abc->bcd", "bcd", get("/cryptMot.html/abc"));
    assertEquals("GET abcdef->bcdefg", "bcdefghijklmnopqrstuvwxyz", get("/cryptMot.html/abcdefghijklmnopqrstuvwxy"));
    
    assertEquals("GET bbb->aaa", "aaa", get("/decryptMot.html/bbb"));
    assertEquals("GET cde->bcd", "bcd", get("/decryptMot.html/cde"));
    assertEquals("GET bcdefg->abcdef", "abcdefghijklmnopqrstuvwxy", get("/decryptMot.html/bcdefghijklmnopqrstuvwxyz"));
    
    assertEquals("GET aaa->bbb<-ccc", get("/cryptMot.html/aaa"), get("/decryptMot.html/ccc"));
    
    char buffer[255] = "/decryptMot.html/";
    char * result = get("/cryptMot.html/aaa");
    
    assertEquals("GET aaa->bbb->aaa", "aaa", get(strcat(buffer,result)));
    
    assertEquals("POST aaa->bbb", "bbb", post("/cryptMot.html", "aaa"));
    assertEquals("POST abc->bcd", "bcd", post("/cryptMot.html", "abc"));
    assertEquals("POST abcdef->bcdefg", "bcdefg", post("/cryptMot.html", "abcdef"));
    
    assertEquals("POST bbb->aaa", "aaa", post("/decryptMot.html", "bbb"));
    assertEquals("POST bcd->abc", "abc", post("/decryptMot.html", "bcd"));
    assertEquals("POST bcdefg->abcdef", "abcdef", post("/decryptMot.html", "bcdefg"));
    
    assertEquals("POST aaa->bbb->aaa", "aaa", post("/decryptMot.html", post("/cryptMot.html", "aaa")));
    
    
    
    uploadAndDownloadResult("/cryptFile.html", "picture.jpg", "picture.jpg.crypted");
    uploadAndDownloadResult("/decryptFile.html", "picture.jpg.crypted", "picture.jpg.decrypted");
    assertFileEquals("UPLOAD aaa->bbb->aaa", "picture.jpg", "picture.jpg.decrypted");
    
    
    unlink("picture.jpg.crypted");
    unlink("picture.jpg.decrypted");
    
    
    //TP GROUPE 1
    char *filename = uploadAndGetResult("/stockImage", "picture.jpg");
    char fullpath[255] = "";
    sprintf(fullpath, "tmp/%s", filename);
    assertFileEquals("STOCK IMAGE", "tests/picture.b64", fullpath);
    
    
    //TP GROUPE 3
    result = uploadAndGetResult("/stockFile/picture.jpg", "picture.jpg");
    
    sprintf(filename, "tmp/%s.tar.gz", result);
    
    sprintf(buffer, "/getFile/%s", result);
    
    getAndDownloadResult(buffer, "tmp.tar.gz");
    
    assertFileEquals("STOCK picture.jpg -> tmp/compressed.tar.gz -> tmp.tar.gz", filename, "tmp.tar.gz");
    
    unlink("tmp.tar.gz");
    unlink(filename);
    
    printf("End !\n");
    kill(pid, SIGTERM);
}

