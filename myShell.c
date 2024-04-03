#include "myShell.h"
#include "myFunction.h"



 bool piping = false;
char ***splitByPipe(char **args)
{
    int count1 =0;
    int size1 = 2, size2 = 2;
    char ***result = (char ***)malloc(sizeof(char **)*3);
    result[0] = (char **)malloc(sizeof(char *) * size1);
    result[1] = (char **)malloc(sizeof(char *) * size2);
    int isPipe = 0;
    for (int i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], "|") == 0)
        {
            isPipe = 1;
            continue;
        }
        if (!isPipe)
        {
            result[0][count1] = args[i];
            count1++;
            if (count1 >= size1)
            {
                size1 *= 2;
                result[0] = (char **)realloc(result[0], sizeof(char *) * size1);
            }
        }
        else
        {
            result[1][count2] = args[i];
            count2++;
            if (count2 >= size2)
            {
                size2 *= 2;
                result[1] = (char **)realloc(result[1], sizeof(char *) * size2);
            }
        }
    }
    result[0][count1] = NULL;
    result[1][count2] = NULL;
    return result;
}

int main() {//פונקצית ראשית

    welcome();
 while (1)//לולאת אינפינטי
    {
        bool piping = false;
        errno = 0;
        getLocation();
        char *input = getInputFromUser();
        if (strcmp(input, "exit") == 0 || strncmp(input, "exit ", 5) == 0)
            logout(input);

        char **arguments = splitArgument(input);//קריאה לפונקציה לפיצול המחרוזת למערך של מחרוזות
         if(strcmp(arguments[0], "exit") == 0){ //בדיקה האם המחרוזת הראשונה במערך היא "exit"
            free(arguments);
            logout(input);
}
 if( errno ==22) continue;
      
        if (strcmp(input, "echo") == 0)//בדיקה האם הקלט שווה ל"echo"
            echo(arguments);
       else if (strncmp(input, "cd", 2) == 0){//בדיקה האם הקלט מתחיל ב"cd"
            cd(arguments);
        }    
        else if (strcmp(input, "cp") == 0)//בדיקה האם הקלט שווה ל"cp"
            cp(arguments);
        free(arguments);
        free(input);
        if(strcmp(arguments[0], "read") == 0){
            readFile(arguments);
        }
        else if(strcmp(arguments[0], "echo") == 0){//בדיקה האם המחרוזת הראשונה במערך היא "echo"
            echorite(arguments);
        }
        else if(strcmp(arguments[0], "wc") == 0){//בדיקה האם המחרוזת הראשונה במערך היא "wc"
            wordCount(arguments);
        }
        else if(strcmp(arguments[0], "echo") == 0){//בדיקה האם המחרוזת הראשונה במערך היא "echo"
            echoppend(arguments);
        }
        else if(strcmp(arguments[0], "mv") == 0){//בדיקה האם המחרוזת הראשונה במערך היא "mv"
            move(arguments);
        }
        else if(strcmp(arguments[0], "delete") == 0){//בדיקה האם המחרוזת הראשונה במערך היא "delete"
            delete(arguments);
        }
        else if(strcmp(arguments[0], "dir") == 0){//בדיקה האם המחרוזת הראשונה במערך היא "dir"
            get_dir();
        }
         else if (piping)//בדיקה האם יש פייפ
        {
            // indexPipe
            // arguments[indexPipe]=NULL;
            // mypipe(arguments, arguments+indexPipe+1);
            mypipe(arguments, arguments+/*indexPipe*/+1);
            wait(NULL);
            for(int i = 0; splitArgumentsArr[i]; i++){
                free(splitArgumentsArr[i]);
            }
            free(splitArgumentsArr);
        }
        else
        {
            systemCall(arguments);//קריאה לפונקציה להפעלת תוכניות
            wait(NULL);//המתנה לסיום התוכנית
        }
        free(arguments);
        free(input);
    }
    return 0;
}


void welcome() {
    printf("Welcome to my Shell\n");//הדפסת הקדימות
          printf("GitHub Username:\n");
        printf("__   __       _ _     _             \n");
        printf("\\ \\ / /__  __| (_) __| |_   _  __ _ \n");
        printf(" \\ V / _ \\/ _` | |/ _` | | | |/ _` |\n");
        printf("  | |  __/ (_| | | (_| | |_| | (_| |\n");
        printf("  |_|\\___|\\__,_|_|\\__,_|\\__, |\\__,_|\n");
        printf("                        |___/       \n");
        printf("\n");
}