// wifi ssid password arduphone
// state 5 -> ventilation eklenmedi
// state 0 -> alar durumu GPIO cikisi eklenmedi
// pwm degisimine gore analog okuma eklenmedi.

#define CP_SIGNAL_OUT 35
#define CP_SIGNAL_IN 33
#define COMM_BT0 25
#define COMM_BT1 26
#define COMM_BT2 27
#define COMM_BT3 14

unsigned int deviceStateCode = 0;
unsigned int deviceState = 1;
//1 -> State A (12V DC - Direnc Yok - bekleme)
//2 -> State B (9V AC - 2.74K Direnc - arac takildi ve hazir)
//3 -> State C (6V AC - 0.882K Direnc - arac sarj oluyor )
//4 -> State D (3C AC - 0.246K Direnc - arac Sarj oluyor. Havanlandirma gerekiyor)
//5 -> State E (0V- HATA)

unsigned int chargeState = 1;  //Device State ile Ayni



unsigned int cpAdcLimits[6] = { 3400, 2320, 1550, 620, 0, 1780 };  //%50
//unsigned int cpAdcLimits[6] = { 3400, 2320, 1400, 620, 0, 1780 };  //%20
//unsigned int cpAdcLimits[6] = { 3543, 2423, 680, 384, 0, 940 };  //%27
//0 -> 12VDC //Araba takili degil
//1 -> 9VDC //Araba takili, pwm baslamadi
//2 -> 9VAC //Araba takili, pwm basladi, sarj baslamadi
//3 -> 6VAC //Araba takili, pwm basladi, sarj basladi
//4 -> 3VAC //Araba takili, sarj basladi, havalandirma gerekiyor
//5 -> 12VAC //pwm varken araba ayrildi.


hw_timer_t *freqGenTimer = NULL;


unsigned int analogValue = 0;
unsigned long mainCounter = 0;
unsigned int pwmState = 0;
unsigned int pwmCounter = 0;
const int pwmDutyCycle = 52;// ( 50 =22kw ) ( 25=11kw ) ( 17=7kw )
unsigned int errorCounter = 0;

void IRAM_ATTR onTimer() {

  if (pwmCounter < pwmDutyCycle) {
    digitalWrite(CP_SIGNAL_IN, HIGH);
  } else {
    digitalWrite(CP_SIGNAL_IN, LOW);
  }

  pwmCounter++;
  if (pwmCounter == 100) {
    pwmCounter = 0;
  }
}

void getCpVoltage() {

  if (pwmState == 1) {

    while (digitalRead(CP_SIGNAL_IN) == LOW) {
    }
    while (digitalRead(CP_SIGNAL_IN) == HIGH) {
    }

    while (digitalRead(CP_SIGNAL_IN) == LOW) {
    }
    analogValue = analogRead(CP_SIGNAL_OUT);
  } else {
    analogValue = analogRead(CP_SIGNAL_OUT);
  }
}

unsigned int getchargeState() {

  unsigned int setState = 0;
  unsigned int pinAdcValue = analogValue;

  if ((pinAdcValue > cpAdcLimits[0] * 0.90) && (pinAdcValue < cpAdcLimits[0] * 1.10)) {
    setState = 1;  //12VDC -> soket takili degil, pwm baslamadi
  }

  if ((pinAdcValue > cpAdcLimits[1] * 0.90) && (pinAdcValue < cpAdcLimits[1] * 1.10)) {
    setState = 2;  //9VDC -> soket takili, pwm baslamadi, soket yeni takildi
  }

  if ((pinAdcValue > cpAdcLimits[2] * 0.90) && (pinAdcValue < cpAdcLimits[2] * 1.10)) {

    if (deviceState == 1) {
      setState = 0;  //Hata var
    } else {
      setState = 3;  //9VAC -> soket takili, pwm basladi. arabanin sarj almasi bekleniyor
    }
  }

  if ((pinAdcValue > cpAdcLimits[3] * 0.90) && (pinAdcValue < cpAdcLimits[3] * 1.10)) {
    setState = 4;  //6VAC -> soket takildi, pwm basladi araba sarj aliyor
  }

  if ((pinAdcValue > cpAdcLimits[4] * 0.90) && (pinAdcValue < cpAdcLimits[4] * 1.0)) {
    setState = 5;  //3VAC -> soket takildi, pwm basladi araba sarj aliyor havalandirma ihtiyac
  }

  if ((pinAdcValue > cpAdcLimits[5] * 0.90) && (pinAdcValue < cpAdcLimits[5] * 1.10)) {

    if (deviceState == 1) {
      setState = 0;  //Hata var
    } else {
      setState = 6;  //12VAC -> soket takili degil, pwm basladi, sarj olurken soket cikarildi
    }
  }

  return setState;
}

