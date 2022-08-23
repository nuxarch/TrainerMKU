#include <Arduino.h>

#define S0_INPUT_PIN  49
#define S1_INPUT_PIN  48
#define S2_INPUT_PIN  47
#define S3_INPUT_PIN  46
#define S4_INPUT_PIN  45
#define S5_INPUT_PIN  44
#define S6_INPUT_PIN  43
#define S7_INPUT_PIN  42


class Switch
{
private:
  /* data */
public:
  uint8_t switch_data[8];
  Switch(){
    pinMode(S0_INPUT_PIN, INPUT_PULLUP);
    pinMode(S1_INPUT_PIN, INPUT_PULLUP);
    pinMode(S2_INPUT_PIN, INPUT_PULLUP);
    pinMode(S3_INPUT_PIN, INPUT_PULLUP);
    pinMode(S4_INPUT_PIN, INPUT_PULLUP);
    pinMode(S5_INPUT_PIN, INPUT_PULLUP);
    pinMode(S6_INPUT_PIN, INPUT_PULLUP);
    pinMode(S7_INPUT_PIN, INPUT_PULLUP);
  };
  ~Switch(){};
  void readSwitch(){
    (digitalRead(S0_INPUT_PIN)==LOW)?(switch_data[0]=0):(switch_data[0]=1);
    (digitalRead(S1_INPUT_PIN)==LOW)?(switch_data[1]=0):(switch_data[1]=1);
    (digitalRead(S2_INPUT_PIN)==LOW)?(switch_data[2]=0):(switch_data[2]=1);
    (digitalRead(S3_INPUT_PIN)==LOW)?(switch_data[3]=0):(switch_data[3]=1);
    (digitalRead(S4_INPUT_PIN)==LOW)?(switch_data[4]=0):(switch_data[4]=1);
    (digitalRead(S5_INPUT_PIN)==LOW)?(switch_data[5]=0):(switch_data[5]=1);
    (digitalRead(S6_INPUT_PIN)==LOW)?(switch_data[6]=0):(switch_data[6]=1);
    (digitalRead(S7_INPUT_PIN)==LOW)?(switch_data[7]=0):(switch_data[7]=1);
  }
  void debugSwitch(){
    readSwitch();
    for (int i = 0; i < 8; i++)
    {
        Serial.println("Switch "+String(i)+" State :["+switch_data[i]+"]");
    }
  }
};

#define LED_0_PIN  49
#define LED_1_PIN  48
#define LED_2_PIN  47
#define LED_3_PIN  46
#define LED_4_PIN  45
#define LED_5_PIN  44
#define LED_6_PIN  43
#define LED_7_PIN  42



class Barled
{
private:
public:
    Barled(){
        pinMode(LED_0_PIN, OUTPUT);
        pinMode(LED_1_PIN, OUTPUT);
        pinMode(LED_2_PIN, OUTPUT);
        pinMode(LED_3_PIN, OUTPUT);
        pinMode(LED_4_PIN, OUTPUT);
        pinMode(LED_5_PIN, OUTPUT);
        pinMode(LED_6_PIN, OUTPUT);
        pinMode(LED_7_PIN, OUTPUT);
    };
    ~Barled(){};
    void All_On(){
        digitalWrite(LED_0_PIN,HIGH);
        digitalWrite(LED_1_PIN,HIGH);
        digitalWrite(LED_2_PIN,HIGH);
        digitalWrite(LED_3_PIN,HIGH);
        digitalWrite(LED_4_PIN,HIGH);
        digitalWrite(LED_5_PIN,HIGH);
        digitalWrite(LED_6_PIN,HIGH);
        digitalWrite(LED_7_PIN,HIGH);
    }
    void All_Off(){
        digitalWrite(LED_0_PIN,LOW);
        digitalWrite(LED_1_PIN,LOW);
        digitalWrite(LED_2_PIN,LOW);
        digitalWrite(LED_3_PIN,LOW);
        digitalWrite(LED_4_PIN,LOW);
        digitalWrite(LED_5_PIN,LOW);
        digitalWrite(LED_6_PIN,LOW);
        digitalWrite(LED_7_PIN,LOW);
    }

};


