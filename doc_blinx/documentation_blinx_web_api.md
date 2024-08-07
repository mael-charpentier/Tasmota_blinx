# API WEB BLINX

Voici les différents endpoint de l'api : `http://host/bc`, `http://host/br`, `http://host/bd`, `http://host/bl`, `http://host/bp`, `http://host/bi`, `http://host/bn` et `http://host/... .csv`.

L'`host` peut soit être l'adresse ip du blinx ou `BLINX000.local`, avec `000` l'id du blinx qui peut varier.

Les arguments peuvent être donné soit en get soit en post. Il y a 2 arguments qui sont récurrent à tous les endpoint : `?seqnum` qui signifie qu'on veut que les résultats soient encapsuler dans un png, ce qui est notamment utilisée par codeboot. Et `content`, qui pourra contenir tous les autres arguments encoder en base64, par exemple au lieu de donner `a=0` comme argument on va donner `content=YT0w`.

## `bc`

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

## `br`

Ce endpoint permet de configurer les sensors de type on/off, par exemple les leds, les relays ...

Les arguments :

- `device` va permettre de savoir quel sensor vous voulez modifer, à l'aide du port. On s'attend à avoir : `Port1A`, `Port1B`, `Port2A` ou `Port2B`.
- `action` représente l'action que vous voulez éxecuter. On s'attend à avoir : `off`, `on`, `toggle` ou `blink`.

```
http://BLINX000.local/bc?device=Port1A&action=off
```

## `bd`

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

## `bl`

Ce endpoint permet de configurer les sensors de type light.

Les arguments :

- `d0` (optionnel), qui permet de gérer l'intensité des lights, on s'attend à un int de 0 à 100, inclus.
- `w0` (optionnel), qui permet de gérer la white value des lights, on s'attend à un int de 0 à 100, inclus.
- `ei` (optionnel), qui permet de changer la valeur des lights, avec `i` le numero de la light.
- `t0` (optionnel), qui permet de gérer la temperature des coleurs des lights, on s'attend à un int de 153 à 500, inclus.
- `h0` (optionnel), qui permet de gérer la teinte des lights, on s'attend à un int de 0 à 359, inclus.
- `n0` (optionnel), qui permet de gérer la saturation des lights, on s'attend à un int de 0 à 99, inclus.

Il faut au moins qu'il y en ait un argument, sinon il ne se passe rien.

```
http://BLINX000.local/bl?d0=50
```

## `bp`

Ce endpoint permet de configurer les sensors de type pwm.

Les arguments :

- `index`, qui permet d'identifier le senseur.
- `freq` (optionnel), qui permet de gérer la fréquence.
- `value` (optionnel), qui permet de gérer la value.
- `phase` (optionnel), qui permet de gérer la phase.

Il faut au moins qu'il y en ait un argument optinnel, sinon il ne se passe rien.

```
http://BLINX000.local/bp?index=0&freq=100&value=50
```

## `bi`

Ce endpoint permet d'obtenir des informations à propos du blinx.

Les informations retournées sont : la listes des senseurs connectés, la liste des devices de type on/off, le hostname, l'adresse ip, la mac adresse et la version du blinx.

Par exemple :
```
{"sensor":",sht3x_temp_SHTC3,sht3x_humi_SHTC3","DEVICE_on_off":["DEVICE_1","DEVICE_2","DEVICE_3"],"Hostname":"BLINX000","IPAddress":"192.168.0.10","Mac":"..:..:..:..:..:..", "Version" : "1.0.0"}
```

## `bn`

Ce endpoint permet de changer le hostname de blinx, utilisé pour le mdns.

On doit fournir un argument : `name` qui va contenir le nouveau hostname.

```
http://BLINX000.local/bn?name=BLINX000
```

## `.csv`

Ce endpoint permet de obtenir les donnéees des senseurs sous forme de csv.

On doit fournir un argument : `time` qui va spécifir quel temps on veut avoir, on attend `50ms`, `1s`, `10s`, `1m`, `10m` ou `1h`.

Pour sécifier les senseurs, on doit écrire les noms des senseurs avant le `.csv`, avec une virgule entre chaque nom.
Si on ne spécifie pas de senseur, on va retourner tous les senseurs qui sont connectés.

```
http://blinx000.local/sht3c_temp,sht3c_humi.csv?time=1s
http://blinx000.local/.csv?time=1s
```

