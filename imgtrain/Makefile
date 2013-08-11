
CFLAGS=-g -Wall -I/usr/include -I/usr/include/opencv2
LDFLAGS=-lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_photo -lopencv_objdetect
CXX=g++


all: veridt symdraw

veridt: main.o funcs.o
	$(CXX) -o $@ $< $(LDFLAGS)


symdraw: symdraw.o
	$(CXX) -o $@ $< $(LDFLAGS)

.cpp.o:
	$(CXX) $(CFLAGS) -c $^

clean:
	rm -vf *.o veridt

