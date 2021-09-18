#include "standardHeaders.h"
#include <stdio.h>
#include <string.h>

char * removeLeadingSpaces(char *str) {


  //printf("GIVENSTRING IS : %s ",str);
  char *ans =  malloc(strlen(str)*sizeof(char));
  memset(ans, '\0', strlen(str)+2);
  long long int count = 0, j, k;

  while (str[count] == ' ') {
    count++;
  }

  for (j = count, k = 0; str[j] != '\0'; j++, k++) {
    ans[k] = str[j];
  }
  //printf("ans is : %s\n",ans);

  return ans;
}
