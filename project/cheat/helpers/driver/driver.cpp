//
// Created by liga on 7/2/2022.
//

#include "driver.hpp"
#include "driver_binary.hpp"
#include "../../../dependencies/kdmapper/kdmapper.hpp"

#include <iostream>

bool driver::init( HANDLE pid )
{
	auto intel_driver_handle = intel_driver::Load( );

	if ( !intel_driver_handle ) {
		std::cout << "Failed to load Intel driver!" << std::endl;
		return false;
	}

	NTSTATUS exit_code{ };

	kdmapper::MapDriver( intel_driver_handle, driver_binary, 0, 0, false, true, false, false, nullptr, &exit_code );

	if ( !NT_SUCCESS( exit_code ) ) {
		std::cout << "Failed to map driver!" << std::endl;

		intel_driver::Unload( intel_driver_handle );

		return false;
	}

	intel_driver::Unload( intel_driver_handle );

	if ( !device_handle ) {
		device_handle = CreateFile( "\\\\.\\hotwheels", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

		if ( device_handle == INVALID_HANDLE_VALUE ) {
			std::cout << "Driver failure. 0x" << std::hex << GetLastError( ) << std::endl;
		} else {
			std::cout << "Driver success." << std::endl;
		}
	}

	process_pid = pid;

	return true;
}

bool driver::shutdown( )
{
	if ( device_handle != INVALID_HANDLE_VALUE ) {
		CloseHandle( device_handle );
		device_handle = INVALID_HANDLE_VALUE;
	}

	return true;
}