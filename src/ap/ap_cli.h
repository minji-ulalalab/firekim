/*
 * ap_cli.h
 *
 *  Created on: 2023. 7. 10.
 *      Author: KIMMINJI
 */

#ifndef SRC_AP_AP_CLI_H_
#define SRC_AP_AP_CLI_H_

#include "cli.h"
#include "hw_def.h"
#include "uart.h"

bool cli_uartInit(uint16_t* Holding_Registers_Database);
void cli_uart(cli_args_t *args);

#endif /* SRC_AP_AP_CLI_H_ */
