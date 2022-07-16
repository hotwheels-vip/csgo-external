#ifndef HOTWHEELS_CSGO_EXTERNAL_CONSOLE_HPP
#define HOTWHEELS_CSGO_EXTERNAL_CONSOLE_HPP

#include "../../../dependencies/fmt/color.h"
#include "../../../dependencies/fmt/core.h"

#include "../../../dependencies/themida/include/ThemidaSDK.h"
#include "../../../dependencies/xor/xor.hpp"

#include <Windows.h>
#include <iostream>
#include <string>

namespace console
{
	template< fmt::color COLOR = fmt::color::white_smoke, typename... ARGS >
	void log( fmt::string_view message, ARGS&&... arguments )
	{
		HANDLE std_handle = GetStdHandle( STD_OUTPUT_HANDLE );
		DWORD mode        = 0;
		GetConsoleMode( std_handle, &mode );
		mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode( std_handle, mode );

		std::string formatted_string = fmt::vformat( message, fmt::make_format_args( arguments... ) );

		fmt::print( fmt::fg( COLOR ), formatted_string + '\n' );
	}
} // namespace console

#endif // HOTWHEELS_CSGO_EXTERNAL_CONSOLE_HPP
