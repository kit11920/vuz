OUTF := ./out
SRCF := ./src
INCF := ./inc
UNITF := ./unit_tests

CC := gcc -I $(INCF)

CFLAGS := --std=c99 -Wall -Werror -Wpedantic -Wextra
SRCS := $(wildcard $(SRCF)/*.c)
OBJS := $(OUTF)/associative_array_impl_1.o $(OUTF)/impl_1_plus.o

CHECK_FLAGS :=  -lcheck -lpthread -lrt -lm
UNIT_SRCS := $(wildcard $(UNITF)/*.c)
CHECK_OBJS := $(UNIT_SRCS:$(UNITF)/%.c=$(OUTF)/%.o)
CHECK_OBJS += $(OUTF)/associative_array_impl_1.o $(OUTF)/impl_1_plus.o


# на моем пк добавляем библиотеку
ifeq ($(pc), my)
	CHECK_FLAGS +=  -lsubunit
endif

# Создание символических ссылок
PATH_CHECK_H := ../lab_10_03_common/unit_tests/inc
PATH_CHECK_C := ../lab_10_03_common/unit_tests/src
FCHECK_H := $(wildcard $(PATH_CHECK_H)/*.h)
FCHECK_C := $(wildcard $(PATH_CHECK_C)/*.c)
NEED_LINK_H := $(FCHECK_H:$(PATH_CHECK_H)/%.h=$(INCF)/%.h)
NEED_LINK_C := $(FCHECK_C:$(PATH_CHECK_C)/%.c=$(UNITF)/%.c)
ALL_NEED_LINKS := $(NEED_LINK_C) $(NEED_LINK_H)

$(INCF)/%.h : $(PATH_CHECK_H)/%.h
	$(RM) $@
	ln -s ../$< $@

$(UNITF)/%.c : $(PATH_CHECK_C)/%.c
	$(RM) $@
	ln -s ../$< $@
## 


$(OUTF)/%.o : $(SRCF)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTF)/%.d : $(SRCF)/%.c
	$(CC) -MM $< > $@

include $(SRCS:$(SRCF)/%.c=$(OUTF)/%.d)
 
unit_tests.exe : CFLAGS += -g3
unit_tests.exe : $(CHECK_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(CHECK_FLAGS)

$(OUTF)/%.o : $(UNITF)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OUTF)/%.d : $(UNITF)/%.c 
	$(CC) -MM $< > $@

include $(UNIT_SRCS:$(UNITF)/%.c=$(OUTF)/%.d)


.PHONY : clean valgrind unit valgrind_unit links

links: $(ALL_NEED_LINKS)
	@echo made .h: $(NEED_LINK_H)
	@echo made .c: $(NEED_LINK_C)

clean_links : 
	$(RM) $(ALL_NEED_LINKS)

clean :
	$(RM) *.exe out/*

unit : 
	echo $(CFLAGS)
	@echo CHECK_OBJS: $(CHECK_OBJS)
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



