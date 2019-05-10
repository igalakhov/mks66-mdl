all: main.o drawer.o display.o edge_matrix.o transformation_matrix.o mdl_parser.o obj_parser.o parametric.o 3d.o unit_matrix.o triangle_matrix.o point_matrix.o vector_utils.o coordinate_stack.o lighting.o settings.o
	g++ -std=c++11 -o main.out main.o drawer.o display.o edge_matrix.o transformation_matrix.o mdl_parser.o obj_parser.o parametric.o 3d.o unit_matrix.o triangle_matrix.o point_matrix.o vector_utils.o coordinate_stack.o lighting.o settings.o
	./main.out

main.o: main.cpp settings.h
	g++ -std=c++11 -c main.cpp

drawer.o: drawing/drawer.cpp drawing/drawer.h settings.h
	g++ -std=c++11 -c drawing/drawer.cpp

display.o: drawing/display.cpp drawing/display.h settings.h
	g++ -std=c++11 -c drawing/display.cpp

unit_matrix.o: matrix/unit_matrix.cpp matrix/unit_matrix.h
	g++ -std=c++11 -c matrix/unit_matrix.cpp

point_matrix.o: matrix/point_matrix.cpp matrix/point_matrix.h
	g++ -std=c++11 -c matrix/point_matrix.cpp

edge_matrix.o: matrix/edge_matrix.cpp matrix/edge_matrix.h matrix/transformation_matrix.h settings.h
	g++ -std=c++11 -c matrix/edge_matrix.cpp

triangle_matrix.o: matrix/triangle_matrix.cpp matrix/triangle_matrix.h
	g++ -std=c++11 -c matrix/triangle_matrix.cpp

transformation_matrix.o: matrix/transformation_matrix.cpp matrix/transformation_matrix.h matrix/edge_matrix.h settings.h
	g++ -std=c++11 -c matrix/transformation_matrix.cpp

mdl_parser.o: parsing/mdl/mdl_parser.cpp matrix/transformation_matrix.h matrix/edge_matrix.h drawing/drawer.h settings.h
	g++ -std=c++11 -c parsing/mdl/mdl_parser.cpp

coordinate_stack.o: parsing/mdl/coordinate_stack.cpp parsing/mdl/coordinate_stack.h
	g++ -std=c++11 -c parsing/mdl/coordinate_stack.cpp

obj_parser.o: parsing/obj_parser.h matrix/edge_matrix.h settings.h
	g++ -std=c++11 -c parsing/obj_parser.cpp

parametric.o: drawing/parametric/parametric.h settings.h
	g++ -std=c++11 -c drawing/parametric/parametric.cpp

3d.o: drawing/3d/3d.cpp
	g++ -std=c++11 -c drawing/3d/3d.cpp

vector_utils.o: matrix/utils/vector_utils.cpp matrix/utils/vector_utils.h
	g++ -std=c++11 -c matrix/utils/vector_utils.cpp

lighting.o: drawing/lighting/lighting.cpp drawing/lighting/lighting.h
	g++ -std=c++11 -c drawing/lighting/lighting.cpp

settings.o: settings.cpp settings.h
	g++ -std=c++11 -c settings.cpp
clean:
	touch fakefile.o
	touch fakefile.h.gch
	touch main.out
	rm *.o
	rm main.out
	rm *.h.gch
