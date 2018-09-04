#include <LiquidCrystal.h>

#define ITERS 4 //Используется для замедления выдачи значений в порт
#define MY_ID "TfLjQmm3XZgiqdNA" // ID устройства по которому можно его найти через поиск по COM-портам
#define KEY_LENGTH 16
#define COUNTS 1000

int i;
int sig_inp = 2; //Аналоговый вход с которого производится считываение
int reset = 5; //Цифровой вывод, который дергает резет

int temp = 0; //переменная для считывания данных
int val = 0;//переменная для хранения данных
int iter = 0;//номер итерации, чтобы экрану не стало плохо
char imput_id[KEY_LENGTH];
bool answer = false; //Для проверки состояния ответа


bool with_pc = false; // Для отладки платы без программы на пк

// Инициализируем объект-экран, передаём использованные
// для подключения контакты на Arduino в порядке:
// RS, E, DB4, DB5, DB6, DB7
LiquidCrystal lcd(4, 5, 10, 11, 12, 13);

byte inc_byte;

//bool chk_conn = false; //Бул для проверки состояния коннекта
//int counter = 0;
//bool is_reading = false; //переменная для определения считывает ли контроллер информацию сейчас или нет

void setup() {
  // устанавливаем размер (количество столбцов и строк) экрана
  lcd.begin(16, 2);
  // очищаем дисплей
  lcd.clear();

  if (with_pc) {
    i = 0;
    while (i < KEY_LENGTH)
    {
      imput_id[i] = MY_ID[i];
      i++;
    }
  }

  Serial.begin(9600);//Скорость COM-порта 9600кб/с
  pinMode(sig_inp, INPUT);//Установка аналогого входа
  pinMode(reset, OUTPUT);//установка резета-выхода

}

void show() {
  lcd.clear();
  lcd.print(val);

}

void reset_and_show() { //Функция сброса
  show();
  val = 0;
  iter = 0;
  digitalWrite(reset, HIGH);

}

void loop() {
  i = 0;
  answer = false;
  if (with_pc) {
    while ((Serial.available() > 0)) {
      inc_byte = Serial.read();
      if (imput_id[i] == inc_byte)
        answer = true;
      else if (inc_byte == "C") {
        Serial.print("E");

      }
      else
        answer = false;
      i++;
      if ((i == KEY_LENGTH - 1) && (answer == true))
        Serial.print("MY_ID");
      //chk_conn = true;
    }

  }
  // if ((chk_conn) && (counter == COUNTS)) { //проверка подключения эхо-запросом
  // Serial.print(6);
  // inc_byte = Serial.read();
  // if (inc_byte == '7')
  // chk_conn = true;
  // else
  // chk_conn = false;
  // }

  temp = analogRead(sig_inp);//чтение АЦП
  if (temp > val)
    val = temp;
  if (iter == ITERS) //ждем ITERS итераций
    reset_and_show();
  iter++;
  //counter++;
}
