#include "myFunction.h"

//פונקציה שמדפיסה הודעת פתיחה
void getLocation()  
{
    char location[SIZE_BUFF];
    char hostname[SIZE_BUFF];
    char* username;//משתנה מחרוזת

    username = getenv("USER");//קבלת המשתמש
    if (username == NULL)//בדיקה האם הקבלת המשתמש הצליחה
        printf("Error\n");
    else
    {
        if (getcwd(location, SIZE_BUFF) == NULL)//קבלת המיקום
            printf("Error\n");
        else
        {
            if (gethostname(hostname, SIZE_BUFF) == -1)//קבלת המארח
                printf("Error\n");
            else
            {
                printf("\033[1;34m%s@%s\033[0m:\033[0;32m%s\033[0m$ ", username, hostname, location); //הדפסת המיקום
                fflush(stdout);  
            }
        }
    }
}

//פונקציה שמקבלת קלט מהמשתמש ומחזירה מחרוזת
char *getInputFromUser()
{
    char ch;
    int size = 1;
    int index = 0;
    char *str = (char *)malloc(size * sizeof(char));//הקצאת זיכרון למחרוזת
    while ((ch = getchar()) != '\n')//לולאה שעוברת על הקלט מהמשתמש
    {
        *(str + index) = ch;//הכנסת התו למחרוזת
        size++;
        index++;
        str = (char *)realloc(str, size);//הקצאת זיכרון למחרוזת
    }
    *(str + index) = '\0';//הכנסת סיום מחרוזת
    return str;

}

//פונקציה שמקבלת מחרוזת ומחזירה מערך של מחרוזות
char **splitArgument(char *str) {
    int size = 2;//גודל המערך
    int index = 0;
    char *start = str;//התחלת המחרוזת
    char *end;//סיום המחרוזת
    char **arguments = (char **)malloc(size * sizeof(char *));//הקצאת זיכרון למערך של מחרוזות
    if (arguments == NULL) {//בדיקה האם הקצאת הזיכרון הצליחה
        perror("malloc");//הדפסת הודעת שגיאה
        exit(EXIT_FAILURE);
    }

if(*start ==' '){//אם המחרוזת מתחילה ברווח
        for (int i = 0; i < strlen(str); i++)//לולאה שעוברת על המחרוזת כדי למחוק את הרווחים בתחילת המחרוזת
        {
            if(*start!=' ') break;//אם התו הוא לא רווח יוצא מהלולאה
           start++;//מעבר לתו הבא
        }
       
    }
    while (*start != '\0') {//לולאה שעוברת על המחרוזת
        if (*start == '"') {//בדיקה האם התו הוא גרש
            end = strchr(start + 1, '"');//מציאת הגרש הבא
            if (end == NULL) {
                perror("missing \"");
                errno = EINVAL;//הדפסת הודעת שגיאה
                break;
            }
            start++;
            *end = '\0';//החלפת הגרש בסיום מחרוזת
            if (*(end + 1) == ' ') {//בדיקה האם יש רווח אחרי הגרש
                end += 2;//העברת הסיום לתו הבא
            } else if (*(end + 1) != '\0') {//בדיקה האם יש רווח אחרי הגרש
                perror("missing space after \"");
                 errno = EINVAL;//הדפסת הודעת שגיאה
                break;
            } else {
                end++;
            }
        } else {
            end = strchr(start, ' ');//מציאת הרווח הבא
            if (end != NULL) {//אם נמצא רווח
                *end = '\0';//החלפת הרווח בסיום מחרוזת
                end++;
            } else {
              
                end = start + strlen(start);//העברת הסיום לסוף המחרוזת
            }
        }
        arguments[index] = start;//הכנסת המחרוזת למערך
        index++;
        if (index >= size) {//בדיקה האם יש צורך להגדיל את המערך
            size += 2;
            arguments = (char **)realloc(arguments, size * sizeof(char *));//הקצאת זיכרון למערך של מחרוזות
            if (arguments == NULL) {//בדיקה האם הקצאת הזיכרון הצליחה
                perror("realloc");
                exit(EXIT_FAILURE);//יציאה מהתוכנית
            }
        }
        arguments[index] = NULL;//הכנסת NULL לסיום המערך
        start = end;//העברת המחרוזת לתחילת המחרוזת הבאה
    }
    return arguments;
}

//פונקציה שמקבלת מערך של מחרוזות ומדפיסה את המערך
void logout(char *input)//פונקציה שמקבלת מחרוזת ומפעילה פעולה כאשר המשתמש מתנתק
{
    free(input);
    puts("logout");
    exit(EXIT_SUCCESS); 
}

//פונקציה שמדפיסה הודעת פתיחה
void echo(char **arguments)
{
    while (*(++arguments))//לולאה שעוברת על המערך
        printf("%s ", *arguments);//הדפסת המחרוזת

    puts("");
}

//פונקציה שמקבלת מערך של מחרוזות ומחזירה את האורך של המערך
void cd(char **path) {
    if (path[2] != NULL) {//בדיקה האם יש יותר מדי ארגומנטים
        printf("-myShell: cd: too many arguments\n");
        return;
    } 
     if (chdir(path[1]) != 0)//שינוי התיקייה  
        printf("-myShell: cd: %s: No such file or directory\n", path[1]);
}

