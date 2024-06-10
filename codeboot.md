# Configuration de blinx

Pour configurer blinx, suivez ces étapes :

1. Rendez-vous sur la page `...`. Assurez-vous d'utiliser un navigateur de type chromium, tel que Google Chrome.
2. Cliquez sur le bouton "Connecter".
3. Choisissez l'élément contenant blinx dans la fenêtre qui s'est ouverte, situé en haut à gauche.

Une fois connecté, vous avez plusieurs options :

- Obtenir le nom
- Compiler le firmware
- Installer le firmware
- Modifier les options de blinx

## Obtenir le nom

Après avoir sélectionné cette option, vous devriez obtenir le nom du blinx.

## Compiler le firmware

Après avoir choisi cette option, sélectionnez les paramètres nécessaires. En général, les paramètres par défaut devraient fonctionner. Voici les actions importantes que vous pouvez faire :

- la configuration du wifi
  - Permet de donner les informations pour que le blinx puisse ce connecter au wifi
- les paramètres :
  - Vous pouvez aussi définir le nom du blinx
  - Vous pouvez choisir les tailles pour les buffers des senseurs
  - Ce qui se passe aux différentes pins du microcontrolleur

Une fois que vous avez choisi vos différentes options, vous pouvez cliquer sur "Compiler". Une fois la compilation terminée, cliquez sur "Installer".

## Installer le firmware

Sélectionnez cette option, puis cliquez sur "Téléverser le firmware". Choisissez le fichier binaire et cliquez sur "Installer".

## Modifier les options de blinx

Sélectionnez cette option pour modifier les informations de blinx. Voici les options importantes que vous pouvez faire :

- changer la configuration du wifi
- changer le nom du blinx
- ce qui se passe aux différentes pins du microcontrolleur
- éxécuter des commandes pour blinx (voir la [documentation de tasmota](https://tasmota.github.io/docs/Commands/))

# `blinx`

Le module `blinx` permet de communiquer avec votre blinx.
La classe `blinx.connection` permet de ce connecter à un blinx.
La propriétée `blinx.sensor` permet d'obtenir la liste des senseurs brancher à blinx.
La classe `blinx.get` permet d'obtenir les données des senseurs.
La classe `blinx.send` permet de modifier le comportements des senseurs.

## `blinx.connection()`

La classe `blinx.connection()` permet de ce connecter à un blinx, avant de pouvoir l'utiliser assurez-vous d'être sur le même réseau wifi que le blinx auquel vous souhaitez vous connecter. Ainsi que de connaître le nom du blinx, qui sera du style `BLINX000`, où `000` peut varier. Cliquez sur le bouton "...", puis entrez le nom du blinx dans le champ et cliquez sur "Connecter". Vous pouvez maintenant utiliser `blinx.connection`.

Voici des examples d'utilisation :

```python
b = blinx.connection()

with blinx.connection() as b:
    ...
```

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

La classe `blinx.get` permet d'obtenir les données des senseurs.

L'argument `time` est qu'elle buffer vous voulez avoir accès. Il doit s'agir d'un string : `1s`, `10s`, `1m`, `10m` ou `1h`.

Les arguments optionnels `**names` permettre de choisir quel senseur vous voulez, si vous ne mettez pas de nom vous auriez tous les senseurs.

```python
b = open('blinx://000')
print(b.get('1s'))
print(b.get('1s', 'temp', 'humi'))
```

## `blinx.send(name, value)`

La classe `blinx.send` permet de modifier le comportements des senseurs.

L'argument `name` est le nom du senseur à modifier. Il doit s'agir d'un string.

L'arguments `value` est la nouvelle valeur du senseur. Il doit s'agir d'un string.

```python
b = open('blinx://000')
print(b.send('led', 'on'))
print(b.send('led', 'off'))
```