##
## EPITECH PROJECT, 2023
## my_printf
## File description:
## The main Makefile of our project
##

CFLAGS = -I./include -Werror -Wpedantic -Wextra
CFLAGS += -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio
CFLAGS += -g -g3 -lm
LFLAGS = -L./lib -lmy -llist
TEST_FLAGS = --coverage -lcriterion -lgcov

SRC	=	src/main.c
SRC += src/do_plane_bis.c
SRC += src/plane_in_tower_area_euclidian.c
SRC += src/tower_area_pos.c
SRC += src/tower_pos.c
SRC += src/draw_everything.c
SRC += src/show_scale.c
SRC += src/free_all.c
SRC += src/show_altitude.c
SRC += src/show_speed.c
SRC += src/init_game_info_2.c
SRC += src/show_time.c
SRC += src/init_game_info.c
SRC += src/insert_se.c
SRC += src/insert_sw.c
SRC += src/insert_ne.c
SRC += src/insert_nw.c
SRC += src/quadtree.c
SRC += src/plane_in_tower_area.c
SRC += src/my_radar.c
SRC += src/my_cmpland_void.c
SRC += src/init_sprite.c
SRC += src/init_script.c
SRC += src/init_quadrants.c
SRC += src/init_circleshape.c
SRC += src/get_plane.c
SRC += src/do_tower.c
SRC += src/do_plane.c
SRC += src/collision_quadtree.c
SRC += src/analyse_events.c

OBJ	=	$(SRC:.c=.o)

NAME = my_radar

all: libmy liblist test

libmy:
	make -C ./lib/my/

liblist:
	make -C ./lib/list/

test: $(OBJ)
	@gcc $(SRC) -o $(NAME) -g3 $(CFLAGS) $(LFLAGS)

valgrind: $(OBJ)
	@gcc $(SRC) -g3 $(CFLAGS) $(LFLAGS)
	@valgrind -s ./$(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

clean_lib:
	@make fclean -C./lib/my/
	@make fclean -C./lib/list/
	@make fclean -C./tests/

re:	clean_lib fclean all

unit_tests: re
	make unit_tests -C ./tests/

tests_run: re
	make -C ./tests/
	@gcovr
