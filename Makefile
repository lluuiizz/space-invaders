CC = gcc
CFLAGS = -Werror -Wall -Wextra -pedantic
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
TARGET = space_invaders
SRCS = space_invaders.c player.c bullet.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

space_invaders.o: space_invaders.c 
player.o: player.c 
bullet.o: bullet.c 

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean run
