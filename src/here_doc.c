#include "../include/pipex.h"

int ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	read_stdin(char *limiter)
{
    char	*line;
	int		fd;

	line = get_next_line(0);
	fd = open("input", O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (fd < 0)
		failure("open failed");
	while (line && ft_strncmp(line, limiter, ft_max(ft_strlen(line) - 1, ft_strlen(limiter))) != 0)
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

