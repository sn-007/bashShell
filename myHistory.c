#include "myHistory.h"
#include "standardHeaders.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

char *file = "./history.txt";

void printHistory(int n)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char history[100][1000];
    int hcount = 0;

    fp = fopen(file, "r");

    while ((read = getline(&line, &len, fp)) != -1) {

        for (int i = 0; i < strlen(line); i++) {
        history[hcount][i] = line[i];
        }
        hcount++;
    }

    fclose(fp);
    if (line)
        free(line);

    for(int i=hcount-n;i<hcount;i++)
    {
        printf("%s",history[i]);
    }
}

void uploadHistory(char *text) {

  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char history[100][1000];
  int hcount = 0;

  fp = fopen(file, "r");

  while ((read = getline(&line, &len, fp)) != -1) {

    for (int i = 0; i < strlen(line); i++) {
      history[hcount][i] = line[i];
    }
    hcount++;
  }

  fclose(fp);
  if (line)
    free(line);

  char *textCopy = malloc(strlen(text) + 1);
  memset(textCopy, '\0', strlen(text) + 2);

  for (int i = 0; i < strlen(text); i++)
    textCopy[i] = text[i];

  if (hcount <= 19) 
  {
    for (int i = 0; i < strlen(textCopy); i++) 
        history[hcount][i] = textCopy[i];
    
    hcount++;

    char buf[100000];
    int count=0;

    for(int i =0;i<hcount;i++)
        for(int j=0;j<strlen(history[i]);j++)
            buf[count++]=history[i][j];
        

    int fd2 = open(file, O_RDWR | O_TRUNC, 0777);
    write(fd2,buf,strlen(buf));
    close(fd2);

  } 
  
  else 
  {
    char newhistory[100][1000];
    
    for (int i = 1; i < 20; i++) 
        for (int j = 0; j < strlen(history[i]); j++) 
            newhistory[i - 1][j] = history[i][j];
      
    

    for (int j = 0; j < strlen(textCopy); j++) 
        newhistory[19][j] = textCopy[j];

    char buf[100000];
    int count=0;


    for(int i =0;i<20;i++)
        for(int j=0;j<strlen(newhistory[i]);j++)
            buf[count++]=newhistory[i][j];

    int fd2 = open(file, O_RDWR | O_TRUNC, 0777);
    write(fd2,buf,strlen(buf));
    close(fd2); 

  }

}
