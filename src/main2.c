#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int	ft_countword(char const *s, char c)
{
	int	i;
	int	cpt;

	cpt = 0;
	i = 1;
	if (s[0] && s[0] != c)
		cpt++;
	while (s[i - 1] && s[i])
	{
		if (s[i - 1] == c && s[i] != c)
			cpt++;
		i++;
	}
	return (cpt);
}

char	*ft_buildw(char const *str, char c)
{
	int		len;
	int		i;
	char	*word;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_check(char **res, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < len)
	{
		if (!res[i++])
		{
			while (j < i)
				free(res[j++]);
			free(res);
			return (NULL);
		}
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		countw;
	int		i;
	int		pos;

	if (!s)
		return (NULL);
	countw = ft_countword(s, c);
	res = (char **)malloc(sizeof(char *) * (countw + 1));
	i = 0;
	if (!res)
		return (NULL);
	if (s[0] && s[0] != c)
		res[i++] = ft_buildw(s, c);
	pos = 1;
	while (s[pos - 1] && s[pos] && i < countw)
	{
		if (s[pos - 1] == c && s[pos] != c)
			res[i++] = ft_buildw(s + pos, c);
		pos++;
	}
	res[i] = 0;
	return (ft_check(res, countw));
}

int main(int argc, char *argv[], char *env[])
{
  pid_t         pid;
  int           pipe_fd[2];

  if (argc < 2)
    return 1;

  if (pipe(pipe_fd) == -1)
    {
      perror("pipe");
      return 1;
    }

  if ((pid = fork()) == -1)
    {
      perror("fork");
      return 1;
    }
  else if (pid == 0)
    {
      close(pipe_fd[0]);
      dup2(pipe_fd[1], 1);
		char **com = ft_split(argv[1], ' ');
      execve(com[0], com + 1, env);
    }
  else
    {
      char      buffer[1024];
      int       ret;
      int       status;

      close(pipe_fd[1]);

      while ((ret = read(pipe_fd[0], buffer, 1023)) != 0)
      {
        printf("%d\n", ret);
        buffer[ret] = 0;
        printf("%s\n", buffer);
      }
    }

  return 0;
}