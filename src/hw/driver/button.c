/*
 * button.c
 *
 *  Created on: Jun 24, 2023
 *      Author: KIMMINJI
 */


#include "button.h"

typedef struct
{
  GPIO_TypeDef *port;
  uint16_t      pin;
} button_tbl_t;


button_tbl_t button_tbl[BUTTON_MAX_CH] =
    {
        {GPIOA, GPIO_PIN_0},
    };


bool buttonInit(void)
{
  bool ret = true;


  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin : PA0 */
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;

  for (int i = 0; i<BUTTON_MAX_CH; i++)
  {
    GPIO_InitStruct.Pin = button_tbl[i].pin;
    HAL_GPIO_Init(button_tbl[i].port, &GPIO_InitStruct);
  }

  return ret;

}

GPIO_PinState buttonStateCheck(uint8_t ch)
{
  if (ch >= BUTTON_MAX_CH) return;
  GPIO_PinState state = HAL_GPIO_ReadPin(button_tbl[ch].port, button_tbl[ch].pin);

  return state;
}








