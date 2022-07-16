//
// Created by liga on 7/1/2022.
//

#ifndef HOTWHEELS_CSGO_EXTERNAL_CHEAT_HPP
#define HOTWHEELS_CSGO_EXTERNAL_CHEAT_HPP

#include <Windows.h>
#include <functional>
#include <iostream>

#include "../entry.hpp"

namespace cheat
{
	inline bool requested_shutdown{ };

	inline hmodule module_handle{ };
	inline std::uint64_t engine_dll{ };
	inline std::uint64_t client_dll{ };

	void init( );
} // namespace cheat

#endif // HOTWHEELS_CSGO_EXTERNAL_CHEAT_HPP
