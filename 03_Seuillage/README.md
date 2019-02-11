la segmentation d'images
===================

### 1 Introduction
Dans cette section, nous présentons la méthode la plus simple pour segmenter une image. La méthode présentée consiste à seuiller l'histogramme d'une image en niveau de gris pour la diviser en deux régions.

Tous les algorithmes de seuillage prennent en entrée une image source ( src ) et une valeur de seuil ( thresh ) et produisent une image de sortie ( dst ) en comparant la valeur de de chaque pixel  source (x, y) au seuil. 
Si **src (x, y)> thresh**  alors  **dst (x, y)** se voit attribuer une certaine valeur. Sinon, dst (x, y) se voit attribuer une autre valeur.

Dans sa forme la plus simple, le seuillage est appelé seuil **binaire** . Outre l'image source ( src ) et la valeur de seuil ( thresh ), un autre paramètre d'entrée appelé valeur maximale ( maxValue ) est nécessaire . Pour chaque emplacement de pixel (x, y), il y a comparaison de la valeur du pixel src (x, y) au seuil . 

    
### 2 Seuil binaire (type = THRESH_BINARY)

C'est le type de seuillage le plus courant et le plus simple. L'algo est le suivant :
 
    Pour chaque pixel
    Si src (x, y) est supérieur à thresh  
      alors  dst (x, y) <- maxValue  
    sinon dst(x,y) <- 0

 
```cpp
// lecture de l'image source
Mat src = imread("threshold.png", IMREAD_GRAYSCALE);
Mat dst; // le résultat image binaire
 
// déclaration des variables thresh et maxValue
double thresh = 5;
double maxValue = 255; 
 
// Binary Threshold
threshold(src, dst, thresh, maxValue, THRESH_BINARY);

// Affichage de l'image obtenue
imshow("maFenetre", dst);
waitKey(0);
```
La fonction **threshold** à 5 arguments

 1. Un objet de type Mat, l'image à seuiller
 2. Le résultat de type Mat, l'image binaire
 3. Un réel de type double, la valeur du seuil
 4.  Une réel de type double, la valeur associée au niveau supérieur du seuil dans le résultat
 5. un entier permettant de choisir le type de seuillage.

 
### 3 Seuil binaire inverse (type = THRESH_BINARY_INV)
 
Pour ce type de seuillage,  L'algo est le suivant : C'est l'inverse du précédent.
 
    Pour chaque pixel
    Si src (x, y) est supérieur à thresh  
      alors  dst (x, y) <- 0  
    sinon dst(x,y) <- maxValue
 

### 4 Troncature du seuillage (type = THRESH_TRUNC)
Dans ce type de seuillage,  si la valeur du pixel source est supérieure au seuil, le pixel de destination est défini sur le seuil (seuil  )  . Sinon, il est défini sur la valeur du pixel source. **maxValue est ignoré** .
 
 

    Pour chaque pixel
        Si src (x, y) est supérieur à thresh  
          alors  dst (x, y) <- thresh 
        sinon dst(x,y) <- src(x,y)

### 5 Seuil à zéro (type = THRESH_TOZERO)

Dans ce type de seuillage, si la valeur de pixel source est supérieure au seuil, la valeur de pixel de destination est définie sur la valeur de pixel source correspondante . Sinon, il est mis à zéro. **maxValue est ignoré** .

    Pour chaque pixel
        Si src (x, y) est supérieur à thresh  
          alors  dst (x, y) <- src(x,y) 
        sinon dst(x,y) <- 0

### 6 Seuil inversé à zéro (type = THRESH_TOZERO_INV)

Dans ce type de seuillage, si la valeur du pixel source est supérieure au seuil, alors la valeur du pixel de destination est définie sur zéro . Sinon, il est défini sur la valeur du pixel source. maxValue est ignoré .

    Pour chaque pixel
            Si src (x, y) est supérieur à thresh  
              alors  dst (x, y) <- 0  
            sinon dst(x,y) <- src(x,y)


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

