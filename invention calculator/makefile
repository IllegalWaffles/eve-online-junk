INVENTION_CALC 	:= invention_calc
SRC 			:= inventionCalc.c
INC 			:= -I invenctionCalc.h
CC 				:= gcc
CFLAGS 			:= -Wall -Werror
LIBS 			:= -pthread
STD 			:= -std=gnu11
DFLAGS 			:= -g -DDEBUG -DCOLOR
IFLAGS			:= -g -DINFO -DCOLOR

all: $(INVENTION_CALC)

$(INVENTION_CALC):
	$(CC) $(CFLAGS) $(INC) $(SRC) -o $@ $(LIBS)

clean:
	$(RM) -r $(INVENTION_CALC) *.o

debug: CFLAGS += $(DFLAGS)
debug: all

info: CLFAGS += $(IFLAGS)
info: all