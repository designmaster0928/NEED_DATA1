#include "driver/uart.h"
#include "stdio.h"
#include "string.h"
#include "BluetoothSerial.h"


// Check if Bluetooth configs are enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Bluetooth Serial object
BluetoothSerial SerialBT;

// Timer: auxiliar variables
unsigned long previousMillis = 0;    // Stores last time temperature was published
const long interval = 100;         // interval at which to publish sensor readings
/////
const uint8_t LEDPIN = 13;


hw_timer_t* timer = NULL;

volatile bool ledstate = 0;
volatile bool flag = 0;



void IRAM_ATTR onTimer() ;
void initialization();


void setup() {
  // put your setup code here, to run once:
  initialization();
}

void loop() {
  // put your main code here, to run repeatedly:

}


void IRAM_ATTR onTimer() {
  flag = 1;
  ledstate = !ledstate;
  digitalWrite(LEDPIN, ledstate);
}

void initialization() {

  pinMode(LEDPIN, OUTPUT);  

  Serial.begin(115200);
  // Bluetooth device name
  SerialBT.begin("ESP32");
  Serial.println("The device started, now you can pair it with bluetooth!");

  timer = timerBegin(0, 80, true); //1us
  timerAttachInterrupt(timer, &onTimer, true); //edge(not evel) triggered
  timerAlarmWrite(timer, 5E5, true); //500ms
  timerAlarmEnable(timer);//enable
}


