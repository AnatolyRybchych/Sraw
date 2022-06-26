
out		:= Sraw.exe

objects	:= obj/glad.o
objects	+= obj/main.o
objects	+= obj/Window.o
objects	+= obj/MainWindow.o
objects	+= obj/MainWindowState.o
objects	+= obj/MonitorInfo.o
objects	+= obj/GlobalWindowInput.o
objects	+= obj/App.o
objects	+= obj/DrawingCanvas.o
objects	+= obj/ShaderProgram.o
objects	+= obj/Texture.o
objects	+= obj/Framebuffer.o
objects	+= obj/DrawImage.o
objects	+= obj/MouseHighlight.o
objects	+= obj/DrawingTool.o
objects	+= obj/MouseHighlightTool.o
objects	+= obj/SelectToolTool.o
objects	+= obj/SelectToolNode.o
objects	+= obj/SelectMenuToolNode.o
objects	+= obj/SelectActionToolNode.o
objects	+= obj/SelectToolMenuManager.o
objects	+= obj/ResourceProvider.o

build:$(objects)
	g++ -g -ggdb -Istbimage -Iglad/ -o $(out) $^ -lgdi32 -lopengl32

obj/%.o:src/%.cpp
	g++ -g -ggdb -Istbimage -Iglad/ -c -o $@ $<

obj/glad.o: glad/glad.c
	gcc -Istbimage -Iglad/ -c -o $@ $<

run:build
	./$(out)

gdb:build
	gdb ./$(out)