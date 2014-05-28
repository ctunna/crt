TARGET=crt
MODULES=crt.o vector.o 
LIBS=-lm
CFLAGS=-Wall -Wextra -std=c99

$(TARGET): $(MODULES)
	gcc $(MODULES) $(CFLAGS) $(LIBS) -o $(TARGET)

clean:
	rm *.o $(TARGET)

all: clean $(TARGET)

conv:
	convert out.ppm q.bmp

vector.o: vector.c vector.h

crt.o: crt.c
