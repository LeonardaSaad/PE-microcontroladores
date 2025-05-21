// Biblioteca para controle do display LCD
#include <LiquidCrystal.h> 

LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2); 

void setup()
{
  lcd_1.begin(16, 2);
  
  Serial.begin(9600);

  // Define os pinos analógicos como entrada para sensores de umidade
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
}

// Função que converte o valor lido do sensor em porcentagem de umidade
int calcMoisture(int value) {
  float calc = (float)(value - 300) / (876 - 300) * 100; // Mapeia o valor de 300 a 876 para 0% a 100%
  float moisture = constrain(calc, 0 , 100); // Garante que o valor fique entre 0% e 100%
  return moisture;
}

void loop()
{
  // Lê os valores analógicos dos sensores de umidade
  int analog_A0 = analogRead(A0);
  int analog_A1 = analogRead(A1);
  int analog_A2 = analogRead(A2);
  int analog_A3 = analogRead(A3);

  // Escreve os rótulos dos sensores na primeira linha do LCD
  lcd_1.setCursor(0,0); 
  lcd_1.print("ST1|ST2|ST3|ST4|"); 

  lcd_1.setCursor(0,1);

  char row[17]; 

  // Formata a linha com os valores de umidade em porcentagem para cada sensor
  sprintf(
    row,
    "%3d|%3d|%3d|%3d|",
    (int)calcMoisture(analog_A0),
    (int)calcMoisture(analog_A1),
    (int)calcMoisture(analog_A2),
    (int)calcMoisture(analog_A3)
  );

  lcd_1.setCursor(0,1); 

  // Exibe os valores formatados na segunda linha do LCD
  lcd_1.print(row);     
}
