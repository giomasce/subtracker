UNAME := $(shell uname -s)
CPP = g++
CFLAGS = $(shell pkg-config --cflags opencv) -g -O2
CPPFLAGS = $(shell pkg-config --cflags opencv) -g -std=c++11 -O2
LIBS = $(shell pkg-config --libs opencv)

HEADERS = blobs_finder.hpp blobs_tracker.hpp utility.hpp
OBJECTS = blobs_finder.o blobs_tracker.o subtracker.o utility.o

all: subtracker

clean:
	rm -f track kalman
	rm subtracker
	rm *.o

subtracker:  $(OBJECTS)
	$(CPP) $(CPPFLAGS) $(LIBS) -o subtracker $(OBJECTS)

subotto_tracking_test: subotto_tracking_test.cpp utility.o subotto_tracking.o subotto_metrics.o
	$(CPP) $(CPPFLAGS) $(LIBS) -o subotto_tracking_test $< utility.o subotto_tracking.o subotto_metrics.o

median_test: median_test.cpp median.o
	$(CPP) $(CPPFLAGS) $(LIBS) -o $@ $< median.o

jobrunner_test: jobrunner_test.cpp jobrunner.o jobrunner.hpp
	$(CPP) $(CPPFLAGS) $(LIBS) -o $@ $< jobrunner.o

ball_tracking_test: ball_tracking_test.cpp subotto_tracking.o ball_density.o utility.o subotto_metrics.o
	$(CPP) $(CPPFLAGS) $(LIBS) -o ball_tracking_test $< subotto_tracking.o ball_density.o utility.o subotto_metrics.o

ball_density_test: ball_density_test.cpp ball_density.o subotto_tracking.o subotto_metrics.o
	$(CPP) $(CPPFLAGS) $(LIBS) -o ball_density_test $< ball_density.o subotto_tracking.o subotto_metrics.o

mock: mock.cpp
	$(CPP) $< -std=c++11 -o mock

%.o: %.cpp $(HEADERS) Makefile
	$(CPP) $(CPPFLAGS) -c $<

% : %.cpp
	$(CPP) $(CPPFLAGS) $(LIBS) -o $@ $<
