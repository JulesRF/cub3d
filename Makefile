# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ascotto- <ascotto-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/11 14:02:45 by ascotto-          #+#    #+#              #
#    Updated: 2022/02/01 14:59:57 by ascotto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT		=	libft/libft.a
LIB_PATH 	=	./libft

LMLX		=	~/minilibx/libmlx_Linux.a
MLX_PATH	=	~/minilibx

SRCS		=	ft_argchecker.c \
				ft_mlx.c \
				ft_draw_line.c \
				ft_end.c \
				ft_fdf.c \
				ft_hooks.c \
				ft_parsing.c \
				ft_print.c \
				ft_projection.c \
				ft_utils.c

OBJS		= 	${SRCS:.c=.o}

.c.o:
	@echo "Creating object file for $<..."
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${LIB_PATH} -I ${MLX_PATH}

NAME		= fdf

CC			= cc
RM			= rm -f

CFLAGS		=  -Wall -Wextra -Werror -g
CLIBS		= -lXext -lX11 -lm

all:	${NAME}

${LIBFT}:	
	@echo "Compiling Libft..."
	@make -C ${LIB_PATH} -s

${NAME}:	${LIBFT} ${OBJS}
	@echo "Compiling Object files..."
	@${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${LMLX} -o ${NAME} -I ${LIB_PATH} -I ${MLX_PATH} ${CLIBS}

clean:
	@echo "Removing object files in current directory..."
	@${RM} ${OBJS}

clean-all: clean
	@echo "Removing object files in ${LIB_PATH}..."
	@make clean -C ${LIB_PATH} -s

fclean:		clean
	@echo "Removing executable ${NAME}..."
	@${RM} ${NAME}

fclean-all: fclean
	@echo "Removing object files in ${LIB_PATH}..."
	@make fclean -C ${LIB_PATH} -s

re:			fclean all

re-all:		fclean
	@echo "Recompiling Libft..."
	@make re -C ${LIB_PATH} -s
	@make all -s
