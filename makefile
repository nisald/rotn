FLAGS=-std=c11 -Wall -Werror -pipe

rotn: rotn.c
	gcc $(FLAGS) rotn.c -o rotn

rotn_debug: rotn.c
	gcc $(FALGS) -g3 rotn.c -o rotn
