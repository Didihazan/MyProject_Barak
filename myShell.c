#include "myShell.h"
#include "myFunction.h"



void welcome();

int main() {
    welcome();


    while (1) {
        char hostname[256];
        struct utsname unameData;

        // קבלת שם המחשב באמצעות הפונקציה gethostname
        if (gethostname(hostname, sizeof(hostname)) == 0) {
            printf("Hostname: %s\n", hostname); // הדפסת שם המחשב
        } else {
            perror("gethostname");
            return 1;
        }

        // קבלת גרסת Ubuntu באמצעות הפונקציה uname
        if (uname(&unameData) == 0) {
            printf("Ubuntu Version: %s\n", unameData.release); // הדפסת גרסת Ubuntu
        } else {
            perror("uname");
            return 1;
        }
         
      printf("GitHub Username:\n");
        printf("__   __       _ _     _             \n");
        printf("\\ \\ / /__  __| (_) __| |_   _  __ _ \n");
        printf(" \\ V / _ \\/ _` | |/ _` | | | |/ _` |\n");
        printf("  | |  __/ (_| | | (_| | |_| | (_| |\n");
        printf("  |_|\\___|\\__,_|_|\\__,_|\\__, |\\__,_|\n");
        printf("                        |___/       \n");
        printf("\n");

        break;
    }
 while (1)
    {
        errno = 0;
        getLocation();
        char *input = getInputFromUser();
        if (strcmp(input, "exit") == 0 || strncmp(input, "exit ", 5) == 0)
            logout(input);

        char **arguments = splitArgument(input);
         if(strcmp(arguments[0], "exit") == 0){ 
            free(arguments);
            logout(input);
}
 if( errno ==22) continue;
      
        if (strcmp(input, "echo") == 0)
            echo(arguments);
       else if (strncmp(input, "cd", 2) == 0){
            cd(arguments);
        }    
        else if (strcmp(input, "cp") == 0)
            cp(arguments);
        free(arguments);
        free(input);
    }
    return 0;
}


void welcome() {
    printf("Welcome to my Shell\n");
}
