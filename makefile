CC = gcc
CFLAG = -c -O3 -std=c99 -Wall -I/usr/local/include/ImageMagick
LINK = gcc
LFLAG = --shared -L/usr/local/lib -Wl,--enable-stdcall-fixup,--dll -s

TARGET = animationgif.auo
OBJ1 = animationgif.o
DEF  = animationgif.def

all: $(TARGET)

$(TARGET): $(OBJ1) $(DEF)
	$(LINK) $(LFLAG) -o $(TARGET) $(OBJ1) -lMagickWand -lMagickCore -lz -lgdi32 $(DEF)
#-lMagickCore -lbz2 -lz -lgdi32 -lm -lgomp -lpthread
$(OBJ1): animationgif.c
	$(CC) $(CFLAG) animationgif.c

clean:
	rm -f *.o
	rm -f *.auo
