#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int		main(int argc, char **argv, char **env)
{
	argc = 0;
	char	*path;

	path = argv[1];


	if (path)
	{
		chdir(path);
	}
	char *pwd = getcwd(NULL, 0);
	printf("path == %s pwd == %s\n", path, pwd);
	return (0);
}