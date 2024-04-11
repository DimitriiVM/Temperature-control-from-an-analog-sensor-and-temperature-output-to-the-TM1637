/*
#AUTHOR Дмитрий Витальевич Мельник
#MAIL i.x.c.o.n@yandex.ru
#LICENSE Использование  только  для не коммерческих проектов, без упоминания автора. При использовании автор не несет ни какой отвественности, и не дает ни какой гарантии работы. Не ведет поддержку или исправление ошибок. 
*/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define PINSPEAK A0 //Пин для подключения динамика
#define PINANALOGREAD A7
#define LIMITTEMP 50

#define SCREEN_WIDTH 128 // Ширина OLED-дисплея, в пикселях
#define SCREEN_HEIGHT 32 // Высота OLED-дисплея, в пикселях
// Декларация для дисплея SSD1306, подключенного к I2C (контакты SDA, SCL)
#define OLED_RESET -1 // Сброс pin-кода # (или -1, если используется общий pin-код сброса Arduino)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int a = 0;
int b = 0;
int tempnow = 0; // Конечное значение, которое используется для всех вычислений

const int sizearrtemp = 5; // Размер массива для фильтрации // Если хочешь повысить фильтрацию и правность просто увеличивай число,  но тогда первый запуск будет  очень  длинным.
int arrtemp[sizearrtemp]; // Сам массив фильтрации

int flagspeakcount = 0;

uint32_t timer = 0; //Таймер для псевдомного поточности
uint32_t timer1 = 0; //Таймер для псевдомного поточности
uint32_t timer2 = 0; //Таймер для псевдомного поточности
uint32_t timer3 = 0; //Таймер для псевдомного поточности

void setup() {
  Serial.begin(115200); //Иницлизация порта
  Serial.println("Start OK!");
  for(int i = 0; i < sizearrtemp; i++){//Тут мы складываем все значения массива в сумму
    arrtemp[i] = 0; //Почистим в начале массив дабы избежать мусора при первом запуске
  }
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
  }
  display.clearDisplay(); // Чистим буфер
  display.setCursor(14, 12);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.println("START OK!");
  display.display();
  delay(2000);

}

