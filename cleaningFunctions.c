#include "standardHeaders.h"

char * removeLeadingSpaces(char *str) {
  char *ans = malloc(strlen(str));
  long long int count = 0, j, k;

  while (str[count] == ' ') {
    count++;
  }

  for (j = count, k = 0; str[j] != '\0'; j++, k++) {
    ans[k] = str[j];
  }

  return ans;
}
