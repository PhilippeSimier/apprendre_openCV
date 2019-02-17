Installation OpenCV 3 pour raspberry pi3plus
===================
Cette section décrit comment installer openCV avec openCV_contrib sur système OS linux rasbian.
Installation testée sur raspberry pi3 plus avec carte SD 16Go.
 
### 1 Mise à jour du système
La première chose à faire en tant que super-utilisateur est de mettre à niveau le système.

```bash
apt-get update
apt-get upgrade
```

### 2 faire de la place sur la carte SD
deuxième chose : faire de la place sur la carte en retirant wolfram-engine et libreoffice.

```bash
sudo apt-get -y purge wolfram-engine
sudo apt-get -y purge libreoffice*
sudo apt-get -y clean
sudo apt-get -y autoremove
```

### 3 Dépendances

Installation des bibliothèques du système d'exploitation

```bash
sudo apt-get install pkg-config unzip ffmpeg qtbase5-dev python-dev python3-dev python-numpy python3-numpy
sudo apt-get install  libdc1394-22 libdc1394-22-dev libjpeg-dev libpng12-dev libtiff5-dev libjasper-dev
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libxine2-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev
sudo apt-get install libv4l-dev libtbb-dev  libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev
sudo apt-get install libvorbis-dev libxvidcore-dev v4l-utils vtk6
sudo apt-get install liblapacke-dev libopenblas-dev libgdal-dev checkinstall

sudo apt-get install libgtk2.0-dev
```
### 4 Installation des bibliothèques Python
```bash
wget https://bootstrap.pypa.io/get-pip.py
sudo python get-pip.py
sudo python3 get-pip.py
pip install numpy
```
### 5 Télécharger opencv et opencv_contrib

```bash
wget -O opencv.zip https://github.com/Itseez/opencv/archive/3.3.0.zip
unzip opencv.zip

wget -O opencv_contrib.zip https://github.com/Itseez/opencv_contrib/archive/3.3.0.zip
unzip opencv_contrib.zip
```

### 6 Création du répertoire build

```bash
cd opencv  opencv-3.3.0
mkdir build
cd build/
```

### 7 cmake

cmake génère les fichiers nécessaires pour construire OpenCV dans le dossier build. cmake ne produit pas directement le logiciel final, il s'occupe de la génération de fichiers de construction standards : les makefiles sous linux.

```bash
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D INSTALL_PYTHON_EXAMPLES=ON -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib-3.3.0/modules -D BUILD_EXAMPLES=ON ..
```
résultat de cmake quand tout va bien

```bash
--   cvconfig.h is in:              /home/pi/opencv-3.3.0/build
-- -----------------------------------------------------------------
--
-- Configuring done
-- Generating done
-- Build files have been written to: /home/pi/opencv-3.3.0/build
```

### 8 Augmentation de la taille du swap
```bash
CONF_SWAPSIZE=1024
sudo /etc/init.d/dphys-swapfile stop
sudo /etc/init.d/dphys-swapfile start
```

### 9 Compilation avec un seul cœur 
il faut compter environ 4 heures 
```bash
sudo make 

sudo make install
sudo ldconfig
```
### 10 verification de l'installation

```bash
/usr/local/bin/opencv_version
3.3.0

pi@raspPi3plus:~/opencv-3.3.0/build $ python3
Python 3.5.3 (default, Sep 27 2018, 17:25:39)
[GCC 6.3.0 20170516] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> import cv2
>>> cv2.__version__
'3.3.0'
>>> quit()
```
### 11 installation du module V4L2

Enfin, nous devons également ajouter une déclaration simple pour nous assurer que VideoCapture (0) fonctionne sur notre Raspberry Pi avec la camera.

```bash
echo "sudo modprobe bcm2835-v4l2" >> ~/.profile
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