void loop() {
  if(millis() - timer >= 1500){//START 1
    timer = millis();
    //Serial.print("Analog value: ");
    //Serial.println(a);
    Serial.print("The value in degrees: ");
    Serial.println(tempnow);
    display.clearDisplay();
    //display.drawRect(0, 0, 128, 32, WHITE); // это рамка для понимания

    display.fillCircle(50, 24, 5, WHITE); // Круг основание градусника
    display.fillRoundRect(48, 4, 5, 24, 2, WHITE);// Прямоугольник скругленный
    display.fillRoundRect(48, 6, 8, 3, 2, WHITE);
    display.fillRoundRect(48, 10, 8, 3, 2, WHITE);
    display.fillRoundRect(48, 14, 8, 3, 2, WHITE);
    
    display.setCursor(68, 6);
    display.setTextColor(WHITE);
    display.setTextSize(3);
    display.println(tempnow);
    display.display();
  }//END 1

  if(millis() - timer1 >= 500){//START 2 
    timer1 = millis();
    a = analogRead(PINANALOGREAD); //Чтение аналогового значения  входа A7
    if(a>1020){b=-40;}
    if(a>1010 and a<1020){b=-16;}
    if(a>1000 and a<1010){b=-15;}
    if(a>990 and a<1000){b=-14;}
    if(a>980 and a<990){b=-13;}
    if(a>970 and a<980){b=-12;}
    if(a>960 and a<970){b=-11;}
    if(a>950 and a<960){b=-10;}
    if(a>940 and a<950){b=-9;}
    if(a>930 and a<940){b=-8;}
    if(a>920 and a<930){b=-7;}
    if(a>910 and a<920){b=-6;}
    if(a>900 and a<910){b=-5;}
    if(a>890 and a<900){b=-4;}
    if(a>880 and a<890){b=-3;}
    if(a>870 and a<880){b=-2;}
    if(a>860 and a<870){b=-1;}    
    if(a>850 and a<860){b=0;}
    if(a>840 and a<850){b=1;}
    if(a>830 and a<840){b=2;}
    if(a>820 and a<830){b=3;}
    if(a>810 and a<820){b=4;}
    if(a>800 and a<810){b=5;}
    if(a>790 and a<800){b=6;}
    if(a>780 and a<790){b=7;}
    if(a>770 and a<780){b=8;}
    if(a>760 and a<770){b=9;}
    if(a>750 and a<760){b=10;}
    if(a>740 and a<750){b=11;}
    if(a>730 and a<740){b=12;}
    if(a>720 and a<730){b=13;}
    if(a>710 and a<720){b=14;}
    if(a>700 and a<710){b=15;}
    if(a>690 and a<700){b=16;}
    if(a>680 and a<690){b=17;}
    if(a>670 and a<680){b=18;}
    if(a>660 and a<670){b=19;}
    if(a>650 and a<660){b=20;}
    if(a>640 and a<650){b=21;}
    if(a>630 and a<640){b=22;}
    if(a>620 and a<630){b=23;}
    if(a>610 and a<620){b=24;}
    if(a>600 and a<610){b=25;}
    if(a>590 and a<600){b=26;}
    if(a>580 and a<590){b=27;}
    if(a>570 and a<580){b=28;}
    if(a>560 and a<570){b=29;}
    if(a>550 and a<560){b=30;}
    if(a>540 and a<550){b=31;}
    if(a>530 and a<540){b=32;}
    if(a>520 and a<530){b=33;}
    if(a>510 and a<520){b=34;}
    if(a>500 and a<510){b=35;}
    if(a>490 and a<500){b=36;}
    if(a>480 and a<490){b=37;}
    if(a>470 and a<480){b=38;}
    if(a>460 and a<470){b=39;}
    if(a>450 and a<460){b=40;}
    if(a>440 and a<450){b=41;}
    if(a>430 and a<440){b=42;}
    if(a>421 and a<430){b=43;}
    if(a>412 and a<421){b=44;}
    if(a>400 and a<412){b=45;}
    if(a>397 and a<400){b=46;}
    if(a>389 and a<397){b=47;}
    if(a>378 and a<389){b=48;}
    if(a>369 and a<378){b=49;}
    if(a>363 and a<369){b=50;}
    if(a>356 and a<363){b=51;}
    if(a>347 and a<356){b=52;}
    if(a>338 and a<347){b=53;}
    if(a>330 and a<338){b=54;}
    if(a>322 and a<330){b=55;}
    if(a>315 and a<322){b=56;}
    if(a>309 and a<315){b=57;}
    if(a>302 and a<309){b=58;}
    if(a>290 and a<302){b=59;}
    if(a>285 and a<290){b=60;}
    if(a>277 and a<285){b=61;}
    if(a>272 and a<277){b=62;}
    if(a>268 and a<272){b=63;}
    if(a>264 and a<268){b=64;}
    if(a>260 and a<264){b=65;}
    if(a>254 and a<260){b=66;}
    if(a>248 and a<254){b=67;}
    if(a>242 and a<248){b=68;}
    if(a>236 and a<242){b=69;}
    if(a>231 and a<236){b=70;}
    if(a>226 and a<231){b=71;}
    if(a>220 and a<226){b=72;}
    if(a>215 and a<220){b=73;}
    if(a>204 and a<215){b=74;}
    if(a>198 and a<204){b=75;}
    if(a>194 and a<198){b=76;}
    if(a>190 and a<194){b=77;}
    if(a>185 and a<190){b=78;}
    if(a>180 and a<185){b=79;}
    if(a>176 and a<180){b=80;}
    if(a>172 and a<176){b=81;}
    if(a>168 and a<172){b=82;}
    if(a>164 and a<168){b=83;}
    if(a>160 and a<164){b=84;}
    if(a>156 and a<160){b=85;}
    if(a>152 and a<156){b=86;}
    if(a>148 and a<152){b=87;}
    if(a>144 and a<148){b=88;}
    if(a>141 and a<144){b=89;}
    if(a>137 and a<141){b=90;}
    if(a>134 and a<137){b=91;}
    if(a>131 and a<134){b=92;}
    if(a>128 and a<131){b=93;}
    if(a>125 and a<128){b=94;}
    if(a>122 and a<125){b=95;}
    if(a>120 and a<122){b=96;}
    if(a>118 and a<120){b=97;}
    if(a>116 and a<118){b=98;}
    if(a>113 and a<116){b=99;}
    if(a>111 and a<113){b=100;}
    if(a>108 and a<111){b=101;}
    if(a>106 and a<108){b=102;}
    if(a>103 and a<106){b=103;}
    if(a>100 and a<103){b=104;}
    if(a>98 and a<100){b=105;}
    if(a>96 and a<98){b=106;}
    if(a>94 and a<96){b=107;}
    if(a>92 and a<94){b=108;}
    if(a>90 and a<92){b=109;}
    if(a>88 and a<90){b=110;}
    if(a>86 and a<88){b=111;}
    if(a>84 and a<86){b=112;}
    if(a>82 and a<84){b=113;}
    if(a>80 and a<82){b=114;}
    if(a>78 and a<80){b=115;}
    if(a>76 and a<78){b=116;}
    if(a>74 and a<76){b=117;}
    if(a>72 and a<74){b=118;}
    if(a>70 and a<72){b=119;}
    if(a>68 and a<70){b=120;}
    if(a>66 and a<68){b=121;}
    if(a>64 and a<66){b=122;}
    if(a>62 and a<64){b=123;}
    if(a>60 and a<62){b=124;}
    if(a>58 and a<60){b=125;}
    if(a>56 and a<58){b=126;}
    if(a>54 and a<56){b=127;}
    if(a>53 and a<54){b=128;}
    if(a>52 and a<53){b=129;}
    if(a>51 and a<52){b=130;}
    if(a>50 and a<51){b=131;}
    if(a>49 and a<50){b=132;}
    if(a>48 and a<49){b=133;}
    if(a>47 and a<48){b=134;}
    if(a>46 and a<47){b=135;}
    if(a>45 and a<46){b=136;}
    if(a>44 and a<45){b=137;}
    if(a>43 and a<44){b=138;}
    if(a>42 and a<43){b=139;}
    if(a>41 and a<42){b=140;}
    if(a>40 and a<41){b=141;}
    if(a>39 and a<40){b=142;}
    if(a>38 and a<39){b=143;}
    if(a>37 and a<38){b=144;}
    if(a>36 and a<37){b=145;}
    if(a>35 and a<36){b=146;}
    if(a>34 and a<35){b=147;}
    if(a>33 and a<34){b=148;}
    if(a>32 and a<33){b=149;}
    if(a<32){b=150;}

    int sumarrtemp = 0;// Данная  переменная используется, чтобы  хранить сумму всей чисел массива
    arrtemp[0] = b;//В первый индекс массива пишем считанное значение
    for(int i = 0; i < sizearrtemp-1; i++){// Тут мы  все значения сдвигаем на один вверх имитируя очередь
      arrtemp[i+1] = arrtemp[i]; //Смещаем массив
    }
    for(int i = 0; i < sizearrtemp; i++){//Тут мы складываем все значения массива в сумму
      sumarrtemp = sumarrtemp + arrtemp[i];
    }
    tempnow = sumarrtemp / sizearrtemp;//Тут мы вычисляем среднее и его и  будет показывать в работе.
  }//END 2

  if(millis() - timer2 >= 1000){//START 3
    timer2 = millis();
    if((LIMITTEMP <= tempnow) &&  (flagspeakcount < 5)){
        tone(PINSPEAK, 1000, 300);
        flagspeakcount++;
        Serial.println("HOT");
    }
  }//END 3

  if(millis() - timer3 >= 30000){//START 4
    timer3 = millis();
    flagspeakcount = 0;
    Serial.println("TIMER NULL");
    /*
    Выше мы просто при каждом пищании прибавляем к счетчику +1, а в этом месте мы  берем и каждые 30 секунд  его отчищаем.
    т.е. у нас будет что  при превышении температуры 5 раз пищать, потом молчит. Через 30 секунд значение обнуляется и он опять будет пищать.
    */
  }//END 4

}
  
