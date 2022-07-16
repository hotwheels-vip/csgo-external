//
// Created by liga on 7/1/2022.
//

#include "cheat.hpp"

#include "features/overlay/overlay.hpp"
#include "helpers/configs/config.hpp"
#include "helpers/console/console.hpp"
#include "helpers/driver/driver.hpp"

#include "features/aimbot/aimbot.hpp"
#include "features/movement/movement.hpp"

#include "../dependencies/hash/hash.hpp"
#include "../dependencies/themida/include/ThemidaSDK.h"
#include "../entry.hpp"

#include <chrono>
#include <thread>

void cheat::init( )
{
	console::log( "" ); // Still on first line.

//	VM_EAGLE_BLACK_START

	g_config.init( );

	handle process_id{ };

	while ( !process_id ) {
		get_window_thread_process_id( find_window( "Valve001", nullptr ), reinterpret_cast< lpdword >( &process_id ) );

		if ( process_id )
			break;

		std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
	}

	std::this_thread::sleep_for( std::chrono::seconds( 1 ) );

	driver::init( reinterpret_cast< handle >( process_id ) );

	while ( true ) {
		if ( driver::base_address( _hash( "serverbrowser.dll" ) ) )
			break;

		std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
	}

	// Fuck off operations
	create_thread( overlay::init );
	create_thread( movement::routine );
	create_thread( aimbot::routine );

	while ( !get_async_key_state( VK_DELETE ) ) {
		std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
	}

//	VM_EAGLE_BLACK_END

	requested_shutdown = true;

	std::this_thread::sleep_for( std::chrono::seconds( 1 ) );

	free_library_and_exit_thread( cheat::module_handle, 0 );
}