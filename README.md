# Algorithme-g-n-tique

Étape 1 : Représentation des individus
Chaque individu est une séquence de 6 bits. Par exemple :

Individu 1 : 110101
Individu 2 : 001000
Individu 3 : 110000
...

Étape 2 : Reproduction
Les deux individus sélectionnés subissent un croisement. Par exemple, prenons les deux individus suivants et effectuons un croisement à un point de coupure (crosspoint) :

Individu 1 : 110101
Individu 2 : 001011

Après croisement à un point de coupure (par exemple, à la 4ème position) :
Nouvel individu : 110011

Étape 3 : Mutation
La mutation peut être appliquée avec une faible probabilité. Par exemple, un bit aléatoire pourrait être inversé dans la séquence de l'individu.

Étape 4 : Génération successive
Les étapes de sélection, croisement et mutation sont répétées sur plusieurs générations, et les individus les mieux adaptés sont sélectionnés pour former de nouvelles générations.

Étape 5 : Score
Cette fonction permet de d'evaluer les individus et d'établir un score a ceux qui sont une solution au problème du Subsetsum et savoir quel sera l'individu aura le meilleur score (celui qui a le plus de 0)
