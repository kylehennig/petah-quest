testfile: testdraw.c draw.c hud.c
	gcc testdraw.c draw.c hud.c -l ncurses -o testfile -Wall

run: testfile
	./testfile

clean: testfile
	@rm -f testfile
