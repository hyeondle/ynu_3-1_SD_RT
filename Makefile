NAME	=	rt

MLX_DIR	=	./minilibx/
MLX		=	$(MLX_DIR)libmlx.a

CC		=	c++
FLAGS	=	-Wall -Wextra -Werror -std=c++98
LIBS	=	-L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
INCD	=	-I ./ -I ./minilibx

SOURCE	=	mlxBase.cpp main.cpp
OBJECT	=	$(SOURCE:.cpp=.o)

.cpp.o:
	$(CC) $(FLAGS) $(INCD) -c $< -o $(<:.cpp=.o)

all: $(NAME)

$(MLX):
	make -C $(MLX_DIR)

$(NAME): $(OBJECT) $(MLX)
	$(CC) $(FLAGS) $(INCD) $(OBJECT) $(LIBS) -o $(NAME)

clean:
	rm -rf $(OBJECT)

fclean: clean
	rm -rf $(NAME)
	make -C $(MLX_DIR) clean
