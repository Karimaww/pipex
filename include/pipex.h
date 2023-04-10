#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct	s_pipe
{
	char	**av;
	char	**env;
	int		ac;
	int		n_cmd;
	int		*here_doc;
	int		*pipe_fds;
	pid_t	*pid;
	int		fd1;
	int		fd2;
}	t_pipe;

void	failure(const char *message);
char	*get_command_path(char *command, t_pipe *p);
void	close_pipes(int *pipe_fds, int num_pipes);
void	generate_pipes(int *pipe_fds, int num_pipes);
int		do_search_com(char *start, char *end, char *command, char *filepath);
char	*find_path(char *path, char *command);
void	read_stdin(int fd, char *limiter);
int		open_here_doc(t_pipe *p);
int		do_pipe(t_pipe *p);
void	do_execve(int i, int pid, t_pipe *p);
#endif