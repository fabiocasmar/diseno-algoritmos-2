CC    = g++
SRCS  = mdpPrimerMejorVecindad.cpp
OBJS  = mdpPrimerMejorVecindad.o
EXE   = mdpPrimerMejorVecindad
FLAGS = -O3

all: $(SRCS) $(EXE)
	rm -f *.o

$(EXE): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $@

%.o: %.cpp
	$(CC) $(FLAGS) -c $<

clean:
	rm -f $(EXE) *.o