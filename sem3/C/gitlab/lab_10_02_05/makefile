SRCF := ./src
INCF := ./inc
OUTF := ./out
UNITF := ./unit_tests

CC := gcc -I $(INCF)

CFLAGS := --std=c99 -Wall -Werror -Wpedantic -Wextra
# OBJS := $(OUTF)/main.o $(OUTF)/node_list.o $(OUTF)/list.o
SRCS := $(wildcard $(SRCF)/*.c)
OBJS := $(SRCS:$(SRCF)/%.c=$(OUTF)/%.o)

CHECK_FLAGS :=  -lcheck -lpthread -lrt -lm
UNIT_SRCS := $(wildcard $(UNITF)/*.c)
CHECK_OBJS := $(UNIT_SRCS:$(UNITF)/%.c=$(OUTF)/%.o)
CHECK_OBJS += $(OUTF)/node_list.o $(OUTF)/list.o $(OUTF)/str_list.o
# CHECK_OBJS := $(OUTF)/node_list.o $(OUTF)/list.o $(OUTF)/check_main.o $(OUTF)/help_check.o 
# CHECK_OBJS += $(OUTF)/check_search_string.o $(OUTF)/check_del_2spaces.o

# на моем пк добавляем библиотеку
ifeq ($(pc), my)
	CHECK_FLAGS +=  -lsubunit
endif

./app.exe : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OUTF)/%.o : $(SRCF)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTF)/%.d : $(SRCF)/%.c
	$(CC) -MM $< > $@

include $(SRCS:$(SRCF)/%.c=$(OUTF)/%.d)


unit_tests.exe : CFLAGS += -g3
unit_tests.exe : $(CHECK_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(CHECK_FLAGS)

out/%.o : $(UNITF)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@ 

out/%.d : $(UNITF)/%.c 
	$(CC) -MM $< > $@

include $(UNIT_SRCS:$(UNITF)/%.c=out/%.d)


.PHONY : clean valgrind unit valgrind_unit func release debug asan msan ubsan gcov_app gcov

clean :
	$(RM) *.exe out/*

valgrind : CFLAGS += -g3
valgrind : app.exe
	valgrind --leak-check=yes -q ./app.exe tmp/data.txt tmp/out.txt -d

unit : 
	echo $(CFLAGS)
	make clean
	@echo ''
	make unit_tests.exe
	@echo ''
	./unit_tests.exe

valgrind_unit : CFLAGS += -g3
valgrind_unit : 
	echo $(CFLAGS)
	make clean
	@echo ''
	make unit_tests.exe
	@echo ''
	valgrind -q --leak-check=yes --undef-value-errors=yes --track-origins=yes ./unit_tests.exe

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

	make clean
#


gcov_app : CFLAGS += -fprofile-arcs -ftest-coverage -g3
gcov_app : app.exe 

gcov : 
	make clean
	make gcov_app
	@echo ''
	./collect_coverage.sh


















