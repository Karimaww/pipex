#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


/*
int main(int argc, char *argv[], char *env[])
{
  pid_t         pid;
  int           pipe_fd[2];

  if (argc < 2)
    return 1;

  if (pipe(pipe_fd) == -1)
    {
      perror("pipe");
      return 1;
    }

  if ((pid = fork()) == -1)
    {
      perror("fork");
      return 1;
    }
  else if (pid == 0)
    {
      close(pipe_fd[0]);
	  // la sortie standard (1), donc de la commande ls -la
	  // est remplacee par pipe_fd[1]
	  // qui sera recupere par le parent
      if (dup2(pipe_fd[1], 1) == -1)
      	perror("dup2");
		// on execute ls -la dans un processus a part (d'ou la necessite d'utiliser fork)	
      else if (execve(argv[1], argv + 1, env) == -1)
      	perror("execve");
      return 1;
    }
  else
    {
      char      buffer[1024];
      int       ret;
      int       status;

      close(pipe_fd[1]);

      while ((ret = read(pipe_fd[0], buffer, 1023)) != 0)
      {
        printf("%d\n", ret);
        buffer[ret] = 0;
        printf("%s\n", buffer);
      }
	  printf("argv + 1 : %s\n", (argv + 2)[0]);
    }

  return 0;
}
*/

int main(int argc, char *argv[], char *env[])
{
  pid_t         pid1, pid2;
  int           pipe_fd[2];

  if (argc < 2)
    return 1;

  if (pipe(pipe_fd) == -1)
    {
      perror("pipe");
      return 1;
    }

  if ((pid1 = fork()) == -1)
    {
      perror("fork");
      return 1;
    }
  if (pid1 == 0)
    {
      //close(pipe_fd[0]);
	  // la sortie standard (1), donc de la commande ls -la
	  // est remplacee par pipe_fd[1]
	  // qui sera recupere par le parent
      dup2(pipe_fd[1], 1);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
		// on execute ls -la dans un processus a part (d'ou la necessite d'utiliser fork)	
      if (execve(argv[1], argv + 1, env) == -1)
      	perror("execve");
      return 1;
    }
	if ((pid2 = fork()) == -1)
    {
      perror("fork");
      return 1;
    }
  if (pid2 == 0)
    {
      //close(pipe_fd[1]);
	  // la sortie standard (1), donc de la commande ls -la
	  // est remplacee par pipe_fd[1]
	  // qui sera recupere par le parent
      dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		// on execute ls -la dans un processus a part (d'ou la necessite d'utiliser fork)	
      if (execve(argv[2], argv + 2, env) == -1)
      	perror("execve");
      return 1;
    }
//waitpid(pid1, NULL, 0);
//waitpid(pid2, NULL, 0);
  
  return 0;
}