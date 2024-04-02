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

char **splitArgument(char *str) {
    int size = 2;
    int index = 0;
    char *start = str;
    char *end;
    char **arguments = (char **)malloc(size * sizeof(char *));
    if (arguments == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while (*start != '\0') {
        if (*start == '"') {
            end = strchr(start + 1, '"');
            if (end == NULL) {
                perror("missing \"");
                errno = EINVAL;
                break;
            }
            start++;
            *end = '\0';
            if (*(end + 1) == ' ') {
                end += 2;
            } else if (*(end + 1) != '\0') {
                perror("missing space after \"");
                 errno = EINVAL;
                break;
            } else {
                end++;
            }
        } else {
            end = strchr(start, ' ');
            if (end != NULL) {
                *end = '\0';
                end++;
            } else {
                // Handle the case when there is no space at the end of the string
                end = start + strlen(start);
            }
        }
        arguments[index] = start;
        index++;
        if (index >= size) {
            size += 2;
            arguments = (char **)realloc(arguments, size * sizeof(char *));
            if (arguments == NULL) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }
        arguments[index] = NULL; // Null-terminate the array
        start = end;
    }
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