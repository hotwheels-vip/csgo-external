//
// Created by liga on 7/2/2022.
//

#include "driver.hpp"
#include "driver_binary.hpp"

#include "../../../entry.hpp"

#include "../../../dependencies/kdmapper/kdmapper.hpp"
#include "../../../dependencies/themida/include/ThemidaSDK.h"

#include "../console/console.hpp"

#include <iostream>

bool driver::init( HANDLE pid )
{
	VM_EAGLE_BLACK_START

	auto intel_driver_handle = intel_driver::Load( );

	if ( !intel_driver_handle ) {
		console::log< fmt::color::red >( "[KDMAPPER] Failed to load Intel driver!" );

		return false;
	}

	console::log< fmt::color::light_blue >( "[KDMAPPER] Loaded Intel driver." );

	NTSTATUS exit_code{ };

	kdmapper::MapDriver( intel_driver_handle, driver_binary, 0, 0, false, true, false, false, nullptr, &exit_code );

	if ( !NT_SUCCESS( exit_code ) ) {
		console::log< fmt::color::red >( "[KDMAPPER] Failed to map driver! Error: {}", exit_code );

		intel_driver::Unload( intel_driver_handle );

		return false;
	}

	console::log< fmt::color::light_blue >( "[KDMAPPER] Mapped driver." );

	if ( !intel_driver::Unload( intel_driver_handle ) ) {
		console::log< fmt::color::red >( "[KDMAPPER] Failed to unload Intel driver!" );

		return false;
	}

	console::log< fmt::color::light_blue >( "[KDMAPPER] Unloaded Intel driver." );

	if ( !device_handle ) {
		device_handle = create_file( "\\\\.\\hotwheels", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

		if ( device_handle == INVALID_HANDLE_VALUE ) {
			console::log< fmt::color::red >( "[LOG] Failed to open device! Error: {}", GetLastError( ) );
		}

		console::log< fmt::color::light_pink >( "[LOG] Successfully opened device!" );
	}

	process_pid = pid;

	VM_EAGLE_BLACK_END

	return true;
}