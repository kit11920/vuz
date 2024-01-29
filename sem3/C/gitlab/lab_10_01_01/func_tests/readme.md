# Тесты lab_10_01_01

## Входные данные
./app.exe filein fileout [ДЕЙСТВИЕ]

## Выходные данные
Файл

## Позитивные тесты
- 01 Выводит данные из файла (без действий)

### -i country_name filecountry
- 02 Искомой страны нет
- 03 Искомых стран несколько
- 04 В списке 1 элемент и он подходит (Вставляет элемент в начало)
- 05 Вставляет элемент в середину
- 06 Вставляет элемент перед последним элементом в файле

### -s
- 07 В списке несколько элементов в рандомном порядке без повторов
- 08 В списке несколько элементов в рандомном порядке с повторами
- 09 В списке элементы расположены по возрастанию
- 10 В списке элементы расположены по убыванию
- 11 В списке 2 элемента расположены по возрастанию
- 12 В списке 2 элемента расположены по убыванию
- 13 В списке 1 элемент

### -d 
- 14 В списке нет повтором
- 15 В списке 1 повтор
- 16 В списке все элементы одинаковые
- 17 В списке 1 элемент


## Негативные тесты



### Ввод-вывод:
- 01 Неверные аргументы конадной строки
- 02 Нет аргументов командной строки
- 03 Нет файла с данными изначальными
- 04 Файл с изначальными данными пуст
- 05 Файл с изначальными данными заполнен неверно

### -i country_name filecountry
- 05 Нет файла с данными которые надо ставить
- 06 Ошибка в файле с данными которые надо ставить





