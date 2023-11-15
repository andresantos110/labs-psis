#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
  char result_str[128] = {0};
  char input[2] = {0};
  int mode = 0;

  printf("Use string.h? (y/n)\n");
  fgets(input,sizeof(input), stdin);

  if(strcmp(input,"n") == 0)
  {
    printf("Not using string.h.\n");
    mode = 1;
  }
  else printf("Using string.h.\n");

  if(mode == 0)
  {
    for(int i = 1; i < argc; i++)
    {
      strcat(result_str,argv[i]);
    }
    printf("%s", result_str);
  }

  if(mode == 1)
  {
    int currPos = 0;
    for(int i = 1; i < argc; i++)
    {
      int j = 0;
      while(argv[i][j] != '\0')
      {
        result_str[currPos] = argv[i][j];
        j++;
        currPos++;
      }
    }
    printf("%s", result_str);
  }
  return 0;
}
