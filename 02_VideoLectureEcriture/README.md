Lecture Ecriture et affichage d'un flux vidéo
===================

### Introduction

L'objectif est d'apprendre à lire, écrire et afficher des vidéos avec OpenCV (langage C++).

Une vidéo est **une suite d'images** en mouvement rapide. La mesure de la fréquence des images qui sont affichées successivement  est donnée par une métrique appelée **FPS** (frames par seconde).  Quand on dit que la vidéo a un FPS de 40, cela signifie que 40 images sont affichées toutes les secondes et donc  une nouvelle image est affichée, toutes les 25 millisecondes. Les autres attributs importants d'une vidéo sont la largeur et la hauteur des images.




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

### 2 Lecture d'une vidéo

Dans OpenCV, une vidéo peut être lue en utilisant le flux d’une caméra connectée à un ordinateur ou en lisant un fichier vidéo. La première étape pour lire un fichier vidéo consiste à créer un objet **VideoCapture**. Son argument peut être soit l’index de la camera, soit le nom du fichier vidéo à lire.

Dans la plupart des cas, une seule caméra est connectée au système. Donc, tout ce que nous faisons est de passer "0" et OpenCV utilise la seul camera connectée à l'ordinateur. Lorsque plusieurs caméras sont connectées à l'ordinateur, nous pouvons sélectionner la deuxième caméra en transmettant "1", la troisième caméra en transmettant "2", etc.

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
Une fois l’objet VideoCapture créé, nous pouvons capturer la vidéo image par image.
 

### 3 Lecture d'une vidéo et affichage

Nous pouvons afficher la vidéo image par image. Une image d'une vidéo est simplement une image qui peut être affichée avec la fonction **imshow**.

On effectue l'acquisition de l'image en utilisant l’opérateur **>>** de la classe *VideoCapture*. l'objet image est une instance de la classe **Mat**.
l'image peut ensuite être  affichée dans une fenêtre avec la fonction **imshow**. Cette fonction prend deux paramètres le nom de la fenêtre et l'image qui est un objet Mat.

```cpp
    cap >> image;
    vide = image.empty();

    if (!vide)
       imshow("nom_de_la_fenetre", image); // affichage de l'image dans la fenêtre
```

Chaque image ne doit être affichée que pendant un intervalle de temps fini. Nous devons donc mettre en pause le programme avec la fonction **waitKey ()**. L'argument attendu est le temps de pause exprimé en millisecondes. (25 ms pour obtenir un FPS de 40 images par seconde)

#### 3 La fonction waitKey()

Si pendant le temps de pause  l'utilisateur  appuie sur une touche du clavier la fonction waitKey() retourne le code du caractère associé à la touche du clavier.
```cpp
  do {
    
  }
  while(waitKey(20) != 27);
```

il faut bien noter que que l'affichage est fait lors de l'appel à la fonction **waitKey**. la fonction imshow envoie un événement au système et la fonction waitKey permet de traiter les événements en attente. La fonction **waitKey est indispensable** pour voir les images sur l'écran. Sans waitKey la fenêtre reste désespéramment grise. 

**waitKey (1)** est approprié lors de la lecture des images d'une webcam, car la cadence d'affichage sera limitée par celle de la webcam, même si nous spécifions un délai de 1 ms dans waitKey.

le programme complet [lecteur.cpp](https://github.com/PhilippeSimier/apprendre_openCV/blob/master/02_VideoLectureEcriture/lecteur.cpp)

### 4 Enregistrer une vidéo

Une fois la capture et le traitement de la vidéo terminés, la prochaine étape que nous souhaitons effectuer consiste à enregistrer la vidéo dans un fichier.

Nous devons créer un objet **VideoWriter** . Premièrement, nous devons spécifier le nom du fichier de sortie avec son format (par exemple: output.avi). Ensuite, nous devrions spécifier le code FourCC et le nombre d'images par seconde (FPS). Enfin, la taille de la frame doit être passée, c'est un objet Size.

FourCC est un code de 4 octets utilisé pour spécifier le codec vidéo. **MJPG** est un choix sûr.
```cpp
VideoWriter writer;
Size taille(640, 380);
writer.open( "output.avi", CV_FOURCC('M','J','P','G'), fps, taille);
```
pour écrire un nouvelle image dans le fichier vidéo 

```cpp
    writer << image;
    //ou
    video.write(image);
```
 Le programme complet [enregistreur.cpp](https://github.com/PhilippeSimier/apprendre_openCV/blob/master/02_VideoLectureEcriture/enregistreur.cpp)
 

 
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

