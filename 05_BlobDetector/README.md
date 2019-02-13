Détection de blobs
===================

### 1 Introduction
Un blob est un groupe de pixels connectés dans une image qui partagent une propriété commune (par exemple, une échelle de gris). Dans l'image ci-dessus, les régions sombres connectées sont des taches, l'objectif de la détection des taches étant d'identifier et de marquer ces régions. OpenCV fournit un moyen pratique de détecter les blobs et de les filtrer en fonction de différentes caractéristiques. 

![SimpleBlobDetector](/05_BlobDetector/snapshot1.png)

## 2 SimpleBlobDetector
```cpp
using namespace cv;
// lecture image
Mat im = imread( "blob.jpg", IMREAD_GRAYSCALE );
 
// Création d'un SimpleBlobDetector avec les paramètres par défaut.
SimpleBlobDetector detector;
 
// Création d'un tableau de points clés.
std::vector<KeyPoint> keypoints;
// Détection des blobs dans l'image
detector.detect( im, keypoints);
 
// Dessine autour des blobs un cercle rouge.
// DrawMatchesFlags::DRAW_RICH_KEYPOINTS Ce drapeau assure que la taille du cercle correspond à la taille du blob
Mat im_with_keypoints;
drawKeypoints( im, keypoints, im_with_keypoints, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );
 
// Affichage des blobs
imshow("keypoints", im_with_keypoints );
waitKey(0);

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

