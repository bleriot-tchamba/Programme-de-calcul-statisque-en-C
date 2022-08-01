#include <stdio.h>
#include <stdlib.h>

//DECLARATION DES STRUCTURES

typedef struct Element Element;
struct Element
{
    int nombre;
    Element *suivant;
};

typedef struct Liste Liste;
struct Liste
{
    Element *premier;
};

Liste *initialisation();
Liste *initialisation2();
void insertion(Liste *liste,int nvNombre);
void suppression(Liste *liste);
void afficherListe(Liste *liste);
void suppressionEnQue(Liste *liste);
void insertionEnQue(Liste *liste,int nvNombre);




int main()
{
    int nbre=1,aux,count,compteur=0,compte=0,compteur3=1;
    int effectifTotal=0,mode=0,aux1=0,aux2=0,somEffCumCroissant=0,somEffCumDecroissant=0;
    double somEffFoisMod=0,moyenne=0,variance,somEffMoinsMoyAuCarre=0,ecart_Type=0,deux=2,mediane=0;

    printf("\n");
    printf("                           ---------SERIE STATISTIQUE----------                       \n\n");
    printf("   Apres avoir entrer les modalites, vous devez taper '-1':\n\n");
    printf("   Veuillez entrer les differentes modalites:\t");


   Liste *maListe=initialisation();
   Liste *modalites=initialisation2();
   Liste *effectifs=initialisation2();
   Liste *EffCumCroissant=initialisation2();
   Liste *EffCumDecroissant=initialisation2();


   Element *c;
   Element *d;
   Element *e;
   Element *pointeurModalites;
   Element *pointeurEffectifs;
   Element *med;



   //ON RECUPERE LES ELEMENTS DE LA LISTE CHAINEE TOUT EN LES CLASSANT PAR ORDRE DECROISSANT

   do
   {
        scanf("  %d",&nbre);
        compteur=compteur+1;
        insertion(maListe,nbre);
        c=maListe->premier;

        nbre=nbre+1;
        while(1)
        {
            if(c == NULL || c->suivant == NULL)
                break;


            if(!(c->nombre < c->suivant->nombre))
                break;


            aux = c->nombre;
            c->nombre = c->suivant->nombre;
            c->suivant->nombre = aux;
            c = c->suivant;

        }
   }while((nbre-1)!=-1);
   suppressionEnQue(maListe);
   printf("\n\n");


   //CALCUL DE LA MEDIANE

    med=maListe->premier;


    if(compteur%2 == 1)
    {
        compte=(compteur/2)+1;
        while(compteur3!=compte)
        {
            med = med->suivant;
            compteur3 = compteur3 +1;
        }
        mediane = med->nombre;
    }
    if(compteur%2 == 0)
     {
         compte=compteur/2;
         while(compteur3!=compte)
        {
            med = med->suivant;
            compteur3 = compteur3 +1;
        }
        mediane = (med->nombre + med->suivant->nombre)/deux;

     }


   //TABLEAU DES EFFECTIFS
   d = maListe->premier;
   e = maListe->premier->suivant;
   while(d!=NULL)
   {
       if(d->nombre!= -1)
       {

           insertion(modalites,d->nombre);
           count=1;
           e=d->suivant;
           while(e != NULL)
           {
               if(e->nombre == d->nombre)
               {
                   count=count+1;
                   e->nombre=-1;
               }
                 e=e->suivant;

           }
            d->nombre = -1;
           insertion(effectifs,count);
       }
                  d = d->suivant;

   }
      suppressionEnQue(modalites);
      suppressionEnQue(effectifs);


   printf("  Modalites:                ");
   afficherListe(modalites);
   printf("\n\n");
   printf("  effectifs:                ");
   afficherListe(effectifs);
   printf("\n\n");


   //EFFECTIFS CUMULES CROISSANTS

    pointeurEffectifs=effectifs->premier;

    while(pointeurEffectifs!=NULL)
    {
       somEffCumCroissant = somEffCumCroissant + pointeurEffectifs->nombre;
       insertionEnQue(EffCumCroissant,somEffCumCroissant);
       pointeurEffectifs = pointeurEffectifs->suivant;
    }
    suppression(EffCumCroissant);
    printf("  effectifs cum crois:      ");
    afficherListe(EffCumCroissant);
    printf("\n\n");


    //EFFECTIFS CUMULES DECROISSANTS

    pointeurEffectifs=effectifs->premier;
    insertionEnQue(EffCumDecroissant,somEffCumCroissant);

    while(pointeurEffectifs!=NULL)
    {
        somEffCumCroissant = somEffCumCroissant - pointeurEffectifs->nombre;
        insertionEnQue(EffCumDecroissant,somEffCumCroissant);
        pointeurEffectifs = pointeurEffectifs->suivant;
    }
    suppression(EffCumDecroissant);
    suppressionEnQue(EffCumDecroissant);
    printf("  effectifs cum decrois:    ");
    afficherListe(EffCumDecroissant);
    printf("\n\n");






   //CALCUL DE LA MOYENNE

   pointeurModalites=modalites->premier;
   pointeurEffectifs=effectifs->premier;

   while(pointeurModalites!=NULL && pointeurEffectifs!=NULL)
   {
       somEffFoisMod = somEffFoisMod + ((pointeurEffectifs->nombre)*(pointeurModalites->nombre));
       pointeurModalites=pointeurModalites->suivant;
       pointeurEffectifs=pointeurEffectifs->suivant;
   }

    pointeurEffectifs=effectifs->premier;


    while(pointeurEffectifs!=NULL)
   {
       effectifTotal = effectifTotal + (pointeurEffectifs->nombre);
       pointeurEffectifs=pointeurEffectifs->suivant;
   }


   moyenne=somEffFoisMod/effectifTotal;
   printf("  la moyenne de cette serie statistique est:%lf\n\n",moyenne);

   //CALCUL DE LA VARIANCE

   pointeurEffectifs=effectifs->premier;
   pointeurModalites=modalites->premier;


    while(pointeurModalites!=NULL && pointeurEffectifs!=NULL)
   {
       somEffMoinsMoyAuCarre = somEffMoinsMoyAuCarre + pointeurEffectifs->nombre * (((pointeurModalites->nombre)-moyenne)*((pointeurModalites->nombre)-moyenne));
       pointeurEffectifs=pointeurEffectifs->suivant;
       pointeurModalites=pointeurModalites->suivant;
   }

   variance=somEffMoinsMoyAuCarre/effectifTotal;
   printf("  la variance de cette serie statistique est:%lf\n\n",variance);

   //CALCUL DE L'ECART-TYPE

   ecart_Type = sqrt(variance);
   printf("  l'ecart-type de cette serie statistique est:%lf\n\n",ecart_Type);


   //CALCUL DU MODE

   pointeurModalites=modalites->premier;
   pointeurEffectifs=effectifs->premier;


   while(pointeurModalites!=NULL && pointeurEffectifs!=NULL)
   {

      if(pointeurEffectifs == NULL || pointeurEffectifs->suivant == NULL)
        break;

      if(pointeurModalites == NULL || pointeurModalites->suivant == NULL)
        break;

      if(pointeurEffectifs->nombre > pointeurEffectifs->suivant->nombre)
        {
            aux1 = pointeurEffectifs->nombre;
            pointeurEffectifs->nombre = pointeurEffectifs->suivant->nombre;
            pointeurEffectifs->suivant->nombre = aux1;

            aux2 = pointeurModalites->nombre;
            pointeurModalites->nombre = pointeurModalites->suivant->nombre;
            pointeurModalites->suivant->nombre = aux2;
        }
        pointeurEffectifs = pointeurEffectifs->suivant;
        pointeurModalites = pointeurModalites->suivant;
   }

    mode=pointeurModalites->nombre;
    printf("  le mode de cette serie statistique est:%d\n\n",mode);
    printf("la mediane de cette serie statistique est %lf\n\n",mediane);






    return 0;
}

