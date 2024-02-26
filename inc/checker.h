/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:47:39 by ivalimak          #+#    #+#             */
/*   Updated: 2024/02/26 11:28:29 by ivalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include "libft.h"
# include <fcntl.h>
# include <string.h>

# define SGR_ERR "\e[31m"
# define SGR_OK "\e[32m"
# define SGR_KO "\e[35m"
# define SGR_FRM "\e[34m"
# define SGR_GRD "\e[36m"
# define SGR_RST "\e[39m"

typedef struct s_frame
{
	short	*top;
	short	*left;
	short	*right;
	short	*bottom;
}	t_frame;

// args.c
t_frame	*parseargs(char *argstring, size_t argc);

// input.c
short	**getsolution(size_t size);

// check.c
void	checksolution(t_frame *frame, short **grid, size_t size);

// check2.c
void	checktop(t_frame *frame, short **grid, size_t size, char *err);
void	checkbot(t_frame *frame, short **grid, size_t size, char *err);
void	checkleft(t_frame *frame, short **grid, size_t size, char *err);
void	checkright(t_frame *frame, short **grid, size_t size, char *err);

// utils.c
void	chk_perror(void);
void	chk_puterror(const char *err);
void	chk_putgrid(t_frame *frame, short **grid, size_t size);

#endif
