#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *iniFile = fopen(argv[1],"r");
    char slowo[30];
    char task [62];
    strcpy(task,argv[2]);
    while(fgets(slowo, sizeof slowo, iniFile)!=NULL)
    {
        printf("%s",slowo);
        switch (slowo[0])
        {
        //comment
        case ';':
            printf("comment \n");
            break;
        //new section
        case '[':
            printf("section \n");
            break;
        //key-value
        case 'a' ... 'z':
            printf("key-value \n");
            break;
        //whitespace
        case '\n':
            printf("whitespace \n");
            break;
        default:
            printf("din not recognise \n");
            break;
        }
    }
    
    


    fclose(iniFile);
}