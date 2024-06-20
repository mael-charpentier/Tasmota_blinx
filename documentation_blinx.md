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


# add buffer to sensor

Il y a 2 cas, on veut modifier un senseur déjà existants ou on veut ajouter un senseur de 0. Les senseurs qui nous intéresse sont les `xsns` (`tasmota/tasmota_xsns_sensor`).

## senseur déjà existants

Le senseur devrait déjà avoir une fonction à la fin de son fichier, nommée `Xsns00`, avec `00` l'id du senseur.
Nous allons modifier cette function, pour rajouter des cas au switch :
```cpp
  #ifdef BLINX
        case FUNC_EVERY_50_MSECOND:
          saveData(...);
          break;
        case FUNC_EVERY_SECOND:
          saveData(...);
          break;
        case FUNC_EVERY_SECOND:
          saveData(...);
          break;
        case FUNC_EVERY_10_SECOND:
          saveData(...);
          break;
        case FUNC_EVERY_MINUTE:
          saveData(...);
          break;
        case FUNC_EVERY_10_MINUTE:
          saveData(...);
          break;
        case FUNC_EVERY_HOUR:
          saveData(...);
          break;
  #endif  // BLINX
```
On ne va rajouter le premier cas, seulement si on veut que le senseur soit lu toutes les 50ms.

La function `saveData` va être une fonction qu'on va créer pour lires les donnéees des senseurs et les sauvegarder.

Nous allons ensuite créer 3 functions après celle-ci :
```cpp
#ifdef BLINX

int Xsns00_size_data(uint32_t phantomType = 0, uint32_t phantomData = 0){
  return ...;
}

int Xsns00_size_name(uint32_t phantomType = 0, uint32_t phantomData = 0){
  return ...;
}

int Xsns00(uint32_t function, uint32_t index_csv, uint32_t phantomType = 0, uint32_t phantomData = 0) {
  ...
    switch (function) {
        case FUNC_WEB_SENSOR_BLINX_SIZE_DATA:
          return Xsns00_size_data(phantomType, phantomData);
        case FUNC_WEB_SENSOR_BLINX_SIZE_NAME:
          return Xsns00_size_name(phantomType, phantomData);
        case FUNC_WEB_SENSOR_BLINX_50ms:
          show(phantomType, phantomData, 0, index_csv);
          break;
        case FUNC_WEB_SENSOR_BLINX_1s:
          show(phantomType, phantomData, 1, index_csv);
          break;
        case FUNC_WEB_SENSOR_BLINX_10s:
          show(phantomType, phantomData, 2, index_csv);
          break;
        case FUNC_WEB_SENSOR_BLINX_1m:
          show(phantomType, phantomData, 3, index_csv);
          break;
        case FUNC_WEB_SENSOR_BLINX_10m:
          show(phantomType, phantomData, 4, index_csv);
          break;
        case FUNC_WEB_SENSOR_BLINX_1h:
          show(phantomType, phantomData, 5, index_csv);
          break;
    }
  ...
  return -1;
}

#endif  // BLINX
```

La function `Xsns00_size_data` va retourner la taille que prend un data.

La function `Xsns00_size_name` va retourner la taille que prend le nom du senseur.

Pour la nouvelle function `Xsns00`, qu'on vient de créer, vous aller faire :

- un copier-coller de la function `Xsns00`
- on va changer :
  - ce que retourne la fonction,
  - ce que la fonction prend en paramètre,
  - le switch

La function `show` appeler dans le switch va être une fonction qu'on va créer plus tard, pour afficher les données du senseurs.

L'argument `phantomType` est utilisé sur on lit différent type du même senseur, par exemple le senseur sht3xpeut lire de 3 senseurs différent : `sht3x`, `sht3c` et `sht4x`.

L'argument `phantomData` est utilisé sur on lit différent données du même senseur, par exemple le senseur sht3x lit 2 données différentes : la température et l'humidité.
Donc si `phantomData=0` on va montrer les 2 données, si `phantomData=1` on va montrer une donnée (par exemple la température) et si `phantomData=2` on va montrer l'autre donnée (par exemple 'humidité).

Pour trouver la function detect, dont je parle plus tard, vous allez dans la fonction `Xsns00`. À l'intérieur vous devriez avoir `if (FUNC_INIT == function) { ... }` qui fait un appel de fonction. La fonction qu'il appel est la fonction detect.

Revenons au début du fichier, just avant la function detect, on va ajouter :
```cpp
#ifdef BLINX

bufferSensor* namebuffer = nullptr;

#endif // BLINX
```
Avec le nom que vous voulez, cela va être le buffer où on va stocker les données. Si le senseur va récolter différentes données ou pour différent type de senseur, comme pour le sht3x, on va :
```cpp
#ifdef BLINX

bufferSensor* namebuffer[size1][size2] = {};

#endif // BLINX
```
Avec `size1` le nombre de différente donnée qu'on va prendre (pour le sht3x cela va être 2 : temperature et humidité) et `size2` le nombre de différent senseur (pour le shtx cela va être `SHT3X_ADDRESSES`).

Maintenant, à l'intérieur de la fonction detect, une fois qu'on a détecter un senseur on va mettre ce code :
```cpp
#ifdef BLINX

namebuffer = initBufferSensor(6);

#endif // BLINX
```
Ce qui va initialiser le buffer, ici on a `6` car on veut les 50ms, si ce n'est pas le cas, on doit mettre `5`;

