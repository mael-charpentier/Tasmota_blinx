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

#endif