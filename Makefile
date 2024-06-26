NAME	=	rt

MLX_DIR	=	./minilibx/
MLX		=	$(MLX_DIR)libmlx.a

CC		=	c++
# FLAGS	=	-Wall -Wextra -Werror -std=c++11
FLAGS	=	-std=c++11
LIBS	=	-L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
INCD	=	-I ./include -I ./minilibx

SOURCE	=	src/main.cpp\
			src/def/MlxBase.cpp\
			src/def/Color.cpp\
			src/def/Vector.cpp\
			src/def/Ray.cpp\
			src/def/Camera.cpp\
			src/def/HitRecord.cpp\
			src/def/HitList.cpp\
			src/def/Interval.cpp\
			src/def/AABB.cpp\
			src/def/BVH.cpp\
			src/def/Material.cpp\
			src/def/Phong.cpp\
			src/def/Light.cpp\
			src/def/Sphere.cpp\
			src/def/Plane.cpp\
			src/def/Cylinder.cpp\


OBJECT	=	$(SOURCE:.cpp=.o)\

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

re : fclean all

run : all
	./$(NAME)
