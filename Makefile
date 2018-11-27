vpath %.c src
vpath %.cpp src
vpath %.h include
vpath %.o bin

LDFLAGS = `pkg-config --static --libs freetype2 glfw3 gl`
FREETYPE_CFLAGS = `pkg-config --cflags freetype2`

OBJECTS = bin/glad.o bin/image_render.o bin/main.o bin/text_render.o \
          bin/main_menu.o

game: $(OBJECTS)
	g++ $(OBJECTS) -o game $(LDFLAGS)
bin/glad.o: glad.c
	gcc -c src/glad.c -o bin/glad.o
bin/image_render.o: shader.h image_render.h image_render.cpp
	g++ -c src/image_render.cpp -o bin/image_render.o
bin/main.o: $(UTILS) game.h scene_master.h main.cpp
	g++ -c src/main.cpp -o bin/main.o
bin/main_menu.o: shader.h scene.h image_render.o text_render.o main_menu.h \
                 main_menu.cpp
	g++ -c src/main_menu.cpp -o bin/main_menu.o
bin/text_render.o: shader.h text_render.h text_render.cpp
	g++ -c src/text_render.cpp -o bin/text_render.o $(FREETYPE_CFLAGS)
clean:
	rm game $(OBJECTS)