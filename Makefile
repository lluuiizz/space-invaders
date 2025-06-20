CC = gcc
CFLAGS = -Werror -Wall -Wextra -pedantic
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
TARGET = space_invaders
SRCS = space_invaders.c player.c bullet.c enemy.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

space_invaders.o: space_invaders.c 
player.o: player.c  
bullet.o: bullet.c 
enemy.o: enemy.c   

run: $(TARGET)
	./$(TARGET)
	rm -rf *.o

clean:
	rm -f $(OBJS) $(TARGET)
val:
	valgrind --leak-check=yes ./space_invaders
.PHONY: all clean run
