exec = pixelux.out
sources = $(wildcard src/*.c)
objects = $(sources: .c = .o)
flags = -g -Wall -lm -ldl -fPIC -rdynamic

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec) -lm

%.o: %.c headers/%.h
	gcc -c $(flags) $< -o $@

clean:
	-rm *.out
	#-rm *.o
	#-rm *.a
	#-rm src/*.o

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c src/%.h
	gcc -c $(flags) $< -o $@

clean:
	-rm *.out
	-rm *.o
	-rm *.a
	-rm src/*.o

lint:
	clang-tidy src/*.c src/headers/*.h
