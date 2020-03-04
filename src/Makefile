TARGET = predictions

OBJS = predictions.o

CXX = g++
CXXFLAGS = -std=c++17
LDFLAGS = 

$(TARGET):	$(OBJS)	
		$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

clean:
		rm -f *.o $(TARGET)

predictions.o: 	predictions.cpp

