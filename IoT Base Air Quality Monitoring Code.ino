#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <DHT.h>
#define DHTPIN 7 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

SoftwareSerial mySerial(5,6);
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

int CO_SensorPin =   A0;
int CO2_SensorPin =  A1;
int SO2_SensorPin =  A2;
int NO_SensorPin =   A3;
int O2_SensorPin =   A4;
int Rain_SensorPin = A5;
int PM2_5_SensorPin = A6;
int PM10_SensorPin = A7;
int KY038_SensorPin = A8;
int i=0;
int j=0;

char temperature[] = "Temp = 00.0 C  ";
char humidity[]    = "RH   = 00.0 %  ";

void setup() {
          lcd.begin(32, 2);
          dht.begin();
          mySerial.begin(9600);
          Serial.begin(9600);
          pinMode(CO_SensorPin , INPUT);
          pinMode(CO2_SensorPin , INPUT);
          pinMode(SO2_SensorPin , INPUT);
          pinMode(O2_SensorPin, INPUT);
          pinMode(Rain_SensorPin, INPUT);
          pinMode(PM2_5_SensorPin, INPUT);
          pinMode(PM10_SensorPin, INPUT);
          pinMode(KY038_SensorPin, INPUT);
}

void loop() {
          lcd.print("Air Quality Monitoring System");
          delay(1000); 
          lcd.clear();

          int CO_SensorValue = analogRead(CO_SensorPin); 
          float CO_SensorVolts = analogRead(CO_SensorPin)*0.0048828125;   
          
          int CO2_SensorValue = analogRead(CO2_SensorPin);   
          float CO2_SensorVolts = analogRead(CO2_SensorPin)*0.0048828125;

          int SO2_SensorValue = analogRead(SO2_SensorPin);   
          float SO2_SensorVolts = analogRead(SO2_SensorPin)*0.0048828125;
          
          int NO_SensorValue = analogRead(NO_SensorPin);   
          float NO_SensorVolts = analogRead(NO_SensorPin)*0.0048828125;

          int O2_SensorValue = analogRead(O2_SensorPin);   
          float O2_SensorVolts = analogRead(O2_SensorPin)*0.0048828125;

          int Rain_SensorValue = analogRead(Rain_SensorPin);   
          float Rain_SensorVolts = analogRead(Rain_SensorPin)*0.0048828125;

          int PM2_5_SensorValue = analogRead(PM2_5_SensorPin)/2;  
          float PM2_5_SensorVolts = analogRead(PM2_5_SensorPin)*0.0048828125;
          
          int PM10_SensorValue = analogRead(PM10_SensorPin)/2;   
          float PM10_SensorVolts = analogRead(PM10_SensorPin)*0.0048828125;
          
          int KY038SensorValue = analogRead(KY038_SensorPin)/8.525; 
          float KY038_SensorVolts = analogRead(KY038_SensorPin)*0.0048828125; 
                   
           byte RH = dht.readHumidity();
           byte Temp = dht.readTemperature();
            
           if (isnan(RH) || isnan(Temp)) {
              lcd.clear();
              lcd.setCursor(5, 0);
              lcd.print("Error");
              return;
           }
            temperature[7]     = Temp / 10 + 48;
            temperature[8]     = Temp % 10 + 48;
            temperature[11]    = 223;
            humidity[7]        = RH / 10 + 48;
            humidity[8]        = RH % 10 + 48;
 
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(temperature);
            Serial.println(" ");
            Serial.println("**////////////////////////////////** ");
            Serial.println(" ");
            Serial.print("Temperature       : ");
            Serial.print(temperature);
            
            lcd.setCursor(0, 1);
            lcd.print(humidity);
            Serial.println(" ");
            Serial.print("Humidity          : ");
            Serial.print(humidity);
           
            delay(1000);
            lcd.clear();
            
//////////////////Amount of CO in the air///////////////////

            lcd.setCursor(0, 0);
            lcd.print("Amount of CO: ");
            lcd.setCursor(17, 0);  
            lcd.print(CO_SensorValue);     
            lcd.print("PPM");

            Serial.println(" ");
            Serial.print("Amount of CO      : ");
            Serial.print(CO_SensorValue);
            Serial.print(" PPM");

            //delay(2000);


//////////////////Amount of CO2 in the air///////////////////

            lcd.setCursor(0, 1);
            lcd.print("Amount of CO2: ");
            lcd.setCursor(18, 1);  
            lcd.print(CO2_SensorValue);     
            lcd.print("PPM");

            Serial.println(" ");
            Serial.print("Amount of CO2     : ");
            Serial.print(CO2_SensorValue);
            Serial.print(" PPM");

            delay(2000);
            lcd.clear();

//////////////////Amount of SO2 in the air///////////////////

            lcd.setCursor(0, 0);
            lcd.print("Amount of SO2: ");
            lcd.setCursor(18,0);  
            lcd.print(SO2_SensorValue);     
            lcd.print("PPM");

            Serial.println(" ");
            Serial.print("Amount of SO2     : ");
            Serial.print(SO2_SensorValue);
            Serial.print(" PPM");

            //delay(2000);


//////////////////Amount of NO in the air///////////////////

            lcd.setCursor(0, 1);
            lcd.print("Amount of NO: ");
            lcd.setCursor(17, 1);  
            lcd.print(NO_SensorValue);     
            lcd.print("PPM");

            Serial.println(" ");
            Serial.print("Amount of NO      : ");
            Serial.print(NO_SensorValue);
            Serial.print(" PPM");

            delay(2000);
            lcd.clear();

//////////////////Amount of O2 in the air///////////////////

            lcd.setCursor(0, 0);
            lcd.print("Amount of O2: ");
            lcd.setCursor(17, 0);  
            lcd.print(O2_SensorValue);     
            lcd.print("PPM");
            
            Serial.println(" ");
            Serial.print("Amount of O2      : ");
            Serial.print(O2_SensorValue);
            Serial.print(" PPM");

            //delay(2000);

            
//////////////////Air Qulity Index (AQI)///////////////////

            float AQI = (CO_SensorValue + CO2_SensorValue + SO2_SensorValue + NO_SensorValue + O2_SensorValue)/5;
            lcd.setCursor(0, 0);
            lcd.print("Air Qulity Index (AQI): ");
            lcd.setCursor(17, 0);  
            lcd.print(AQI);     
            
            Serial.println(" ");
            Serial.print("Air Qulity Index (AQI): ");
            Serial.print(AQI);



//////////////////Amount of PM2.2 in the air///////////////////

            lcd.setCursor(0, 1);
            lcd.print("Amount of PM2.5: ");
            lcd.setCursor(19, 1);  
            lcd.print(PM2_5_SensorValue);     
            lcd.print("ug/m^3");
            
            Serial.println(" ");
            Serial.print("Amount of PM2.5   : ");
            Serial.print(PM2_5_SensorValue);
            Serial.print(" ug/m^3");

            delay(1000);
            lcd.clear();

//////////////////Amount of PM10 in the air///////////////////

            lcd.setCursor(0, 0);
            lcd.print("Amount of PM10: ");
            lcd.setCursor(19, 0);  
            lcd.print(PM10_SensorValue);     
            lcd.print("ug/m^3");
            
            Serial.println(" ");
            Serial.print("Amount of PM10    : ");
            Serial.print(PM10_SensorValue);
            Serial.print(" ug/m^3");

            //delay(2000);



//////////////////Amount of KY038 Sensor in the air///////////////////

            lcd.setCursor(0, 1);
            lcd.print("Noise Level: ");
            lcd.setCursor(12, 1);  
            lcd.print(KY038SensorValue);     
            lcd.print(" dB");
            
            Serial.println(" ");
            Serial.print("Noise Level       : ");
            Serial.print(KY038SensorValue);
            Serial.print(" dB");

            delay(2000);
            lcd.clear();
            
//////////////////Amount of Rain in the air///////////////////

            lcd.print("Posibility of rain: ");
            lcd.setCursor(20,0);  
            lcd.print(Rain_SensorValue);     
            lcd.print("mm");

            Serial.println(" ");
            Serial.print("Posibility of rain: ");
            Serial.print(Rain_SensorValue);
            Serial.print(" mm");

            delay(1000);
            lcd.clear();


            
//////////////////////////////////Description\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

              if(CO_SensorValue >= 350){
                lcd.setCursor(0,0);
                lcd.print("Amount of CO is very high");
                Serial.println(" ");
                Serial.println(" ");
                Serial.println("//////////////////////////////// ");
                Serial.println(" ");
                Serial.print("Amount of CO is very high");  
              }
              else{
                //lcd.setCursor(0,1);
                //lcd.print("Amount of CO stable");
                Serial.println(" ");
                Serial.println(" ");
                Serial.print("Amount of CO is stable");
                i++;             }
              //delay(1000);
              //lcd.clear();
              
////////////////////////////////////////////////////////////////////////

                if(CO2_SensorValue >= 500){
                lcd.setCursor(0,1);
                lcd.print("Amount of CO2 is very high");
                Serial.println(" ");
                Serial.println(" ");
                Serial.print("Amount of CO2 is very high");  
              }
              else{
                //lcd.setCursor(0,1);
                //lcd.print("Amount of CO2 is stable");
                Serial.println(" ");
                Serial.println(" ");
                Serial.print("Amount of CO2 is stable");
                i++; 
              }
            delay(2000);
            lcd.clear();
            
///////////////////////////////////////////////////////////////////////////////

                if(SO2_SensorValue >= 300){
                lcd.setCursor(0,0);
                lcd.print("Amount of SO2 is very high");
                Serial.println(" ");
                Serial.println(" ");
                Serial.print("Amount of SO2 is very high");
                j++;  
              }
              else{
                //lcd.setCursor(0,1);
                //lcd.print("Amount of SO2 is stable");
                Serial.println(" ");
                Serial.println(" ");
                Serial.print("Amount of SO2 is stable");
                i++;  
              }
            //delay(2000);
            //lcd.clear();
            
////////////////////////////////////////////////////////////////////////////

             if(NO_SensorValue >= 250){
                lcd.setCursor(0,1);
                lcd.print("Amount of NO is very high");
                Serial.print("Amount of NO is very high");  
              }
              else{
                //lcd.setCursor(0,1);
               // lcd.print("Amount of NO is stable");
                Serial.println(" ");
                Serial.println(" ");
                Serial.print("Amount of NO is stable");
                i++;  
              }
            delay(2000);
            lcd.clear();
            
////////////////////////////////////////////////////////////////////

              if(O2_SensorValue >= 500){
                //lcd.setCursor(0,1);
                //lcd.print("Amount of O2 is very Good");
                Serial.println(" ");
                Serial.println(" ");
                Serial.print("Amount of O2 is very Good");
                i++;  
              }
              else{
                lcd.setCursor(0,1);
                lcd.print("Amount of O2 is Low");
                Serial.println(" ");
                Serial.println(" ");
                Serial.print("Amount of O2 is Low");  
              }
            //delay(2000);
            //lcd.clear();
            
/////////////////////////////// ////////////////////////////////////////////////////////

                if(PM2_5_SensorValue <= 35){
                lcd.setCursor(0,1);
                lcd.print("Amount of PM2.5 is Standard");
                Serial.println(" ");
                Serial.println(" ");
                Serial.print("Amount of PM2.5 is Standard");
                i++;
                }
                
                else if(30<PM2_5_SensorValue <= 80){
                lcd.setCursor(0,1);
                lcd.print("PM2.5 level Unhealthy for sensative Group");
                Serial.println(" ");
                Serial.println(" ");
                Serial.print("PM2.5 level Unhealthy for sensative Group");  
                }

                else if(81<PM2_5_SensorValue <= 250){
                lcd.setCursor(0,1);
                lcd.print("PM2.5 level Very Unhealthy for sensative Group");
                Serial.println(" ");
                Serial.println(" ");
                Serial.print("PM2.5 level Very Unhealthy for sensative Group");  
                }
              
               else{
               lcd.setCursor(0,1);
               lcd.print("PM2.5 level Hazardous");
               Serial.println(" ");
               Serial.println(" ");
               Serial.print("PM2.5 level Hazardous");  
              }
            delay(2000);
            lcd.clear();
            
///////////////////////////////////////////////////////////////////////////////

                if(PM10_SensorValue <= 50){
                lcd.setCursor(0,0);
                lcd.print("Amount of PM10 is Standard");
                Serial.println(" ");
                Serial.println(" ");
                Serial.print("Amount of PM10 is Standard");
                i++;
                }
                
                else if(50<PM10_SensorValue <= 110){
                lcd.setCursor(0,0);
                lcd.print("PM10 level Unhealthy for sensative Group");
                Serial.println(" ");
                Serial.println(" ");
                Serial.print("PM10 level Unhealthy for sensative Group");  
                }

                else if(111<PM10_SensorValue <= 330){
                lcd.setCursor(0,0);
                lcd.print("PM10 level Very Unhealthy for sensative Group");
                Serial.println(" ");
                Serial.println(" ");
                Serial.print("PM10 level Very Unhealthy for sensative Group");  
                }
              
               else{
               lcd.setCursor(0,0);
               lcd.print("PM10 level Hazardous");
               Serial.println(" ");
               Serial.println(" ");
               Serial.print("PM10 level Hazardous");  
              }
            //delay(2000);
           // lcd.clear();
            
//////////////////////////////////////////////////////////////////////////////

                if(KY038SensorValue <= 40){
                lcd.setCursor(0,1);
                lcd.print("Faint Level Noise");
                Serial.println(" ");
                Serial.println(" ");
                Serial.print("Paint Level Noise");
                i++;
                }
                
                else if(41<KY038SensorValue <= 65){
                lcd.setCursor(0,1);
                lcd.print("Moderate Level Noise");
                Serial.println(" ");
                Serial.println(" ");
                Serial.print("Moderate Level Noise");
                i++;  
                }

                else if(66<KY038SensorValue <= 80){
                lcd.setCursor(0,1);
                lcd.print(" Loud");
                Serial.println(" ");
                Serial.println(" ");
                Serial.print("Loud");  
                }
                
                else if(81<KY038SensorValue <= 100){
                lcd.setCursor(0,1);
                lcd.print(" Very Loud");
                Serial.println(" ");
                Serial.println(" ");
                Serial.print("Very Loud");  
                }
                
               else{
               lcd.setCursor(0,1);
               lcd.print("Hazardous");
               Serial.println(" ");
               Serial.println(" ");
               Serial.print("Hazardous");  
              }
            delay(2000);
            lcd.clear();
            
//////////////////////////////////////////////////////////////////
              
              if(Rain_SensorValue >= 400){
                    if(j==1){
                    lcd.setCursor(0,0);
                    lcd.print("High probability of Acid rain");
                    Serial.println(" ");
                    Serial.println(" ");
                    Serial.print("High probability of Acid rain");
                    }
                    else{
                    lcd.setCursor(0,0);
                    lcd.print("High probability of rain");
                    Serial.println(" ");
                    Serial.println(" ");
                    Serial.print("High probability of rain");
                    }  
                }
              else{
                //lcd.setCursor(0,1);
                //lcd.print("Less probability of rain");
                Serial.println(" ");
                Serial.println(" ");
                Serial.print("Less probability of rain");  
              }
            delay(1000);
            lcd.clear();
            
//////////////////////////////////////////////////////////////////

            if(i==8){
              lcd.print("This Area vere Much Suitable For Educational Institute");
              Serial.println(" ");
              Serial.print("****This Area vere Much Suitable For Educational Institute****");
            }
            else{
              lcd.print("This Area not Suitable For Educational Institute");
              Serial.println(" ");
              Serial.print("****This Area not Suitable For Educational Institute****");
            }
}