void setup() {

  delay(1000);
  Serial.begin(9600);
  Serial.println("IKARUS TEKNOLOJI");

  pinMode(CP_SIGNAL_IN, OUTPUT);
  pinMode(COMM_BT0, OUTPUT);
  pinMode(COMM_BT1, OUTPUT);
  pinMode(COMM_BT2, OUTPUT);
  pinMode(COMM_BT3, INPUT);

  digitalWrite(CP_SIGNAL_IN, HIGH);
  digitalWrite(COMM_BT0, LOW);
  digitalWrite(COMM_BT1, LOW);
  digitalWrite(COMM_BT2, LOW);

  freqGenTimer = timerBegin(0, 80, true);
  timerAttachInterrupt(freqGenTimer, &onTimer, true);
  timerAlarmWrite(freqGenTimer, 10, true);
  //timerAlarmEnable(freqGenTimer);
}

void loop() {

  if (mainCounter < millis()) {

    mainCounter = millis() + 400;
    getCpVoltage();
    chargeState = getchargeState();

    if (deviceState == 1) {  //Cihaz bekleme modunda ise (araba takili degil)

      switch (chargeState) {

        case 1:  //Olcume gore bekleme durumunda ise
          deviceStateCode = 11;
          digitalWrite(COMM_BT0, LOW);
          digitalWrite(COMM_BT1, LOW);
          digitalWrite(COMM_BT2, LOW);
          break;

        case 2:  //Olcume gore araba algilandi ise
          deviceState = 2;
          digitalWrite(COMM_BT0, LOW);
          digitalWrite(COMM_BT1, HIGH);
          digitalWrite(COMM_BT2, LOW);
          deviceStateCode = 12;
          break;

        default:  //Olcume gore sarj baslamadigi halde hata algilandi ise
          //deviceState = 0;
          deviceStateCode = 10;
          break;
      }
    }

    if (deviceState == 2) {  //Cihaz arac baglandi ama pwm baslamadi modunda ise

      switch (chargeState) {

        case 1:  //Olcume gore arac istasyondan ayrildi ise
          deviceState = 1;
          timerAlarmDisable(freqGenTimer);
          pwmState = 0;
          digitalWrite(CP_SIGNAL_IN, HIGH);
          digitalWrite(COMM_BT0, LOW);
          digitalWrite(COMM_BT1, LOW);
          digitalWrite(COMM_BT2, LOW);
          deviceStateCode = 21;
          break;

        case 2:  //Arac Baglandi ama ana islemciden PWM baslatma gelmedi ise, beklemede

          if (digitalRead(COMM_BT3) == HIGH) {  //ana islemciden pwm baslat emri geldi mi?
            timerAlarmEnable(freqGenTimer);
            pwmState = 1;
          }
          deviceStateCode = 22;
          break;

        case 3:  //Arac baglandi, pwm basladi ise
          deviceState = 3;
          errorCounter = 0;
          digitalWrite(COMM_BT0, LOW);
          digitalWrite(COMM_BT1, HIGH);
          digitalWrite(COMM_BT2, LOW);
          deviceStateCode = 23;
          break;

        case 4:  //Arac baglandi, pwm basladi ise

          deviceState = 4;
          digitalWrite(COMM_BT0, HIGH);
          digitalWrite(COMM_BT1, HIGH);
          digitalWrite(COMM_BT2, LOW);
          deviceStateCode = 24;
          break;

        default:  //Olcume gore hata algilandi ise
          //deviceState = 0;


          deviceStateCode = 26;
          break;
      }
    }

    if (deviceState == 3) {  //Cihaz arac baglandi, Pwm verildi, aracın sarj almasi bekleniyor ise

      switch (chargeState) {

        case 1:  //Olcume gore arac istasyondan ayrildi ise (case 3'den sonra, araba soketi cikarildi ise buraya gelecek)
          deviceState = 1;
          timerAlarmDisable(freqGenTimer);
          pwmState = 0;
          digitalWrite(CP_SIGNAL_IN, HIGH);
          digitalWrite(COMM_BT0, LOW);
          digitalWrite(COMM_BT1, LOW);
          digitalWrite(COMM_BT2, LOW);
          deviceStateCode = 21;
          break;

        case 2:  //Arac Baglandi ama ana islemci tarafindan pwm sonlandirildi ise (case 3'den sonra, araba soket takili ise buraya gelecek)
          deviceState = 2;
          digitalWrite(COMM_BT0, LOW);
          digitalWrite(COMM_BT1, HIGH);
          digitalWrite(COMM_BT2, LOW);
          deviceStateCode = 32;
          break;

        case 3:                                //Arac baglandi, pwm verildi, arac sarja baslamadi ise
          if (digitalRead(COMM_BT3) == LOW) {  //ana islemci tarafindan pwm sonlandirildi ise
            timerAlarmDisable(freqGenTimer);
            pwmState = 0;
            digitalWrite(CP_SIGNAL_IN, HIGH);
          }

          digitalWrite(COMM_BT0, HIGH);
          digitalWrite(COMM_BT1, HIGH);
          digitalWrite(COMM_BT2, LOW);
          deviceStateCode = 33;
          errorCounter = 0;
          break;

        case 4:  //Arac baglandi pwm basladi, araba sarja basladi ise
          deviceState = 4;
          digitalWrite(COMM_BT0, HIGH);
          digitalWrite(COMM_BT1, HIGH);
          digitalWrite(COMM_BT2, LOW);
          deviceStateCode = 34;
          break;

        case 6:  //Pwm varken araba soketi sokuldu ise

          if (errorCounter < 10) {
            errorCounter++;
          }
          else {
            deviceState = 1;
            timerAlarmDisable(freqGenTimer);
            pwmState = 0;
            digitalWrite(CP_SIGNAL_IN, HIGH);
            digitalWrite(COMM_BT0, LOW);
            digitalWrite(COMM_BT1, LOW);
            digitalWrite(COMM_BT2, LOW);
          }
          deviceStateCode = 36;
          break;

        default:  //hata durumu

          if (errorCounter < 10) {
            errorCounter++;
          }
          else {
            deviceState = 0;
          }
          deviceStateCode = 30;
          break;
      }
    }

    if (deviceState == 4) {  //Cihaz arac baglandi ve sarj basladi modunda ise

      switch (chargeState) {

        case 1:  //Olcume gore arac istasyondan ayrildi ise (case 3'den sonra, araba soketi cikarildi ise buraya gelecek)
          deviceState = 1;
          timerAlarmDisable(freqGenTimer);
          pwmState = 0;
          digitalWrite(CP_SIGNAL_IN, HIGH);
          digitalWrite(COMM_BT0, LOW);
          digitalWrite(COMM_BT1, LOW);
          digitalWrite(COMM_BT2, LOW);
          deviceStateCode = 41;
          break;

        case 2:  //Arac Baglandi ama ana islemci tarafindan pwm sonlandirildi ise (case 3'den sonra, araba soket takili ise buraya gelecek)
          deviceState = 2;
          digitalWrite(COMM_BT0, LOW);
          digitalWrite(COMM_BT1, HIGH);
          digitalWrite(COMM_BT2, LOW);
          deviceStateCode = 42;
          break;

        case 3:  //Arac baglandi, arac sarj alirken ana islemci tarafından pwm kesildi ise (case 4'den sonra buraya gelebilir)
          deviceState = 3;
          digitalWrite(COMM_BT0, HIGH);
          digitalWrite(COMM_BT1, LOW);
          digitalWrite(COMM_BT2, LOW);
          deviceStateCode = 43;
          break;

        case 4:                                //Arac baglandi pwm  basladi sarj basladi ise
          if (digitalRead(COMM_BT3) == LOW) {  //ana islemci pwm kes der ise
            timerAlarmDisable(freqGenTimer);
            pwmState = 0;
            digitalWrite(CP_SIGNAL_IN, HIGH);
          }
          deviceStateCode = 44;
          break;

        case 5:  //Arac baglandi pwm  basladi sarj basladi ve havalandirma gerekiyor ise
          deviceStateCode = 45;
          break;

        case 6:  //Pwm varken araba soketi sokuldu ise
          deviceState = 1;
          timerAlarmDisable(freqGenTimer);
          pwmState = 0;
          digitalWrite(CP_SIGNAL_IN, HIGH);
          digitalWrite(COMM_BT0, LOW);
          digitalWrite(COMM_BT1, LOW);
          digitalWrite(COMM_BT2, LOW);
          deviceStateCode = 46;
          break;

        default:  //hata algilandi ise
          //deviceState = 0;
          deviceStateCode = 40;
          break;
      }
    }

    if (deviceState == 5) {  //Cihaz arac baglandi ve sarj basladi ve havalandirma modunda ise
    }

    if (deviceState == 0) {  //Cihaz ariza modunda ise

      deviceStateCode = 0;
      timerAlarmDisable(freqGenTimer);
      pwmState = 0;
      digitalWrite(CP_SIGNAL_IN, HIGH);
    }

    Serial.print(analogValue);
    Serial.print("=");
    Serial.print(getchargeState());
    Serial.print("=");
    Serial.print(deviceStateCode);
    Serial.print("=");
    Serial.print(pwmState);
    Serial.print("=");
    Serial.print(digitalRead(COMM_BT0));
    Serial.print("=");
    Serial.print(digitalRead(COMM_BT1));
    Serial.print("=");
    Serial.print(digitalRead(COMM_BT2));
    Serial.print("=");
    Serial.println(digitalRead(COMM_BT3));
  }
}
