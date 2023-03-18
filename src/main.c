#include "../include/pipex.h"

int	open_files(char	*file1, char *file)
{

}

int	main(int ac, char **av)
{
	int	fd1;
	int fd2;
	char *limiter;

	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0)
		{
			//eventually change this
			limiter = ft_strdup(av[2]);
			fd1 = 0;
			fd2 = open(av[ac - 1], O_WRONLY);
		}
		else
		{
			(void)limiter;
			fd1 = open(av[1], O_RDONLY);
			fd2 = open(av[ac - 1], O_WRONLY);
		}
		if (!fd1 || !fd2)
			return (write(2, "Error\n", 6), NULL);
		// problem might arrise in bonus case
		close(fd2);
		close(fd1);
	}

}