# Script

### 1 - Le mouton a faim.
Le mouton est dans un désert.
En option: on le voit finir de manger la dernière touffe d’herbe.

Zoom out : le mouton est tout seul, il n’y a rien autour.

### 2 - Le mouton marche longtemps
Plusieurs plans du mouton qui marche.
On peut le montrer à plusieurs endroits ; ou alors, alternance jour / nuit pour montrer qu’il marche longtemps.

### 3 - Il voit un panneau restaurant
Le mouton tombe nez à nez avec un panneau. Il est surpris. Le panneau indique un restaurant. Le mouton suit le panneau.

### 4 - Il marche longtemps (bis)
Variante du 2 ci-dessus.

### 5 - Il est en haut d’une colline
Le mouton arrive en haut d’une colline. Il écarquille les yeux et découvre un champ d’herbe fraîche. Il court en descendant la colline.

### 6. Il tombe sur un panneau /!\
En bas de la colline, il voit le panneau point d’exclamation. Il hésite ; il regarde l’herbe derrière. Il s’avance.

### 7. Il se fait écraser.
Fin.

# Note

Anti aliasing :

- Distance Field AA : J'ai testé comme decrit dans ce [papier](https://graphics.stanford.edu/courses/cs348b-20-spring-content/uploads/hart.pdf), ne fonctionne pas dans certain cas.
- TAA : Au vu de la complexité de l'animation, la reprojection me parait compliqué
- Supersampling : La bonne méthode pour avoir un rendu de qualité mais trop couteux ? A voir a la fin
- FXAA : La méthode actuellement utilisée, avec 2 passes. Ca fonctionne bien meme si ca rend l'image un peu flou ?

Performance : Pour le moment tous les objets sont dans la scene pour simplifier. On pourra creer differentes variantes du shader pour ne tracer que certains objets a l'aide de macro.

# Bugs

- Problème dans le calcul de l'AO et du SSS : provoque une discontinuité a certains endroit due au faible sampling. Ajouter une rotation du kernel regle le probleme mais introduit du bruit. (Passer le #if a 1 dans AmbientOcclusion()). A voir si on peut pas etre plus malin sur le sampling.

- Kodelife : fichier binaire, pas de diff sur github :(. A voir si c'est bloquant a terme.


# Idées / TODO

- Mise en scène

- Musique / son

- Un vrai ciel avec cycle jour nuit ? Physiquement correct ou Cartoon ?

- Faire un generique d'intro et fin pour ressembler encore plus a un short movie ?
 Generique de fin : Greetings ?
