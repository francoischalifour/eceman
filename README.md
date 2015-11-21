# Eceman
*Pour Windows uniquement.*

Jeu d'arcade en C développé dans le cadre du module Algorithmique et Programmation en C.


> Inspiré par *Club Penguin Thin Ice*.

![Aperçu du jeu](https://cloud.githubusercontent.com/assets/6137112/11317974/e5aedc72-9040-11e5-93a3-4603370a117a.jpg)

## Objectifs du projet

Le projet a pour objectif de nous familiariser avec la programmation en C et ses concepts, ainsi qu'au travail de groupe. Pour gérer ce projet, nous avons utilisé [Slack](https://slack.com/) et [Git](https://git-scm.com/).

## Explication du jeu

![Accueil du jeu](https://cloud.githubusercontent.com/assets/6137112/11317972/db03d700-9040-11e5-8dae-3083988243ce.png)


### Règles du jeu

Le personnage principal, nommé Eceman, se déplace dans les 4 directions dans un univers composé de glace fine, de banquises épaisses, de murs, d'outils et d'ennemis. Le but est d'atteindre la porte de sortie du niveau le plus vite possible, en marchant sur le plus de cases possible.

Attention, une fois que le personnage marche sur une case, celle-ci fond et l'empêche de revenir en arrière.

Les règles et les informations à propos du jeu sont stockées dans le dossier `data/info/`.

### Plateau de jeu

Le plateau de jeu se présente comme une matrice de caractères de 15 lignes par 19 colonnes. Cette matrice est créée à partir d'un fichier *map* composé de caractères correspondant à un certain type de case.

### Types de cases

* Glace fine
* Glace glissante
* Banquise épaisse
* Eau
* Potion de légèreté
* Bonus de score
* Tunnel
* Trou
* Lieu d'apparition
* Porte de sortie
* Mur
* Extérieur

### Les entités

* Tondeuse
* Ennemi
* Eceman

### Les scores

A chaque fois que le joueur quitte la partie, le score s'enregistre dans un fichier. Lorsqu'il finit le jeu, on enregistre son score final dans un fichier de classements.

Les scores sont stockés dans le dossier `data/saving/`.

### L'éditeur de niveaux

Il est possible d'éditer ou de créer un niveau directement dans le jeu avec l'éditeur. Il facilite la création de niveau et permet un rendu plus productif avec son aperçu en temps réel.

![Editeur de niveaux](https://cloud.githubusercontent.com/assets/6137112/11317970/cde1e86e-9040-11e5-9262-960038d310ab.jpg)

## Graphe d'appels

![Graphe d'appels](https://cloud.githubusercontent.com/assets/6137112/11317967/b6a5730a-9040-11e5-9c61-d24553bb3d07.png)


## Notes

### Documentation
Toutes les fonctions sont entièrement documentées de la façon suivante :

```
/**
 * Change le comportement du jeu en fonction de l'arrivée du héros sur une case.
 * Cette fonction est appelée après le déplacement du joueur.
 * @param game L'état du jeu
 * @param board Le plateau de jeu
 * @param hero Le héros
 * @param entityList La liste des entités
 */
void runCaseAction(GameState* game, char board[ROWS][COLS], Eceman* hero, Entity* entityList[ENTITY_MAX]);
```


### Code Style

L'ensemble du projet respecte le [Google C++ Style Guide](https://google-styleguide.googlecode.com/svn/trunk/cppguide.html) :

```
if (condition) {
  foo;
} else {
  bar;
}
```


### Outils utilisés

* [Sublime Text](http://www.sublimetext.com/) avec les [snippets](https://github.com/francoischalifour/cpp-sublime-snippet) correspondant au Google C++ Style Guide.
* [Slack](https://slack.com/)
* [Git](https://git-scm.com/)

## Auteurs
* [François Chalifour](http://www.francoischalifour.com)
* Bertrand d'Aure
