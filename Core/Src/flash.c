#include "flash.h"

void flash_print_info() {
	flash_print_id();
	flash_print_status_register();
	flash_print_nonvolatile_configuration_register();
	flash_print_volatile_configuration_register();
	flash_print_enhanced_volatile_configuration_register();
	flash_print_flag_status_register();
}

void flash_print_id() {
	QSPI_CommandTypeDef flash_cmd;
	uint8_t data_rcv[3];
	flash_cmd.InstructionMode   	= QSPI_INSTRUCTION_1_LINE;
	flash_cmd.Instruction			= CMD_READ_ID;
	flash_cmd.AddressMode			= QSPI_ADDRESS_NONE;
	flash_cmd.AlternateByteMode		= QSPI_ALTERNATE_BYTES_NONE;
	flash_cmd.DataMode         		= QSPI_DATA_1_LINE;
	flash_cmd.DummyCycles      		= 0;
	flash_cmd.Address          		= 0;
	flash_cmd.DdrMode				= QSPI_DDR_MODE_DISABLE;
	flash_cmd.SIOOMode				= QSPI_SIOO_INST_EVERY_CMD;
	flash_cmd.NbData				= 3;
	HAL_QSPI_Command(&hqspi, &flash_cmd, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
	HAL_QSPI_Receive(&hqspi, data_rcv, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
	printf("\r\n");
	printf("FLASH -> Manufacturer ID: 0x%x \r\n",data_rcv[0]);
	printf("      -> Memory type: 0x%x \r\n",data_rcv[1]);
	printf("      -> Memory capacity: 0x%x \r\n",data_rcv[2]);
}

void flash_print_status_register() {
	QSPI_CommandTypeDef flash_cmd;
	uint8_t data_rcv[1];
	flash_cmd.InstructionMode   	= QSPI_INSTRUCTION_1_LINE;
	flash_cmd.Instruction			= CMD_READ_STATUS_REGISTER;
	flash_cmd.AddressMode			= QSPI_ADDRESS_NONE;
	flash_cmd.AlternateByteMode		= QSPI_ALTERNATE_BYTES_NONE;
	flash_cmd.DataMode         		= QSPI_DATA_1_LINE;
	flash_cmd.DummyCycles      		= 0;
	flash_cmd.Address          		= 0;
	flash_cmd.DdrMode				= QSPI_DDR_MODE_DISABLE;
	flash_cmd.SIOOMode				= QSPI_SIOO_INST_EVERY_CMD;
	flash_cmd.NbData				= 1;
	HAL_QSPI_Command(&hqspi, &flash_cmd, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
	HAL_QSPI_Receive(&hqspi, data_rcv, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
	printf("\r\n");
	printf("FLASH -> Status register: 0x%x \r\n",data_rcv[0]);
	if(data_rcv[0] & 0b10000000)
		printf("      -> Status register write: Disabled \r\n");
	else
		printf("      -> Status register write: Enabled \r\n");
	if(data_rcv[0] & 0b00100000)
		printf("      -> Block protect 3–0: Bottom \r\n");
	else
		printf("      -> Block protect 3–0: Top \r\n");
	if(data_rcv[0] & 0b01011100)
		printf("      -> Block protect 3–0: Set\r\n");
	else
		printf("      -> Block protect 3–0: None\r\n");
	if(data_rcv[0] & 0b00000010)
		printf("      -> Write enable latch: Set \r\n");
	else
		printf("      -> Write enable latch: Cleared (default) \r\n");
	if(data_rcv[0] & 0b00000001)
		printf("      -> Write in progress: Busy \r\n");
	else
		printf("      -> Write in progress: Ready \r\n");
}

void flash_print_nonvolatile_configuration_register() {
	QSPI_CommandTypeDef flash_cmd;
	uint8_t data_rcv[2];
	flash_cmd.InstructionMode   	= QSPI_INSTRUCTION_1_LINE;
	flash_cmd.Instruction			= CMD_READ_NONVOLATILE_CONFIGURATION_REGISTER;
	flash_cmd.AddressMode			= QSPI_ADDRESS_NONE;
	flash_cmd.AlternateByteMode		= QSPI_ALTERNATE_BYTES_NONE;
	flash_cmd.DataMode         		= QSPI_DATA_1_LINE;
	flash_cmd.DummyCycles      		= 0;
	flash_cmd.Address          		= 0;
	flash_cmd.DdrMode				= QSPI_DDR_MODE_DISABLE;
	flash_cmd.SIOOMode				= QSPI_SIOO_INST_EVERY_CMD;
	flash_cmd.NbData				= 2;
	HAL_QSPI_Command(&hqspi, &flash_cmd, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
	HAL_QSPI_Receive(&hqspi, data_rcv, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
	printf("\r\n");
	printf("FLASH -> Nonvolatile configuration register: 0x%x%x \r\n", data_rcv[1], data_rcv[0]);
	printf("      -> Number of dummy clock cycles: 0x%x\r\n", (data_rcv[1] & 0b11110000) >> 4);
	printf("      -> XIP mode at power-on reset: 0x%x\r\n", (data_rcv[1] & 0b00001110) >> 1);
	printf("      -> Output driver strength: 0x%x\r\n", (data_rcv[1] & 0b00000001) << 2 | (data_rcv[0] & 0b11000000) >> 6);
	if(data_rcv[0] & 0b00010000)
		printf("      -> Reset/hold: Enabled (default)\r\n");
	else
		printf("      -> Reset/hold: Disabled\r\n");
	if(data_rcv[0] & 0b00001000)
		printf("      -> Quad I/O protocol: Disabled (default)\r\n");
	else
		printf("      -> Quad I/O protocol: Enabled\r\n");
	if(data_rcv[0] & 0b00000100)
		printf("      -> Dual I/O protocol: Disabled (default)\r\n");
	else
		printf("      -> Dual I/O protocol: Enabled\r\n");
	if(data_rcv[0] & 0b00000001)
		printf("      -> Lock nonvolatile configuration register: Enabled (default)\r\n");
	else
		printf("      -> Lock nonvolatile configuration register: Disabled\r\n");
}

void flash_print_volatile_configuration_register() {
	QSPI_CommandTypeDef flash_cmd;
	uint8_t data_rcv[1];
	flash_cmd.InstructionMode   	= QSPI_INSTRUCTION_1_LINE;
	flash_cmd.Instruction			= CMD_READ_VOLATILE_CONFIGURATION_REGISTER;
	flash_cmd.AddressMode			= QSPI_ADDRESS_NONE;
	flash_cmd.AlternateByteMode		= QSPI_ALTERNATE_BYTES_NONE;
	flash_cmd.DataMode         		= QSPI_DATA_1_LINE;
	flash_cmd.DummyCycles      		= 0;
	flash_cmd.Address          		= 0;
	flash_cmd.DdrMode				= QSPI_DDR_MODE_DISABLE;
	flash_cmd.SIOOMode				= QSPI_SIOO_INST_EVERY_CMD;
	flash_cmd.NbData				= 1;
	HAL_QSPI_Command(&hqspi, &flash_cmd, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
	HAL_QSPI_Receive(&hqspi, data_rcv, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
	printf("\r\n");
	printf("FLASH -> Volatile configuration register: 0x%x \r\n", data_rcv[0]);
	printf("      -> Number of dummy clock cycles: 0x%x\r\n", (data_rcv[0] & 0b11110000) >> 4);
	if(data_rcv[0] & 0b00001000)
		printf("      -> XIP: Disabled\r\n");
	else
		printf("      -> XIP: Enabled\r\n");
	printf("      -> Wrap: 0x%x (default 0x3)\r\n", data_rcv[0] & 0b00000011);
}

void flash_print_enhanced_volatile_configuration_register() {
	QSPI_CommandTypeDef flash_cmd;
	uint8_t data_rcv[1];
	flash_cmd.InstructionMode   	= QSPI_INSTRUCTION_1_LINE;
	flash_cmd.Instruction			= CMD_READ_ENHANCED_VOLATILE_CONFIGURATION_REGISTER;
	flash_cmd.AddressMode			= QSPI_ADDRESS_NONE;
	flash_cmd.AlternateByteMode		= QSPI_ALTERNATE_BYTES_NONE;
	flash_cmd.DataMode         		= QSPI_DATA_1_LINE;
	flash_cmd.DummyCycles      		= 0;
	flash_cmd.Address          		= 0;
	flash_cmd.DdrMode				= QSPI_DDR_MODE_DISABLE;
	flash_cmd.SIOOMode				= QSPI_SIOO_INST_EVERY_CMD;
	flash_cmd.NbData				= 1;
	HAL_QSPI_Command(&hqspi, &flash_cmd, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
	HAL_QSPI_Receive(&hqspi, data_rcv, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
	printf("\r\n");
	printf("FLASH -> Enhanced volatile configuration register: 0x%x \r\n", data_rcv[0]);
	if(data_rcv[0] & 0b10000000)
		printf("      -> Quad I/O protocol: Disabled (default)\r\n");
	else
		printf("      -> Quad I/O protocol: Enabled\r\n");
	if(data_rcv[0] & 0b01000000)
		printf("      -> Dual I/O protocol: Disabled (default)\r\n");
	else
		printf("      -> Dual I/O protocol: Enabled\r\n");
	if(data_rcv[0] & 0b00010000)
		printf("      -> Reset/hold: Enabled (default)\r\n");
	else
		printf("      -> Reset/hold: Disabled\r\n");
	if(data_rcv[0] & 0b00001000)
		printf("      -> VPP accelerator: Disabled (default)\r\n");
	else
		printf("      -> VPP accelerator: Enabled\r\n");
	printf("      -> Output driver strength: 0x%x \r\n", data_rcv[0] & 0b00000111);
}

void flash_print_flag_status_register() {
	QSPI_CommandTypeDef flash_cmd;
	uint8_t data_rcv[1];
	flash_cmd.InstructionMode   	= QSPI_INSTRUCTION_1_LINE;
	flash_cmd.Instruction			= CMD_READ_FLAG_STATUS_REGISTER;
	flash_cmd.AddressMode			= QSPI_ADDRESS_NONE;
	flash_cmd.AlternateByteMode		= QSPI_ALTERNATE_BYTES_NONE;
	flash_cmd.DataMode         		= QSPI_DATA_1_LINE;
	flash_cmd.DummyCycles      		= 0;
	flash_cmd.Address          		= 0;
	flash_cmd.DdrMode				= QSPI_DDR_MODE_DISABLE;
	flash_cmd.SIOOMode				= QSPI_SIOO_INST_EVERY_CMD;
	flash_cmd.NbData				= 1;
	HAL_QSPI_Command(&hqspi, &flash_cmd, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
	HAL_QSPI_Receive(&hqspi, data_rcv, HAL_QSPI_TIMEOUT_DEFAULT_VALUE);
	printf("\r\n");
	printf("FLASH -> Flag status register: 0x%x \r\n", data_rcv[0]);
	if(data_rcv[0] & 0b10000000)
		printf("      -> Program or erase controller: Ready\r\n");
	else
		printf("      -> Program or erase controller: Busy\r\n");
	if(data_rcv[0] & 0b01000000)
		printf("      -> Erase suspend: In effect\r\n");
	else
		printf("      -> Erase suspend: Not in effect\r\n");
	if(data_rcv[0] & 0b00100000)
		printf("      -> Erase: Failure or protection error\r\n");
	else
		printf("      -> Erase: Clear\r\n");
	if(data_rcv[0] & 0b00010000)
		printf("      -> Program: Failure or protection error\r\n");
	else
		printf("      -> Program: Clear\r\n");
	if(data_rcv[0] & 0b00001000)
		printf("      -> VPP: Disabled (default)\r\n");
	else
		printf("      -> VPP: Enabled\r\n");
	if(data_rcv[0] & 0b00000100)
		printf("      -> Program suspend: In effect\r\n");
	else
		printf("      -> Program suspend: Not in effect\r\n");
	if(data_rcv[0] & 0b00000010)
		printf("      -> Protection: Failure or protection error\r\n");
	else
		printf("      -> Protection: Clear\r\n");
}
