Le suivi  d'objet dans une vidéo
===================
Dans cette section, nous allons étudier l’API de suivi d'objet  introduite dans OpenCV 3.0.

### 1 Introduction sur le suivi d'objets
La localisation d'un objet dans les images successives d'une vidéo est appelée **tracking**.

**Traqueurs à objet unique** : dans cette classe de suiveurs, la première image est marquée à l'aide d'un rectangle pour indiquer l'emplacement de l'objet que nous souhaitons suivre. L'objet est ensuite suivi dans les images suivantes à l'aide de l'algorithme de suivi. Dans la plupart des applications réelles, ces suiveurs sont utilisés conjointement avec un détecteur d'objet.

#### 1-1 Le suivi est plus rapide que la détection : 
les algorithmes de suivi sont généralement plus rapides que les algorithmes de détection. La raison est simple. Lorsque vous suivez un objet détecté dans l'image précédente, vous en savez beaucoup sur l'apparence de l'objet. Vous connaissez également l'emplacement dans l'image précédente, ainsi que la direction et la vitesse de son mouvement. Ainsi, dans l'image suivante, vous pouvez utiliser toutes ces informations pour prédire l'emplacement de l'objet  et effectuer une petite recherche autour de l'emplacement attendu de l'objet pour le localiser avec précision. Un bon algorithme de suivi utilisera toutes les informations dont il dispose sur l'objet jusqu'à ce point, tandis qu'un algorithme de détection repart toujours de zéro. 

 Par conséquent, lors de la conception d'un système efficace, généralement une détection d'objet est exécuté sur chaque n ième image alors que l'algorithme de suivi est utilisé dans les n-1 trames situées entre les deux détections. Pourquoi ne détectons-nous pas simplement l'objet dans la première image et ne suivons-nous pas par la suite? Il est vrai que le suivi profite des informations supplémentaires dont il dispose, mais vous pouvez également perdre la trace d'un objet lorsqu'il passe derrière un obstacle pendant une période prolongée ou s'il se déplace si rapidement que l'algorithme de suivi ne peut pas le rattraper. Il est également courant que les **algorithmes de suivi accumulent des erreurs** et que le cadre de sélection poursuivant l'objet s'éloigne lentement de l'objet suivi. Pour résoudre ces problèmes avec Les algorithmes de suivi, un algorithme de détection est exécuté de temps en temps. Les algorithmes de détection sont formés sur un grand nombre d'exemples d'objet. Ils ont donc davantage des connaissances sur la classe générale de l'objet. 

#### 1-2 Le suivi conserve l'identité : 

le résultat de la détection d'objet est un tableau de rectangles contenant l'objet. Cependant, aucune identité n'est attachée à l'objet. Autrement dit nous ne savons pas quel rectangle correspond à quel objet et nous ne pouvons pas affirmer que lors de deux détections successives le même rectangle sera associé au même objet.
Le tracking  fournit un moyen de relier littéralement les objets d'une image à une autre!

### 2 API de suivi OpenCV 3
OpenCV 3.0 a implémentaté ce 4 trackers  - **BOOSTING, MIL, TLD, MEDIANFLOW.**

OpenCV 3.1 a implémenté ces 5 trackers - BOOSTING, MIL, TLD, MEDIANFLOW et **KCF**. 

OpenCV 3.2 a  implémentaté ces 6 trackers : BOOSTING, MIL, TLD, MEDIANFLOW, **MOSSE et GOTURN**.

OpenCV 3.3, l'API de suivi a été modifiée. A partir de cette version chaque tracker possède sa propre classe.  Ainsi le code suivant :
```cpp
Ptr<Tracker> tracker;
tracker = Tracker::create("TLD");
```
devient :
```cpp
Ptr<Tracker> tracker;
tracker = TrackerTLD::create();
```

OpenCV 3.4.1 a les implémentations des 8 suiveurs suivants- BOOSTING, MIL, KCF, TLD, MEDIANFLOW, GOTURN, MOSSE et CSRT.

###3 Commentaires sur le code proposé

Après avoir créer un objet tracker, un fichier vidéo est ouvert, puis la première image est lue.
Un rectangle de sélection contenant l'objet sur cette  première image est défini manuellement avec la fonction **selectROI**.
```cpp
Rect2d bbox;
bbox = selectROI(frame, false);
```
Le rectangle est dessiné sur cette première image
```cpp
 rectangle(frame, bbox, Scalar( 255, 0, 0 ), 2, 1 );   
```
Le tracker est initialisé avec ce rectangle
```cpp
 tracker->init(frame, bbox);
```
Les images suivantes de la vidéo sont lues dans une boucle et pour chacune d'elles, le rectangle de sélection est mis à jour.

```cpp
 bool ok = tracker->update(frame, bbox);
```
la méthode update renvoie true si le tracking est possible. 

### 4 Les Algorithmes de suivi d'objets
Dans ce paragraphe, nous allons creuser un peu les différents algorithmes de suivi. L'objectif n'est pas d'avoir une compréhension théorique approfondie de chaque traqueur, mais de les comprendre d'un point de vue pratique.

