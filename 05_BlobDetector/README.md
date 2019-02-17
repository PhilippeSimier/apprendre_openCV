Installation OpenCV
===================
Cette section décrit comment installer openCV avec openCV_contrib sur système OS linux Ubuntu.
 
### 1 Mise à jour du système
La première chose à faire est de mettre à niveau le système.
en tant que super-utilisateur
```bash
apt-get update
apt-get upgrade
```
### 2 Installation des paquets E/S
Puis, nous pouvons passer à l'installation de **paquets d'E/S d'image** qui nous permettent de charger les formats de fichiers image tels que JPEG, PNG, TIFF, etc...
Nous avons également besoin de **paquets d'E/S vidéo**. Ces paquets nous permettent de charger différents formats de fichiers vidéo ainsi que de travailler avec des flux vidéo:
Nous devons installer la **bibliothèque de développement GTK** afin que nous puissions compiler le sous-module Highgui d'OpenCV, qui nous permet d'afficher des images sur l'écran et de créer des interfaces GUI simples:
Diverses opérations à l'intérieur d' OpenCV (telles que les opérations matricielles) peuvent être optimisées en utilisant les dépendances ajoutées suivantes:

```bash
sudo apt-get install pkg-config unzip ffmpeg qtbase5-dev python-dev python3-dev python-numpy python3-numpy
sudo apt-get install libopencv-dev libgtk-3-dev libdc1394-22 libdc1394-22-dev libjpeg-dev libpng12-dev libtiff5-dev libjasper-dev
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libxine2-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev
sudo apt-get install libv4l-dev libtbb-dev libfaac-dev libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev
sudo apt-get install libvorbis-dev libxvidcore-dev v4l-utils vtk6
sudo apt-get install liblapacke-dev libopenblas-dev libgdal-dev checkinstall
```

### 2 Obtenir le code source OpenCV

Les lignes suivantes permettent d'obtenir la version 3.4.4 sur github.
décompresser les archives, renommer les répertoires, puis se placer dans le répertoire obtenu **opencv**
```bash
cd ~
wget -O opencv.zip https://github.com/opencv/opencv/archive/3.4.4.zip
wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/3.4.4.zip

unzip opencv.zip
unzip opencv_contrib.zip

mv opencv-3.4.4/ opencv
mv opencv_contrib-3.4.4/ opencv_contrib

cd opencv
```
### 3 Compilation et installation d'OpenCV

Tout d’abord installer **cmake**
```bash
apt install cmake
```
Dans le répertoire opencv;  créer un dossier **build** 
```bash
mkdir build
cd build/
```
cmake génère les fichiers nécessaires pour construire OpenCV dans le dossier build.
```bash    
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D FORCE_VTK=ON -D WITH_TBB=ON -D WITH_V4L=ON -D WITH_QT=ON -D WITH_OPENGL=ON -D WITH_CUBLAS=ON -D CUDA_NVCC_FLAGS="-D_FORCE_INLINES" -D WITH_GDAL=ON -D WITH_XINE=ON -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules  -D BUILD_EXAMPLES=ON ..
```
Enfin, nous sommes maintenant prêts à compiler OpenCV: pour cela on utilisera tous les cœurs du processeur avec l'option -j $(($(nproc) + 1)) .  Compter une vingtaine de minutes.

```bash
make -j $(($(nproc) + 1))
```
Puis nous pouvons passer à l'installation en tant que super-utilisateur
```bash
sudo make install
sudo /bin/bash -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
sudo ldconfig
sudo apt-get update
```
### 4 Vérification de l'installation

Pour contrôler l'installation exécuter le programme opencv_version situé dans le répertoire /usr/local/bin.
```bash
/usr/local/bin/opencv_version
3.3.4
```
### 5 Vérification pour python

```bash
psimier@b107PSR ~/opencv3/apprendre_openCV/01_testInstallation $ python3
Python 3.5.2 (default, Nov 12 2018, 13:43:14) 
[GCC 5.4.0 20160609] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> import cv2
>>> cv2.__version__
'3.3.4'
>>> quit()
```

### 6 Compilation d'un premier programme
le programme test.cpp est un programme très simple qui se contente de créer une image de couleur uniforme et de l'afficher dans une fenêtre.

Pour compiler ce programme utiliser la ligne de commande suivante :
```bash
g++ -ggdb test.cpp -o test `pkg-config --cflags --libs opencv`
```
Lancer l'exécution vous devez voir apparaître une fenêtre avec un rectangle de couleur unie.
```bash
./test
```

### Changelog

 **24/12/2018 :** Ajout du README . 
 
 
> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER Lycée Touchard Le Mans**
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


