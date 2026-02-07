# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 02:37:43 by dukim             #+#    #+#              #
#    Updated: 2025/01/08 02:37:45 by dukim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		= 	rm -rf
SRC		= 	src/builtins/builtin_handler.c \
			src/builtins/ft_cd.c \
			src/builtins/ft_echo.c \
			src/builtins/ft_env.c \
			src/builtins/ft_exit.c \
			src/builtins/ft_export.c \
			src/builtins/ft_pwd.c \
			src/builtins/ft_unset.c\
			src/command/cmd_utils.c \
			src/command/excutor_utils.c \
			src/command/command.c \
			src/command/excutor.c \
			src/command/redirection.c \
			src/command/heredoc.c \
			src/tokenizer/quote_parser.c \
			src/tokenizer/tokenizer.c \
			src/tokenizer/token_utils.c \
			src/tokenizer/word_utils.c \
			src/utils/env_utils.c \
			src/utils/error_utils.c \
			src/utils/ft_utils1.c \
			src/signal_handler.c \
			src/parser_handler.c \
			src/main.c
OBJS = $(SRC:.c=.o)
NAME = minishell

all : $(NAME)
		
$(NAME): $(OBJS)
	@make bonus -C libft/
	@$(CC) $(CFLAGS) $(OBJS) -L libft/ -lft -o $(NAME) -lreadline

clean :
	@make clean -C libft/
	@$(RM) $(OBJS)
	
fclean :
	@make fclean -C libft/
	@$(RM) $(OBJS) $(NAME)

re :
	@make fclean
	@make all

.PHONY: all clean fclean re
