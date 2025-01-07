// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<main.c>>

#include "checker.h"

i32	main(i32 ac, char **av) {
	const frame_t	*frame;

	if (ac != 2)
		err_exit(E_INVALID_ARGC, NULL);
	if (!ft_ti_loadinfo(getenv("TERM")))
		err_exit(E_NO_TERMINFO_FOUND, NULL);
	sgr0 = ft_ti_getstr("sgr0");
	setaf = ft_ti_getstr("setaf");
	if (sgr0 == ABS_STR || setaf == ABS_STR)
		err_exit(E_MISSING_TERMINFO_CAP, NULL);
	frame = args_parse(av[1]);
	check(frame);
	return ft_return(0);
}
