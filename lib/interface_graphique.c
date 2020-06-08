#include "interface_graphique.h"

/* permet d'afficher le plateau de jeu */
int affiche_plateau(int joueur, PLATEAU *plateau, int *parc_gratuit, int lancer, int *a, int *b, int tete) {
	
	/* ecran jeu */
	
	SDL_Surface *ecran =NULL;
	SDL_Surface *rectangle=NULL;
	SDL_Surface *bouton = NULL;
	SDL_Surface *texte=NULL;
    SDL_Rect positionbouton;
	SDL_Rect position;
	int nb1=0,nb2=0,nb3=0,i;
	int *appui;
	appui=(int *)malloc(sizeof(int));
	*appui=0;
	
	if(SDL_Init(SDL_INIT_VIDEO)==-1){
		fprintf(stderr,"Erreur d'initialisation de la SDL : %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	/*ouverture ecran*/
	ecran = SDL_SetVideoMode(1180,660,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(ecran==NULL){
		fprintf(stderr,"Impossible de charger le mode video : %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	/*titre fenetre*/
	SDL_WM_SetCaption("MonopolyTech",NULL);
	
	/*coloration ecran*/
	SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
	
	/* initialisation écriture */
	TTF_Init();
	
	/* couleur plateau */
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,660,660,32,0,0,0,0);
	position.x=0;
	position.y=0;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,213,208,134));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	/* couleur cadran joueur */
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,500,590,32,0,0,0,0);
	position.x=670;
	position.y=10;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,147));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	/* affichage 4 cases joueurs */
	cases4_joueurs(joueur,rectangle,position,ecran,texte,plateau);
	
	/*placement joueur sur plateau*/
	int j1=position_joueur(0,plateau);
	int j2=position_joueur(1,plateau);
	int j3=position_joueur(2,plateau);
	int j4=position_joueur(3,plateau);
	placer_joueur(rectangle,position,ecran,j1,0,nb1++);
	if (j2==j1) placer_joueur(rectangle,position,ecran,j2,1,nb1++);
	else placer_joueur(rectangle,position,ecran,j2,1,nb2++);
	if (j3==j1) placer_joueur(rectangle,position,ecran,j3,2,nb1++);
	else if (j3==j2) placer_joueur(rectangle,position,ecran,j3,2,nb2++);
	else placer_joueur(rectangle,position,ecran,j3,2,nb3++);
	if (j4==j1) placer_joueur(rectangle,position,ecran,j4,3,nb1);
	else if (j4==j2) placer_joueur(rectangle,position,ecran,j4,3,nb2);
	else if (j4==j3) placer_joueur(rectangle,position,ecran,j4,3,nb3);
	else placer_joueur(rectangle,position,ecran,j4,3,0);
	
	/* affichage proprietaires rues */
	for (i=1;i<=40;i++) affiche_proprietaire(ecran,position,rectangle,plateau,i);
	
	/* rues */
	affiche_rues(rectangle, position, ecran);
	
	/* affichage maison */
	for (i=1;i<=40;i++){
		placer_maison(rectangle,position,ecran,i,nb_maisons(i,plateau));	
	}
	/* écriture */
	texte_base(ecran,position,texte);
	infos_joueur(ecran,position,texte,rectangle,plateau,joueur);
	TTF_Font *police_p=NULL,*police8=NULL,*police9=NULL,*police10=NULL;
	police8=TTF_OpenFont("police/liberation/LiberationSans-Regular.ttf",8);
	police9=TTF_OpenFont("police/liberation/LiberationSans-Regular.ttf",9);
	police10=TTF_OpenFont("police/liberation/LiberationSans-Regular.ttf",10);
	police_p=TTF_OpenFont("police/liberation/LiberationSans-Regular.ttf",15);
	for(i=1;i<=40;i++) {
		ecrire_nom_rue(ecran,position,texte,plateau,i,police_p,police8,police9,police10);
	}
	/* affichage infos case */
	affiche_infos_case(ecran,position,texte,rectangle,plateau,position_joueur(joueur,plateau),joueur);
	
	/* bouton sauvegarde */
	positionbouton.x =1100;
    positionbouton.y =605;
	bouton = SDL_LoadBMP("images_bmp/sauvegarde.bmp");
	SDL_SetColorKey(bouton,SDL_SRCCOLORKEY,SDL_MapRGB(bouton->format,0,255,0));
	SDL_BlitSurface(bouton, NULL, ecran, &positionbouton);
	TTF_Font *police=NULL;
	SDL_Color noire={0,0,0};
	police=TTF_OpenFont("police/liberation/LiberationSans-Bold.ttf",25);
	texte=TTF_RenderText_Blended(police,"Sauvegarder et Quitter",noire);
	position.x=1100-texte->w;
	position.y=630-texte->h/2;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	
	/* bouton suivant */
	bouton = SDL_LoadBMP("images_bmp/bouton.bmp");
	positionbouton.x =920-bouton->w/2;
    positionbouton.y =500;
	SDL_SetColorKey(bouton,SDL_SRCCOLORKEY,SDL_MapRGB(bouton->format,255,255,255));
	SDL_BlitSurface(bouton, NULL, ecran, &positionbouton);
	SDL_Color blanc={255,255,255};
	texte=TTF_RenderText_Blended(police,"Continuer",blanc);
	position.x=positionbouton.x+bouton->w/2-texte->w/2;
	position.y=500+bouton->h/2-texte->h/2;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	
	/* lignes */
	affichage_lignes(ecran);
	
	/* affichage argent open_source ou dés*/
	if (lancer==0) affiche_argent_parc(ecran,position,texte,parc_gratuit);
	else {
		SDL_Rect posdes1;
		SDL_Rect posdes2;
		posdes1.x=215;
		posdes1.y=240;
		posdes2.x=345;
		posdes2.y=240;
		lance_des(ecran,a,b,posdes1,posdes2);
	}
	
	SDL_Flip(ecran); /*mise a jour ecran*/
	int res;
	res=pause(ecran,joueur,plateau,parc_gratuit,tete);
	
	SDL_FreeSurface(rectangle);
	SDL_FreeSurface(bouton);
	SDL_FreeSurface(texte);
	SDL_FreeSurface(ecran);
	TTF_Quit();
	SDL_Quit();
	return res;
}

/* fonction qui attend un evenement (appui sur bouton,...) */
int pause(SDL_Surface *ecran, int joueur_courant, PLATEAU *plateau, int *parc_gratuit, int tete){
	int continuer=1;
	SDL_Event event;
	while (continuer==1){
		SDL_WaitEvent(&event);
		switch(event.type) {
			case SDL_QUIT :
				continuer=-2;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(traitement_bouton_sauvegarde(&event) == 1){
					sauvegarder(joueur_courant,plateau,*parc_gratuit,tete);
					continuer=-1;
				} else if (event.button.button == SDL_BUTTON_LEFT && verification_zone(&event,845,500,150,50)){
					continuer=0;
				}
				break;
		}
	}
	return continuer;
}

/* permet de colorer un pixel de l'ecran */
void SDL_PutPixel(SDL_Surface *surface, int x, int y, unsigned long pixel)
{
    int bpp = surface->format->BytesPerPixel;
    unsigned char *p = (unsigned char *)surface->pixels + y * surface->pitch + x * bpp;
    if (bpp==4)
        *(unsigned long*)p = pixel;
}

/* permet de tracer une ligne a l'ecran */
void Line(SDL_Surface* surf,int x1,int y1, int x2,int y2,unsigned long couleur)
{
  int x,y;
  int Dx,Dy;
  int xincr,yincr;
  int erreur;
  int i;
 
  Dx = abs(x2-x1);
  Dy = abs(y2-y1);
  if(x1<x2)
    xincr = 1;
  else
    xincr = -1;
  if(y1<y2)
    yincr = 1;
  else
    yincr = -1;
 
  x = x1;
  y = y1;
  if(Dx>Dy)
    {
      erreur = Dx/2;
      for(i=0;i<Dx;i++)
        {
          x += xincr;
          erreur += Dy;
          if(erreur>Dx)
            {
              erreur -= Dx;
              y += yincr;
            }
        SDL_PutPixel(surf,x, y,couleur);
        }
    }
  else
    {
      erreur = Dy/2;
      for(i=0;i<Dy;i++)
        {
          y += yincr;
          erreur += Dx;
          if(erreur>Dy)
            {
              erreur -= Dy;
              x += xincr;
            }
        SDL_PutPixel(surf,x, y,couleur);
        }
    }
}

/* affichage des 4 cases recapitulatives au centre du plateau */
void cases4_joueurs(int joueur, SDL_Surface *rectangle, SDL_Rect position, SDL_Surface *ecran, SDL_Surface *texte, PLATEAU *plateau) {
	/* affichage 4 cases joueurs */
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,100,90,32,0,0,0,0);
	position.x=87;
	position.y=420;
	if (joueur==0) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,0));
	else if (joueur_present(0,plateau)) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,255));
	else SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,65,65,65));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,100,10,32,0,0,0,0);
	position.x=87;
	position.y=510;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,0));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	TTF_Font *police=NULL;
	SDL_Color noire={0,0,0};
	police=TTF_OpenFont("police/liberation/LiberationSans-Regular.ttf",20);
	char nom[20];
	nom_joueur(nom,0,plateau);
	texte=TTF_RenderText_Blended(police,nom,noire);
	position.x=137-texte->w/2;
	position.y=430;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	sprintf(nom,"%d",compte_joueur(0,plateau));
	strcat(nom," pp");
	texte=TTF_RenderText_Blended(police,nom,noire);
	position.x=137-texte->w/2;
	position.y=470;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,100,90,32,0,0,0,0);
	position.x=215;
	position.y=420;
	if (joueur==1) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,0));
	else if (joueur_present(1,plateau)) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,255));
	else SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,65,65,65));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,100,10,32,0,0,0,0);
	position.x=215;
	position.y=510;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,255,0));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	nom_joueur(nom,1,plateau);
	texte=TTF_RenderText_Blended(police,nom,noire);
	position.x=265-texte->w/2;
	position.y=430;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	sprintf(nom,"%d",compte_joueur(1,plateau));
	strcat(nom," pp");
	texte=TTF_RenderText_Blended(police,nom,noire);
	position.x=265-texte->w/2;
	position.y=470;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,100,90,32,0,0,0,0);
	position.x=343;
	position.y=420;
	if (joueur==2) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,0));
	else if (joueur_present(2,plateau)) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,255));
	else SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,65,65,65));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,100,10,32,0,0,0,0);
	position.x=343;
	position.y=510;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,0,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	nom_joueur(nom,2,plateau);
	texte=TTF_RenderText_Blended(police,nom,noire);
	position.x=393-texte->w/2;
	position.y=430;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	sprintf(nom,"%d",compte_joueur(2,plateau));
	strcat(nom," pp");
	texte=TTF_RenderText_Blended(police,nom,noire);
	position.x=393-texte->w/2;
	position.y=470;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,100,90,32,0,0,0,0);
	position.x=471;
	position.y=420;
	if (joueur==3) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,0));
	else if (joueur_present(3,plateau)) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,255));
	else SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,65,65,65));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,100,10,32,0,0,0,0);
	position.x=471;
	position.y=510;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	nom_joueur(nom,3,plateau);
	texte=TTF_RenderText_Blended(police,nom,noire);
	position.x=521-texte->w/2;
	position.y=430;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	sprintf(nom,"%d",compte_joueur(3,plateau));
	strcat(nom," pp");
	texte=TTF_RenderText_Blended(police,nom,noire);
	position.x=521-texte->w/2;
	position.y=470;
	SDL_BlitSurface(texte,NULL,ecran,&position);
}

