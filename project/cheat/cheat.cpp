//
// Created by liga on 7/1/2022.
//

#include "cheat.hpp"

#include "sdk/structs/offsets.hpp"

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
	VM_EAGLE_BLACK_START

	console::log( "" ); // Still on first line.

	g_config.init( );

	handle process_id{ };

	while ( !process_id ) {
		get_window_thread_process_id( find_window( "Valve001", nullptr ), reinterpret_cast< lpdword >( &process_id ) );

		if ( process_id )
			break;

		sleep( 1000 );
	}

	window_handle = find_window( "Valve001", nullptr );

	sleep( 1000 );

	driver::init( reinterpret_cast< handle >( process_id ) );

	while ( true ) {
		if ( driver::base_address( _hash( "serverbrowser.dll" ) ) )
			break;

		sleep( 1000 );
	}

	client_dll = driver::base_address( _hash( "client.dll" ) );
	engine_dll = driver::base_address( _hash( "engine.dll" ) );

	std::thread thread_overlay( &overlay::init );
	std::thread thread_aimbot( &aimbot::routine );
	std::thread thread_movement( &movement::routine );

	while ( !get_async_key_state( VK_DELETE ) ) {
		static auto client_state          = driver::read< std::uint32_t >( reinterpret_cast< PVOID >( engine_dll + offsets::client_state ) );
		static std::string last_directory = { };

		char read_map[ 128 ]{ };
		char read_directory[ 128 ]{ };

		driver::read( reinterpret_cast< PVOID >( client_state + offsets::client_state_map_directory ), &read_map, 128 );
		driver::read( reinterpret_cast< PVOID >( engine_dll + offsets::game_dir ), &read_directory, 128 );

		if ( last_directory.find( read_map ) == std::string::npos ) {
			std::thread thread_bsp( &rn::bsp_parser::load_map, &bsp_parser, read_directory, read_map );
			thread_bsp.join( );

			last_directory = read_map;

			std::string file_name = last_directory.substr( last_directory.find_last_of( "\\/" ) + 1 );

			console::log< fmt::color::light_pink >( "[BSP] Map loaded {}", file_name );
		}

		sleep( 1 );
	}

	requested_shutdown = true;

	VM_EAGLE_BLACK_END

	free_library_and_exit_thread( cheat::module_handle, 0 );
}