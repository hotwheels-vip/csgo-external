//
// Created by liga on 7/3/2022.
//

#include "../structs/game.hpp"
#include "../structs/offsets.hpp"

#include "../../helpers/driver/driver.hpp"

sdk::player* sdk::game::local_player( )
{
	static auto engine_dll = driver::base_address( "engine.dll" );
	auto client_state      = driver::read< std::uint32_t >( reinterpret_cast< PVOID >( engine_dll + offsets::client_state ) );

	return get_entity( driver::read< unsigned int >( reinterpret_cast< PVOID >( client_state + offsets::client_state_get_local_player ) ) );
}

sdk::player* sdk::game::get_entity( int index )
{
	static auto client_dll = driver::base_address( "client.dll" );

	return reinterpret_cast< player* >(
		driver::read< std::uint32_t >( reinterpret_cast< PVOID >( client_dll + offsets::entity_list + ( 0x10 * index ) ) ) );
}
