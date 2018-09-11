#include <LiquidCrystal.h>

#define ITERS 5000 //Используется для замедления выдачи значений в порт
//#define MY_ID TfLjQmm3XZgiqdNA
#define KEY_LENGTH 3
#define COUNTS 1000

int i;
int sig_inp = A2; //Аналоговый вход с которого производится считываение
int reset = 6; //Цифровой вывод, который дергает резет

int temp = 0; //переменная для считывания данных
int val = 0;//переменная для хранения данных
int iter = 0;//номер итерации, чтобы экрану не стало плохо
//char imput_id[KEY_LENGTH];
bool answer = true; //Для проверки состояния ответа
char MY_ID = 'Q'; // ID устройства по которому можно его найти через поиск по COM-портам

byte smiley[8] = {
  B01100,
  B01100,
  B00100,
  B11111,
  B00100,
  B01010,
  B01001,
};
bool with_pc = false; // Для отладки платы без программы на пк

// Инициализируем объект-экран, передаём использованные
// для подключения контакты на Arduino в порядке:
// RS, E, DB4, DB5, DB6, DB7
LiquidCrystal lcd(4, 5, 10, 11, 12, 13);

char inc_byte = 11;

bool chk_conn = false; //Бул для проверки состояния коннекта
int counter = 0;
//bool is_reading = false; //переменная для определения считывает ли контроллер информацию сейчас или нет

void setup() {
  lcd.createChar(0, smiley);
  // устанавливаем размер (количество столбцов и строк) экрана
  lcd.begin(16, 2);
  // очищаем дисплей
  lcd.clear();

  //if (with_pc) {
 //   i = 0;
  //  while (i < KEY_LENGTH)
  //  {
   //   imput_id[i] = MY_ID[i];
   //   i++;
  //  }
  //}
  lcd.print("Starting..");
  lcd.setCursor(0, 1);
  lcd.print("Open COM...");
  Serial.begin(9600);//Скорость COM-порта 9600кб/с
  lcd.print("Setting pins...");
  pinMode(sig_inp, INPUT);//Установка аналогого входа
  pinMode(reset, OUTPUT);//установка резета-выхода
lcd.clear();
i = 0;
}

void show() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(byte(0));//выводит символ(по аски)
  lcd.print("ADC(5v):"); // \xA0
  lcd.setCursor(0, 1);
  lcd.print(val);
  //counter ++;
  if(chk_conn)
    Serial.println(val);
  
}

void reset_and_show() { //Функция сброса
  show();
  val = 0;
  iter = 0;
  digitalWrite(reset, HIGH);

}

void loop() {
  
  answer = false;
  //if (with_pc) {
    if ((Serial.available() > 0)) {
      inc_byte = Serial.read();

      //delay(200);
      //Serial.println("sosi");

       if (MY_ID == inc_byte){
        Serial.println(MY_ID);
        delay(1000);
        chk_conn = true;
        counter = 0;
       }
      else if (inc_byte == 'S') {
        Serial.write("E\n");
        counter = 0;
      }
      else
      {
        answer = false;
        i = 0;
        Serial.write("Decline\n");
      }
                                                       //
    }

  //}
  // if ((chk_conn) && (counter == COUNTS)) { //проверка подключения эхо-запросом
  // Serial.print(6);
  // inc_byte = Serial.read();
  // if (inc_byte == '7')
  // chk_conn = true;
  // else
  // chk_conn = false;
  // }
 // if (counter == 40)
 //   chk_conn = false;

  temp = analogRead(sig_inp);//чтение АЦП
  if (temp > val)
    val = temp;
  if (iter == ITERS) //ждем ITERS итераций
    reset_and_show();
  iter++;

      //counter++;
}
