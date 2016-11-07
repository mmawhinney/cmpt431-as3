#!/bin/bash 
icc -std=c99 -g -O2 othello.c othello.h othello-simple-ai.c othello-good-ai2.c -o othello-parallel

#icpc -O2 othello.c othello.h othello-simple-ai.cpp othello-good-ai.cpp -o othello-parallel2

