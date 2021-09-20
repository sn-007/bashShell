#include "standardHeaders.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>


void processPinfo(char *pid, char* newHome)
{
    
    char statPath[1000],exepath[1000];
    sprintf(statPath, "/proc/%s/stat", pid);
    FILE* fd = fopen(statPath,"r");
    if(!fd)
    {
        printf("%s: no such process\n",pid);
        return;
    }
    char statBuf[1111]; char * statWords[111]; char * token;
    fgets(statBuf, 1111, fd);
    
    token = strtok(statBuf, " ");
    statWords[0]= token;int j=1;

    while (token != NULL) {
      token = strtok(NULL, " ");
      if (token != NULL)
        statWords[j++] =token;
    }
    fclose(fd);

    printf("pid -- %s\n", pid);
    printf("Process Status -- %s\n", statWords[2]);
    printf("memory -- %s\n", statWords[22]);

    char exeBuf[1111];
    sprintf(exepath, "/proc/%s/exe", pid);
    j = readlink(exepath,exeBuf,1111);
    if(j==-1) return;
    exeBuf[j] = '\0';

    

    if(strlen(exeBuf) > strlen(newHome))
    {
        char modifiedExeBuf[1111];
        for(int x = 0; x < strlen(exeBuf)-strlen(newHome);x++)
        {
            modifiedExeBuf[x] = exeBuf[strlen(newHome)+x];
        }
        printf("Executable path -- ~%s\n", modifiedExeBuf);
        return;
    }
    else
    {
        printf("Executable path -- %s\n",exeBuf);
        return;
    }

    return;

}