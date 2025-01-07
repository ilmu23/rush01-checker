// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<args.c>>

#include "checker.h"

static inline u8	_count_args(const char **args);

const frame_t	*args_parse(const char *argstr) {
	static frame_t	frame;
	const char		**args;
	u64				argval;
	u8				*tmp;
	u8				i;

	args = ft_pusharr(ft_split(argstr, ' '));
	if (!args)
		err_exit(E_ALLOC_FAIL, NULL);
	frame.size = _count_args(args);
	frame = (frame_t) {
		.size = frame.size,
		.top = alloc(frame.size * sizeof(*frame.top)),
		.bot = alloc(frame.size * sizeof(*frame.bot)),
		.lft = alloc(frame.size * sizeof(*frame.lft)),
		.rgt = alloc(frame.size * sizeof(*frame.rgt))
	};
	if (!frame.top || !frame.bot || !frame.lft || !frame.rgt)
		err_exit(E_ALLOC_FAIL, NULL);
	for (i = 0, tmp = frame.top; args[i]; i++) {
		argval = ft_atou64(args[i]);
		if (!inrange(argval, 1, frame.size))
			err_exit(E_ARG_OUT_OF_RANGE, NULL);
		tmp[i % frame.size] = (u8)argval;
		if ((i + 1) % frame.size == 0) {
			switch ((i + 1) / frame.size) {
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
		ft_popblk(args[i]);
	}
	ft_popblk(args);
	return &frame;
}

static inline u8	_count_args(const char **args) {
	u8	i;

	for (i = 0; args[i]; i++)
		;
	if (i % 4)
		err_exit(E_INVALID_ARGC, NULL);
	i /= 4;
	if (!inrange(i, 4, 9))
		err_exit(E_INVALID_ARGC, NULL);
	return i;
}
