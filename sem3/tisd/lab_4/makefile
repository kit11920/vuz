OUTF := ./out
SRCF := ./src
INCF := ./inc 

CC := gcc -I $(INCF)
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -g3

OBJS := $(OUTF)/main.o $(OUTF)/errs.o $(OUTF)/static_stack.o $(OUTF)/work_stack.o $(OUTF)/list_stack.o $(OUTF)/efficiency.o $(OUTF)/fort.o
SRCS := $(wildcard $(SRCF)/*.c)

app.exe : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(OUTF)/%.o : $(SRCF)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OUTF)/%.d : $(SRCF)/%.c 
	$(CC) -MM $< > $@ 

include $(SRCS:$(SRCF)/%.c=$(OUTF)/%.d)

.PHONY : clean valgrind

clean :
	$(RM) *.exe $(OUTF)/*


valgrind : ./app.exe
	valgrind --leak-check=yes --undef-value-errors=yes --track-origins=yes -q ./app.exe
