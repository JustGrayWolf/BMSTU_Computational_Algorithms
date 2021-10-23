OUTDIR := ./out/
FLAGS :=  -std=c99 -Wall -Werror -c
CC := gcc

app.exe : $(OUTDIR)functions.o $(OUTDIR)main.o
	$(CC) -o $@ $^

$(OUTDIR)functions.o : functions.c $(OUTDIR)
	$(CC) $(FLAGS) $^ -o $@

$(OUTDIR)main.o : main.c $(OUTDIR)
	$(CC) $(FLAGS) $< -o $@
	
$(OUTDIR) :
	mkdir $(OUTDIR)
.PHONY : clean
clean :
	rm $(OUTDIR)*.o *.exe