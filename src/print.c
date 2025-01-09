// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<print.c>>

#include "checker.h"

static inline const char	*_utoa(const u64 n);

ssize_t	tputc(const i8 c) {
	return write(1, &c, 1);
}

void	display_grid(const u64 *grid, const frame_t *frame) {
	const char	*n;
	u8			i;
	u8			j;

	if (ft_putstr_fd("  ", 1) == -1)
		err_exit(E_STDOUT_WRITE, NULL);
	for (i = 0; i < frame->size;) {
		n = _utoa(frame->top[i]);
		while (*n)
			putc_color(*n++, COLOR_FRAME);
		if (tputc((++i != frame->size) ? ' ' : '\n') == -1)
			err_exit(E_STDOUT_WRITE, NULL);
	}
	for (i = 0; i < frame->size; i++) {
		n = _utoa(frame->lft[i]);
		while (*n)
			putc_color(*n++, COLOR_FRAME);
		if (tputc(' ') == -1)
			err_exit(E_STDOUT_WRITE, NULL);
		for (j = 0; j < frame->size; j++) {
			n = _utoa(grid[i * frame->size + j]);
			while (*n)
				putc_color(*n++, COLOR_GRID);
			if (tputc(' ') == -1)
				err_exit(E_STDOUT_WRITE, NULL);
		}
		n = _utoa(frame->rgt[i]);
		while (*n)
			putc_color(*n++, COLOR_FRAME);
		if (tputc('\n') == -1)
			err_exit(E_STDOUT_WRITE, NULL);
	}
	if (ft_putstr_fd("  ", 1) == -1)
		err_exit(E_STDOUT_WRITE, NULL);
	for (i = 0; i < frame->size;) {
		n = _utoa(frame->bot[i]);
		while (*n)
			putc_color(*n++, COLOR_FRAME);
		if (tputc((++i != frame->size) ? ' ' : '\n') == -1)
			err_exit(E_STDOUT_WRITE, NULL);
	}
	if (tputc('\n') == -1)
		err_exit(E_STDOUT_WRITE, NULL);
}

void	putc_color(const i8 c, const u8 color) {
	if (ft_ti_tputs(ft_ti_tparm(ft_ti_getstr("setaf"), color), 1, tputc) == -1 ||
		tputc(c) == -1 || ft_ti_tputs(ft_ti_getstr("sgr0"), 1, tputc) == -1)
		err_exit(E_STDOUT_WRITE, NULL);
}

static inline const char	*_utoa(const u64 n) {
	const char	*out;

	out = ft_utoa(n);
	if (!out)
		err_exit(E_ALLOC_FAIL, NULL);
	return out;
}
