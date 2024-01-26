OUTF := ./out
SRCF := ./src
INCF := ./inc
UNITF := ./unit_tests

CC := gcc -I $(INCF)
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra

SRCS := $(wildcard $(SRCF)/*.c)
OBJS := $(SRCS:$(SRCF)/%.c=$(OUTF)/%.o)

CHECK_FLAGS :=  -lcheck -lpthread -lrt -lm
UNIT_SRCS := $(wildcard $(UNITF)/*.c)
CHECK_OBJS := $(UNIT_SRCS:$(UNITF)/%.c=$(OUTF)/%.o)
CHECK_OBJS += $(OBJS)


# на моем пк добавляем библиотеку
ifeq ($(pc), my)
	CHECK_FLAGS +=  -lsubunit
endif

unit_tests.exe : CFLAGS += -g3
unit_tests.exe : $(CHECK_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(CHECK_FLAGS)

$(OUTF)/%.o : $(UNITF)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OUTF)/%.d : $(UNITF)/%.c 
	$(CC) -MM $< > $@

include $(UNIT_SRCS:$(UNITF)/%.c=$(OUTF)/%.d)

$(OUTF)/%.o : $(SRCF)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OUTF)/%.d : $(SRCF)/%.c 
	$(CC) -MM $< > $@

include $(SRCS:$(SRCF)/%.c=$(OUTF)/%.d)


.PHONY : clean unit valgrind_unit 

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



# Функциональное тестирование со всеми санитайзерами:
asan : CFLAGS += -g3 -fsanitize=address -fno-omit-frame-pointer 
asan : unit_tests.exe
	@echo "CC = " $(CC) "CFLAGS = " $(CFLAGS)

msan : CFLAGS += -g3 -fsanitize=memory -fPIE -fno-omit-frame-pointer -fsanitize-memory-track-origins
msan : CC := clang -I inc
msan : unit_tests.exe
	@echo "CC = " $(CC) "CFLAGS = " $(CFLAGS)

ubsan : CFLAGS += -g3 -fsanitize=undefined -fno-omit-frame-pointer
ubsan : unit_tests.exe
	@echo "CC = " $(CC) "CFLAGS = " $(CFLAGS)

san : unit_tests.exe
	make clean
	make asan
	@echo ''
	@echo 'Address sanitizer'
	@./unit_tests.exe
	@echo ''

	make clean
	make msan
	@echo ''
	@echo 'Memory sanitizer'
	@./unit_tests.exe
	@echo ''

	make clean
	make ubsan
	@echo ''
	@echo 'Undefined behavior sanitizer'
	@./unit_tests.exe
	@echo ''

	make clean
#

















