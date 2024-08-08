
# Adding Buffer to Sensor

There are two cases: either we want to modify an existing sensor or we want to add a new sensor from scratch. The sensors we're interested in are the `xsns` ([`tasmota/tasmota_xsns_sensor`](./../tasmota/tasmota_xsns_sensor)).

## Existing Sensor

The sensor should already have a function at the end of its file, named `Xsns00`, with `00` as the sensor's ID. We will modify this function to add cases to the switch statement :
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
We will add the first case only if we want the sensor to be read every 50ms.

The `saveData` function will be one that we create to read sensor data and save it.

Next, we will create another function after this:
```cpp
#ifdef BLINX

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

For the new function `Xsns00` that we just created, you will:

- Copy and paste the `Xsns00` function.
- Change :
  - What the function returns,
  - The parameters the function takes,
  - The switch statement.

The `show` function called in the switch will be a function that we will create later to display sensor data.

The `phantomType` argument is used when reading different types from the same sensor; for example, the sensor sht3x can read from 3 different sensors: `sht3x`, `sht3c` and `sht4x`.

The `phantomData` argument is used when reading different data from the same sensor; for example, the sht3x sensor reads 2 different types of data: temperature and humidity. So if `phantomData=0` we will show both data, if `phantomData=1` we will show one data (e.g., temperature) and if `phantomData=2` we will show the other data (e.g., humidity).

To find the detect function, which I mention later, go into the `Xsns00` function. Inside you should find `if (FUNC_INIT == function) { ... }` which makes a function call. The function it calls is the detect function.

Returning to the beginning of the file, just before the detect function, we will add:
```cpp
#ifdef BLINX

bufferSensor* namebuffer = nullptr;
int32_t nanValue = ....;
int32_t errorValue = ....;

int32_t clampNameBlinx( int32_t v){
  return v;
}

#endif // BLINX
```
With the name you want, this will be the buffer where we store the data.

The variables `nanValue` and `errorValue` will store the error codes that the sensor will return if the value is out of the sensor’s range (`nanValue`) or if there was an error / it couldn’t read the data (`errorValue`). If the sensor doesn’t return data, you don’t need to create them. If Blinx receives the value `errorValue`, it will directly replace it with the last value it had. For `nanValue`, it will depend on the sensor, which is why we have the clampNameBlinx function, which will tell Blinx what to do with the value: if we return v (the input value and thus `nanValue`), Blinx will save the `nanValue` (for averages, if one of the values is `nanValue`, then the average will also be `nanValue`, the `nanValue` will be absorbing); otherwise, we can return another value that Blinx will use instead.

If the sensor collects different data or is of a different type, as for the sht3x, we will:
```cpp
#ifdef BLINX

bufferSensor* namebuffer[size1][size2] = {};

#endif // BLINX
```
With `size1` as the number of different data we will collect (for the sht3x, this will be 2: temperature and humidity) and `size2` as the number of different sensors (for shtx, this will be `SHT3X_ADDRESSES`).

Now, inside the detect function, once we have detected a sensor, we will put this code:
```cpp
#ifdef BLINX

namebuffer = initBufferSensor(6, true, true, clampNameBlinx, nanValue, errorValue);

#endif // BLINX
```
This will initialize the buffer, here we use `6` because we want the 50ms data, if not, we should use `5`.

The first two booleans indicate (in respective order) if the sensor has a `nanValue` and if the sensor has an `errorValue`. By default, these booleans are `false`. Then we pass the clamp function; by default, we will use `clampFunctionBlinx` (a function that directly returns the sensor value, hence `nanValue`). Finally, we pass the two errors values; by default, they are set to `0`.

After the detect function, we will create different functions:
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
These functions will be for saving and displaying data. I've provided an example, but you should use the code to create these functions. Normally, there is already a function to get data and another to display data.

There is an additional function `sendFunction` which specifies how we want to display the data, if there are calculations to be made before displaying, it will be done here.

For the show function, the `index_csv` argument specifies the index we want to display, knowing that for index 0 we want the sensor's name.

## If the Sensor Does Not Exist

The sensor library must be placed in the [`lib/libeps32`](./../lib/libeps32) or [`lib/lib_i2c`](./../lib/lib_i2c) directory.
And the sensor file must be placed in the [`tasmota/tasmota_xsns_sensor`](./../tasmota/tasmota_xsns_sensor) directory.

To see what it should look like, I recommend looking at the code for the [temperature and humidity sensor](./../tasmota/tasmota_xsns_sensor/xsns_14_sht3x.ino). Generally, the information that needs to be modified includes: `USE_sensor`, `Xsns00`, `XI2C_id`, as well as how to read and display the data.

Additionally, you will need to change the webcompiler to define `USE_sensor`. Otherwise, the sensor will not be activated.

For more information on parts related to Blinx in the file, see the section above.

# Show the Sensor on the Display

To display the sensor values on the display, you need to create a new function:
```cpp
#ifdef BLINX
bool Xsns00Name(bool first, bool json){
  if (first){
    if (json){
      ResponseAppend_P(PSTR(","));
    } else {
      blinx_send_data_sensor(false, PSTR(","));
    }
  }
  int v = get_value();
  first = true;
  if (json){
    ResponseAppend_P(PSTR("\"nameSensor\":{\"typeData\":\"%d\"}"), v);
  } else{
    blinx_send_data_sensor(false, PSTR("\"nameSensor\":{\"typeData\":\"%d\"}"), v);
  }
  return first;
}
#endif // BLINX
```
This function will send the sensor name (`nameSensor`) as a key in a JSON object, with the value being a JSON object that has as many elements as the sensor has data types. The elements will be: the type of data (e.g., `Temperature` or `Distance`) as the key and the current data as the value. For example, for the sht3c, it would be: `"SHTC3":{"Temperature":"25.8", "Humidity":"42.1"}`.


# Give blinx access the Sensor

For Blinx to access the sensor, you need to modify the `xsns_get_sensor_blinx.ino` file. To do this, use the Python file `prefixreeSearch.py` located in `tools/blinx`. You need to add your sensor to the `prefix_dict` dictionary, then execute the code. This will generate the code to be placed in the `xsns_get_sensor_blinx.ino` file.

By default, the code will assume you have written code to display data on the display; if not, you will need to comment out a line in the `blinxGetInfoSensorI2C` function.