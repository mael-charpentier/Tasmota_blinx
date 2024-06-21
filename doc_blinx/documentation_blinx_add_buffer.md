
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