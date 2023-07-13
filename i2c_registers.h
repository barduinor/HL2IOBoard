// These are the registers in the HL2 IO board Pico

#define GPIO_DIRECT_BASE	170	// map registers to GPIO pins for direct write
#define REG_TX_FREQ_BYTE4	0
#define REG_TX_FREQ_BYTE3	1
#define REG_TX_FREQ_BYTE2	2
#define REG_TX_FREQ_BYTE1	3
#define REG_FIRMWARE_MAJOR	4
#define REG_FIRMWARE_MINOR	5
#define REG_INPUT_PINS		6
#define REG_RF_INPUTS		11
#define REG_FAN_SPEED		12
#define REG_TX_FREQUENCY	13
#define REG_ANTENNA_TUNER	14