/* affichage des lignes principales du plateau */
void affichage_lignes(SDL_Surface *ecran){
	/* lignes */
	Line(ecran,59,0,59,659,0x000);
	Line(ecran,0,0,0,659,0x000);
	Line(ecran,599,0,599,659,0x000);
	Line(ecran,659,0,659,659,0x000);
	Line(ecran,0,0,659,0,0x000);
	Line(ecran,0,59,659,59,0x000);
	Line(ecran,0,599,659,599,0x000);
	Line(ecran,0,659,659,659,0x000);
	int i,j;
	for(i=1;i<10;i++){
		j=59+60*i;
		Line(ecran,j,0,j,59,0x000);
		Line(ecran,j,599,j,659,0x000);
		Line(ecran,0,j,59,j,0x000);
		Line(ecran,599,j,659,j,0x000);
	}
	Line(ecran,10,599,10,648,0x000);
	Line(ecran,10,648,59,648,0x000);
	Line(ecran,614,645,644,645,0x000);
	Line(ecran,614,645,622,653,0x000);
	Line(ecran,614,645,622,637,0x000);	
	for (i=0;i<4;i++){
		j=87+i*128;
		Line(ecran,j,420,j+100,420,0x0);
		Line(ecran,j,520,j+100,520,0x0);
		Line(ecran,j,420,j,520,0x0);
		Line(ecran,j+100,420,j+100,520,0x0);
	}
	Line(ecran,670,10,1170,10,0x000);
	Line(ecran,670,10,670,600,0x000);
	Line(ecran,670,600,1170,600,0x000);
	Line(ecran,1170,10,1170,600,0x000);
	Line(ecran,670,80,1170,80,0x000);
	
	Line(ecran,180,75,480,75,0x0);
	Line(ecran,180,75,180,225,0x0);
	Line(ecran,180,225,480,225,0x0);
	Line(ecran,480,75,480,225,0x0);
}

/* permet d'affiche les cases des rues du plateau */
void affiche_rues(SDL_Surface *rectangle, SDL_Rect position, SDL_Surface *ecran){
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,15,32,0,0,0,0);
	position.x=539;
	position.y=599;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,128,64,0));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,15,32,0,0,0,0);
	position.x=419;
	position.y=599;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,128,64,0));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,15,32,0,0,0,0);
	position.x=239;
	position.y=599;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,255,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,15,32,0,0,0,0);
	position.x=119;
	position.y=599;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,255,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,15,32,0,0,0,0);
	position.x=59;
	position.y=599;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,255,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,15,60,32,0,0,0,0);
	position.x=44;
	position.y=539;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,15,60,32,0,0,0,0);
	position.x=44;
	position.y=419;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,15,60,32,0,0,0,0);
	position.x=44;
	position.y=359;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,15,60,32,0,0,0,0);
	position.x=44;
	position.y=239;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,128,0));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,15,60,32,0,0,0,0);
	position.x=44;
	position.y=119;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,128,0));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,15,60,32,0,0,0,0);
	position.x=44;
	position.y=59;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,128,0));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,15,32,0,0,0,0);
	position.x=59;
	position.y=44;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,0));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,15,32,0,0,0,0);
	position.x=179;
	position.y=44;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,0));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,15,32,0,0,0,0);
	position.x=239;
	position.y=44;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,0));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,15,32,0,0,0,0);
	position.x=359;
	position.y=44;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,0));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,15,32,0,0,0,0);
	position.x=419;
	position.y=44;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,0));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,15,32,0,0,0,0);
	position.x=539;
	position.y=44;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,0));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,15,60,32,0,0,0,0);
	position.x=599;
	position.y=59;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,200,0));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,15,60,32,0,0,0,0);
	position.x=599;
	position.y=119;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,200,0));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,15,60,32,0,0,0,0);
	position.x=599;
	position.y=239;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,200,0));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,15,60,32,0,0,0,0);
	position.x=599;
	position.y=419;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,0,160));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,15,60,32,0,0,0,0);
	position.x=599;
	position.y=539;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,0,160));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);	
}

/* permet de placer le curseur des joueurs sur le plateau */
void placer_joueur(SDL_Surface *rectangle, SDL_Rect position, SDL_Surface *ecran, int pos, int num, int nb){
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,10,10,32,0,0,0,0);
	if (num==0) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,0));
	else if (num==1) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,255,0));
	else if (num==2) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,0,255));
	else if (num==3) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,255));
	
	if (pos>=2 && pos<=11) {
		position.x=604-(pos-1)*60+nb*14;
		position.y=649;
	} else if (pos>=12 && pos<=21) {
		position.x=0;
		position.y=604-(pos-11)*60+nb*14;
	} else if (pos>=22 && pos<=31) {
		position.x=4+(pos-21)*60+nb*14;
		position.y=0;
	} else if (pos>=32 && pos<=40){
		position.x=649;
		position.y=4+(pos-31)*60+nb*14;
	} else if (pos==1) {
		position.x=649;
		position.y=604+nb*14;
	}
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
}

/* permet d'afficher les maisons presentes sur les rues du plateau */
void placer_maison(SDL_Surface *rectangle, SDL_Rect position, SDL_Surface *ecran, int pos, int nb){
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,6,6,32,0,0,0,0);
	int i;
	if (pos>=2 && pos<=10) {
		if (nb==5) {
			position.x=627-(pos-1)*60;
			position.y=594;
			SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,221,0,0));
			SDL_BlitSurface(rectangle,NULL,ecran,&position);
		} else if (nb>=1) {
			SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,51,166,60));
			for (i=1;i<=nb;i++){
				position.x=609+(i-1)*12-(pos-1)*60;
				position.y=594;
				SDL_BlitSurface(rectangle,NULL,ecran,&position);
			}
		}		
	} else if (pos>=12 && pos<=20) {
		if (nb==5) {
			position.x=60;
			position.y=627-(pos-11)*60;
			SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,221,0,0));
			SDL_BlitSurface(rectangle,NULL,ecran,&position);
		} else if (nb>=1) {
			SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,51,166,60));
			for (i=1;i<=nb;i++){
				position.x=60;
				position.y=609-(pos-11)*60+(i-1)*12;
				SDL_BlitSurface(rectangle,NULL,ecran,&position);
			}
		}	
	} else if (pos>=22 && pos<=30) {
		if (nb==5) {
			position.x=27+(pos-21)*60;
			position.y=60;
			SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,221,0,0));
			SDL_BlitSurface(rectangle,NULL,ecran,&position);
		} else if (nb>=1) {
			SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,51,166,60));
			for (i=1;i<=nb;i++){
				position.x=9+(i-1)*12+(pos-21)*60;
				position.y=60;
				SDL_BlitSurface(rectangle,NULL,ecran,&position);
			}
		}	
	} else if (pos>=32 && pos<=40) {
		if (nb==5) {
			position.x=594;
			position.y=27+(pos-31)*60;
			SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,221,0,0));
			SDL_BlitSurface(rectangle,NULL,ecran,&position);
		} else if (nb>=1) {
			SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,51,166,60));
			for (i=1;i<=nb;i++){
				position.x=594;
				position.y=9+(pos-31)*60+(i-1)*12;
				SDL_BlitSurface(rectangle,NULL,ecran,&position);
			}
		}
	}
}

