
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
enum state{main_menu,louer_system,voiture_system};
enum state currentwindow=main_menu;
typedef struct date{
    int mouth;
    int day;
    int year;
}date;
typedef struct voiture {
    int idVoiture;
    char matricule[30];
    char etat[30]; //dispo,en pqnne,louee...
    char couleur[30];
    int prixjour;

}voiture;


typedef struct locataire{
    int idClient;
    char nom[30];

}locataire;
// structure    CONTRAT //
typedef struct contratLocation
{
    float numContrat;
    int idVoiture;
    int idClient;
    date debut;
    date  fin;
    int   cout;
}contrat;





// Fonction pour afficher les voitures disponibles
void voituresDisponibles() {
    FILE *fichier = fopen("voiture.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier voiture.txt");
        return;
    }

    voiture v;
    printf("Voitures disponibles :\n");
    printf("---------------------------------------------------\n");
    printf("ID   Matricule    etat   Couleur   Prix            \n");
    printf("---------------------------------------------------\n");

    while (fscanf(fichier, "%d %49s %49s %19s %d ",
                  &v.idVoiture, v.matricule, v.etat, v.couleur,
                   &v.prixjour) == 5) {

        if (strcmp(v.etat, "disponible") == 0) {
            printf("%-6d %-12s %-10s %-8s %-6d \n",
                   v.idVoiture, v.matricule, v.etat, v.couleur,
                    v.prixjour);
        }
    }

    printf("---------------------------------------------------\n");

    fclose(fichier);
}

// Fonction pour louer une voiture par ID
void louer() {
    voituresDisponibles();  // Affiche la liste des voitures disponibles

    int idLocation;
    printf("Saisir l'ID de la voiture à louer : ");
    scanf("%d", &idLocation);

    FILE *fichierLecture = fopen("voiture.txt", "r");
    FILE *fichierEcriture = fopen("voituretemp.txt", "w");

    if (fichierLecture == NULL || fichierEcriture == NULL) {
        perror("Erreur lors de l'ouverture des fichiers");
        return;
    }

    voiture v;
    int voitureTrouvee = 0;

    while (fscanf(fichierLecture, "%d %49s %49s %19s %d",
                  &v.idVoiture, v.matricule, v.etat, v.couleur,
                   &v.prixjour) == 5) {
        if (v.idVoiture == idLocation && strcmp(v.etat, "enpanne") != 0) {
            voitureTrouvee = 1;
            printf("Voiture louée avec succés :\n");
            printf("ID       : %d\n", v.idVoiture);
            printf("Matricule  : %s\n", v.matricule);
            printf("Etat  : louee\n");
            printf("Couleur  : %s\n", v.couleur);
            printf("Prix/Jour: %d\n", v.prixjour);

            fprintf(fichierEcriture, "%d %s %s %s %d \n",
                    v.idVoiture, v.matricule, "louee", v.couleur,
                    v.prixjour);

            FILE *contratFile = fopen("contrat.txt", "a");  
            if (contratFile != NULL) {

                fprintf(contratFile, "%d %s %s %d\n", v.idVoiture , v.matricule,v.couleur,v.prixjour);
                fclose(contratFile);  
            } else {
                perror("Erreur lors de l'ouverture du fichier contrat.txt");
            }
        } else {
            fprintf(fichierEcriture, "%d %s %s %s %d \n",
                    v.idVoiture, v.matricule, v.etat, v.couleur,
                     v.prixjour);
        }
    }

    fclose(fichierLecture);
    fclose(fichierEcriture);

    
    if (remove("voiture.txt") == 0 && rename("voituretemp.txt", "voiture.txt") == 0) {
        if (!voitureTrouvee) {
            printf("Aucune voiture disponible avec l'ID %d ou d�j� lou�e.\n", idLocation);
        }
    } else {
        perror("Erreur lors de la suppression ou du renommage des fichiers");
    }
}



