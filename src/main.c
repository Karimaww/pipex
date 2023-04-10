#include "../include/pipex.h"

void	do_execve(int i, int pid, t_pipe *p)
{
	char	**com;
	char	*path;

	com = ft_split(p->av[i + 2 + (p->here_doc != NULL)], ' ');
	path = get_command_path(com[0], p);
	if (!path)
		failure("path");
	if (execve(path, com, p->env) < 0)
		failure("execve");
	else if (pid < 0)
		failure("pid");
}

void	init_pipe(t_pipe *p, int ac, char *av[], char *env[])
{
	p->ac = ac;
	p->av = av;
	p->env = env;
	p->fd1 = -2;
	p->fd2 = -2;
}

int	main(int ac, char *av[], char *env[])
{
	t_pipe	p;

	init_pipe(&p, ac, av, env);
	if (ac <= 4)
		return (ft_putstr_fd("Error\n", 1), 1);
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0)
	{
		p.n_cmd = ac - 4;
		open_here_doc(&p);
	}
	else
	{
		p.here_doc = NULL;
		p.n_cmd = ac - 3;
	}
	if (do_pipe(&p) == EXIT_FAILURE)
		return (perror("pipe"), 1);
	if (p.here_doc)
	{
		close(p.here_doc[0]);
		free(p.here_doc);
	}
	return (free(p.pid), 0);
}
