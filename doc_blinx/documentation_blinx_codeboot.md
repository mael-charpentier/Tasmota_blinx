# ATTENTION
this doc isn't valid, don't read.

# Configuration de blinx

Pour configurer blinx, suivez ces étapes :

1. Rendez-vous sur la page `...`. Assurez-vous d'utiliser un navigateur de type chromium, tel que Google Chrome.
2. Cliquez sur le bouton "Connecter".
3. Choisissez l'élément contenant blinx dans la fenêtre qui s'est ouverte, situé en haut à gauche.

Une fois connecté, vous avez plusieurs options :

- Obtenir le nom
- Modifier les options de blinx

## Obtenir le nom

Après avoir sélectionné cette option, vous devriez obtenir le nom du blinx.

## Modifier les options de blinx

Sélectionnez cette option pour modifier les informations de blinx. Voici les options importantes que vous pouvez faire :

- changer la configuration du wifi, pour les senseurs analogues
- changer le nom du blinx

# `blinx`

Le module `blinx` permet de communiquer avec votre blinx.
La classe `blinx.connection` permet de ce connecter à un blinx.
La propriétée `blinx.sensor` permet d'obtenir la liste des senseurs brancher à blinx.
La classe `blinx.get` permet d'obtenir les données des senseurs.
La classe `blinx.display` permet de modifier le comportements du display.
La classe `blinx.pwm` permet de modifier le comportements des senseurs de type PWM.
La classe `blinx.light` permet de modifier le comportements des senseurs de type light.
La classe `blinx.OnOff` permet de modifier le comportements des senseurs de type on/off, par exemple les led ou les buzzers.

## `blinx.connection()`

La classe `blinx.connection()` permet de ce connecter à un blinx, avant de pouvoir l'utiliser assurez-vous d'être sur le même réseau wifi que le blinx auquel vous souhaitez vous connecter. Ainsi que de connaître le nom du blinx, qui sera du style `BLINX000`, où `000` représente l'id du blinc et peut varier. Cliquez sur le bouton "...", puis entrez le nom du blinx dans le champ et cliquez sur "Connecter". Vous pouvez maintenant utiliser `blinx.connection('id')`.

Voici des examples d'utilisation :

```python
b = blinx.connection('000')

with blinx.connection('000') as b:
    ...
```

### note :

Pour vous connectez à un blinx, vous pouvez aussi utiliser `open('blinx://id')`, où `id` représente les 3 chiffres dans le nom du blinx. Vous avez également 2 options pour utiliser `open` :

```python
b = open('blinx://000')
```

## `blinx.sensor`

La propriétée `blinx.sensor` permet d'obtenir la liste des senseurs brancher à blinx.

```python
b = open('blinx://000')
print(b.sensor)
```

## `blinx.get(time, **names)`

La classe `blinx.get` permet d'obtenir les données des senseurs sous forme d'un csv.

L'argument `time` est qu'elle buffer vous voulez avoir accès. Il doit s'agir d'un string : `1s`, `10s`, `1m`, `10m` ou `1h`.

Les arguments optionnels `**names` permettre de choisir quel senseur vous voulez, si vous ne mettez pas de nom vous auriez tous les senseurs.

```python
b = open('blinx://000')
print(b.get('1s'))
print(b.get('1s', 'temp', 'humi'))
```

## `blinx.display(mode = null, dimmer = null, size = null, rotate = null, text = null)`

La classe `blinx.display` permet de modifier le comportements du display.

Tous les arguments sont optionnels, c'st vous qui choissiez ce que vous voulez modifier. Si la valeur est `null`, on va garder la valeur actuel du display.

L'argument `mode`, permet de modifier le mode du display (pour plus d'info voir la [documentation de tasmota](https://tasmota.github.io/docs/Displays/#displaytext)). Il y a un mode supplémentaire : le mode 6, qui est le mode par défault. Il permet d'affichier le nom du blinx, le nom du wifi et les senseurs. Il doit s'agir d'un int compris entre 0 et 6, inclus.

L'arguments `dimmer` représente l'intensité du senseur. Il doit s'agir d'un int compris entre 0 et 100, inclus, avec 0 pour éteind et 100 l'intensité maximale.

L'arguments `size` permet de scale ce qui est affiché. Il doit s'agir d'un int compris entre 1 et 4, inclus.

L'arguments `rotate` permet de rotate ce qui est affiché. Il doit s'agir d'un int compris entre 0 et 3, inclus. Avec 0 qui représente 0°, 1 pour 90°, 2 pour 180° et 3 pour 270°.

L'arguments `text` permet de changer le texte qui est affiché. Pour pouvoir utiliser cet argument, il faut que le mode soit sur 0. Si vous voulez afficher des choses spéciaux voir [documentation de tasmota](https://tasmota.github.io/docs/Displays/#displaytext). Il doit s'agir d'un string.


```python
b = open('blinx://000')
print(b.display(mode = 0, text = 'Hello World'))
print(b.display(dimmer = 0))
```

## `blinx.pwm(index, freq = null, value = null, phase = null)`

La classe `blinx.pwm` permet de modifier le comportements des senseurs de type PWM.

Tous les arguments sont optionnels, sauf index, c'st vous qui choissiez ce que vous voulez modifier. Si la valeur est `null`, on va garder la valeur actuel.

L'argument `index`, permet d'indentifé les senseurs PWM. Il doit s'agir d'un int.

L'arguments `freq` représente la fréquence du senseur, en Hz. Il doit s'agir d'un int.

L'arguments `value` représente la valeur du senseur. Il doit s'agir d'un int.

L'arguments `phase` représente la phase du senseur. Il doit s'agir d'un int.

```python
b = open('blinx://000')
print(b.pwm(index = 0, freq = 50, value = 1000))
```

## `blinx.OnOff(device, action)`

La classe `blinx.OnOff` permet de modifier le comportements des senseurs de type on/off, par exemple les led ou les buzzers.

L'argument `device`, permet d'indentifé le senseur. Il doit s'agir d'un string : `Port1A`, `Port1B`, `Port2A` ou `Port2B`, on fonction où est brancé le senseur.

L'arguments `action` représente l'action que vous voulez éxecuter. Il doit s'agir d'un string : `off`, `on`, `toggle` ou `blink`.

```python
b = open('blinx://000')
print(b.OnOff("Port1A", 3))
```