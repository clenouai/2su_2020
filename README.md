# INSA 2SU 2020

https://bitbucket.org/whitewand/2su_2020/src


# Crack emily:

Mon nom de fichier est: td1
- *file td1* nous donne le format sous lequel est stocké l'exécutable
- *strings td1* nous donne les phrases ASCII qu'on peut déchiffrer de l'exécutable comme:
"poop
Please input a word:
That's correct!
That's not correct!"

On obtient en clair le mot de passe attendu ! Une obfuscation pour cacher les strings auraient été une bonne idée.

- avec la commande *objdump*, on observe que la fonction main fait apelle a la fonction <is_valid>, et dans cette fonction on repère la condition qui va permettre de passer sans erreur.

861:   75 07                   jne    86a <is_valid+0x2a> (Offset dans le fichier : 0x86a)
863:   b8 01 00 00 00          mov    $0x1,%eax
868:   eb 05                   jmp    86f <is_valid+0x2f> (Offset dans le fichier : 0x86f)
86a:   b8 00 00 00 00          mov    $0x0,%eax

on s'apperçoit que la valeur rentrée dans %eax, est le retour 1 ou 0 selon que la condition avant le 'jne' soit fausse ou vraie. **jne = jump if not equal** donc on suppose que si l'on passe dans jne on va à l'adresse 86a et le retour sera 0 (faux). Nous souhaitons donc modifier le code tel que la fonction <is_valid> retour 1 et donc met $0x01 dans %eax.

L'instruction a pour code machine :  b8 00 00 00 00 et l'adresse est 0x86a donc 2154 bytes. Hors nous voulons changer le byte numéro 4. Donc le code se trouve au **2158ème** bytes.

Retrouvons cette instruction avec la commande hexdump autour de l'adresse 86a:

_00000860  c0 75 07 b8 01 00 00 00  eb 05 **b8 00 00 00 00** c9  |.u..............|_

La commande pour modifier le byte adéquate dans le binaire est :
_printf '\x01' | dd of=td1 bs=1 seek=2158 count=1 conv=notrunc14_

![GitHub Logo](/capture/archive_emily_succes.png)
Format: ![Alt Text](url)


#binwalk
