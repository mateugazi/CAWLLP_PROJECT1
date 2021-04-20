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
    struct section* result2 = NULL;
    result2 = malloc(3*sizeof(result2));
    //printf("%i", sizeof(sections));
    FILE *iniFile = fopen(argv[1],"r");
    int size = 100;
    char *slowo = NULL;
    slowo = malloc(size * sizeof (char));
    char *task = NULL;
    char *task2 = NULL;
    char *expression = NULL;
    
    if(!strcmp(argv[2], "expression"))
    {
        task = malloc(sizeof(argv[3])* sizeof(char));
        strcpy(task,argv[3]);
        expression = malloc(sizeof(argv[4])* sizeof(char));
        strcpy(expression,argv[4]);
        task2 = malloc(sizeof(argv[5])* sizeof(char));
        strcpy(task2,argv[5]);
    }else{
        task = malloc(sizeof(argv[2])* sizeof(char));
        strcpy(task,argv[2]);
    }
    
    char delim[10] = ".";
    char *ptr = strtok(task,delim);
    char taskSection[10000];
    char tmp[100] = "[";

    strcat(tmp,ptr);

    strcpy(taskSection,tmp);
    strcat(taskSection,"]\n");
    ptr = strtok(NULL,delim);
    char taskKey[100];

    strcpy(taskKey,ptr);

    ptr = strtok(task2,delim);
    char task2Section[10000];
    char tmp2[100] = "[";
    strcat(tmp2,ptr);

    strcpy(task2Section,tmp2);
    strcat(task2Section,"]\n");
    ptr = strtok(NULL,delim);
    char task2Key[100];

    strcpy(task2Key,ptr);

    //printf("task : %s %s",taskSection, taskKey);
    //printf("task : %s %s",task2Section, task2Key);
    int goodSection = 0;
    bool endSearch = false;
    bool found = false;

    while(fgets(slowo, size, iniFile)!=NULL)
    {
        //if(endSearch)break;
       //printf("%s", slowo);

        while (slowo[size] != '\n')
        {
            
            slowo = realloc(slowo, size * sizeof(char));
            if (feof(iniFile)) break;
            size += 1;
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
                    goodSection = 1;
                }
                else if(task2Section!=NULL && !strcmp(slowo, task2Section))
                {
                    result2->name = malloc(size);
                    strcpy(result2->name, slowo);
                    goodSection = 2;
                }
                else{
                    goodSection = 0;
                }
                // else
                // {
                //     if(goodSection>0)
                //     {
                //         printf("Failed to find key %s in section %s", taskKey, taskSection);
                //         endSearch = true;
                //     }
                // }

                break;
                //key-value
            case 'a' ... 'z':
            if(1)
            {
                // strcpy(value,value);
                strcpy(delim," = ");
                ptr = strtok(slowo,delim);
                char key[size];
                strcpy(key,ptr);
                ptr = strtok(NULL,delim);
                ptr[strlen(ptr)-1]='\0';
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
                    if(goodSection!=1)break;
                    result->key = malloc(size);
                    result->value = malloc(size);
                    strcpy(result->key, key);
                    strcpy(result->value, value);
                    //printf("Founded value: %s", value);
                    found = true;
                }
                if(task2Key!=NULL && !strcmp(key,task2Key))
                {
                    if(goodSection!=2)break;
                    result2->key = malloc(size);
                    result2->value = malloc(size);
                    strcpy(result2->key, key);
                    strcpy(result2->value, value);
                    //printf("Founded value2: %s", value);
                    found = true;
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

    
    if(!strcmp(argv[2], "expression"))
    {
        bool string = false;
        bool string2 = false;
        int num = 0;
        for(int i=0;i<strlen(result->value);i++)
        {
            if(result->value[i]>'9' || result->value[i]<'0')
            {
                //printf("3 %s %d",result2->value[i],sizeof(result->value));
                string = true;
                break;
            }
            else{
                int x=1;
                for(int j=0;j<strlen(result->value)-i-1;j++)x=x*10;
                num+= x*(result->value[i]-'0');
            }
        }
        int num2 = 0;
        for(int i=0;i<strlen(result2->value);i++)
        {
            if(result2->value[i]>'9' || result2->value[i]<'0')
            {
                string2 = true;
                break;
            }
            else{
                int x=1;
                for(int j=0;j<strlen(result2->value)-i-1;j++)x=x*10;
                num2+= x*(result2->value[i]-'0');
            }
        }
        
        if(string && string2)
        {
            if(expression[0] == '+')
            {
                printf("%s%s", result->value, result2->value);
            }
            else
            {
                printf("invalid expression");
            }
            
        }else if (!string && !string2)
        {
            //printf("testing %d %d", num, num2);
            switch(expression[0])
            {
                case '+':
                    printf("%d",num+num2);
                    break;
                case '-':
                    printf("%d",num-num2);
                    break;
                case '*':
                    printf("%d",num*num2);
                    break;
                case '/':
                    printf("%d",num/num2);
                    break;
                default:
                    printf("invalid expression");
                    break;
            }
        }
        else{
            printf("invalid expression");
        }
    }
    else if(found){
        printf("%s", result->name);
        printf("%s\n", result->key);

        printf("%s", result->value);

    }
    
    fclose(iniFile);
}
