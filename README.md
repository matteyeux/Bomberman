# Bomberman

### Build
Les paquets suivants sont nécessaires pour la compilation (sous Debian/Ubuntu)
- libsdl2-dev
- libsdl2-image-dev
- libsdl2-ttf-dev

```bash
$ sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```

Pour compiler : `make`
### Documentation

Documentation générée avec Doxygen disponible ici : bomberman.matteyeux.com.

Ou vous pouvez aussi la générer vous-même avec make : `make docs`.

### Menu 
Si vous lancez Bomberman dans une machine virtuelle, il se peut que vous ayez des problèmes avec les choix du menu (1, 2 et 3).

Pour cela pour pouvez utiliser les touches suivantes : 
- C : pour créer une partie (create)
- J : pour rejoindre une partie (join)
- Q : quitter

### support

Testé uniquements sur les systèmes GNU/Linux. Il est recommandé d'utiliser Debian 9.

