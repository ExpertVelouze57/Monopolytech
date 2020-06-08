all: Monopoly

Monopoly: executables/main.o executables/interface_graphique.o executables/fct_elem.o executables/init.o executables/ordre_depart.o executables/fct.o executables/init_joueur.o executables/fenetre_tt_tour.o executables/aide_graphique.o executables/joueur_ruine.o executables/choix_prison.o executables/info.o
	gcc -ansi -Wall -o Monopoly executables/main.o executables/interface_graphique.o executables/fct_elem.o executables/init.o executables/ordre_depart.o executables/fct.o executables/init_joueur.o executables/fenetre_tt_tour.o executables/aide_graphique.o executables/joueur_ruine.o executables/choix_prison.o executables/info.o -lSDL -lSDL_ttf

executables/interface_graphique.o: lib/interface_graphique.c lib/interface_graphique.h
	gcc -ansi -Wall -c lib/interface_graphique.c
	mv interface_graphique.o executables

executables/main.o: main.c lib/interface_graphique.h
	gcc -ansi -Wall -c main.c
	mv main.o executables
	
executables/fct_elem.o: lib/fct_elem.c lib/fct_elem.h
	gcc -ansi -Wall -c lib/fct_elem.c
	mv fct_elem.o executables
	
executables/init.o: lib/init.c lib/init.h
	gcc -ansi -Wall -c lib/init.c
	mv init.o executables
	
executables/ordre_depart.o: lib/ordre_depart.c lib/ordre_depart.h
	gcc -ansi -Wall -c lib/ordre_depart.c
	mv ordre_depart.o executables

executables/fct.o: lib/fct.c lib/fct.h
	gcc -ansi -Wall -c lib/fct.c
	mv fct.o executables
	
executables/init_joueur.o: lib/init_joueur.c lib/init_joueur.h
	gcc -ansi -Wall -c lib/init_joueur.c
	mv init_joueur.o executables
	
executables/fenetre_tt_tour.o: lib/fenetre_tt_tour.c lib/fenetre_tt_tour.h
	gcc -ansi -Wall -c lib/fenetre_tt_tour.c
	mv fenetre_tt_tour.o executables
	
executables/aide_graphique.o: lib/aide_graphique.c lib/aide_graphique.h
	gcc -ansi -Wall -c lib/aide_graphique.c
	mv aide_graphique.o executables
	
executables/joueur_ruine.o: lib/joueur_ruine.c lib/joueur_ruine.h
	gcc -ansi -Wall -c lib/joueur_ruine.c
	mv joueur_ruine.o executables
	
executables/choix_prison.o: lib/choix_prison.c lib/choix_prison.h
	gcc -ansi -Wall -c lib/choix_prison.c
	mv choix_prison.o executables
	
executables/info.o: lib/info.c lib/info.h
	gcc -ansi -Wall -c lib/info.c
	mv info.o executables


clean:	
	rm -fr executables/*.o Monopoly
