#!/bin/sh



./wumpsim  -trials 1000 -tries 10 | grep -w "Score" > test.txt


cat test.txt |  grep -e "-10" > 100.txt