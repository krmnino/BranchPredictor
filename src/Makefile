TARGET = predictions

OBJS = predictions.o

CXX = g++
CXXFLAGS = -std=c++17

$(TARGET):	$(OBJS)	
		$(CXX) $(CXXFLAGS) predictions.o -o $(TARGET)

clean:
		rm -f *.o $(TARGET)

predictions.o: 	predictions.cpp