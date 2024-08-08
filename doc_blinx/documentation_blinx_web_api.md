# BLINX API WEB

## Endpoints
Here are the various endpoints of the API : `http://host/bc`, `http://host/br`, `http://host/bd`, `http://host/bl`, `http://host/bp`, `http://host/bi`, `http://host/bn` and `http://host/... .csv`.

the `host` can either be the IP address of the Blinx or `BLINX000.local`, where `000` is the Blinx ID, which can vary.

Arguments can be provided via GET or POST requests. There is one argument common to all endpoints: `content`, which can contain all other arguments encoded in base64. For example, instead of providing `a=0` as an argument, you would provide `content=YT0w`.

### `bc`

This endpoint allows you to configure the analog ports of the Blinx.

Arguments :

- `port1A` (optional),
- `port1B` (optional),
- `port2A` (optional),
- `port2B` (optional)

At least one argument is required; otherwise, no changes will be made.
The arguments specify the port and the value of the arguments determines the type of sensor. Here is the list of type accepted by blinx :

- Relay
- Relay_i
- PWM
- PWM_i
- ADC Joystick
- ADC Input
- ADC Temp
- ADC Light
- ADC Button
- ADC Button_i
- ADC Range
- ADC CT Power

The `_i` is for inverse.

```
http://BLINX000.local/bc?port1A=PWM&port1B=Relay
```

### `br`

This endpoint allows you to configure on/off type sensors, such as LEDs, relays ...

Arguments :

- `device` specifies which sensor you want to modify, using the port. Expected values are: `Port1A`, `Port1B`, `Port2A` ou `Port2B`.
- `action` represents the action you want to execute. Expected values are: `off`, `on`, `toggle` ou `blink`.

```
http://BLINX000.local/br?device=Port1A&action=off
```

### `bd`

This endpoint allows you to configure the display.

Arguments :

- `DisplayMode` (optional), manages the display mode. For different modes, see [documentation tasmota](https://tasmota.github.io/docs/Displays/#displaymode). An additional mode, mode 6, is specific to Blinx and displays the hostname on the first line alternating with the SSID, and the remaining three lines show sensor data. Expected values are integers from 0 to 6, inclusive.
- `DisplayDimmer` (optional), controls the display brightness. Expected values are integers from 0 to 100, inclusive, with 0 to turn off the display.
- `DisplaySize` (optional), scales the display content. Expected values are integers from 1 to 4, inclusive.
- `DisplayRotate` (optional), rotates the display content. Expected values are integers from 0 to 3, inclusive, where 0 represents 0°, 1 represents 90°, 2 represents 180°, and 3 represents 270°.
- `DisplayText` (optional), changes the text displayed. This argument only works if the mode is set to 0. For special displays, refer to the [documentation de tasmota](https://tasmota.github.io/docs/Displays/#displaytext).

At least one argument is required; otherwise, no changes will be made.

```
http://BLINX000.local/bd?DisplayMode=0&DisplayText=Hello, World
```

### `bp`

This endpoint allows you to configure PWM type sensors, such as some motor.

Arguments :

- `device`, identifies the sensor and must be one of the following: `buzzer`, `Port1A`, `Port1B`, `Port2A` ou `Port2B`.
- `freq` (optional), manages the frequency.
- `value` (optional), manages the value.
- `phase` (optional), manages the phase.

At least one optional argument is required; otherwise, no changes will be made.

```
http://BLINX000.local/bp?device=buzzer&freq=100&value=50
```

### `bi`

This endpoint provides information about the Blinx.

Returned information includes: list of connected sensors (I2C and analog), hostname, IP address, MAC address, and Blinx version.

Par exemple :
```json
{"sensorI2C":{"SHTC3":{"Temperature":{"access_name":"sht3c_temp","value":"28.1"}, "Humidity":{"access_name":"sht3c_humi","value":"41.4"}}},"analog":{"1A":{"name":"None"},"1B":{"name":"None"},"2A":{"name":"None"},"2B":{"name":"None"},"default":{"name":"None"}},"Hostname":"blinx133","IPAddress":"192.168.10.123","Mac":"DC:54:75:B4:..:..", "VersionBlinx" : "1.0.0", "VersionTasmota" : "13.4.0"}
```

### `bn`

This endpoint allows you to change the hostname of Blinx used for mDNS.

You must provide one argument: `name`, which will contain the new hostname.
```
http://BLINX000.local/bn?name=BLINX000
```

### `.csv`

This endpoint allows you to obtain sensor data in CSV format.

Arguments :
- `delta` specifies the time interval. Expected values are `50ms`, `1s`, `10s`, `1m`, `10m` or `1h`.
- `n` specifies how many data points you want.

To specify sensors, write the sensor names before the `.csv , with each name separated by a comma. If no sensors are specified, all connected sensors will be returned.

```
http://blinx000.local/sht3c_temp,sht3c_humi.csv?delta=1s
http://blinx000.local/.csv?delta=1s&n=20
```

Here is the list of sensor names:

- counter
- analog_1A (analog sensor)
- analog_1B (analog sensor)
- analog_2A (analog sensor)
- analog_2B (analog sensor)
- ds18x20_temp (temperature sensor)
- sht3x_temp (temperature sensor)
- sht3x_humi (humidity sensor)
- sht3c_temp (temperature sensor)
- sht3c_humi (humidity sensor)
- sht4x_temp (temperature sensor)
- sht4x_humi (humidity sensor)
- vl53l0x (distance sensor)


##  GET Arguments

You can also make requests to the API using GET arguments on the root endpoint, in base64 with `content` : `http://host/??seqnum=...&content=...`. To use this, you must include the `?seqnum` argument with any value, otherwise, it will not work.

Different arguments, possible to give to `content`:

- `version`, gives you the version of Blinx
- `restart`, allows you to restart Blinx
- `config`=`arguments for configuration`. The expected arguments are the same as for [endpoint `bc`](#bc).
- `screen`=`arguments to change the screen`. The expected arguments are the same as for [endpoint `bd`](#bd).
- `SENSOR`=`arguments to change the sensor output SENSOR`, where `SENSOR` need to be etither `led`, `buzzer`, `Port1A`, `Port1B`, `Port2A` or `Port2B`. Expected arguments are the same as for [endpoint `bp`](#bp) (without the `device` argument) if the sensor is a PWM/motor/... However, if the sensor is of type relay/led/..., the action should be provided directly.

The values of the sub-arguments for `config`, `screen` and `SENSOR` should be in the format :
```
nomArg1=valArg1/nomArg2=valArg2
```
Same as you would do for the GET argument, but replace `&` by `/`, and don't use the `?` at the begining.

For example (text is in clear, but it should normally be in base64):
```
http://host/??seqnum=0&content=version
http://host/??seqnum=0&content=restart
http://host/??seqnum=0&content=config=port1A=PWM/port1B=Relay
http://host/??seqnum=0&content=DisplayMode=0/DisplayText=Hello, World
http://host/??seqnum=0&content=buzzer=freq=100/value=50
http://host/??seqnum=0&content=led=off
```