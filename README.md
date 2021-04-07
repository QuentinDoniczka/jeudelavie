# Projet jeu de la vie S3 info UFR de Strasbourg Niveau 5

Mise en pratique du fameux jeu de la vie, le choix d'une évolution dans une grille cyclique ou non, de façon dynamique,
ainsi que la gestion du vieillissement ou non de façon dynamique (une cellule présente sur la même case pendant 8 évolution meure de vieillesse)

## Tuto makefile

Une fois le tout télécharger, voici les différente commande du makefile

```sh
make
```
Permet de compilier les fichier et de récupéré l'executable main

```sh
make clean
```
Permet de supprimer tous les fichiers temporaires(fichier .o main doxygen et archive)
```sh
make dist
```
Cree une archive "NomPrénom-GoL-<version>.tar.xz"

```sh
make docs
```
Pour récupéré la documentation doxygene du projet

## Versionnage

les commit autre que les comit de sauvgarde serons accompagner d'un tag sous la forme a.b.c
'a' représente le "niveau" du jeu de la vie, suivis des nouvelle implémentation demander
'b' représente les ajout majeur, comme une nouvelle fonctionnalité et surtout a la réponse d'une question du projet
'c' représente les ajout mineur, ou les correction d'erreur (correction de fuite memoire, modification du git ignore, optimisation d'une fonction ou amélioration du rendu visuel)
Le niveau 1 commence donc a 1.0.0
