#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

extern char **environ;

int	main(int argc, char *argv[])
{
	char	**new_argv;
	char	command[] = "ls";
	int		idx;

	new_argv = (char **)malloc(sizeof(char *) * (argc + 1));

	new_argv[0] = command; // 명령어를 ls로 변경

	// command line으로 넘어온 parameter를 그대로 사용
	for (idx = 1; idx < argc; idx++)
		new_argv[idx] = argv[idx];

	// argc를 execve 파라미터에 전달할 수 없기 때문에 NULL이 파라미터의 끝을 의미한다.
	new_argv[argc] = NULL;
	if (execve("/bin/ls", new_argv, environ) == -1)
	{
		fprintf(stderr, "프로그램 실행 error: %s\n", strerror(errno));
		return 1;
	}

	// ls 명령어 binary로 실행로직이 교체되었으므로 이후의 로직은 절대 실행되지 않는다.
	printf("이것은 이제 ls 명령어러 이 라인은 출력되지 않는다. \n");
	return 0;
}