/* fonction pour l'appui sur le bouton sauvegarde */
int traitement_bouton_sauvegarde(SDL_Event *event){
	if (event->button.button == SDL_BUTTON_LEFT){
		if(event->button.x > (1100) && event->button.x < (1150) && event->button.y > (605) && event->button.y < (655)){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

/* renvoie 2 nombres aleatoires dans a et b */
void nb_alea(int *a, int *b){
    srand(time(NULL));
    *a = (rand() % (MAX - MIN + 1)) + MIN;
	*b = (rand() % (MAX - MIN + 1)) + MIN;
}

/* permet l'affichage des dés sur le plateau */
void lance_des(SDL_Surface *ecran, int *a, int*b, SDL_Rect posdes1, SDL_Rect posdes2){
	SDL_Surface *des1,*des2;

	/*partie annimation*/
	int i,aff;
	char source[20];
	
	for(i=0; i<10;i++){
		aff = (rand() % (MAX - MIN + 1)) + MIN;
		choix_des(source, aff);
		des1 = SDL_LoadBMP(source);
		aff = (rand() % (MAX - MIN + 1)) + MIN;
		choix_des(source, aff);
		des2 = SDL_LoadBMP(source);
	
		
		SDL_BlitSurface(des1, NULL, ecran, &posdes1);
		SDL_BlitSurface(des2, NULL, ecran, &posdes2);
		
		Line(ecran,posdes1.x,posdes1.y,posdes1.x+100,posdes1.y,0x000);
		Line(ecran,posdes1.x,posdes1.y,posdes1.x,posdes1.y+100,0x000);
		Line(ecran,posdes1.x+100,posdes1.y,posdes1.x+100,posdes1.y+100,0x000);
		Line(ecran,posdes1.x,posdes1.y+100,posdes1.x+100,posdes1.y+100,0x000);
		Line(ecran,posdes2.x,posdes2.y,posdes2.x+100,posdes2.y,0x000);
		Line(ecran,posdes2.x,posdes2.y,posdes2.x,posdes2.y+100,0x000);
		Line(ecran,posdes2.x+100,posdes2.y,posdes2.x+100,posdes2.y+100,0x000);
		Line(ecran,posdes2.x,posdes2.y+100,posdes2.x+100,posdes2.y+100,0x000);
	
		SDL_Flip(ecran);
		SDL_Delay(100);
	}
	
	/*Partie affichage des resultat*/
	
	nb_alea(a,b);
	choix_des(source, *a);
	des1 = SDL_LoadBMP(source);
	choix_des(source, *b);
	des2 = SDL_LoadBMP(source);

	SDL_BlitSurface(des1, NULL, ecran, &posdes1);
	SDL_BlitSurface(des2, NULL, ecran, &posdes2);
	Line(ecran,posdes1.x,posdes1.y,posdes1.x+100,posdes1.y,0x000);
	Line(ecran,posdes1.x,posdes1.y,posdes1.x,posdes1.y+100,0x000);
	Line(ecran,posdes1.x+100,posdes1.y,posdes1.x+100,posdes1.y+100,0x000);
	Line(ecran,posdes1.x,posdes1.y+100,posdes1.x+100,posdes1.y+100,0x000);
	Line(ecran,posdes2.x,posdes2.y,posdes2.x+100,posdes2.y,0x000);
	Line(ecran,posdes2.x,posdes2.y,posdes2.x,posdes2.y+100,0x000);
	Line(ecran,posdes2.x+100,posdes2.y,posdes2.x+100,posdes2.y+100,0x000);
	Line(ecran,posdes2.x,posdes2.y+100,posdes2.x+100,posdes2.y+100,0x000);
	
	SDL_Flip(ecran);
}

/* permet de renvoyer dans dest le nom du fichier du dés correspondant a num */
void choix_des(char *dest, int num){
	strcpy(dest, "images_bmp/de_");
	char c[2];
	sprintf(c,"%d",num);
	strcat(dest,c);
	strcat(dest,".bmp");
}

/* affichage des textes de base de l'ecran de jeu */
void texte_base(SDL_Surface *ecran, SDL_Rect position, SDL_Surface *texte){
	TTF_Font *police=NULL;
	SDL_Color noire={0,0,0};
	police=TTF_OpenFont("police/liberation/LiberationSans-BoldItalic.ttf",20);
	texte=TTF_RenderText_Blended(police,"Proprietes : ",noire);
	position.x=675;
	position.y=80;
	SDL_BlitSurface(texte,NULL,ecran,&position);
}

/* affiche les informations relatives au joueur sur la droite de l'ecran */
void infos_joueur(SDL_Surface *ecran, SDL_Rect position, SDL_Surface *texte, SDL_Surface *rectangle, PLATEAU *plateau, int j){
	TTF_Font *police=NULL;
	SDL_Color noire={0,0,0};
	police=TTF_OpenFont("police/liberation/LiberationSans-Regular.ttf",20);
	
	char chaine[20];
	char base_j[25]="Joueur : ";
	nom_joueur(chaine,j,plateau);
	strcat(base_j,chaine);
	texte=TTF_RenderText_Blended(police,base_j,noire);
	position.x=675;
	position.y=15;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	
	sprintf(chaine,"%d",compte_joueur(j,plateau));
	strcat(chaine," pp");
	char base_a[20]="Argent : ";
	strcat(base_a,chaine);
	texte=TTF_RenderText_Blended(police,base_a,noire);
	position.x=1000;
	position.y=15;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	
	texte=TTF_RenderText_Blended(police,"Couleur : ",noire);
	position.x=675;
	position.y=45;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,20,32,0,0,0,0);
	position.x=765;
	position.y=48;
	if (j==0) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,0));
	else if (j==1) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,255,0));
	else if (j==2) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,0,255));
	else if (j==3) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,15,32,0,0,0,0);
	position.x=680;
	position.y=110;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,128,64,0));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,45,32,0,0,0,0);
	position.x=680;
	position.y=125;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,15,32,0,0,0,0);
	position.x=750;
	position.y=110;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,255,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,45,32,0,0,0,0);
	position.x=750;
	position.y=125;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,15,32,0,0,0,0);
	position.x=820;
	position.y=110;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,45,32,0,0,0,0);
	position.x=820;
	position.y=125;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,15,32,0,0,0,0);
	position.x=890;
	position.y=110;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,128,0));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,45,32,0,0,0,0);
	position.x=890;
	position.y=125;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,15,32,0,0,0,0);
	position.x=960;
	position.y=110;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,0));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,45,32,0,0,0,0);
	position.x=960;
	position.y=125;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,15,32,0,0,0,0);
	position.x=1030;
	position.y=110;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,0));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,45,32,0,0,0,0);
	position.x=1030;
	position.y=125;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,15,32,0,0,0,0);
	position.x=1100;
	position.y=110;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,255,0));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,45,32,0,0,0,0);
	position.x=1100;
	position.y=125;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,15,32,0,0,0,0);
	position.x=820;
	position.y=180;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,0,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,45,32,0,0,0,0);
	position.x=820;
	position.y=195;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,60,32,0,0,0,0);
	position.x=890;
	position.y=180;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	texte=TTF_RenderText_Blended(police,"Gares",noire);
	position.x=920-texte->w/2;
	position.y=180;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,60,32,0,0,0,0);
	position.x=960;
	position.y=180;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	texte=TTF_RenderText_Blended(police,"Comp.",noire);
	position.x=990-texte->w/2;
	position.y=180;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	
	int i;
	for (i=0;i<7;i++){
		Line(ecran,680+i*70,110,740+i*70,110,0x000);
		Line(ecran,680+i*70,110,680+i*70,170,0x000);
		Line(ecran,680+i*70,170,740+i*70,170,0x000);
		Line(ecran,740+i*70,110,740+i*70,170,0x000);
	}
	for (i=0;i<3;i++){
		Line(ecran,820+i*70,180,880+i*70,180,0x000);
		Line(ecran,820+i*70,180,820+i*70,240,0x000);
		Line(ecran,820+i*70,240,880+i*70,240,0x000);
		Line(ecran,880+i*70,180,880+i*70,240,0x000);
	}
	
	int tab[10];
	for (i=0;i<10;i++) tab[i]=0;
	for (i=2;i<=40;i++){
		if (i!=3 && i!=5 && i!=8 && i!=11 && i!=18 && i!=21 && i!=23 && i!=31 && i!=34 && i!=37 && i!=39){
			if (proprietaire_terrain(i,plateau)==j){
				tab[type_terrain(i,plateau)]+=1;
			}
		}
	}
	ecrire_propriete(ecran,position,texte,rectangle,plateau,tab);
	
	char nb_terr[3];
	sprintf(nb_terr,"%d",nb_terrains_joueur(j,plateau));
	char base_terr[30]="Nb terrains : ";
	strcat(base_terr,nb_terr);
	texte=TTF_RenderText_Blended(police,base_terr,noire);
	position.x=675;
	position.y=300;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	
	CASE *c;
	int cpt=0;
	int t=2;
	for (c=plateau->case_depart->suivante;c!=plateau->case_depart;c=c->suivante){
		if (c->terrain!=NULL){
			if (c->terrain->proprietaire==j){
				if(test_hypotheque(t,plateau)==1){
					cpt++;	
				}
			}
		}
		t++;
	}
	char nb_hyp[3];
	sprintf(nb_hyp,"%d",cpt);
	char base_hyp[30]="Nb terrains hypotheque : ";
	strcat(base_hyp,nb_hyp);
	texte=TTF_RenderText_Blended(police,base_hyp,noire);
	position.x=675;
	position.y=330;
	SDL_BlitSurface(texte,NULL,ecran,&position);	
}

/* affiche le proprietaire de chaque terrain */
void affiche_proprietaire(SDL_Surface *ecran, SDL_Rect position, SDL_Surface *rectangle, PLATEAU *plateau, int terrain){
	int j;
	if (terrain>=2 && terrain<=10 && terrain!=3 && terrain!=5 && terrain!=8) {
		rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,10,32,0,0,0,0);
		position.x=540-(terrain-2)*60;
		position.y=618;
		j=proprietaire_terrain(terrain,plateau);
		if (j==0) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,0));
		else if (j==1) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,255,0));
		else if (j==2) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,0,255));
		else if (j==3) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,255));
		else SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,213,208,134));
		SDL_BlitSurface(rectangle,NULL,ecran,&position);	
	} else if (terrain>=12 && terrain<=20 && terrain!=18) {
		rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,10,60,32,0,0,0,0);
		position.x=31;
		position.y=540-(terrain-12)*60;
		j=proprietaire_terrain(terrain,plateau);
		if (j==0) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,0));
		else if (j==1) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,255,0));
		else if (j==2) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,0,255));
		else if (j==3) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,255));
		else SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,213,208,134));
		SDL_BlitSurface(rectangle,NULL,ecran,&position);	
	} else if (terrain>=22 && terrain<=30 && terrain!=23) {
		rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,60,10,32,0,0,0,0);
		position.x=60+(terrain-22)*60;
		position.y=31;
		j=proprietaire_terrain(terrain,plateau);
		if (j==0) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,0));
		else if (j==1) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,255,0));
		else if (j==2) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,0,255));
		else if (j==3) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,255));
		else SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,213,208,134));
		SDL_BlitSurface(rectangle,NULL,ecran,&position);	
	} else if (terrain>=32 && terrain<=40 && terrain!=34 && terrain!=37 && terrain!=39) {
		rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,10,60,32,0,0,0,0);
		position.x=618;
		position.y=60+(terrain-32)*60;
		j=proprietaire_terrain(terrain,plateau);
		if (j==0) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,0));
		else if (j==1) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,255,0));
		else if (j==2) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,0,0,255));
		else if (j==3) SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,0,255));
		else SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,213,208,134));
		SDL_BlitSurface(rectangle,NULL,ecran,&position);	
	}
}

/* fonction pour l'appui sur les boutons de l'ecran de demarrage */
int traitement_bouton_demarrage(SDL_Event *event, SDL_Rect position1, SDL_Rect position2, SDL_Rect position3, SDL_Surface *texte1, SDL_Surface *texte2, SDL_Surface *texte3){
	if (event->button.button == SDL_BUTTON_LEFT){
		if(event->button.x>position1.x && event->button.x<(position1.x+texte1->w) && event->button.y>position1.y && event->button.y<(position1.y+texte1->h)){
			return 1;
		} else if(event->button.x>position2.x && event->button.x<(position2.x+texte2->w) && event->button.y>position2.y && event->button.y<(position2.y+texte2->h)){
			return 2;
		} else if(event->button.x>position3.x && event->button.x<(position3.x+texte3->w) && event->button.y>position3.y && event->button.y<(position3.y+texte3->h)){
			return 3;
		}
		else{return 0;}
	}
	else{return 0;}
}

