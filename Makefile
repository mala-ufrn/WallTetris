vpath %.c src
vpath %.cpp src
vpath %.h include

LDFLAGS = `pkg-config --static --libs freetype2 glfw3 gl`
FREETYPE_CFLAGS = `pkg-config --cflags freetype2`

utils = shader.h text_render.h stb_image.h
objects = bin/glad.o bin/image_render.o bin/main.o bin/text_render.o

game: $(objects)
	g++ $(objects) -o game $(LDFLAGS)
bin/glad.o: glad.c
	gcc -c src/glad.c -o bin/glad.o
bin/image_render.o: image_render.h image_render.cpp
	g++ -c src/image_render.cpp -o bin/image_render.o
bin/main.o: $(utils) main.cpp
	g++ -c src/main.cpp -o bin/main.o
bin/text_render.o: text_render.h text_render.cpp
	g++ -c src/text_render.cpp -o bin/text_render.o $(FREETYPE_CFLAGS)
clean:
	rm game $(objects)