# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
# export LD_LIBRARY_PATH

SRCF := ./src
INCF := ./inc
OUTF := ./out
UNITF := ./unit_tests
PYF := ./py

CC := gcc -I $(INCF)
CFLAGS := -std=c99 -Wall -Werror -Wpedantic
CHECK_FLAGS := -lpthread -lrt -lcheck -lm

# SRCS := $(wildcard $(SRCF)/*.c)
SRCS := $(SRCF)/arr.c
OBJS := $(SRCS:$(SRCF)/%.c=$(OUTF)/%.o)

UNIT_SRCS := $(wildcard $(UNITF)/*.c)
UNIT_OBJS := $(UNIT_SRCS:$(UNITF)/%.c=$(OUTF)/%.o)
UNIT_LIB_OBJS := $(UNIT_OBJS:$(OUTF)/check_main.o=$(nullstring))


# на моем пк добавляем библиотеку
ifeq ($(pc), my)
	CHECK_FLAGS +=  -lsubunit
endif


app : libarr.so
	python3 $(PYF)/setup.py build_ext --inplace
	python3 $(PYF)/main.py


# динамическая компоновка
./unit_tests.exe : $(OUTF)/check_main.o libunit.so
	$(CC) $(CFLAGS) -o $@ $^ $(CHECK_FLAGS) -lm

libarr.so : CFLAGS += -fPIC
libarr.so : $(OBJS)
	$(CC) -o $@ -shared $^

$(OUTF)/%.o : $(SRCF)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTF)/%.d : $(SRCF)/%.c
	$(CC) -MM $< > $@

include $(SRCS:$(SRCF)/%.c=$(OUTF)/%.d)

libunit.so : CFLAGS += -fPIC
libunit.so : $(UNIT_LIB_OBJS) libarr.so
	$(CC) -o $@ -shared $^

$(OUTF)/%.o : $(UNITF)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTF)/%.d : $(UNITF)/%.c
	$(CC) -MM $< > $@

include $(UNIT_SRCS:$(UNITF)/%.c=$(OUTF)/%.d)



.PHONY : clean valgrind unit design design_clean

clean : 
	$(RM) -r ./build $(PYF)/__pycache__
	$(RM) *.exe *.so out/*

unit : 
	echo $(CFLAGS)
	make clean
	@echo ''
	make ./unit_tests.exe
	@echo ''
	./unit_tests.exe

valgrind : CFLAGS += -g3
valgrind : ./unit_tests.exe
	valgrind -q --leak-check=yes ./unit_tests.exe


# Генерация скриптов на питоне описывающих интерфейс
DESIGN_UI := $(wildcard $(PYF)/*.ui)
DESIGN_PY := $(DESIGN_UI:$(PYF)/%.ui=$(PYF)/%.py)

$(PYF)/%.py : $(PYF)/%.ui
	pyuic5 $< -o $@

design: $(DESIGN_PY)
	@echo "design done!"

design_clean :
	$(RM) $(DESIGN_PY)
# 





