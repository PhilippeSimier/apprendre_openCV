Lecture et affichage d'une image
===================
Dans cette section, nous allons voir comment charger une image à partir d'un fichier ou d'une caméra et l'afficher dans une fenêtre puis pour terminer comment l'enregistrer  dans un fichier.
Avec OpenCV, on peut facilement lire des images avec différents formats de fichier (JPG, PNG, TIFF, etc.) 

### 1 Introduction

Une photo est simplement une lumière réfléchie par un objet et capturée par une caméra. Une caméra en niveaux de gris enregistre l'intensité de la lumière réfléchie. Une caméra couleur enregistre la lumière réfléchie en trois points du spectre visible: rouge (650 nm), vert (510 nm) et bleu (475 nm).

### Comment une couleur est-elle capturée par un appareil photo numérique?

Dans un appareil photo numérique, le capteur est sensible à la lumière visible (photons). Le capteur a de nombreux photosites ou pixels disposés sur une grille rectangulaire. Ces photosites produisent une charge électrique directement proportionnelle à la quantité de lumière (photons) reçue.

Selon la scène que nous enregistrons, différents pixels du capteur sont exposés à différentes quantités de lumière et nous avons un motif de charge électrique. La quantité de charge électrique est convertie en un nombre compris entre 0 et 255. Cela correspond à un octet (8 bits) ou à 256 valeurs. Cette matrice rectangulaire de nombres entre 0 et 255 est une image numérique en niveaux de gris .

![Capteur couleur bayer](/02_ImagelectureEcriture/capteur_couleur_bayer.png)

Les capteurs de couleur sont beaucoup plus compliqués. Chaque pixel du capteur n’enregistre qu’une couleur, le rouge, le vert ou le bleu. Le modèle présenté ci-dessus s'appelle le modèle Bayer . Notez qu'il y a deux fois plus de pixels verts que de pixels bleus et rouges, car l'œil humain est beaucoup plus sensible à la lumière verte par rapport à la lumière rouge ou bleue. Les deux canaux manquants à chaque pixel sont calculés en interpolant les valeurs des pixels voisins. Ce processus s'appelle le dématriçage.



### Enregistrement d'une photo dans un fichier

Une fois que l'image est lue par le capteur, elle est dématricée et convertie en une image RVB. Généralement, cette **matrice de pixels RVB** est compressée aux formats **JPG** ou **PNG** avant d’être stockée sur le disque. La plupart des formats d'image, comme JPG, ont deux parties:

 - En-tête d'image: cette partie contient des métadonnées de l'image telles que la largeur et la hauteur de l'image, le nombre de canaux, le profil de couleur, le nombre de bits par pixel, etc.
 - Données: cette partie contient des valeurs RVB compressées.


### 2 représentation des images en mémoire avec OpenCV en C++

Lorsque nous lisons une image à l'aide d'OpenCV, celle-ci est d'abord décompressée et stockée dans un format standard.
Les images sont des instances de la classe **Mat** .

 - **En-tête d'image**: cette partie contient des métadonnées d'image telles
   que la largeur et la hauteur de l'image, le nombre de canaux, le
   nombre de bits par pixel, etc.
 - **Données** : cette partie est un tableau de valeurs **BGR** non compressées
   dans le format ligne par ligne.  OpenCV stocke les    images au format BGR pour des raisons historiques .

Les trois premiers octets de ce tableau de données correspondent aux canaux bleu, vert et rouge dans le coin supérieur gauche de l'image. Les 3 octets suivants correspondent au pixel de la deuxième colonne et de la première ligne de l'image. Tous les pixels d'une rangée (ligne) d'une image sont stockés sous forme de bloc continu en mémoire. 
Tandis que les pixels d'une **ligne** pour une image sont physiquement stockés dans **un bloc continu dans la RAM**, toutes les lignes de pixels ne sont pas toujours dans des blocs continus de mémoire. Nous n'aurons jamais à nous soucier de ce détail, cependant sachez qu'il n'est pas possible de parcourir les pixels d'une image avec un pointeur en l'incrémentant pour passer au pixel suivant.

Dans OpenCV, 

 - la fonction **imread** est utilisée pour lire une image, 
 - **imwrite** pour écrire une image en mémoire sur un disque
 - **imshow** en conjonction avec namedWindow et waitKey pour afficher
   une image en mémoire.

### La fonction imread()

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

### 4 Enregistrer une image dans un fichier
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

