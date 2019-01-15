CC      = gcc
SDL_FLAGS = -I/usr/include/SDL2 -D_REENTRANT
CFLAGS  = -I. -Wall -Wextra -g3 $(SDL_FLAGS)
LDFLAGS  = -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_image -lSDL2_ttf

RM      = rm -f
TARGET  = bomberman

SRC 	= 	src/main.c \
			src/bomberman.c

OBJ = $(SRC:.c=.o)

.PHONY: all $(TARGET) clean fclean re

all : $(TARGET)

$(TARGET): $(OBJ) 
	@echo "LD	$@"
	@$(CC) $(OBJ) -o $@ $(LDFLAGS) 

src/%.o : src/%.c
	@echo "CC	$<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(TARGET)

re : fclean all
