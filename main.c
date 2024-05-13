#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_BILLETS 100
#define NOM_FICHIER "billets_avion.txt"

struct Billet {
    int numeroBillet;
    char nomPassager[50];
    char depart[50];
    char destination[50];
    float prix;
    int quantite;
};

struct Billet billets[MAX_BILLETS];
int numBillets = 0;

// Prototypes de fonctions
void ajouterBillet(const char *nomPassager, const char *depart, const char *destination, float prix, int quantite);
void supprimerBillet(int numeroBillet);
void sauvegarderBilletsDansFichier();
void chargerBilletsDepuisFichier();
void afficherBillets();
void rechercherBillet();
void modifierBillet();
void calculerPrixTotal();
int validerEntier();
float validerFlottant();

int main() {
    chargerBilletsDepuisFichier(); // Charger les donnees des billets existants depuis le fichier, le cas echeant

    int choix;
    do {
        printf("\nSysteme de Gestion de Billets d'Avion\n");
        printf("1. Ajouter un Billet\n");
        printf("2. Supprimer un Billet\n");
        printf("3. Afficher les Billets\n");
        printf("4. Rechercher un Billet\n");
        printf("5. Modifier un Billet\n");
        printf("6. Calculer le Prix Total\n");
        printf("7. Sauvegarder les Billets dans un Fichier\n");
        printf("8. exit\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                char nomPassager[50], depart[50], destination[50];
                float prix;
                int quantite;
                printf("Entrez le Nom du Passager : ");
                scanf("%s", nomPassager);
                printf("Entrez le Depart : ");
                scanf("%s", depart);
                printf("Entrez la Destination : ");
                scanf("%s", destination);
                printf("Entrez le Prix : ");
                prix = validerFlottant();
                printf("Entrez la Quantite : ");
                quantite = validerEntier();
                ajouterBillet(nomPassager, depart, destination, prix, quantite);
                break;
            }
            case 2: {
                int numeroBillet;
                printf("Entrez le Numero du Billet a supprimer : ");
                numeroBillet = validerEntier();
                supprimerBillet(numeroBillet);
                break;
            }
            case 3:
                afficherBillets();
                break;
            case 4:
                rechercherBillet();
                break;
            case 5:
                modifierBillet();
                break;
            case 6:
                calculerPrixTotal();
                break;
            case 7:
                sauvegarderBilletsDansFichier();
                break;
            case 8:
                printf("Programme termine.\n");
                break;
            default: 
                printf("choix invalid\n");
        }
    } while (choix != 8);

    return 0;
}

void ajouterBillet(const char *nomPassager, const char *depart, const char *destination, float prix, int quantite) {
    if (numBillets < MAX_BILLETS) {
        // Trouver le numero de billet maximum
        int maxNumeroBillet = 0;
        for (int i = 0; i < numBillets; i++) {
            if (billets[i].numeroBillet > maxNumeroBillet) {
                maxNumeroBillet = billets[i].numeroBillet;
            }
        }

        // Assigner le prochain numero de billet disponible
        billets[numBillets].numeroBillet = maxNumeroBillet + 1;
        strcpy(billets[numBillets].nomPassager, nomPassager);
        strcpy(billets[numBillets].depart, depart);
        strcpy(billets[numBillets].destination, destination);
        billets[numBillets].prix = prix;
        billets[numBillets].quantite = quantite;
        numBillets++; // Incrementer numBillets ici
        printf("Billet ajoute avec succes.\n");
    } else {
        printf("Impossible d'ajouter le billet. Nombre maximum de billets atteint.\n");
    }
}


void supprimerBillet(int numeroBillet) {
    int i, trouve = 0;
    for (i = 0; i < numBillets; i++) {
        if (billets[i].numeroBillet == numeroBillet) {
            trouve = 1;
            break;
        }
    }
    if (trouve) {
        for (; i < numBillets - 1; i++) {
            billets[i] = billets[i + 1];
        }
        numBillets--;
        printf("Billet supprime avec succes.\n");
    } else {
        printf("Billet non trouve.\n");
    }
}

