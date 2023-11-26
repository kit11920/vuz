INCF := ./inc
SRCF := ./src
OUTF := ./out
GRAPHF := ./graph

CC := gcc -I $(INCF)
CFLAGS := -Wall -Werror -Wpedantic -Wextra
SRCS := $(wildcard $(SRCF)/*.c)
OBJS := $(SRCS:$(SRCF)/%.c=$(OUTF)/%.o)

./app.exe : $(OBJS)
	@echo $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(OUTF)/%.o : $(SRCF)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTF)/%.d : $(SRCF)/%.c
	$(CC) -MM $< > $@

include $(SRCS:$(SRCF)/%.c=$(OUTF)/%.d)



.PHONY : clean valgrind graph

clean : 
	$(RM) *.exe $(OUTF)/*

valgrind : CFLAGS += -g3
valgrind : ./app.exe
	valgrind --leak-check=yes -q ./app.exe

GV := $(wildcard $(GRAPHF)/*.gv)
PNG := $(GV:$(GRAPHF)/%.gv=$(GRAPHF)/%.png)

$(GRAPHF)/%.png : $(GRAPHF)/%.gv
	dot -Tpng $< -o $@

graph : $(PNG)
	@echo $(PNG)

clean_graph :
	$(RM) $(GRAPHF)/*


