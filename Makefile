# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/25 18:02:08 by ivalimak          #+#    #+#              #
#    Updated: 2024/02/26 13:06:20 by ivalimak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	checker

BUILD	=	normal

CC 				=	cc
cflags.common	=	-Wall -Wextra -Werror
cflags.debug	=	-g
cflags.debum	=	$(cflags.debug) -D DEBUG_MSG=1
cflags.asan		=	$(cflags.debug) -fsanitize=address -static-libsan
cflags.normal	=	
CFLAGS			=	$(cflags.common) $(cflags.$(BUILD))

SRCDIR	=	src
OBJDIR	=	obj
INCDIR	=	inc
LIBDIR	=	libft
LIBFT	=	$(LIBDIR)/libft.a

SRCFILES	=	main.c \
				args.c \
				input.c \
				check.c \
				check2.c \
				utils.c

SRCS	=	$(addprefix $(SRCDIR)/, $(SRCFILES))
OBJS	=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(OBJDIR) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo Compiling $(NAME)...
	@$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBDIR) $(OBJS) -L$(LIBDIR) -lft -o $(NAME)
ifneq ("$(wildcard ../rush-01)", "")
	@cp $(NAME) ../
endif

$(OBJDIR):
	@echo Creating objdir...
	@mkdir -p $(OBJDIR)

$(LIBFT):
	@make -C $(LIBDIR) BUILD=$(BUILD)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo Compiling $@
	@$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBDIR) -c $< -o $@

clean:
	@make -C $(LIBDIR) clean
	@rm -f $(OBJS)

fclean: clean
	@make -C $(LIBDIR) fclean
	@rm -rf $(OBJDIR)
	@rm -f $(NAME)

re: fclean all
