Renforcer les contours
===================

### 1 Introduction
Dans cette section, nous présentons deux méthodes  pour obtenir les contours dans une image. Le filtre Laplacian et l'algorithme de Canny.
![Canny detection des contours](/04_RenforcementContours/Canny_screenshot_06.02.2019.png)

### 2 Le Laplacian

le filtre Laplacien est un filtre de convolution particulier utilisé pour mettre en valeur les détails  qui ont une variation rapide de luminosité. Il est donc idéal pour rendre visible les contours des objets.
Le laplacien est la somme des dérivées secondes d'une image suivant x et y.  On peut obtenir la dérivée seconde (soit le laplacien) avec une bonne approximation grâce au noyau de   convolution suivant :

                1  1  1
                1 -8  1
                1  1  1

Il peut être utilisé pour rendre plus net les contours d'une image. Pour cela, on soustrait à l'image une fraction du laplacien.



### 3 Détecter les contours d'une image avec un filtre de Canny

L'algorithme a été conçu par John Canny en 1986.    

L’algorithme de **Canny** se décompose en plusieurs phases :

 - Réduction du bruit 
 - Calcul de la dérivée suivant quatre directions (horizontale, verticale, et les deux diagonales à 45 °)
 - Localisation des contours par seuillage à hystérésis. 

Deux seuils sont définis, une valeur basse et une haute, qui sont comparées avec le gradient en chaque point. Si la valeur de gradient est: 

 - inférieur au seuil bas, le point est mis au rebut;
 - supérieur au seuil haut, le point est acceptée comme une partie d'un
   contour;
 - compris entre les deux seuils, le point est accepté que si contigu à
   un point préalablement accepté.
   
A la fin de ces étapes on obtient une image binaire où chaque pixel est marqué comme appartenant ou non à un contour.
OpenCV met tout ce qui précède dans une seule fonction **Canny**

Le premier argument est l'image d'entrée
Le deuxième est l'image de sortie
Les troisième et quatrième arguments sont respectivement les valeurs des seuils bas et haut.
Le dernier argument spécifie l'équation permettant de rechercher l'amplitude du gradient. Si true alors le gradient est égal à la racine carré des sommes au carré des gradients suivant x et y. Sinon le gradient est égal à la somme des valeurs absolues des gradients suivant x et y.

```cpp
 cvtColor( image, image_gray, CV_RGB2GRAY);
 blur( image_gray, image_gray, Size(5,5) );
 Canny( image_gray, image_CNY, seuilA, seuilB, 3, true );
 imshow("Canny", image_CNY);
```

### Changelog

 **08/02/2019 :** Ajout du README . 
 
 
> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER Lycée Touchard Le Mans**
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#
https://docplayer.fr/15188945-Le-traitement-d-images-avec-opencv.html

