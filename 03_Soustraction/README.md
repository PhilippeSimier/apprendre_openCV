la détection de mouvement
===================

### 1 Introduction
Dans cette section, nous présentons une méthode  simple pour détecter des mouvements dans un flux vidéo. 

Cette démonstration vous permet de tester la fonction de soustraction d'arrière-plan   incluse dans OpenCV.  La soustraction d'arrière-plan peut être utile pour localiser  des objets en mouvements  sur un arrière-plan fixe.
 
L'algorithme est  simple : le programme capture une frame,  la convertie en noir et blanc et la compare avec la précédente  qu'il a mis en mémoire.  

Si la différence entre ces deux images est supérieure à un certain seuil, le programme considère qu'il y a eu mouvement,  et déclenche une action particulière (ici affichage d'un texte dans la fenêtre de contrôle).

La différence entre les deux images est obtenue  en utilisant la fonction **absdiff** puis le résultat est segmenté avec la fonction **threshold**. ainsi seul les différences supérieures au seuil sont conservées. 
 
Pour finir la fonction **CountNonZero**  permet de calculer le nombre de pixels non noirs sur l'image segmentée. Le nombre maximum de pixels qui pourraient être comptés correspond  à la résolution  en pixels de l'image.
    
### 2 absdiff 

    void absdiff(InputArray src1, InputArray src2, OutputArray dst)

Paramètres:	

    src1 – Première matrice Mat ou scalaire .
    src2 – Seconde matrice Mat ou scalaire .
    src  – Une matrice pour le résultat.


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

