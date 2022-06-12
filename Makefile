

out		:= Sraw.exe
objects	:= obj/main.o

build:$(objects)
	g++ -o $(out) $^

obj/%.o:src/%.cpp
	g++ -c -o $@ $<

run:build
	./$(out)