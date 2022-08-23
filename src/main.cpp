#include <Arduino.h>
#include <Shell.h>
#include "DirectIO.h"
#include "LiquidCrystal_I2C.h"
#include "LedControlMS.h"
#include "AccelStepper.h"
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define DATA_PIN 13
#define CLK_PIN 12
#define CS_PIN 11

MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
OutputPort<PORT_A> port;
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
AccelStepper stepper(AccelStepper::FULL4WIRE, 42, 43, 44, 45);

int shell_reader(char *data)
{
  if (Serial.available())
  {
    *data = Serial.read();
    return 1;
  }
  return 0;
}
void shell_writer(char data)
{
  // Wrapper for Serial.write() method
  Serial.write(data);
}
int command_led(int argc, char **argv)
{
  int i;

  shell_println("-----------------------------------------------");
  shell_println("SHELL DEBUG / TEST UTILITY");
  shell_println("-----------------------------------------------");
  shell_println("");
  shell_printf("Received %d arguments for test command\r\n", argc);

  for (i = 0; i < argc; i++)
  {
    shell_printf("%d - \"%s\" [len:%d]\r\n", i, argv[i], strlen(argv[i]));
  }
  for (i = 0; i < argc; i++)
  {
    if (i == 0)
      continue;
    if (!strcmp(argv[i], "-help"))
    {
      return SHELL_RET_SUCCESS;
    }
    else if (!strcmp(argv[i], (const char *)"bright"))
    {
      uint8_t val_bright, pwm_pin;
      val_bright = strtol(argv[3], NULL, 0);
      pwm_pin = strtol(argv[2], NULL, 0);
      Serial.println("pin: " + String(pwm_pin) + ", pwm :" + String(val_bright));
      pinMode(pwm_pin, OUTPUT);
      analogWrite(pwm_pin, val_bright);

      return SHELL_RET_SUCCESS;
    }
    else if (!strcmp(argv[i], (const char *)"on"))
    {
      uint8_t val_led_numb;
      val_led_numb = strtol(argv[2], NULL, 0);
      digitalWrite(val_led_numb, HIGH);

      return SHELL_RET_SUCCESS;
    }
    else if (!strcmp(argv[i], (const char *)"right"))
    {
      uint8_t a = 0x80;
      for (int i = 0; i < 9; i++)
      {
        PORTA = a >> i;
        delay(100);
      }
      return SHELL_RET_SUCCESS;
    }
    else if (!strcmp(argv[i], (const char *)"left"))
    {
      uint8_t a = 0x01;
      for (int i = 0; i < 9; i++)
      {
        PORTA = a << i;
        delay(100);
      }
      return SHELL_RET_SUCCESS;
    }
    else if (!strcmp(argv[i], (const char *)"rotate"))
    {
      uint8_t val_delay;
      val_delay = strtol(argv[2], NULL, 0);

      for (uint8_t i = 0; i < 10; i++)
      {

        uint8_t a = 0x01;
        for (int i = 0; i < 9; i++)
        {
          PORTA = a << i;
          delay(val_delay);
        }
        a = 0x80;
        for (int i = 0; i < 9; i++)
        {
          PORTA = a >> i;
          delay(val_delay);
        }
      }
      return SHELL_RET_SUCCESS;
    }
  }
  // return SHELL_RET_SUCCESS;
}
int command_lcd(int argc, char **argv)
{
  int i;

  shell_println("-----------------------------------------------");
  shell_println("SHELL DEBUG / TEST UTILITY");
  shell_println("-----------------------------------------------");
  shell_println("");
  shell_printf("Received %d arguments for test command\r\n", argc);

  for (i = 0; i < argc; i++)
  {
    shell_printf("%d - \"%s\" [len:%d]\r\n", i, argv[i], strlen(argv[i]));
  }
  for (i = 0; i < argc; i++)
  {
    if (i == 0)
      continue;
    if (!strcmp(argv[i], "-help"))
    {
      return SHELL_RET_SUCCESS;
    }
    else if (!strcmp(argv[i], (const char *)"print"))
    {
      uint8_t line_pos;
      line_pos = strtol(argv[2], NULL, 0);

      lcd.setCursor(0, line_pos);
      lcd.print("                   ");
      lcd.setCursor(0, line_pos);
      lcd.print(String(argv[3]));

      return SHELL_RET_SUCCESS;
    }
  }
  // return SHELL_RET_SUCCESS;
}
int command_pot(int argc, char **argv)
{
  int i;

  shell_println("-----------------------------------------------");
  shell_println("SHELL DEBUG / TEST UTILITY");
  shell_println("-----------------------------------------------");
  shell_println("");
  shell_printf("Received %d arguments for test command\r\n", argc);

  for (i = 0; i < argc; i++)
  {
    shell_printf("%d - \"%s\" [len:%d]\r\n", i, argv[i], strlen(argv[i]));
  }
  for (i = 0; i < argc; i++)
  {
    if (i == 0)
      continue;
    if (!strcmp(argv[i], "-help"))
    {
      shell_print("pot read 54(A0)->61(A7)");
      return SHELL_RET_SUCCESS;
    }
    else if (!strcmp(argv[i], (const char *)"read"))
    {
      uint8_t pot_number = A0;
      pot_number = strtol(argv[2], NULL, 0);
      while (analogRead(pot_number) < 1000)
      {
        // Serial.println("Pot. " + String(pot_number) + ": " + String(analogRead(pot_number)));
        Serial.println("Pot[" + String(pot_number) + "]: " + map(analogRead(pot_number), 0, 1023, 0, 100));
        lcd.setCursor(0, 1);
        lcd.print("Pot[" + String(pot_number) + "]: " + map(analogRead(pot_number), 0, 1023, 0, 100));
      }
      return SHELL_RET_SUCCESS;
    }
  }
  // return SHELL_RET_SUCCESS;
}
int command_matrix(int argc, char **argv)
{
  int i;
  long x = 0;
  shell_println("-----------------------------------------------");
  shell_println("SHELL DEBUG / TEST UTILITY");
  shell_println("-----------------------------------------------");
  shell_println("");
  shell_printf("Received %d arguments for test command\r\n", argc);

  for (i = 0; i < argc; i++)
  {
    shell_printf("%d - \"%s\" [len:%d]\r\n", i, argv[i], strlen(argv[i]));
  }
  for (i = 0; i < argc; i++)
  {
    if (i == 0)
      continue;
    if (!strcmp(argv[i], "-help"))
    {
      shell_println("-----------------------------------------------");
      shell_println("Matrix control command");
      shell_println("-----------------------------------------------");
      shell_println("matrix [message]");
      shell_println("ex: matrix HELLOWORLD");

      return SHELL_RET_SUCCESS;
    }
    else if (!strcmp(argv[i], (const char *)"print"))
    {
      shell_println("Matrix print command");
      P.begin();
      while (x < 100000)
      {
        if (P.displayAnimate())
        {
          // P.displayText("POLI", PA_CENTER, P.getSpeed(), P.getPause(), PA_SCROLL_DOWN, PA_SCROLL_UP);
          P.displayScroll(argv[2], PA_CENTER, PA_SCROLL_RIGHT, 200);
          P.setZoneEffect(0, true, PA_FLIP_LR);
          P.setZoneEffect(0, true, PA_FLIP_UD);
        }
        ++x;
      }
      return SHELL_RET_SUCCESS;
    }
  }
  // return SHELL_RET_SUCCESS;
}

