
pquest: bin/main.o bin/net.o bin/controller.o
	gcc $^ -o pquest -lncurses

bin/%.o: src/%.c | bin
	gcc $< -o $@ -lncurses -c

bin:
	mkdir bin

.PHONY: clean

clean:
	rm -r bin || true
	rm pquest || true
