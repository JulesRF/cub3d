# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/11 14:02:45 by ascotto-          #+#    #+#              #
#    Updated: 2022/10/06 17:36:02 by ascotto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g

NAME		=	cub3D

RM			=	rm -f



MLX_PATH	=	mlx_linux
MLX			=	mlx_linux/libmlx_Linux.a
MLX_FLAGS	=	-Lmlx_linux -lmlx_Linux -L/usr/lib \
				-Imlx_linux -lXext -lX11 -lm -lz

SRCS_FILES	=	main.c					\
				hooks.c					\
				draw.c				 	\
				draw_utils.c			\
				textures.c 				\
				init.c 					\
				raycasting.c			\
				getmap.c				\
				checkmap.c				\
				cleaninf.c				\
				alloc_map.c				\
				check_inf2.c			\
				init_mstruct.c			\
				parsing_utils.c			\
				get_next_line.c			\
				checkmap_utils.c		\
				checkmap_utils2.c		\
				get_next_line_utils.c					

OBJ_DIR		=	.obj
OBJS		=	${addprefix ${OBJ_DIR}/,${SRCS_FILES:.c=.o}}


INCLUDES 	=	includes
SRCS_PATH	=	srcs


all:				${NAME}

${OBJ_DIR}/%.o:		${SRCS_PATH}/%.c
	@mkdir -p ${OBJ_DIR}
	@printf "Compiling $< ...\n"
	@${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o $@

${MLX}:
	@echo "Compiling mlx..."
	@make -C ${MLX_PATH} -s

${NAME}:	${MLX} ${OBJS}
	@echo "Compiling Object files..."
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${MLX} ${MLX_FLAGS} -I ${MLX_PATH}

clean:
	@echo "Removing object files in current directory..."
	@${RM} ${OBJS}

clean-all: clean
	@echo "Removing object files in ${MLX_PATH}..."
	@make clean -C ${MLX_PATH} -s

fclean:		clean
	@echo "Removing executable ${NAME}..."
	@${RM} ${NAME}

re:			fclean all

re-all:		fclean
	@echo "Recompiling mlx..."
	@make re -C ${MLX_PATH} -s
	@make all -s


.PHONY:		all clean fclean re
