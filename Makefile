

LIB_INCLUDE_PATH	:= -IC:\include -IC:\include\freetype2
LIB_BIN_PATH		:= -LC:\bin
LIBS				:= -lgdi32 -lopengl32 -lglew32 -lfreetype

out		:= Sraw.exe

objects	+= obj/main.o
objects	+= obj/Window.o
objects	+= obj/MainWindow.o
objects	+= obj/MainWindowState.o
objects	+= obj/MonitorInfo.o
objects	+= obj/GlobalWindowInput.o
objects	+= obj/App.o
objects	+= obj/DrawingCanvas.o
objects	+= obj/ShaderProgram.o
objects	+= obj/DrawImage.o
objects	+= obj/MouseHighlight.o
objects	+= obj/DrawingTool.o
objects	+= obj/SelectToolMenuManager.o
objects	+= obj/ResourceProvider.o
objects	+= obj/RenderText.o
objects	+= obj/FreeType.o

objects	+= obj/Texture.o
objects	+= obj/Framebuffer.o

objects	+= obj/SelectToolTool.o
objects	+= obj/SelectToolNode.o
objects	+= obj/BrushTool.o
objects	+= obj/EraserTool.o
objects	+= obj/ColorPaletTool.o
objects	+= obj/MouseHighlightTool.o
objects	+= obj/SelectMenuToolNode.o
objects	+= obj/SelectActionToolNode.o

build:$(objects)
	g++ -g -ggdb $(LIB_INCLUDE_PATH) -o $(out) $^ $(LIB_BIN_PATH) $(LIBS)

obj/%.o:src/%.cpp
	g++ -g -ggdb $(LIB_INCLUDE_PATH) -c -o $@ $<

obj/%.o:src/GlWrappers/%.cpp
	g++ -g -ggdb $(LIB_INCLUDE_PATH) -c -o $@ $<

obj/%.o:src/Tools/%.cpp
	g++ -g -ggdb $(LIB_INCLUDE_PATH) -c -o $@ $<

obj/glad.o: glad/glad.c
	gcc $(LIB_INCLUDE_PATH) -c -o $@ $<

run:build
	./$(out)

gdb:build
	gdb ./$(out)