void sauvegarderBilletsDansFichier() {
    FILE *fichier = fopen(NOM_FICHIER, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour l'ecriture. Creation d'un nouveau fichier...\n");
        fichier = fopen(NOM_FICHIER, "w+");
        if (fichier == NULL) {
            printf("Erreur lors de la creation du fichier. Veuillez verifier les autorisations ou le chemin du fichier.\n");
            return;
        }
    }

    for (int i = 0; i < numBillets; i++) {
        fprintf(fichier, "%d,%s,%s,%s,%.2f,%d\n", billets[i].numeroBillet, billets[i].nomPassager, billets[i].depart, billets[i].destination, billets[i].prix, billets[i].quantite);
    }

    fclose(fichier);
    printf("Billets sauvegardes dans le fichier avec succes.\n");
}

void chargerBilletsDepuisFichier() {
    FILE *fichier = fopen(NOM_FICHIER, "r");
    if (fichier == NULL) {
        printf("Aucune donnee de billet existante.\n");
        return;
    }

    numBillets = 0;
    while (fscanf(fichier, "%d,%[^,],%[^,],%[^,],%f,%d\n", &billets[numBillets].numeroBillet, billets[numBillets].nomPassager, billets[numBillets].depart, billets[numBillets].destination, &billets[numBillets].prix, &billets[numBillets].quantite) != EOF) {
        numBillets++;
    }

    fclose(fichier);
    printf("Billets charges depuis le fichier avec succes.\n");
}

void afficherBillets() {
    printf("Num Billet\t | Nom du Pass\t | Depart\t | Destination\t | Prix\t | Quantite\n");
    for (int i = 0; i < numBillets; i++) {
        printf("\t%d\t | %s\t | %s\t | %s\t | %.2f | %d\n", billets[i].numeroBillet, billets[i].nomPassager, billets[i].depart, billets[i].destination, billets[i].prix, billets[i].quantite);
    }
}

