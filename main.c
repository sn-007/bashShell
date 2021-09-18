#include "standardHeaders.h"
#include "prompt.h"
#include "cleaningFunctions.h"
#include "getCommand.h"
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include "wait.h"
#include "systemCommands.h"


char * bgProcessnames[100005];
long long int bgProcessIDS[100005];
long long int bgProcessCount=0;

void handler()
{
    int status,index;
    pid_t pid = wait(NULL); // contains pid of the process which sent the signal

    int  found = -1;

    waitpid(pid, &status, 0);
    

       
    for(long long int i =0;i < bgProcessCount;i++)
    {
        //ids will be zero for allready tracked processes so emiting those.
        if(bgProcessIDS[i]!=0)
        {
            if(bgProcessIDS[i]==pid)
            {
                bgProcessIDS[i]=0;
                //asigignin 0 because we dont want to see them again.
                index=i;found =1;
            }
        }
            
     
    }
    if(found!=-1)
    {    
        if(WIFEXITED(status))
        {
            fprintf(stdout,"\n%s with pid %d exited normally with status %d\n",bgProcessnames[index],pid,WEXITSTATUS(status));
            return;
        }

       fprintf(stderr,"\n%s with pid %d doesnot exited normally\n",bgProcessnames[index],pid);

    }
    return;
}




int main()
{
    char newHome[100000]="";
    getcwd(newHome,sizeof(newHome));
    //printf("%s",newHome);
    
    
    
    
    
    system("clear");
    while(1)
    {
        signal(SIGCHLD,handler);
        unsigned long int n;
        char * textInput;

        displayPrompt(newHome);

        getline(&textInput, &n, stdin);

        if(strcmp(textInput,"\n")==0 || textInput==NULL) continue;

        char* noSpaceTextInput =removeLeadingSpaces(textInput,newHome);
        noSpaceTextInput[strlen(noSpaceTextInput)-1] = '\0'; //removing enter key
        breakAndProcess(noSpaceTextInput,newHome);
    }

}