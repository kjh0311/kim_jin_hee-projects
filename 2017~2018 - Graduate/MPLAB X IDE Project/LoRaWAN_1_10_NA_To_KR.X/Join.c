/*
 * File:   Join.c
 * Author: 김진희
 *
 * Created on 2018년 5월 1일 (화), 오후 3:36
 */


#include "mcc_generated_files/mcc.h"


void JoinABP()
{
	/*
	static uint32_t	devAddr = 0x2604127E;
	static uint8_t
		nwkSKey[16] = { 0xFF, 0xDC, 0x72, 0xB1, 0x50, 0x03, 0xD9, 0x71, 0x00, 0x46, 0x91, 0x66, 0x0E, 0xFC, 0xF5, 0xF2 },
		appSKey[16] = { 0x5A, 0xEB, 0xB0, 0x61, 0x5D, 0xD2, 0x95, 0x1B, 0x69, 0x8C, 0x7D, 0x7C, 0xEE, 0x34, 0xFE, 0xFE };
	*/
	static uint32_t	devAddr = 0x00000000;
	static uint8_t
		nwkSKey[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		appSKey[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	
	LORAWAN_SetNetworkSessionKey(nwkSKey);
	LORAWAN_SetApplicationSessionKey(appSKey);
	LORAWAN_SetDeviceAddress(devAddr);
	
	LORAWAN_Join(ABP);
}


void JoinOTAA()
{
	static uint8_t
		devEui[8] = { 0x00, 0x25, 0x35, 0xF4, 0xF5, 0x87, 0x98, 0x29 },
		appEui[8] = { 0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x00, 0xC2, 0x19 };
//		appKey[16] = { 0x1D, 0x44, 0x36, 0x2A, 0x7A, 0x0B, 0x24, 0x96,
//					   0x26, 0xC6, 0xA9, 0xE2, 0xBD, 0xF9, 0x5C, 0x28 };
	
	LORAWAN_SetDeviceEui(devEui);
	LORAWAN_SetApplicationEui(appEui);
	//LORAWAN_SetApplicationKey(appKey);
	
	//LORAWAN_Join(OTAA);
}
