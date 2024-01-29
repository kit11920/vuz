# Компилятор
CC := gcc -I ./inc 

# Опции компилятора 
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra

# библиотеки check
CHECK_FLAGS :=  -lcheck -lpthread -lrt -lm

# Общие обьектные файл
OBJS := out/main.o out/input_output.o out/array.o

CHECK_OBJS := out/array.o out/check_main.o out/check_key.o out/check_mysort.o out/check_cmp.o out/check_swap.o

# Все СИ файлы
SRCS := $(wildcard src/*.c)

# на моем пк добавляем библиотеку
ifeq ($(pc), my)
	CHECK_FLAGS +=  -lsubunit
endif


app.exe : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

out/%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

out/%.d : src/%.c
	$(CC) -MM $< > $@

include $(SRCS:src/%.c=out/%.d)



UNIT_SRCS := $(wildcard unit_tests/*.c)

unit_tests.exe : CFLAGS += -g3
unit_tests.exe : $(CHECK_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(CHECK_FLAGS)

out/%.o : unit_tests/%.c 
	$(CC) $(CFLAGS) -c $< -o $@ 

out/%.d : unit_tests/%.c 
	$(CC) -MM $< > $@

include $(UNIT_SRCS:unit_tests/%.c=out/%.d)


data_graphic.exe : out/array.o out/data_graphic.o 
	$(CC) $(CFLAGS) $^ -o $@ -lm

out/data_graphic.o : data_time/data_graphic.c inc/array.h
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY : clean release debug asan msan ubsan func  unit graphic gcov gcov_app
clean : 
	$(RM) out/* *.exe


unit : 
	echo $(CFLAGS)
	make clean
	@echo ''
	make unit_tests.exe
	@echo ''
	./unit_tests.exe


graphic : 
	make clean 
	@echo ''
	make data_graphic.exe
	./data_graphic.exe
	@echo ''
	./make_graphic.sh
	@echo ''
	@echo 'Рисунок графика лежит в папке ./data_time'



release : CFLAGS += -DNDEBUG -g0
release : app.exe

debug : CFLAGS += -g3
debug : app.exe
	@echo "CC = " $(CC) "CFLAGS = " $(CFLAGS)

# Функциональное тестирование со всеми санитайзерами:
asan : CFLAGS += -g3 -fsanitize=address -fno-omit-frame-pointer
asan : app.exe
	@echo "CC = " $(CC) "CFLAGS = " $(CFLAGS)

msan : CFLAGS += -g3 -fsanitize=memory -fPIE -fno-omit-frame-pointer
msan : CC := clang -I inc
msan : app.exe
	@echo "CC = " $(CC) "CFLAGS = " $(CFLAGS)

ubsan : CFLAGS += -g3 -fsanitize=undefined -fno-omit-frame-pointer
ubsan : app.exe
	@echo "CC = " $(CC) "CFLAGS = " $(CFLAGS)

func : 
	make clean
	make debug
	@echo ''
	@echo 'Without sanitizers'
	@./func_tests/scripts/func_tests.sh
	@echo ''

	make clean
	make asan
	@echo ''
	@echo 'Address sanitizer'
	@./func_tests/scripts/func_tests.sh
	@echo ''

	make clean
	make msan
	@echo ''
	@echo 'Memory sanitizer'
	@./func_tests/scripts/func_tests.sh
	@echo ''

	make clean
	make ubsan
	@echo ''
	@echo 'Undefined behavior sanitizer'
	@./func_tests/scripts/func_tests.sh
	@echo ''

	make clean
	make debug
	@echo ''
	@echo 'Use valgrind'
	@./func_tests/scripts/func_tests.sh -vg
	@echo ''
#


gcov_app : CFLAGS += -fprofile-arcs -ftest-coverage -g3
gcov_app : app.exe 

gcov : 
	make clean
	make gcov_app
	@echo ''
	./collect_coverage.sh


