
out		:= Sraw.exe
objects	:= obj/main.o
objects	+= obj/Window.o
objects	+= obj/MainWindow.o
objects	+= obj/MainWindowState.o
objects	+= obj/MonitorInfo.o
objects	+= obj/glad.o
objects	+= obj/GlobalWindowInput.o
objects	+= obj/App.o

build:$(objects)
	g++ -Iglad/ -o $(out) $^ -lgdi32 -lopengl32

obj/%.o:src/%.cpp
	g++ -Iglad/ -c -o $@ $<

obj/glad.o: glad/glad.c
	gcc -Iglad/ -c -o $@ $<

run:build
	./$(out)