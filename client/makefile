
pquest: bin/main.o bin/net.o bin/controller.o bin/draw.o bin/hud.o
	gcc $^ -o pquest -lncurses

bin/%.o: src/%.c | bin
	gcc $< -o $@ -lncurses -c

bin:
	mkdir bin

.PHONY: clean

clean:
	rm -r bin || true
	rm pquest || true
