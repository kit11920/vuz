OUTF := ./out
SRCF := ./src
INCF := ./inc

CC := gcc -I $(INCF)
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra

OBJS := $(OUTF)/main.o $(OUTF)/mtrx.o $(OUTF)/errs.o $(OUTF)/in_output.o $(OUTF)/operations.o $(OUTF)/actions.o $(OUTF)/efficieny.o $(OUTF)/check.o 
SRCS := $(wildcard $(SRCF)/*.c)

app.exe : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(OUTF)/%.o : $(SRCF)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTF)/%.d : $(SRCF)/%.c
	$(CC) -MM $< > $@

include $(SRCS:$(SRCF)/%.c=$(OUTF)/%.d)

.PHONY : clean valgrind 

valgrind : CFLAGS += -g3
valgrind : app.exe 
	valgrind -q --leak-check=yes --undef-value-errors=yes --track-origins=yes ./app.exe

clean :
	$(RM) $(OUTF)/* *.exe


test : app.exe
	./app.exe < tmp.txt

