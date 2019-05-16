BUILD_FOLDER=build
OBJECTS=$(BUILD_FOLDER)/main.o $(BUILD_FOLDER)/drawer.o $(BUILD_FOLDER)/display.o $(BUILD_FOLDER)/edge_matrix.o \
	$(BUILD_FOLDER)/transformation_matrix.o $(BUILD_FOLDER)/mdl_parser.o $(BUILD_FOLDER)/obj_parser.o \
	$(BUILD_FOLDER)/parametric.o $(BUILD_FOLDER)/3d.o $(BUILD_FOLDER)/unit_matrix.o $(BUILD_FOLDER)/triangle_matrix.o \
	$(BUILD_FOLDER)/point_matrix.o $(BUILD_FOLDER)/vector_utils.o $(BUILD_FOLDER)/coordinate_stack.o $(BUILD_FOLDER)/lighting.o \
	$(BUILD_FOLDER)/settings.o $(BUILD_FOLDER)/symbol_table.o $(BUILD_FOLDER)/parser.o


all: prepare $(BUILD_FOLDER)/bison_parser.o $(BUILD_FOLDER)/flex_lexer.o $(OBJECTS)
	g++ -o mdl.out $(OBJECTS) $(BUILD_FOLDER)/bison_parser.o $(BUILD_FOLDER)/flex_lexer.o -ll
	clear
	./mdl.out script.mdl

prepare:
	mkdir -p build

# flex and yacc stuff

$(BUILD_FOLDER)/bison_parser.o: compiler/mdl.yy
	bison -b $(BUILD_FOLDER)/mdl -d -v compiler/mdl.yy
	g++ -c -o $(BUILD_FOLDER)/bison_parser.o $(BUILD_FOLDER)/mdl.tab.cc

$(BUILD_FOLDER)/flex_lexer.o: compiler/mdl.l
	flex -o $(BUILD_FOLDER)/lex.yy.cc -I compiler/mdl.l
	g++ -o $(BUILD_FOLDER)/flex_lexer.o -c $(BUILD_FOLDER)/lex.yy.cc

# objects
$(BUILD_FOLDER)/main.o: main.cpp settings.h
	g++ -std=c++11 -o $(BUILD_FOLDER)/main.o -c main.cpp

$(BUILD_FOLDER)/drawer.o: drawing/drawer.cpp drawing/drawer.h settings.h
	g++ -std=c++11 -o $(BUILD_FOLDER)/drawer.o -c drawing/drawer.cpp

$(BUILD_FOLDER)/display.o: drawing/display.cpp drawing/display.h settings.h
	g++ -std=c++11 -o $(BUILD_FOLDER)/display.o -c drawing/display.cpp

$(BUILD_FOLDER)/unit_matrix.o: matrix/unit_matrix.cpp matrix/unit_matrix.h
	g++ -std=c++11 -o $(BUILD_FOLDER)/unit_matrix.o -c matrix/unit_matrix.cpp

$(BUILD_FOLDER)/point_matrix.o: matrix/point_matrix.cpp matrix/point_matrix.h
	g++ -std=c++11 -o $(BUILD_FOLDER)/point_matrix.o -c matrix/point_matrix.cpp

$(BUILD_FOLDER)/edge_matrix.o: matrix/edge_matrix.cpp matrix/edge_matrix.h matrix/transformation_matrix.h settings.h
	g++ -std=c++11 -o $(BUILD_FOLDER)/edge_matrix.o -c matrix/edge_matrix.cpp

$(BUILD_FOLDER)/triangle_matrix.o: matrix/triangle_matrix.cpp matrix/triangle_matrix.h
	g++ -std=c++11 -o $(BUILD_FOLDER)/triangle_matrix.o -c matrix/triangle_matrix.cpp

$(BUILD_FOLDER)/transformation_matrix.o: matrix/transformation_matrix.cpp matrix/transformation_matrix.h matrix/edge_matrix.h settings.h
	g++ -std=c++11 -o $(BUILD_FOLDER)/transformation_matrix.o -c matrix/transformation_matrix.cpp

$(BUILD_FOLDER)/mdl_parser.o: parsing/mdl/mdl_parser.cpp matrix/transformation_matrix.h matrix/edge_matrix.h drawing/drawer.h settings.h
	g++ -std=c++11 -o $(BUILD_FOLDER)/mdl_parser.o -c parsing/mdl/mdl_parser.cpp

$(BUILD_FOLDER)/coordinate_stack.o: parsing/mdl/coordinate_stack.cpp parsing/mdl/coordinate_stack.h
	g++ -std=c++11 -o $(BUILD_FOLDER)/coordinate_stack.o -c parsing/mdl/coordinate_stack.cpp

$(BUILD_FOLDER)/obj_parser.o: parsing/obj_parser.h matrix/edge_matrix.h settings.h
	g++ -std=c++11 -o $(BUILD_FOLDER)/obj_parser.o -c parsing/obj_parser.cpp

$(BUILD_FOLDER)/parametric.o: drawing/parametric/parametric.h settings.h
	g++ -std=c++11 -o $(BUILD_FOLDER)/parametric.o -c drawing/parametric/parametric.cpp

$(BUILD_FOLDER)/3d.o: drawing/3d/3d.cpp
	g++ -std=c++11 -o $(BUILD_FOLDER)/3d.o -c drawing/3d/3d.cpp

$(BUILD_FOLDER)/vector_utils.o: matrix/utils/vector_utils.cpp matrix/utils/vector_utils.h
	g++ -std=c++11 -o $(BUILD_FOLDER)/vector_utils.o -c matrix/utils/vector_utils.cpp

$(BUILD_FOLDER)/lighting.o: drawing/lighting/lighting.cpp drawing/lighting/lighting.h
	g++ -std=c++11 -o $(BUILD_FOLDER)/lighting.o -c drawing/lighting/lighting.cpp

$(BUILD_FOLDER)/settings.o: settings.cpp settings.h
	g++ -std=c++11 -o $(BUILD_FOLDER)/settings.o -c settings.cpp

$(BUILD_FOLDER)/symbol_table.o: compiler/symbol_table.cpp settings.h
	g++ -std=c++11 -o $(BUILD_FOLDER)/symbol_table.o -c compiler/symbol_table.cpp

$(BUILD_FOLDER)/parser.o: compiler/parser.cpp settings.h
	g++ -std=c++11 -o $(BUILD_FOLDER)/parser.o -c compiler/parser.cpp

remake-build:
	rm -rf build/
	mkdir build
	make
