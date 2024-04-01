#include "myShell.h"
#include "myFunction.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>


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
        getLocation();
        char *input = getInputFromUser();
    puts(input);
        if (strcmp(input, "exit") == 0 || strncmp(input, "exit ", 5) == 0)
            logout(input);

        char **arguments = splitArgument(input);
         if(strcmp(arguments[0], "exit") == 0){ 
            free(arguments);
            logout(input);
}
 for (int i = 0; i < 3; i++)
 {
    printf("arg[%s]", arguments[i]);
 }
      
        if (strcmp(input, "echo") == 0)
            echo(arguments);
       else if (strncmp(input, "cd", 2) == 0){
            puts("yes");
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
