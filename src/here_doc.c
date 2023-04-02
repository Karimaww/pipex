#include "../include/pipex.h"

void	init_pipes(int *pipe_fds, int size)
{
	pipe_fds = (int *)malloc(sizeof(int) * 2 * size);
	if (!pipe_fds)
		failure("init pipes");
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

char	*get_rand_name(void)
{
	int		fd;
	int		cpt;
	char	*filename;

	fd = 0;
	cpt = 0;
	while (fd == -1)
	{
		filename = ft_itoa(cpt);
		fd = open(filename, O_CREAT | O_EXCL | O_RDWR, 0644);
		if (fd == -1)
			free(filename);
		++cpt;
	}
	return (filename);
}

int	read_stdin(char *limiter, char *filename)
{
	char	*line;
	int		fd;

	line = get_next_line(0);
	fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (fd < 0)
		failure("open failed");
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
	return (fd);
}
