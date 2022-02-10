# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bterral <bterral@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 10:52:39 by bterral           #+#    #+#              #
#    Updated: 2022/02/10 13:28:17 by bterral          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= pipex

NAME_BONUS		= pipex_bonus

LIBFT			= libft/libft.a

SRCS			= pipex.c	children_processes.c	error.c

SRCS_BONUS		= pipex_bonus.c	children_processes_bonus.c	error_bonus.c

OBJS			= ${addprefix ${OBJD},${SRCS:.c=.o}}

OBJS_BONUS		= ${addprefix ${OBJD_BONUS},${SRCS_BONUS:.c=.o}}

SRCD			= srcs/

SRCD_BONUS		= srcs_bonus/

OBJD			= .obj/

OBJD_BONUS		= .obj_bonus/

INCLUDES		= includes/pipex.h

INCLUDES_BONUS	= includes_bonus/pipex_bonus.h

INCLUDESD		= includes/

INCLUDESD_BONUS	= includes_bonus/

INCLUDES_LIBFT	= libft/libft.h

INCLUDES_LIBFTD	= libft

CC				= gcc

CFLAGS			= -Wall -Wextra -Werror

all: $(LIBFT) ${NAME}

bonus: ${NAME_BONUS}

${NAME}: ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}

${OBJD}%.o: ${SRCD}%.c ${INCLUDES} ${INCLUDES_LIBFT} | ${OBJD}
	${CC} ${CFLAGS} -I $(INCLUDESD) -I ${INCLUDES_LIBFTD} -c $< -o $@ 

${NAME_BONUS}: ${OBJS_BONUS} ${LIBFT}
	${CC} ${CFLAGS} ${OBJS_BONUS} ${LIBFT} -o ${NAME_BONUS}

${OBJD_BONUS}%.o: ${SRCD_BONUS}%.c ${INCLUDES_BONUS} ${INCLUDES_LIBFT} | ${OBJD_BONUS}
	${CC} ${CFLAGS} -I ${INCLUDESD_BONUS} -I ${INCLUDES_LIBFTD} -c $< -o $@

${OBJD}:
	mkdir -p $@

${OBJD_BONUS}:
	mkdir -p $@

$(LIBFT):
	$(MAKE) -C libft/
    
clean:
	rm -rf ${OBJD}
	rm -rf ${OBJD_BONUS}
	$(MAKE) clean -C libft/

fclean: clean
	rm -f ${NAME}
	rm -f ${NAME_BONUS}
	$(MAKE) fclean -C libft/

re: fclean all

.PHONY: all lib clean fclean re