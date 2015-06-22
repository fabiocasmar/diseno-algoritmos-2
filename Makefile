CC   = g++
LIB  = solution
SRC  = mdp.cpp
OBJS = solution.o mdp.o
EXE  = mdp
LS   = LS/
ILS  = ILS/
ITS  = ITS/
TS   = TS/
MA   = MA/
GA   = GA/
FLAG = -O3

all: ls ils its ts ma ga
	rm -f $(LIB).o

ls: $(LIB)
	$(CC) $(FLAG) -c $(LS)mdp_pmv.cpp
	$(CC) $(FLAG) $(LIB).o mdp_pmv.o -o $(LS)mdp_pmv
	$(CC) $(FLAG) -c $(LS)mdp_mv.cpp
	$(CC) $(FLAG) $(LIB).o mdp_mv.o -o $(LS)mdp_mv
	rm -f mdp_pmv.o mdp_mv.o

ils: $(LIB)
	$(CC) $(FLAG) -c $(ILS)$(SRC)
	$(CC) $(FLAG) $(OBJS) -o $(ILS)$(EXE)
	rm -f $(EXE).o

its: $(LIB)
	$(CC) $(FLAG) -c $(ITS)$(SRC)
	$(CC) $(FLAG) $(OBJS) -o $(ITS)$(EXE)
	rm -f $(EXE).o

ts: $(LIB)
	$(CC) $(FLAG) -c $(TS)$(SRC)
	$(CC) $(FLAG) $(OBJS) -o $(TS)$(EXE)
	rm -f $(EXE).o

ma: $(LIB)
	$(CC) $(FLAG) -c $(MA)$(SRC)
	$(CC) $(FLAG) $(OBJS) -o $(MA)$(EXE)
	rm -f $(EXE).o

ga: $(LIB)
	$(CC) $(FLAG) -c $(GA)$(SRC)
	$(CC) $(FLAG) $(OBJS) -o $(GA)$(EXE)
	rm -f $(EXE).o

$(LIB):
	$(CC) $(FLAG) -c lib/$@.cpp

clean:
	find . -name "mdp" -type f -delete
	rm -f $(LS)mdp_pmv $(LS)mdp_mv
	rm -f *.o