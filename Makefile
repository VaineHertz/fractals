# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpadilla <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/30 12:28:05 by tpadilla          #+#    #+#              #
#    Updated: 2017/01/11 10:07:22 by tpadilla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
SRC = fractol.c
OBJ = $(SRC:.c=.o)
MLX = minilibx_macos/libmlx.a
LIBFT = libft/libft.a
FRAMEWORK = -framework OpenGL -framework AppKit
all: $(NAME)

$(NAME): $(OBJ)
	make -C minilibx_macos/
	make -C libft/
	gcc -o $(NAME) $(OBJ) $(MLX) $(LIBFT) $(FRAMEWORK)

clean:
	rm -f $(OBJ)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean
	make -C minilibx_macos/ clean

run: $(OBJ)
	gcc -o $(NAME) $(OBJ) $(MLX) $(LIBFT) $(FRAMEWORK)
	rm -f $(OBJ)

fsan: $(OBJ)
	gcc -o $(NAME) $(OBJ) $(MLX) $(LIBFT) $(FRAMEWORK) -fsanitize=address
	rm -f $(OBJ)

re: clean all
	make -C minilibx_macos/ re
	make -C libft/ re
