// INTERACTIVE LIGHT DISPLAY IN RESPONSE TO SOUND
// with optional buzzer tones

// By Andrea Kereliuk for Sheridan College IMM, 2014-2015

// Parts:
  // MAX9814 Electret Microphone Amplifier 
    // https://www.adafruit.com/products/1713
  // 4 LEDs
  // DC Buzzer (SPKBZ-221005)  
// With help from the tutorials from:
  // Bill Earl @ Adafruit
    // https://learn.adafruit.com/adafruit-microphone-amplifier-breakout/measuring-sound-levels
  // Starting Electronics
    // http://startingelectronics.com/beginners/circuits/arduino-buzzer/
//
 
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
 
int soundVal = 0;           // variable to store the value read
int speakerPin = 3;         // pin where buzzer is wired in

int numTones = 10;          
int tones[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};
// mid C C# D D# E F F# G G# A // array of tones to select from
void setup()
{

pinMode(6, OUTPUT);
pinMode(8, OUTPUT);
pinMode(10, OUTPUT);
pinMode(12, OUTPUT);
// initialize pins for LEDs

Serial.begin(9600);          //  setup serial

}

void loop()
{
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      soundVal = analogRead(0);
      if (soundVal < 1024)  // toss out spurious readings
      {
         if (soundVal > signalMax)
         {
            signalMax = soundVal;  // save just the max levels
         }
         else if (soundVal < signalMin)
         {
            signalMin = soundVal;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 3.3) / 1024;  // convert to volts
 
   Serial.println(volts);
  
  
  // light display handler
  // TEST values for indoor testing
  // CAR values for monitoring music level in cars
  // can be adjusted to liking (view values in serial monitor)
  if (volts >= 0.15 && volts < 0.30) { // CAR >= 0.15 && volts < 0.50  // TEST >= 0.15 && volts < 0.30 
    // 2) TWO; dim sound, minimal noise
      tone(speakerPin, tones[3]);  // second frequency
      
      digitalWrite(10, LOW);
      digitalWrite(12, LOW);    // other lights off
      
      digitalWrite(6, HIGH);
      digitalWrite(8, HIGH);    // two lights on, slight warning
      
    } else if (volts >= 0.30 && volts < 0.45) { // CAR >= 0.50 && volts < 1.15  // TEST >= 0.30 && volts < 0.45
    // 3) THREE; bass inundation
      tone(speakerPin, tones[6]);  // second highest frequency
      
      digitalWrite(12, LOW);    // other light off
      
      digitalWrite(6, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(10, HIGH);
      delay(200);
      digitalWrite(10, LOW);
      delay(200);              // only last LED blinking, slightly annoying
      
    } else if (volts >= 0.45) { // CAR >= 1.15  // TEST >= 0.45
    // 4) FOUR; TOO LOUD
      tone(speakerPin, tones[9]);  // highest most annoying frequency
      digitalWrite(6, HIGH);

      digitalWrite(8, LOW);
      digitalWrite(10, LOW);
      digitalWrite(12, LOW);    // blinking reset

      delay(100);
      digitalWrite(8, HIGH);
      delay(100); 
      digitalWrite(8, LOW);
      delay(100);
      digitalWrite(10, HIGH);
      delay(100);              
      digitalWrite(10, LOW); 
      delay(100);             
      digitalWrite(12, HIGH);  
      delay(100);
      digitalWrite(12, LOW);  
      delay(100);                  // 3 non-green lights blink, maximum obnoxious
      
    } else {                       // CAR less than 0.15
    // 1) ONE; minimal noise, basically null
      noTone(speakerPin);
      
      digitalWrite(6, HIGH);    // always on to signify unit is on
      
      digitalWrite(8, LOW);
      digitalWrite(10, LOW);
      digitalWrite(12, LOW);    // other lights off
    }  
}
