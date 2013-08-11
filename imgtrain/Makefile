
CFLAGS=-g -Wall -I/usr/include -I/usr/include/opencv2
LDFLAGS=-lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_photo
CXX=g++


all: veridt

veridt: main.o
	$(CXX) -o $@ $< $(LDFLAGS)

.cpp.o:
	$(CXX) $(CFLAGS) -c $^

clean:
	rm -vf *.o veridt