//פונקציה שמדפיסה את תוכן התיקייה
void cp(char **arguments)
{
    if(arguments[1]==NULL || arguments[2]==NULL){//בדיקה האם יש פחות מדי ארגומנטים
        puts("error");
        return;
    }
    if(arguments[3]!=NULL){//בדיקה האם יש יותר מדי ארגומנטים
        puts("error");
        return;
    }
    char ch;
    FILE *src, *des;//משתנה קובץ
    if ((src = fopen(arguments[1], "r")) == NULL)//פתיחת הקובץ לקריאה
    {
        puts("error");
        return;
    }

    if ((des = fopen(arguments[2], "w")) == NULL)//פתיחת הקובץ לכתיבה
    {
        puts("error");
        fclose(src);
        return;
    }
    while ((ch = fgetc(src)) != EOF)//לולאה שעוברת על הקובץ
        fputc(ch, des);

    fclose(src);
    fclose(des);
}
//פונקציה שמדפיסה את תוכן התיקייה
void get_dir()
{
    DIR *dir;//משתנה תיקייה
    struct dirent *ent;//משתנה קובץ
    if ((dir = opendir("./")) == NULL)//פתיחת התיקייה
    {
        perror("");//הדפסת הודעת שגיאה
        return;
    }
    while ((ent = readdir(dir)) != NULL)//לולאה שעוברת על הקבצים בתיקייה
        printf("%s ", ent->d_name);//הדפסת הקבצים
    puts("");
}

//פונקציה שמוחקת קובץ
void delete(char **path)
{
    if (unlink(path[1]) != 0)//מחיקת הקובץ
        printf("-myShell: delete: %s: No such file or directory\n", path[1]);
}

//פונקציה שמקבלת מערך של מחרוזות ומפעילה את התוכנית
void systemCall(char **arguments)
{
    pid_t pid = fork();//יצירת תהליך ילד
    if (pid == -1)//בדיקה האם היצירה הצליחה
    {
        printf("fork err\n");
        return;
    }
    if (pid == 0)//בדיקה האם זה התהליך הילד
    {
        if (execvp(arguments[0], arguments) == -1)//הרצת התוכנית
            exit(EXIT_FAILURE);
    }
}

//פונקציה שמקבלת מערך של מחרוזות ומעבירה את הקובץ ממקום למקום
void move(char **args) {
    if (rename(args[0], args[1]) != 0) {//העברת הקובץ
        printf("Cannot move file.\n");
    }
}

//פונקציה שמקבלת מערך של מחרוזות ומוסיפה תוכן לקובץ
void echoppend(char **args) {
    FILE *file;

    file = fopen(args[1], "a");//פתיחת הקובץ לכתיבה
    if (file == NULL) {
        printf("Cannot open file.\n");
        return;
    }

    fprintf(file, "%s", args[0]);//כתיבת המחרוזת לקובץ

    fclose(file);
}

//פונקציה שמקבלת מערך של מחרוזות ומכתוב תוכן לקובץ
void echorite(char **args) {
    FILE *file;

    file = fopen(args[1], "w");//פתיחת הקובץ לכתיבה
    if (file == NULL) {
        printf("Cannot open file.\n");
        return;
    }

    fprintf(file, "%s", args[0]);//כתיבת המחרוזת לקובץ

    fclose(file);
}

//פונקציה שמקבלת מערך של מחרוזות וקוראת תוכן מקובץ
void readFile(char **args) {
    FILE *file;
    char ch;

    file = fopen(args[0], "r");//פתיחת הקובץ לקריאה
    if (file == NULL) {
        printf("Cannot open file.\n");
        return;
    }

    while ((ch = fgetc(file)) != EOF) {//לולאה שעוברת על הקובץ
        putchar(ch);
    }

    fclose(file);
}

//פונקציה שמקבלת מערך של מחרוזות ומדפיסה את מספר השורות או המילים בקובץ
void wordCount(char **args) {
    FILE *file;//יצירת משתנה קובץ
    char ch;
    int lines = 0, words = 0, characters = 0;

    file = fopen(args[1], "r");//פתיחת הקובץ לקריאה
    if (file == NULL) {//בדיקה האם הקובץ נפתח
        printf("Cannot open file.\n");
        return;
    }

    while ((ch = fgetc(file)) != EOF) {//לולאה שעוברת על הקובץ
        characters++;//מוסיף למונה של התווים
        if (ch == '\n' || ch == '\0') {//בדיקה האם התו הוא סיום שורה או סיום קובץ
            lines++;
        }
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0') {//בדיקה האם התו הוא רווח, טאב או סיום שורה
            words++;
        }
    }

    if (args[0][1] == 'l') {
        printf("Lines: %d\n", lines);
    } else if (args[0][1] == 'w') {
        printf("Words: %d\n", words);
    }

    fclose(file);
}

//פונקציה שמקבלת מערך של מחרוזות ומחלקת את המערך לשני מערכים
void mypipe(char **argv1,char ** argv2){
    int fildes[2];//מערך של שני קובצי קריאה וכתיבה
    if (fork() == 0)//יצירת תהליך ילד
    {
        pipe(fildes);//יצירת פייפ
        if (fork() == 0)
        {
          
            close(STDOUT_FILENO);//סגירת הקלט
            dup(fildes[1]);//העברת הקלט לקובץ הכתיבה
            close(fildes[1]);
            close(fildes[0]);
            execvp(argv1[0], argv1);//הרצת התוכנית
        }
       
        close(STDIN_FILENO);
        dup(fildes[0]);
        close(fildes[0]);
        close(fildes[1]);
     
        execvp(argv2[0], argv2);
    }
}