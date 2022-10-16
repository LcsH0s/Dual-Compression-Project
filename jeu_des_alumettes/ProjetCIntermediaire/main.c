#include <stdio.h>
#include <stdlib.h>

void bienvenue(){
    printf("                        **********************\n                        * Jeu des allumettes *\n                        **********************\n\nBonjour et bienvenue dans le jeu des allumettes.\n\nVous allez avoir 3 menus.\nVous choisirez d'abord si vous voulez voir les règles du jeu ou non, puis le nombre d'allumettes à utiliser, et enfin le nombre de joueurs.\n\nsh: pause: not found\nsh: cls: not found\n\n  Que faire ?\n\n1 - Jouer\n2 - Voir les règles du jeu\n3 - Voir les crédits\n4 - Quitter\n\nVotre choix : ");
}

void voirLesReglesDuJeu(){
    printf("\nLe but du jeu est simple :\n\nCe jeu se joue à deux, vous avez un nombre n d'allumettes.\nÀ tour de rôle, chacun des deux joueurs enlève entre 1 et 3 allumettes selon ce qu'il souhaite.\nLe perdant est celui qui doit enlever la dernière allumette.\n\nAttention, il existe 2 niveaux de difficulté en version humain vs ordi.\nLe 1er est plutôt simple à battre, donc pour les débutants. Mais le dernier...\nContactez-moi si vous avez réussi (screenshot évidemment ^^), mon e-mail est dans les crédits.");
}

void voirLesCredits(){
    printf("\nLe jeu a été codé par Samy LATEB, étudiant en 3ème année d'École d'Ingénieur à l'ESIEA et en apprentissage au sein du Ministère des Armées.\nAfin de me contacter, mon mail est : lateb@et.esiea.fr\nMerci d'avoir joué à mon jeu.");
}

int quitter(){
    return 0;
}

void jouer() {
    char pseudo[100];
    char niveau[100];
    int mode;
    int allumettesAEnlever;
    printf("Bienvenue dans le jeu de l'allumette !\nQuel est ton prénom ? : ");
    scanf("%s", &pseudo);
    printf("\n\nBonjour %s.\nIl existe deux niveaux : le niveau naïf (niveau 1), et le niveau expert (niveau 2).\nQuel niveau choisis-tu pour affronter l'ordinateur ?\nTon choix : ",
           pseudo);
    scanf("%s", &niveau);

    // En cas de sélection du niveau Naïf
    if (niveau == "naif" || niveau == "Naïf" || niveau == "naif" || niveau == "Naif", niveau) {
        char allumettes[20] = {'|'};
        for (int i = 0; i < sizeof(allumettes); i++) {
            printf("%s ", allumettes);
        }
        printf("        Il reste %d allumettes.", sizeof(allumettes));
        printf("\nVous devez me donner un entier compris entre 1 et %d.\nCombien prenez-vous d'allumettes ? ", sizeof(allumettes));
        scanf("%d", &allumettesAEnlever);
        int nbAllumettesRestantes = sizeof(allumettes) - allumettesAEnlever;
        // Exception à générer en cas de prise supérieure ou égale au nombre d'allumettes restantes.
        if (allumettesAEnlever >= nbAllumettesRestantes){
            printf("Erreur ! Prise invalide : %d\nRecommencez !", allumettesAEnlever);
            // à compléter.
        }
        printf("\n%s prend %d allumette(s).\n", pseudo, allumettesAEnlever);
        printf("%s - Nombre d'allumettes à enlever : %d\n", pseudo, allumettesAEnlever);
        for(int i = 0; i < nbAllumettesRestantes; i++){
            printf("%s ", allumettes);
        }
        // Générer un nombre aléatoire entre 1 et le nombre d'allumettes maximal à l'instant t
        int nbAleatoireAllumettesOrdinateur = rand()%nbAllumettesRestantes;
        // Nombre d'allumettes restantes APRES que l'ordinateur ait joué
        int nbAllumettesRestantesVersusOrdinateur = nbAllumettesRestantes - nbAleatoireAllumettesOrdinateur;
        printf("        Il reste %d allumettes.", nbAllumettesRestantes);
        printf("\nAu tour d'Ordinateur.\nOrdinateur prend %d allumette(s).", nbAleatoireAllumettesOrdinateur);
        printf("\nNombre d'allumettes restantes : %d\nAu tour de %s.\nCombien prenez-vous d'allumettes ? ", nbAllumettesRestantesVersusOrdinateur, pseudo);
        scanf("%d", &allumettesAEnlever);

        /* TO DO LIST

         Exception à générer si le joueur ou l'ordinateur choisi plus d'allumettes qu'il n'en reste sur le jeu
         Créer une boucle While : tant que le nombre d'allumettes est supérieur strictement à 1, continuer de faire jouer le joueur et l'ordinateur.
         Lorsque le nombre d'allumettes restantes == 1, le "dernier" joueur à jouer est perdant.
         La sélection du mode Expert*/
    }
}

void selectionMenu(){
    int choix, choix2, choix3;
    bienvenue();
    scanf("%d", &choix);
    if(choix == 1){
        jouer();
    }
    if (choix == 4){
        quitter();
    }
    else if(choix == 2) {
        voirLesReglesDuJeu();
        printf("\n\n Que faire ?\n1 - Jouer\n2 - Voir les crédits\n3 - Quitter\nVotre choix : ");
        scanf("%d", &choix2);
        if (choix2 == 1) {
            jouer();
        } else if (choix2 == 2) {
            voirLesCredits();
            printf("\n\n Que faire ?\n1 - Jouer\n2 - Quitter\nVotre choix : ");
            scanf("%d", &choix2);
            if (choix2 == 1) {
                jouer();
            } else if (choix2 == 2) {
                quitter();
            }
        }
    }
    if (choix == 3){
        voirLesCredits();
        printf("\n\n Que faire ?\n1 - Jouer\n2 - Voir les règles du Jeu\n3 - Quitter\nVotre choix : ");
        scanf("%d", &choix2);
        if (choix2 == 1){
            jouer();
        }
        else if(choix2 == 2){
            voirLesReglesDuJeu();
            printf("\n\n Que faire ?\n1 - Jouer\n2 - Quitter\nVotre choix : ");
            scanf("%d", &choix3);
            if (choix3 == 1){
                jouer();
            }
            else if(choix3 == 2){
                quitter();
            }
        }
    }
}

int main() {
    selectionMenu();
}