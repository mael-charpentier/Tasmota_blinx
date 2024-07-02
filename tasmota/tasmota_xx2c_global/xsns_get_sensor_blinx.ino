

#ifdef BLINX

int blinxFindSensor(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 0) { return -1; }
    else if (input[0] == 'a'){
        return blinxFindSensor_A(input, l, function, index_csv);
    }
    else if (input[0] == 's'){
        return blinxFindSensor_S(input, l, function, index_csv);
    }
    else if (input[0] == 'v'){
        return blinxFindSensor_V(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_A(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 1) { return -1; }
    else if (input[1] == 'n'){
        return blinxFindSensor_AN(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_AN(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 2) { return -1; }
    else if (input[2] == 'a'){
        return blinxFindSensor_ANA(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_ANA(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 3) { return -1; }
    else if (input[3] == 'l'){
        return blinxFindSensor_ANAL(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_ANAL(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 4) { return -1; }
    else if (input[4] == 'o'){
        return blinxFindSensor_ANALO(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_ANALO(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 5) { return -1; }
    else if (input[5] == 'g'){
        return blinxFindSensor_ANALOG(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_ANALOG(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 6) { return -1; }
    else if (input[6] == '_'){
        return blinxFindSensor_ANALOG_(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_ANALOG_(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 7) { return -1; }
    else if (input[7] == '1'){
        return blinxFindSensor_ANALOG_1(input, l, function, index_csv);
    }
    else if (input[7] == '2'){
        return blinxFindSensor_ANALOG_2(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_ANALOG_1(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 8) { return -1; }
    else if (input[8] == 'A'){
        if (l == 9){
            return Xsns02(function, index_csv, 1, 0);
        } else {
            return -1;
        }
    }
    else if (input[8] == 'B'){
        if (l == 9){
            return Xsns02(function, index_csv, 2, 0);
        } else {
            return -1;
        }
    }
    return -1;
}

int blinxFindSensor_ANALOG_2(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 8) { return -1; }
    else if (input[8] == 'A'){
        if (l == 9){
            return Xsns02(function, index_csv, 3, 0);
        } else {
            return -1;
        }
    }
    else if (input[8] == 'B'){
        if (l == 9){
            return Xsns02(function, index_csv, 4, 0);
        } else {
            return -1;
        }
    }
    return -1;
}

int blinxFindSensor_S(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 1) { return -1; }
    else if (input[1] == 'h'){
        return blinxFindSensor_SH(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SH(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 2) { return -1; }
    else if (input[2] == 't'){
        return blinxFindSensor_SHT(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 3) { return -1; }
    else if (input[3] == '3'){
        return blinxFindSensor_SHT3(input, l, function, index_csv);
    }
    else if (input[3] == '4'){
        return blinxFindSensor_SHT4(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT3(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 4) { return -1; }
    else if (input[4] == 'c'){
        return blinxFindSensor_SHT3C(input, l, function, index_csv);
    }
    else if (input[4] == 'x'){
        return blinxFindSensor_SHT3X(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT3C(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 5) { return -1; }
    else if (input[5] == '_'){
        return blinxFindSensor_SHT3C_(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT3C_(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 6) { return -1; }
    else if (input[6] == 'h'){
        return blinxFindSensor_SHT3C_H(input, l, function, index_csv);
    }
    else if (input[6] == 't'){
        return blinxFindSensor_SHT3C_T(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT3C_H(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 7) { return -1; }
    else if (input[7] == 'u'){
        return blinxFindSensor_SHT3C_HU(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT3C_HU(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 8) { return -1; }
    else if (input[8] == 'm'){
        return blinxFindSensor_SHT3C_HUM(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT3C_HUM(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 9) { return -1; }
    else if (input[9] == 'i'){
        if (l == 10){
            return Xsns14(function, index_csv, 2, 2);
        } else {
            return -1;
        }
    }
    return -1;
}

int blinxFindSensor_SHT3C_T(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 7) { return -1; }
    else if (input[7] == 'e'){
        return blinxFindSensor_SHT3C_TE(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT3C_TE(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 8) { return -1; }
    else if (input[8] == 'm'){
        return blinxFindSensor_SHT3C_TEM(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT3C_TEM(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 9) { return -1; }
    else if (input[9] == 'p'){
        if (l == 10){
            return Xsns14(function, index_csv, 2, 1);
        } else {
            return -1;
        }
    }
    return -1;
}

int blinxFindSensor_SHT3X(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 5) { return -1; }
    else if (input[5] == '_'){
        return blinxFindSensor_SHT3X_(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT3X_(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 6) { return -1; }
    else if (input[6] == 'h'){
        return blinxFindSensor_SHT3X_H(input, l, function, index_csv);
    }
    else if (input[6] == 't'){
        return blinxFindSensor_SHT3X_T(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT3X_H(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 7) { return -1; }
    else if (input[7] == 'u'){
        return blinxFindSensor_SHT3X_HU(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT3X_HU(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 8) { return -1; }
    else if (input[8] == 'm'){
        return blinxFindSensor_SHT3X_HUM(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT3X_HUM(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 9) { return -1; }
    else if (input[9] == 'i'){
        if (l == 10){
            return Xsns14(function, index_csv, 1, 2);
        } else {
            return -1;
        }
    }
    return -1;
}

int blinxFindSensor_SHT3X_T(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 7) { return -1; }
    else if (input[7] == 'e'){
        return blinxFindSensor_SHT3X_TE(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT3X_TE(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 8) { return -1; }
    else if (input[8] == 'm'){
        return blinxFindSensor_SHT3X_TEM(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT3X_TEM(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 9) { return -1; }
    else if (input[9] == 'p'){
        if (l == 10){
            return Xsns14(function, index_csv, 1, 1);
        } else {
            return -1;
        }
    }
    return -1;
}

int blinxFindSensor_SHT4(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 4) { return -1; }
    else if (input[4] == 'x'){
        return blinxFindSensor_SHT4X(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT4X(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 5) { return -1; }
    else if (input[5] == '_'){
        return blinxFindSensor_SHT4X_(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT4X_(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 6) { return -1; }
    else if (input[6] == 'h'){
        return blinxFindSensor_SHT4X_H(input, l, function, index_csv);
    }
    else if (input[6] == 't'){
        return blinxFindSensor_SHT4X_T(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT4X_H(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 7) { return -1; }
    else if (input[7] == 'u'){
        return blinxFindSensor_SHT4X_HU(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT4X_HU(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 8) { return -1; }
    else if (input[8] == 'm'){
        return blinxFindSensor_SHT4X_HUM(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT4X_HUM(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 9) { return -1; }
    else if (input[9] == 'i'){
        if (l == 10){
            return Xsns14(function, index_csv, 3, 2);
        } else {
            return -1;
        }
    }
    return -1;
}

int blinxFindSensor_SHT4X_T(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 7) { return -1; }
    else if (input[7] == 'e'){
        return blinxFindSensor_SHT4X_TE(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT4X_TE(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 8) { return -1; }
    else if (input[8] == 'm'){
        return blinxFindSensor_SHT4X_TEM(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_SHT4X_TEM(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 9) { return -1; }
    else if (input[9] == 'p'){
        if (l == 10){
            return Xsns14(function, index_csv, 3, 1);
        } else {
            return -1;
        }
    }
    return -1;
}

int blinxFindSensor_V(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 1) { return -1; }
    else if (input[1] == 'l'){
        return blinxFindSensor_VL(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_VL(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 2) { return -1; }
    else if (input[2] == '5'){
        return blinxFindSensor_VL5(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_VL5(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 3) { return -1; }
    else if (input[3] == '3'){
        return blinxFindSensor_VL53(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_VL53(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 4) { return -1; }
    else if (input[4] == 'l'){
        return blinxFindSensor_VL53L(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_VL53L(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 5) { return -1; }
    else if (input[5] == '0'){
        return blinxFindSensor_VL53L0(input, l, function, index_csv);
    }
    return -1;
}

int blinxFindSensor_VL53L0(String input, size_t l, uint32_t function, uint32_t index_csv){
    if (l == 6) { return -1; }
    else if (input[6] == 'x'){
        if (l == 7){
            return Xsns45(function, index_csv, 0, 0);
        } else {
            return -1;
        }
    }
    return -1;
}




int blinxFindSensorAll(uint32_t function, uint32_t index_csv){
   int sum = 0;
   sum += Xsns14(function, index_csv, 1, 1) + 1;
   sum += Xsns14(function, index_csv, 1, 2) + 1;
   sum += Xsns14(function, index_csv, 2, 1) + 1;
   sum += Xsns14(function, index_csv, 2, 2) + 1;
   sum += Xsns14(function, index_csv, 3, 1) + 1;
   sum += Xsns14(function, index_csv, 3, 2) + 1;
   sum += Xsns45(function, index_csv, 0, 0) + 1;
   sum += Xsns02(function, index_csv, 1, 0) + 1;
   sum += Xsns02(function, index_csv, 2, 0) + 1;
   sum += Xsns02(function, index_csv, 3, 0) + 1;
   sum += Xsns02(function, index_csv, 4, 0) + 1;
   return sum;
}

#endif