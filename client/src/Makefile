testfile: testdraw.c draw.c
	gcc testdraw.c draw.c -l ncurses -o testfile -Wall

run: testfile
	./testfile

clean: testfile
	@rm -f testfile
