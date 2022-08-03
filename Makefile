

LIB_INCLUDE_PATH	:= -I.\include -I.\include\freetype2
LIB_BIN_PATH		:= -L.\dlls
LIBS				:= -lMsimg32 -lgdi32 -lopengl32 -lglew32 -lfreetype -lComdlg32 -lGdiplus


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
objects	+= obj/Basics.o
objects	+= obj/CutBmpWindow.o
objects	+= obj/SelectMenuToolNode.o
objects	+= obj/SelectActionToolNode.o
objects	+= obj/DrawDiagramBgProgram.o
objects	+= obj/RectRenderer.o
objects	+= obj/Coords.o

objects	+= obj/Texture.o
objects	+= obj/Framebuffer.o

objects	+= obj/SelectToolTool.o
objects	+= obj/SelectToolNode.o
objects	+= obj/BrushTool.o
objects	+= obj/EraserTool.o
objects	+= obj/TextTool.o
objects	+= obj/ColorPaletTool.o
objects	+= obj/MouseHighlightTool.o
objects	+= obj/BlockDiagramTool.o
objects	+= obj/ActionBlockDiagramTool.o
objects	+= obj/ConditionBlockDiagramTool.o
objects	+= obj/StartEndBlockDiagramTool.o
objects	+= obj/InOutBlockDiagramTool.o
objects	+= obj/FuncBlockDiagramTool.o
objects	+= obj/SelectionTool.o
objects	+= obj/PrimitiveTool.o
objects	+= obj/LineTool.o

build_exe:$(objects)
	g++ -mwindows $(LIB_INCLUDE_PATH) -o bin/$(out) $^ $(LIB_BIN_PATH) $(LIBS)

obj/%.o:src/%.cpp
	@mkdir -p obj
	g++ $(LIB_INCLUDE_PATH) -c -o $@ $<

obj/%.o:src/GlWrappers/%.cpp
	@mkdir -p obj
	g++ $(LIB_INCLUDE_PATH) -c -o $@ $<

obj/%.o:src/Tools/%.cpp
	@mkdir -p obj
	g++ $(LIB_INCLUDE_PATH) -c -o $@ $<

#output dir
bin_dir:
	mkdir -p bin

dlls: bin_dir
	cp dlls/* bin/

fonts: bin_dir
	mkdir -p bin/fonts
	cp fonts/* bin/fonts/
	
images: bin_dir
	mkdir -p bin/images
	cp images/* bin/images/

shaders: bin_dir
	mkdir -p bin/shaders
	cp shaders/* bin/shaders/

build: bin_dir build_exe dlls fonts images shaders
#output dir end

run:build
	cd ./bin ; ./$(out)
