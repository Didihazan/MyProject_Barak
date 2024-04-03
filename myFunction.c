#include "myFunction.h"


void getLocation()  //פונקציה להצגת המיקום הנוכחי
{
    // מגדיר משתנים של מחרוזות שיכילו את המיקום והשם של המחשב
    char location[SIZE_BUFF];
    char hostname[SIZE_BUFF]; 
    char* username;

    // משיג את שם המשתמש מהמשתנה הסביבתי "USER"
    username = getenv("USER");
    if (username == NULL)
        // אם המשתנה הסביבתי "USER" לא קיים, מדפיס שגיאה
        printf("Error\n");
    else
    {
        // משיג את המיקום הנוכחי של התיקייה בה אנחנו נמצאים
        if (getcwd(location, SIZE_BUFF) == NULL)
            // אם לא הצליח לשיג את המיקום, מדפיס שגיאה
            printf("Error\n");
        else
        {
            // משיג את שם המחשב
            if (gethostname(hostname, SIZE_BUFF) == -1)
                // אם לא הצליח לשיג את שם המחשב, מדפיס שגיאה
                printf("Error\n");
            else
            {
                // מדפיס את שם המשתמש, שם המחשב והמיקום הנוכחי בצורה מסוימת
                printf("\033[1;34m%s@%s\033[0m:\033[0;32m%s\033[0m$ ", username, hostname, location); 
                // פורט את הפלאש ומנקה את הזיכרון
                fflush(stdout);  
            }
        }
    }
}


char *getInputFromUser()//קליטת קלט מהמשתמש
{
    char ch;
    int size = 1;
    int index = 0;
    char *str = (char *)malloc(size * sizeof(char));//הקצאת זיכרון למחרוזת
    while ((ch = getchar()) != '\n')//קליטת תווים מהמשתמש עד לחיצת אנטר
    {
        *(str + index) = ch;//הכנסת התו למחרוזת
        size++;//הגדלת המערך
        index++;//הגדלת האינדקס
        str = (char *)realloc(str, size);//הרחבת המערך
    }
    *(str + index) = '\0';//הוספת סיומת למחרוזת
    return str;//החזרת המחרוזת

}


