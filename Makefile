# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/25 18:02:08 by ivalimak          #+#    #+#              #
#    Updated: 2025/01/07 17:01:48 by ivalimak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	checker

BUILD	=	normal

COLOR_FRAME	=	
COLOR_GRID	=	
COLOR_OK	=	
COLOR_KO	=	

CC 				=	cc
cflags.common	=	-Wall -Wextra -Werror -Wpedantic -pedantic-errors -std=c17
cflags.debug	=	-g
cflags.debugm	=	$(cflags.debug) -D DEBUG_MSG=1
cflags.fsan		=	$(cflags.debug) -fsanitize=address,undefined
cflags.normal	=	-Ofast
cflags.extra	=	
CFLAGS			=	$(cflags.common) $(cflags.$(BUILD)) $(cflags.extra)

ifneq ("$(COLOR_FRAME)", "")
	CFLAGS += -DCOLOR_FRAME=$(COLOR_FRAME)
endif

ifneq ("$(COLOR_GRID)", "")
	CFLAGS += -DCOLOR_GRID=$(COLOR_GRID)
endif

ifneq ("$(COLOR_OK)", "")
	CFLAGS += -DCOLOR_OK=$(COLOR_OK)
endif

ifneq ("$(COLOR_KO)", "")
	CFLAGS += -DCOLOR_KO=$(COLOR_KO)
endif

LDFLAGS	=	-L$(LFTDIR) -L$(LRLDIR) -L$(LTIDIR) -lrl42 -lti42 -lft

SRCDIR	=	src
OBJDIR	=	obj
INCDIR	=	inc
LIBDIR	=	lib
LRLDIR	=	$(LIBDIR)/rl42
LTIDIR	=	$(LIBDIR)/ti42
LFTDIR	=	$(LIBDIR)/libft

LFT	=	$(LFTDIR)/libft.a
LRL	=	$(LRLDIR)/librl42.a
LTI	=	$(LTIDIR)/libti42.a
INC	=	-I$(INCDIR) -I$(LFTDIR)/$(INCDIR) -I$(LRLDIR)/$(INCDIR) -I$(LTIDIR)/$(INCDIR)

SRCFILES	=	main.c \
				args.c \
				check.c \
				err.c \
				interactive.c \
				print.c

SRCS	=	$(addprefix $(SRCDIR)/, $(SRCFILES))
OBJS	=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(LFT) $(LTI) $(LRL) $(OBJDIR) $(OBJS)
	@printf "\e[1;38;5;42mCHECKER >\e[m Linking %s\n" $@
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@
	@printf "\e[1;38;5;42mCHECKER >\e[m \e[1mDone!\e[m\n"
ifneq ("$(wildcard ../rush-01)", "")
	@cp $@ ../
endif

$(LFT):
	@make --no-print-directory -C $(LFTDIR) BUILD=$(BUILD) cflags.extra=$(cflags.extra)

$(LRL):
	@make --no-print-directory -C $(LRLDIR) BUILD=$(BUILD) cflags.extra=$(cflags.extra)

$(LTI):
	@make --no-print-directory -C $(LTIDIR) BUILD=$(BUILD) cflags.extra=$(cflags.extra)

$(OBJDIR):
	@printf "\e[1;38;5;42mCHECKER >\e[m Creating objdir\n" $@
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@printf "\e[1;38;5;42mCHECKER >\e[m Compiling %s\n" $@
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@make --no-print-directory -C $(LFTDIR) clean
	@make --no-print-directory -C $(LRLDIR) fclean
	@make --no-print-directory -C $(LTIDIR) clean
	@rm -f $(OBJS)

fclean: clean
	@make --no-print-directory -C $(LFTDIR) fclean
	@make --no-print-directory -C $(LRLDIR) fclean
	@make --no-print-directory -C $(LTIDIR) fclean
	@rm -rf $(OBJDIR)
	@rm -f $(NAME)

re: fclean all

db:
	@make --no-print-directory -C $(LFTDIR) db BUILD=$(BUILD) cflags.extra=$(cflags.extra)
	@make --no-print-directory -C $(LRLDIR) db BUILD=$(BUILD) cflags.extra=$(cflags.extra)
	@make --no-print-directory -C $(LTIDIR) db BUILD=$(BUILD) cflags.extra=$(cflags.extra)
	@printf "\e[1;38;5;42mCHECKER >\e[m Creating compilation command database\n"
	@compiledb make --no-print-directory BUILD=$(BUILD) cflags.extra=$(cflags.extra) | sed -E '/^##.*\.\.\.$$|^[[:space:]]*$$/d'
	@printf "\e[1;38;5;42mCHECKER >\e[m \e[1mDone!\e[m\n"

.PHONY: all clean fclean re db
