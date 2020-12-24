# Very Nice Chess
## Description
Very Good Chess ou VGC est un moteur d'échec basé sur la bibliothèque [graphique MLV](http://www-igm.univ-mlv.fr/~boussica/mlv/api/French/html/index.html).
Celui-ci permet notament de suivre un déroulrment normal de partie, sauvegarder une
partie en cours et éditer un plateau pour commencer une partie customisée.

## Dépendances
Le projet étant basé sur la bibliothèque MLV il possède une dépendance à celle-ci.
Pour l'installer il suffit de suivre les instructions présentes dans le
[guide d'installation MLV](http://www-igm.univ-mlv.fr/~boussica/mlv/api/French/html/installation.html).

## Compilation
Pour compiler, utilisez la commande:
```
make
```
Une fois compilé si les fichiers objets vous gênent utilisez la commande:
```
make clean
```

Les options de compilation utilisées sont:
```
-W -Wall -std=c89 -pedantic -O3 -g
```
et pour la bibliothèque MLV:
```
`pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV`
```

## Notes
Pour le moment, ce projet n'est qu'un moteur d'échec, il est certes possible de jouer contre un humain sur la même machine.
Néanmoins il ne permet pas de jouer contre une IA.
Mais il est tout à fait possible de partir de celui-ci et d'intégrer la votre.
Si l'envie vous en prend nous serions très heureux de voir vos projets :smile:.
