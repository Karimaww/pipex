## PIPEX

Because we are better than everybody.

In the bonus there is this part:

```sh
cmd << LIMITER | cmd1 >> file
```

Basically, it will add "LIMITER" to the end of the "file".
For example for 
```sh
echo a << END | echo b >> output
```
You will get
```sh
# do Ctrl+D, then
cat b
>> b
```

# Basic knowledge

pipe -> here is a small tutorial to use pipe
```c
int	fd[2];
if (pipe(fd) == -1)
	return 1;
// then you need to write in one process and then read in another
// i'll do that example later
```
FIFO -> file type to which you can read or write from any process

# Allowed commands
```c
int access(const char *pathname, int mode);
```
checks whether the calling process can access the file pathname. If pathname is a symbolic link, it is dereferenced.

```c
#include <unistd.h>
int execve(const char *fichier, char *const argv[], 
char *const envp[]);  
```
- plusieurs fork pr chaque execlp