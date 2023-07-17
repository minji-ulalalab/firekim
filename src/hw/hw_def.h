/*
 * hw_def.h
 *
 *  Created on: Jun 23, 2023
 *      Author: KIMMINJI
 */

#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_


#include "def.h"
#include "bsp.h"


#define _USE_HW_LED
#define      HW_LED_MAX_CH        1

#define _USE_HW_UART
#define      HW_UART_MAX_CH       1

#define _USE_HW_BUTTON
#define      HW_BUTTON_MAX_CH     1

#define _USE_HW_FLASH

#define _USE_HW_CLI
#define      HW_CLI_CMD_NAME_MAX    16
#define      HW_CLI_CMD_LIST_MAX    16
#define      HW_CLI_LINE_HIS_MAX  4
#define      HW_CLI_LINE_BUF_MAX  32

#define HW_SLAVE_ID               1

#define HW_ILLEGAL_FUNCTION       0x01
#define HW_ILLEGAL_DATA_ADDRESS   0x02
#define HW_ILLEGAL_DATA_VALUE     0x03

#define _MODBUS_FLASH_ADDR       0x0800F000
#define _SLAVE_ID_FLASH_ADDR     0x800F000              //size -> uint16_t(2byte)
#define _BAUDRATE_HH_FLASH_ADDR  0x800F000 + 0x00000002 //size -> uint16_t(2byte)
#define _BAUDRATE_LL_FLASH_ADDR  0x800F000 + 0x00000004 //size -> uint16_t(2byte)
#define _DATABIT_FLASH_ADDR      0x800F000 + 0x00000006 //size -> uint16_t(2byte)
#define _PARITY_FLASH_ADDR       0x800F000 + 0x00000008 //size -> uint16_t(2byte)
#define _STOPBIT_FLASH_ADDR      0x800F000 + 0x0000000A //size -> uint16_t(2byte)
#define _FLOWCTL_FLASH_ADDR      0x800F000 + 0x0000000C //size -> uint16_t(2byte)
#define _CLI_MODE_FLASH_ADDR     0x800F000 + 0x0000000E //size -> uint16_t(2byte)



/*
 * DISABLE NOW

static uint8_t Coils_Database[25]={
    0b01001001, 0b10011100, 0b10101010, 0b01010101, 0b11001100,    // 0-39    1-40
    0b10100011, 0b01100110, 0b10101111, 0b01100000, 0b10111100,    // 40-79   41-80
    0b11001100, 0b01101100, 0b01010011, 0b11111111, 0b00000000,    // 80-119  81-120
    0b01010101, 0b00111100, 0b00001111, 0b11110000, 0b10001111,    // 120-159 121-160
    0b01010100, 0b10011001, 0b11111000, 0b00001101, 0b00101010,    // 160-199 161-200
};

static const uint8_t Inputs_Database[25]={
    0b01001001, 0b10011100, 0b10101010, 0b01010101, 0b11001100,    // 0-39    10001-10040
    0b10100011, 0b01100110, 0b10101111, 0b01100000, 0b10111100,    // 40-79   10041-10080
    0b11001100, 0b01101100, 0b01010011, 0b11111111, 0b00000000,    // 80-119  10081-10120
    0b01010101, 0b00111100, 0b00001111, 0b11110000, 0b10001111,    // 120-159 10121-10160
    0b01010100, 0b10011001, 0b11111000, 0b00001101, 0b00101010,    // 160-199 10161-10200
};

*/

#endif /* SRC_HW_HW_DEF_H_ */
