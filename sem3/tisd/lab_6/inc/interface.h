#ifndef INTERFACE_H__
#define INTERFACE_H__

#define INTRANCE "\
Программа производит работу бинарным деревом поиска и\n\
деревом выражения A + (B * (C + (D * (E + F) - (G - H)) + I))\n\n"

#define ACT_BIN_SEARCH_TREE 1
#define ACT_EFFICIENCY 2
#define ACT_EXP_TREE 3
#define ACT_EXIT 0

#define WHAT_DO "\
Возможности программы:\n\
1 - Работать со своим бинарным деревом поиска\n\
2 - Эффективность функций создания и поиска в бинарном дереве поиска\n\
3 - Работать с деревом выражения\n\
0 - Завершить программу\n\
\n\
Введите номер действия, которого хотите совершить: "

#define WORK_ADD 1
#define WORK_DEL 2
#define WORK_FIND 3
#define WORK_SHOW 4
#define WORK_CLEAR 5
#define WORK_END 0

#define WORK_BIN_SEARCH_TREE "\
Действия с бинарным деревом поиска целых чисел:\n\
1 - Добавить узел\n\
2 - Удалить узел по содержимому\n\
3 - Найти элемент по содержимому\n\
4 - Показать дерево\n\
5 - Очистить дерево\n\
0 - Завершить работу\n\
\n\
Введите номер действия, которого хотите совершить: "



#endif