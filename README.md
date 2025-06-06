# 🍩 Projet d'algorithmique et d'image 🍩

Dans le cadre de nos cours de programmation et algorithmie C++ et de synthèse d'image d'IMAC 1 nous avons eu l'occasion de réaliser un jeu de type Diamond digger. 

Nous avons décidé de faire notre jeu sur le thème des Simpsons. Dans la suite de ce README, nous allons donc vous présenter notre jeu : **The Simpsons The Game**. Nous allons détailler notre travail, ses spécificités et nos différents retours.

![Écran titre du jeu](/assets/images/ecranTitre.png)

## 🖥️ Système d'exploitation testé
Le code a été créé et testé sur windows 11 et macOS avec le compilateur GCC 14.2.0.


## 🍩 Présentation du jeu

### Comment y jouer
Les commandes sont assez simples pour ce jeu, nous utilisons ZQSD pour gérer les déplacements et les choix dans le menu se font à la souris. 

### L’univers du jeu 
Homer doit retrouver tous ses précieux donuts sans se faire rattraper par les membres de sa famille.
Pour ce faire, il sera prêt à tout, même à marcher sur les magnifiques parterres de fleurs. 
Mais attention ! Des mines dangereuses se cachent dans l’herbe..  

###Les sprites
Tous nos sprites (sauf le rocher pris sur internet) ont été réalisés par Louiza.
![Sprite](/assets/images/homerB1.png) ![Sprite](/assets/images/homerD1.png) ![Sprite](/assets/images/homerH1.png) ![Sprite](/assets/images/homerG1.png) ![Sprite](/assets/images/margeB1.png) ![Sprite](/assets/images/margeD1.png) ![Sprite](/assets/images/margeH1.png) ![Sprite](/assets/images/margeG1.png)

### Les sprites animés
Comme amélioration obligatoire, on a choisi de réaliser des sprites animés, on en a intégré deux : les donuts qui brillent et l’animation de “Boum” lorsque le joueur marche sur une mine. Puisque nos animations contiennent peu de frames, on a décidé de gérer l’affichage avec des vectors de textures où on change la texture affichée en fonction du temps et de l’indice du tableau.
![Sprite](/assets/images/boum1.png) ![Sprite](/assets/images/boum2.png) ![Sprite](/assets/images/boum3.png)
![Sprite](/assets/images/donut1.png) ![Sprite](/assets/images/donut2.png)

## 🗃️ Organisation du code
C’était la première fois que nous faisions un projet de cette ampleur, il a donc fallu porter une attention particulière à l’organisation du code et à la répartition des fichiers. 

Nous avons fragmenté en plusieurs fichiers .cpp les différentes parties de notre code. Les fichiers sont donc : 
- **initOpenGL :** Il regroupe plusieurs fonctions appelées pendant l’initialisation du jeu. 
- **draw_scene :** Il permet d’afficher le menu et les changements d’état du jeu.
- **draw_map :** Il gère tout ce qui est relatif à la map et les différents éléments qui la compose. 
- **draw_scene :** Il gère ce qui concerne le joueur et ses interactions. 
- **ennemies :** Il gère les ennemis et leurs déplacements.
- **texture :** Il permet de gérer les textures de tous les éléments du jeu.
- **utils.hpp :** Il permet d’utiliser les variables globales dans tous les fichiers

### draw_map.cpp
Premièrement, on crée la grille map qui est un tableau 2D de int. Ensuite, on l’améliore avec l’algo cellular automata, une fois la map. Pour finir, on ajoute aléatoirement des objets dans la grille.

Ce qui nous donne un tableau comme ceci :
![grillemap](/doc/grillemap.png)
- 0 : herbe
- 1 : fleurs
- 2 : donuts
- 3 : pièges
- 4 : fleurs écrasées
- 5 : rochers

Ensuite, il y a toutes les fonctions qui dessinent les différents blocs (drawHerbe(), drawObjet(), drawPiege()...).

Pour finir la fonction DrawMap() qui dessine les différents blocs de la map en fonction du numéro de la grilleMap.


### ennemies.cpp
Les ennemis sont des bots qui se dirigent automatiquement vers le personnage s’il leur est accessible. Pour réduire la quantité de calculs, nous avons mis en place un flow field qui permet de générer une grille de direction que les bots pourront suivre. Pour se faire : 
- On initialise la recherche avec la position du joueur
- On explore les cases adjacentes et on assigne la direction d’où l’on vient
- On répète cette étape jusqu’à avoir tout visité
- Les ennemis se dirigent en fonction de la direction assignée à la case sur laquelle ils se trouvent
- Nos personnages peuvent se déplacer en diagonale, que le mouvement vertical et horizontal ne passe pas par un bloc plein pour éviter que les bots se retrouvent bloqués dans des blocs. 






### texture.cpp
On a une fonction générale loadTexture() qui prend en paramètre un nom de fichier et un GLBI_Texture, qui va charger le sprite, créer la texture, l’attacher et fixer les paramètres.
Ensuite on initie toutes les textures avec la fonction initAllTextures(). Et pour finir la fonction applyTexture() qui va prendre en paramètre un GLBI_Texture, les coordonnées de l'objet et sa taille, elle permet d’appliquer la texture sur l’objet.


## 🛠️ Nos retours
### Difficultés rencontrées
Nous avons eu du mal à prendre en main la librairie et nous avons parfois bloqué longtemps sur des détails comme la transparence. Mais grâce aux conseils de professeurs et de nos amis, nous avons réussi à prendre en main openGL et la librairie mise à notre disposition. 
Au début, nous avons eu des problèmes de répétition dans le code, certains de nos fichiers ont pris une taille importante, c’était particulièrement le cas pour le fichier des textures. Assez rapidement, c’est devenu compliqué de s’y retrouver et nous avons créé des fonctions polyvalentes pouvant être réutilisées dans de nombreux cas. Par exemple, les fonctions suivantes ont bien réduit notre code : 
```cpp
void loadTexture(const char* filename,GLBI_Texture& texture);
void applyTexture(GLBI_Texture& texture, float x, float y, float taille);
```
La plus grande difficulté à été la gestion des variables. Nous avons réfléchi en amont des principales variables dont nous aurions besoin, mais nous n’avons pas toujours eu les bons réflexes. Cela a créé pas mal de difficultés lors de l’utilisation de variables d’un fichier à un autre. Nous avons fini par créer un certain nombre des variables globales, ce qui est à éviter au maximum. Nous nous sommes rendu compte un peu tard que nous aurions dû faire une structure qui contient les données dont nous avons besoin dans beaucoup d’endroits puis la passer en référence dans les fonctions qui en ont besoin. 
	
### Apprentissages
Les difficultés que nous avons rencontrées ont été très formatrices et nous ont permis de progresser dans de nombreux domaines. 
- **Améliorations des tests et des outils de débogage :** le projet étant important nous avons pris l’habitude de tester notre code petit à petit grâce à des étapes intermédiaires. Nous avons aussi dû utiliser le débogueur de nombreuses fois pour comprendre ce qui n’allait pas dans notre code.
- **Meilleure compréhension des notions vues ce semestre :** que ce soit en programmation ou en synthèse d’image, ce projet nous a vraiment permis de pratiquer toutes les notions apprises cette année. 
- **Meilleure prise en main de git :** les push, les merges et la gestion de conflit ont pas mal été démystifiés avec ce projet. 
