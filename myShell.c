#include "myShell.h"
#include "myFunction.h"



 bool piping = false;
char ***splitByPipe(char **args) {
    char ***result = (char ***)malloc(sizeof(char **) * 1);
    int count = 0;
    int indexResult = 0;
    int size = 0;
    for (int i = 0; args[i]; i++) {
        count++;
        size++;
        if (strcmp(args[i], "|") == 0) {
            piping = true;
            result = (char ***)realloc(result, sizeof(char **) * (indexResult + 2));
            result[indexResult] = (char **)malloc(sizeof(char *) * count);
            for (int j = i - count + 1; j < count - 1; j++) {
                result[indexResult][j - (i - count + 1)] = args[j];
            }
            result[indexResult][count - 1] = NULL;
            indexResult++;
            count = 0;
        }
    }

    // Handle last substring
    if (piping) {
        result = (char ***)realloc(result, sizeof(char **) * (indexResult + 2));
        result[indexResult] = (char **)malloc(sizeof(char *) * (count + 1));
        for (int j = size - count; j < size; j++) {
            result[indexResult][j - (size - count)] = args[j];
        }
        result[indexResult][count] = NULL;
        indexResult++;
        result[indexResult] = NULL;
    } else {
        // If no pipe found, free and return NULL
        free(result);
        return NULL;
    }

    return result;
}

int main() {

    welcome();
 while (1)
    {
    piping = false;
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
char ***splitArgumentsArr = splitByPipe(arguments);
 if( errno !=0) continue;
      
        if (strcmp(input, "echo") == 0)
            echo(arguments);
       else if (strncmp(input, "cd", 2) == 0){
            cd(arguments);
        }    
        else if (strcmp(input, "cp") == 0)
            cp(arguments);
        if(strcmp(arguments[0], "read") == 0){
            readFile(arguments);
        }
        else if(strcmp(arguments[0], "echo") == 0){
            echorite(arguments);
        }
        else if(strcmp(arguments[0], "wc") == 0){
            wordCount(arguments);
        }
        else if(strcmp(arguments[0], "echo") == 0){
            echoppend(arguments);
        }
        else if(strcmp(arguments[0], "mv") == 0){
            move(arguments);
        }
        else if(strcmp(arguments[0], "delete") == 0){
            delete(arguments);
        }
        else if(strcmp(arguments[0], "dir") == 0){
            get_dir();
        }
         else if (piping)
        {
            mypipe(splitArgumentsArr[0], splitArgumentsArr[1]);
            wait(NULL);
            for(int i = 0; splitArgumentsArr[i]; i++){
                free(splitArgumentsArr[i]);
            }
            free(splitArgumentsArr);
        }
        else
        {
            systemCall(arguments);
            wait(NULL);
        }
        free(arguments);
        free(input);
    }
    return 0;
}


void welcome() {
    printf("Welcome to my Shell\n");
          printf("GitHub Username:\n");
        printf("__   __       _ _     _             \n");
        printf("\\ \\ / /__  __| (_) __| |_   _  __ _ \n");
        printf(" \\ V / _ \\/ _` | |/ _` | | | |/ _` |\n");
        printf("  | |  __/ (_| | | (_| | |_| | (_| |\n");
        printf("  |_|\\___|\\__,_|_|\\__,_|\\__, |\\__,_|\n");
        printf("                        |___/       \n");
        printf("\n");
}
