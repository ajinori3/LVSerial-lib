#ifndef LVSERIAL_H_
#define LVSERIAL_H_

#include "Arduino.h"

class LVSerial
{
public:
	enum class ErrorStatus
	{
		OK,
		TIMED_OUT,
		INVALID_COMMAND,
		DATA_DAMAGED
	};
	enum class RegName
	{
		SYS_PN,
		SYS_VER,
		SYS_UID,
		SYS_SID,
		SYS_RST,
		SYS_BR,
		SYS_T0,
		SYS_RID,
		SYS_PCT,
		SYS_DCT,
		SYS_ECT,
		SYS_ULK,
		PWM_PSN,
		PWM_PSA,
		PWM_SST,
		PWM_SLP,
		PWM_PSO,
		M_POS,
		M_SPD,
		M_VE,
		M_TEMP,
		M_VI,
		M_IERR,
		FB_TPOS,
		FB_PG,
		FB_DG,
		FB_EG,
		FB_IG,
		FB_ILIM,
		FB_PDB,
		FB_DDB,
		FB_EDB,
		PWM_EN,
		PWM_LIM,
		PWM_PCH,
		PWM_OUT,
		AL_TEMP,
		SD_TEMP,
		AL_VI,
		SD_VI,
		VIB_OTH,
		VIB_STH,
		BST_DUM,
		BST_LEN,
		BST_SYN,
		BST_WA0,
		BST_WA1,
		BST_WA2,
		BST_WA3,
		BST_WA4,
		BST_WA5,
		BST_WA6,
		BST_WA7,
		BST_RA0,
		BST_RA1,
		BST_RA2,
		BST_RA3,
		BST_RA4,
		BST_RA5,
		BST_RA6,
		BST_RA7
	};
	
	explicit LVSerial(HardwareSerial &serial);
	LVSerial(HardwareSerial &serial, const long baud);
	
	ErrorStatus readRAM(const RegName reg, uint8_t* const read_buff, const size_t buff_size);
	ErrorStatus writeRAM(const RegName reg, uint8_t* const write_buff, const size_t buff_size);
	
	ErrorStatus init();
	ErrorStatus init(const uint8_t servo_id);
	
	ErrorStatus isConnected();
	ErrorStatus releaseWriteProtection(const bool do_enable);
	ErrorStatus doEnableServoPower(const bool is_enable);
	ErrorStatus writeTargetPos(const uint16_t raw_pos);
	ErrorStatus readPowerVoltage(float* const voltage_f);
	ErrorStatus readNowPos(uint16_t* const raw_pos);
	ErrorStatus readBackEMF(float* const voltage_f);
	ErrorStatus readNowSpeed(uint16_t* const raw_pos_speed);
	
	
private:
	HardwareSerial *serial_;
	uint8_t servo_id_;
	
	typedef struct RegElement_t
	{
		int address;
		int size;
		bool is_writeable;
	} RegElement_t;
	
	RegElement_t getRegisterSpecification(const RegName);		
	ErrorStatus transmitReceiveToRAM(const RegName reg, uint8_t* const write_data, uint8_t* const read_data, const size_t buff_size, const bool is_write);
};

#endif // !LVSERIAL_H_