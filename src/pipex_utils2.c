#include "../include/pipex.h"

void	do_dup(int i, int *pipe_fds, t_pipe *p)
{
	if (i + 1 == p->n_cmd)
	{
		if (dup2(p->fd2, 1) < 0)
			failure("dup2");
	}
	else if (i + 1 != p->n_cmd)
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

void	files_open_option(t_pipe *p, int i)
{
	if (i == 0)
	{
		if (!p->here_doc)
			p->fd1 = open(p->av[1], O_RDONLY, 0644);
		else
			p->fd1 = p->here_doc[0];
		if (p->fd1 == -1)
			failure(p->av[1]);
	}
	if (i == p->n_cmd - 1)
	{
		if (!p->here_doc)
			p->fd2 = open(p->av[p->ac - 1],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			p->fd2 = open(p->av[p->ac - 1],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (p->fd2 == -1)
			failure(p->av[p->ac - 1]);
	}
}

void	do_smth(int i, int *pipe_fds, t_pipe *p, pid_t pid)
{
	files_open_option(p, i);
	do_dup(i, pipe_fds, p);
	close_pipes(pipe_fds, 2 * (p->n_cmd - 1));
	do_execve(i, pid, p);
}

void	close_pipe_cmd(t_pipe *p, int i)
{
	if (i + 1 == p->n_cmd)
	{
		if (p->fd2 >= 0)
			close(p->fd2);
	}
	else
		close(p->pipe_fds[i * 2 + 1]);
	if (i != 0)
		close(p->pipe_fds[i * 2 - 2]);
	else
	{
		if (p->fd1 >= 0)
			close(p->fd1);
	}
}

int	do_pipe(t_pipe *p)
{
	int		i;

	i = 0;
	p->pid = (pid_t *)malloc(sizeof(pid_t) * p->n_cmd);
	p->pipe_fds = (int *)malloc(sizeof(int) * 2 * (p->n_cmd - 1));
	if (!p->pipe_fds || !p->pid)
		return (EXIT_FAILURE);
	generate_pipes(p->pipe_fds, p->n_cmd - 1);
	while (i < p->n_cmd)
	{
		p->pid[i] = fork();
		if (p->pid[i] == -1)
			failure("fork");
		if (p->pid[i] == 0)
			do_smth(i, p->pipe_fds, p, p->pid[i]);
		close_pipe_cmd(p, i);
		++i;
	}
	i = 0;
	while (i < p->n_cmd)
		waitpid(p->pid[i++], NULL, 0);
	return (free(p->pipe_fds), EXIT_SUCCESS);
}
