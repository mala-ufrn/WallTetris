vpath %.c src
vpath %.cpp src
vpath %.h include

LDFLAGS = `pkg-config --static --libs freetype2 glfw3 gl`
FREETYPE_CFLAGS = `pkg-config --cflags freetype2`

OBJECTS = bin/glad.o bin/image_render.o bin/main.o bin/text_render.o \
          bin/main_menu.o bin/endless_mode.o bin/credits.o

game: $(OBJECTS)
	g++ $(OBJECTS) -o game $(LDFLAGS)
bin/endless_mode.o: scene.h endless_mode.h endless_mode.cpp
	g++ -c src/endless_mode.cpp -o bin/endless_mode.o
bin/credits.o: scene.h credits.h credits.cpp
	g++ -c src/credits.cpp -o bin/credits.o
bin/glad.o: glad.c
	gcc -c src/glad.c -o bin/glad.o
bin/image_render.o: image_render.h image_render.cpp
	g++ -c src/image_render.cpp -o bin/image_render.o
bin/main.o: $(UTILS) game.h scene_master.h main.cpp
	g++ -c src/main.cpp -o bin/main.o
bin/main_menu.o: scene.h main_menu.h main_menu.cpp
	g++ -c src/main_menu.cpp -o bin/main_menu.o
bin/text_render.o: text_render.h text_render.cpp
	g++ -c src/text_render.cpp -o bin/text_render.o $(FREETYPE_CFLAGS)
clean:
	rm game $(OBJECTS)