# API WEB BLINX

Voici les différents endpoint de l'api : `http://host/bc`, `http://host/br`, `http://host/bd`, `http://host/bl`, `http://host/bb` et `http://host/... .csv`.

L'`host` peut soit être l'adresse ip du blinx ou `BLINX000.local`, avec `000` l'id du blinx qui peut varier.

Les arguments peuvent être donné soit en get soit en post. Il y a 2 arguments qui sont récurrent à tous les endpoint : `?seqnum` qui signifie qu'on veut que les résultats soient encapsuler dans un png, ce qui est utilisée par codeboot. Et `content`, qui pourra contenir tous les autres arguments encoder en base64, par exemple au lieu de donner `a=0` comme argument on va donner `content=YT0w`.

# `bc`

Ce endpoint permet de configurer les ports analogues du blinx.

On peut fournir 4 arguments optionnel : `port1A`, `port1B`, `port2A` et `port2B`.
Les arguments vous spécifier le port et la valeur des arguments le type de sensor (voir [documentation tasmota](https://tasmota.github.io/docs/Components-old/#gpio-conversion)) qui doivent être le nom et pas le gpio (sans le nombre à la fin). Les deux types les plus importants sont `PWM` et `Relay`

```
http://BLINX000.local/bc?port1A=PWM&port1B=Relay
```

# `br`

Ce endpoint permet de configurer les sensors de type on/off, par exemple les leds, les relays ...

On doit fournir 2 arguments : `device`, `action`.

`device` va permettre de savoir quel sensor vous voulez modifé, à l'aide du port. On s'attend à avoir : `Port1A`, `Port1B`, `Port2A` ou `Port2B`.
`action` représente l'action que vous voulez éxecuter. On s'attend à avoir : `off`, `on`, `toggle` ou `blink`.

```
http://BLINX000.local/bc?device=Port1A&action=off
```

# `bd`

Ce endpoint permet de configurer le display.

On peut fournir 4 arguments optionnel :

# `bl`

# `bb`

# `.csv`

