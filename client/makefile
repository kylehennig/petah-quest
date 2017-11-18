
pquest: bin/main.o bin/net.o
	gcc $? -o pquest -lncurses

bin/%.o: src/%.c | bin
	gcc $< -o $@ -lncurses -c

bin:
	mkdir bin
