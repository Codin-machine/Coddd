// Пины для драйвера L298n mini
const int IN1 = 5; 
const int IN2 = 6;

// Пины для датчика HC-SR04
const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  Serial.begin(9600); // Для мониторинга расстояния в консоли
}

long getDistance() {
  // Очищаем триггер
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Посылаем импульс 10 мкс
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Считаем время отклика в микросекундах
  long duration = pulseIn(ECHO_PIN, HIGH);
  
  // Расчет расстояния в см (скорость звука 340 м/с)
  long distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  long dist = getDistance();
  
  // Выводим расстояние в монитор порта для проверки
  Serial.print("Distance: ");
  Serial.println(dist);

  dist = constrain(dist, 10, 200);
  dist = map(dist, 10, 200, 255, 0);

  Serial.print("Speed: ");
  Serial.println(dist);

  analogWrite(IN1, dist); 
  analogWrite(IN2, 0);

  delay(100); // Небольшая задержка для стабильности
}
