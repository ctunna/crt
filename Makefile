TARGET=crt
MODULES=crt.o vector.o 
LIBS=-lm
CFLAGS=-Wall -Wextra -std=c99

$(TARGET): $(MODULES)
	gcc $(MODULES) $(CFLAGS) $(LIBS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) && convert out.ppm out.bmp && open out.bmp

clean:
	rm *.o $(TARGET)

all: clean $(TARGET)

conv:
	convert out.ppm out.png

vector.o: vector.c vector.h

crt.o: crt.c
