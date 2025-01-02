#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

void handle_parse(char *input, char **args)
{
  int i = 0;
  args[i] = strtok(input, " \t\n");
  while (args[i] != NULL)
  {
    i++;
    args[i] = strtok(NULL, " \t\n");
  }
};

int main()
{

  char input[MAX_INPUT_SIZE];
  char *args[MAX_ARGS];

  pid_t pid;
  while (1)
  {
    printf("$rsh<3 ");
    fflush(stdout);

    if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
    {
      perror("fgets");
      break;
    }

    if (strncmp(input, "exit", 4) == 0)
    {
      printf("Thanks for using rsh\n");
      exit(0);
    };

    if (strncmp(input, "help", 4) == 0)
    {
      printf("rsh is a simple shell\n");
      printf("you can use commands like ls, cd, pwd, ls, echo, etc\n");
      continue;
    };

    handle_parse(input, args);

    if (args[0] == NULL)
    {
      continue;
    };

    pid = fork();
    if (pid < 0)
    {
      perror("fork");
      break;
    };
    if (pid == 0)
    {
      if (execvp(args[0], args) == -1)
      {
        perror("execvp");
        exit(1);
      };
    }
    else
    {
      wait(NULL);
    }
  };
}