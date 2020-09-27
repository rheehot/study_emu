//
// Created by nhy20 on 2020-09-27.
//
#include "../GameboyCPU.h"


void GameboyCPU::bitTest(BYTE op_code)
{
	BYTE bit_position = ( op_code & 0b00111000u ) >> 3u;
	BYTE reg_value = get8BitArgumentValue(  op_code & 0b00000111u );

	BYTE result = (reg_value & (0b1u << bit_position)) >> bit_position;

	setFlagZ( result == 0 );
	setFlagH( true );
	setFlagN( false );
}