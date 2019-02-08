Lecture Ecriture de flux vidéo
===================

### 1 En tête pour utiliser la librairie

Pour écrire un programme basé sur OpenCV, il faut inclure le fichier 
```c
    #include <opencv2/opencv.hpp>
```
Ce fichier contient tous les en-têtes associées aux modules d'OpenCV de base. La simplicité de cette méthode à pour contre-partie une augmentation du temps de compilation.

pour le programme lecteur.cpp au lieu de opencv2/opencv.hpp on peut aussi  écrire :
```c
    #include <opencv2/highgui/highgui.hpp>
    #include <opencv2/videoio.hpp>
```
Toutes les classes et les méthodes d’OpenCV en C++ ont un espace de nommage (namespace) 
nommée cv. Ainsi on doit utiliser la directive de compilation suivante après avoir déclaré les 
fichiers d’en tête.
```c
    using namespace cv;
```

### 2 L'objet VideoCapture

le constructeur de la classe VideoCapture ouvre un flux vidéo issu soit d'une camera, ou d'un fichier vidéo.

Exemple 1 : Ouvre le flux vidéo de la première camera
```cpp
	VideoCapture cap(0);
```
Exemple 2: Création de l'objet puis utilisation de la méthode open() pour ouvrir le flux.
```cpp
	VideoCapture cap;
	cap.open(0);
	// ou pour un fichier
	cap.open("chaplin.mp4");
	
```

La méthode *isOpened()* de *VideoCapture* retourne la valeur vraie  si l'ouverture du périphérique est effective.

```cpp
  if (!cap.isOpened()) {
    cerr << "ERREUR: Impossible d'ouvrir le flux vidéo" << endl;
    return -1;
  }
```
 
 
### 3 La fonction WaitKey()

La fonction ***char waitKey(int delay);*** 
Cette fonction : bloque une boucle du programme pendant un certain temps (paramètre **delay**  nombre de millisecondes) . Elle attend pendant ce temps que l'utilisateur ait appuyé sur une touche du clavier et retourne le caractère associé à la touche du clavier.
```cpp
  do {
    
  }
  while(waitKey(20) != 27);
```
### 4 Acquisition d'une image dans un flux vidéo
On effectue l'acquisition de l'image en utilisant l’opérateur **>>** de la classe *VideoCapture*. l'objet image est une instance de la classe **Mat**.
l'image peut ensuite être  affichée dans une fenêtre avec la fonction imshow. Cette fonction prend deux paramètres le nom de la fenêtre et l'image (un objet Mat).

```cpp
    cap >> image;
    vide = image.empty();

    if (!vide)
       imshow(titre, image); // affichage de l'image dans la fenêtre
```
il faut bien noter que que l'affichage est fait lors de l'appel à la fonction **waitKey**. la fonction imshow envoie un événement au système et la fonction waitKey permet de traiter les événements en attente. La fonction **waitKey est indispensable** pour voir les images sur l'écran. Sans waitKey la fenêtre reste désespéramment grise. 

le programme complet **lecteur.cpp**

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

