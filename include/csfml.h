/*
** EPITECH PROJECT, 2023
** Libmy
** File description:
** Store libmy functions prototypes
*/


#ifndef CSFML_H
    #define CSFML_H

    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/Audio.h>
    #include <stdbool.h>
    #include <malloc.h>
    #include <stdlib.h>
    #include <time.h>
    #include "mylist.h"
    #include <unistd.h>
    #include <fcntl.h>
    #include <math.h>

enum status {
    SUCCESS,
    FAILURE,
    CONTINUE,
};

enum scene {
    MAIN,
    FREE_ALL,
};

typedef struct shape {
    sfIntRect rect;
    sfVector2f position;
    int radius;
    sfCircleShape *circle;
    sfRectangleShape *rectangle;
} shape_t;

typedef struct {
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f origin;
    sfText *text;
    sfVector2f position;
    sfVector2f scale;
    sfIntRect rect;
    shape_t *hitbox;
    shape_t *circle;
    sfSound *sound;
    char *id;
} sprite_t;

typedef struct {
    sfVector2f position;
    sfVector2f direction;
    sfIntRect area;
    sfSprite *sprite;
    sfClock *clock;
    sfSound *hit_sound;
    sfSound *miss_sound;
    sfSound *end_window;
    int one_bird_hit;
    int life;
} npc_t;

typedef struct {
    char const *str;
    sfFont *font;

    char const *police;
    sfColor color;
    int size;

    sfColor outline_color;
    float outline_size;

    sfTextStyle style;

    sfVector2f scale;
    sfVector2f position;
} text_t;

typedef struct {
    sfVideoMode video_mode;
    sfRenderWindow *my_window;
    sfSprite *background_sprite;
    sfTexture *background_texture;
    sfClock *clock;
    sfEvent event;
    float resize;
    int f;
    float delay;
} window_info_t;

typedef struct corner {
    sfIntRect rect;
    unsigned int nb_circles;
    nodes_t *circles;
} corner_t;

typedef struct tower {
    sfVector2f position;
    float radius;
    float area;
    int start_w;
    int end_w;
    int start_h;
    int end_h;
} tower_t;

typedef struct quadtree {
    sfVector2f pos;
    sfVector2f size;
    nodes_t *planes_in_quadrant;
    int planes_count;
    int tower_count;

    struct quadtree *nw;
    struct quadtree *ne;
    struct quadtree *sw;
    struct quadtree *se;
} quadtree_t;

typedef struct plane {
    sfIntRect rect;
    sfIntRect old_rect;
    sfVector2f position;
    sfVector2f final_pos;
    int altitude;
    float pixels;
    sfVector2f speed;
    float angle;
    float delay;
    int land;
    int destroyed;
    int safe_zone;
    int go_by_endw;
    int go_by_startw;
    int go_by_endh;
    int go_by_starth;
    sfVector2f scale;

} plane_t;

typedef struct file {
    struct stat *s;
    char *buffer;
    char **script;
    sprite_t *plane;
    sprite_t *tower;
    long long int nb_planes;
    long long int nb_towers;
    nodes_t *planes_info;
    nodes_t *tower_info;
}file_t;

typedef struct variables {
    int hitbox;
    int sprite;
    int move;
    int speeduser;
    int quad_treeview;
    sfVector2f scale;
} user_variables_t;

typedef struct {
    window_info_t *info_window;
    sfVector2i mouse_pos;
    file_t *file;
    sfText *time;
    sfText *speed_t;
    sfText *altitude;
    sfText *scaletxt;
    sfClock *clock_time;
    user_variables_t *user_variables;
    quadtree_t *quadtree;
    int state;
    shape_t *quad;
    int old_state;
} game_info_t;

int my_radar(int ac, char **av);
int error_handling(int ac, char **av, game_info_t *game_info, struct stat *s);
void analyse_events(game_info_t *game_info);


/////Init Game Info

//Menu
void init_window(game_info_t *game_info);
//File
int init_file(game_info_t *game_info);