/* fonction pour le deplacement de la souris sur l'ecran de demarrage */
int traitement_deplacement(SDL_Event *event, SDL_Rect position1, SDL_Rect position2, SDL_Rect position3, SDL_Surface *texte1, SDL_Surface *texte2, SDL_Surface *texte3){
	if(event->motion.x>position1.x && event->motion.x<(position1.x+texte1->w) && event->motion.y>position1.y && event->motion.y<(position1.y+texte1->h)){
		return 1;
	} else if(event->motion.x>position2.x && event->motion.x<(position2.x+texte2->w) && event->motion.y>position2.y && event->motion.y<(position2.y+texte2->h)){
		return 2;
	} else if(event->motion.x>position3.x && event->motion.x<(position3.x+texte3->w) && event->motion.y>position3.y && event->motion.y<(position3.y+texte3->h)){
		return 3;
	}
	else{return 0;}
}				  

/* affiche l'ecran de demarrage */
int affiche_ecran_demarrage() {
	SDL_Surface *ecran =NULL;
	SDL_Surface *rectangle1=NULL,*rectangle2=NULL,*rectangle3=NULL;
	SDL_Surface *imageb=NULL,*imagebi=NULL,*imaged=NULL,*imagedi=NULL,*imagep=NULL;
	SDL_Surface *textenom=NULL, *textebouton1=NULL, *textebouton2=NULL, *textebouton3=NULL, *textetitre=NULL;
    SDL_Rect positionbouton1, positionbouton2, positionbouton3;
	SDL_Rect position;
	TTF_Font *police=NULL, *policebouton=NULL, *policetitre=NULL;
	SDL_Color blanc={255,255,255};
	SDL_Color rouge={255,0,0};
	SDL_Color noir={0,0,0};
	SDL_Color beige={213,208,134};
	
	/* ecran demarrage */
	if(SDL_Init(SDL_INIT_VIDEO)==-1){
		fprintf(stderr,"Erreur d'initialisation de la SDL : %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	/*ouverture ecran*/
	ecran = SDL_SetVideoMode(1180,660,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(ecran==NULL){
		fprintf(stderr,"Impossible de charger le mode video : %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	/*titre fenetre*/
	SDL_WM_SetCaption("MonopolyTech",NULL);
	
	/*coloration ecran*/
	SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,213,208,134));
	
	/* initialisation écriture */
	TTF_Init();
	
	/* affichage images */
	imageb = SDL_LoadBMP("images_bmp/bonhomme.bmp");
	imagebi = SDL_LoadBMP("images_bmp/bonhomme_inverse.bmp");
	imaged = SDL_LoadBMP("images_bmp/de_jouer_inverse.bmp");
	imagedi = SDL_LoadBMP("images_bmp/de_jouer.bmp");
	imagep = SDL_LoadBMP("images_bmp/plateau.bmp");
	policetitre=TTF_OpenFont("police/liberation/LiberationSans-Bold.ttf",40);
	police=TTF_OpenFont("police/liberation/LiberationSans-Italic.ttf",15);
	policebouton=TTF_OpenFont("police/liberation/LiberationSans-Bold.ttf",25);
	
	SDL_SetColorKey(imageb,SDL_SRCCOLORKEY,SDL_MapRGB(imageb->format,0,255,0));
	position.x=0;
    position.y=233;
	SDL_BlitSurface(imageb, NULL, ecran, &position);
	
	SDL_SetColorKey(imagebi,SDL_SRCCOLORKEY,SDL_MapRGB(imagebi->format,0,255,0));
	position.x=920;
    position.y=233;
	SDL_BlitSurface(imagebi, NULL, ecran, &position);
	
	SDL_SetColorKey(imaged,SDL_SRCCOLORKEY,SDL_MapRGB(imaged->format,0,255,0));
	position.x=120;
    position.y=70;
	SDL_BlitSurface(imaged, NULL, ecran, &position);
	
	SDL_SetColorKey(imagedi,SDL_SRCCOLORKEY,SDL_MapRGB(imagedi->format,0,255,0));
	position.x=909;
    position.y=70;
	SDL_BlitSurface(imagedi, NULL, ecran, &position);
	
	SDL_SetColorKey(imagep,SDL_SRCCOLORKEY,SDL_MapRGB(imagep->format,255,128,192));
	position.x=ecran->w /2 - imagep->w/2;
    position.y=120;
	SDL_BlitSurface(imagep, NULL, ecran, &position);
	
	textetitre=TTF_RenderText_Shaded(policetitre,"MONOPOLYTECH",blanc,rouge);
	position.x=ecran->w /2 - textetitre->w/2;
	position.y=50;
	SDL_BlitSurface(textetitre,NULL,ecran,&position);
	
	textenom=TTF_RenderText_Shaded(police,"Made by : Valentin ISAAC--CHASSANDE, Cyril POUCHOL, Johan ROVAREY, Mathis VERNAY",noir,beige);
	position.x=ecran->w-textenom->w-5;
	position.y=640;
	SDL_BlitSurface(textenom,NULL,ecran,&position);
	
	textebouton1=TTF_RenderText_Blended(policebouton,"Nouvelle partie",noir);
	positionbouton1.x=ecran->w /2 - textebouton1->w/2;
	positionbouton1.y=250;
	SDL_BlitSurface(textebouton1,NULL,ecran,&positionbouton1);
	
	textebouton2=TTF_RenderText_Blended(policebouton,"Charger partie",noir);
	positionbouton2.x=ecran->w /2 - textebouton2->w/2;
	positionbouton2.y=350;
	SDL_BlitSurface(textebouton2,NULL,ecran,&positionbouton2);
	
	textebouton3=TTF_RenderText_Blended(policebouton,"Quitter",noir);
	positionbouton3.x=ecran->w /2 - textebouton3->w/2;
	positionbouton3.y=450;
	SDL_BlitSurface(textebouton3,NULL,ecran,&positionbouton3);
	
	/*mise a jour ecran*/
	SDL_Flip(ecran); 
	
	int continuer=1, retour=0, selection=0;
	SDL_Event event;
	while (continuer){
		SDL_WaitEvent(&event);
		switch(event.type) {
			case SDL_QUIT :
				continuer=0;
				retour=0;
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (traitement_bouton_demarrage(&event,positionbouton1,positionbouton2,positionbouton3,textebouton1,textebouton2,textebouton3)){
					case 1: 
						continuer=0;
						retour=1;
						break;
					case 2 :
						continuer=0;
						retour=2;
						break;
					case 3 :
						continuer=0;
						retour=3;
						break;
				}
				break;
			case SDL_MOUSEMOTION :
				selection=traitement_deplacement(&event,positionbouton1,positionbouton2,positionbouton3,textebouton1,textebouton2,textebouton3);
				
		}
		SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,213,208,134));

		/* affichage images */
		position.x=0;
		position.y=233;
		SDL_BlitSurface(imageb, NULL, ecran, &position);

		position.x=920;
		position.y=233;
		SDL_BlitSurface(imagebi, NULL, ecran, &position);

		position.x=120;
		position.y=70;
		SDL_BlitSurface(imaged, NULL, ecran, &position);

		position.x=909;
		position.y=70;
		SDL_BlitSurface(imagedi, NULL, ecran, &position);

		position.x=ecran->w /2 - imagep->w/2;
		position.y=120;
		SDL_BlitSurface(imagep, NULL, ecran, &position);

		position.x=ecran->w /2 - textetitre->w/2;
		position.y=50;
		SDL_BlitSurface(textetitre,NULL,ecran,&position);

		position.x=ecran->w-textenom->w-5;
		position.y=640;
		SDL_BlitSurface(textenom,NULL,ecran,&position);
		
		positionbouton1.x=ecran->w /2 - textebouton1->w/2;
		positionbouton1.y=250;
		positionbouton2.x=ecran->w /2 - textebouton2->w/2;
		positionbouton2.y=350;
		positionbouton3.x=ecran->w /2 - textebouton3->w/2;
		positionbouton3.y=450;
		
		if (selection==1) {
			rectangle1=SDL_CreateRGBSurface(SDL_HWSURFACE,textebouton1->w,textebouton1->h,32,0,0,0,0);
			SDL_FillRect(rectangle1,NULL,SDL_MapRGB(ecran->format,200,0,0));
			SDL_BlitSurface(rectangle1,NULL,ecran,&positionbouton1);	
		} else if (selection==2) {
			rectangle2=SDL_CreateRGBSurface(SDL_HWSURFACE,textebouton2->w,textebouton2->h,32,0,0,0,0);
			SDL_FillRect(rectangle2,NULL,SDL_MapRGB(ecran->format,200,0,0));
			SDL_BlitSurface(rectangle2,NULL,ecran,&positionbouton2);	
		} else if (selection==3) {
			rectangle3=SDL_CreateRGBSurface(SDL_HWSURFACE,textebouton3->w,textebouton3->h,32,0,0,0,0);
			SDL_FillRect(rectangle3,NULL,SDL_MapRGB(ecran->format,200,0,0));	
			SDL_BlitSurface(rectangle3,NULL,ecran,&positionbouton3);	
		}

		SDL_BlitSurface(textebouton1,NULL,ecran,&positionbouton1);

		SDL_BlitSurface(textebouton2,NULL,ecran,&positionbouton2);

		SDL_BlitSurface(textebouton3,NULL,ecran,&positionbouton3);

		/*mise a jour ecran*/
		SDL_Flip(ecran); 
	}
	
	/* fin ecran demarrage */
	TTF_Quit();
	SDL_Quit();
	return retour;
}

/* affiche l'ecran de lancer de dés pour l'ordre de jeu */
int affiche_lancer_de(char nom[][15]){
	SDL_Surface *ecran =NULL;
	SDL_Surface *bouton = NULL;
	SDL_Surface *texte=NULL;
	SDL_Surface *imageb=NULL,*imagebi=NULL,*imaged=NULL,*imagedi=NULL;
	SDL_Rect position, positionbouton;
	SDL_Surface *des1,*des2;
	SDL_Rect posdes1,posdes2;
	
	imageb = SDL_LoadBMP("images_bmp/bonhomme.bmp");
	imagebi = SDL_LoadBMP("images_bmp/bonhomme_inverse.bmp");
	imaged = SDL_LoadBMP("images_bmp/de_jouer_inverse.bmp");
	imagedi = SDL_LoadBMP("images_bmp/de_jouer.bmp");
	SDL_SetColorKey(imageb,SDL_SRCCOLORKEY,SDL_MapRGB(imageb->format,0,255,0));
	position.x=0;
    position.y=233;
	SDL_BlitSurface(imageb, NULL, ecran, &position);
	
	SDL_SetColorKey(imagebi,SDL_SRCCOLORKEY,SDL_MapRGB(imagebi->format,0,255,0));
	position.x=920;
    position.y=233;
	SDL_BlitSurface(imagebi, NULL, ecran, &position);
	
	SDL_SetColorKey(imaged,SDL_SRCCOLORKEY,SDL_MapRGB(imaged->format,0,255,0));
	position.x=120;
    position.y=70;
	SDL_BlitSurface(imaged, NULL, ecran, &position);
	
	SDL_SetColorKey(imagedi,SDL_SRCCOLORKEY,SDL_MapRGB(imagedi->format,0,255,0));
	position.x=909;
    position.y=70;
	SDL_BlitSurface(imagedi, NULL, ecran, &position);
	
	int tab[4];
	int j1,j2,j3,j4,i;
	int *a,*b;
	a=(int *)malloc(sizeof(int));
	*a=1;
	b=(int *)malloc(sizeof(int));
	*b=1;
	char source[20];
	if(SDL_Init(SDL_INIT_VIDEO)==-1){
		fprintf(stderr,"Erreur d'initialisation de la SDL : %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	ecran = SDL_SetVideoMode(1180,660,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(ecran==NULL){
		fprintf(stderr,"Impossible de charger le mode video : %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_WM_SetCaption("MonopolyTech",NULL);
	SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,213,208,134));
	TTF_Init();
	
	posdes1.x=ecran->w/2 -125;
	posdes1.y=ecran->h/2 +100;
	posdes2.x=ecran->w/2 +25;
	posdes2.y=ecran->h/2 +100;
	TTF_Font *police=NULL;
	SDL_Color noire={0,0,0};
	SDL_Color blanc={255,255,255};
	police=TTF_OpenFont("police/liberation/LiberationSans-Regular.ttf",20);
	texte=TTF_RenderText_Blended(police,nom[0],noire);
	position.x=ecran->w/2 - texte->w/2;
	position.y=ecran->h/2 - texte->h/2 - 100;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	bouton=SDL_LoadBMP("images_bmp/bouton.bmp");
	positionbouton.x=ecran->w/2-bouton->w/2;
	positionbouton.y=ecran->h/2-bouton->h/2;
	SDL_SetColorKey(bouton,SDL_SRCCOLORKEY,SDL_MapRGB(bouton->format,255,255,255));
	SDL_BlitSurface(bouton,NULL,ecran,&positionbouton);
	texte=TTF_RenderText_Blended(police,"Lancer",blanc);
	position.x=positionbouton.x+bouton->w/2-texte->w/2;
	position.y=positionbouton.y+bouton->h/2-texte->h/2;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	
	des1=SDL_LoadBMP("images_bmp/de_1.bmp");
	des2=SDL_LoadBMP("images_bmp/de_1.bmp");
	SDL_BlitSurface(des1,NULL,ecran,&posdes1);
	SDL_BlitSurface(des2,NULL,ecran,&posdes2);
	Line(ecran,posdes1.x,posdes1.y,posdes1.x+100,posdes1.y,0x000);
	Line(ecran,posdes1.x,posdes1.y,posdes1.x,posdes1.y+100,0x000);
	Line(ecran,posdes1.x+100,posdes1.y,posdes1.x+100,posdes1.y+100,0x000);
	Line(ecran,posdes1.x,posdes1.y+100,posdes1.x+100,posdes1.y+100,0x000);
	Line(ecran,posdes2.x,posdes2.y,posdes2.x+100,posdes2.y,0x000);
	Line(ecran,posdes2.x,posdes2.y,posdes2.x,posdes2.y+100,0x000);
	Line(ecran,posdes2.x+100,posdes2.y,posdes2.x+100,posdes2.y+100,0x000);
	Line(ecran,posdes2.x,posdes2.y+100,posdes2.x+100,posdes2.y+100,0x000);
	SDL_Flip(ecran); 
	
	int continuer=0;
	int lance=0;
	SDL_Event event;
	while (continuer<4){
		SDL_WaitEvent(&event);
		switch(event.type) {
			case SDL_QUIT :
				continuer=4;
				return continuer;
				break;
			case SDL_MOUSEBUTTONUP:
				if(event.button.button == SDL_BUTTON_LEFT){
					if (event.button.x > positionbouton.x && event.button.x < positionbouton.x+bouton->w && event.button.y > positionbouton.y && 
						event.button.y < positionbouton.y+bouton->h){
						lance_des(ecran,a,b,posdes1,posdes2);
						tab[continuer]=*a+*b;
						if (continuer==0) j1=tab[continuer];
						else if (continuer==1) j2=tab[continuer];
						else if (continuer==2) j3=tab[continuer];
						else if (continuer==3) j4=tab[continuer];
						lance=1;
					}
				}
				break;
		}
		SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,213,208,134));
		texte=TTF_RenderText_Blended(police,nom[continuer],noire);
		position.x=ecran->w/2 - texte->w/2;
		position.y=ecran->h/2 - texte->h/2 - 100;
		SDL_BlitSurface(texte,NULL,ecran,&position);
		position.x=0;
		position.y=233;
		SDL_BlitSurface(imageb, NULL, ecran, &position);

		position.x=920;
		position.y=233;
		SDL_BlitSurface(imagebi, NULL, ecran, &position);

		position.x=120;
		position.y=70;
		SDL_BlitSurface(imaged, NULL, ecran, &position);

		position.x=909;
		position.y=70;
		SDL_BlitSurface(imagedi, NULL, ecran, &position);
		if (lance==1) {
			continuer++;
			lance=0;
			choix_des(source, *a);
			des1=SDL_LoadBMP(source);
			choix_des(source, *b);
			des2=SDL_LoadBMP(source);
			SDL_BlitSurface(des1,NULL,ecran,&posdes1);
			SDL_BlitSurface(des2,NULL,ecran,&posdes2);
			Line(ecran,posdes1.x,posdes1.y,posdes1.x+100,posdes1.y,0x000);
			Line(ecran,posdes1.x,posdes1.y,posdes1.x,posdes1.y+100,0x000);
			Line(ecran,posdes1.x+100,posdes1.y,posdes1.x+100,posdes1.y+100,0x000);
			Line(ecran,posdes1.x,posdes1.y+100,posdes1.x+100,posdes1.y+100,0x000);
			Line(ecran,posdes2.x,posdes2.y,posdes2.x+100,posdes2.y,0x000);
			Line(ecran,posdes2.x,posdes2.y,posdes2.x,posdes2.y+100,0x000);
			Line(ecran,posdes2.x+100,posdes2.y,posdes2.x+100,posdes2.y+100,0x000);
			Line(ecran,posdes2.x,posdes2.y+100,posdes2.x+100,posdes2.y+100,0x000);
			SDL_Flip(ecran); 
			SDL_WaitEvent(&event);
		} else {
			SDL_SetColorKey(bouton,SDL_SRCCOLORKEY,SDL_MapRGB(bouton->format,255,255,255));
			SDL_BlitSurface(bouton,NULL,ecran,&positionbouton);
			texte=TTF_RenderText_Blended(police,"Lancer",blanc);
			position.x=positionbouton.x+bouton->w/2-texte->w/2;
			position.y=positionbouton.y+bouton->h/2-texte->h/2;
			SDL_BlitSurface(texte,NULL,ecran,&position);
			choix_des(source, *a);
			des1=SDL_LoadBMP(source);
			choix_des(source, *b);
			des2=SDL_LoadBMP(source);
			SDL_BlitSurface(des1,NULL,ecran,&posdes1);
			SDL_BlitSurface(des2,NULL,ecran,&posdes2);
			Line(ecran,posdes1.x,posdes1.y,posdes1.x+100,posdes1.y,0x000);
			Line(ecran,posdes1.x,posdes1.y,posdes1.x,posdes1.y+100,0x000);
			Line(ecran,posdes1.x+100,posdes1.y,posdes1.x+100,posdes1.y+100,0x000);
			Line(ecran,posdes1.x,posdes1.y+100,posdes1.x+100,posdes1.y+100,0x000);
			Line(ecran,posdes2.x,posdes2.y,posdes2.x+100,posdes2.y,0x000);
			Line(ecran,posdes2.x,posdes2.y,posdes2.x,posdes2.y+100,0x000);
			Line(ecran,posdes2.x+100,posdes2.y,posdes2.x+100,posdes2.y+100,0x000);
			Line(ecran,posdes2.x,posdes2.y+100,posdes2.x+100,posdes2.y+100,0x000);
			SDL_Flip(ecran); 
		}
			
	}
	
	tri_rapide(tab,0,3);
	SDL_FreeSurface(bouton);
	SDL_FreeSurface(texte);
	SDL_FreeSurface(des1);
	SDL_FreeSurface(des2);
	TTF_Quit();
	SDL_Quit();
	
	int t1=0,t2=0,t3=0,t4=0;
	for (i=3;i>=0;i--){
		if (tab[i]==j1 && t1==0) {
			changer_nom_joueur(3-i,nom[0]);
			t1=1;
		} else if (tab[i]==j2 && t2==0) {
			changer_nom_joueur(3-i,nom[1]);
			t2=1;
		} else if (tab[i]==j3 && t3==0){
			changer_nom_joueur(3-i,nom[2]);
			t3=1;
		} else if (tab[i]==j4 && t4==0){
			changer_nom_joueur(3-i,nom[3]);
			t4=1;
		}		
	}
	return 1;
}

