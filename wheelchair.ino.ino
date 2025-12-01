#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
#define motor1Forward 5
#define motor1Backward 6
#define motor2Forward 9
#define motor2Backward 10

char command;

void setup() {
    Serial.begin(9600);
    pinMode(motor1Forward, OUTPUT);
    pinMode(motor1Backward, OUTPUT);
    pinMode(motor2Forward, OUTPUT);
    pinMode(motor2Backward, OUTPUT);

    Wire.begin();
    mpu.initialize();
    
    if (!mpu.testConnection()) {
        Serial.println("MPU6050 connection failed!");
    } else {
        Serial.println("MPU6050 connected!");
    }
}

void loop() {
    if (Serial.available()) {
        command = Serial.read();
        Serial.println(command);
        moveWheelchair(command);
    }

    detectFall(); // Check if patient has fallen
}

void moveWheelchair(char cmd) {
    switch (cmd) {
        case 'F':
            digitalWrite(motor1Forward, HIGH);
            digitalWrite(motor1Backward, LOW);
            digitalWrite(motor2Forward, HIGH);
            digitalWrite(motor2Backward, LOW);
            break;

        case 'B': 
            digitalWrite(motor1Forward, LOW);
            digitalWrite(motor1Backward, HIGH);
            digitalWrite(motor2Forward, LOW);
            digitalWrite(motor2Backward, HIGH);
            break;

        case 'L':
            digitalWrite(motor1Forward, LOW);
            digitalWrite(motor1Backward, HIGH);
            digitalWrite(motor2Forward, HIGH);
            digitalWrite(motor2Backward, LOW);
            break;

        case 'R':
            digitalWrite(motor1Forward, HIGH);
            digitalWrite(motor1Backward, LOW);
            digitalWrite(motor2Forward, LOW);
            digitalWrite(motor2Backward, HIGH);
            break;

        case 'S':
            digitalWrite(motor1Forward, LOW);
            digitalWrite(motor1Backward, LOW);
            digitalWrite(motor2Forward, LOW);
            digitalWrite(motor2Backward, LOW);
            break;
    }
}

void detectFall() {
    int16_t ax, ay, az;
    mpu.getAcceleration(&ax, &ay, &az);
    
    float acceleration = sqrt(ax * ax + ay * ay + az * az);

    if (acceleration < 5000) { 
        Serial.println("FALL DETECTED! Alerting!");
    }
}
