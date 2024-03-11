
#include "select_act.h"


void init_action_data(action_data_t &act_data)
{
    act_data.act = NO;
}

void set_action_to_load(action_data_t &act_data, const char *filename)
{
    act_data.act = LOAD;
    act_data.filename = filename;
}

void set_action_to_draw(action_data_t &act_data, draw_data_t &draw_data)
{
    act_data.act = DRAW;
    act_data.draw_data = draw_data;
}

void set_action_to_scale(action_data_t &act_data, scale_data_t scale_data)
{
    act_data.act = SCALE;
    act_data.scale_data = scale_data;
}

void set_action_to_rotate(action_data_t &act_data, rotate_data_t &rotate_data)
{
    act_data.act = ROTATE;
    act_data.rotate_data = rotate_data;
}

void set_action_to_shift(action_data_t &act_data, shift_data_t &shift_data)
{
    act_data.act = SHIFT;
    act_data.shift_data = shift_data;
}

void set_action_to_quit(action_data_t &act_data)
{
    act_data.act = QUIT;
}

err_t do_action(action_data_t &act_data)
{
    static figure_t figure = start_init_figure();
    
    Actions act = act_data.act;
    if (act == NO)
        return ERR_ACT_NO;

    err_t rc = OK;
    switch (act)
    {
        case LOAD:
            rc = load_figure(&figure, act_data.filename);
            break;
        case DRAW:
            rc = draw_figure(figure, act_data.draw_data);
            break;
        case SCALE:
            rc = scale_figure(figure, act_data.scale_data);
            break;
        case ROTATE:
            rc = rotate_figure(figure, act_data.rotate_data);
            break;
        case SHIFT:
            rc = shift_figure(figure, act_data.shift_data);
            break;
        case QUIT:
            free_data_figure(figure);
            break;
        default:
            rc = ERR_UNKNOWN;
    }

    return rc;
}