Dans le suivi, notre objectif est de trouver un objet dans l’image courante, car nous avons réussi à l’obtenir dans toutes les images précédentes (ou presque).

Comme nous avons suivi l’objet jusqu’à l’image actuelle, nous savons comment il a bougé. En d'autres termes, nous connaissons les paramètres du modèle de mouvement . Le modèle de mouvement est simplement une manière sophistiquée de dire que vous connaissez l'emplacement et la vitesse (vitesse + direction du mouvement) de l'objet dans les images précédentes. Si vous ne connaissiez rien d'autre à propos de l'objet, vous pourriez prédire le nouvel emplacement en fonction du modèle de mouvement actuel et vous seriez assez proche de l'emplacement du nouvel emplacement de l'objet.

Mais nous avons plus d'informations que le mouvement de l'objet. Nous savons à quoi ressemble l'objet dans chacune des images précédentes. En d'autres termes, nous pouvons créer un modèle d'apparence qui code à quoi ressemble l'objet. Ce modèle d'apparence peut être utilisé pour rechercher dans un petit voisinage de l'emplacement prédit par le modèle de mouvement afin de prédire plus précisément l'emplacement de l'objet.

Le modèle de mouvement prédit l'emplacement approximatif de l'objet. Le modèle d'apparence peaufine cette estimation pour fournir une estimation plus précise basée sur l'apparence.

Si l'objet était très simple et ne modifiait pas beaucoup son apparence, nous pourrions utiliser un modèle simple comme modèle d'apparence et rechercher ce modèle. Cependant, la vraie vie n'est pas si simple. L'apparence d'un objet peut changer radicalement. Pour résoudre ce problème, dans de nombreux suiveurs modernes, ce modèle d’apparence est un classificateur formé en ligne . 

La tâche du classificateur est de classer une région rectangulaire d'une image en tant qu'objet ou en arrière-plan. Le classificateur prend en entrée un patch d’image et renvoie un score compris entre 0 et 1 pour indiquer la probabilité que le patch d’image contienne l’objet. Le score est 0 lorsqu'il est absolument certain que le patch d'image est l'arrière-plan et 1 lorsqu'il est absolument certain que le patch est l'objet.

En apprentissage machine, nous utilisons le mot «en ligne» pour désigner des algorithmes formés à la volée au moment de l'exécution. Un classificateur hors ligne peut nécessiter des milliers d'exemples pour former un classificateur, mais un classificateur en ligne est généralement formé à l'aide de très peu d'exemples au moment de l'exécution.

Un classificateur est formé en lui donnant des exemples positifs (objet) et négatifs (arrière-plan).
Voyons comment différents algorithmes de suivi abordent ce problème de formation en ligne.

#### 4-1 **traqueur BOOSTING **
Ce traqueur est basé sur une version en ligne d’AdaBoost, l’algorithme utilisé en interne par le détecteur de visage à cascade HAAR. Ce classificateur doit être formé au moment de l'exécution avec des exemples positifs et négatifs de l'objet. Le cadre de sélection initial fourni par l'utilisateur (ou par un autre algorithme de détection d'objet) est pris comme exemple positif pour l'objet, et de nombreux correctifs d'image situés en dehors du cadre de sélection sont traités comme un arrière-plan. Étant donné une nouvelle image, le classificateur est exécuté sur chaque pixel au voisinage de l'emplacement précédent et le score du classificateur est enregistré. Le nouvel emplacement de l'objet est celui où le score est maximal. Nous avons maintenant un autre exemple positif pour le classificateur. Au fur et à mesure que plus de cadres entrent, le classificateur est mis à jour avec ces données supplémentaires.

**Avantages** : Aucun. Cet algorithme a 10 ans et fonctionne bien, mais je n’ai pas trouvé de bonne raison de l’utiliser, en particulier lorsque d’autres trackers avancés (MIL, KCF) reposant sur des principes similaires sont disponibles.

**Inconvénients** : les performances de suivi sont médiocres. Il ne sait pas de manière fiable quand le suivi a échoué.

#### 4-2 traqueur MIL 
Ce tracker a une idée similaire au tracker BOOSTING décrit ci-dessus. La grande différence est qu'au lieu de ne considérer que l'emplacement actuel de l'objet comme exemple positif, il semble que dans un petit quartier situé autour de l'emplacement actuel, il génère plusieurs exemples positifs potentiels. Vous pensez peut-être que c'est une mauvaise idée, car dans la plupart de ces exemples «positifs», l'objet n'est pas centré.

Aller voir la page du projet MIL qui a plus d’informations pour ceux qui veulent approfondir les rouages ​​du tracker MIL.

**Avantages** : la performance est très bonne. Il ne dérive pas autant que le suivi BOOSTING et fait un travail raisonnable en occlusion partielle. Si vous utilisez OpenCV 3.0, cela pourrait être le meilleur outil de suivi disponible. Mais si vous utilisez une version supérieure, considérez KCF.

**Inconvénients** : L'échec du suivi n'est pas signalé de manière fiable. Ne se remet pas d'une occlusion complète.