/* affiche les noms des rues sur le plateau */
void ecrire_nom_rue(SDL_Surface *ecran, SDL_Rect position, SDL_Surface *texte, PLATEAU *plateau, int rue, TTF_Font *police_p, TTF_Font *police8, TTF_Font *police9, TTF_Font *police10){
	TTF_Font *police=NULL;
	SDL_Color noire={0,0,0};
	char nom[30];
	nom_terrain(nom,rue,plateau);
	if (contient_tiret(nom)){
		char nom2[20];
		int n=0;
		gestion_tiret(nom,nom2);
		if (strlen(nom2)==0) n=1;
		if (strlen(nom)>12) police=police8;
		else if (strlen(nom)>10) police=police9;
		else police=police10;
		if (n!=1) texte=TTF_RenderText_Blended(police,nom2,noire);
		if (rue>=2 && rue<=10){
			if (n!=1){
				position.x=570-(rue-2)*60-texte->w/2;
				position.y=622;
				SDL_BlitSurface(texte,NULL,ecran,&position);
			}
			texte=TTF_RenderText_Blended(police,nom,noire);
			position.x=570-(rue-2)*60-texte->w/2;
			position.y=612;
			SDL_BlitSurface(texte,NULL,ecran,&position);
		} else if (rue>=12 && rue<=20){
			if (n!=1){
				position.x=30-texte->w/2;
				position.y=560-(rue-12)*60;
				SDL_BlitSurface(texte,NULL,ecran,&position);
			}
			texte=TTF_RenderText_Blended(police,nom,noire);
			position.x=30-texte->w/2;
			position.y=550-(rue-12)*60;
			SDL_BlitSurface(texte,NULL,ecran,&position);
		} else if (rue>=22 && rue<=30){
			if (n!=1){
				position.x=90+(rue-22)*60-texte->w/2;
				position.y=35;
				SDL_BlitSurface(texte,NULL,ecran,&position);
			}
			texte=TTF_RenderText_Blended(police,nom,noire);
			position.x=90+(rue-22)*60-texte->w/2;
			position.y=25;
			SDL_BlitSurface(texte,NULL,ecran,&position);
		} else if (rue>=32 && rue<=40){
			if (n!=1){
				position.x=630-texte->w/2;
				position.y=80+(rue-32)*60;
				SDL_BlitSurface(texte,NULL,ecran,&position);
			}
			texte=TTF_RenderText_Blended(police,nom,noire);
			position.x=630-texte->w/2;
			position.y=70+(rue-32)*60;
			SDL_BlitSurface(texte,NULL,ecran,&position);
		} else if (rue==1){
			if (n!=1){
				position.x=630-texte->w/2;
				position.y=630;
				SDL_BlitSurface(texte,NULL,ecran,&position);
			}
			texte=TTF_RenderText_Blended(police,nom,noire);
			position.x=630-texte->w/2;
			position.y=620;
			SDL_BlitSurface(texte,NULL,ecran,&position);	
		} else if (rue==11){
			if (n!=1){
				position.x=35-texte->w/2;
				position.y=630;
				SDL_BlitSurface(texte,NULL,ecran,&position);
			}
			texte=TTF_RenderText_Blended(police,nom,noire);
			position.x=35-texte->w/2;
			position.y=620;
			SDL_BlitSurface(texte,NULL,ecran,&position);	
		} else if (rue==21){
			if (n!=1){
				position.x=30-texte->w/2;
				position.y=35;
				SDL_BlitSurface(texte,NULL,ecran,&position);
			}
			texte=TTF_RenderText_Blended(police,nom,noire);
			position.x=30-texte->w/2;
			position.y=25;
			SDL_BlitSurface(texte,NULL,ecran,&position);	
		} else if (rue==31){
			if (n!=1){
				position.x=629-texte->w/2;
				position.y=35;
				SDL_BlitSurface(texte,NULL,ecran,&position);
			}
			texte=TTF_RenderText_Blended(police,nom,noire);
			position.x=629-texte->w/2;
			position.y=25;
			SDL_BlitSurface(texte,NULL,ecran,&position);	
		}
	} else {
		if (strlen(nom)>12) police=police8;
		else if (strlen(nom)>10) police=police9;
		else police=police10;
		texte=TTF_RenderText_Blended(police,nom,noire);
		if (rue>=2 && rue<=10){
			position.x=570-(rue-2)*60-texte->w/2;
			position.y=622;
		} else if (rue>=12 && rue<=20){
			position.x=30-texte->w/2;
			position.y=550-(rue-12)*60;
		} else if (rue>=22 && rue<=30){
			position.x=90+(rue-22)*60-texte->w/2;
			position.y=30;
		} else if (rue>=32 && rue<=40){
			position.x=630-texte->w/2;
			position.y=70+(rue-32)*60;
		} else if (rue==1){
			position.x=630-texte->w/2;
			position.y=615;	
		} else if (rue==11){
			position.x=35-texte->w/2;
			position.y=620;	
		} else if (rue==21){
			position.x=30-texte->w/2;
			position.y=30-texte->h/2;	
		} else if (rue==31){
			position.x=629-texte->w/2;
			position.y=29-texte->h/2;	
		}
		SDL_BlitSurface(texte,NULL,ecran,&position);
	}
	char chaine[10];
	if (rue==2 || rue==4 || rue==6 || rue==7 || rue==9 || rue==10) {
		sprintf(chaine,"%d",prix_terrain(rue,plateau));
		strcat(chaine," pp");
		texte=TTF_RenderText_Blended(police_p,chaine,noire);
		position.x=570-(rue-2)*60-texte->w/2;
		position.y=640;	
		SDL_BlitSurface(texte,NULL,ecran,&position);
	} else if ((rue>=12 && rue<=17) || rue==19 || rue==20){
		sprintf(chaine,"%d",prix_terrain(rue,plateau));
		strcat(chaine," pp");
		texte=TTF_RenderText_Blended(police_p,chaine,noire);
		position.x=30-texte->w/2;
		position.y=580-(rue-12)*60;	
		SDL_BlitSurface(texte,NULL,ecran,&position);
	} else if ((rue==22 || (rue>=24 && rue<=30))){
		sprintf(chaine,"%d",prix_terrain(rue,plateau));
		strcat(chaine," pp");
		texte=TTF_RenderText_Blended(police_p,chaine,noire);
		position.x=90+(rue-22)*60-texte->w/2;
		position.y=10;	
		SDL_BlitSurface(texte,NULL,ecran,&position);
	} else if ((rue==32 || rue==33 || rue==35 || rue==36 || rue==38 || rue==40)){
		sprintf(chaine,"%d",prix_terrain(rue,plateau));	
		strcat(chaine," pp");
		texte=TTF_RenderText_Blended(police_p,chaine,noire);
		position.x=630-texte->w/2;
		position.y=100+(rue-32)*60;		
		SDL_BlitSurface(texte,NULL,ecran,&position);
	}
}

