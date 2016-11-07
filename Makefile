
CC = gcc-5.4
CXX = g++-5.4
CC_FLAGS = -std=c99 -fcilkplus -g

ifeq ($(DEBUG), 1)
	CC_FLAGS += -g
else
	CC_FLAGS += -O2
endif

all: othello-serial othello-parallel

clean:
	rm -f othello-serial othello-parallel

othello-serial: othello.c hwtimer.h othello.h othello-human.c othello-simple-ai.c othello-good-ai.c
	$(CC) $(CC_FLAGS) othello.c othello-simple-ai.c othello-good-ai.c -o othello-serial -D SERIALIZE #. If you want to serialize. 

othello-parallel: hwtimer.h othello.c hwtimer.h othello.h othello-human.c othello-simple-ai.c othello-good-ai.cpp
	$(CXX) othello.c othello-simple-ai.c othello-good-ai.cpp -o othello-parallel -fcilkplus
