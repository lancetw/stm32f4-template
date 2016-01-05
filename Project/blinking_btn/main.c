/**
  Exercise 4.2 Blinking Lights with Pushbutton (STM32F4 version)
  ref: www.cs.indiana.edu/~geobrown/book.pdf
**/

#include "stm32f4_discovery.h"
#include "main.h"

#define ORANGE LED3_PIN
#define GREEN  LED4_PIN
#define RED    LED5_PIN
#define BLUE   LED6_PIN

#define ALL_LEDS (GREEN | ORANGE | RED | BLUE)

#define LEDS_GPIO_PORT (GPIOD)

#define BUTTON_PIN  USER_BUTTON_PIN
#define BUTTON_GPIO_PORT  (GPIOA)

#define PAUSE_LONG  1000  /* 1s */
#define PAUSE_SHORT 120   /* 120ms */
#define PAUSE_FLASH 240   /* 240ms */

static uint16_t leds[LEDn] = { GREEN, ORANGE, RED, BLUE };

static void setup()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);

  /* LEDs */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  GPIO_InitStructure.GPIO_Pin = ALL_LEDS;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_Init(LEDS_GPIO_PORT, &GPIO_InitStructure);

  /* Blue Button */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = BUTTON_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_Init(BUTTON_GPIO_PORT, &GPIO_InitStructure);
}

static void loop()
{
  GPIO_ResetBits(LEDS_GPIO_PORT, ALL_LEDS);
  Delay(PAUSE_LONG);
  GPIO_SetBits(LEDS_GPIO_PORT, GREEN);
  Delay(PAUSE_LONG);
  GPIO_SetBits(LEDS_GPIO_PORT, ORANGE);
  Delay(PAUSE_LONG);
  GPIO_SetBits(LEDS_GPIO_PORT, RED);
  Delay(PAUSE_LONG);
  GPIO_SetBits(LEDS_GPIO_PORT, BLUE);
  Delay(PAUSE_LONG);

  GPIO_ResetBits(LEDS_GPIO_PORT, ALL_LEDS);
  Delay(PAUSE_FLASH);
  GPIO_SetBits(LEDS_GPIO_PORT, ALL_LEDS);
  Delay(PAUSE_FLASH);
  GPIO_ResetBits(LEDS_GPIO_PORT, ALL_LEDS);
  Delay(PAUSE_FLASH);
  GPIO_SetBits(LEDS_GPIO_PORT, ALL_LEDS);
  Delay(PAUSE_FLASH);
  GPIO_ResetBits(LEDS_GPIO_PORT, ALL_LEDS);
  Delay(PAUSE_FLASH);
  GPIO_ResetBits(LEDS_GPIO_PORT, ALL_LEDS);

  uint8_t status = 0;
  uint8_t next = 0;
  uint8_t prev = LEDn - 1;

  while (1) {
    status = GPIO_ReadInputDataBit(BUTTON_GPIO_PORT, BUTTON_PIN);

    if (status) {
      GPIO_ResetBits(LEDS_GPIO_PORT, leds[prev]);
      GPIO_SetBits(LEDS_GPIO_PORT, leds[next]);
      prev = next++;
      next = next % LEDn;
    }

    Delay(PAUSE_SHORT);
  }
}