/* teste si le mot contient un "_" ou non, renvoie 1 si oui et 0 sinon */
int contient_tiret(char *mot){
	int n=strlen(mot);
	int i;
	for (i=0;i<n;i++){
		if (mot[i]=='_') return 1;	
	}
	return 0;
}

/* separe mot en 2 si besoin au niveau du "_" */
void gestion_tiret(char *mot, char *mot2){
	int i=0;
	int j=0;
	int f=0;
	mot2[0]='\0';
	while (f==0 && i<strlen(mot)){
		if (mot[i]=='_' && i>=6) {
			mot[i]='\0';
			i+=1;
			while (mot[i]!='\0') {
				mot2[j]=mot[i];
				mot[i]='\0';
				i++;
				j++;
			}
			mot2[j]='\0';
			f=1;
		}
		i+=1;
	}
}

/* affiche l'argent de open_source au centre du plateau */
void affiche_argent_parc(SDL_Surface *ecran, SDL_Rect position, SDL_Surface *texte, int *parc_gratuit){
	TTF_Font *police=NULL;
	SDL_Color noire={0,0,0};
	police=TTF_OpenFont("police/liberation/LiberationSans-Bold.ttf",20);
	texte=TTF_RenderText_Blended(police,"Argent Open_Source",noire);
	position.x=330-texte->w/2;
	position.y=330-texte->h;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	char chaine[20];
	sprintf(chaine,"%d",*parc_gratuit);
	strcat(chaine," pp");
	texte=TTF_RenderText_Blended(police,chaine,noire);
	position.x=330-texte->w/2;
	position.y=330;
	SDL_BlitSurface(texte,NULL,ecran,&position);
}

/* affiche le nombre de proprietes sur la droite de l'ecran pour chaque couleur */
void ecrire_propriete(SDL_Surface *ecran, SDL_Rect position, SDL_Surface *texte, SDL_Surface *rectangle, PLATEAU *plateau, int *tab){
	TTF_Font *police=NULL;
	SDL_Color noire={0,0,0};
	police=TTF_OpenFont("police/liberation/LiberationSans-Regular.ttf",20);
	char chaine[3];
	int i;
	for (i=0;i<7;i++){
		sprintf(chaine,"%d",tab[i]);
		texte=TTF_RenderText_Blended(police,chaine,noire);
		position.x=710+i*70-texte->w/2;
		position.y=147-texte->h/2;
		SDL_BlitSurface(texte,NULL,ecran,&position);
	}
	
	sprintf(chaine,"%d",tab[7]);
	texte=TTF_RenderText_Blended(police,chaine,noire);
	position.x=850-texte->w/2;
	position.y=217-texte->h/2;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	
	sprintf(chaine,"%d",tab[8]);
	texte=TTF_RenderText_Blended(police,chaine,noire);
	position.x=920-texte->w/2;
	position.y=217-texte->h/2;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	
	sprintf(chaine,"%d",tab[9]);
	texte=TTF_RenderText_Blended(police,chaine,noire);
	position.x=990-texte->w/2;
	position.y=217-texte->h/2;
	SDL_BlitSurface(texte,NULL,ecran,&position);
}

/* affichage des infos de la case sur laquelle le joueur est */
void affiche_infos_case(SDL_Surface *ecran, SDL_Rect position, SDL_Surface *texte, SDL_Surface *rectangle, PLATEAU *plateau, int rue, int joueur){
	rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,300,150,32,0,0,0,0);
	position.x=180;
	position.y=75;
	SDL_FillRect(rectangle,NULL,SDL_MapRGB(ecran->format,255,255,255));
	SDL_BlitSurface(rectangle,NULL,ecran,&position);
	
	TTF_Font *police=NULL;
	SDL_Color noire={0,0,0};
	police=TTF_OpenFont("police/liberation/LiberationSans-Regular.ttf",20);
	char chaine_p[10];
	char chaine_j[15];
		
	nom_terrain(chaine_p,rue,plateau);
	texte=TTF_RenderText_Blended(police,chaine_p,noire);
	position.x=330-texte->w/2;
	position.y=75;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	
	if (rue!=1 && rue!=3 && rue!=5 && rue!=8 && rue!=11 && rue!=18 && rue!=21 && rue!=23 && rue!=31 && rue!=34 && rue!=37 && rue!=39){
		sprintf(chaine_p,"%d",prix_terrain(rue,plateau));
		strcat(chaine_p," pp");
		char base[20]="Prix : ";
		strcat(base,chaine_p);
		texte=TTF_RenderText_Blended(police,base,noire);
		position.x=183;
		position.y=100;
		SDL_BlitSurface(texte,NULL,ecran,&position);
		
		char base_p[40]="Proprietaire : ";
		int j=proprietaire_terrain(rue,plateau);
		if (j==-1) copie_string("/",chaine_j);
		else nom_joueur(chaine_j,j,plateau);
		strcat(base_p,chaine_j);
		texte=TTF_RenderText_Blended(police,base_p,noire);
		position.x=183;
		position.y=130;
		SDL_BlitSurface(texte,NULL,ecran,&position);
	} else {
		char base[40]="Prix : /";
		texte=TTF_RenderText_Blended(police,base,noire);
		position.x=183;
		position.y=100;
		SDL_BlitSurface(texte,NULL,ecran,&position);
		
		char base_p[40]="Proprietaire : /";
		texte=TTF_RenderText_Blended(police,base_p,noire);
		position.x=183;
		position.y=130;
		SDL_BlitSurface(texte,NULL,ecran,&position);
	}
	sprintf(chaine_p,"%d",nb_maisons(rue,plateau));
	char base_m[30]="Nb maisons : ";
	strcat(base_m,chaine_p);
	texte=TTF_RenderText_Blended(police,base_m,noire);
	position.x=183;
	position.y=160;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	
	sprintf(chaine_p,"%d",loyer(joueur,rue,plateau));
	char base_l[30]="Loyer : ";
	strcat(base_l,chaine_p);
	texte=TTF_RenderText_Blended(police,base_l,noire);
	position.x=183;
	position.y=190;
	SDL_BlitSurface(texte,NULL,ecran,&position);
}

