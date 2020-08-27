# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lgutter <lgutter@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/09/11 13:40:17 by lgutter        #+#    #+#                 #
#    Updated: 2020/01/08 10:31:03 by lgutter       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include Source_files/printfsources
include libft/libftsources
include libft/covsources

JUNK = $(shell find -E . -regex ".*(\..*~|\#.*\#|\.DS_Store)" 2>/dev/null)

OBJECTS := $(PRINTFSOURCES:%=Source_files/%.o)
OBJECTS += $(LFTSOURCES:%=libft/%.o)
OBJECTS += $(COVSOURCES:%=libft/%.o)

INCL_PATH := -I. -I./libft/
HEADER := ft_printf.h

CFLAGS = -Wall -Wextra -Werror -g

NAME := libftprintf.a

PLUS = \033[38;5;35m| + |\033[0;00m
MINUS = \033[38;5;214m| - |\033[0;00m

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER)
	@ar rc $@ $^
	@ranlib $@
	@echo "$(PLUS) compiled: $@"

%.o: %.c
	@gcc -c $< $(CFLAGS) $(INCL_PATH) -o $@
	@echo "$(PLUS) compiled: $@"

clean:
	@rm -rfv $(JUNK) $(OBJECTS) | sed -E $$'s/(.*)/$(MINUS) removed: \\1/g'

fclean: clean
	@rm -rfv $(NAME) | sed -E $$'s/(.*)/$(MINUS) removed: \\1/g'

re: fclean all

.PHONY: all clean fclean re
