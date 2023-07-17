/*
 * modbusSlave.h
 *
 *  Created on: Oct 27, 2022
 *      Author: controllerstech.com
 */

#ifndef INC_MODBUSSLAVE_H_
#define INC_MODBUSSLAVE_H_

#include "modbus_crc.h"
#include "hw.h"
#include "hw_def.h"

#define SLAVE_ID               HW_SLAVE_ID

#define ILLEGAL_FUNCTION       HW_ILLEGAL_FUNCTION
#define ILLEGAL_DATA_ADDRESS   HW_ILLEGAL_DATA_ADDRESS
#define ILLEGAL_DATA_VALUE     HW_ILLEGAL_DATA_VALUE


bool ModbusInit(void);

uint8_t readHoldingRegs (uint16_t* Holding_Registers_Database);
uint8_t readInputRegs (uint16_t* Input_Registers_Database);
uint8_t writeSingleReg (uint16_t* Holding_Registers_Database);

/*
 * DISABLE
uint8_t readCoils (void);
uint8_t readInputs (void);
uint8_t writeHoldingRegs (void);
*/



void modbusException (uint8_t exceptioncode);

#endif /* INC_MODBUSSLAVE_H_ */




