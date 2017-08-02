# 21sh_jpp

![Alt text](http://media0.giphy.com/media/IerVAJUS26GQg/giphy.gif)

## Index

1. [Developpement](#developpement)
2. [Git workflow](#git-workflow)


## Developpement

Controles speciaux:

Alt + right : deplacement par mot droite
Alt + left : deplacement par mot gauche

Alt + k : couper la chaine du curseur jusqu'à la fin de la ligne
Alt + j : couper la chaine du curseur jusqu'au début de la ligne
Alt + y : coller une chaine

## Git workflow

Ce git workflow decrit l'utilisation de Git dans le cas d'un travail de groupe. Il n'est pas pertinent dans le contexte du 21sh.
Je le rajoute ici cependant, pour spreader son contenu, et parceque le 21sh est pour le moment le premier projet sur mon overview Github ^^


(c'est partit pour l'explication de la MAGIE)

![magiiiiiiiiiie](http://ljdchost.com/Gon7Sw7.gif)

Si vous ignorez ce qu'est un Git worflow, je vous conseille cet excellent texte : [awesome link](https://www.atlassian.com/git/tutorials/comparing-workflows)

Voici comment nous procéderons:

La branche **master** n'aura pour utilité que de rassembler les versions fonctionnelles du shell. En soit, personne ne pushera dessus.

Nous travaillerons sur la branche **develop**.

Pour chaque nouvelle feature sur laquelle une seule personne travaillera, il sera créé une nouvelle branche "**XXXX**".

### Noms de commit

Autant que possible, rendez vos noms de commit utiles et intuitifs.

Chaque commit devra, dans la mesure du possible renvoyer une version "fonctionnelle" de l'avancement de la feature. Ainsi, pas de commits ayant pour nom "code" "more code" "blah blah" "wfewefgaergaehbr er" ...

Les commits peuvent être de la longueur que vous voulez, abrégez vos "réparation de segfaults" en "Fix SF" pour normer vos commits, mais soyez libre de les documenter sur les lignes suivantes.

Pensez comme ceci: la première ligne est le titre, les autres sont la description.
ecrivez donc:

```
git cm "Fix SF on CI
Case: Empty line putted into the Command Interpretor"
```

Il est inutile de signer vos commits, git s'en charge à votre place. Soyez juste bien certains d'avoir renseignez votre login et votre email dans le gitconfig.

### /!\ Méthode de merge

Quand la feature sera achevée, la branche sera mergee sans fast forward vers develop ou la branche parente (bien sur sentez vous libre de créer autant de branche que cela vous semblera utile).

Je vous conseil d'ajouter ces quelques lignes dans la section alias de votre ~/.gitconfig (pour plus de détails quant aux alias git et leur utilisation, appliquez le protocole RTFM)

```
    au = add -u
*   cb = checkout -b
    cl = clone
    cm = commit -m
    co = checkout
    st = status
    br = branch
    rv = remote -v
*   me = merge --no-ff -m
    st = status
    pu = push
    su = submodule update --remote
    lo = log --graph --abbrev-commit --decorate --format=format:'%C(bold blue)%h%C(reset) - %C(bold white)%s%C(reset) %C(bold green)(%ar)%C(reset)%C(bold yellow)%d%C(reset)%n''          %C(cyan)%aD%C(reset)%C(white) - %an%C(reset)%n' --all
```

Certaines sont bateau et peuvent vous donner de belles idées, je me reporterais aux highlighted dans l'explication qui va suivre, quant à **lo**, il n'est pas obligatoire et tout à fait modifiable selon vos envies, il est juste cool et pratique.

Pour toute question quant à la signification exacte de chaque option, reportez vous au protocole RTFM, sauf pour celles ci qui vous sont gracieusement expliquées par votre serviteur et dieu.

**cb**

"checkout" sert à se déplacer dans toutes les directions dans les branches et les commits. L'option -b suivie d'un nom, créera une nouvelle branche a ce nom, et positionnera Git dessus.

**me**

"merge some_branch" mergera la branche cible vers la branche courante (soyez donc sur d'être bien positionné).
l'option --no-ff empêche le fast forward.

Qu'est ce que le ff? Quand git voit que la branche cible se trouve dans la continuité de la branche courante, il ne mergera pas les modification mais "décalera" les commits. En somme, il fera comme si la branche mergee n'avait jamais existé et que le travail qui avait ete fait dessus avait en réalité été directement pushé sur la branche courante.
C'est donc le mal,

*imaginez si on mergeait develop en fast-forward sur master ...*

![git merge develop](http://tclhost.com/HalfComplexConure-size_restricted.gif)

dev team:

![fwe](http://ljdchost.com/MkjU8sy.gif)

l'option -m vous permet de taper le message en ligne de commande (entre quotes).

en somme vous taperez avant et après avoir code une feature::

(depuis la branche develop)
```
git cb myfeature
.... some code stuff
git cm "Add Chocobo AI
Usefull stuff added. Very good. It's true."
....
git cm "Fix SF
Case : Lorem Ipsum dolor sit amet..."
...
git co develop
git cm "Merge myfeature into develop" myfeature
```

*Pour plus de clarté, le message de merge doit être du type "Merge XXXX into XXXX"*

**VOICI POUR L'UTILISATION DE GIT ET DU REPO EN GENERAL**

```Toute erreur sera réparée, mais vous pâtirez d'un lourd regard de reproche.```

![regard](http://ljdchost.com/WljQddo.gif)

```Dans le doute, relisez ce fichier ou demandez moi ;)```

![Akasha](http://ljdchost.com/u9FX3.gif)

## Arborescence

La racine du repo contiendra le Makefile du projet, le dossier de la libft collaborative, le dossier includes contenant les .h, et le dossier srcs, organise en une arborescence selon l'utilité des fichiers qu'il contient.

Ce README.md vous a ete fourni par Akasha (nmougino),
si une remise en question vous semble pertinente, n'hésitez pas à m'en faire part :)

Encore désolé pour le ton de gros git-nazi avec lequel j'ai écrit ça, mais cet abruti de Dilinger a tout effacé et j'ai été forcé de tout réécrire...

En plus de ca, travailler en groupe sur git sans workflow etabli, c'est travailler avec cette tete:

![raven](http://i.imgur.com/wNSSJrq.gif)
