//
// Created by liga on 7/3/2022.
//

#include <Windows.h>
#include <chrono>
#include <thread>

#include "movement.hpp"

#include "../../cheat.hpp"

#include "../../helpers/configs/config.hpp"
#include "../../helpers/console/console.hpp"
#include "../../helpers/driver/driver.hpp"

#include "../../../dependencies/hash/hash.hpp"
#include "../../../dependencies/themida/include/ThemidaSDK.h"
#include "../../../dependencies/xor/xor.hpp"

#include "../../sdk/enums/flags.hpp"
#include "../../sdk/enums/weapon_id.hpp"
#include "../../sdk/structs/game.hpp"
#include "../../sdk/structs/offsets.hpp"
#include "../../sdk/structs/vector.hpp"

void movement::routine( )
{
	VM_TIGER_WHITE_START

	while ( !cheat::requested_shutdown ) {
		if ( *g_config.find< bool >( _hash( "movement_bunny_hop" ) ) ) {
			if ( GetAsyncKeyState( VK_SPACE ) ) {
				auto luck  = rand( ) % 17 + 1; // Add 1 to prevent C0000094
				auto delay = *g_config.find< int >( _hash( "movement_bunny_hop_delay" ) ) % luck;

				auto player = sdk::game::local_player( );

				if ( !player )
					continue;

				auto flags = player->flags( );

				if ( flags & sdk::ONGROUND ) {
					if ( luck == 1 || !*g_config.find< bool >( _hash( "movement_bunny_hop_error" ) ) ) {
						driver::write< int >( reinterpret_cast< void* >( cheat::client_dll + offsets::force_jump ), 4 );

						sleep( 50 );

						continue;
					}

					std::this_thread::sleep_for( std::chrono::milliseconds( delay ) ); // themida fuckery sorry

					driver::write< int >( reinterpret_cast< void* >( cheat::client_dll + offsets::force_jump ), 6 );
				} else {
					driver::write< int >( reinterpret_cast< void* >( cheat::client_dll + offsets::force_jump ), 4 );
				}
			}
		}

		sleep( 1 );
	}

	VM_TIGER_WHITE_END
}