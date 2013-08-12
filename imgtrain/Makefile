
CFLAGS=-g -O2 -Wall -I/usr/include -I/usr/include/opencv2
LDFLAGS=-lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_photo -lopencv_objdetect -lopencv_video
#CXX=g++
CXX=clang++


all: veridt symdraw

veridt: main.o funcs.o
	$(CXX) -g -o $@ $^ $(LDFLAGS)


symdraw: symdraw.o
	$(CXX) -g -o $@ $^ $(LDFLAGS)

.cpp.o:
	$(CXX) $(CFLAGS) -c $^

clean:
	rm -vf *.o veridt

