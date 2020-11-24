//
// Created by HaruGakkaP on 2020-11-23.
//

#include "Cartridge.h"
#include <fstream>
#include <algorithm>

void Cartridge::Load(std::string_view path)
{
	std::fstream file( path.data(), std::fstream::binary | std::fstream::in );
	if( !file.is_open() ) { throw std::logic_error("NO FILE");}

	std::vector<char> buffer( (std::istreambuf_iterator<char>( file )), std::istreambuf_iterator<char>()  );
	if( buffer.empty() ) { throw std::logic_error("NO DATA"); }
	// 검증

	// 버퍼
	mBuffer = std::move( buffer );
}

std::string Cartridge::GetTitle()
{
	if( mBuffer.empty() ) { throw std::logic_error("Cartridge Not INITED."); }

	const size_t TITLE_START_POINT = 0x134;
	const size_t TITLE_END_POINT = 0x143;

	if( mBuffer.size() < TITLE_END_POINT ) { throw std::logic_error("NOT VALID CARTRIDGE."); }

	std::string name = std::string( &mBuffer[TITLE_START_POINT], &mBuffer[TITLE_END_POINT] );

	// Null 문자 제거
	name.erase( std::remove_if( name.begin(), name.end(), []( unsigned char c ) -> bool {
		return c == '\x00';
	} ), name.end() );

	return name;
}