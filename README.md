# Very Nice Chess
## Description
Very Nice Chess ou VNC est un moteur d'échec basé sur la bibliothèque graphique MLV.
Celui-ci permet notament de suivre un déroulrment normal de partie, sauvegarder une
partie en cours et éditer un plateau pour commencer une partie customisée.

## Compilation
Pour compiler, utilisez la commande:
```
make
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
