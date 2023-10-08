#ifndef COUNTRY_STRUCT_H__
#define COUNTRY_STRUCT_H__


#include <stdbool.h>

#define NAME_LEN 30
#define CAPITAL_LEN 30
#define CONTINENT_LEN 30
#define TYPE_SIGHTS_LEN 30
#define SEASON_LEN 30
#define SPORT_LEN 30

#define TABLE_LEN 100
#define BIG_TABLE_LEN 15000

typedef enum type_tourism_enum { EXCURSION_TOURISM = 0, BEACH_TOURISM = 1, SPORT_TOURISM = 2 } type_tourism_t;

struct excursion_tourism_t
{
    int count_sights;
    char type_sights[TYPE_SIGHTS_LEN + 1];
};


struct beach_tourism_t
{
    char season[SEASON_LEN + 1];
    int air_tempr;
    int water_tempr;
};


struct country_t
{
    size_t ind;
    char name[NAME_LEN + 1];
    char capital[CAPITAL_LEN + 1];
    char continent[CONTINENT_LEN + 1];
    bool visa;
    int time;
    int cost_min;
    type_tourism_t type_tourism;
    union tourism_t {
        struct excursion_tourism_t excursion_tourism;
        struct beach_tourism_t beach_tourism;
        char sport_type[SPORT_LEN + 1];
    } tourism;

};


struct key_table_t
{
    size_t ind_orig;
    int time;
};



#endif
