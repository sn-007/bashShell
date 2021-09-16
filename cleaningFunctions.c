#include "standardHeaders.h"
#include <string.h>

char * removeLeadingSpaces(char *str) {

  char *ans = malloc(strlen(str));
  memset(ans, '\0', strlen(str)+2);
  long long int count = 0, j, k;

  while (str[count] == ' ') {
    count++;
  }

  for (j = count, k = 0; str[j] != '\0'; j++, k++) {
    ans[k] = str[j];
  }

  return ans;
}
