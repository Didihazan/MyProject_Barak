#include "myShell.h"
#include "myFunction.h"



 bool piping = false;//משתנה שמציין אם יש פייפ במערך
 //פונקציה שמקבלת מערך של מחרוזות ומחזירה מערך של מערכים של מחרוזות
char ***splitByPipe(char **args) {
    char ***result = (char ***)malloc(sizeof(char **) * 1);//הקצאת זיכרון למערך של מערכים של מחרוזות
    int count = 0;
    int indexResult = 0;
    int size = 0;
    for (int i = 0; args[i]; i++) {//לולאה שעוברת על המערך כדי לספור כמה פייפים יש במערך
        count++;
        size++;
        if (strcmp(args[i], "|") == 0) {//אם המחרוזת היא פייפ
            piping = true;//הפייפ נמצא במערך
            result = (char ***)realloc(result, sizeof(char **) * (indexResult + 2));//הקצאת זיכרון למערך של מערכים של מחרוזות
            result[indexResult] = (char **)malloc(sizeof(char *) * count);//הקצאת זיכרון למערך של מחרוזות
            for (int j = i - count + 1; j < count - 1; j++) {//העתקת המחרוזות למערך של מחרוזות
                result[indexResult][j - (i - count + 1)] = args[j];
            }
            result[indexResult][count - 1] = NULL;//הכנסת NULL לסיום המערך
            indexResult++;//העברת האינדקס למערך הבא
            count = 0;//איפוס הספירה
        }
    }

  
    if (piping) {
        result = (char ***)realloc(result, sizeof(char **) * (indexResult + 2));//הקצאת זיכרון למערך של מערכים של מחרוזות
        result[indexResult] = (char **)malloc(sizeof(char *) * (count + 1));
        for (int j = size - count; j < size; j++) {//העתקת המחרוזות למערך של מחרוזות
            result[indexResult][j - (size - count)] = args[j];
        }
        result[indexResult][count] = NULL;//הכנסת NULL לסיום המערך
        indexResult++;//העברת האינדקס למערך הבא
        result[indexResult] = NULL;//הכנסת NULL לסיום המערך
    } else {
      
        free(result);
        return NULL;
    }

    return result;
}

int main() {

    welcome();
 while (1)
    {
    piping = false;//איפוס המשתנה שמציין אם יש פייפ במערך
        errno = 0;
        getLocation();//הדפסת המיקום
        char *input = getInputFromUser();//קליטת קלט מהמשתמש
        if (strcmp(input, "exit") == 0 || strncmp(input, "exit ", 5) == 0)//בדיקה האם הקלט הוא יציאה
            logout(input);

        char **arguments = splitArgument(input);//קריאה לפונקציה שמפעילה פעולה על הקלט
         if(strcmp(arguments[0], "exit") == 0){ //בדיקה האם הקלט הוא יציאה
            free(arguments);
            logout(input);
}
char ***splitArgumentsArr = splitByPipe(arguments);//קריאה לפונקציה שמפעילה פעולה על המערך של מחרוזות
 if( errno !=0) continue;//בדיקה האם יש שגיאה
      
        if (strcmp(input, "echo") == 0)//בדיקה האם הקלט הוא echo
            echo(arguments);
       else if (strncmp(input, "cd", 2) == 0){//בדיקה האם הקלט הוא cd
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
            mypipe(splitArgumentsArr[0], splitArgumentsArr[1]);//קריאה לפונקציה שמפעילה פעולה על המערך של מערכים של מחרוזות
            wait(NULL);//המתנה לסיום התהליך
            for(int i = 0; splitArgumentsArr[i]; i++){//לולאה שעוברת על המערך של מערכים של מחרוזות
                free(splitArgumentsArr[i]);//שחרור זיכרון
            }
            free(splitArgumentsArr);
        }
        else
        {
            systemCall(arguments);//קריאה לפונקציה שמפעילה פעולה על המערך של מחרוזות
            wait(NULL);//המתנה לסיום התהליך
        }
        free(arguments);
        free(input);
    }
    return 0;
}

//פונקציה שמדפיסה הודעת ברכה
void welcome() {
    printf("Welcome to my Shell\n");//הדפסת הודעת ברכה
          printf("GitHub Username:\n");
        printf("__   __       _ _     _             \n");
        printf("\\ \\ / /__  __| (_) __| |_   _  __ _ \n");
        printf(" \\ V / _ \\/ _` | |/ _` | | | |/ _` |\n");
        printf("  | |  __/ (_| | | (_| | |_| | (_| |\n");
        printf("  |_|\\___|\\__,_|_|\\__,_|\\__, |\\__,_|\n");
        printf("                        |___/       \n");
        printf("\n");
}