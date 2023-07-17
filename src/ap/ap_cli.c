/*
 * ap_cli.c
 *
 *  Created on: 2023. 7. 10.
 *      Author: KIMMINJI
 */

#include "ap_cli.h"

uint16_t* Holding_Reg;


bool cli_uartInit(uint16_t* Holding_Registers_Database)
{
  bool ret = true;
  Holding_Reg = Holding_Registers_Database;
  cliAdd("uart", cli_uart);

  return ret;
}

void cli_uart(cli_args_t *args)
{
  bool ret = false;
  uint32_t uart_baudrate;

  cliPrintf("uart baudrate\n");

  if (args->argc == 1)
  {
    uart_baudrate = (uint32_t)args->getData(0);

    Holding_Reg[1] = (uint16_t)(uart_baudrate >>16);
    Holding_Reg[2] = (uint16_t)(uart_baudrate & 0xffff);

    ret = true;
  }

  if (ret != true)
  {
    cliPrintf("uart baudrate\n");
  }
}


