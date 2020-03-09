TARGET = predictions

OBJS = predictions.o\
#		all_taken.o\
		all_not_taken\
		bimodal_1bit.o\
		bimodal_2bit.o\
		branch_target_buffer.o\
		gshare.o\
		tournament.o\
		predictions.o

CXX = g++
CXXFLAGS = -std=c++17

$(TARGET):	$(OBJS)	
		$(CXX) $(CXXFLAGS) predictions.o -o $(TARGET)

clean:
		rm -f *.o $(TARGET)

all_not_taken.o:	all_not_taken.cpp
all_taken.o:	all_taken.cpp
bimodal_1bit.o:	bimodal_1bit.cpp
bimodal_2bit.o:	bimodal_2bit.cpp
branch_target_buffer.o: branch_target_buffer.cpp
gshare.o: gshare.cpp
tournament.o: tournament.cpp
predictions.o: 	predictions.cpp