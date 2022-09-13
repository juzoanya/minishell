# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/06 14:58:05 by euyi              #+#    #+#              #
#    Updated: 2022/09/12 16:15:19 by euyi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = app/main.c	app/parser_switch.c	app/run_plugins.c	\
	assets/libft_tools.c	assets/libft_tools_2.c	assets/libft_tools_3.c	\
	assets/run_plugins_utils.c	assets/parser_switch_utils.c	\
	plugins/0-ready_stdin.c	plugins/ready_stdout.c	\
	plugins/1-dollar_processor.c	\
	plugins/2-check_exec_type.c	\
	plugins/run_execve.c	plugins/run_pwd.c	\
	plugins/run_cd.c	plugins/run_echo.c	plugins/run_signal.c	\
	plugins/export_unset_env.c	plugins/run_env.c	\
	plugins_assets/0-ready_stdin_utils.c	plugins_assets/check_exec_type_utils.c	\
	plugins_assets/dollar_processor_utils.c	plugins_assets/cd_utils.c	\
	plugins_assets/cd_utils_2.c	plugins_assets/export_unset_env_utils.c	\
	plugins_assets/run_execve_utils.c	plugins_assets/utilities.c

OBJ = $(subst .c,.o,$(SRC))

CC ?= cc

CFLAGS =	-Wall	-Werror	-Wextra

LINKED =	-lreadline

all: $(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)	$(LINKED)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY:	all	clean	fclean	re