Après la function detect, nous allons créer différents functions :
```cpp
#ifdef BLINX

void saveData(uint8_t ind) {
  if(ind == 0){
    getData();
    return;
  }

    if (namebuffer == nullptr) {
      namebuffer = initBufferSensor(6);
      namebuffer->buffer[ind].save(0);
    } else{
      namebuffer->save(ind);
    }
}

void sendFunction(uint16_t val){
    blinx_send_data_sensor(true, PSTR("%d"), val);
}

void show(uint8_t ind, uint32_t index_csv) {
  if (index_csv == 0){
      blinx_send_data_sensor(false, PSTR(",name_senseur"));
  } else{
      blinx_send_data_sensor(false, PSTR(","));
      namebuffer->buffer[ind].getData(index_csv, &sendFunction);
  }
}

#endif
```
Cela va être les functions pour enregistrer les données et afficher les données, j'ai donné un exemple, mais vous devait vous inspirer du code pour créer ces fonctions. Normalement il y a déjà une fonction pour aller chercher les données et une autre pour afficher les données.

Il y a une fonction supplémentaire `sendFunction` qui est là pour dire comment on veut afficher les données, s'il y a des calculs à effectuer avant de les affichers c'est ici ...

Pour la fonction show, l'argument `index_csv` va spécifier l'index qu'on veut afficher, sachant que pour l'index 0 on veut le nom du senseur.

## si le senseur n'existe pas

La librairy du senseur doit être mis dans le dossier `lib/libeps32` ou `lib/lib_i2c`.
Et le fichier pour le senseur doit être mis dans le dossier `tasmota/tasmota_xsns_sensor`.

Voici à quoi doit ressemble le fichier du sensor :
```cpp
#ifdef USE_I2C
#ifdef USE_sensor


#include "sensor.h"


#ifdef BLINX

bufferSensor* namebuffer = nullptr;

#endif // BLINX

void Detect(void) {
  for (uint32_t bus = 0; bus < 2; bus++) {
    ...
    if(detected){
      #ifdef BLINX
        namebuffer = initBufferSensor(5); // 6 if we want the 50ms
      #endif // BLINX
    }
  }
}


#ifdef BLINX

void getData() {
  ...
}

void saveData(uint8_t ind) {
  if(ind == 0){
    getData();
    return;
  }

    if (namebuffer == nullptr) {
      namebuffer = initBufferSensor(6);
      namebuffer->buffer[ind].save(0);
    } else{
      namebuffer->save(ind);
    }
}

void sendFunction(uint16_t val){
    blinx_send_data_sensor(true, PSTR("%d"), val);
}

void showBlinx(uint8_t ind, uint32_t index_csv) {
  if (index_csv == 0){
      blinx_send_data_sensor(false, PSTR(",name_senseur"));
  } else{
      blinx_send_data_sensor(false, PSTR(","));
      namebuffer->buffer[ind].getData(index_csv, &sendFunction);
  }
}

#endif

void Show(bool json) {
  ...
}

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

bool Xsns00(uint32_t function) {
  if (!I2cEnabled(XI2C_id)) { return false; }

  bool result = false;

  if (FUNC_INIT == function) {
    Detect();
  }
  else {
    switch (function) {
  #ifdef BLINX
        case FUNC_EVERY_SECOND:
          saveData(0);
          break;
        case FUNC_EVERY_10_SECOND:
          saveData(1);
          break;
        case FUNC_EVERY_MINUTE:
          saveData(2);
          break;
        case FUNC_EVERY_10_MINUTE:
          saveData(3);
          break;
        case FUNC_EVERY_HOUR:
          saveData(4);
          break;
  #endif  // BLINX
      case FUNC_JSON_APPEND:
        Show(1);
        break;
  #ifdef USE_WEBSERVER
      case FUNC_WEB_SENSOR:
        Show(0);
        break;
  #endif  // USE_WEBSERVER
    }
  }
  return result;
}

#ifdef BLINX

int Xsns00_size_data(uint32_t phantomType = 0, uint32_t phantomData = 0){
  return ...;
}

int Xsns00_size_name(uint32_t phantomType = 0, uint32_t phantomData = 0){
  return ...;
}

int Xsns00(uint32_t function, uint32_t index_csv, uint32_t phantomType = 0, uint32_t phantomData = 0) {
  ...
    switch (function) {
        case FUNC_WEB_SENSOR_BLINX_SIZE_DATA:
          return Xsns00_size_data(phantomType, phantomData);
        case FUNC_WEB_SENSOR_BLINX_SIZE_NAME:
          return Xsns00_size_name(phantomType, phantomData);
        case FUNC_WEB_SENSOR_BLINX_50ms:
          showBlinx(phantomType, phantomData, 0, index_csv);
          break;
        case FUNC_WEB_SENSOR_BLINX_1s:
          showBlinx(phantomType, phantomData, 1, index_csv);
          break;
        case FUNC_WEB_SENSOR_BLINX_10s:
          showBlinx(phantomType, phantomData, 2, index_csv);
          break;
        case FUNC_WEB_SENSOR_BLINX_1m:
          showBlinx(phantomType, phantomData, 3, index_csv);
          break;
        case FUNC_WEB_SENSOR_BLINX_10m:
          showBlinx(phantomType, phantomData, 4, index_csv);
          break;
        case FUNC_WEB_SENSOR_BLINX_1h:
          showBlinx(phantomType, phantomData, 5, index_csv);
          break;
    }
  ...
  return -1;
}

#endif  // BLINX

#endif  // USE_sensor
#endif  // USE_I2C
```
Vous devez changer : `USE_sensor`, `Xsns00`, `XI2C_id`.

De plus, il faudra changer le compilateur pour qu'il define le `USE_sensor`. Sinon, le senseur ne sera pas activé.

Pour d'informations sur ce que j'ai mis, voir la section au dessus.

Vous pouvez bien sûr rajouter des variables, des functions, ... et modifier ce que j'ai mis.