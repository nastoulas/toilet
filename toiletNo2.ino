#include <Servo.h> 

const int pinPIRsensor = 2;             // Ανίχνευση κίνησης
const int pinFan = 3;                   // Διαχείριση εξαερισμού τουαλέτας
const int pinLights = 4;                // Διαχείριση φωτισμού τουαλέτας
const int pinAroma = 5;                 // Διαχείριση αρωματισμού τουαλέτας

Servo srvAroma;                         // Ορισμός αντικειμένου σερβοκινητήρα

int t = 0;
boolean aroma = false;
  
void setup () {
  Serial.begin(9600);              // καθορισμός ταχύτητας σειριακής επικοινωνίας
  
  pinMode(LED_BUILTIN, OUTPUT); 
  digitalWrite(LED_BUILTIN, LOW);  // σβήσιμο εσωτερικού led 
  
  srvAroma.attach(pinAroma);       // ενεργοποίηση σερβοκινητήρα

  pinMode (pinPIRsensor, INPUT); 
  pinMode (pinFan, OUTPUT); 
  pinMode (pinLights, OUTPUT); 
  pinMode (pinAroma, OUTPUT);

}

void loop () {
  if (digitalRead(pinPIRsensor) == HIGH) {        // έλεγχος για την είσοδο ατόμου στην τουαλέτα
      digitalWrite(pinLights, HIGH);
      digitalWrite(pinFan, HIGH);
      aroma = true;
      }  
  else { 
      delay(3000);
      digitalWrite(pinLights, LOW); 
      digitalWrite(pinFan, LOW);
      aroma = false;
      t = 0;
      } 
  delay(2000);

    if (aroma) {                // έλεγχος για αρωματισμός της τουαλέτας κάθε 120 δευτερόλεπτα
      t += 2;
      if (t == 12) {
      srvAroma.write(40); 
      delay(3000); 
      srvAroma.write(120);
      delay(3000);
      t = 0;
    }
  }
  Serial.println(t);
}

