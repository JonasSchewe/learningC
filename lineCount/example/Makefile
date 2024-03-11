ccFlags= -Wall -fsanitize=address -fsanitize=leak -fsanitize=undefined

.SILENT: run linecount clean
.phony: clean

run: linecount
	./build/linecount ../..

linecount:	linecount.c
	mkdir -p build
	cd build/
	gcc -g linecount.c -o build/linecount

clean:
	rm -rf build/