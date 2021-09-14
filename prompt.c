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

char* directoryManipulation(char * newHome)
{
    char dirBuf[100000];
    char *currentWorkingDirectory = getcwd(dirBuf,100000);
    //printf("\ncwd is %s\n",currentWorkingDirectory);

    int cwdLength = strlen(currentWorkingDirectory);
    
        
    if(strlen(newHome) > cwdLength)
    {
        
        char *ans = malloc((3+cwdLength)*sizeof(char));
        ans[0]=':';ans[1]='~';
        for(int i=0;i<cwdLength;i++)
        {
            ans[2+i]=currentWorkingDirectory[i];
        }
        ans[3+cwdLength-1] = '>';
        return ans;
    }

    else if (strlen(newHome) < cwdLength)
    {
     
        char *ans = malloc((cwdLength-strlen(newHome)+1+2)*sizeof(char));
        ans[0]=':';ans[1]='~';
        for(int i=0;i<(cwdLength-strlen(newHome));i++)
        {
            ans[2+i]=currentWorkingDirectory[strlen(newHome)+i];
        }
        ans[(cwdLength-strlen(newHome)+1+2-1)] = '>';
        return ans;
    }
           
    return ":~>" ;
 
}

void displayPrompt(char * newHome)
{
    char hostBuf[100000];
    printf("<%s@", getenv("USER"));
    gethostname(hostBuf, 100000);
    printf("%s", hostBuf);
    printf("%s", directoryManipulation(newHome));
    
    

}

