CC    = g++
SRCS  = mdp.cpp
OBJS  = mdp.o
EXE   = mdp
LS    = LS/
ILS   = ILS/
TS    =	TS/
MA    = MA/
GA    = GA/
FLAGS = -O3

all: ils ts ma ga

ils: $(ILS)$(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(ILS)$(EXE); rm -f *.o

ts: $(TS)$(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(TS)$(EXE); rm -f *.o

ma: $(MA)$(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(MA)$(EXE); rm -f *.o

ga: $(GA)$(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(GA)$(EXE); rm -f *.o

$(ILS)%.o: $(ILS)%.cpp
	$(CC) $(FLAGS) -c $<

$(TS)%.o: $(TS)%.cpp
	$(CC) $(FLAGS) -c $<

$(MA)%.o: $(MA)%.cpp
	$(CC) $(FLAGS) -c $<

$(GA)%.o: $(GA)%.cpp
	$(CC) $(FLAGS) -c $<

clean:
	find . -name "mdp" -type f -delete