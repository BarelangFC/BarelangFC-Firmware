/* *************************************
 * ****************CLASS****************
 * *************************************/

class GY25 {
  public:
  /*
   *      GY25
   */
    char inChar;
    char dataYaw[7];
    char dataPitch[7];
    char dataRoll[7];
    String dataInIMU;
    int i;
    boolean parsing = false;
    int YAW,PITCH,ROLL = 0;
    int con360 = 0;
    int YAW360 = 0;
    int kalibrasi = 0;
    float hadap;
    float headImu;
    void setImu();
    void parsingData();
    void imuCalibration();
    /*
     *     Tombol
     */
    int strategyNumber = 0;
    int statusKill = 0;
    int tombol = 0;
    int tombol1 = 0;
    int prevTombol = 0;
    int prevTombol1 = 0;
    int killNRun = 0;
    int statusTombol = 0;
    int statusTombol1 = 0;
    void debounce();
    /*
     *     Timer
     */
    int time = 0;
    int time1 = 0;
    int debounceDelay = 70;
    int waktuTunggu = 5000;
    int timerLedOn;
    int timerLedOn1;
    int switchLedBlinking = 0;
    int switchStartLedOff = 0; 
    int timerLedOff = 0; 
    int finishLedBlinking = 0;
    /*
     *     Counting
     */
    int countButton = 0;
    int countButton1 = 0;
    int countTreshold = 15000;
    int countTreshold1 = 10000;
    int maxStrategyState = 0;
    int kalibrasiState = 0;
    /*
     *      Kirim data
     */
    char buff[50];
    void inits();
    void getData();
    void strategyDisplay();
    void killRun();
}; 
GY25 GY25;

/* *************************************
 * ****************METHOD****************
 * *************************************/

/////////////////////////////////////////////////////////////////////////////////
////////////////////////////Fungsi Strategy Display//////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
void GY25::strategyDisplay(){
  if(strategyNumber == 0 && killNRun == 0){
      digitalWrite(PB6, HIGH);
      digitalWrite(PB7, HIGH);
      digitalWrite(PB8, HIGH);
  }
  else if(strategyNumber == 1 && killNRun == 0){
      digitalWrite(PB6, LOW);
      digitalWrite(PB7, HIGH);
      digitalWrite(PB8, HIGH);
  }
  else if(strategyNumber == 2 && killNRun == 0){
      digitalWrite(PB6, HIGH);
      digitalWrite(PB7, LOW);
      digitalWrite(PB8, HIGH);
  }
  else if(strategyNumber == 3 && killNRun == 0){
      digitalWrite(PB6, LOW);
      digitalWrite(PB7, LOW);
      digitalWrite(PB8, HIGH);
  }
  else if(strategyNumber == 4 && killNRun == 0){
      digitalWrite(PB6, HIGH);
      digitalWrite(PB7, HIGH);
      digitalWrite(PB8, LOW);
  }
}