char **splitArgument(char *str) {//פיצול מחרוזת למערך של מחרוזות
    int size = 2;
    int index = 0;
    char *start = str;//הצבת המצביע לתחילת המחרוזת
    char *end;//הצבת המצביע לסיום המחרוזת
    char **arguments = (char **)malloc(size * sizeof(char *));//הקצאת זיכרון למערך של מחרוזות
    if (arguments == NULL) {//בדיקה האם הקצאת הזיכרון הצליחה
        perror("malloc");//הדפסת שגיאה
        exit(EXIT_FAILURE);//יציאה מהתוכנית
    }

    while (*start != '\0') {//לולאה שרצה עד שהגענו לסוף המחרוזת
        if (*start == '"') {//בדיקה האם התו הנוכחי הוא גרש
            end = strchr(start + 1, '"');//מציאת הגרש הבא
            if (end == NULL) {//בדיקה האם לא נמצא גרש נוסף
                perror("missing \"");//הדפסת שגיאה
                errno = EINVAL;//הגדרת שגיאה
                break;
            }
            start++;//הזזת המצביע לאחר הגרש
            *end = '\0';//החלפת הגרש בסיומת
            if (*(end + 1) == ' ') {//בדיקה האם אחרי הגרש יש רווח
                end += 2;//הזזת המצביע לאחר הרווח
            } else if (*(end + 1) != '\0') {//בדיקה האם אחרי הגרש יש תו אחר
                perror("missing space after \"");//הדפסת שגיאה
                 errno = EINVAL;//הגדרת שגיאה
                break;
            } else {
                end++;//הזזת המצביע לתו הבא
            }
        } else {
            end = strchr(start, ' ');//מציאת הרווח הבא
            if (end != NULL) {//בדיקה האם נמצא רווח
                *end = '\0';//החלפת הרווח בסיומת
                end++;//הזזת המצביע לתו הבא
            } else {
            
                end = start + strlen(start);//הזזת המצביע לסוף המחרוזת
            }
        }
        arguments[index] = start;//הכנסת המחרוזת למערך
        index++;//הגדלת האינדקס
        if (index >= size) {//בדיקה האם הגענו לגודל המערך
            size += 2;//הגדלת המערך
            arguments = (char **)realloc(arguments, size * sizeof(char *));//הרחבת המערך
            if (arguments == NULL) {//בדיקה האם הרחבת המערך הצליחה
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }
        arguments[index] = NULL; //הכנסת סיומת למערך
        start = end;//הזזת המצביע לתחילת המחרוזת הבאה
    }
    return arguments;
}


void logout(char *input)//פונקציה ליציאה מהתוכנית
{
    free(input);
    puts("logout");
    exit(EXIT_SUCCESS); //יציאה מהתוכנית
}


void echo(char **arguments)//פונקציה להדפסת מחרוזות
{

    // int i = 1;
    // while (*(arguments + i))
    //     printf("%s ", *(arguments + i));
    // i=1
    // while (arguments[i])
    //     printf("%s ", arguments[i]);

    while (*(++arguments))//הדפסת המחרוזות שנמצאות במערך
        printf("%s ", *arguments);//הדפסת המחרוזת

    puts("");//הדפסת שורה חדשה
}


void cd(char **path) {//פונקציה לשינוי תיקייה
    if (path[2] != NULL) {//בדיקה האם יש יותר מדי ארגומנטים
        printf("-myShell: cd: too many arguments\n");
        return;
    } 
     if (chdir(path[1]) != 0)  //בדיקה האם הצליח לשנות את התיקייה
        printf("-myShell: cd: %s: No such file or directory\n", path[1]);
}


void cp(char **arguments)//פונקציה להעתקת קובץ
{
    if(arguments[1]==NULL || arguments[2]==NULL){//בדיקה האם יש מספר לא תקין של ארגומנטים
        puts("error");
        return;
    }
    if(arguments[3]!=NULL){//בדיקה האם יש מספר לא תקין של ארגומנטים
        puts("error");
        return;
    }
    char ch;
    FILE *src, *des;//הגדרת משתנים לקבצים
    if ((src = fopen(arguments[1], "r")) == NULL)//פתיחת קובץ מקור
    {
        puts("error");
        return;
    }

    if ((des = fopen(arguments[2], "w")) == NULL)//פתיחת קובץ יעד
    {
        puts("error");
        fclose(src);//סגירת הקובץ המקורי
        return;
    }
    while ((ch = fgetc(src)) != EOF)//העתקת התוכן מהקובץ המקורי לקובץ היעד
        fputc(ch, des);//הכנסת התו לקובץ היעד

    fclose(src);
    fclose(des);
}


void get_dir()//פונקציה להצגת קבצים בתיקייה
{
    DIR *dir;//משתנה לתיקייה
    struct dirent *ent;//משתנה לקבצים בתיקייה
    if ((dir = opendir("./")) == NULL)//פתיחת התיקייה
    {
        perror("");
        return;
    }
    while ((ent = readdir(dir)) != NULL)//הדפסת קבצים בתיקייה
        printf("%s ", ent->d_name);//הדפסת שם הקובץ
    puts("");
}


void delete(char **path)//פונקציה למחיקת קובץ
{
    if (unlink(path[1]) != 0)//בדיקה האם הצליח למחוק את הקובץ
        printf("-myShell: delete: %s: No such file or directory\n", path[1]);
}


void systemCall(char **arguments)//פונקציה להפעלת תוכניות
{
    pid_t pid = fork();//יצירת תהליך ילד
    if (pid == -1)//בדיקה האם הצליח ליצור תהליך
    {
        printf("fork err\n");
        return;
    }
    if (pid == 0)//בדיקה האם זה התהליך הילד
    {
        if (execvp(arguments[0], arguments) == -1)//הפעלת התוכנית
            exit(EXIT_FAILURE);//יציאה מהתהליך
    }
}


void move(char **args) {//פונקציה להעברת קובץ
    if (rename(args[0], args[1]) != 0) {//בדיקה האם הצליח להעביר את הקובץ
        printf("Cannot move file.\n");
    }
}


void echoppend(char **args) {//פונקציה להוספת מחרוזת לקובץ
    FILE *file;//משתנה לקובץ

    file = fopen(args[1], "a");//פתיחת קובץ לכתיבה
    if (file == NULL) {//בדיקה האם הצליח לפתוח את הקובץ
        printf("Cannot open file.\n");
        return;
    }

    fprintf(file, "%s", args[0]);//הוספת המחרוזת לקובץ

    fclose(file);
}


void echorite(char **args) {//פונקציה לכתיבת מחרוזת לקובץ
    FILE *file;//משתנה לקובץ

    file = fopen(args[1], "w");//פתיחת קובץ לכתיבה
    if (file == NULL) {//בדיקה האם הצליח לפתוח את הקובץ
        printf("Cannot open file.\n");
        return;
    }

    fprintf(file, "%s", args[0]);//הוספת המחרוזת לקובץ

    fclose(file);
}


void readFile(char **args) {//פונקציה לקריאת קובץ
    FILE *file;//משתנה לקובץ
    char ch;

    file = fopen(args[0], "r");//פתיחת קובץ לקריאה
    if (file == NULL) {//בדיקה האם הצליח לפתוח את הקובץ
        printf("Cannot open file.\n");
        return;
    }

    while ((ch = fgetc(file)) != EOF) {//הדפסת הקובץ
        putchar(ch);//הדפסת התו
    }

    fclose(file);
}


void wordCount(char **args) {//פונקציה לספירת מילים ושורות בקובץ
    FILE *file;//משתנה לקובץ
    char ch;
    int lines = 0, words = 0, characters = 0;//משתנים לספירת שורות, מילים ותווים

    file = fopen(args[1], "r");//פתיחת קובץ לקריאה
    if (file == NULL) {//בדיקה האם הצליח לפתוח את הקובץ
        printf("Cannot open file.\n");
        return;
    }

    while ((ch = fgetc(file)) != EOF) {//ספירת שורות, מילים ותווים
        characters++;//הגדלת מונה התווים
        if (ch == '\n' || ch == '\0') {//בדיקה האם יש סיום שורה
            lines++;//הגדלת מונה השורות
        }
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0') {//בדיקה האם יש רווח, טאב או סיום שורה
            words++;//הגדלת מונה המילים
        }
    }

    if (args[0][1] == 'l') {//בדיקה האם צריך להדפיס את מספר השורות
        printf("Lines: %d\n", lines);//הדפסת מספר השורות
    } else if (args[0][1] == 'w') {//בדיקה האם צריך להדפיס את מספר המילים
        printf("Words: %d\n", words);//הדפסת מספר המילים
    }

    fclose(file);
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