int init_game_info(game_info_t *game_info);
int init_variables(game_info_t *game_info);
int init_time(game_info_t *game_info);
int init_speedtext(game_info_t *game_info);
int init_altitudetxt(game_info_t *game_info);
int init_scaletxt(game_info_t *game_info);

////


//Init sprite
sprite_t *init_sprite(sfTexture *, char *text, sfVector2f pos, sfIntRect area);

//Sound creation
sfSound *init_sound(char const *filename);
sfMusic *init_music(char const *filename);

//Text creation
sfText *init_text(text_t info_text);

//Init Shape
shape_t *init_circle(sfVector2f position, float radius, sfColor color);
sfRectangleShape *init_rectangle(sfVector2f position, sfVector2f size,
    sfColor color, int outline);

//Check script
int init_script(game_info_t *game_info, char **av);
int get_info_script(file_t *file);

//Info plane
float get_angle(sfVector2f pos, sfVector2f final_pos);
void get_speed(plane_t *plane, sfVector2f final_pos, sfVector2f position);
int next_info_plane(file_t *file, plane_t *plane, int i, int *len_nbr);
void draw_plane_decalage(plane_t *plane, int decalage, game_info_t *game_info);
void show_alternative(game_info_t *game_info, plane_t *plane);
plane_t *get_plane(file_t *file, int i);
sprite_t *init_plane(game_info_t *game_info);

void show_hitbox_plane(game_info_t *game_info, plane_t *tmp, sfVector2f);
//void move_plane(int speeduser, int delay, sfSprite *sprite, nodes_t *tmp);
int show_plane(game_info_t *game_info);
int get_pos(int decalage, sfVector2f *pos);
int check_euclidian(plane_t *plane, tower_t *tower, int decalage);
void check_safe_zone(plane_t *plane,
    nodes_t **tower_list);

//Info tower
void set_and_show_tower(tower_t *tower, game_info_t *game_info);
void set_and_show_tower_area(tower_t *tower, game_info_t *game_info);
void show_tower(game_info_t *game_info);
tower_t *get_tower(file_t *file, int i);
sprite_t *init_tower(game_info_t *game_info);


int my_cmpland_void(void *data, void *data2);
quadtree_t *init_quadtree(sfVector2f pos, sfVector2f size);
void insert_plane_in_quadtree(quadtree_t *root, nodes_t *tmp,
    game_info_t *game_info);
void get_nw(quadtree_t *root, sfVector2f mid_root);
void get_ne(quadtree_t *root, sfVector2f mid_root);
void get_sw(quadtree_t *root, sfVector2f mid_root);
void get_se(quadtree_t *root, sfVector2f mid_root);
int split_quadtree(quadtree_t *root, sfVector2f);
void collide_plane(nodes_t **plane_list);
void check_collision_quadtree(quadtree_t *quadtree, game_info_t *);
void free_quadtree_recursively(quadtree_t *root);
void push_in(quadtree_t *root, nodes_t *tmp, game_info_t *game_info);
int check_recursively(quadtree_t *root, game_info_t *game_info);

int insert_nw(quadtree_t *root, nodes_t *tmp,
    sfVector2f, game_info_t *game_info);
int insert_ne(quadtree_t *root, nodes_t *tmp,
    sfVector2f, game_info_t *game_info);
int insert_sw(quadtree_t *root, nodes_t *tmp,
    sfVector2f, game_info_t *game_info);
int insert_se(quadtree_t *root, nodes_t *tmp,
    sfVector2f, game_info_t *game_info);

void draw_everything(game_info_t *game_info);
void show_quadtree(quadtree_t *root, game_info_t *game_info);
int show_time(sfRenderWindow *, sfClock *, sfText *, int speed);
int show_speed(sfText *text, int speed_user, sfRenderWindow *window);
int show_altitude(game_info_t *game_info, plane_t *plane,
    sfVector2i mouse_pos, sfVector2f);
int show_scale(sfRenderWindow *, sfText *, sfVector2f scale);
int check_end(nodes_t **list);
int free_all(game_info_t *game_info);
float euclidean_distance(sfVector2f pos_1, sfVector2f pos_2);
#endif //CSFML_H
