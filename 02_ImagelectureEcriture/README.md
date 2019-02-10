Lecture et affichage d'une image
===================

### Introduction

Dans cette section, nous allons voir comment charger une image à partir d'un fichier et l'afficher dans une fenêtre puis pour terminer comment l'enregistrer  dans un fichier.
Avec OpenCV, vous pouvez facilement lire des images avec différents formats de fichier (JPG, PNG, TIFF, etc.) 

### 2 Lecture d'un fichier image

 La fonction  **imread** permet de lire un fichier image. L'utilisation de base est indiquée ci-dessous. Le contenu du fichier est chargé dans un objet de type **Mat**. En effet une image en mémoire n'est rien d'autre qu'une matrice. 
```cpp
Mat imread(const string& filename, int flags=IMREAD_COLOR )
```
L' option flags est utilisée pour contrôler le mode de lecture de l'image. 
Une grande majorité des images sont des images 8 bits par canal (ou 24 bits). Ils peuvent être lus à l'aide des flags par défaut.

```cpp
Mat image = imread("image.jpg");
```
Lire une image tout en effectuant une conversion en niveaux de gris 8 bits

```cpp
Mat image = imread("image.jpg", IMREAD_GRAYSCALE);
```

Lire un fichier image PNG ou TIFF avec des  transparence.
Une image transparente possède quatre canaux - 3 pour la couleur et un pour la transparence appelé canal alpha. 
```cpp
Mat image = imread("image.png", IMREAD_UNCHANGED);
```


### 3 Affichage d'une image à l'écran
Les images sont affichées dans une fenêtre graphique qui doit être nommée. La fonction waitKey(0) met en pause le programme pour un temps infini. Appuyer sur une touche du clavier pour continuer.
```cpp
imshow("maFenetre", image);
waitKey(0);
```

### 4 Enregistrer une image
La fonction **imwrite** enregistre une image dans un fichier spécifié.  Le format de l'image est choisi en fonction de l' extension du nom de fichier.  Des paramètres supplémentaires peuvent être utilisés pour définir par exemple le taux de qualité ou compression. Pour le format JPEG, il peut s'agir d'une qualité ( CV_IMWRITE_JPEG_QUALITY ) comprise entre 0 et 100 (le plus élevé étant le meilleur). La valeur par défaut est 95.  
```cpp
bool isSuccess = imwrite("monImage.jpg", image); 
 
if (isSuccess == false)
{
    cout << "Erreur lors de l'enregistrement de l'image" << endl;
    return -1;
 }
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

