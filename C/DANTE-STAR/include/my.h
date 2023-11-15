/*
** EPITECH PROJECT, 2021
** my.h
** File description:
** my.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <fcntl.h>

#ifndef MY_H_
#define MY_H_

typedef struct info {
    int l;
    int h;
} info_t;

typedef struct pos_player {
    int x;
    int y;
} pp_t;

struct parcours_t {
    int x;
    int y;
    struct parcours_t *previous;
    struct parcours_t *next;
};

void my_putchar(char c);

void my_putstr(char *str);

void my_putstr_error(char *str);

int my_strlen(char const *str);

int my_strcmp(char const *str1, char const *str2);

int my_getnbr(char *nbr);

void my_putnbr(int nb);

char *func_buffer(char *filepath);

char *my_revstr(char *str);

int my_puttab(char **tab);

char **generate(char **map, info_t pos);

int generate_numb(int min, int max);

int generate_numb_2(int min, int max);

char **my_str_to_word_array(char *str);

int generate_numb(int min, int max);

int generate_numb_2(int min, int max);

int verify_finished(char **map, info_t pos);

int check_direction_outside_map(char **, int direction, info_t pos, pp_t pp);

char **change_map(char **map, int direction, info_t pos, pp_t pp);

int verif_num(char *str);

int check_arround(char **map, int direction, info_t pos, pp_t pp);

int check_direction(char **map, int direction, info_t pos, pp_t pp);

int check_error(int ac, char **av);

struct parcours_t *create_par(int x, int y, struct parcours_t *previous, struct  parcours_t *next);

char **load_2d_array_from_file(char *filepath);

info_t know_info(char **map);

int finish(int **map, info_t info);

int got_a_dir(int type);

int new_direction(int **map_int, pp_t my_pos, info_t info, int type);

int i_cant_move_anymore(int **map_int, pp_t my_pos, info_t pos);

int **update_direction(int **map_int, pp_t my_pos, int poid, int direction);

pp_t update_my_pos(pp_t my_pos, int direction);

int know_type(int **map_int, info_t pos);

void check_no_solutions(int poid);

int **made_my_algo(int **map_int, info_t pos);

pp_t know_my_direction(int **map_int, pp_t my_pos, info_t pos);

#endif /* !MY_H_ */