/* renvoie differents messages d'erreur en fonction de e */
void erreur(int e){
	SDL_Surface *ecran =NULL;
	SDL_Surface *texte=NULL;
	SDL_Rect position;
	
	if(SDL_Init(SDL_INIT_VIDEO)==-1){
		fprintf(stderr,"Erreur d'initialisation de la SDL : %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	ecran = SDL_SetVideoMode(350,40,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(ecran==NULL){
		fprintf(stderr,"Impossible de charger le mode video : %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	SDL_WM_SetCaption("Erreur",NULL);
	
	SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,213,208,134));
	
	TTF_Init();
	TTF_Font *police=NULL;
	SDL_Color noir={0,0,0};
	SDL_Color beige={213,208,134};
	police=TTF_OpenFont("police/liberation/LiberationSans-Regular.ttf",15);
	if (e==1) texte=TTF_RenderText_Shaded(police,"La sauvegarde doit se faire en debut de tour !",noir,beige);
	else if (e==2) texte=TTF_RenderText_Shaded(police,"Tu ne possedes pas la carte !",noir,beige);
	position.x=ecran->w/2-texte->w/2;
	position.y=ecran->h/2-texte->h/2;
	SDL_BlitSurface(texte,NULL,ecran,&position);
	SDL_Flip(ecran);
	
	int continuer=1;
	SDL_Event event;
	while (continuer){
		SDL_WaitEvent(&event);
		switch(event.type) {
			case SDL_QUIT :
				continuer=0;
				break;
		}
	}
}

/* demande a l'utilisateur si il veut acheter le terrain, renvoie 1 si oui et 0 sinon */
int choix_achat_terrain(PLATEAU *plateau, int pos, int joueur_courant){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
	int retour;
	
    SDL_Surface *ecran = NULL, *boutton1 = NULL, *boutton2 = NULL, *texte1 = NULL, *texte2 = NULL, *texte3=NULL, *texte4=NULL, *solde=NULL;
    SDL_Rect positionbouton1, positionbouton2, p_texte1, p_texte2, p_texte3, p_texte4, p_solde;

    TTF_Font *police = NULL;
    police = TTF_OpenFont("police/arial/arial_narrow_7.ttf", 24);
    
    SDL_Color Noir = {0,0,0};
    
    positionbouton1.x =400/4-140/2; /*a ajuster*/
	positionbouton2.x =positionbouton1.x+200; /*a ajuster*/
    positionbouton1.y = 200-70;
	positionbouton2.y = positionbouton1.y;
    
    boutton1 = SDL_CreateRGBSurface(SDL_HWSURFACE, 150,40,32,0,0,0,0);
    SDL_FillRect(boutton1,NULL,SDL_MapRGB(boutton1->format,239,243,73));
	boutton2 = SDL_CreateRGBSurface(SDL_HWSURFACE, 150,40,32,0,0,0,0);
    SDL_FillRect(boutton2,NULL,SDL_MapRGB(boutton2->format,239,243,73));
	
	char chaine[20];
	char tempory_string[60];
	nom_terrain(chaine,pos,plateau);
    
    texte1 = TTF_RenderText_Blended(police,"Oui", Noir);
	texte2 = TTF_RenderText_Blended(police,"Non", Noir);
	texte3 = TTF_RenderText_Blended(police,chaine, Noir);
	sprintf(chaine,"%d pp",prix_terrain(pos,plateau));
	texte4 = TTF_RenderText_Blended(police,chaine, Noir);
	
    sprintf(tempory_string,"solde dispo : %d pp",compte_joueur(joueur_courant,plateau));
    solde=TTF_RenderText_Blended(police,tempory_string, Noir);

    p_texte1.x = positionbouton1.x+boutton1->w/2-texte1->w/2;
    p_texte1.y = positionbouton1.y+boutton1->h/2-texte1->h/2;
	p_texte2.x = positionbouton2.x+boutton2->w/2-texte2->w/2;
    p_texte2.y = positionbouton2.y+boutton2->h/2-texte2->h/2;
	p_texte3.x = 20;
	p_texte3.y = 20;
	p_texte4.x = p_texte3.x;
	p_texte4.y = p_texte3.y+texte3->h+5;
	p_solde.x = p_texte4.x;
	p_solde.y = p_texte4.y+texte4->h+5;

    ecran = SDL_SetVideoMode(400, 200, 32, SDL_HWSURFACE);
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 213, 208, 134));
	
    SDL_WM_SetCaption("Voulez-vous acheter ce terrain ?", NULL);
   
    /* On blitte par-dessus l'écran */
    SDL_BlitSurface(boutton1, NULL, ecran, &positionbouton1);
    SDL_BlitSurface(texte1, NULL, ecran, &p_texte1);
	SDL_BlitSurface(boutton2, NULL, ecran, &positionbouton2);
    SDL_BlitSurface(texte2, NULL, ecran, &p_texte2);
    SDL_BlitSurface(texte3, NULL, ecran, &p_texte3);
    SDL_BlitSurface(texte4, NULL, ecran, &p_texte4);
    SDL_BlitSurface(solde, NULL, ecran, &p_solde);
    SDL_Flip(ecran);

    /*Variable fin d'attende evenement sdl*/
    SDL_bool init_j_lauch = SDL_TRUE;
       
    while(init_j_lauch){
		SDL_Event event;
		
        /*Boucle sur les evenements*/
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_MOUSEBUTTONDOWN:
					if(verification_zone(&event,positionbouton1.x ,positionbouton1.y ,boutton1->w,boutton1->h) == 1){
                        retour = 1;
                        init_j_lauch = SDL_FALSE;
                    }
					if(verification_zone(&event,positionbouton2.x ,positionbouton2.y ,boutton2->w,boutton2->h) == 1){
                        retour = 0;
                        init_j_lauch = SDL_FALSE;
                    }
					break;
				case SDL_QUIT:
					break;
				default:
					break;
			}
		}
    }
	
    SDL_FreeSurface(texte1);
    SDL_FreeSurface(boutton1);
	SDL_FreeSurface(texte2);
    SDL_FreeSurface(boutton2);
	SDL_FreeSurface(texte3);
	SDL_FreeSurface(texte4);
	SDL_FreeSurface(solde);
    SDL_Quit();

	return retour;
}

/* demande a l'utilisateur ce qu'il veut vendre si il est ruiné, (1) maisons, (2) terrain, (3) carte sortie prison */
int si_joueur_ruine(){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
	int retour;
	
    SDL_Surface *ecran = NULL, *boutton1 = NULL, *boutton2 = NULL, *boutton3 = NULL, *texte1 = NULL, *texte2 = NULL, *texte3 = NULL;
    SDL_Rect positionbouton1, positionbouton2, positionbouton3, p_texte1, p_texte2, p_texte3;

    TTF_Font *police = NULL;
    police = TTF_OpenFont("police/arial/arial_narrow_7.ttf", 24);
    
    SDL_Color Noir = {0,0,0};
	
	positionbouton1.x =400/2-340/2;
    positionbouton1.y =200-180;
    positionbouton2.x =400/2-340/2;
    positionbouton2.y =200-120;
    positionbouton3.x =400/2-340/2;
    positionbouton3.y =200-60;
    
    boutton1 = SDL_CreateRGBSurface(SDL_HWSURFACE, 340,40,32,0,0,0,0);
    SDL_FillRect(boutton1,NULL,SDL_MapRGB(boutton1->format,239,243,73));
	boutton2 = SDL_CreateRGBSurface(SDL_HWSURFACE, 340,40,32,0,0,0,0);
    SDL_FillRect(boutton2,NULL,SDL_MapRGB(boutton2->format,239,243,73));
	boutton3 = SDL_CreateRGBSurface(SDL_HWSURFACE, 340,40,32,0,0,0,0);
    SDL_FillRect(boutton3,NULL,SDL_MapRGB(boutton3->format,239,243,73));
    
    texte1 = TTF_RenderText_Blended(police,"Vendre une maison", Noir);
	texte2 = TTF_RenderText_Blended(police,"Hypothequer un terrain", Noir);
	texte3 = TTF_RenderText_Blended(police,"Vendre la carte sortie de prison", Noir);

    p_texte1.x = positionbouton1.x+boutton1->w/2-texte1->w/2;
    p_texte1.y = positionbouton1.y+boutton1->h/2-texte1->h/2;
	p_texte2.x = positionbouton2.x+boutton2->w/2-texte2->w/2;
    p_texte2.y = positionbouton2.y+boutton2->h/2-texte2->h/2;
	p_texte3.x = positionbouton3.x+boutton3->w/2-texte3->w/2;
    p_texte3.y = positionbouton3.y+boutton3->h/2-texte3->h/2;

    ecran = SDL_SetVideoMode(400, 200, 32, SDL_HWSURFACE);
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 213, 208, 134));
	
    SDL_WM_SetCaption("Vous etes ruinés ! Que voulez-vous faire ?", NULL);

    /* Chargement d'une image Bitmap dans une surface */
   
    /* On blitte par-dessus l'écran */
    SDL_BlitSurface(boutton1, NULL, ecran, &positionbouton1);
    SDL_BlitSurface(texte1, NULL, ecran, &p_texte1);
	SDL_BlitSurface(boutton2, NULL, ecran, &positionbouton2);
    SDL_BlitSurface(texte2, NULL, ecran, &p_texte2);
	SDL_BlitSurface(boutton3, NULL, ecran, &positionbouton3);
    SDL_BlitSurface(texte3, NULL, ecran, &p_texte3);
    SDL_Flip(ecran);

    /*Variable fin d'attende evenement sdl*/
    SDL_bool init_j_lauch = SDL_TRUE;
       
    while(init_j_lauch){
		SDL_Event event;
		
        /*Boucle sur les evenements*/
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_MOUSEBUTTONDOWN:
					if(verification_zone(&event,positionbouton1.x ,positionbouton1.y ,boutton1->w,boutton1->h) == 1){
                        retour = 0;
                        init_j_lauch = SDL_FALSE;
                    }
					if(verification_zone(&event,positionbouton2.x ,positionbouton2.y ,boutton2->w,boutton2->h) == 1){
                        retour = 1;
                        init_j_lauch = SDL_FALSE;
                    }
					if(verification_zone(&event,positionbouton3.x ,positionbouton3.y ,boutton3->w,boutton3->h) == 1){
                        retour = 2;
                        init_j_lauch = SDL_FALSE;
                    }
					break;
				case SDL_QUIT:
					break;
				default:
					break;
			}
		}
    }
	
    SDL_FreeSurface(texte1);
    SDL_FreeSurface(boutton1);
	SDL_FreeSurface(texte2);
    SDL_FreeSurface(boutton2);
	SDL_FreeSurface(texte3);
    SDL_FreeSurface(boutton3);
    SDL_Quit();

	return retour;
}

