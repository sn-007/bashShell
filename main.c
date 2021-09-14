#include "standardHeaders.h"
#include "prompt.h"
#include "cleaningFunctions.h"
#include "getCommand.h"
#include <stdio.h>

unsigned long int n;
char * textInput;



int main()
{
    char newHome[100000]="";
    getcwd(newHome,sizeof(newHome));
    
    system("clear");
    while(1)
    {
        displayPrompt(newHome);
        getline(&textInput, &n, stdin);
        if(strcmp(textInput,"\n")==0 || textInput==NULL) continue;
        char* noSpaceTextInput =removeLeadingSpaces(textInput);
        noSpaceTextInput[strlen(noSpaceTextInput)-1] = '\0';
        breakAndProcess(noSpaceTextInput,newHome);
        

        

    }

}