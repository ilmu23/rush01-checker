// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<interactive.c>>

#include "checker.h"

#include <signal.h>
#include <sys/wait.h>

#define free(x)		(free((void *)x))
#define pclose(x)	(close(x[0]), close(x[1]))

frame_t	frame;

extern char	**environ;

extern int kill (__pid_t __pid, int __sig) __THROW;

_Noreturn static inline void	_exec_rush(const i32 outfd, char *args);
_Noreturn static inline void	_exec_checker(const i32 infd, char *args);
static inline void				_show_args(void);
static inline void				_set_args(void);
static inline void				_run(void);
static inline u8				_count_args(const char **args);

u8	interactive(void) {
	const char	*line;

	frame = (frame_t) {
			.size = 4,
			.top = ft_memcpy(alloc(9 * sizeof(*frame.top)), (u8 [4]){4, 3, 2, 1}, 4 * sizeof(*frame.top)),
			.bot = ft_memcpy(alloc(9 * sizeof(*frame.bot)), (u8 [4]){1, 2, 2, 2}, 4 * sizeof(*frame.bot)),
			.rgt = ft_memcpy(alloc(9 * sizeof(*frame.rgt)), (u8 [4]){4, 3, 2, 1}, 4 * sizeof(*frame.rgt)),
			.lft = ft_memcpy(alloc(9 * sizeof(*frame.lft)), (u8 [4]){1, 2, 2, 2}, 4 * sizeof(*frame.lft)),
	};
	if (!frame.top || !frame.bot || !frame.lft || !frame.rgt)
		err_exit(E_ALLOC_FAIL, NULL);
	_show_args();
	for (line = ft_register(ft_readline("> ", FT_RL_HIST_ON), 0); line; free(line), line = ft_register(ft_readline("> ", FT_RL_HIST_ON), 0)) {
		if (ft_strequals(line, "set"))
			_set_args();
		else if (ft_strequals(line, "show"))
			_show_args();
		else if (ft_strequals(line, "run"))
			_run();
		else if (ft_strequals(line, "exit"))
			break ;
		else
			ft_printf("unrecognized command: %s\n", line);
	}
	return 0;
}

_Noreturn static inline void	_exec_rush(const i32 outfd, char *args) {
	char	*av[3] = {"rush01", args, NULL};

	if (dup2(1, outfd) == -1)
		exit(E_DUP_FAIL);
	execve(av[0], av, environ);
	exit(E_EXEC_FAIL);
}

_Noreturn static inline void	_exec_checker(const i32 infd, char *args) {
	char	*av[3] = {"checker", args, NULL};

	if (dup2(0, infd) == -1)
		exit(E_DUP_FAIL);
	execve(av[0], av, environ);
	exit(E_EXEC_FAIL);
}

static inline void	_show_args(void) {
	u8	i;

	ft_printf("args: ");
	for (i = 0; i < frame.size; i++)
		ft_printf("%hhu ", frame.top[i]);
	for (i = 0; i < frame.size; i++)
		ft_printf("%hhu ", frame.bot[i]);
	for (i = 0; i < frame.size; i++)
		ft_printf("%hhu ", frame.lft[i]);
	for (i = 0; i < frame.size; i++)
		ft_printf("%hhu%c", frame.rgt[i], (i + 1 != frame.size) ? ' ' : '\n');
}

void	_set_args(void) {
	const char	**args;
	const char	*line;
	u64			argval;
	u8			*tmp;
	u8			argc;
	u8			i;

	line = ft_readline("Enter args > ", FT_RL_HIST_ON);
	if (!line)
		return ;
	args = ft_pusharr(ft_split(line, ' '));
	if (!args) {
		free(line);
		err_exit(E_ALLOC_FAIL, NULL);
	}
	argc = _count_args(args);
	if (argc == 0)
		goto ret;
	for (i = 0, tmp = frame.top; args[i];) {
		argval = ft_atou64(args[i]);
		if (!inrange(argval, 1, frame.size)) {
			ft_printf("args: argument out of range: %llu\n", argval);
			goto ret;
		}
		tmp[i % frame.size] = (u8)argval;
		if (++i % frame.size == 0) {
			switch (i / frame.size) {
				case 1:
					tmp = frame.bot;
					break ;
				case 2:
					tmp = frame.lft;
					break ;
				case 3:
					tmp = frame.rgt;
			}
		}
		ft_popblk(args[i - 1]);
	}
	ft_popblk(args);
ret:
	free(line);
}

void	_run(void) {
	pid_t	pids[2];
	char	buf[256];
	i32		pfd[2];
	i32		estat;
	u8		i;
	u8		j;

	for (i = j = 0; i < frame.size; i++, j++) {
		buf[j] = frame.top[i] + '0';
		buf[++j] = ' ';
	}	
	for (i = 0; i < frame.size; i++, j++) {
		buf[j] = frame.bot[i] + '0';
		buf[++j] = ' ';
	}
	for (i = 0; i < frame.size; i++, j++) {
		buf[j] = frame.lft[i] + '0';
		buf[++j] = ' ';
	}
	for (i = 0; i < frame.size; i++, j++) {
		buf[j] = frame.rgt[i] + '0';
		buf[++j] = (i + 1 != frame.size) ? ' ' : '\0';
	}
	ft_printf("\x1b[?1049h");
	if (pipe(pfd) == -1)
		err_exit(E_PIPE_FAIL, NULL);
	pids[0] = fork();
	if (pids[0] == 0)
		_exec_rush(pfd[1], buf);
	if (pids[0] == -1) {
		pclose(pfd);
		err_exit(E_FORK_FAIL, NULL);
	}
	pids[1] = fork();
	if (pids[1] == 0)
		_exec_checker(pfd[0], buf);
	if (pids[1] == -1) {
		pclose(pfd);
		kill(pids[0], SIGKILL);
		err_exit(E_FORK_FAIL, NULL);
	}
	pclose(pfd);
	waitpid(pids[0], &estat, 0);
	waitpid(pids[1], &estat, 0);
	estat = WEXITSTATUS(estat);
	if (estat == E_ALLOC_FAIL || estat == E_PIPE_FAIL || estat == E_FORK_FAIL ||
		estat == E_EXEC_FAIL || estat == E_DUP_FAIL)
		err_exit(estat, NULL);
	ft_printf("\x1b[?1049l");
}

static inline u8	_count_args(const char **args) {
	u8	i;

	for (i = 0; args[i]; i++)
		;
	if (i % 4) {
		ft_printf("args: argument count not divisible by 4");
		return 0;
	}
	i /= 4;
	if (!inrange(i, 4, 9)) {
		if (i < 4) 
			ft_printf("args: not enough args\n");
		else
			ft_printf("args: too many args\n");
		return 0;
	}
	return i;
}