/* affiche l'action a effectuer en fonction de action */
void action_carte(int action, int somme, char *t){
	SDL_Surface *ecran =NULL;
	SDL_Surface *texte=NULL;
	SDL_Rect position;
	
	if(SDL_Init(SDL_INIT_VIDEO)==-1){
		fprintf(stderr,"Erreur d'initialisation de la SDL : %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	ecran = SDL_SetVideoMode(350,40,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(ecran==NULL){
		fprintf(stderr,"Impossible de charger le mode video : %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	SDL_WM_SetCaption("Action carte chance",NULL);
	
	SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,213,208,134));
	
	TTF_Init();
	TTF_Font *police=NULL;
	SDL_Color noir={0,0,0};
	SDL_Color beige={213,208,134};
	police=TTF_OpenFont("police/liberation/LiberationSans-Regular.ttf",15);
	
	char chaine_g[10];
	char chaine_p[10];
	char gagnez[20]="Gagnez ";
	char payez[20]="Payez ";
	char allez[30]="Allez a la case ";
	
	if (action==1){
		texte=TTF_RenderText_Shaded(police,"Reculez de 3 cases",noir,beige);
		position.x=ecran->w/2-texte->w/2;
		position.y=ecran->h/2-texte->h/2;
		SDL_BlitSurface(texte,NULL,ecran,&position);
	} else if (action==2){
		sprintf(chaine_g,"%d",somme);
		strcat(chaine_g," pp");
		strcat(gagnez,chaine_g);
		texte=TTF_RenderText_Shaded(police,gagnez,noir,beige);
		position.x=ecran->w/2-texte->w/2;
		position.y=ecran->h/2-texte->h/2;
		SDL_BlitSurface(texte,NULL,ecran,&position);
	} else if (action==3){
		sprintf(chaine_p,"%d",somme);
		strcat(chaine_p," pp");
		strcat(payez,chaine_p);
		texte=TTF_RenderText_Shaded(police,payez,noir,beige);
		position.x=ecran->w/2-texte->w/2;
		position.y=ecran->h/2-texte->h/2;
		SDL_BlitSurface(texte,NULL,ecran,&position);
	} else if (action==4){
		texte=TTF_RenderText_Shaded(police,"Allez en prison",noir,beige);
		position.x=ecran->w/2-texte->w/2;
		position.y=ecran->h/2-texte->h/2;
		SDL_BlitSurface(texte,NULL,ecran,&position);
	} else if (action==5){
		strcat(allez,t);
		texte=TTF_RenderText_Shaded(police,allez,noir,beige);
		position.x=ecran->w/2-texte->w/2;
		position.y=ecran->h/2-texte->h/2;
		SDL_BlitSurface(texte,NULL,ecran,&position);
	} else if (action==6){
		strcat(allez,t);
		texte=TTF_RenderText_Shaded(police,allez,noir,beige);
		position.x=ecran->w/2-texte->w/2;
		position.y=ecran->h/2-texte->h;
		SDL_BlitSurface(texte,NULL,ecran,&position);
		texte=TTF_RenderText_Shaded(police,"sans passer par la case depart",noir,beige);
		position.x=ecran->w/2-texte->w/2;
		position.y=ecran->h/2;
		SDL_BlitSurface(texte,NULL,ecran,&position);
	} else if (action==7){
		texte=TTF_RenderText_Shaded(police,"Reparation maisons 40pp et hotel 115pp",noir,beige);
		position.x=ecran->w/2-texte->w/2;
		position.y=ecran->h/2-texte->h/2;
		SDL_BlitSurface(texte,NULL,ecran,&position);
	} else if (action==8){
		texte=TTF_RenderText_Shaded(police,"Reparation maisons 25pp et hotel 100pp",noir,beige);
		position.x=ecran->w/2-texte->w/2;
		position.y=ecran->h/2-texte->h/2;
		SDL_BlitSurface(texte,NULL,ecran,&position);
	} else if (action==9){
		texte=TTF_RenderText_Shaded(police,"Carte sortie prison obtenue",noir,beige);
		position.x=ecran->w/2-texte->w/2;
		position.y=ecran->h/2-texte->h/2;
		SDL_BlitSurface(texte,NULL,ecran,&position);	
	}
	
	SDL_Flip(ecran);
	
	int continuer=1;
	SDL_Event event;
	while (continuer){
		SDL_WaitEvent(&event);
		switch(event.type) {
			case SDL_QUIT :
				continuer=0;
				break;
		}
	}
}

/* affichage pour demander a l'utilisateur si il veut racheter un terrain hypothequé, renvoie 1 si oui et 0 sinon */
int rachat_hypotheque(PLATEAU *plateau, int pos, int joueur_courant){
	SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
	int retour;
	
    SDL_Surface *ecran = NULL, *boutton1 = NULL, *boutton2 = NULL, *texte1 = NULL, *texte2 = NULL, *texte3=NULL, *texte4=NULL, *solde=NULL;
    SDL_Rect positionbouton1, positionbouton2, p_texte1, p_texte2, p_texte3, p_texte4, p_solde;

    TTF_Font *police = NULL;
    police = TTF_OpenFont("police/arial/arial_narrow_7.ttf", 24);
    
    SDL_Color Noir = {0,0,0};
    
    positionbouton1.x =400/4-140/2; /*a ajuster*/
	positionbouton2.x =positionbouton1.x+200; /*a ajuster*/
    positionbouton1.y = 200-70;
	positionbouton2.y = positionbouton1.y;
    
    boutton1 = SDL_CreateRGBSurface(SDL_HWSURFACE, 150,40,32,0,0,0,0);
    SDL_FillRect(boutton1,NULL,SDL_MapRGB(boutton1->format,239,243,73));
	boutton2 = SDL_CreateRGBSurface(SDL_HWSURFACE, 150,40,32,0,0,0,0);
    SDL_FillRect(boutton2,NULL,SDL_MapRGB(boutton2->format,239,243,73));
	
	char chaine[20];
	char tempory_string[60];
	nom_terrain(chaine,pos,plateau);
    
    texte1 = TTF_RenderText_Blended(police,"Oui", Noir);
	texte2 = TTF_RenderText_Blended(police,"Non", Noir);
	texte3 = TTF_RenderText_Blended(police,chaine, Noir);
	sprintf(chaine,"%d pp",valeur_hypothequaire(pos,plateau));
	texte4 = TTF_RenderText_Blended(police,chaine, Noir);
	
    sprintf(tempory_string,"solde dispo : %d pp",compte_joueur(joueur_courant,plateau));
    solde=TTF_RenderText_Blended(police,tempory_string, Noir);

    p_texte1.x = positionbouton1.x+boutton1->w/2-texte1->w/2;
    p_texte1.y = positionbouton1.y+boutton1->h/2-texte1->h/2;
	p_texte2.x = positionbouton2.x+boutton2->w/2-texte2->w/2;
    p_texte2.y = positionbouton2.y+boutton2->h/2-texte2->h/2;
	p_texte3.x = 20;
	p_texte3.y = 20;
	p_texte4.x = p_texte3.x;
	p_texte4.y = p_texte3.y+texte3->h+5;
	p_solde.x = p_texte4.x;
	p_solde.y = p_texte4.y+texte4->h+5;

    ecran = SDL_SetVideoMode(400, 200, 32, SDL_HWSURFACE);
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 213, 208, 134));
	
    SDL_WM_SetCaption("Voulez-vous racheter l'hypotheque ?", NULL);
   
    /* On blitte par-dessus l'écran */
    SDL_BlitSurface(boutton1, NULL, ecran, &positionbouton1);
    SDL_BlitSurface(texte1, NULL, ecran, &p_texte1);
	SDL_BlitSurface(boutton2, NULL, ecran, &positionbouton2);
    SDL_BlitSurface(texte2, NULL, ecran, &p_texte2);
    SDL_BlitSurface(texte3, NULL, ecran, &p_texte3);
    SDL_BlitSurface(texte4, NULL, ecran, &p_texte4);
    SDL_BlitSurface(solde, NULL, ecran, &p_solde);
    SDL_Flip(ecran);

    /*Variable fin d'attende evenement sdl*/
    SDL_bool init_j_lauch = SDL_TRUE;
       
    while(init_j_lauch){
		SDL_Event event;
		
        /*Boucle sur les evenements*/
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_MOUSEBUTTONDOWN:
					if(verification_zone(&event,positionbouton1.x ,positionbouton1.y ,boutton1->w,boutton1->h) == 1){
                        retour = 1;
                        init_j_lauch = SDL_FALSE;
                    }
					if(verification_zone(&event,positionbouton2.x ,positionbouton2.y ,boutton2->w,boutton2->h) == 1){
                        retour = 0;
                        init_j_lauch = SDL_FALSE;
                    }
					break;
				case SDL_QUIT:
					break;
				default:
					break;
			}
		}
    }
	
    SDL_FreeSurface(texte1);
    SDL_FreeSurface(boutton1);
	SDL_FreeSurface(texte2);
    SDL_FreeSurface(boutton2);
	SDL_FreeSurface(texte3);
	SDL_FreeSurface(texte4);
	SDL_FreeSurface(solde);
    SDL_Quit();

	return retour;	
}

