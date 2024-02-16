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

        // הדפסת קישור לפרופיל הגיטהאב של המשתמש
         char *githubUsername = "Yedidya";
         
      printf("GitHub Username (ASCII art):\n");
        printf("__   __       _ _     _             \n");
        printf("\\ \\ / /__  __| (_) __| |_   _  __ _ \n");
        printf(" \\ V / _ \\/ _` | |/ _` | | | |/ _` |\n");
        printf("  | |  __/ (_| | | (_| | |_| | (_| |\n");
        printf("  |_|\\___|\\__,_|_|\\__,_|\\__, |\\__,_|\n");
        printf("                        |___/       \n");
        printf("\n");



        break;
    }

    return 0;
}


void welcome() {
    printf("Welcome to my Shell\n");
}