// affichage d'une voiture a partir de son id
void afficher(int idRecherche) {
    FILE *fichier = fopen("voiture.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier voiture.txt");
        return;
    }

    voiture v;
    int trouve = 0;

    while (fscanf(fichier, "%d %s %s %s %d",
                  &v.idVoiture, v.matricule, v.etat, v.couleur,
                   &v.prixjour) == 5) {
        if (v.idVoiture == idRecherche) {
            trouve = 1;
            printf("Informations de la voiture avec l'ID %d :\n", idRecherche);
            printf("ID       : %d\n", v.idVoiture);
            printf("Matricule  : %s\n", v.matricule);
            printf("Etat  : %s\n", v.etat);
            printf("Couleur  : %s\n", v.couleur);
            printf("Prix/Jour: %d\n", v.prixjour);

            break;
        }
    }

    fclose(fichier);

    if (!trouve) {
        printf("Aucune voiture trouv�e avec l'ID %d\n", idRecherche);
    }
}

void exit_system()
{
    printf("\t\tSortir...\n\t\t aucun enregistement \n\n\t\tPress \"Entrer/Retourner\" Pour sortir");
    char exitprog;
    fflush(stdin);
    scanf("%c",&exitprog);
}



void afficherliste() {
    FILE* fichier = NULL;
    char chaine[400] = "";
    fichier = fopen("voiture.txt", "r");

    if (fichier != NULL) {
        while (fgets(chaine, 400, fichier) != NULL) {
            voiture v;
            sscanf(chaine, "%d %29s %29s %29s %d",
                   &v.idVoiture, v.matricule, v.etat, v.couleur, &v.prixjour);

            
            printf("ID: %d, Matricule: %s, Etat: %s, Couleur: %s, Prix/Jour: %d\n",
                   v.idVoiture, v.matricule, v.etat, v.couleur, v.prixjour);
        }
        fclose(fichier);
    } else {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier voiture.txt\n");
    }
}




