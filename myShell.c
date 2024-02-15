#include "myShell.h"
#include "myFunction.h"
int main()
{
    welcome();
    while (1)
    {
        getLocation();
        char *input = getInputFromUser();
        puts(input);
        char **arguments = splitArgument(input);
        for (int i = 0; *(arguments + i) != NULL; i++)
        {
            puts(*(arguments+i));
            puts(arguments[i]);
        }

        free(arguments);
        free(input);

        break;
    }
    return 0;
}
// יש לכתוב את פונקציית הברוכים הבאים כרצונכם אבל קצת יותר ממה שמוצג מטה לדוגמא:
//                     aSPY//YASa       
//              apyyyyCY//////////YCa       |
//             sY//////YSpcs  scpCY//Pp     | Welcome to myShell
//  ayp ayyyyyyySCP//Pp           syY//C    | Version 2.4.3
//  AYAsAYYYYYYYY///Ps              cY//S   |
//          pCCCCY//p          cSSps y//Y   | https://github.com/<user>
//          SPPPP///a          pP///AC//Y   |
//               A//A            cyP////C   | Have fun!
//               p///Ac            sC///a   |
//               P////YCpc           A//A   | Craft packets like it is your last
//        scccccp///pSP///p          p//Y   | day on earth.
//       sY/////////y  caa           S//P   |                      -- Lao-Tze
//        cayCyayP//Ya              pY/Ya   |
//         sY/PsY////YCc          aC//Yp 
//          sc  sccaCY//PCypaapyCP//YSs  
//                   spCPY//////YPSps    
//                        ccaacs         
//                                        using c 
void welcome()
{
    puts("Welcome to my Shell");
}