# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/11 14:02:45 by ascotto-          #+#    #+#              #
#    Updated: 2022/08/29 08:54:47 by ascotto-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

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
				init_mstruct.c			\
				parsing_utils.c			\
				get_next_line.c			\
				checkmap_utils.c		\
				checkmap_utils2.c		\
				get_next_line_utils.c					

FLAGS = -Wall -Werror -Wextra -g

MLXFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

INCLUDES = includes

PATH = srcs

OBJ_DIR = obj

OBJ = $(addprefix $(OBJ_DIR)/,$(SRCS_FILES:.c=.o))

all: $(NAME)

$(OBJ_DIR)/%.o: $(PATH)/%.c
	@$(shell mkdir -p $(OBJ_DIR))
	@printf "Compiling $< ...\n"
	@$(shell cc $(FLAGS) -I $(INCLUDES) -c $< -o $@)

$(NAME): $(OBJ)
	@$(shell cc $(OBJ) $(MLXFLAGS) -o $(NAME))
	@printf "Executable $@ created !\n"

clean:
	@printf "Deleting objects\n"
	@$(shell rm -rf $(OBJ_DIR))

fclean: clean
	@printf "Deleting executable\n"
	@$(shell rm -rf $(NAME))

bonus: $(NAME)

re: fclean all

.PHONY:		all clean fclean re
