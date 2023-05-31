#define SENSOR_IR_DERECHO 11
#define SENSOR_IR_IZQ 12
#define VL_MOTOR 180

// MOTOR DERECHO
int activarMotorDerecho = 6;
int motorDerechoPin1 = 7;
int motorDerechoPin2 = 8;

// MOTOR IZQUIERDO
int activarMotorIzq = 5;
int motorIzqPin1 = 9;
int motorIzqPin2 = 10;

void setup()
{
    // The problem with TT gear motors is that, at very low pwm value it does not even rotate.
    // If we increase the PWM value then it rotates faster and our robot is not controlled in that speed and goes out of line.
    // For that we need to increase the frequency of analogWrite.
    // Below line is important to change the frequency of PWM signal on pin D5 and D6
    // Because of this, motor runs in controlled manner (lower speed) at high PWM value.
    // This sets frequecny as 7812.5 hz.
    TCCR0B = TCCR0B & B11111000 | B00000010;

    // put your setup code here, to run once:
    pinMode(activarMotorDerecho, OUTPUT);
    pinMode(motorDerechoPin1, OUTPUT);
    pinMode(motorDerechoPin2, OUTPUT);

    pinMode(activarMotorIzq, OUTPUT);
    pinMode(motorIzqPin1, OUTPUT);
    pinMode(motorIzqPin2, OUTPUT);

    pinMode(SENSOR_IR_DERECHO, INPUT);
    pinMode(SENSOR_IR_IZQ, INPUT);
    rotateMotor(0, 0);
}

void loop()
{

    int IRSensorDerValue = digitalRead(SENSOR_IR_DERECHO);
    int IRSensorIzqValue = digitalRead(SENSOR_IR_IZQ);

    // Si no detecta ninguno de los sensores lineas negras seguira recto
    if (IRSensorDerValue == LOW && IRSensorIzqValue == LOW)
    {
        rotateMotor(VL_MOTOR, VL_MOTOR);
    }
    // Si solo el sensor derecho detecta una linea negra, entonces girara a la derecha
    else if (IRSensorDerValue == HIGH && IRSensorIzqValue == LOW)
    {
        rotateMotor(-VL_MOTOR, VL_MOTOR);
    }
    // Si solo el sensor izquierdo detecta una linea negra, entonces girara a la izquierda
    else if (IRSensorDerValue == LOW && IRSensorIzqValue == HIGH)
    {
        rotateMotor(VL_MOTOR, -VL_MOTOR);
    }
    // Si ambos sensores detectan una linea negra se detendra
    else
    {
        rotateMotor(0, 0);
    }
}

void rotateMotor(int VelMotorDerecho, int VelMotorIzq)
{

    if (VelMotorDerecho < 0)
    {
        digitalWrite(motorDerechoPin1, LOW);
        digitalWrite(motorDerechoPin2, HIGH);
    }
    else if (VelMotorDerecho > 0)
    {
        digitalWrite(motorDerechoPin1, HIGH);
        digitalWrite(motorDerechoPin2, LOW);
    }
    else
    {
        digitalWrite(motorDerechoPin1, LOW);
        digitalWrite(motorDerechoPin2, LOW);
    }

    if (VelMotorIzq < 0)
    {
        digitalWrite(motorIzqPin1, LOW);
        digitalWrite(motorIzqPin2, HIGH);
    }
    else if (VelMotorIzq > 0)
    {
        digitalWrite(motorIzqPin1, HIGH);
        digitalWrite(motorIzqPin2, LOW);
    }
    else
    {
        digitalWrite(motorIzqPin1, LOW);
        digitalWrite(motorIzqPin2, LOW);
    }
    analogWrite(activarMotorDerecho, abs(VelMotorDerecho));
    analogWrite(activarMotorIzq, abs(VelMotorIzq));
}
