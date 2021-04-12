#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    FILE *iniFile = fopen(argv[1],"r");
    char slowo[100];
    char task [62];
    strcpy(task,argv[2]);

    char delim [10] = ".";
    char *ptr = strtok(task,delim);
    char taskSection[30];
    char tmp[32] = "[";
    strcat(tmp,ptr);
    strcpy(taskSection,tmp);
    strcat(taskSection,"]\n");

    ptr = strtok(NULL,delim);
    char taskKey[30];
    strcpy(taskKey,ptr);

    //printf("task : %s %s",taskSection, taskKey);
    bool goodSection = false;

    while(fgets(slowo, sizeof slowo, iniFile)!=NULL)
    {
        switch (slowo[0])
        {
        //new section
        case '[':
            
            if(!strcmp(slowo, taskSection))
            {
                goodSection = true;
            }
            else
            {
                goodSection = false;
            }

            break;
        //key-value
        case 'a' ... 'z':
            if(goodSection)
            {
                strcpy(delim," = ");
                ptr = strtok(slowo,delim);
                char key[30];
                strcpy(key,ptr);

                ptr = strtok(NULL,delim);
                char value[30];
                strcpy(value,ptr);
                if(!strcmp(key,taskKey))
                {
                    printf("%s", value);
                }
            }
            
            break;
        //comment and whitespace
        case ';':
        case '\n':
            break;
        default:
            printf("input not recognised: %s",slowo);
            break;
        }
    }
    
    


    fclose(iniFile);
}