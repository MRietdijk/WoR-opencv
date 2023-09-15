CFLAGS= -Wall `pkg-config --cflags opencv4`
LIBS= `pkg-config --libs opencv4`

O_FILES= CameraFeed.o FileFeed.o Feed.o
COMMAND_O_FILES= CameraFeed FileFeed Feed

all: main clean

main: $(COMMAND_O_FILES)
	g++ main.cpp $(O_FILES) $(CFLAGS) $(LIBS) -o main
 

FileFeed: Feed
	g++ -c FileFeed.cpp $(CFLAGS) $(LIBS) -o FileFeed.o

CameraFeed: Feed
	g++ -c CameraFeed.cpp $(CFLAGS) $(LIBS) -o CameraFeed.o

Feed:
	g++ -c Feed.cpp $(CFLAGS) $(LIBS) -o Feed.o

preprocessing:
	g++ preprocessing.cpp $(CFLAGS) $(LIBS) -o main

clean:
	-rm Feed.o
	-rm CameraFeed.o
	-rm FileFeed.o