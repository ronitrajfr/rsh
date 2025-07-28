#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

int main(int argc, char *argv[])
{
  // Flush after every printf
  setbuf(stdout, NULL);

  while (true)
  {

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("$%s ", cwd);
    // printf("$ ");
    char input[100];
    fgets(input, 100, stdin);
    input[strcspn(input, "\n")] = '\0';

    char *argv[20]; // 20 arguments
    int i = 0;

    char *command = strtok(input, " ");

    while (command != NULL && i < 10)
    {
      argv[i++] = command;
      command = strtok(NULL, " ");
    }
    argv[i] = NULL;

    // EXIT COMMAND

    if (strcmp(argv[0], "exit") == 0)
    {
      char *arg = argv[1];
      if (arg != NULL)
      {
        // parsing the string to int using atoi
        int value = atoi(arg);
        exit(value);
      }
    }

    // ECHO COMMAND
    else if (strcmp(argv[0], "echo") == 0)
    {
      for (int j = 1; argv[j] != NULL; j++)
        printf("%s ", argv[j]);
      printf("\n");
    }

    else if (strcmp(argv[0], "cd") == 0)
    {
      if (chdir(argv[1]) == 0)
      {
        printf("Changed directory to %s successfully.\n", argv[1]);
      }
      else
      {
        perror("chdir failed");
      }
    }

    // TYPE COMMAND

    else if (strcmp(argv[0], "type") == 0)
    {
      char *arg = argv[1];

      char *names[] = {"echo", "exit", "type"};
      int count = sizeof(names) / sizeof(names[0]);
      int i = 0;
      bool found = false;
      for (int i = 0; i < count; i++)
      {
        if (strcmp(names[i], arg) == 0)
        {
          printf("%s is a shell builtin\n", arg);
          found = true;
          break;
        }
      }

      if (!found)
      {
        char *path_env = getenv("PATH");
        char path_copy[1000];
        strcpy(path_copy, path_env);

        char *token = strtok(path_copy, ":");
        while (token != NULL)
        {
          char full_path[1024];
          snprintf(full_path, sizeof(full_path), "%s/%s", token, arg);

          // Check if file is executable
          if (access(full_path, X_OK) == 0)
          {
            printf("%s is %s\n", arg, full_path);
            found = true;
            break;
          }

          token = strtok(NULL, ":"); // Move to next directory
        }
      }

      if (!found)
      {
        printf("%s: not found\n", arg);
      }
    }

    else
    {
      pid_t pid = fork();

      if (pid == 0)
      {
        // child
        execvp(argv[0], argv);
        // if exec fails:
        perror("rsh ");
        exit(1);
      }
      else if (pid > 0)
      {
        // parent waits
        wait(NULL);
      }
      else
      {
        perror("fork failed");
      }
    }
  }
  return 0;
}
