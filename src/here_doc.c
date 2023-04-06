#include "../include/pipex.h"

void	failure(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	read_stdin(int fd, char *limiter)
{
	char	*line;

	line = get_next_line(0);
	while (line && ft_strncmp(line, limiter, ft_max(ft_strlen(line) - 1,
				ft_strlen(limiter))) != 0)
	{
		if (write(fd, line, ft_strlen(line)) < 0)
			failure("write failed");
		free(line);
		line = get_next_line(0);
	}
	if (line)
		free(line);
	close(fd);
}

int	open_here_doc(t_pipe *p)
{
	p->here_doc = malloc(sizeof(int) * 2);
	if (pipe(p->here_doc) < 0)
		failure("pipe");
	read_stdin(p->here_doc[1], p->av[2]);
	return (EXIT_SUCCESS);
}
