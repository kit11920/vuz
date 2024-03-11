#pragma once

#include "figure.h"

enum Actions {
    DRAW,
    LOAD,
    SCALE,
    ROTATE,
    SHIFT,
    QUIT,
    NO
};

typedef struct action_data_s action_data_t;
struct action_data_s
{
    Actions act;
    union
    {
        const char *filename;
        shift_data_t shift_data;
        rotate_data_t rotate_data;
        scale_data_t scale_data;
        draw_data_t draw_data;
    };
};

void init_action_data(action_data_t &act_data);

void set_action_to_load(action_data_t &act_data, const char *filename);

void set_action_to_draw(action_data_t &act_data, draw_data_t &draw_data);

void set_action_to_scale(action_data_t &act_data, scale_data_t scale_data);

void set_action_to_rotate(action_data_t &act_data, rotate_data_t &rotate_data);

void set_action_to_shift(action_data_t &act_data, shift_data_t &shift_data);

void set_action_to_quit(action_data_t &act_data);

err_t do_action(action_data_t &act_data);
