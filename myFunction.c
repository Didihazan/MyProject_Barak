#include "myFunction.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// בפונקציה הנ"ל קיבלנו את הנתיב ממנו אנחנו מריצים את התוכנית שלנו
//  עליכם לשדרג את הנראות של הנתיב כך ש-בתחילת הנתיב יופיע שם המחשב (כמו בטרמינל המקורי) בסוף יופיע הסימן דולר
//  ולאחר הדולר ניתן אפשרות למשתמש להזין מחרוזת מבלי שנרד שורה.


// #define SIZE_BUFF 1024

void getLocation()  
{
    char location[SIZE_BUFF];
    char hostname[SIZE_BUFF]; 
    char* username;

    username = getenv("USER");
    if (username == NULL)
        printf("Error\n");
    else
    {
        if (getcwd(location, SIZE_BUFF) == NULL)
            printf("Error\n");
        else
        {
            if (gethostname(hostname, SIZE_BUFF) == -1)
                printf("Error\n");
            else
            {
                printf("\033[1;34m%s@%s\033[0m:\033[0;32m%s\033[0m$ ", username, hostname, location); 
                fflush(stdout);  
            }
        }
    }
}


char *getInputFromUser()
{
    char ch;
    int size = 1;
    int index = 0;
    char *str = (char *)malloc(size * sizeof(char));
    while ((ch = getchar()) != '\n')
    {
        *(str + index) = ch;
        size++;
        index++;
        str = (char *)realloc(str, size);
    }
    *(str + index) = '\0';
    return str;

}

// עליכם לממש את הפונקציה strtok כלומר שהפונקציה הנ"ל תבצע בדיוק אותו הדבר רק בלי השימוש בפונקציה strtok

    // cp file file
    // [cp,file,file,NULL]
    
    // cp\0file file
    // hello1\0hello2\0hello3\0hello4\0
    // subStr = address of 'h'
    // str = address of 'h'
    // int i=0;
    // int startIndex=0;
    // while(*str+i!=' '){
    // }
    // *(str+i)='\0';
    // // [str+startIndex,]
    // startIndex=++i;
    // while(*str+i!=' '){
    // }
    // *(str+i)='\0';
    // // [str+startIndex,str+startIndex]
    // startIndex=++i;

char **splitArgument(char *str)
{
    int size = 2;
    int index = 0;
    char **arguments = (char **)malloc(size * sizeof(char *));
    char *start = str;
    char *end;

for ( int i = 0; i < strlen(str); i++)
{
    if(str[i]==' ')
        start++;
}

    while ((end = strchr(start, ' ')) != NULL)
    {
        arguments[index]=start;
        arguments[index][end - start] = '\0';
        start = end + 1;
        index++;
        size++;
        arguments = (char **)realloc(arguments, size * sizeof(char *));
    }

    arguments[index] = strdup(start);
    size++;
    arguments = (char **)realloc(arguments, size * sizeof(char *));
    arguments[size - 1] = NULL; 

    return arguments;
}


void logout(char *input)
{
    free(input);
    puts("logout");
    exit(EXIT_SUCCESS); // EXIT_SUCCESS = 0
}


void echo(char **arguments)
{

    // int i = 1;
    // while (*(arguments + i))
    //     printf("%s ", *(arguments + i));
    // i=1
    // while (arguments[i])
    //     printf("%s ", arguments[i]);

    while (*(++arguments))
        printf("%s ", *arguments);

    puts("");
}
//לקחת את המחרוזת, ולהוריד את הרווחים בין כל המילים שיש בתוך הגרשיים (את ה\0)

void cd(char **path) {
    if (strncmp(path[1], "\"", 1) != 0 && path[2] != NULL) {
        printf("-myShell: cd: too many arguments\n");
        return;
    } // בדיקה האם יש יותר מדי ארגומנטים

    else if (strncmp(path[1], "\"", 1) == 0) { // אם יש גרש בהתחלה
        int i = 2; //אחרי הלולאה המשתנה i יכיל את המיקום של הארגומנט האחרון
        while (path[i] != NULL) {
            i++;
        }
        int size = strlen(path[i - 1])-1; // אורך הארגומנט האחרון
        if(strcmp(path[i - 1]+size, "\"") != 0){ //בדיקה אם יש גרש בסוף
           printf("-myShell: cd: too many arguments\n");
            return;
        }
        char *temp = (char *)malloc((strlen(path[1]) + 1) * sizeof(char)); // הקצאת זכרון למחרוזת שאמורה להחזיק את הנתיב
        strcpy(temp, path[1]); // העתקת המחרוזת למשתנה הזמני
        strcat(temp, " "); // הוספת רווח בסוף המחרוזת
        memmove(temp,temp+1,strlen(temp));// מחיקת הגרש
        for(int j=2;j<i;j++){
            temp = (char *)realloc(temp,((strlen(path[j])+2) * sizeof(char))); //הוספת מקום למחרוזת הבאה
            if(j == i-1){ // אם זה הארגומנט האחרון
                strcat(temp, path[j]); // הוספת הארגומנט למחרוזת
                 temp[strlen(temp)-1] = '\0'; // מחיקת הגרש
            }else{
               strcat(temp, path[j]); // הוספת הארגומנט למחרוזת
                 strcat(temp, " "); // הוספת רווח בסוף המחרוזת
            }  
        }
        if (chdir(temp) != 0) { // בדיקה האם הצלחתי לשנות נתיב
            printf("-myShell: cd: %s: No such file or directory", temp);
        }
        free(temp);
    }
    else if (chdir(path[1]) != 0)  
        printf("-myShell: cd: %s: No such file or directory\n",path[1]);
}


void cp(char **arguments)
{
    char ch;
    FILE *src, *des;
    if ((src = fopen(arguments[1], "r")) == NULL)
    {
        puts("error");
        return;
    }

    if ((des = fopen(arguments[2], "w")) == NULL)
    {
        puts("error");
        fclose(src);
        return;
    }
    while ((ch = fgetc(src)) != EOF)
        fputc(ch, des);

    fclose(src);
    fclose(des);
}


void mypipe(char **argv1,char ** argv2){

    int fildes[2];
    if (fork() == 0)
    {
        pipe(fildes);
        if (fork() == 0)
        {
            /* first component of command line */
            close(STDOUT_FILENO);
            dup(fildes[1]);
            close(fildes[1]);
            close(fildes[0]);
            execvp(argv1[0], argv1);
        }
        /* 2nd command component of command line */
        close(STDIN_FILENO);
        dup(fildes[0]);
        close(fildes[0]);
        close(fildes[1]);
        /* standard input now comes from pipe */
        execvp(argv2[0], argv2);
    }
}