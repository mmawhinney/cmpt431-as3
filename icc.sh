#!/bin/bash 
icc -std=c99 -O2 othello.c othello.h othello-simple-ai.c othello-good-ai.c -o othello-parallel
