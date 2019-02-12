Renforcer les contours
===================

### 1 Introduction
Dans cette section, nous présentons deux méthodes  pour obtenir les contours dans une image. le filtre Laplacian et l'algorithme de Canny.


### 2 Le Laplacian
le filtre Laplacien est un filtre de convolution particulier utilisé pour mettre en valeur les détails   ont une variation rapide de luminosité. Il est donc idéal pour rendre visible les contours des objets.
Le laplacien est la somme des dérivées secondes d'une image suivant x et y.  On peut obtenir la dérivée seconde (soit le laplacien) avec une bonne approximation grâce au noyau de   convolution suivant :

                1  1  1
                1 -8  1
                1  1  1

Il peut être utilisé pour rendre plus net les contours d'une image. Pour cela, on soustrait à l'image une fraction du laplacien.



### 3 Détecter les contours d'une image avec un filtre de Canny

L'algorithme a été conçu par John Canny en 1986.    
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

