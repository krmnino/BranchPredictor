CXXFLAGS = -std=c++17

DEPS =	all_not_taken.cpp all_taken.cpp bimodal_1bit.cpp bimodal_2bit.cpp\
		branch_target_buffer.cpp gshare.cpp tournament.cpp

OBJS =	all_not_taken.o all_taken.o bimodal_1bit.o bimodal_2bit.o\
		branch_target_buffer.o gshare.o tournament.o

predictors: predictors.o $(OBJS)
	g++ predictors.o $(OBJS) -o predictors

predictors.o: predictors.cpp 
	g++ -c $(CXXFLAGS) predictors.cpp

$(OBJS): $(DEPS)
	g++ -c $(CXXFLAGS) $(DEPS)

clean:
	rm -f *.o predictors