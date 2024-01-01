#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <stdbool.h>
#include <limits.h>

const int TP =20;
const int TP_enfants=20;
int TP_mutant = 0;
const int bin = 6;
const double proba = 0.3;
const double proba_bis = 0.2;
const int NB_ENSEMBLES = 6;
const int NB_ELEMENTS = 7;

int sous_ensembles[NB_ENSEMBLES][NB_ELEMENTS] = {
    {1, 0, 0, 1, 0, 0, 1}, // A
    {1, 0, 0, 1, 0, 0, 0}, // B
    {0, 0, 0, 1, 1, 0, 1}, // C
    {0, 0, 1, 0, 1, 1, 0}, // D
    {0, 1, 1, 0, 0, 1, 1}, // E
    {0, 1, 0, 0, 0, 0, 1}  // F
};

void generer_individu(int **ensemble){
    int i,j;
    for(i=0;i<TP;i++){
        ensemble[i] = (int *)malloc(bin * sizeof(int));
        for(j=0;j<bin;j++){
            ensemble[i][j]=rand()%2;
        }
    }
}

void ajout_enfants(int **ensemble){
    srand(time(NULL));
    int k = (rand()%7);
    printf("\n\nNombre aleatoire : %d\n\n" , k);
    int i,j;
    int nb_pop = TP;
    for(i=0;i<TP;i=i+2){
        for(j=0;j<bin;j++){
            if(j<k){
                // ensemble[nb_pop] = (int *)malloc(bin * sizeof(int)); // Allouer de la mémoire
                // ensemble[nb_pop + 1] = (int *)malloc(bin * sizeof(int));
                ensemble[nb_pop][j] = ensemble[i+1][j];
                ensemble[nb_pop+1][j] = ensemble[i][j];
            
            }else{
                ensemble[nb_pop][j] = ensemble[i][j];
                ensemble[nb_pop+1][j] = ensemble[i+1][j];
            }
        }
        nb_pop=nb_pop+2;
    }
}

int mutation(int **ensemble){
    double resultat, resultat_bis;
    int nb_mutant = 0; // Nombre de mutants créés
    int i, j;
    srand(time(NULL));
    
    for(i = 0; i < TP + TP_enfants; i++){
        resultat = ((double)rand() / (double)RAND_MAX);
    
        if(resultat < proba){
            for(j = 0; j < bin; j++){
                resultat_bis = ((double)rand() / (double)RAND_MAX);

                if(resultat_bis < proba_bis){
                    if(ensemble[i][j] == 1){
                        ensemble[TP + TP_enfants + nb_mutant] = (int *)malloc(bin * sizeof(int));
                        ensemble[TP + TP_enfants + nb_mutant][j] = 0;
                    } else {
                        ensemble[TP + TP_enfants + nb_mutant] = (int *)malloc(bin * sizeof(int));
                        ensemble[TP + TP_enfants + nb_mutant][j] = 1;
                    }
                    nb_mutant++;
                } else {
                    ensemble[TP + TP_enfants + nb_mutant] = (int *)malloc(bin * sizeof(int));
                    ensemble[TP + TP_enfants + nb_mutant][j] = ensemble[i][j];
                }
            }
        }
    }
    return nb_mutant;
}

void score(int **ensemble) {
    int best_index = -1;
    int best = 0;
    int score;
    int flag;
    int sum[NB_ELEMENTS] = {0};
    for (int i = 0; i < TP + TP_enfants + TP_mutant; i++) {
        printf("--------------------------------------------\n\n");
        printf("Individu N°%d : ",i+1);
        for(int e=0;e<bin;e++){
            printf("%d ",ensemble[i][e]);
        }
        printf("\n\n");
        score = 0;
        flag = 0;
        for (int i = 0; i < NB_ELEMENTS; i++) {
            sum[i] = 0;
        }
        for (int j = 0; j < bin; j++) {
            if (ensemble[i][j] == 1) {
                char a = 'A' + j;
                printf("%c : ", a);
                for (int w = 0; w < NB_ELEMENTS; w++) {
                    printf("%d ", sous_ensembles[j][w]);
                    sum[w] += sous_ensembles[j][w]; 
                }
                printf("\n");
            }else{
                score++;
            }
        }
        printf("\n");
        for (int col = 0; col < NB_ELEMENTS; col++) {
            if (sum[col] == 0) {
                flag = 0;
                break; 
            }else{
                flag = 1;
            }
        }
        if (flag == 0) {
            score = INT_MIN;
            printf("\nFLOP avec un score de %d\n\n",score);
        }else {
            printf("\nSOLUTION avec un score de %d\n\n",score);
        }
        if(best<score){
            best = score;
            best_index = i; // Met à jour l'indice de l'individu avec le meilleur score
        }
    }
    if (best_index != -1) {
    printf("L'individu qui a le meilleur score est l'individu N°%d qui a un score de %d\n", best_index + 1, best);
    } else {
    printf("Aucun individu trouvé avec un score valide.\n");
    }   
    printf("Les sous ensembles de ce dernier sont : ");
    for(int i = 0; i < bin; i++)
    {
        if(ensemble[best_index][i] == 1)
        {
            char c = 'A' + i;
            printf(" %c ",c);
        }
    }
}

void afficherPop(int **tableau, int taille) {
    for (int i = 0; i < taille; i++) {
        if (i==0) printf("\nTableau Parents :\n\n");
        if (i==TP) printf("\nTableau Enfants :\n\n");
        if (i==TP+TP_enfants) printf("\nTableau Mutants :\n\n");
        if(i<9){
            printf("%d  : ",i+1);
        }else{
            printf("%d : ",i+1);
        }
        for (int j = 0; j < 6; j++) {
            printf("%d ", tableau[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    int **ensemble = (int **)malloc((TP + TP_enfants + TP_mutant) * sizeof(int *));
    for(int i = 0; i < TP + TP_enfants + TP_mutant; i++){
        ensemble[i] = (int *)malloc(bin * sizeof(int));
    }

    int taille;
    generer_individu(ensemble);
    ajout_enfants(ensemble);
    TP_mutant = mutation(ensemble);
    taille = TP + TP_enfants + TP_mutant;
    afficherPop(ensemble,taille);
    printf("La population est de : ");
    printf("%d \n\n",taille);
    score(ensemble);

    free(ensemble);
    
    

    return EXIT_SUCCESS;
}

