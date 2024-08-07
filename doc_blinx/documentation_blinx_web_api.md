# API WEB BLINX

## endpoint
Voici les différents endpoint de l'api : `http://host/bc`, `http://host/br`, `http://host/bd`, `http://host/bl`, `http://host/bp`, `http://host/bi`, `http://host/bn` et `http://host/... .csv`.

L'`host` peut soit être l'adresse ip du blinx ou `BLINX000.local`, avec `000` l'id du blinx qui peut varier.

Les arguments peuvent être donné soit en get soit en post. Il y a un argument qui est récurrent à tous les endpoint : `content`, qui pourra contenir tous les autres arguments encoder en base64, par exemple au lieu de donner `a=0` comme argument on va donner `content=YT0w`.

### `bc`

Ce endpoint permet de configurer les ports analogues du blinx.

Les arguments :

- `port1A` (optionnel),
- `port1B` (optionnel),
- `port2A` (optionnel),
- `port2B` (optionnel)

Il faut au moins qu'il y en ait un argument, sinon il ne se passe rien.
Les arguments vous spécifier le port et la valeur des arguments le type de sensor (voir [documentation tasmota](https://tasmota.github.io/docs/Components-old/#gpio-conversion)) qui doivent être le nom et pas le gpio (sans le nombre à la fin). Les deux types les plus importants sont `PWM` et `Relay`.

```
http://BLINX000.local/bc?port1A=PWM&port1B=Relay
```

### `br`

Ce endpoint permet de configurer les sensors de type on/off, par exemple les leds, les relays ...

Les arguments :

- `device` va permettre de savoir quel sensor vous voulez modifer, à l'aide du port. On s'attend à avoir : `Port1A`, `Port1B`, `Port2A` ou `Port2B`.
- `action` représente l'action que vous voulez éxecuter. On s'attend à avoir : `off`, `on`, `toggle` ou `blink`.

```
http://BLINX000.local/br?device=Port1A&action=off
```

### `bd`

Ce endpoint permet de configurer le display.

Les arguments :

- `DisplayMode` (optionnel), qui permet de gérer le mode du display, pour voir les différents modes voir [documentation tasmota](https://tasmota.github.io/docs/Displays/#displaymode). On a un mode supplémentaire, le mode 6, qui est propre à blinx. Ce mode permet d'afficher le hostname sur la première ligne avec le ssid (en alternance), puis les 3 autres lignes servent à afficher des senseurs. On s'attend d'avoir un int de 0 à 6, inclus.
- `DisplayDimmer` (optionnel), qui permet de gérer l'intensité du display, on s'attend d'avoir un int de 0 à 100, inclus. Avec 0 pour éteindre le display.
- `DisplaySize` (optionnel), qui permet de scale ce qui est affiché. Il doit s'agir d'un int compris entre 1 et 4, inclus.
- `DisplayRotate` (optionnel), qui permet de rotate ce qui est affiché. Il doit s'agir d'un int compris entre 0 et 3, inclus. Avec 0 qui représente 0°, 1 pour 90°, 2 pour 180° et 3 pour 270°.
- `DisplayText` (optionnel), qui permet de changer le texte qui est affiché. Pour pouvoir utiliser cet argument, il faut que le mode soit sur 0. Si vous voulez afficher des choses spéciaux voir [documentation de tasmota](https://tasmota.github.io/docs/Displays/#displaytext).

Il faut au moins qu'il y en ait un argument, sinon il ne se passe rien.

```
http://BLINX000.local/bd?DisplayMode=0&DisplayText=Hello, World
```

### `bp`

Ce endpoint permet de configurer les sensors de type pwm.

Les arguments :

- `device`, qui permet d'identifier le senseur, qui doit faire partie de la liste : `buzzer`, `Port1A`, `Port1B`, `Port2A` ou `Port2B`.
- `freq` (optionnel), qui permet de gérer la fréquence.
- `value` (optionnel), qui permet de gérer la value.
- `phase` (optionnel), qui permet de gérer la phase.

Il faut au moins qu'il y en ait un argument optinnel, sinon il ne se passe rien.

```
http://BLINX000.local/bp?device=buzzer&freq=100&value=50
```

### `bi`

Ce endpoint permet d'obtenir des informations à propos du blinx.

Les informations retournées sont : la listes des senseurs connectés, la liste des devices de type on/off, le hostname, l'adresse ip, la mac adresse et la version du blinx.

Par exemple :
```
{"sensor":["SHTC3":{"Temperature":"25.8", "Humidity":"42.1"}],"analog":{"1A":{"name":"None"},"1B":{"name":"None"},"2A":{"name":"None"},"2B":{"name":"None"},"default":{"name":"None"}},"Hostname":"blinx133","IPAddress":"192.168.10.123","Mac":"DC:54:75:B4:..:..", "Version" : "13.4.0"}
```

### `bn`

Ce endpoint permet de changer le hostname de blinx, utilisé pour le mdns.

On doit fournir un argument : `name` qui va contenir le nouveau hostname.

```
http://BLINX000.local/bn?name=BLINX000
```

### `.csv`

Ce endpoint permet de obtenir les donnéees des senseurs sous forme de csv.

Les arguments :
- `delta` qui va spécifir quel temps on veut avoir, on attend `50ms`, `1s`, `10s`, `1m`, `10m` ou `1h`.
- `n` pour spécifier combien de donnée on veut

Pour sécifier les senseurs, on doit écrire les noms des senseurs avant le `.csv`, avec une virgule entre chaque nom.
Si on ne spécifie pas de senseur, on va retourner tous les senseurs qui sont connectés.

```
http://blinx000.local/sht3c_temp,sht3c_humi.csv?time=1s
http://blinx000.local/.csv?time=1s
```

Voici la liste des noms des senseurs :

- counter
- analog_1A (senseur analog)
- analog_1B (senseur analog)
- analog_2A (senseur analog)
- analog_2B (senseur analog)
- ds18x20_temp (senseur de temperature)
- sht3x_temp (senseur de temperature)
- sht3x_humi (senseur d'humidité)
- sht3c_temp (senseur de temperature)
- sht3c_humi (senseur d'humidité)
- sht4x_temp (senseur de temperature)
- sht4x_humi (senseur d'humidité)
- vl53l0x (senseur de distance)


##  get argument

On peut aussi faire des requêtes à l'api à l'aide d'argument get sur le root, en base 64 avec `content` : `http://host/??seqnum=...&content=...`. Pour l'utiliser, vous devez utiliser l'argument `?seqnum` avec n'mporte quel valeur, sinon cela ne va pas fonctioner.

Les différents arguments :

- `version`, vous donne la version du blinx
- `restart`, permet de restart le blinx
- `config`=`argument pour la config`. Les arguments attendu sont les mêmes que pour [endpoint `bc`](#bc).
- `screen`=`argument pour changer le screen`. Les arguments attendu sont les mêmes que pour [endpoint `bd`](#bd).
- `SENSOR`=`argument pour changer le senseur output SENSOR`, avec `SENSOR` dans `led`, `buzzer`, `Port1A`, `Port1B`, `Port2A` ou `Port2B`. Les arguments attendu sont les mêmes que pour [endpoint `bp`](#bp) (sans l'argument `device`) si le senseur est un pwm/motor/... Cependant, si le senseur est de type relay/led/..., on s'attends à avoir directment l'action.

La valeur des sous-arguments pour `config`, `screen` et `SENSOR`, doivent être sous la forme :
```
nomArg1=valArg1/nomArg2=valArg2
```

Par exemple (le text est en claire, mais normalement ce serait en base 64) :
```
http://host/??seqnum=0&content=version
http://host/??seqnum=0&content=restart
http://host/??seqnum=0&content=config=port1A=PWM/port1B=Relay
http://host/??seqnum=0&content=DisplayMode=0/DisplayText=Hello, World
http://host/??seqnum=0&content=buzzer=freq=100/value=50
http://host/??seqnum=0&content=led=off
```