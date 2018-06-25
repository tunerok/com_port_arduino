#DEFINE ITERS 4


int sig_inp = 2; //Аналоговый вход с которого производится считываение
int reset = 5; //Цифровой вывод, который дергает резет
bool is_reading = false; //переменная для определения считывает ли контроллер информацию сейчас или нет
int temp = 0; //переменная для считывания данных
int val = 0;//переменная для хранения данных
int iter = 0;//номер итерации, чтобы экрану не стало плохо

void setup() {
  
  Serial.begin(9600);//Скорость COM-порта 9600кб/с
  pinMode(sig_inp, INPUT);//Установка аналогого 
  pinMode(reset, OUTPUT);//установка резета  

}

void reset_and_show(){//функция сброса
	show(val);
	val = 0;
	iter = 0;
	digitalWrite(reset, HIGH);
	
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
	
	
    temp = analogRead(analogPin);//чтение АЦП
	if (temp > val)
		val = temp;
	if (iter == ITERS) //ждем ITERS итераций
		reset_and_show();
	iter++;
	
}
