//
// Created by liga on 7/3/2022.
//

#include "../structs/player.hpp"
#include "../structs/game.hpp"
#include "../structs/offsets.hpp"

#include "../enums/bones.hpp"

#include "../../../dependencies/hash/hash.hpp"
#include "../../../dependencies/xor/xor.hpp"
#include "../../helpers/driver/driver.hpp"

#include "../../../dependencies/themida/include/ThemidaSDK.h"
#include "../../cheat.hpp"

int sdk::player::flags( )
{
	return driver::read< int >( this + offsets::flags );
}

sdk::vector sdk::player::aim_punch_angle( )
{
	return driver::read< sdk::vector >( this + offsets::aim_punch_angle );
}

int sdk::player::default_fov( )
{
	return driver::read< int >( this + offsets::default_fov );
}

sdk::collideable* sdk::player::collideable( )
{
	return reinterpret_cast< sdk::collideable* >( this + offsets::collision );
}

sdk::matrix_3x4 sdk::player::rgfl( )
{
	return driver::read< sdk::matrix_3x4 >( this + offsets::rgfl );
}

int sdk::player::team_id( )
{
	return driver::read< int >( this + offsets::team_num );
}

sdk::life_state sdk::player::life_state( )
{
	return static_cast< sdk::life_state >( driver::read< int >( this + offsets::life_state ) );
}

bool sdk::player::dormant( )
{
	return driver::read< bool >( this + offsets::dormant );
}

bool sdk::player::spotted_by_mask( )
{
	return driver::read< bool >( this + offsets::spotted_by_mask );
}

sdk::player_info sdk::player::player_info( )
{
	auto client_state = driver::read< std::uint32_t >( reinterpret_cast< PVOID >( cheat::engine_dll + offsets::client_state ) );
	auto user_info    = driver::read< std::uint32_t >( reinterpret_cast< PVOID >( client_state + offsets::client_state_player_info ) );
	auto items        = driver::read< std::uint32_t >(
        reinterpret_cast< PVOID >( driver::read< std::uint32_t >( reinterpret_cast< PVOID >( user_info + 0x40 ) ) + 0xC ) );

	return driver::read< sdk::player_info >(
		reinterpret_cast< PVOID >( driver::read< std::uint32_t >( reinterpret_cast< PVOID >( items + 0x28 + ( index( ) - 1 ) * 0x34 ) ) ) );
}

int sdk::player::index( )
{
	return driver::read< int >( this + offsets::entity_index );
}

int sdk::player::health( )
{
	return driver::read< int >( this + offsets::health );
}

std::string_view sdk::player::competitive_rank( )
{
	STR_ENCRYPT_START

	auto resource = driver::read< std::uint32_t >( reinterpret_cast< PVOID >( cheat::client_dll + offsets::player_resource ) );

	if ( !resource )
		return "Broken Rank";

	auto rank = driver::read< std::uint32_t >( reinterpret_cast< PVOID >( resource + offsets::competitive_ranking + ( index( ) * 0x4 ) ) );

	const char* rank_names[] = {
		"Unranked",
		"Silver I",
		"Silver II",
		"Silver III",
		"Silver IV",
		"Silver Elite",
		"Silver Elite Master",
		"Gold Nova I",
		"Gold Nova II",
		"Gold Nova III",
		"Gold Nova Master",
		"Master Guardian I",
		"Master Guardian II",
		"Master Guardian Elite",
		"Distinguished Master Guardian",
		"Legendary Eagle",
		"Legendary Eagle Master",
		"Supreme Master First Class",
		"The Global Elite",
	};

	if ( rank > 18 || rank < 0 )
		return "Broken Rank";

	STR_ENCRYPT_END

	return rank_names[ rank ];
}

int sdk::player::money( )
{
	return driver::read< int >( this + offsets::account );
}

sdk::weapon* sdk::player::get_weapon( int index )
{
	auto weapon_index = driver::read< int >( this + offsets::my_weapons + ( index * 0x4 ) ) & 0xFFF;

	return reinterpret_cast< sdk::weapon* >( sdk::game::get_entity( weapon_index - 1 ) );
}

sdk::weapon* sdk::player::get_weapon( )
{
	auto weapon_index = driver::read< int >( this + offsets::active_weapon ) & 0xFFF;

	return reinterpret_cast< sdk::weapon* >( sdk::game::get_entity( weapon_index - 1 ) );
}

bool sdk::player::visible( )
{
	auto local_player = sdk::game::local_player( );

	if ( !local_player )
		return false;

	auto local_player_origin   = local_player->origin( );
	auto local_player_position = local_player_origin + local_player->shoot_position( );

	auto player_position        = origin( ) + shoot_position( );
	auto player_position_head   = player_position + this->bone_position( bone_head );
	auto player_position_pelvis = player_position + this->bone_position( bone_pelvis );

	rn::vector3 translated_position_local  = { local_player_position.x, local_player_position.y, local_player_position.z };
	rn::vector3 translated_position_head   = { player_position_head.x, player_position_head.y, player_position_head.z };
	rn::vector3 translated_position_pelvis = { player_position_pelvis.x, player_position_pelvis.y, player_position_pelvis.z };

	return cheat::bsp_parser.is_visible( translated_position_local, translated_position_pelvis ) ||
	       cheat::bsp_parser.is_visible( translated_position_local, translated_position_head );
}

sdk::vector sdk::player::bone_position( int bone_index )
{
	auto bone_matrix = driver::read< sdk::matrix_3x4 >( this + offsets::bone_matrix + ( bone_index * 0x30 ) );

	return bone_matrix.to_vector( 3 );
}

sdk::vector sdk::player::shoot_position( )
{
	auto shoot_position = driver::read< sdk::vector >( this + offsets::view_offset );

	return shoot_position;
}

sdk::vector sdk::player::origin( )
{
	auto origin = driver::read< sdk::vector >( this + offsets::origin );

	return origin;
}