#### 4-3   traqueur KCF
KFC est synonyme de filtres de corrélation par noyau . Ce tracker s'appuie sur les idées présentées dans les deux précédents. Ce suivi utilise ce fait que les multiples échantillons positifs utilisés dans le suivi MIL comportent de grandes régions qui se chevauchent. Ces données qui se chevauchent donnent lieu à de bonnes propriétés mathématiques exploitées par ce suivi pour rendre le suivi plus rapide et plus précis en même temps.

**Avantages** : La précision et la rapidité sont meilleures que le MIL et le signalement des échecs de suivi est meilleur que le BOOSTING et le MIL. Si vous utilisez OpenCV 3.1 et supérieur, je vous recommande de l'utiliser pour la plupart des applications.

**Inconvénients** : Ne récupère pas d'une occlusion complète. Non implémenté dans OpenCV 3.0.


#### 4-4 Traqueur  TLD
TLD est synonyme de suivi, d'apprentissage et de détection. Comme son nom l'indique, ce traqueur décompose la tâche de suivi à long terme en trois composants: suivi (à court terme), apprentissage et détection. Dans le document de l'auteur, «Le suivi suit l'objet d'une image à l'autre. Le détecteur localise toutes les apparences observées jusqu'à présent et corrige le suivi si nécessaire. Le détecteur d'apprentissage estime les erreurs et les met à jour pour éviter ces erreurs à l'avenir. »La sortie de ce suivi a tendance à basculer un peu. Par exemple, si vous suivez un piéton et qu'il y a d'autres piétons dans la scène, ce suivi peut parfois suivre temporairement un piéton différent de celui que vous souhaitez suivre. Du côté positif, cette piste semble suivre un objet sur une plus grande échelle, le mouvement et l’occlusion.

**Avantages** : fonctionne le mieux sous l'occlusion sur plusieurs cadres. En outre, trace les meilleurs changements sur l'échelle.

**Inconvénients** : Beaucoup de faux positifs le rendant presque inutilisable.

#### 4-5  traqueur MEDIANFLOW 
En interne, ce traqueur suit l’objet dans le temps, dans les deux sens, et mesure les écarts entre ces deux trajectoires. La minimisation de cette erreur ForwardBackward leur permet de détecter de manière fiable les échecs de suivi et de sélectionner des trajectoires fiables dans les séquences vidéo.

Lors de mes tests, j’ai constaté que ce suivi fonctionnait mieux lorsque le mouvement était faible et prévisible. Contrairement aux autres suiveurs qui continuent même lorsque le suivi a clairement échoué, ce suivi permet de savoir quand le suivi a échoué.

**Avantages** : Excellent rapport d'échec de suivi. Fonctionne très bien lorsque le mouvement est prévisible et qu'il n'y a pas d'occlusion.

**Inconvénients** : échoue sous un grand mouvement.

#### 4-6   Traqueur GOTURN
Parmi tous les algorithmes de suivi de la classe de suivi, il s'agit du seul basé sur le réseau de neurones convolutionnels (CNN). D'après la documentation OpenCV, nous savons qu'il est «robuste face aux changements de points de vue, modifications d'éclairage et déformations». Mais il ne gère pas très bien l'occlusion.

Remarque : GOTURN étant un tracker basé sur CNN, utilise un modèle caffe pour le suivi. Le modèle **Caffe** et le fichier texte **proto** doivent être présents dans le répertoire dans lequel le code est présent. Ces fichiers peuvent également être téléchargés à partir du référentiel opencv_extra , concaténés et extraits avant utilisation.

#### 4-7 Traqueur MOSSE
La somme minimale de sortie de l'erreur au carré (MOSSE) utilise une corrélation adaptative pour le suivi d'objet qui produit des filtres de corrélation stables lorsqu'elle est initialisée à l'aide d'une seule trame. MOSSE Tracker est robuste aux variations d’éclairage, d’échelle, de pose et aux déformations non rigides. Il détecte également l’occlusion sur la base du rapport pic à lobe latéral, ce qui permet au suivi de se mettre en pause et de reprendre où il s’est arrêté lorsque l’objet réapparaît. MOSSE Tracker fonctionne également à une vitesse plus élevée (450 images par seconde et même plus). Pour ajouter aux aspects positifs, il est également très facile à mettre en œuvre, est aussi précis que d’autres systèmes de suivi complexes et beaucoup plus rapide. Mais, sur une échelle de performance, il est en retard sur les trackers basés sur l’apprentissage en profondeur.

#### 4-8  Traqueur CSRT
Dans le filtre de corrélation discriminante avec fiabilité de canal et spatiale (DCF-CSR), nous utilisons la carte de fiabilité spatiale pour ajuster la prise en charge du filtre à la partie de la région sélectionnée à partir de la trame pour le suivi. Cela garantit l’agrandissement et la localisation de la région sélectionnée et un suivi amélioré des régions ou objets non rectangulaires. Il utilise seulement 2 fonctionnalités standard (HoGs et Colornames). Il fonctionne également à une vitesse relativement basse (25 images par seconde), mais offre une plus grande précision pour le suivi des objets.


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

