CXX := g++
CXXFLAGS := -std=c++11 -Wall -O2

TARGET := sum-nbo
SRCS := main.cpp sum_nbo.cpp
OBJS := $(SRCS:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp sum_nbo.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
