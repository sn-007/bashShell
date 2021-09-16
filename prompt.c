#include "standardHeaders.h"
#include "prompt.h"
#include <stdio.h>
#include <string.h>

 


// void getHome()
// {
//     char homeBuf[1024];
//     localHome = getcwd(homeBuf,1024);
//     printf("\n in gethome localhome is %s",localHome);
// }

void directoryManipulation(char * newHome, char * ans)
{
    char dirBuf[100000];
    char *currentWorkingDirectory = getcwd(dirBuf,100000);
    int cwdLength = strlen(currentWorkingDirectory);

    int f=1; //flag for checking whether cwd is part of newhome
    for(int i =0;i<strlen(newHome);i++)
    {
        if(newHome[i]!=currentWorkingDirectory[i]){f=0;break;}
    }
   
    if(f==0)
    {
        
        for(int i=0; i < strlen(currentWorkingDirectory);i++ )
        {
            ans[i] = currentWorkingDirectory[i];
        }
        return ; 
        
        
    }
    
    else if(f==1)
    {
        for(int i=strlen(newHome); i < strlen(currentWorkingDirectory);i++ )
        {
            ans[i-strlen(newHome)+1] = currentWorkingDirectory[i];
        }
        return; 

    }
}

void displayPrompt(char * newHome)
{
    char ans[1000];
    memset(ans, '\0', 1000);
    ans[0]='~';

    directoryManipulation(newHome,ans);

    char hostBuf[100000];
    printf("<%s@", getenv("USER"));
    gethostname(hostBuf, 100000);
    printf("%s:", hostBuf);
    printf("%s>", ans);


}

