CC      = gcc
SDL_FLAGS = -I/usr/include/SDL2 -D_REENTRANT
CFLAGS  = -I. -Wall -Wextra -g3 $(SDL_FLAGS)
LDFLAGS =

ifeq ($(shell uname), Linux)
	LDFLAGS  += -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_image -lSDL2_ttf
endif

ifeq ($(shell uname), Darwin)
	#LDFLAGS += -lSDL2 -lSDL2_Image -framework SDL2_ttf
	#LDFLAGS += -lSDL2_Image
	LDFLAGS += -framework SDL2 -framework SDL2_Image
endif


RM      = rm -f
TARGET  = bomberman

SRC 	= 	\
			main.c game.c
			#mainTest.c
			#src/main.c \
			#src/bomberman.c

OBJ = $(SRC:.c=.o)

.PHONY: all $(TARGET) clean fclean re

all : $(TARGET)

$(TARGET): $(OBJ) 
	@echo "LD	$@"
	@$(CC) $(OBJ) -o $@ $(LDFLAGS) 

src/%.o : src/%.c
	@echo "CC	$<"
	@$(CC) $(CFLAGS) -c $< -o $@

coffee: all clean

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(TARGET)

re : fclean all
