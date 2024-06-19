

#ifdef BLINX

int blinxFindSensor(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 0) { return -1; }
    else if (input[0] == 's'){
        return blinxFindSensorS(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensorS(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 1) { return -1; }
    else if (input[1] == 'h'){
        return blinxFindSensorSH(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensorSH(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 2) { return -1; }
    else if (input[2] == 't'){
        return blinxFindSensorSHT(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensorSHT(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 3) { return -1; }
    else if (input[3] == '3'){
        return blinxFindSensorSHT3(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensorSHT3(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 4) { return -1; }
    else if (input[4] == 'c'){
        return blinxFindSensorSHT3C(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensorSHT3C(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 5) { return -1; }
    else if (input[5] == '_'){
        return blinxFindSensorSHT3C_(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensorSHT3C_(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 6) { return -1; }
    else if (input[6] == 'h'){
        return blinxFindSensorSHT3C_H(input, l, function, index_csv);
    }
    else if (input[6] == 't'){
        return blinxFindSensorSHT3C_T(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensorSHT3C_H(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 7) { return -1; }
    else if (input[7] == 'u'){
        return blinxFindSensorSHT3C_HU(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensorSHT3C_HU(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 8) { return -1; }
    else if (input[8] == 'm'){
        return blinxFindSensorSHT3C_HUM(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensorSHT3C_HUM(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 9) { return -1; }
    else if (input[9] == 'i'){
        if (l == 10){
            return Xsns14(function, index_csv, 2);
        } else {
            return -1;
        }
    }
    return -1;
}

int blinxFindSensorSHT3C_T(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 7) { return -1; }
    else if (input[7] == 'e'){
        return blinxFindSensorSHT3C_TE(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensorSHT3C_TE(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 8) { return -1; }
    else if (input[8] == 'm'){
        return blinxFindSensorSHT3C_TEM(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensorSHT3C_TEM(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 9) { return -1; }
    else if (input[9] == 'p'){
        if (l == 10){
            return Xsns14(function, index_csv, 1);
        } else {
            return -1;
        }
    }
    return -1;
}




int blinxFindSensorAll(uint32_t function, uint32_t index_csv){
   int sum = 0;
   sum += Xsns14(function, index_csv, 1) + 1;
   sum += Xsns14(function, index_csv, 2) + 1;
   return sum;
}

#endif