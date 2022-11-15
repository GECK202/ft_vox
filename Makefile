.PHONY: all, clean, fclean, re

PROGRAM_NAME = ft_vox

FLAGS =	 -std=c++11 -pthread -Wall -Wextra #-Werror -g

FILES =		ft_vox \
			window \
			events \
			shader \
			texture \
			png_loading \
			camera \
			mesh \
			chunk \
			chunks \
			chunks_controller \
			voxel_renderer \
			files \
			lightmap \
			light_solver \
			lighting \
			block \
			world_files \
			player \
			hitbox \
			physics_solver \
			chunks_loader \
			world_generator \
			cubemap \
			assets \
			

S_DIR =		src

O_DIR =		obj

T_DIR = 	world

H_DIR =		include

O_FILES =	$(addprefix $(O_DIR)/, $(addsuffix .o, $(FILES)))

H_FILE =	$(H_DIR)/declarations.h $(H_DIR)/world_render.h $(H_DIR)/voxel.h

H_FILES =	$(addprefix $(H_DIR)/, $(addsuffix .h, $(FILES))) $(H_FILE)

LIBS =		-L./libs/glfw -lglfw3 \
			-L./libs/glad/ -lglad \
			-L /usr/local/Cellar/libpng/1.6.37/lib/ -lpng \

H_FIND =	-I ./include \
			-I ./libs/glfw \
			-I ./libs/glad \
			-I /usr/local/Cellar/libpng/1.6.37/include \
			-I ~/.brew/Cellar/glm/0.9.9.8/include \

FRAME =		-framework Cocoa -framework OpenGL -framework IOKit \

all: $(PROGRAM_NAME)

$(PROGRAM_NAME): $(O_FILES)
	g++ $(FLAGS) -o $@ $^ $(LIBS) $(FRAME)

$(O_DIR)/%.o: $(S_DIR)/%.cpp $(H_FILES)
	@mkdir -p $(O_DIR)
	@mkdir -p $(T_DIR)
	g++ $(FLAGS) -c $< -o $@ $(H_FIND)

clean:
	@rm -rf $(O_DIR)
	@rm -rf $(T_DIR)

fclean : clean
	rm -f $(PROGRAM_NAME)

re: fclean all
