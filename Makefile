CC = gcc
CFLAGS = -Wall  -g -pg
LIB_NAME = libeln.a
TARGET =  eln.o


all: $(LIB_NAME)

$(LIB_NAME): $(TARGET)
	ar rcs $(LIB_NAME) $(TARGET)
	rm $(TARGET)

$(TARGET): eln.c eln.h
	$(CC) $(CFLAGS) -c eln.c

clean:
	rm -f $(TARGET) $(LIB_NAME)

