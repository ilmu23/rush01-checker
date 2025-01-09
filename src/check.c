// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<check.c>>

#include "checker.h"

u64			sum_tgt;
u8			ko;

#define gnl			(ft_push(get_next_line(0)))
#define err_line	(ft_strnjoin(3, ft_itoa(lnbr + 1), ": ", line))

static inline void	_check_line(const u64 *line, const char *lname, const u8 hint1, const u8 hint2, u8 lsize);
static inline void	_fill_grid(u64 *grid, u8 size);

void	check(const frame_t *frame) {
	static const char	*rnames[9] = {"row 1", "row 2", "row 3", "row 4", "row 5", "row 6", "row 7", "row 8", "row 9"};
	static const char	*cnames[9] = {"col 1", "col 2", "col 3", "col 4", "col 5", "col 6", "col 7", "col 8", "col 9"};
	u64					*line;
	u64					*grid;
	u8					i;
	u8					j;

	line = alloc(frame->size * sizeof(*line));
	grid = alloc((frame->size * frame->size) * sizeof(*grid));
	if (!line || !grid)
		err_exit(E_ALLOC_FAIL, NULL);
	_fill_grid(grid, frame->size);
	display_grid(grid, frame);
	for (sum_tgt = 0, i = 1; i <= frame->size; i++)
		sum_tgt += i;
	for (i = 0; i < frame->size; i++) {
		ft_memcpy(line, &grid[i * frame->size], frame->size * sizeof(*line));
		_check_line(line, rnames[i], frame->lft[i], frame->rgt[i], frame->size);
	}
	for (i = 0; i < frame->size; i++) {
		for (j = 0; j < frame->size; j++)
			line[j] = grid[j * frame->size + i];
		_check_line(line, cnames[i], frame->top[i], frame->bot[i], frame->size);
	}
	if (!ko && ft_printf("%sOK!%s\n", ft_ti_tparm(setaf, COLOR_OK), sgr0) == -1)
		err_exit(E_STDOUT_WRITE, NULL);
	else if (ko && ft_printf("%sKO!%s\n", ft_ti_tparm(setaf, COLOR_KO), sgr0) == -1)
		err_exit(E_STDOUT_WRITE, NULL);
}

static inline void	_check_line(const u64 *line, const char *lname, const u8 hint1, const u8 hint2, u8 lsize) {
	u64					hi;
	u64					sum;
	u8					visible;
	u8					i;

	if (!sgr0)
		sgr0 = ft_ti_getstr("sgr0");
	for (i = sum = 0; i < lsize; i++)
		sum += line[i];
	if (sum != sum_tgt) {
		if (ft_printf("%sInvalid sum on %s%s\n", ft_ti_tparm(setaf, COLOR_KO), lname, sgr0) == -1)
			err_exit(E_STDOUT_WRITE, NULL);
		ko = 1;
	}
	for (i = hi = visible = 0; i < lsize; i++) {
		if (line[i] > hi) {
			hi = line[i];
			visible++;
		}
	}
	if (visible != hint1) {
		if (ft_printf("%sExpected %hhu visible numbers at %s %s, found %hhu%s\n", ft_ti_tparm(setaf, COLOR_KO), hint1, lname, (*lname == 'r') ? "left" : "top", visible, sgr0) == -1)
			err_exit(E_STDOUT_WRITE, NULL);
		ko = 1;
	}
	for (hi = visible = 0, i--; lsize; lsize--, i--) {
		if (line[i] > hi) {
			hi = line[i];
			visible++;
		}
	}
	if (visible != hint2) {
		if (ft_printf("%sExpected %hhu visible numbers at %s %s, found %hhu%s\n", ft_ti_tparm(setaf, COLOR_KO), hint2, lname, (*lname == 'r') ? "right" : "bot", visible, sgr0) == -1)
			err_exit(E_STDOUT_WRITE, NULL);
		ko = 1;
	}
}

static inline void	_fill_grid(u64 *grid, u8 size) {
	char	**numbers;
	char	*line;
	char	*tmp;
	u8		gsize;
	u8		lnbr;
	u8		i;
	u8		j;

	for (i = lnbr = errno = 0, gsize = size * size, line = gnl; line && i < gsize; errno = 0, line = gnl, lnbr++) {
		for (tmp = line; *tmp; tmp++) {
			if (ft_isspace(*tmp))
				*tmp = ' ';
		}
		numbers = ft_pusharr(ft_split(line, ' '));
		if (!numbers)
			err_exit(E_ALLOC_FAIL, NULL);
		for (j = 0; numbers[j] && j < size; j++)
			grid[i++] = ft_atou64(numbers[j]);
		if (numbers[j])
			err_exit(E_TOO_MANY_NUMBERS, err_line);
		if (j < size)
			err_exit(E_NOT_ENOUGH_NUMBERS, err_line);
		ft_popblk(line);
	}
	if (line)
		err_exit(E_TOO_MANY_LINES, NULL);
	if (i < gsize) {
		if (errno)
			err_exit(E_STDIN_READ, NULL);
		err_exit(E_NOT_ENOUGH_LINES, NULL);
	}
}
