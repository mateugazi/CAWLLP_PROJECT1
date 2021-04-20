#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    struct section{
        char* name;
        char* key;
        char* value;
    };

    struct section* result = NULL;
    result = malloc(3*sizeof(result));
    //printf("%i", sizeof(sections));
    FILE *iniFile = fopen(argv[1],"r");
    int size = 100;
    char *slowo = NULL;
    slowo = malloc(size * sizeof (char));
    int argSize = sizeof(argv[2])* sizeof(char);
    char *task = malloc(argSize);
    strcpy(task,argv[2]);

    char delim[10] = ".";
    char *ptr = strtok(task,delim);
    char taskSection[10000];
    char tmp[100] = "[";
//    char* tmp;
//    tmp = malloc(argSize + 2*sizeof(char));
//    strcpy(tmp, "[");
//    printf("%s\n", tmp);
    strcat(tmp,ptr);
//    printf("%s\n",ptr);
//    printf("%s\n", tmp);
    strcpy(taskSection,tmp);
    strcat(taskSection,"]\n");
    ptr = strtok(NULL,delim);
    char taskKey[100];

    strcpy(taskKey,ptr);

    //printf("task : %s %s",taskSection, taskKey);
    bool goodSection = false;
    bool endSearch = false;
    bool found = false;

    while(fgets(slowo, size, iniFile)!=NULL)
    {
        if(endSearch)break;
       //printf("%s", slowo);

        while (slowo[size] != '\n')
        {
            size += 1;
            slowo = realloc(slowo, size * sizeof(char));
            if (feof(iniFile)) break;
           // printf("%i\n", strlen(slowo));
        }

        switch (slowo[0])
        {

            //new section
            case '[':
                for(int i = 1; i < strlen(slowo)-2; i++)
                {
                   // printf("%c\t", slowo[i]);
                    if (!(isalnum(slowo[i]) || slowo[i] == '-'))
                    {
                       // printf("%c\n", slowo[i]);
                        printf("invalid name: %s ", slowo);
                        break;
                    }
                }
                if(!strcmp(slowo, taskSection))
                {
                    result->name = malloc(size);
                    strcpy(result->name, slowo);
                    goodSection = true;
                }
                else
                {
                    if(goodSection)
                    {
                        printf("Failed to find key %s in section %s", taskKey, taskSection);
                        endSearch = true;
                    }
                }

                break;
                //key-value
            case 'a' ... 'z':
                if(true)
                {

                   // strcpy(value,value);
                    strcpy(delim," = ");
                    ptr = strtok(slowo,delim);
                    char key[size];
                    strcpy(key,ptr);
                    ptr = strtok(NULL,delim);
                    char value[size];
                    strcpy(value,ptr);
                    for(int i = 1; i < strlen(key)-1; i++)
                    {
                       // printf("%c\t", key[i]);
                        if (!(isalnum(key[i]) || key[i] == '-'))
                        {
                            printf("%s is invalid key\n", key);
                            break;
                        }
                    }
                    for(int i = 1; i < strlen(value)-1; i++)
                    {
                       // printf("%c\t", key[i]);
                        if (!(isalnum(value[i]) || value[i] == '-'))
                        {
                            printf("%s is invalid value\n", value);
                            break;
                        }
                    }
                    if(!strcmp(key,taskKey))
                    {
                        result->key = malloc(size);
                        result->value = malloc(size);
                        strcpy(result->key, key);
                        strcpy(result->value, value);
                        printf("Founded value: %s", value);
                        found = true;
                        endSearch = true;
                    }
                }

                break;
                //comment and whitespace
            case ';':
            case '\n':
                break;
            default:
              // printf("input not recognised: %s",slowo);
                break;
        }
    }
    if(!goodSection)
    {
        printf("Failed to find section %s",taskSection);
    }
    free(slowo);

    if(found){
        printf("%s", result->name);
        printf("%s\n", result->key);

        printf("%s", result->value);

    }
    fclose(iniFile);
}
