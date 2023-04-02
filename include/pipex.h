#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../libft/libft.h"

typedef struct	s_pipe
{
	char	**av;
	char	**env;
    int		ac;
    int 	fd1;
	int		fd2;
}	t_pipe;

void	failure(const char *message);
void	close_pipes(int *pipe_fds, int num_pipes);
void	generate_pipes(int *pipe_fds, int num_pipes);
int		do_search_com(char *start, char *end, char *command, char *filepath);
char	*find_path(char *path, char *command);
int		read_stdin(char *limiter, char *filename);
void	init_pipes(int *pipe_fds, int size);
char	*get_rand_name(void);
#endif