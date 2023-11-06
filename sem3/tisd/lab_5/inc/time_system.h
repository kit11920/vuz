#ifndef TIME_H__
#define TIME_H__

#define CHANGE_T1_MIN 1
#define CHANGE_T1_MAX 2
#define CHANGE_T2_MIN 3
#define CHANGE_T2_MAX 4
#define CHANGE_T3_MIN 5
#define CHANGE_T3_MAX 6
#define CHANGE_T4_MIN 7
#define CHANGE_T4_MAX 8

#define EPS 1e-6

typedef struct struct_time_params
{
    double t1_min;
    double t1_max;

    double t2_min;
    double t2_max;

    double t3_min;
    double t3_max;

    double t4_min;
    double t4_max;
    
} time_params_t;


/// @brief Инициализирует параметры времени в системе
/// @param tp - параметры времени в системе (указатель на структуру)
void init_time_params(time_params_t *tp);

void print_time_params(time_params_t *tp);

int change_time_params(time_params_t *tp);

/// @brief Возвращает интервал времени поступления заявки типа 1
/// @param tp - параметры времени в системе (указатель на структуру)
/// @return интервал времени поступления заявки типа 1
double receive_time_1(time_params_t *tp);

/// @brief Возвращает интервал времени поступления заявки типа 2
/// @param tp - параметры времени в системе (указатель на структуру)
/// @return интервал времени поступления заявки типа 2
double receive_time_2(time_params_t *tp);

/// @brief Возвращает время обработки заявки типа 1
/// @param tp - параметры времени в системе (указатель на структуру)
/// @return время обработки заявки типа 1
double process_time_1(time_params_t *tp);

/// @brief Возвращает время обработки заявки типа 2
/// @param tp - параметры времени в системе (указатель на структуру)
/// @return время обработки заявки типа 2
double process_time_2(time_params_t *tp);

void print_mid_koef();

#endif
