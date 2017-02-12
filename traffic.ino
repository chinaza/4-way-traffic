//PIR motion sensors
int pir[4]; //Declare PIR array

//Traffic Lights
int tlight[4][3]; //Declare Traffic light array

//Control Variables
bool pirCheck = false;


void setup() {
  //Initialize serial for debugging
  Serial.begin(9600);

  //Specify pins for PIR
  pir[0] = 1; //PIR for junction 1
  pir[1] = 2; //PIR for junction 2
  pir[2] = 3; //PIR for junction 3
  pir[3] = 4; //PIR for junction 4

  //Specify pins for Traffic Lights
  //Junction 1
  tlight[0][0] = 1; //Red Light
  tlight[0][1] = 2; //Amber Light
  tlight[0][2] = 3; //Green light
  //Junction 2
  tlight[1][0] = 1; //Red Light
  tlight[1][1] = 2; //Amber Light
  tlight[1][2] = 3; //Green light
  //Junction 3
  tlight[2][0] = 1; //Red Light
  tlight[2][1] = 2; //Amber Light
  tlight[2][2] = 3; //Green light
  //Junction 4
  tlight[3][0] = 1; //Red Light
  tlight[3][1] = 2; //Amber Light
  tlight[3][2] = 3; //Green light

  
  // Initialize INPUT Pins (PIR sensors) and Callibrate the sensor
  for (int i=0; i<4; i++){
    pinMode(pir[i], INPUT);
    digitalWrite(pir[i], LOW);
  }
  
  // Initialize OUTPUT Pins (Traffic lights)
  for (int i=0; i<4; i++){
    for (int j=0; j<3; j++){
      pinMode(tlight[i][j], OUTPUT);
    }    
  }

  //Turn all junction traffic lights Red while sensor callibrates
  allRed();
  
  //Give the sensor some time to callibrate
  for (int i=0; i<20; i++){
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Callibration complete...");
  Serial.println("SENSOR ACTIVE...");
  delay(50);
  
  bool pirCheck = true; //Begin the process
}

void loop() {
  // put your main code here, to run repeatedly:
  if (pirCheck == true){
    if (digitalRead(pir[0]) == HIGH){      
      if (checkStat(0) == true){ //If no car present at other junctions
        initiateOverride(0); //For junction 1
      } else {
        normalOP(); //Normal Operation
      }
    } else if (digitalRead(pir[1]) == HIGH){
      if (checkStat(1) == true){ //If no car present at other junctions
        initiateOverride(1); //For junction 2
      } else {
        normalOP(); //Normal Operation
      }
    } else if (digitalRead(pir[2]) == HIGH){
      if (checkStat(2) == true){ //If no car present at other junctions
        initiateOverride(2); //For junction 3
      } else {
        normalOP(); //Normal Operation
      }
    } else if (digitalRead(pir[3]) == HIGH){
      if (checkStat(3) == true){ //If no car present at other junctions
        initiateOverride(3); //For junction 4
      } else {
        normalOP(); //Normal Operation
      }
    }
  }
}

bool checkStat(int junc){
  bool stat = true; //Inidicate other junctions have no cars
  for (int i=0; i<4; i++){
    if (i != junc){
      if (digitalRead(pir[i]) == HIGH){ //If motion detected
        stat = false; //Inidicate other junctions have cars
        break;
      }
    }
  }
  return stat;
}

void initiateOverride(int junc){
  pirCheck = false;
  allRed();
  delay(3000);
  changeStat(junc, 'g');
  delay(20000);
  changeStat(junc, 'a');
  delay(3000);
  changeStat(junc, 'r');
  pirCheck = true;
}

void normalOP(){
  pirCheck = false;
  allRed();
  delay(3000);
  for (int i=0; i<4; i++){ //Loop through the junctions
    changeStat(i, 'g');
    delay(30000);
    changeStat(i, 'a');
    delay(5000);
    changeStat(i, 'r');
  }
  pirCheck = true;
}

void allRed(){
  for (int i=0; i<4; i++){ //Loop through the junctions
    for (int j=0; j<3; j++){ //Loop through the lights
      if (j == 0){ //If red light
        digitalWrite(tlight[i][j], HIGH); //Turn ON
      } else {
        digitalWrite(tlight[i][j], LOW); //Turn OFF
      }
    }    
  }
}

void changeStat(int junc, char stat){
  if (junc == 'r'){ //Turn red
    for (int j=0; j<3; j++){ //Loop through the lights
      if (j == 0){ //If red light
        digitalWrite(tlight[junc][j], HIGH); //Turn ON
      } else {
        digitalWrite(tlight[junc][j], LOW); //Turn OFF
      }
    }
  } else if (junc == 'a'){ //Turn amber
    for (int j=0; j<3; j++){ //Loop through the lights
      if (j == 1){ //If amber light
        digitalWrite(tlight[junc][j], HIGH); //Turn ON
      } else {
        digitalWrite(tlight[junc][j], LOW); //Turn OFF
      }
    }
  } else if (junc == 'g'){ //Turn green
    for (int j=0; j<3; j++){ //Loop through the lights
      if (j == 2){ //If green light
        digitalWrite(tlight[junc][j], HIGH); //Turn ON
      } else {
        digitalWrite(tlight[junc][j], LOW); //Turn OFF
      }
    }
  }
}

