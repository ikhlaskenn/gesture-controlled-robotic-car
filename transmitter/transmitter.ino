#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <BluetoothSerial.h>

Adafruit_MPU6050 mpu;
BluetoothSerial SerialBT;

float baseX = 0, baseY = 0;

// ---- tuning values ----
const float DEAD_ZONE = 0.25;   // ignore tiny motions
const float TH_F = 1.6;         // forward threshold
const float TH_B = -1.6;        // backward threshold
const float TH_R = 1.1;         // right threshold
const float TH_L = -1.1;        // left threshold

// for smoothing
float filtDx = 0, filtDy = 0;
const float ALPHA = 0.3;        // 0..1, bigger = faster but noisier

void calibrate() {
  Serial.println("Calibrating...");
  float sumX = 0, sumY = 0;

  for (int i = 0; i < 120; i++) {
    sensors_event_t a, g, t;
    mpu.getEvent(&a, &g, &t);
    sumX += a.acceleration.x;
    sumY += a.acceleration.y;
    delay(10);
  }

  baseX = sumX / 120.0;
  baseY = sumY / 120.0;

  Serial.println("Calibration DONE!");
}

void setup() {
  Serial.begin(115200);
  Serial.println("HAND Controller Booting...");

  // Bluetooth client
  SerialBT.begin("ESP32_TRANSMITTER", true);
  Serial.println("Connecting to ESP32_ROBOT...");
  while (!SerialBT.connect("ESP32_ROBOT")) {
    Serial.println("Failed... retrying in 1 sec");
    delay(1000);
  }
  Serial.println("CONNECTED TO ROBOT!");

  // MPU
  if (!mpu.begin()) {
    Serial.println("MPU6050 ERROR!");
    while (1);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(500);
  calibrate();
}

void loop() {
  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);

  // raw differences
  float dx = a.acceleration.x - baseX;
  float dy = a.acceleration.y - baseY;

  // low-pass filter (smoothing)
  filtDx = ALPHA * dx + (1.0 - ALPHA) * filtDx;
  filtDy = ALPHA * dy + (1.0 - ALPHA) * filtDy;

  // -------------------------
  // 📊 LOG RAW + FILTERED VALUES FOR GRAPH D
  Serial.print(dx); Serial.print(",");
  Serial.print(filtDx); Serial.print(",");
  Serial.print(dy); Serial.print(",");
  Serial.println(filtDy);
  // -------------------------

  // apply dead zone
  if (fabs(filtDx) < DEAD_ZONE) filtDx = 0;
  if (fabs(filtDy) < DEAD_ZONE) filtDy = 0;

  char cmd = 'S';

  // decide command
  if (filtDy > TH_F)        cmd = 'F';
  else if (filtDy < TH_B)   cmd = 'B';
  else if (filtDx > TH_R)   cmd = 'R';
  else if (filtDx < TH_L)   cmd = 'L';
  else                      cmd = 'S';

  Serial.print("dx: "); Serial.print(filtDx, 2);
  Serial.print("  dy: "); Serial.print(filtDy, 2);
  Serial.print("  Cmd: "); Serial.println(cmd);

  SerialBT.write(cmd);
  delay(120);
}
