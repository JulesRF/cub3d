# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/11 14:02:45 by ascotto-          #+#    #+#              #
#    Updated: 2022/07/29 17:28:49 by jroux-fo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS_FILES	=	main.c 					\
				get_next_line.c			\
				get_next_line_utils.c	\
				# ft_itoa.c				\
				# ft_init.c				\
				# ft_utils.c				\
				# ft_switch.c				\
				# ft_square.c				\
				# ft_checkmap.c			\
				# ft_alloc_map.c			\
				# ft_checkchar.c			\
				# ft_enemy_move.c			\
				# ft_checkrectangle.c		\

FLAGS = -Wall -Werror -Wextra -Imlx_linux -g

#MLXFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -I mlx_linux -lXext -lX11 -lm -lz

INCLUDES = header

PATH = srcs

OBJ_DIR = obj

OBJ = $(addprefix $(OBJ_DIR)/,$(SRCS_FILES:.c=.o))

all: $(NAME)

$(OBJ_DIR)/%.o: $(PATH)/%.c
	@$(shell mkdir -p $(OBJ_DIR))
	@printf "Compiling $< ...\n"
	@$(shell gcc $(FLAGS) -I $(INCLUDES) -c $< -o $@)

$(NAME): $(OBJ)
	@$(shell gcc $(OBJ) -o $(NAME))
#$(MLXFLAGS)
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
