//main variables
long prtime = 0;
long time1, t2;
float flow = 0;
int count = 0;
byte cCount = 0;
byte preCount = 0;

//editable variables
float sensitive = 10;

//filter variables
float kg = 0.9;
float Eest = 4.0;
float preEst = 5.0;
float Emea = 3.0;
float est = 340.0;
float preEst = 344.0;
float mea = 343.0;
byte index = 0;
float kv = 0;
float kvr = 0;


void setup(){
  Serial.begin(9600);
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), blink1, RISING);
}

void loop(){
  kv = 6280000.00/t2;
  if (kv>5000){
    // highspeed error occured
    kv = 0;
  }
  if (count == preCount){
    cCount = cCount + 1;
  }
  if (cCount > 10){
    kv = 0;
  }
  preCount = count;
  kvr = kv;
  filter();
  Serial.println(flow);
  delay(30)
}

void blink1(){
  count = count +1;
  cCount = 0;
  if (count>=20){
    time1 = micros();
    t2 = time1-prtime;
    count = 0;
  }
  prtime = time1
}

//Kalman filter
void filter(){
  mea = kvr;
  index = index + 1;
  kg = Eest / (Eest+Emea);                  //Kalman gain
  est = preEst + kg*(mea-preEst);           //estimate
  Eest = ((1-kg)*preEst)+0.0001*sensitive;  //error
  preEst = Eest;
  flow = est
}
