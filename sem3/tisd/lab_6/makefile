INCF := ./inc
SRCF := ./src
OUTF := ./out

CC := gcc -I $(INCF)
CFLAGS := -Wall -Werror -Wpedantic -Wextra
SRCS := $(wildcard $(SRCF)/*.c)
OBJS := $(SRCS:$(SRCF)/%.c=$(OUTF)/%.o)

./app.exe : $(OBJS)
	@echo $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OUTF)/%.o : $(SRCF)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTF)/%.d : $(SRCF)/%.c
	$(CC) -MM $< > $@

include $(SRCS:$(SRCF)/%.c=$(OUTF)/%.d)



.PHONY : clean valgrind

clean : 
	$(RM) *.exe $(OUTF)/*

valgrind : CFLAGS += -g3
valgrind : ./app.exe
	valgrind --leak-check=yes -q ./app.exe




