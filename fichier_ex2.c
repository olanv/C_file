#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 15

typedef struct joueur {
    char nom[SIZE];
    int nb_bateau;
}t_joueur;

t_joueur create_joueur(char *nom) {
    t_joueur joueur;
    strncpy(joueur.nom, nom, SIZE);
    joueur.nb_bateau = rand()%100;
    return joueur;
}

void afficher_joueur(t_joueur joueur) {
    printf("nom: %s\nnb bateau: %d\n", joueur.nom, joueur.nb_bateau);
}

int save_joueur(t_joueur joueur) {
    FILE *sauvegarde = fopen("sauvegarde.txt", "a");
    fwrite(&joueur, sizeof(t_joueur), 1, sauvegarde);

    if (fwrite != 0) {
        printf("content to file written successfully\n");
    } else {
        printf("error while writting to file\n");
    }

    fclose(sauvegarde);
}

int charge_joueur(t_joueur *joueur, int ind) {
    FILE * save_file = fopen("sauvegarde.txt", "r");
    if (save_file == NULL) {
        printf("err opening file\n");
        return 1;
    }

    int compt = 0;

    while(!feof(save_file)) {
        fread(joueur, sizeof(t_joueur), 1, save_file);
        compt++;
        if (compt == ind) {
            break;
        }
    } 
    fclose(save_file);

    return 0;
}



int main( int argc, char * argv[] ) {
    int choix;    

    srand(time(NULL));

    printf("pour enregistrer un nouveau joueur: 1\npour charger un joueur: 2\n");
    scanf("%d", &choix);

    if (choix == 1) {
        char name[SIZE];
        printf("Entrez le nom du nouveau joueur: ");
        scanf("%s", name);
        t_joueur new_joueur = create_joueur(name);
        save_joueur(new_joueur);
    } else {
        t_joueur retrieved_joueur;
        int ind = 0;
        printf("quel joueur (id) voulez vous ?\n");
        scanf("%d", &ind);
        charge_joueur(&retrieved_joueur, ind);
        printf("joueur charge: \n");
        afficher_joueur(retrieved_joueur);
    }

    return 0;
}