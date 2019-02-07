#include <LiquidCrystal.h>

#define coef 0.051
#define ITERS 10 //Используется для замедления выдачи значений в порт
#define TRIGGER 2 //Используется для замедления выдачи значений в порт
//#define MY_ID TfLjQmm3XZgiqdNA


int i;
int sig_inp = A2; //Аналоговый вход с которого производится считываение
int reset = 3; //Цифровой вывод, который дергает резет
float temp_t;

int temp = 0; //переменная для считывания данных
int previos = 0;//переменная для вывода
int show, prev_show;
int val = 0;//переменная для хранения данных
int iter = 0;//номер итерации, чтобы экрану не стало плохо

bool answer = true; //Для проверки состояния ответа
char MY_ID = 'Q'; // ID устройства по которому можно его найти через поиск по COM-портам
int g = 0;
double dt = 0;



bool with_pc = false; // Для отладки платы без программы на пк

// Инициализируем объект-экран, передаём использованные
// для подключения контакты на Arduino в порядке:
// RS, E, DB4, DB5, DB6, DB7
LiquidCrystal lcd(7, 6, 9, 10, 11, 12);

char inc_byte = 11;

bool chk_conn = false; //Бул для проверки состояния коннекта
int counter = 0;
//bool is_reading = false; //переменная для определения считывает ли контроллер информацию сейчас или нет

void setup() {
 temp_t = coef;
// lcd.createChar(0, smiley);
  // устанавливаем размер (количество столбцов и строк) экрана
  lcd.begin(16, 2);
  // очищаем дисплей
  lcd.clear();

  lcd.print("Starting..");
  lcd.setCursor(0, 1);
  lcd.print("Open COM...");
  
  lcd.print("Setting pins...");
  lcd.clear();

  Serial.begin(4800);//Скорость COM-порта 9600кб/с
  
  pinMode(sig_inp, INPUT);//Установка аналогого входа
  pinMode(reset, OUTPUT);//установка резета-выхода


prev_show = 0;
show = 0;
i = 0;
reset_and_show();
}

void show1() {
  temp_t = show*coef;
  lcd.clear();
  lcd.setCursor(0, 0);
  //lcd.write(byte(0));//выводит символ(по аски)
  lcd.print("Pulse energy"); // \xA0
  lcd.setCursor(0, 1);
  lcd.print(temp_t);
  lcd.print(" mJ");
  delay(200);
  //if(chk_conn)
    Serial.println(temp_t);
  
}

void reset_and_show() { //Функция сброса
  
  show1();
  iter = 0;
  prev_show = show;
  
  
  digitalWrite(reset, HIGH);
  delay (100);
  digitalWrite(reset, LOW);

}

void loop() {
 
  answer = false;

    if (Serial.available() > 0) {
      inc_byte = Serial.read();

       if (MY_ID == inc_byte){
        Serial.println(MY_ID);
        delay(2000);
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
    }


  temp = analogRead(sig_inp);//чтение АЦП
  if (temp > val){
    previos = val;
    dt = -previos + temp;//тест. наклон более 50
   // Serial.print("dt ");
   // Serial.println(dt);
   // Serial.print("val ");
   // Serial.println(val);
   // Serial.print("temp ");
   // Serial.println(temp);
    //Serial.print("show ");
    //Serial.println(show);
   // Serial.print("prev_show ");
    //Serial.println(prev_show);
    delay(20);
    if (dt > TRIGGER)
      show = temp;
    
    }

  
  val = temp;
  
  
  if (iter > ITERS) //ждем ITERS итераций
  {
 
    if ((prev_show - show) != 0){
     
      reset_and_show();
      
    }
  }
  iter++;

}

