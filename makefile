all: clean diningFilo diningFilo_mod diningFilo2 diningFilo_mod2 

diningFilo: diningFilo.c
	gcc diningFilo.c -o diningFilo -pthread -w

diningFilo_mod: diningFilo_mod.c
	gcc diningFilo_mod.c -o diningFilo_mod -pthread -w

diningFilo2: diningFilo2.c
	gcc diningFilo2.c -o diningFilo2 -pthread

diningFilo_mod2: diningFilo_mod2.c
	gcc diningFilo_mod2.c -o diningFilo_mod2 -pthread -w

clean :
	rm -f diningFilo diningFilo_mod diningFilo2 diningFilo_mod2