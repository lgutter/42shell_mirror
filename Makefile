# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lgutter <lgutter@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/09/11 13:40:17 by lgutter       #+#    #+#                  #
#    Updated: 2020/06/15 14:07:04 by lgutter       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include src/42shsrcs
include inc/headerlist

OBJS := $(42SHSRCS:%= src/%.o)
LIBFT := ft_printf/libftprintf.a
INCLPATH := -I ./inc -I ./ft_printf
MAIN := src/main.o

CFLAGS := -Wall -Wextra -Werror -O2

NAME := 42sh

PLUS = \033[38;5;40m| + |\033[0;00m
MINUS = \033[38;5;160m| - |\033[0;00m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(MAIN) $(HEADERS)
	@$(CC) $(MAIN) $(OBJS) $(CFLAGS) $(LIBFT) -ltermcap $(INCLPATH) -o $@
	@echo "$(PLUS) compiled: $@"

$(LIBFT): FORCE
	@$(MAKE) -C ft_printf/

%.o: %.c
	@$(CC) -c $< $(CFLAGS) $(INCLPATH) -o $@
	@echo "$(PLUS) compiled: $@"

lclean:
	@rm -rfv $(OBJS) $(MAIN)| sed -E $$'s/(.*)/$(MINUS) removed: \\1/g'

clean: lclean
	@$(MAKE) clean -C ft_printf/

lfclean: lclean
	@rm -rfv $(NAME) | sed -E $$'s/(.*)/$(MINUS) removed: \\1/g'

fclean: lfclean
	@$(MAKE) fclean -C ft_printf/

re:
	@$(MAKE) fclean
	@$(MAKE) all

FORCE:

.PHONY: all clean lclean lfclean fclean re FORCE
