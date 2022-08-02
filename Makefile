all: BOSS
BOSS: BOSS.o lib_boss.o 
		gcc BOSS.o lib_boss.o -lm -o BOSS -lz
BOSS.o: BOSS.c lib_boss.h external/kseq.h
		gcc -Wall -Werror -c BOSS.c
lib_boss.o: lib_boss.c lib_boss.h
		gcc -Wall -Werror -c lib_boss.c
# kseq.o: kseq.h
# 		gcc -Wall -Werror -c kseq.h -lz