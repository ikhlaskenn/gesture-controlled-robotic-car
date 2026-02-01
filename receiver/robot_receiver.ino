#include <BluetoothSerial.h>
BluetoothSerial SerialBT;

#define IN1 25
#define IN2 26
#define IN3 27
#define IN4 33

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_ROBOT");  // Bluetooth device name

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();
  Serial.println("Waiting for command...");
}

void loop() {
  if (SerialBT.available()) {
    char cmd = SerialBT.read();

    if (cmd == '\n' || cmd == '\r') return;

    Serial.print("Received: ");
    Serial.println(cmd);

    if (cmd == 'F') {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    else if (cmd == 'B') {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }
    else if (cmd == 'L') {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    else if (cmd == 'R') {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }
    else {
      stopMotors();  // Stop on unknown command
    }
  }
}

