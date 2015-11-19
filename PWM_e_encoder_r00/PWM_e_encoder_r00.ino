#include <avr/io.h> 
// Variables used on this code
unsigned long timet;
unsigned long previousTime;
boolean enterFunction= true;
boolean led13 = false;
//-----------------------
int pwmSetado = 0;
long pwmLido = 0;
int pwmPin = 11;
int   tensaoTransistorInteger; 
int PinoLeituraAnalogica = A2;
int tensaoMotorInteger = 0;
long TensaoMotorVolts = 0;

void setup() {
    DDRB |= (1<<PB5); // Port B5 (pin 13 Arduino) as output
    Serial.begin(9600);
    Serial.println("digite um valor entre 0 e 100% para o PWM: ");
   }

void loop() {
  timet = micros();
  if (enterFunction == true){
    previousTime= timet;
    //Serial.println(previousTime); // for debugging

    // Start your code below 
    //-----------------------
    
    PORTB ^=(1<<PB5); //liga pino 13 (LED) 
    pwmSetado = 127; // Valor do PWM aplicado ao motor. 0=SemTensao, 127=MetadeDaTensao, 255=TensaoMaxima
    analogWrite(pwmPin, pwmSetado); // Escreve o valor do PWM no pino de gate do transistor drive do motor
    tensaoTransistorInteger = analogRead(PinoLeituraAnalogica); // lê a tensão sobre o transistor drive do motor (em números inteiros)
    tensaoMotorInteger = 1023 - tensaoTransistorInteger; // Obtem a tensão sobre o motor (em números inteiros)
    TensaoMotorVolts = tensaoMotorInteger * 0.0048875; // Converte a tensão do motor de inteiros para volts >> multiplica-se o número inteiro vindo do AD por 5/1023=4.885mV (5V/1023 valores possíveis)
 
      
    
    
     



    //-----------------------
    // End of your code
  }
  
  // The DELAY time is adjusted in the constant below >> 
  if (timet - previousTime < 49990){ // 1 million microsencods= 1 second delay
    /* I have actually used 0.999990 seconds, in a trial to compensate the time that
       this IF function takes to be executed. this is really a point that
       need improvement in my code */   
    enterFunction= false;
  } 
  else {
    enterFunction= true;
  }
}
