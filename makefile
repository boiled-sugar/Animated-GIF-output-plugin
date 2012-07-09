CC = gcc
CFLAG = -c -O3 -std=c99 -Wall -fopenmp -D_LIB -D_MT -I/usr/local/include/ImageMagick
# MagickWand-config --cflags
LINK = gcc
LFLAG = --shared -L/usr/local/lib -Wl,--enable-stdcall-fixup,--dll -s

TARGET = animationgif.auo
OBJ1 = animationgif.o
DEF  = animationgif.def

all: $(TARGET)

$(TARGET): $(OBJ1) $(DEF)
	$(LINK) $(LFLAG) -o $(TARGET) $(OBJ1) -lMagickWand -lMagickCore -lz -lgdi32 -lgomp -lpthread $(DEF)

$(OBJ1): animationgif.c
	$(CC) $(CFLAG) animationgif.c

clean:
	rm -f *.o
	rm -f *.auo
