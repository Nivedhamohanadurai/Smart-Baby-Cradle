#include <Servo.h>

#define key1 2
#define key2 3
#define serv 9
#define sound 8
#define wat A0
#define buz 7

Servo serw;
int key1_r, key2_r;
int pos = 100;
int auto_m, auto_Status, cradle_m, cradle_Status;
int s_c, s_x;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(sound, INPUT);
  pinMode(key1, INPUT_PULLUP);
  pinMode(key2, INPUT_PULLUP);
  pinMode(buz, OUTPUT);
  digitalWrite(buz, LOW);
  serw.attach(serv);
  serw.write(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  key1_r = digitalRead(key1);
  key2_r = digitalRead(key2);
  int wat_r = analogRead(wat);
  int snd_r = digitalRead(sound);





  if (wat_r > 500) {
    digitalWrite(buz, HIGH);
    delay(200);
    digitalWrite(buz, LOW);
  }


  if (key1_r == 0 and auto_m == 0) {
    Serial.println("Auto Mode ON");
    auto_Status = 1;
    auto_m = 1;
  } else if (key1_r == 1 and auto_m == 1) {

    auto_m = 2;
  }

  else if (key1_r == 0 and auto_m == 2) {
    Serial.println("Auto Mode OFF");
    auto_Status = 0;
    auto_m = 3;
  } else if (key1_r == 1 and auto_m == 3) {

    auto_m = 0;
  }


  if (auto_Status == 1) {
    Serial.println(snd_r);
    if (!snd_r) {
      s_c += 1;
      if (s_c >= 2) {
        cradle_Status = 1;
        s_x = 10;
      }
    } else {
      s_x += 1;
      if (s_x > 10) {
        cradle_Status = 0;
        s_c = 0;
        s_x = 10;
      }
    }


  } else {
   s_x = 10;
    s_c = 0;
    if (key2_r == 0 and cradle_m == 0) {
      Serial.println("Cradle ON");
      for (pos = 100; pos >= 50; pos -= 1) {  // goes from 180 degrees to 0 degrees
        serw.write(pos);                      // tell servo to go to position in variable 'pos'
        delay(15);                            // waits 15 ms for the servo to reach the position
      }
      cradle_Status = 1;
      cradle_m = 1;
    } else if (key2_r == 1 and cradle_m == 1) {

      cradle_m = 2;
    }

    else if (key2_r == 0 and cradle_m == 2) {
      Serial.println("Cradle OFF");
      cradle_Status = 0;
      cradle_m = 3;
    } else if (key2_r == 1 and cradle_m == 3) {

      cradle_m = 0;
    }
  }

  if (cradle_Status) {

    for (pos = 50; pos <= 150; pos += 1) {  // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      serw.write(pos);  // tell servo to go to position in variable 'pos'
      delay(15);        // waits 15 ms for the servo to reach the position
    }
    for (pos = 150; pos >= 50; pos -= 1) {  // goes from 180 degrees to 0 degrees
      serw.write(pos);                      // tell servo to go to position in variable 'pos'
      delay(15);                            // waits 15 ms for the servo to reach the position
    }
  } else {
    serw.write(100);
  }


  delay(100);
}