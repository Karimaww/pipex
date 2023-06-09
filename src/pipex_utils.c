#include "../include/pipex.h"

char	*get_command_path(char *command, t_pipe *p)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (p->env[i] != NULL)
	{
		if (strncmp(p->env[i], "PATH=", 5) == 0)
		{
			path = p->env[i] + 5;
			break ;
		}
		i++;
	}
	return (find_path(path, command));
}

void	close_pipes(int *pipe_fds, int num_pipes)
{
	int	k;

	k = 0;
	while (k < num_pipes)
	{
		close(pipe_fds[k]);
		k++;
	}
}

void	generate_pipes(int *pipe_fds, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipe_fds + (i * 2)) < 0)
			failure("pipe");
		i++;
	}
}

int	do_search_com(char *start, char *end, char *command, char *filepath)
{
	int	len;

	len = end - start;
	ft_strncpy(filepath, start, len);
	filepath[len] = '/';
	ft_strncpy(filepath + len + 1, command, ft_strlen(command));
	if (access(filepath, X_OK) != -1)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

char	*find_path(char *path, char *command)
{
	char	*start;
	char	*end;
	char	*filepath;

	start = path;
	while (*start)
	{
		end = start;
		while (*end && *end != ':')
			end++;
		filepath = (char *)malloc(sizeof(char)
				* ((end - start) + 2 + ft_strlen(command)));
		if (!filepath)
			return (NULL);
		if (do_search_com(start, end, command, filepath) == EXIT_SUCCESS)
			return (filepath);
		free(filepath);
		if (*end == ':')
			start = end + 1;
		else
			break ;
	}
	return (NULL);
}
