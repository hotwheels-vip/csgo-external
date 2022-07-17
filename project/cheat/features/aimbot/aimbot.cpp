//
// Created by liga on 7/5/2022.
//

#include "aimbot.hpp"

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

void aimbot::routine( )
{
	static sdk::vector last_aim_punch{ };

	while ( !cheat::requested_shutdown ) {
		auto player = sdk::game::local_player( );

		if ( !player )
			continue;

		auto current_weapon = player->get_weapon( );

		if ( !current_weapon )
			continue;

		auto client_state = driver::read< std::uint32_t >( reinterpret_cast< void* >( cheat::engine_dll + offsets::client_state ) );
		auto view_angles  = driver::read< sdk::vector >( reinterpret_cast< PVOID >( client_state + offsets::client_state_view_angles ) );
		auto aim_punch    = player->aim_punch_angle( );

		sdk::vector adjusted_angles = { aim_punch.x * ( *g_config.find< float >( _hash( "aimbot_rcs_y" ) ) / 100.f ),
			                            aim_punch.y * ( *g_config.find< float >( _hash( "aimbot_rcs_x" ) ) / 100.f ) };

		if ( GetAsyncKeyState( VK_LBUTTON ) ) {
			auto random_x = static_cast< float >( rand( ) + 1 % 10 );
			auto random_y = static_cast< float >( rand( ) + 1 % 10 ) - 5.f;

			sdk::vector random_angles = { random_x / 100.f, random_y / 100.f };

			if ( aim_punch.is_zero( ) )
				random_angles = { 0.f, 0.f };

			if ( *g_config.find< bool >( _hash( "aimbot_rcs" ) ) ) {
				if ( current_weapon->is_pistol( ) || current_weapon->is_sniper( ) || current_weapon->is_shotgun( ) ||
				     current_weapon->weapon_id( ) == sdk::weapon_negev ) // Although there are those fully auto snipers, who really uses them
					continue;

				auto corrected_angle = view_angles - ( adjusted_angles * 2 - last_aim_punch ) +
				                       ( *g_config.find< bool >( _hash( "aimbot_rcs_error" ) ) ? random_angles : sdk::vector{ } );

				auto lerped_angle = view_angles.lerp( corrected_angle, -( *g_config.find< float >( _hash( "aimbot_rcs_smooth" ) ) / 100.f ) + 1.f );

				driver::write< sdk::vector >( reinterpret_cast< PVOID >( client_state + offsets::client_state_view_angles ),
				                              lerped_angle.clamped( ) );
			}
		}

		last_aim_punch = adjusted_angles * 2;

		sleep( 1 );
	}
}