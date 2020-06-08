#include "ordre_depart.h"


/*fonction qui trie les joueurs selon les résultat du premier tirage des dés*/
int tri_rapide(int *T,int debut,int fin){
	int pivot,i,j,temp;
	pivot=T[debut];
	if (debut>=fin) return 0;
	j=debut;
	for (i=debut+1;i<=fin;i++){
		if (T[i]<pivot){
			j++;
			temp=T[i];
			T[i]=T[j];
			T[j]=temp;
		}
	}
	temp=T[j];
	T[j]=T[debut];
	T[debut]=temp;
	tri_rapide(T,debut,j-1);
	tri_rapide(T,j+1,fin);
	return 0;
}


