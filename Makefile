# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bterral <bterral@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 10:52:39 by bterral           #+#    #+#              #
#    Updated: 2022/02/10 10:55:53 by bterral          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 				:= pipex

### FILES ###

SRCS_FILES			:= pipex.c error.c children_processes.c

OBJS 				:= $(addprefix $(OBJS_DIR), $(SRCS_FILES:.c=.o))

SRCS_DIR			:= srcs/

OBJS_DIR			:= objs/

### INCLUDES ###

INCLUDES			:= ./includes/pipex.h

INCLUDES_LIB		:= ./libft/libft.h

### LIB ###

LIBFT_DIR			:= ./libft

LIBFT_LIB 			:= ./libft/libft.a

### COMMANDS ###

CC					:= gcc

CFLAGS				:= -Wall -Wextra -Werror

RM					:= rm -rf

.PHONY: all clean fclean re

all: $(OBJS) #$(LIBFT_LIB) $(NAME) 

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) ${OBJS} ${LIBFT_LIB} -o $(NAME)

${OBJS_DIR}%.o: .c $(INCLUDES) $(INCLUDES_LIB) | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS_DIR)
	$(MAKE) clean -C ./libft

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C ./libft

re: fclean all