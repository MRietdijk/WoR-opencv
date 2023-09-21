CFLAGS= -Wall -Wextra -Wconversion `pkg-config --cflags opencv4`
LIBS= `pkg-config --libs opencv4`
# -Wall -Wextra -Wconversion

O_FILES= CameraFeed.o FileFeed.o Feed.o Command.o FileReader.o Input.o ImageProcessor.o
COMMAND_O_FILES= CameraFeed FileFeed Feed Command FileReader Input ImageProcessor

all: main clean

main: $(COMMAND_O_FILES)
	g++ main.cpp $(O_FILES) $(CFLAGS) $(LIBS) -o main
 

FileFeed: Feed
	g++ -c FileFeed.cpp $(CFLAGS) $(LIBS) -o FileFeed.o

CameraFeed: Feed
	g++ -c CameraFeed.cpp $(CFLAGS) $(LIBS) -o CameraFeed.o

Feed:
	g++ -c Feed.cpp $(CFLAGS) $(LIBS) -o Feed.o

Command:
	g++ -c Command.cpp $(CFLAGS) $(LIBS) -o Command.o

FileReader:
	g++ -c FileReader.cpp $(CFLAGS) $(LIBS) -o FileReader.o

Input:
	g++ -c Input.cpp $(CFLAGS) $(LIBS) -o Input.o

ImageProcessor:
	g++ -c ImageProcessor.cpp $(CFLAGS) $(LIBS) -o ImageProcessor.o

clean:
	-rm *.o