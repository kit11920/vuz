FSRC := ./src
FINC := ./inc
FOUT := ./out

CC := gcc -I $(FINC) 
CFLAGS := --std=c99 -Wall -Werror -Wpedantic -Wextra -g3

OBJS := $(FOUT)/main.o $(FOUT)/errs.o $(FOUT)/arr.o $(FOUT)/time_system.o $(FOUT)/list.o $(FOUT)/free_adresses_arr.o $(FOUT)/efficiency.o $(FOUT)/fort.o
SRCS := $(wildcard $(FSRC)/*.c)

app.exe : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(FOUT)/%.o : $(FSRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(FOUT)/%.d : $(FSRC)/%.c
	$(CC) -MM $< > $@

include $(SRCS:$(FSRC)/%.c=$(FOUT)/%.d)


.PHONY : clean valgrind

clean :
	$(RM) *.exe $(FOUT)/*

valgrind : app.exe
	valgrind --leak-check=yes -q ./app.exe

