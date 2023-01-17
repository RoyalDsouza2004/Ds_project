#include <stdio.h>
#include <string.h>

int main() {
  char str1[20];
  gets(str1);
  char str2[20];

  // copying str1 to str2
  strcpy(str2, str1);

  puts(str2); // C programming

  return 0;
}