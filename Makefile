# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/25 18:02:08 by ivalimak          #+#    #+#              #
#    Updated: 2025/01/07 06:38:45 by ivalimak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	checker

BUILD	=	normal

CC 				=	cc
cflags.common	=	-Wall -Wextra -Werror
cflags.debug	=	-g
cflags.debugm	=	$(cflags.debug) -D DEBUG_MSG=1
cflags.fsan		=	$(cflags.debug) -fsanitize=address,undefined
cflags.normal	=	-Ofast
cflags.extra	=	
CFLAGS			=	$(cflags.common) $(cflags.$(BUILD)) $(cflags.extra)

SRCDIR	=	src
OBJDIR	=	obj
INCDIR	=	inc
LIBDIR	=	libft

LFT	=	$(LIBDIR)/libft.a
INC	=	-I$(INCDIR) -I$(LIBDIR)/$(INCDIR)

SRCFILES	=	main.c \
				args.c \
				input.c \
				check.c \
				check2.c \
				utils.c

SRCS	=	$(addprefix $(SRCDIR)/, $(SRCFILES))
OBJS	=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(LFT) $(OBJDIR) $(OBJS)
	@printf "\e[1;38;5;42mCHECKER >\e[m Linking %s\n" $@
	@$(CC) $(CFLAGS) $(INC) $(OBJS) -L$(LIBDIR) -lft -o $@
	@printf "\e[1;38;5;42mCHECKER >\e[m \e[1mDone!\e[m\n"
ifneq ("$(wildcard ../rush-01)", "")
	@cp $@ ../
endif

$(OBJDIR):
	@printf "\e[1;38;5;42mCHECKER >\e[m Creating objdir\n" $@
	@mkdir -p $(OBJDIR)

$(LFT):
	@make --no-print-directory -C $(LIBDIR) BUILD=$(BUILD) cflags.extra=$(cflags.extra)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@printf "\e[1;38;5;42mCHECKER >\e[m Compiling %s\n" $@
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@make --no-print-directory -C $(LIBDIR) clean
	@rm -f $(OBJS)

fclean: clean
	@make --no-print-directory -C $(LIBDIR) fclean
	@rm -rf $(OBJDIR)
	@rm -f $(NAME)

re: fclean all
