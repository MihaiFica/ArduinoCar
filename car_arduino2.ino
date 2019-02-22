#include <SoftwareSerial.h>
 SoftwareSerial BTSerial(2, 4);
 #include <Servo.h>
 const int servoMotor = 5;
 const int motorA1 = 8;  
 const int motorA2 = 9; 
 const int motorB1 = 10; 
 const int motorB2 = 11;
 const int trigPin = 3;
 const int echoPin = 6;
 long durata;
 float distanta;
 char stare;
 Servo myservo; 


void setup()  
{
    myservo.attach(servoMotor);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    BTSerial.begin(38400);
    Serial.begin(9600);   
}


void loop() 
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2); 
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    durata = pulseIn(echoPin, HIGH);
    distanta = durata * 0.034 / 2;
    Serial.println(distanta);
    if(distanta < 15)                                                   //algoritm prin care se evita ciocnirea masinii cu un obstacol
        {                                                               //daca masina ajunge la 15 centimetrii de un obstocol motoarele isi schimba sensul de rotatie ,iar masina se departeaza de obstacol
            while(distanta < 40)                                           //in acest timp controlul nu este la utilizator  
                { 
                    digitalWrite(motorA1, HIGH);
                    digitalWrite(motorA2, LOW);
                    digitalWrite(motorB1, LOW);
                    digitalWrite(motorB2, HIGH);
                    digitalWrite(trigPin, HIGH);
                    delayMicroseconds(10);
                    digitalWrite(trigPin, LOW);
                    durata = pulseIn(echoPin, HIGH);
                    distanta = durata * 0.034 / 2;
                    Serial.println(distanta);                         
                }
             stare = 'O';
         }
    if(BTSerial.available() > 0)
         {     
             stare = BTSerial.read(); 
             Serial.println(stare);  
         }
    if(stare == 'A' )                                                    //mers inainte
         {
             digitalWrite(motorA1, LOW);
             digitalWrite(motorA2, HIGH);
             digitalWrite(motorB1, HIGH);
             digitalWrite(motorB2, LOW);
         }
    if(stare == 'O')                                                     //echilibru motoare
         {
             digitalWrite(motorA1, LOW);
             digitalWrite(motorA2, LOW);
             digitalWrite(motorB1, LOW);
             digitalWrite(motorB2, LOW);
         }
    if(stare == 'D')                                                     //mers inapoi
         {
             digitalWrite(motorA1, HIGH);
             digitalWrite(motorA2, LOW);
             digitalWrite(motorB1, LOW);
             digitalWrite(motorB2, HIGH);
         }
    if(stare == 'B')
         {
             myservo.write(90);                                        //viraj dreapta
         }
    if(stare == 'C')
        {
             myservo.write(30);                                        //viraj stanga
        }
    if(stare == 'H')
        {
             myservo.write(60);                                        // echilbru servo
        }
}