//  la fonction supprimerVoituresEnPanne
void supprimerVoituresEnPanne() {
    int idToRemove;
    printf("Saisir l'ID de la voiture en panne � supprimer : ");
    scanf("%d", &idToRemove);

    voiture v;
    FILE *fichier, *f;

    fichier = fopen("voiture.txt", "r");
    f = fopen("voituretemp.txt", "w");

    if (fichier == NULL || f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    int voitureTrouvee = 0;

    while (fscanf(fichier, "%d %s %s %s %d", &v.idVoiture, v.matricule, v.etat, v.couleur, &v.prixjour) == 5) {
        if (v.idVoiture == idToRemove && strcmp(v.etat, "enpanne") == 0) {
            voitureTrouvee = 1;
            continue; 
        }

        fprintf(f, "%d %s %s %s %d\n", v.idVoiture, v.matricule, v.etat, v.couleur, v.prixjour);
    }

    fclose(fichier);
    fclose(f);

    
    if (remove("voiture.txt") != 0) {
        perror("Erreur lors de la suppression du fichier");
        exit(EXIT_FAILURE);
    }

    
    if (rename("voituretemp.txt", "voiture.txt") != 0) {
        perror("Erreur lors du renommage du fichier");
        exit(EXIT_FAILURE);
    }

    if (voitureTrouvee) {
        printf("Suppression réussie.\n");
    } else {
        printf("Aucune voiture en panne trouvée avec l'ID %d.\n", idToRemove);
    }
}

//  fonction modifierV
void modifierV(voiture *v) {
    FILE *file1, *file2;
    float idvoiture;
    printf("Saisir l' id du voiture � modifier : ");
    scanf("%f", &idvoiture);
    file2 = fopen("voiturehelp.txt", "a");
    file1 = fopen("voiture.txt", "r+");

    while (fscanf(file1, "%d %s %s %s %d", &v->idVoiture, v->matricule, v->etat, v->couleur, &v->prixjour) == 5) {
        if (idvoiture != v->idVoiture) {
            fprintf(file2, "%d %s %s %s %d\n", v->idVoiture, v->matricule, v->etat, v->couleur, v->prixjour);
        } else {
            idvoiture = v->idVoiture;
            printf("Saisir le nouveau id\n");
            scanf("%d", &v->idVoiture);
            printf("Entrer la nouvelle matricule\n");
            scanf("%s", v->matricule);
            printf("Entrer nouveau couleur\n");
            scanf("%s", v->couleur);
            printf("Entrer le nouveau etat de la voiture\n");
            scanf("%s", v->etat);
            printf("Entrer nouveau prix du jour\n");
            scanf("%d", &v->prixjour);
            fprintf(file2, "%d %s %s %s %d\n", v->idVoiture, v->matricule, v->etat, v->couleur, v->prixjour);
        }

        if (feof(file1)) {
            break; 
        }
    }

    fclose(file1);
    fclose(file2);
    remove("voiture.txt");
    rename("voiturehelp.txt", "voiture.txt");
    printf("FELICITATION\n");
}



// la fonction ajouter voiture //
void ajouterV() {
    voiture v;

    printf("Entrer l'id du voiture : ");
    scanf("%d", &v.idVoiture);
    printf("Entrer la matricule : ");
    scanf("%s", &v.matricule);
    printf("Entrer la couleur : ");
    scanf("%s", &v.couleur);
    printf("Entrer l'etat : ");
    scanf("%s", &v.etat);
    printf("Entrer le prixjour : ");
    scanf("%d", &v.prixjour);


    FILE* fichier = fopen("voiture.txt", "a");
    if (fichier != NULL) {
        fprintf(fichier,  "%d %s %s %s %d\n",
                v.idVoiture,v.matricule, v.etat, v.couleur, v.prixjour);
        fclose(fichier);
        printf("Voiture ajout�e avec succ�s.\n");
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}



// la fonction pour visualiser les informations contenus dans un contrat //
void visualiserContrat(contrat *C){

int numcontrat;

 printf(">>>>>>>>>>>>>>>>> CONTRAT DE LOCATION D UNE VOITURE <<<<<<<<<<<<<<");
printf("saisir le numero du contrat a visualiser\n");
scanf("%d",&numcontrat);

FILE *fichier=fopen("contrat.txt","r");
if(fichier == NULL){
printf("Erreur\n");
}else{
            do{
                  fscanf(fichier,"%d %d %s   %d/%d/%d   %d/%d/%d   %d\n",&C->numContrat,&C->idVoiture,&C->idClient,&C->debut,
                  &C->fin,&C->cout);
                  if(numcontrat == C->numContrat){
                  fprintf(fichier,"Le numero du contrat est   :%d\n",C->numContrat);
                  fprintf(fichier,"L' id du voiture est       :%d\n",C->idVoiture);
                  fprintf(fichier,"L' id du client est        :%d\n",C->idClient);
                  fprintf(fichier,"La date du debut est       :%d/%d/%d\n",C->debut);
                  fprintf(fichier,"La date du fin est         :%d/%d/%d\n",C->fin);
                  fprintf(fichier,"Le cout est                :%d\n",C->cout);
                  }

            }while(!feof(fichier));
fclose(fichier);
}
}


// Fonction pour afficher l'historique des locations
void afficherHistoriqueLocations() {
    FILE *fichier = fopen("contrat.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier contrat.txt");
        return;
    }

    contrat C;
    printf("Historique des locations :\n");
    printf("-------------------------------------------------------------\n");
    printf("Num Contrat  Voiture ID  Client ID  Debut       Fin         Cout\n");
    printf("-------------------------------------------------------------\n");

    while (fscanf(fichier, "%f %d %d %d %d %d %d %d %d %d ",
                  &C.numContrat, &C.idVoiture, &C.idClient,
                  &C.debut.mouth, &C.debut.day, &C.debut.year,
                  &C.fin.mouth, &C.fin.day, &C.fin.year, &C.cout) == 10) {
        printf("%-12.2f %-10d %-11d %02d %02d %04d %02d %02d %04d %-6d\n",
               C.numContrat, C.idVoiture, C.idClient,
               C.debut.mouth, C.debut.day, C.debut.year,
               C.fin.mouth, C.fin.day, C.fin.year, C.cout);
    }

    printf("-------------------------------------------------------------\n");

    fclose(fichier);
}


// la fonction REMPLIR CONTRAT //
void remplircontrat()
{   
    contrat l;

    printf("Donner le numero de loueur : \n");
    scanf("%f",&l.numContrat);
    printf("Donner le id de voiture : \n");
    scanf("%d",&l.idVoiture);
    printf("Donner le id de client: \n");
    scanf("%d",&l.idClient);
    printf("Donner la debut de location : \n");
    scanf("%d",&l.debut);
    printf("Donner la fin de location : \n");
    scanf("%d",&l.fin);
    printf("Donner le cout de location : \n");
    scanf("%d",&l.cout);
    FILE *fichier=fopen("contrat.txt","a");
if (fichier != NULL) {
        fprintf(fichier,  "%d %s %s %s %d\n",
                l.numContrat, l.idVoiture,l.idClient, l.debut, l.fin, l.cout);
        fclose(fichier);
        printf("contrat ajout�e avec succ�s.\n");
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}

//la fonction main /:


void main(){
    while(1)
    {


         int n,a,b,c,choix;
          contrat C;
          voiture v;
          int test1=1;
          int test2=1;
         


  printf("===================================================\n \n");
  printf("            Menu Principal            \n \n \n");
  printf("===================================================\n \n");
  printf("    Location............................. 1 \n");
  printf("    Gestion voitures..................... 2 \n");
  printf("    Quitter.............................. 4 \n");
  printf("    \n \n \n");
  printf("                   votre choix : ");
  scanf("%d",&n);
  printf("    \n \n \n");
   switch(n){
       case 1:
                currentwindow=louer_system;
                system("CLS");
                break;
             //LOCATION D UNE VOITURE //

       case 2:

             currentwindow=voiture_system;
              system("CLS");
              break;


        case 4:
            exit_system();
            exit(0);
        	break;


}

if(currentwindow==louer_system)
{
      while(test1)
              {

             printf("             \n  \n ");
             printf("\n           Visualiser contrat ................ 1 \n");
             printf("\n           Louer voiture ..................... 2 \n");
             printf("\n           Remplir contrat..  ................ 3 \n");
             printf("\n           Historiques contrat ............... 4 \n");
             printf("\n           Retour ........... ................ 5 \n");
             printf("\n \n \n ");
             printf("                            Votre choix :   ");
             scanf("%d",&a);
             printf("    \n \n \n");
              


             switch(a)
                   {
                   	  case 1:
                           visualiserContrat(&C);
                            system("PAUSE");
                            system("CLS");
                   	      break;
                      case 2:
                         louer();
                         system("PAUSE");
                         system("CLS");
                          break;
                      case 3:
                            remplircontrat();
                            system("PAUSE");
                            system("CLS");
                          break;
                      case 4:
                           afficherHistoriqueLocations();
                         break;
                      case 5:
                     currentwindow=main_menu;
                     test1=0;
                     system("CLS");
                         break;


            }}}

else if (currentwindow==voiture_system){
      while(test2)
            {
             printf("\n=============================================\n");
             printf("               GESTION DES VOITURES              ");
             printf("\n=============================================\n");

             printf(">>> Veuillez Choisir l'une de ces commandes : \n\n");
             printf("Liste des voitures...................... 1\n");
             printf("Ajouter voiture ........................ 2\n");
             printf("Modifier voiture ....................... 3\n");
             printf("Supprimer voiture en panne  ............ 4\n");
             printf("RETOUR ................................. 5");

             printf("\n=============================================");


            printf("\n \t \t           Votre choix :   ");
            scanf("%d",&choix);
            printf("\n");
            printf("\n ");

            



               switch(choix)
                 {
                  case 1:
                      afficherliste();
                        system("PAUSE");
                         system("CLS");
                      break;
                  case 2:
                      ajouterV();
                         system("PAUSE");
                         system("CLS");
                      break;
                  case 3:
                      modifierV(&v);
                         system("PAUSE");
                         system("CLS");
                      break;
                  case 4:
                       supprimerVoituresEnPanne();
                         system("PAUSE");
                         system("CLS");
                      break;
                  case 5:
                    currentwindow=main_menu;
                    test2=0;
                    system("CLS");
                    break;


               }}

}




}

          }