void rechercherBillet() {
    int choix, numeroBillet;
    char chaineRecherche[50];
    while (true){
        printf("Rechercher par :\n");
        printf("1. Numero de Billet\n");
        printf("2. Nom du Passager\n");
        printf("3. Depart\n");
        printf("4. Destination\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);
        if (choix >= 1 && choix <= 4)
        {
            break;
        };   
        printf("choix invalid\n");
} 
     ;
    

    switch (choix) {
        case 1:
            printf("Entrez le Numero de Billet : ");
            numeroBillet = validerEntier();
            for (int i = 0; i < numBillets; i++) {
                if (billets[i].numeroBillet == numeroBillet) {
                    printf("Billet trouve :\n");
                    printf("Num Billet\t | Nom du Pass\t | Depart\t | Destination\t | Prix\t | Quantite\n");
                    printf("\t%d\t | %s\t | %s\t | %s\t | %.2f | %d\n", billets[i].numeroBillet, billets[i].nomPassager, billets[i].depart, billets[i].destination, billets[i].prix, billets[i].quantite);
                    return;
                }
            }
            printf("Billet non trouve.\n");
            break;
        case 2:
            printf("Entrez le Nom du Passager : ");
            scanf("%s", chaineRecherche);
            for (int i = 0; i < numBillets; i++) {
                if (strcmp(billets[i].nomPassager, chaineRecherche) == 0) {
                    printf("Billet trouve :\n");
                    printf("Num Billet\t | Nom du Pass\t | Depart\t | Destination\t | Prix\t | Quantite\n");
                    printf("\t%d\t | %s\t | %s\t | %s\t | %.2f | %d\n", billets[i].numeroBillet, billets[i].nomPassager, billets[i].depart, billets[i].destination, billets[i].prix, billets[i].quantite);
                    return;
                }
            }
            printf("Billet non trouve.\n");
            break;
        case 3:
            printf("Entrez le Depart : ");
            scanf("%s", chaineRecherche);
            for (int i = 0; i < numBillets; i++) {
                if (strcmp(billets[i].depart, chaineRecherche) == 0) {
                    printf("Billet trouve :\n");
                    printf("Num Billet\t | Nom du Pass\t | Depart\t | Destination\t | Prix\t | Quantite\n");
                    printf("\t%d\t | %s\t | %s\t | %s\t | %.2f | %d\n", billets[i].numeroBillet, billets[i].nomPassager, billets[i].depart, billets[i].destination, billets[i].prix, billets[i].quantite);
                    return;
                }
            }
            printf("Billet non trouve.\n");
            break;
        case 4:
            printf("Entrez la Destination : ");
            scanf("%s", chaineRecherche);
            for (int i = 0; i < numBillets; i++) {
                if (strcmp(billets[i].destination, chaineRecherche) == 0) {
                    printf("Billet trouve :\n");
                    printf("Num Billet\t | Nom du Pass\t | Depart\t | Destination\t | Prix\t | Quantite\n");
                    printf("\t%d\t | %s\t | %s\t | %s\t | %.2f | %d\n", billets[i].numeroBillet, billets[i].nomPassager, billets[i].depart, billets[i].destination, billets[i].prix, billets[i].quantite);
                    return;
                }
            }
            printf("Billet non trouve.\n");
            break;
        default:
            printf("Choix invalide.\n");
    }
}

void modifierBillet() {
    int numeroBillet, choix;
    printf("Entrez le Numero de Billet a modifier : ");
    numeroBillet = validerEntier();

    while (true) {
        printf("Modifier :\n");
        printf("1. Nom du Passager\n");
        printf("2. Depart\n");
        printf("3. Destination\n");
        printf("4. Prix\n");
        printf("5. Quantite\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        if (choix >= 1 && choix <= 5) {
            break;
        } else {
            printf("Choix invalide.\n");
        }
    }

    for (int i = 0; i < numBillets; i++) {
        if (billets[i].numeroBillet == numeroBillet) {
            switch (choix) {
                case 1:
                    printf("Entrez le nouveau Nom du Passager : ");
                    scanf("%s", billets[i].nomPassager);
                    break;
                case 2:
                    printf("Entrez le nouveau Depart : ");
                    scanf("%s", billets[i].depart);
                    break;
                case 3:
                    printf("Entrez la nouvelle Destination : ");
                    scanf("%s", billets[i].destination);
                    break;
                case 4:
                    printf("Entrez le nouveau Prix : ");
                    billets[i].prix = validerFlottant();
                    break;
                case 5:
                    printf("Entrez la nouvelle Quantite : ");
                    billets[i].quantite = validerEntier();
                    break;
                default:
                    printf("Choix invalide.\n");
            }
            printf("Billet modifie avec succes.\n");
            return;
        }
    }
    printf("Billet non trouve.\n");
}

void calculerPrixTotal() {
    float prixTotal = 0;
    for (int i = 0; i < numBillets; i++) {
        prixTotal += billets[i].prix * billets[i].quantite;
    }
    printf("Prix Total de tous les billets : %.2f\n", prixTotal);
}

int validerEntier() {
    int entree;
    while (1) {
        if (scanf("%d", &entree) != 1) {
            printf("Entree invalide. Veuillez entrer un entier : ");
            while (getchar() != '\n'); 
        } else {
            while (getchar() != '\n'); 
            return entree;
        }
    }
}


float validerFlottant() {
    float entree;
    while (1) {
        if (scanf("%f", &entree) != 1) {
            printf("Entree invalide. Veuillez entrer un nombre decimal : ");
            while (getchar() != '\n'); 
        } else {
            while (getchar() != '\n'); 
            return entree;
        }
    }
}