/////////////////////////////////////////////////////////////////////////////////
////////////////////////////Fungsi KillnRun Indicator////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
void GY25::killRun(){
  if(statusKill == 1 && killNRun == 0){
    digitalWrite(PB6, HIGH);
    digitalWrite(PB7, HIGH);
    digitalWrite(PB8, HIGH);
    delay(100);
    digitalWrite(PB8, LOW);
    delay(100);
    digitalWrite(PB7, LOW);
    delay(100);
    digitalWrite(PB6, LOW);
    delay(100);
    digitalWrite(PB6, HIGH);
    digitalWrite(PB7, HIGH);
    digitalWrite(PB8, HIGH);
    switchLedBlinking = 0;
    switchStartLedOff = 0; 
    finishLedBlinking = 0;
    statusKill = 0;
  }
  else if(killNRun == 1 && statusKill == 0){
    if(strategyNumber == 0){
      if(switchLedBlinking == 0 && switchStartLedOff == 0){
        timerLedOn = millis();
        digitalWrite(PB6, LOW);
        digitalWrite(PB7, LOW);
        digitalWrite(PB8, LOW);            
        switchStartLedOff = 1;
      }
      if((millis() - timerLedOn == 100) && (switchStartLedOff == 1) && (switchLedBlinking == 0)){
        timerLedOff = millis();
        switchLedBlinking = 1;
      }
      if((millis() - timerLedOff <= 100) && (switchStartLedOff == 1) && (switchLedBlinking == 1)){
        digitalWrite(PB6, HIGH);
        digitalWrite(PB7, HIGH);
        digitalWrite(PB8, HIGH);      
      }
      if(millis() - timerLedOff == 100){
        finishLedBlinking = 1;
      }
      if(switchLedBlinking == 1 && switchStartLedOff == 1 && finishLedBlinking == 1){
        switchLedBlinking = 0;
        switchStartLedOff = 0;
        finishLedBlinking = 0;
      }
    }
    else if(strategyNumber == 1){
      if(switchLedBlinking == 0 && switchStartLedOff == 0){
      timerLedOn = millis();
      digitalWrite(PB6, LOW);
      digitalWrite(PB7, HIGH);
      digitalWrite(PB8, HIGH);          
      switchStartLedOff = 1;
      }
      if((millis() - timerLedOn == 100) && (switchStartLedOff == 1) && (switchLedBlinking == 0)){
        timerLedOff = millis();
        switchLedBlinking = 1;
      }
      if((millis() - timerLedOff <= 100) && (switchStartLedOff == 1) && (switchLedBlinking == 1)){
        digitalWrite(PB6, HIGH);
      }
      if(millis() - timerLedOff == 100){
        finishLedBlinking = 1;
      }
      if(switchLedBlinking == 1 && switchStartLedOff == 1 && finishLedBlinking == 1){
        switchLedBlinking = 0;
        switchStartLedOff = 0;
        finishLedBlinking = 0;
      }
    }
    else if(strategyNumber == 2){
      if(switchLedBlinking == 0 && switchStartLedOff == 0){
        timerLedOn = millis();
        digitalWrite(PB6, HIGH);
        digitalWrite(PB7, LOW);
        digitalWrite(PB8, HIGH);
        switchStartLedOff = 1;
      }
      if((millis() - timerLedOn == 100) && (switchStartLedOff == 1) && (switchLedBlinking == 0)){
        timerLedOff = millis();
        switchLedBlinking = 1;
      }
      if((millis() - timerLedOff <= 100) && (switchStartLedOff == 1) && (switchLedBlinking == 1)){
        digitalWrite(PB7, HIGH);
      }
      if(millis() - timerLedOff == 100){
        finishLedBlinking = 1;
      }
      if(switchLedBlinking == 1 && switchStartLedOff == 1 && finishLedBlinking == 1){
        switchLedBlinking = 0;
        switchStartLedOff = 0;
        finishLedBlinking = 0;
      }
    }
    else if(strategyNumber == 3){
      if(switchLedBlinking == 0 && switchStartLedOff == 0){
        timerLedOn = millis();
        digitalWrite(PB6, LOW);
        digitalWrite(PB7, LOW);
        digitalWrite(PB8, HIGH);
        switchStartLedOff = 1;
      }
      if((millis() - timerLedOn == 100) && (switchStartLedOff == 1) && (switchLedBlinking == 0)){
        timerLedOff = millis();
        switchLedBlinking = 1;
      }
      if((millis() - timerLedOff <= 100) && (switchStartLedOff == 1) && (switchLedBlinking == 1)){
        digitalWrite(PB6, HIGH);
        digitalWrite(PB7, HIGH);
      }
      if(millis() - timerLedOff == 100){
        finishLedBlinking = 1;
      }
      if(switchLedBlinking == 1 && switchStartLedOff == 1 && finishLedBlinking == 1){
        switchLedBlinking = 0;
        switchStartLedOff = 0;
        finishLedBlinking = 0;
      }
    }
    else if(strategyNumber == 4){
      if(switchLedBlinking == 0 && switchStartLedOff == 0){
        timerLedOn = millis();
        digitalWrite(PB6, HIGH);
        digitalWrite(PB7, HIGH);
        digitalWrite(PB8, LOW);
        switchStartLedOff = 1;
      }
      if((millis() - timerLedOn == 100) && (switchStartLedOff == 1) && (switchLedBlinking == 0)){
        timerLedOff = millis();
        switchLedBlinking = 1;
      }
      if((millis() - timerLedOff <= 100) && (switchStartLedOff == 1) && (switchLedBlinking == 1)){
        digitalWrite(PB8, HIGH);
      }
      if(millis() - timerLedOff == 100){
        finishLedBlinking = 1;
      }
      if(switchLedBlinking == 1 && switchStartLedOff == 1 && finishLedBlinking == 1){
        switchLedBlinking = 0;
        switchStartLedOff = 0;
        finishLedBlinking = 0;
      }
    }   
  }
}

void GY25::getData(){
  setImu();
  debounce();
  sprintf(buff,"start,%d,%d,%d,%d,%d\r\n", strategyNumber, killNRun, YAW,PITCH,ROLL);
  Serial2.println(buff);  
}

void GY25::inits(){
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(2000000);
  dataInIMU = "";
  imuCalibration();  
}

