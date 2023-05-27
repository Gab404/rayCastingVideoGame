SRC =   ./src/main.c \
        ./src/display.c \
        ./src/free.c \
        ./src/game.c \
        ./src/getNumNpc.c \
        ./src/gun.c \
        ./src/handleError.c \
        ./src/loadMap.c \
        ./src/opps.c \
        ./src/pauseMenu.c \
        ./src/player.c \
        ./src/quickSort.c \
        ./src/raycasting.c \
        ./src/loadTexture.c \

OBJ    =    $(SRC:.c=.o)

NAME   =    raycasting

CFLAGS += -Wall -Wextra

CPPFLAGS    +=  -I./includes

LIBS += -lm -lalleg44 -lmingw32 -lwinmm

all:    $(NAME)

$(NAME): $(OBJ)
    gcc -o $(NAME) $(OBJ) $(LIBS)

clean:
    rm -f $(OBJ)

fclean: clean
    rm -f $(NAME)

re: fclean all

.PHONY: clean
    fclean
    re