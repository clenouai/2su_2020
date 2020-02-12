# INSA 2SU 2020

https://bitbucket.org/whitewand/2su_2020/src

##Questions

    Quels sont les chemins d'attaque possibles sur la signature d'un système embarqué?
    A quoi sert la chaine de confiance? Pourquoi est-elle nécessaire?
    Décrire la méthode pour aborder la sécurité sur un produit embarqué. Pourquoi établir un modèle d'attaquant est-il important?
      Commence par le flot d'information: 1 - produit/service 2- qu'est ce que l'attaquant gagne en cassant notre système  3- flot d'info (par ou on rentre) 4-
    Trouver un moyen rapide de faire du debug embarqué (par exemple sur cible ARM)? Expliquer les avantages
      emulation, qemu, etc    question ouverte
    Lister les catégories de bug possibles et comment les exploiter et les défendre
        comment attaquer comment défendre
    Quelles idées pour améliorer la sécurité en embarqué? (IA, Anti-debug, Obfuscation, Crypto ...) Choisissez une idée, chercher si elle existe et développer en quelques phrases quel avantage elle apporte et ses limites




## TD1 : [Reverse engineering]

## Crack emily:

Mon nom de fichier est: td1
- *file td1* nous donne le format sous lequel est stocké l'exécutable
- *strings td1* nous donne les phrases ASCII qu'on peut déchiffrer de l'exécutable comme:
"poop
Please input a word:
That's correct!
That's not correct!"

On obtient en clair le mot de passe attendu ! Une obfuscation pour cacher les strings auraient été une bonne idée.

- avec la commande *objdump*, on observe que la fonction main fait apelle à la fonction <is_valid>, et dans cette fonction on repère la condition qui va permettre de passer sans erreur.

*861:   75 07                   jne    86a <is_valid+0x2a> (Offset dans le fichier : 0x86a)
863:   b8 01 00 00 00          mov    $0x1,%eax
868:   eb 05                   jmp    86f <is_valid+0x2f> (Offset dans le fichier : 0x86f)
86a:   b8 00 00 00 00          mov    $0x0,%eax*

on s'apperçoit que la valeur rentrée dans %eax, est le retour 1 ou 0 selon que la condition avant le 'jne' soit fausse ou vraie. **jne = jump if not equal** donc on suppose que si l'on passe dans jne on va à l'adresse 86a et le retour sera 0 (faux). Nous souhaitons donc modifier le code tel que la fonction <is_valid> retour 1 et donc met $0x01 dans %eax.

L'instruction a pour code machine :  b8 00 00 00 00 et l'adresse est 0x86a donc 2154 bytes. Hors nous voulons changer le byte numéro 2. Donc le code se trouve au **215ème** bytes.

Retrouvons cette instruction avec la commande hexdump autour de l'adresse 86a:

_00000860  c0 75 07 b8 01 00 00 00  eb 05 **b8 00 00 00 00** c9  |.u..............|_

La commande pour modifier le byte adéquate dans le binaire est :
_printf '\x01' | dd of=td1 bs=1 seek=2155 count=1 conv=notrunc_

![GitHub Logo](/capture/success_emily.png)



## Binwalk

Installer qemu_system_arm
Installer binwalk

Après extraction des archives à l'aide de la commande ' binwalk -e nom_archive ' on trouve dans le fichier '/_vmlinuz-qemu-arm-2.6.20.extracted/_31B0.extracted/_E7E0.extracted/cpio-root/usr/local/share/directfb-examples/tux.png'_ la photo des pingouin .

![GitHub Logo](/capture/binwalk_png.png)

Adresse de l'image des pingouins : 0x2D89DC

Nous extrayons la photo du pingouin avec la commande suivante :

![GitHub Logo](/capture/extraction_png.png)

3] Que peut faire un attaquant avec binwalk ?

Permet de chercher, analyser et décompresser des fichiers binaires comme les firmwares. Il intègre plusieurs options permettant de reconnaître et extraire des formats standards dans les binaires (systèmes de fichiers, kernel, fichiers compressés/archivés, headers de fichiers connus...). De plus, il dispose de fonctionnalités permettant de faire des analyses d'entropie. Avec tous ces moyens, un attaquant peut faire du reverse sur n'importe quel binaire ou firmware pour extraire des données qui peuvent être sensibles.
