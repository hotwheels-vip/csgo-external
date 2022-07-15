//
// Created by liga on 7/3/2022.
//

#include <Windows.h>
#include <chrono>
#include <thread>

#include "movement.hpp"

#include "../../cheat.hpp"
#include "../../helpers/configs/config.hpp"
#include "../../helpers/driver/driver.hpp"
#include "../../sdk/enums/flags.hpp"
#include "../../sdk/structs/game.hpp"
#include "../../sdk/structs/offsets.hpp"
#include "../../sdk/structs/vector.hpp"

#include "../../../dependencies/hash/hash.hpp"
#include "../../../dependencies/xor/xor.hpp"

void movement::routine( )
{
	static auto client_dll    = driver::base_address( __( "client.dll" ) );
	static auto engine_dll    = driver::base_address( __( "engine.dll" ) );
	static auto window_handle = FindWindowA( _( "Valve001" ), nullptr );

	srand( time( nullptr ) );

	while ( !cheat::requested_shutdown ) {
		if ( *g_config.find< bool >( __( "movement_bunny_hop" ) ) ) {
			if ( GetAsyncKeyState( VK_SPACE ) && GetForegroundWindow( ) == window_handle ) {
				auto luck  = rand( ) % 17 + 1; // Add 1 to prevent C0000094
				auto delay = *g_config.find< int >( __( "movement_bunny_hop_delay" ) ) % luck;

				auto player = sdk::game::local_player( );

				if ( !player )
					continue;

				auto flags = player->flags( );

				if ( flags & sdk::ONGROUND ) {
					if ( luck == 1 || !*g_config.find< bool >( __( "movement_bunny_hop_error" ) ) ) {
						driver::write< int >( reinterpret_cast< void* >( client_dll + offsets::force_jump ), 4 );

						std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );

						continue;
					}

					std::this_thread::sleep_for( std::chrono::milliseconds( delay ) );

					driver::write< int >( reinterpret_cast< void* >( client_dll + offsets::force_jump ), 6 );
				} else {
					driver::write< int >( reinterpret_cast< void* >( client_dll + offsets::force_jump ), 4 );
				}
			}
		}

		std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
	}
}