void GY25::debounce(){
  tombol = digitalRead(PB0);
////////////////////////////Strategy UP ////////////////
  if(tombol != prevTombol){
      time = millis();
  }
  if (millis() - time > debounceDelay){
    if(tombol != statusTombol){
      if(statusTombol == 1 && maxStrategyState == 0){
        strategyNumber = strategyNumber + 1;
        if(strategyNumber > 4){
          strategyNumber = 0;
        }
        else if(strategyNumber < 0){
          strategyNumber = 4;
        }     
        switchLedBlinking = 0;
        switchStartLedOff = 0;  
        finishLedBlinking = 0;
      }
      else{
        maxStrategyState = 0;
      }
      statusTombol = tombol;
    }
  }
  prevTombol = tombol;
  
///////////////Stategy MAX////////////////
  if( tombol == 1 && maxStrategyState == 0){
    if(countButton > countTreshold){
      strategyNumber = 4;
      countButton = 0;
      maxStrategyState = 1;
    }
    else{
      countButton++;
    }
  }
  else{
    countButton = 0;
  }

  tombol1 = digitalRead(PB1);
////////////////////Kill n Run/////////////////
  if(tombol1 != prevTombol1){
      time1 = millis();
  }
  if (millis() - time1 > debounceDelay){
    if(tombol1 != statusTombol1){
      if(statusTombol1 == 1 && kalibrasiState == 0){
        killNRun =! killNRun;
        statusKill = !killNRun;       
      }
      else{
        kalibrasiState = 0;
      }
      statusTombol1 = tombol1;
    }
  }
  prevTombol1 = tombol1;  
////////////////////Kalibrasi Sensor////////////////
  if( tombol1 == 1 && kalibrasiState == 0){
    if(countButton1 > countTreshold){
      kalibrasi = 1;
      countButton1 = 0;
      kalibrasiState = 1;
      digitalWrite(PB5, LOW);
      digitalWrite(PB9, LOW);
      imuCalibration();
    }
    else{
      countButton1++;
    }
  }
  else{
    countButton1 = 0;
  }
}

void GY25::setImu(){
  if (Serial1.available() > 0) {
    inChar = (char)Serial1.read();
    dataInIMU += inChar;
    if (inChar == '\n') {
      parsing = true;
    }
  }

  if (parsing) {
    parsingData();
    parsing = false;
    dataInIMU = "";
  }
}

void GY25::parsingData(){
  dataYaw[0] = dataInIMU[6];
  dataYaw[1] = dataInIMU[7];
  dataYaw[2] = dataInIMU[8];
  dataYaw[3] = dataInIMU[9];
  dataYaw[4] = dataInIMU[10];
  dataYaw[5] = dataInIMU[11];
  //YAW = atof(dataYaw);
  YAW = atoi(dataYaw);
  if(dataInIMU[5] == '+'){
    YAW = YAW * -1;
  }
  if(dataInIMU[5] == '-'){
    con360 = 180 - YAW;
    YAW360 = 180 + con360;
    if(YAW360 >= 360){
      YAW360 = 0;
    }
  }
  else{
    YAW360 = YAW;
  }

  if(YAW > 40){
    digitalWrite(PB5, HIGH);
    digitalWrite(PB9, LOW);
  }
  else if( YAW < -40) {
    digitalWrite(PB5, LOW);
    digitalWrite(PB9, HIGH);
  }
  else{
    digitalWrite(PB5, HIGH);
    digitalWrite(PB9, HIGH);
  }  

  dataPitch[0] = dataInIMU[14];
  dataPitch[1] = dataInIMU[15];
  dataPitch[2] = dataInIMU[16];
  dataPitch[3] = dataInIMU[17];
  dataPitch[4] = dataInIMU[18];
  dataPitch[5] = dataInIMU[19];
  PITCH = atoi(dataPitch);
  if(dataInIMU[13] == '+'){
    PITCH = PITCH * -1;
  }

  dataRoll[0] = dataInIMU[22];
  dataRoll[1] = dataInIMU[23];
  dataRoll[2] = dataInIMU[24];
  dataRoll[3] = dataInIMU[25];
  dataRoll[4] = dataInIMU[26];
  dataRoll[5] = dataInIMU[27];
  ROLL = atoi(dataRoll);
  if(dataInIMU[21] == '+'){
    ROLL = ROLL * -1;
  }  
}

void GY25::imuCalibration(){
  Serial1.write(0xA5);
  Serial1.write(0x54);
  delay(1000);
  //Kalibrasi Heading
  Serial1.write(0xA5);
  Serial1.write(0x55);
  delay(100);
  //Output ASCII
  Serial1.write(0xA5);
  Serial1.write(0x53);
  delay(1000);
  digitalWrite(PB9, HIGH);
  delay(100);
  digitalWrite(PB5, HIGH);  
  kalibrasi = 0;
}

/* *************************************
 * ****************MAIN****************
 * *************************************/

void setup() {
  // put your setup code here, to run once:
  GY25.inits();
}

void loop() {
  // put your main code here, to run repeatedly:
  GY25.getData();
}
