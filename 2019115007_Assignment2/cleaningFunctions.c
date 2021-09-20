#include "standardHeaders.h"
#include <stdio.h>
#include <string.h>

char * tildaCheck(char *str,char * newHome) {

  if(strlen(str) < 2)
  {
    return str;
  }

  if(str[0]=='~' && str[1]=='/')
  {
    char *ans =  malloc(strlen(str)+1000);
    memset(ans, '\0', strlen(str)+1002);

    for(int i =0; i < strlen(newHome);i++)
    {
      ans[i] = newHome[i];
    }
    for(int i =1; i < strlen(str);i++)
    {
      ans[strlen(newHome)+i-1] = str[i];
    }
    return ans;

  }
return str;
  
}


char * removeLeadingSpaces(char *str, char * newHome) {


  //printf("GIVENSTRING IS : %s ",str);
  char *ans =  malloc(strlen(str)+1000);
  memset(ans, '\0', strlen(str)+1002);
  long long int count = 0, j, k;

  while (str[count] == ' ') {
    count++;
  }

  for (j = count, k = 0; str[j] != '\0'; j++, k++) {
    ans[k] = str[j];
  }


  return tildaCheck(ans,newHome);
}

