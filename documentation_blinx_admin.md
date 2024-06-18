Nous allons nous baser sur l'outil : [TasmoAdmin](https://github.com/TasmoAdmin/TasmoAdmin), dans le futur.

# Important

Pour tout ce qui se fait par port serial, suivez ces étapes :

1. Assurez-vous d'utiliser un navigateur de type chromium, tel que Google Chrome.
2. Cliquez sur le bouton "Connecter", ou un équivalent.
3. Choisissez l'élément contenant blinx dans la fenêtre qui s'est ouverte, situé en haut à gauche.

# Compiler le firmware

Nous allons utiliser l'outil : [tasmocompiler_blinx](https://github.com/MaelC001/tasmocompiler_blinx). Suiver les étapes du readme pour l'installer.

Ensuite, sélectionnez les paramètres nécessaires. En général, les paramètres par défaut devraient fonctionner. Voici les actions importantes que vous pouvez faire :

- la configuration du wifi
  - Permet de donner les informations pour que le blinx puisse ce connecter au wifi
- les paramètres :
  - Vous pouvez aussi définir le nom du blinx
  - Vous pouvez choisir les tailles pour les buffers des senseurs
  - Ce qui se passe aux différentes pins du microcontrolleur

Une fois que vous avez choisi vos différentes options, vous pouvez cliquer sur "Compiler". Puis cliquer sur le boutton `FIRMWARE.FACTORY.BIN` pour télécharger le firmware. 

# Installer le firmware

Nous allons utiliser l'outil [tasmota install](https://tasmota.github.io/install/). Qui utilise le port serial.

Vous devez d'abord uploader le firmware, puis cliquer sur `CONNECT` pour ce connecter au blinx par port serial.

Ensuite, cliquer sur `INSTALL TASMOTA (...)`, puis suivez les étapes.