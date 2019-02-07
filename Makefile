# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ocojeda- <ocojeda-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 11:21:21 by ocojeda-          #+#    #+#              #
#    Updated: 2019/02/07 15:24:12 by ocojeda-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop
CC = gcc

SRC_PATH = ./src/
OBJ_PATH = ./obj/
LIB_PATH = ./lib/
INC_PATH = ./include/ $(LIB_PATH)libft/include/ $(LIB_PATH)glfw/include/ \
			$(LIB_PATH)libmat4/include/
GCC_FLGS = -g -Werror -Wextra -Wall
GCC_LIBS = -lglfw3 -framework AppKit -framework OpenGL -framework IOKit -framework CoreVideo

SRC_NAME = main.c init.c events_scop.c matrix.c parse_obj.c camera.c bitmap_parser.c matrix_ops.c \
shader_parser.c init_aux.c init_glfw.c parse_obj1.c

OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_NAME = libft libmat4 glfw/src

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LIB = $(addprefix -L$(LIB_PATH),$(LIB_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_PATH)libft -j
	make -C $(LIB_PATH)libmat4 -j
	$(CC) $(GCC_FLGS) $(LIB) -lft -lmat4 $(INC) $(OBJ) $(GCC_LIBS) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(GCC_FLGS) $(INC) -o $@ -c $<

clean:
	rm -fv $(OBJ)
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C $(LIB_PATH)libft fclean
	make -C $(LIB_PATH)libmat4 fclean
	rm -fv $(NAME)

re: fclean all