#include "myFunction.h"

// בפונקציה הנ"ל קיבלנו את הנתיב ממנו אנחנו מריצים את התוכנית שלנו
//  עליכם לשדרג את הנראות של הנתיב כך ש-בתחילת הנתיב יופיע שם המחשב (כמו בטרמינל המקורי) בסוף יופיע הסימן דולר
//  ולאחר הדולר ניתן אפשרות למשתמש להזין מחרוזת מבלי שנרד שורה.
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE_BUFF 1024

void getLocation()  // מגדיר פונקציה שמחזירה את הנתיב הנוכחי
{
    char location[SIZE_BUFF];  // מגדיר מערך של תווים לשמירת הנתיב
    char hostname[SIZE_BUFF];  // מגדיר מערך של תווים לשמירת שם המחשב
    if (getcwd(location, SIZE_BUFF) == NULL)
        printf("Error\n");
    else
    {
        if (gethostname(hostname, SIZE_BUFF) == -1)
            printf("Error\n");
        else
        {
            printf("\033[0;33m%s\033[0m:\033[0;32m%s\033[0m$ ", hostname, location);// מדפיס את שם המחשב בצבע כתום, את הנתיב בצבע ירוק, ואת סימן הדולר
            fflush(stdout);   // מרוקן את הבאפר של הפלט כדי לוודא שהפלט מודפס מיד
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
    //[cp,file,file,NULL]
    
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
    char **arguments = (char **)malloc(size * sizeof(char *));// מקצה זיכרון למערך של מחרוזות
    char *start = str;
    char *end;

    while ((end = strchr(start, ' ')) != NULL)// מחפש את המרחק הראשון של הרווח
    {
        arguments[index] = (char *)malloc((end - start + 1) * sizeof(char)); // מקצה זיכרון למחרוזת
        strncpy(arguments[index], start, end - start);// מעתיק את התת-מחרוזת לתוך המערך
        arguments[index][end - start] = '\0'; // מסיים את המחרוזת בתו NULL
        start = end + 1;
        index++;
        size++;
        arguments = (char **)realloc(arguments, size * sizeof(char *));// מגדיל את הזיכרון שהוקצה למערך של הארגומנטים
    }

   // מוסיף את הארגומנט האחרון
    arguments[index] = strdup(start);
    size++;
    arguments = (char **)realloc(arguments, size * sizeof(char *));
    arguments[size - 1] = NULL; 

    return arguments;
}

// בכל שינוי יש לבצע קומיט מתאים העבודה מחייבת עבודה עם גיט.
// ניתן להוסיף פונקציות עזר לתוכנית רק לשים לב שלא מוסיפים את חתימת הפונקציה לקובץ הכותרות
