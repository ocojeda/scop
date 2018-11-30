NAME = scop
CC = gcc

SRC_PATH = ./src/
OBJ_PATH = ./obj/
LIB_PATH = ./lib/
INC_PATH = ./include/ $(LIB_PATH)glfw/include/ \
		   			$(LIB_PATH)libvec/include/

GCC_FLGS = -g #-Werror -Wextra -Wall -pedantic -g3

GCC_LIBS = -lglfw3 -framework AppKit -framework OpenGL -framework IOKit -framework CoreVideo -DGLEW_STATIC

#GCC_LIBS = -framework Carbon -framework OpenGL -framework GLUT
SRC_NAME = main.c gl_funcs.c events_scop.c ft_strings.c

OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_NAME = glfw/src libvec

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LIB = $(addprefix -L$(LIB_PATH),$(LIB_NAME))

all: $(NAME)

$(NAME): $(OBJ)
		make -C $(LIB_PATH)libvec -j
		$(CC) $(GCC_FLGS) $(LIB) $(INC) $(OBJ) $(GCC_LIBS) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		mkdir -p $(OBJ_PATH)
		$(CC) $(GCC_FLGS) $(INC) -o $@ -c $<

clean:
		rm -fv $(OBJ)
		rm -rf $(OBJ_PATH)

fclean: clean
		make -C $(LIB_PATH)libvec fclean
		rm -fv $(NAME)

re: fclean all
