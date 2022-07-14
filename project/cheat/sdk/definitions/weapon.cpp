//
// Created by liga on 7/9/2022.
//

#include "../structs/weapon.hpp"
#include "../enums/weapon_id.hpp"
#include "../structs/game.hpp"
#include "../structs/offsets.hpp"

#include "../../helpers/driver/driver.hpp"

short sdk::weapon::weapon_id( )
{
	return driver::read< short >( this + offsets::item_definition_index );
}

void sdk::weapon::set_item_id( int id )
{
	driver::write< int >( this + offsets::item_id_high, id );
}

void sdk::weapon::set_fallback_paint_kit( int kit )
{
	driver::write< int >( this + offsets::fallback_paint_kit, kit );
}

void sdk::weapon::set_fallback_seed( int seed )
{
	driver::write< int >( this + offsets::fallback_seed, seed );
}

void sdk::weapon::set_fallback_wear( float wear )
{
	driver::write< float >( this + offsets::fallback_wear, wear );
}

void sdk::weapon::set_fallback_stat_trak( int stat_trak )
{
	auto player_info = game::local_player( )->player_info( );

	driver::write< int >( this + offsets::account_id, player_info.xuidlow );
	driver::write< int >( this + offsets::fallback_stat_trak, stat_trak );
}

void sdk::weapon::set_quality( int quality )
{
	driver::write< int >( this + offsets::entity_quality, quality );
}

bool sdk::weapon::is_pistol( )
{
	auto weapon_id = this->weapon_id( );

	return weapon_id == weapon_deagle || weapon_id == weapon_elite || weapon_id == weapon_fiveseven || weapon_id == weapon_glock ||
	       weapon_id == weapon_tec9 || weapon_id == weapon_hkp2000 || weapon_id == weapon_usp_silencer || weapon_id == weapon_cz75a ||
	       weapon_id == weapon_revolver || weapon_id == weapon_p250;
}

bool sdk::weapon::is_rifle( )
{
	auto weapon_id = this->weapon_id( );

	return weapon_id == weapon_ak47 || weapon_id == weapon_m4a1 || weapon_id == weapon_m4a1_silencer || weapon_id == weapon_galilar ||
	       weapon_id == weapon_famas || weapon_id == weapon_aug || weapon_id == weapon_sg556;
}

bool sdk::weapon::is_sniper( )
{
	auto weapon_id = this->weapon_id( );

	return weapon_id == weapon_awp || weapon_id == weapon_scar20 || weapon_id == weapon_g3sg1 || weapon_id == weapon_ssg08;
}

bool sdk::weapon::is_smg( )
{
	auto weapon_id = this->weapon_id( );

	return weapon_id == weapon_mac10 || weapon_id == weapon_mp7 || weapon_id == weapon_mp9 || weapon_id == weapon_p90 || weapon_id == weapon_bizon ||
	       weapon_id == weapon_ump45 || weapon_id == weapon_mp5;
}

bool sdk::weapon::is_shotgun( )
{
	auto weapon_id = this->weapon_id( );

	return weapon_id == weapon_xm1014 || weapon_id == weapon_nova || weapon_id == weapon_sawedoff || weapon_id == weapon_mag7;
}

bool sdk::weapon::is_lmg( )
{
	auto weapon_id = this->weapon_id( );

	return weapon_id == weapon_negev || weapon_id == weapon_m249;
}