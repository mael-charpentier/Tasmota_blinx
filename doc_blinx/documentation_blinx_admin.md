# Important

For anything that involves serial port communication, follow these steps:

1. Make sure to use a Chromium-based browser, such as Google Chrome.
2. Click the "Connect" button or its equivalent.
3. Select the item containing Blinx from the window that opens, located in the top left.

# Compile the Firmware

We will use the tool: [blinxcompiler](https://github.com/mael-charpentier/blinxcompiler). Follow the README steps to install it, but for now, do not install it using Docker.

Next, select the necessary settings. Generally, the default settings should work. Here are some important actions you can take:

- Wi-Fi Configuration
  - Provides the information needed for Blinx to connect to Wi-Fi.
- Settings of the blinx
  - You can also set the name of the Blinx.
  - You can choose sizes for sensor buffers.


Once you have selected your options, click "Compile." Then click the `FIRMWARE.FACTORY.BIN` button to download the firmware.

# Install the Firmware

We will use the tool [tasmota install](https://tasmota.github.io/install/), which utilizes the serial port.

First, upload the firmware, then click `CONNECT` to connect to Blinx via the serial port.

Next, click `INSTALL TASMOTA (...)`, and follow the steps.

# Administer Blinx :

To administer Blinx, we will use : [BlinxAdmin](https://github.com/mael-charpentier/BlinxAdmin).