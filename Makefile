CC = gcc
CFLAGS = -Wall  -g -pg
LIB_NAME = libGGN.a
TARGET = GGN_lib.o


all: $(LIB_NAME)

$(LIB_NAME): $(TARGET)
	ar rcs $(LIB_NAME) $(TARGET)
	rm $(TARGET)

$(TARGET): GGN_lib.c GGN_lib.h
	$(CC) $(CFLAGS) -c GGN_lib.c

clean:
	rm -f $(TARGET) $(LIB_NAME)

