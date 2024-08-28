#define ECHO_PIN 4
#define TRIG_PIN 2
#define REDLED_PIN 33
#define GREENLED_PIN 32
#define YELLOWLED_PIN 26

const int DISTANCE_THRESHOLD_SHORT = 10;
const int DISTANCE_THRESHOLD_MEDIUM = 20;
const int DISTANCE_THRESHOLD_LONG = 30;

class DistanceSensor {
private:
  int trigPin;
  int echoPin;
  int redLedPin;
  int greenLedPin;
  int yellowLedPin;
  long duration;
  long distance;

public:
  // Constructor para inicializar los pines
  DistanceSensor(int trig, int echo, int redLed, int greenLed, int yellowLed) {
    trigPin = trig;
    echoPin = echo;
    redLedPin = redLed;
    greenLedPin = greenLed;
    yellowLedPin = yellowLed;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(redLedPin, OUTPUT);
    pinMode(greenLedPin, OUTPUT);
    pinMode(yellowLedPin, OUTPUT);
  }

  // Función para medir y mostrar la distancia
  void measureAndDisplayDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(4);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    duration = duration / 2;
    distance = duration / 29.2;
    Serial.print("Distance in Cm: ");
    Serial.println(distance);
  }

  // Función para encender un LED específico
  void turnOnLed(int pin) {
    digitalWrite(pin, HIGH);
  }

  // Función para apagar un LED específico
  void turnOffLed(int pin) {
    digitalWrite(pin, LOW);
  }

  // Función para apagar todos los LEDs
  void turnOffAllLeds() {
    turnOffLed(redLedPin);
    turnOffLed(greenLedPin);
    turnOffLed(yellowLedPin);
  }

  // Función para manejar los LEDs según la distancia medida
  void handleLeds() {
    if (distance >= 0 && distance <= 400) {
      if (distance < DISTANCE_THRESHOLD_SHORT) {
        turnOnLed(redLedPin);
        turnOnLed(greenLedPin);
        turnOnLed(yellowLedPin);
      } else if (distance < DISTANCE_THRESHOLD_MEDIUM) {
        turnOnLed(redLedPin);
        turnOnLed(greenLedPin);
      } else if (distance < DISTANCE_THRESHOLD_LONG) {
        turnOnLed(redLedPin);
      } else {
        turnOffAllLeds();
      }
    } else {
      Serial.println("Invalid Distance Reading.");
    }
  }
  
  // Getter para la distancia medida
  long getDistance() {
    return distance;
  }
};

// Instanciamos el objeto de la clase DistanceSensor
DistanceSensor sensor(TRIG_PIN, ECHO_PIN, REDLED_PIN, GREENLED_PIN, YELLOWLED_PIN);

void setup() {
  Serial.begin(115200);
}

void loop() {
  sensor.measureAndDisplayDistance();
  sensor.handleLeds();
  delay(500);
  sensor.turnOffAllLeds();
  delay(200);
}