int command_stepper(int argc, char **argv)
{
  int i;
  shell_println("-----------------------------------------------");
  shell_println("SHELL DEBUG / TEST UTILITY");
  shell_println("-----------------------------------------------");
  shell_println("");
  shell_printf("Received %d arguments for test command\r\n", argc);

  for (i = 0; i < argc; i++)
  {
    shell_printf("%d - \"%s\" [len:%d]\r\n", i, argv[i], strlen(argv[i]));
  }
  for (i = 0; i < argc; i++)
  {
    if (i == 0)
      continue;
    if (!strcmp(argv[i], "-help"))
    {
      shell_println("-----------------------------------------------");
      shell_println("Stepper control command");
      shell_println("-----------------------------------------------");
      shell_println("stepper go [angle]");
      shell_println("ex: stepper go 100");

      return SHELL_RET_SUCCESS;
    }
    else if (!strcmp(argv[i], (const char *)"go "))
    {
      shell_println("Stepper print command");

      uint8_t angle_val;
      angle_val = strtol(argv[2], NULL, 0);
      stepper.moveTo(100);

      return SHELL_RET_SUCCESS;
    }
  }
  // return SHELL_RET_SUCCESS;
}

void setup()
{
  Serial.begin(115200);
  delay(1000);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("===Trainer Ready====");
  P.begin();
  stepper.setMaxSpeed(100);
  stepper.setAcceleration(100);

  shell_init(shell_reader, shell_writer, 0);
  shell_register(command_led, PSTR("led"));
  shell_register(command_lcd, PSTR("lcd"));
  shell_register(command_pot, PSTR("pot"));
  shell_register(command_matrix, PSTR("matrix"));
  shell_register(command_stepper, PSTR("stepper"));
  // shell_register(command_lcd, PSTR(""));
}

void loop()
{
  shell_task();
}
