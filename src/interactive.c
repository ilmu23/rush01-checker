// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<interactive.c>>

#include "checker.h"

#include <time.h>
#include <signal.h>
#include <termios.h>
#include <sys/wait.h>

#define free(x)		(free((void *)x))
#define pclose(x)	(close(x[0]), close(x[1]))

typedef struct termios	tios_t;
typedef struct timespec	tspec_t;

frame_t	frame;
i32		pfd[2];

extern char	**environ;

extern int kill (__pid_t __pid, int __sig) __THROW;

_Noreturn static inline void	_exec_rush(char *args);
_Noreturn static inline void	_exec_checker(char *args);
static inline void				_gen_args(const u64 size);
static inline void				_wait_for_key(void);
static inline void				_show_args(void);
static inline void				_set_args(void);
static inline void				_run(void);
static inline u8				_count_args(const char **args);
static inline u8				_rand_range(const u8 min, const u8 max);

u8	interactive(void) {
	const char	*line;
	tspec_t		time;

	frame = (frame_t) {
			.size = 4,
			.top = ft_memcpy(alloc(9 * sizeof(*frame.top)), (u8 [4]){4, 3, 2, 1}, 4 * sizeof(*frame.top)),
			.bot = ft_memcpy(alloc(9 * sizeof(*frame.bot)), (u8 [4]){1, 2, 2, 2}, 4 * sizeof(*frame.bot)),
			.lft = ft_memcpy(alloc(9 * sizeof(*frame.lft)), (u8 [4]){4, 3, 2, 1}, 4 * sizeof(*frame.lft)),
			.rgt = ft_memcpy(alloc(9 * sizeof(*frame.rgt)), (u8 [4]){1, 2, 2, 2}, 4 * sizeof(*frame.rgt)),
	};
	if (!frame.top || !frame.bot || !frame.lft || !frame.rgt)
		err_exit(E_ALLOC_FAIL, NULL);
	_show_args();
	if (timespec_get(&time, TIME_UTC) == -1)
		err_exit(E_TIMESPEC_FAIL, NULL);
	srand(time.tv_nsec);
	for (line = ft_register(ft_readline("> ", FT_RL_HIST_ON), 0); line; line = ft_register(ft_readline("> ", FT_RL_HIST_ON), 0)) {
		if (ft_strequals(line, "set"))
			_set_args();
		else if (ft_strequals(line, "show"))
			_show_args();
		else if (ft_strequals(line, "run") || !*line)
			_run();
		else if (ft_strequals(line, "exit"))
			break ;
		else
			ft_printf("unrecognized command: %s\n", line);
	}
	return 0;
}

_Noreturn static inline void	_exec_rush(char *args) {
	char	*av[3] = {"rush01", args, NULL};

	if (dup2(pfd[1], 1) == -1)
		exit(E_DUP_FAIL);
	pclose(pfd);
	execve(av[0], av, environ);
	exit(E_EXEC_FAIL);
}

_Noreturn static inline void	_exec_checker(char *args) {
	char	*av[3] = {"checker", args, NULL};

	if (dup2(pfd[0], 0) == -1)
		exit(E_DUP_FAIL);
	pclose(pfd);
	execve(av[0], av, environ);
	exit(E_EXEC_FAIL);
}

static inline void	_gen_args(const u64 size) {
	u8	used_row[9];
	u8	used_col[9];
	u8	grid[9][9];
	u8	visible;
	u8	highest;
	u8	row;
	u8	col;
	u8	n;
	u8	i;

	if (!inrange(size, 4, 9)) {
		ft_printf("args: argument out of range: %llu\n", size);
		return ;
	}
	frame.size = (u8)size;
	ft_memset(grid, 0, sizeof(grid));
gen_grid:
	for (row = 0; row < frame.size; row++) {
		for (col = 0, ft_memset(used_row, 0, sizeof(used_row)); col < frame.size; col++) {
			n = _rand_range(1, frame.size);
			for (i = 0, ft_memset(used_col, 0, sizeof(used_col)); i < row; i++)
				used_col[grid[i][col] - 1] = 1;
			for (i = 0; used_row[n - 1] || used_col[n - 1]; i++) {
				if (i > frame.size * 2)
					goto gen_grid;
				n = (n < frame.size) ? n + 1 : 1;
			}
			grid[row][col] = n;
			used_row[n - 1] = 1;
		}
	}
	for (row = 0; row < frame.size; row++) {
		for (col = visible = highest = 0; col < frame.size; col++) {
			if (grid[row][col] > highest) {
				highest = grid[row][col];
				visible++;
			}
		}
		frame.lft[row] = visible;
		for (visible = highest = 0; col && highest != frame.size;) {
			if (grid[row][--col] > highest) {
				highest = grid[row][col];
				visible++;
			}
		}
		frame.rgt[row] = visible;
	}
	for (col = 0; col < frame.size; col++) {
		for (row = visible = highest = 0; row < frame.size; row++) {
			if (grid[row][col] > highest) {
				highest = grid[row][col];
				visible++;
			}
		}
		frame.top[col] = visible;
		for (visible = highest = 0; row && highest != frame.size;) {
			if (grid[--row][col] > highest) {
				highest = grid[row][col];
				visible++;
			}
		}
		frame.bot[col] = visible;
	}
}

static inline void	_wait_for_key(void) {
	static tios_t	old;
	static tios_t	new;
	static u8		init;
	u64				kbuf;

	if (!init) {
		tcgetattr(0, &old);
		new = old;
		new.c_iflag &= ~(ICRNL | IXON);
		new.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
		init = 1;
	}
	tcsetattr(0, TCSANOW, &new);
	read(0, &kbuf, 8);
	tcsetattr(0, TCSANOW, &old);
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
	if (ft_getblksize(args) == 2 * sizeof(*args)) {
		_gen_args(ft_atou64(args[0]));
		ft_popblks(2, args[0], args);
		goto ret;
	}
	argc = _count_args(args);
	if (argc == 0)
		goto ret;
	frame.size = argc;
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
	char	buf[128];
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
	ft_printf("\x1b[?1049h\x1b[?25l");
	if (pipe(pfd) == -1)
		err_exit(E_PIPE_FAIL, NULL);
	pids[0] = fork();
	if (pids[0] == 0)
		_exec_rush(buf);
	if (pids[0] == -1) {
		pclose(pfd);
		err_exit(E_FORK_FAIL, NULL);
	}
	pids[1] = fork();
	if (pids[1] == 0)
		_exec_checker(buf);
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
	if (estat == 0)
		_wait_for_key();
	ft_printf("\x1b[?1049l\x1b[?25h");
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

static inline u8	_rand_range(const u8 min, const u8 max) {
	return rand() % (max - min + 1) + min;
}
