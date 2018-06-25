int sig_inp = 2; //Аналоговый вход с которого производится считываение
int reset = 5; //Цифровой вывод, который дергает резет
bool is_reading = false; //переменная для определения считывает ли контроллер информацию сейчас или нет

void setup() {
  
  Serial.begin(9600);//Скорость COM-порта 
  pinMode(sig_inp, INPUT);//Установка аналогого  

}

void loop() {
  if (Serial.available() > 0){
    
      inc_byte = Serial.read();
      switch (inc_byte){
        case:''{break;}
        case:''{break;}
        case:''{break;}
        default:{break;}
      }
    }

    

}
