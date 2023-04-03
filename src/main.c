#include "../include/pipex.h"

void	do_execve(int i, int pid, t_pipe *p)
{
	char	**com;
	char	*path;

	com = ft_split(p->av[i], ' ');
	path = get_command_path(com[0], p);
	if (!path)
		failure("path");
	if (execve(path, com, p->env) < 0)
		failure("execve");
	else if (pid < 0)
		failure("pid");
}

void	do_dup(int i, int *pipe_fds, t_pipe *p)
{
	if (i + 1 == p->ac)
	{
		if (dup2(p->fd2, 1) < 0)
			failure("dup2");
	}
	else if (i + 1 != p->ac)
	{
		if (dup2(pipe_fds[i * 2 + 1], 1) < 0)
			failure("dup2");
	}
	if (i != 0)
	{
		if (dup2(pipe_fds[i * 2 - 2], 0) < 0)
			failure("dup2");
	}
	else if (i == 0)
	{
		if (dup2(p->fd1, 0) < 0)
			failure("dup2");
	}
}

void	do_smth(int i, int *pipe_fds, t_pipe *p, pid_t pid)
{
	do_dup(i, pipe_fds, p);
	close_pipes(pipe_fds, 2 * (p->ac - 1));
	do_execve(i, pid, p);
}

int	do_pipe(t_pipe *p)
{
	pid_t	pid;
	int		*pipe_fds;
	int		i;

	i = 0;
	pipe_fds = (int *)malloc(sizeof(int) * 2 * (p->ac - 1));
	if (!pipe_fds)
		return (EXIT_FAILURE);
	generate_pipes(pipe_fds, p->ac - 1);
	while (i < p->ac)
	{
		pid = fork();
		if (pid == -1)
			failure("fork");
		if (pid == 0)
			do_smth(i, pipe_fds, p, pid);
		++i;
	}
	while (i++ < p->ac - 1)
		if (wait(&pid) == -1)
			failure("wait");
	return (close_pipes(pipe_fds, p->ac - 1), free(pipe_fds), EXIT_SUCCESS);
}

int	main(int ac, char *av[], char *env[])
{
	t_pipe	p;
	char	*filename;

	p.env = env;
	filename = get_rand_name();
	if (ac <= 4)
		return (unlink(filename), free(filename), ft_putstr_fd("Error\n", 1), 1);
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0)
	{
		p.ac = ac - 4;
		p.av = av + 3;
		read_stdin(av[2], filename);
		p.fd1 = open(filename, O_RDONLY | O_CREAT, 0644);
	}
	else
	{
		p.ac = ac - 3;
		p.av = av + 2;
		p.fd1 = open(av[1], O_RDONLY | O_CREAT, 0644);
	}
	p.fd2 = open(av[ac - 1], O_WRONLY | O_CREAT, 0644);
	if (do_pipe(&p) == EXIT_FAILURE || !p.fd1 || !p.fd2)
		return (unlink(filename), free(filename), ft_putstr_fd("Error\n", 1), 1);
	return (close(p.fd1), close(p.fd2), unlink(filename), free(filename), 0);
}
