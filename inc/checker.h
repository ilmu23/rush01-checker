// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<checker.h>>

#ifndef CHECKER_H
# define CHECKER_H

# include "defs.h"

# define _FT_RL_HFILE "~/.rchk_hist"

# include "rl42.h"
# include "ti42.h"
# include "libft.h"
# include "ft_stdio/ft_printf.h"

# include <errno.h>
# include <fcntl.h>

// args.c

const frame_t	*args_parse(const char *argstr);

// check.c

void	check(const frame_t *frame);

// interactive.c

u8	interactive(void);

// print.c

extern const char	*sgr0;
extern const char	*setaf;

void	display_grid(const u64 *grid, const frame_t *frame);
void	putc_color(const i8 c, const u8 color);

// err.c

_Noreturn void err_exit(const u8 err, const char *context);

#endif
