#include "myFunction.h"

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

char *tokenize_next_segment(char *str, const char delim, int check_quotes) {
    static char *next_segment = NULL; 
    char *segment;
    static int quotes_mode;

    if (str != NULL) { 
        segment = str; 
        next_segment = NULL; 
        quotes_mode = check_quotes;
    } 
    else {
        if (next_segment == NULL) { 
            return NULL;
        }
        segment = next_segment;
    }

    if (quotes_mode) {
        if (*segment == '"') {
            segment++;
            char *quote_end = strchr(segment, '"');
            if (quote_end != NULL) {
                next_segment = quote_end;
                *next_segment = '\0';
                next_segment++;
                if (*next_segment == '\0') {
                    next_segment = NULL;
                } else {
                    next_segment++;
                }
                return segment;
            }
            segment--;
        }
    }

    int segment_length = strlen(segment);
    if (*segment == delim) {
        for (int i = 0; i < segment_length; i++) {
            if (*(segment + i) != delim) {
                segment = segment + i;
                break;
            }
        }
    }
    
    for (int i = 0; i < strlen(segment); i++) { 
        if (*(segment + i) == delim && *(segment + i + 1) != delim) {
            next_segment = segment + i;
            break;
        }
        if (i == strlen(segment) - 1) {
            next_segment = NULL;
        }
    }
    
    if (next_segment != NULL) {
        *next_segment = '\0';
        next_segment++;
    }

    return segment;
}


char **splitArgument(char *str) {
    char *subStr;
    subStr = tokenize_next_segment(str, ' ', 1);
    int size = 2;
    int index = 0;
    char **arguments = (char **)malloc(size * sizeof(char *));
    *(arguments + index) = subStr;
    while ((subStr = tokenize_next_segment(NULL, ' ', 1)) != NULL) {
        index++;
        size++;
        arguments = (char **)realloc(arguments, size * sizeof(char *));
        *(arguments + index) = subStr;
    }
    *(arguments + (index + 1)) = NULL;

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
    printf("petch 2", path[2]);
    if (path[2] != NULL) {
        printf("-myShell: cd: too many arguments\n");
        return;
    } 
     if (chdir(path[1]) != 0)  
        printf("-myShell: cd: %s: No such file or directory\n", path[1]);
}


void cp(char **arguments)
{
    char ch;
    FILE *src, *des;
    char *source_path = NULL;
    char *destination_path = NULL;

    for (int i = 1; arguments[i] != NULL; i++) {
        if (strcmp(arguments[i], "-") == 0) {
            // Next argument should be a path
            if (arguments[i + 1] != NULL) {
                if (source_path == NULL)
                    source_path = arguments[i + 1];
                else if (destination_path == NULL)
                    destination_path = arguments[i + 1];
                i++; // Skip the next argument
            } else {
                printf("Missing path after '-'.\n");
                return;
            }
        } else {
            printf("Invalid option: %s\n", arguments[i]);
            return;
        }
    }

    if (source_path == NULL || destination_path == NULL) {
        printf("Missing source or destination path.\n");
        return;
    }

    if ((src = fopen(source_path, "r")) == NULL)
    {
        printf("Error opening source file: %s\n", source_path);
        return;
    }

    if ((des = fopen(destination_path, "w")) == NULL)
    {
        printf("Error opening destination file: %s\n", destination_path);
        fclose(src);
        return;
    }

    while ((ch = fgetc(src)) != EOF)
        fputc(ch, des);

    fclose(src);
    fclose(des);

    printf("File copied successfully from %s to %s.\n", source_path, destination_path);
}

void get_dir()
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("./")) == NULL)
    {
        perror("");
        return;
    }
    while ((ent = readdir(dir)) != NULL)
        printf("%s ", ent->d_name);
    puts("");
}


void delete(char **path)
{
    if (unlink(path[1]) != 0)
        printf("-myShell: delete: %s: No such file or directory\n", path[1]);
}

void systemCall(char **arguments)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        printf("fork err\n");
        return;
    }
    if (pid == 0)
    {
        if (execvp(arguments[0], arguments) == -1)
            exit(EXIT_FAILURE);
    }
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