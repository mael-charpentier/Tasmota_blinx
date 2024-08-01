#ifdef BLINX

int32_t clampFunctionBlinx(int32_t v){
  return v;
}

bufferSensor* initBufferSensor(int size, bool existNanValue = false, bool existErrorValue = false, FunctionClampType clamp = clampFunctionBlinx, int32_t nanValue = 0, int32_t errorValue = 0){
    AddLog(LOG_LEVEL_INFO, PSTR("9"));
  bufferSensor* temp = new bufferSensor(size, clamp, nanValue, existNanValue, errorValue, existErrorValue);
  int index = 0;
  if (size == 6){
    temp->activate(index, 0, 0);
    index ++;
  }
  
  temp->activate(index, 1, 20);
  index ++;
  
  temp->activate(index, 2, 10);
  index ++;
  
  temp->activate(index, 3, 6);
  index ++;
  
  temp->activate(index, 4, 10);
  index ++;
  
  temp->activate(index, 5, 6);

  return temp;
}



idDeviceBlinx getIdDeviceSensorBlinx(int priority, int device, bool stop){
    int nmb_total_sensor = 0;
    if (priority != 0){
        idDeviceBlinx t = getIdDeviceSensorBlinx(priority-1, device, false);
        nmb_total_sensor = t.id;
    }
    for (int y = 0; y<5; y++){
        String result = infoConfigBlinx.find_name_type(Settings->my_gp.io[infoConfigBlinx.pin_analog[y]], priority);
        if (result != ""){
            nmb_total_sensor ++;
        }
        if (stop && y == device){
            idDeviceBlinx t;
            t.id = nmb_total_sensor;
            t.name = result;
            return t;
        }
    }
    idDeviceBlinx t;
    t.id = nmb_total_sensor;
    t.name = "";
    return t;
}

void blinxGetInfoSensorAnalog(void){
    String listName[5] = {"1A", "1B", "2A", "2B", "default"};
    for (int i = 0; i<5; i++){
        String nameSensor = infoConfigBlinx.find_name_type(Settings->my_gp.io[infoConfigBlinx.pin_analog[i]]);
        if (nameSensor == ""){
            nameSensor = "None";
        }
        blinx_send_data_sensor(false, PSTR("\"%s\":{\"name\":\"%s\""), listName[i],
            nameSensor);

        blinx_send_data_sensor(false, PSTR("}"));

        if (i < 5-1){
            blinx_send_data_sensor(false, PSTR(","));
        }
    }
   
}

void blinxDisplayInfoSensor(void){
    String listName[5] = {"A1A", "A1B", "A2A", "A2B", "A0"};
    bool first = false;
    for (int i = 0; i<5; i++){
        String nameSensor = infoConfigBlinx.find_name_type(Settings->my_gp.io[infoConfigBlinx.pin_analog[i]]);
        if (nameSensor == ""){
            nameSensor = "None";
        }

        if(first){
            ResponseAppend_P(PSTR(","));
        }
        first = true;

        ResponseAppend_P(PSTR("\"%s\":{\"%s\":\"value\"}"), listName[i],
            nameSensor);
    }
    
    blinxGetInfoSensorI2C(first, true);
   
}


#endif