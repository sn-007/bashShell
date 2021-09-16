#include "standardHeaders.h"
#include "prompt.h"
#include "cleaningFunctions.h"
#include "getCommand.h"
#include <stdio.h>
#include <string.h>




int main()
{
    char newHome[100000]="";
    getcwd(newHome,sizeof(newHome));
    
    
    
    system("clear");
    while(1)
    {
        unsigned long int n;
        char * textInput;

        displayPrompt(newHome);

        getline(&textInput, &n, stdin);

        if(strcmp(textInput,"\n")==0 || textInput==NULL) continue;

        char* noSpaceTextInput =removeLeadingSpaces(textInput);
        noSpaceTextInput[strlen(noSpaceTextInput)-1] = '\0'; //removing enter key
        breakAndProcess(noSpaceTextInput,newHome);
    }

}