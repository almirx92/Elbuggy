
/*
 Digital outputs on arduino

 PWM modulacija
 --------------------------------

 digitalPin 9 PWM -> dialUbrzanje  zakodirano a1 value
 digitalPin 10 PWM -> dialKocenje  zakodirano g1 value



 digitalPin 2 -> ON  zakodirano b1
 digitalPin 3 -> OFF zakodirano c1

 Smijer kretanja
 ---------------------------
 digitalPin 4 ->  Naprijed  zakodirano e1
 digitalPin 5 ->  Nazad     zakodirano d1
 ditalPin 6 -> Zaustavi     zakodiranof1

*/


#define dial_Ubrzanje 9
#define dial_Kocenje 10
#define ON 2
#define OFF 3
#define Naprijed 4
#define Nazad 5
#define Zaustavi 6

void setup()
{
  pinMode(dial_Ubrzanje, OUTPUT);
  pinMode(dial_Kocenje, OUTPUT);
  pinMode(ON, OUTPUT);
  pinMode(OFF, OUTPUT);
  pinMode(Naprijed, OUTPUT);
  pinMode(Nazad, OUTPUT);
  pinMode(Zaustavi, OUTPUT);
  
//  pinMode(red_led, OUTPUT);
//  pinMode(green_led, OUTPUT);
//  pinMode(blue_led, OUTPUT);
//  analogWrite(red_led, 255);
//  analogWrite(green_led, 255);
//  analogWrite(blue_led, 255);
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available()){
    char output_specifier = Serial.read();
    int output_value = Serial.parseInt();
    write_outputs(output_specifier, output_value);
  }
}

void write_outputs(char out, int value)
{
    if(out == 'a'){
      int val = map(value, 0, 100, 0, 255);
      analogWrite(dial_Ubrzanje, val);
      return;
    }
    if(out == 'b'){
      digitalWrite(OFF,LOW);
      digitalWrite(ON, HIGH);
    }
    if(out =='c'){
      digitalWrite(ON,LOW);
      digitalWrite(OFF,HIGH);
    }
    if(out =='d'){
      digitalWrite(Nazad, HIGH);
    }
    if(out == 'e'){
      digitalWrite(Naprijed, HIGH);
    }
    if(out == 'f'){
      digitalWrite(Zaustavi, HIGH);
      digitalWrite(Naprijed, LOW);
      digitalWrite(Nazad, LOW);
    }
    if(out == 'g'){
      int val = map(value, 0, 100, 0, 255);
      analogWrite(dial_Kocenje, val);
    }
  
//  if (out == 'a'){
//    analogWrite(red_led, 255 - value);
//    Serial.print(value);
//    return;
//  }
//  
//  if (led == 'g'){
//    analogWrite(green_led, 255 - value);
//      Serial.print(brightness);
//    return;
//  }
//  if (led == 'b'){
//    analogWrite(blue_led, 255 - value);
//      Serial.print(brightness);
//    return;
//  }
  
  return;
}
