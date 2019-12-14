#include <stdio.h>
#include <string.h>

int main() {
  char *str;
  int i;

  fgets(str, 1024, stdin);

  printf("This is string from java %s", str);

  return 0;
}