Liste *initialisation()
{
    int b;
    Liste *liste=malloc(sizeof(*liste));
    Element *element=malloc(sizeof(*element));
    if(liste==NULL)
    {
        exit(EXIT_FAILURE);
    }
    scanf("%d",&b);
    element->nombre=b;
    element->suivant=NULL;
    liste->premier=element;
    return liste;

}

void insertion(Liste *liste,int nvNombre)
{
    //CREATION DU NOUVEL ELEMENT
    Element *nouveau=malloc(sizeof(*nouveau));
    if(liste == NULL||nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->nombre=nvNombre;

    //INSERTION DE L'ELELMENT AU DEBUT DE LA LISTE
    nouveau->suivant=liste->premier;
    liste->premier=nouveau;
}

void suppression(Liste *liste)
{
   if(liste==NULL)
    {
        exit(EXIT_FAILURE);
    }
   if(liste->premier!=NULL)
    {
        Element *aSupprimer=liste->premier;
        liste->premier=liste->premier->suivant;
        free(aSupprimer);
    }
}

void afficherListe(Liste *liste)
{
  if(liste==NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *actuel=liste->premier;
    while(actuel!=NULL)
    {
        printf("%-3d     ",actuel->nombre);
        actuel=actuel->suivant;
    }
}


Liste *initialisation2()
{
    Liste *liste=malloc(sizeof(*liste));
    Element *element=malloc(sizeof(*element));
    if(liste==NULL)
    {
        exit(EXIT_FAILURE);
    }
    element->nombre=0;
    element->suivant=NULL;
    liste->premier=element;
    return liste;

}

void suppressionEnQue(Liste *liste)
{


    Element *aux=NULL;
    Element *o=NULL;
    Element *m=liste->premier;

    while(m->suivant!=NULL)
    {

        aux=m;
        m=m->suivant;
    }
    o=m;
    aux->suivant=NULL;
    free(o);

}

void insertionEnQue(Liste *liste,int nvNombre)
{
    Element *aux=NULL;
    Element *m=liste->premier;

    Element *nouveau=malloc(sizeof(*nouveau));
    if(liste == NULL||nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    while(m->suivant!=NULL)
    {
        aux = m;
        m = m->suivant;
    }
    nouveau->nombre = nvNombre;
    nouveau->suivant = NULL;

    m->suivant = nouveau;

}






