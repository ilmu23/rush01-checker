// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<err.c>>

#include <string.h>
#include "checker.h"

_Noreturn void	err_exit(const u8 err, const char *context) {
	ft_printf("\x1b[?1049l\x1b[?25h");
	switch (err) {
		case E_INVALID_ARGC:
			ft_dprintf(2, "checker: invalid argument count");
			break ;
		case E_NO_TERMINFO_FOUND:
			ft_dprintf(2, "checker: no terminal description found");
			break ;
		case E_MISSING_TERMINFO_CAP:
			ft_dprintf(2, "checker: terminal description missing required capability");
			break ;
		case E_STDOUT_WRITE:
			ft_dprintf(2, "checker: unable to write to stdout: %s", strerror(errno));
			break ;
		case E_ALLOC_FAIL:
			ft_dprintf(2, "checker: unable to allocate memory: %s", strerror(errno));
			break ;
		case E_ARG_OUT_OF_RANGE:
			ft_dprintf(2, "checker: argument out of range");
			break ;
		case E_TOO_MANY_NUMBERS:
			ft_dprintf(2, "checker: too many numbers on line ");
			break ;
		case E_NOT_ENOUGH_NUMBERS:
			ft_dprintf(2, "checker: not enough numbers on line ");
			break ;
		case E_TOO_MANY_LINES:
			ft_dprintf(2, "checker: too many lines");
			break ;
		case E_NOT_ENOUGH_LINES:
			ft_dprintf(2, "checker: not enough lines");
			break ;
		case E_STDIN_READ:
			ft_dprintf(2, "checker: unable to read from stdin: %s", strerror(errno));
			break ;
		case E_PIPE_FAIL:
			ft_dprintf(2, "checker: failed to create pipe: %s", strerror(errno));
			break ;
		case E_FORK_FAIL:
			ft_dprintf(2, "checker: failed to create child process: %s", strerror(errno));
			break ;
		case E_EXEC_FAIL:
			ft_dprintf(2, "checker: failed to execute command");
			break ;
		case E_DUP_FAIL:
			ft_dprintf(2, "checker: failed to duplicate pipe");
			break ;
		case E_TIMESPEC_FAIL:
			ft_dprintf(2, "checker: failed to get current time: %s", strerror(errno));
			break ;
		default:
			ft_dprintf(2, "checker: unspecified error: ");
	}
	if (context)
		ft_putstr_fd(context, 2);
	ft_putchar_fd('\n', 2);
	exit(ft_return((err != 0) ? err : -1));
}
