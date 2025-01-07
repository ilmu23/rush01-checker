# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/23 15:26:18 by ivalimak          #+#    #+#              #
#    Updated: 2025/01/07 07:40:55 by ivalimak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

BUILD	=	normal

CC				=	cc
cflags.common	=	-Wall -Wextra -Werror
cflags.debug	=	-g
cflags.debugm 	=	$(cflags.debug) -D DEBUG_MSG=1
cflags.asan		=	$(cflags.debug) -fsanitize=address
cflags.normal	=	-Ofast
cflags.extra	=	
CFLAGS			=	$(cflags.common) $(cflags.$(BUILD)) $(cflags.extra)

SRCDIR	=	src
OBJDIR	=	obj
INCDIR	=	inc

GCDIR	=	gc
GNLDIR	=	gnl
HMAPDIR	=	hmap
ISDIR	=	is
LSTDIR	=	lst
MATHDIR	=	math
MEMDIR	=	mem
NBRDIR	=	nbr
PFDIR	=	printf
PUTDIR	=	put
STRDIR	=	str
TODIR	=	to

GCFILES		=	ft_alloc.c \
				ft_arrdup.c \
				ft_calloc.c \
				ft_clean.c \
				ft_exit.c \
				ft_getblksize.c \
				ft_mark.c \
				ft_obj.c \
				ft_objmap.c \
				ft_pop.c \
				ft_push.c \
				ft_pushtrap.c \
				ft_register.c \
				ft_return.c \
				ft_sweep.c \
				ft_vm.c

GNLFILES	=	gnl.c \
				gnl_utils.c

HMAPFILES	=	ft_mapadd.c \
				ft_maparr.c \
				ft_mapget.c \
				ft_mapnew.c \
				ft_mappop.c \
				ft_maprm.c \
				ft_map_utils.c \
				ft_map_utils2.c

ISFILES		=	ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isfloat.c \
				ft_isint_base.c \
				ft_isint.c \
				ft_isint_utils.c \
				ft_islower.c \
				ft_isprime.c \
				ft_isprint.c \
				ft_isspace.c \
				ft_isuint_base.c \
				ft_isuint.c \
				ft_isupper.c

LSTFILES	=	ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstdup.c \
				ft_lstfirst.c \
				ft_lstlast.c \
				ft_lstnew.c \
				ft_lstpopall.c \
				ft_lstpop.c \
				ft_lstpushall.c \
				ft_lstpush.c \
				ft_lstrmnode.c

MATHFILES	=	ft_ceil.c \
				ft_floor.c \
				ft_max.c \
				ft_min.c \
				ft_pow.c \
				ft_round.c \
				ft_sqrt.c \
				ft_umax.c \
				ft_umin.c \
				ft_upow.c

MEMFILES	=	ft_bzero.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c

NBRFILES	=	ft_intlen.c \
				ft_uintlen.c

PFFILES		=	ft_printf.c \
				ft_dprintf.c \
				ft_sprintf.c \
				ft_snprintf.c \
				ft_vprintf.c \
				ft_vdprintf.c \
				ft_vsprintf.c \
				ft_vsnprintf.c \
				cast.c \
				expand.c \
				expand2.c \
				parse.c \
				parse2.c \
				utils.c

PUTFILES	=	ft_debugmsg.c \
				ft_debugnbr.c \
				ft_debugunbr.c \
				ft_debugxnbr.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_putunbr_fd.c \
				ft_putxnbr_fd.c

STRFILES	=	ft_split.c \
				ft_strchr.c \
				ft_strclen.c \
				ft_strdup.c \
				ft_strequals.c \
				ft_strhash.c \
				ft_strjoin.c \
				ft_strnjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strlower.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strremove.c \
				ft_strrev.c \
				ft_strsjoin.c \
				ft_strsnjoin.c \
				ft_strtrim.c \
				ft_strupper.c \
				ft_substr.c \
				ft_wordcount.c

TOFILES		=	ft_atof.c \
				ft_atoi_base.c \
				ft_atoi.c \
				ft_atou_base.c \
				ft_atou.c \
				ft_itoa_base.c \
				ft_itoa.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_utoa_base.c \
				ft_utoa.c

FILES	=	$(addprefix $(GCDIR)/, $(GCFILES)) \
			$(addprefix $(GNLDIR)/, $(GNLFILES)) \
			$(addprefix $(HMAPDIR)/, $(HMAPFILES)) \
			$(addprefix $(ISDIR)/, $(ISFILES)) \
			$(addprefix $(LSTDIR)/, $(LSTFILES)) \
			$(addprefix $(MATHDIR)/, $(MATHFILES)) \
			$(addprefix $(MEMDIR)/, $(MEMFILES)) \
			$(addprefix $(NBRDIR)/, $(NBRFILES)) \
			$(addprefix $(PFDIR)/, $(PFFILES)) \
			$(addprefix $(PUTDIR)/, $(PUTFILES)) \
			$(addprefix $(STRDIR)/, $(STRFILES)) \
			$(addprefix $(TODIR)/, $(TOFILES))

SRCS	=	$(addprefix $(SRCDIR)/, $(FILES))
OBJS	=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(NAME)

bonus:
	@printf "bonus!\n"

$(NAME): $(OBJDIR) $(OBJS)
	@printf "\e[34;1mLIBFT >\e[m Creating %s\n" $@
	@ar -crs $(NAME) $(OBJS)
	@printf "\e[34;1mLIBFT >\e[m \e[1mDone!\e[m\n"

$(OBJDIR):
	@printf "\e[34;1mLIBFT >\e[m Creating objdirs\n" $@
	@mkdir -p $(OBJDIR)/$(GCDIR)
	@mkdir -p $(OBJDIR)/$(GNLDIR)
	@mkdir -p $(OBJDIR)/$(HMAPDIR)
	@mkdir -p $(OBJDIR)/$(ISDIR)
	@mkdir -p $(OBJDIR)/$(LSTDIR)
	@mkdir -p $(OBJDIR)/$(MATHDIR)
	@mkdir -p $(OBJDIR)/$(MEMDIR)
	@mkdir -p $(OBJDIR)/$(NBRDIR)
	@mkdir -p $(OBJDIR)/$(PFDIR)
	@mkdir -p $(OBJDIR)/$(PUTDIR)
	@mkdir -p $(OBJDIR)/$(STRDIR)
	@mkdir -p $(OBJDIR)/$(TODIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@printf "\e[34;1mLIBFT >\e[m Compiling %s\n" $@
	@$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -rf $(OBJDIR)
	@rm -f $(NAME)

re: fclean all

db:
	@printf "\e[34;1mLIBFT >\e[m Creating compilation command database\n"
	@compiledb make --no-print-directory BUILD=$(BUILD) cflags.extra=$(cflags.extra) | sed -E '/^##.*\.\.\.$$|^[[:space:]]*$$/d'
	@printf "\e[34;1mLIBFT >\e[m \e[1mDone!\e[m\n"

.PHONY: all clean fclean re db
