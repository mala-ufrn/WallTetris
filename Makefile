vpath %.c ./src:./src/utils
vpath %.cpp ./src:./src/models:./src/rendering:./src/scenes:./src/utils
vpath %.h ./include:./include/models:./include/rendering:./include/scenes:\
          ./include/utils

LDFLAGS = `pkg-config --static --libs freetype2 glfw3 gl`
FREETYPE_CFLAGS = `pkg-config --cflags freetype2`
INCLUDE_PATH = -I./include

OBJECTS = bin/glad.o bin/image_render.o bin/main.o bin/text_render.o \
          bin/main_menu.o bin/endless_mode.o bin/credits.o

game: $(OBJECTS)
	g++ $(OBJECTS) -o game $(LDFLAGS)
bin/endless_mode.o: scene.h game_master.h endless_mode.h endless_mode.cpp
	g++ -c src/scenes/endless_mode.cpp -o bin/endless_mode.o $(INCLUDE_PATH)
bin/credits.o: scene.h credits.h credits.cpp
	g++ -c src/scenes/credits.cpp -o bin/credits.o $(INCLUDE_PATH)
bin/glad.o: glad.c
	gcc -c src/utils/glad.c -o bin/glad.o
bin/image_render.o: image_render.h image_render.cpp
	g++ -c src/rendering/image_render.cpp -o bin/image_render.o $(INCLUDE_PATH)
bin/main.o: $(UTILS) game.h scene_master.h main.cpp
	g++ -c src/main.cpp -o bin/main.o $(INCLUDE_PATH)
bin/main_menu.o: scene.h main_menu.h main_menu.cpp
	g++ -c src/scenes/main_menu.cpp -o bin/main_menu.o $(INCLUDE_PATH)
bin/text_render.o: text_render.h text_render.cpp
	g++ -c src/rendering/text_render.cpp -o bin/text_render.o $(INCLUDE_PATH) \
	$(FREETYPE_CFLAGS)
clean:
	rm game $(OBJECTS)