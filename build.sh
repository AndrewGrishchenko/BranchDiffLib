#!/bin/sh
gcc -c -fpic -o branchdiff.o branchdiff.c
gcc -shared -o libbranchdiff.so branchdiff.o
