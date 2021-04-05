#include <stdio.h>
#include <stdlib.h>
 
int main()
{
    FILE *iniFile = fopen("ini1.txt","r");
    char slowo[30];
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