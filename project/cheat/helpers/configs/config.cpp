//
// Created by liga on 7/2/2022.
//

#include "config.hpp"
#include "../../../dependencies/themida/include/ThemidaSDK.h"
#include "../../features/grenades/grenades.hpp"
#include "../console/console.hpp"

#include <ShlObj.h>
#include <Windows.h>
#include <fstream>

void config::impl::save( std::string path )
{
	STR_ENCRYPT_START

	using namespace nlohmann;

	json reader;

	for ( auto& setting : settings ) {
		switch ( setting.second.type ) {
		case variable_type::VARIABLE_BOOL:
			reader[ std::to_string( setting.first ) ] = setting.second.bool_value;
			break;
		case variable_type::VARIABLE_INT:
			reader[ std::to_string( setting.first ) ] = setting.second.int_value;
			break;

		case variable_type::VARIABLE_FLOAT:
			reader[ std::to_string( setting.first ) ] = setting.second.float_value;
			break;

		case variable_type::VARIABLE_COLOR:
			reader[ std::to_string( setting.first ) ] = { setting.second.color_value.x, setting.second.color_value.y, setting.second.color_value.z,
				                                          setting.second.color_value.w };
			break;

		case variable_type::VARIABLE_STRING:
			reader[ std::to_string( setting.first ) ] = setting.second.string_value;
			break;
		}
	}

	std::ofstream stream( path );

	stream << std::setw( 4 ) << reader << std::endl;

	stream.close( );

	std::string file_name = path.substr( path.find_last_of( "\\/" ) + 1 );

	console::log< fmt::color::light_pink >( "[CONFIG] Saved config to {}", file_name );

	STR_ENCRYPT_END
}

void config::impl::load( std::string path )
{
	STR_ENCRYPT_START

	using namespace nlohmann;

	json reader{ };

	std::ifstream stream( path );

	if ( !stream )
		return;

	stream >> reader;

	stream.close( );

	for ( auto& setting : settings ) {
		if ( !reader.contains( std::to_string( setting.first ) ) )
			continue;

		switch ( setting.second.type ) {
		case variable_type::VARIABLE_BOOL:
			setting.second.bool_value = reader[ std::to_string( setting.first ) ];
			break;
		case variable_type::VARIABLE_INT:
			setting.second.int_value = reader[ std::to_string( setting.first ) ];
			break;

		case variable_type::VARIABLE_FLOAT:
			setting.second.float_value = reader[ std::to_string( setting.first ) ];
			break;

		case variable_type::VARIABLE_COLOR:
			setting.second.color_value.x = reader[ std::to_string( setting.first ) ][ 0 ];
			setting.second.color_value.y = reader[ std::to_string( setting.first ) ][ 1 ];
			setting.second.color_value.z = reader[ std::to_string( setting.first ) ][ 2 ];
			setting.second.color_value.w = reader[ std::to_string( setting.first ) ][ 3 ];

			break;

		case variable_type::VARIABLE_STRING:
			setting.second.string_value = reader[ std::to_string( setting.first ) ];

			break;
		}
	}

	std::string file_name = path.substr( path.find_last_of( "\\/" ) + 1 );

	console::log< fmt::color::light_pink >( "[CONFIG] Loaded config from {}", file_name );

	STR_ENCRYPT_END
}

void config::impl::insert( std::uint32_t hash, option _option )
{
	settings.insert( std::make_pair( hash, _option ) );
}

void config::impl::init( )
{
	insert( _hash( "menu_open_smooth" ), true );

	insert( _hash( "aimbot_rcs" ), false );
	insert( _hash( "aimbot_rcs_x" ), 100.f );
	insert( _hash( "aimbot_rcs_y" ), 100.f );
	insert( _hash( "aimbot_rcs_smooth" ), 0.f );
	insert( _hash( "aimbot_rcs_error" ), true );

	insert( _hash( "visuals_visible" ), false );
	insert( _hash( "visuals_boxes" ), false );
	insert( _hash( "visuals_boxes_color" ), ImVec4( 1.f, 1.f, 1.f, 1.f ) );
	insert( _hash( "visuals_names" ), false );
	insert( _hash( "visuals_names_color" ), ImVec4( 1.f, 1.f, 1.f, 1.f ) );
	insert( _hash( "visuals_weapons" ), false );
	insert( _hash( "visuals_weapons_icons" ), false );
	insert( _hash( "visuals_weapons_color" ), ImVec4( 1.f, 1.f, 1.f, 1.f ) );
	insert( _hash( "visuals_health_bars" ), false );
	insert( _hash( "visuals_health_bars_color" ), ImVec4( 0.f, 1.f, 0.f, 1.f ) );
	insert( _hash( "visuals_skeletons" ), false );
	insert( _hash( "visuals_skeletons_color" ), ImVec4( 1.f, 1.f, 1.f, 1.f ) );

	insert( _hash( "visuals_bomb_timer" ), false );
	insert( _hash( "visuals_recoil_crosshair" ), false );
	insert( _hash( "visuals_recoil_crosshair_color" ), ImVec4( 1.f, 1.f, 1.f, 1.f ) );

	insert( _hash( "movement_bunny_hop" ), false );
	insert( _hash( "movement_bunny_hop_delay" ), 0 );
	insert( _hash( "movement_bunny_hop_error" ), false );

	static CHAR my_documents[ MAX_PATH ]{ };
	static HRESULT result = get_folder_path( nullptr, CSIDL_PERSONAL, nullptr, SHGFP_TYPE_CURRENT, my_documents );

	using namespace nlohmann;

	json reader{ };

	std::ifstream stream( "C:\\Users\\liga\\Documents\\hotwheels\\default.nades" );

	if ( !stream )
		return;

	stream >> reader;

	stream.close( );

	for ( auto& grenade : reader[ "GRENADES" ] ) {
		grenades::grenade_info grenade_info{ };

		grenade_info.name     = grenade[ "name" ];
		grenade_info.angle    = { grenade[ "pitch" ].get< float >( ), grenade[ "yaw" ].get< float >( ) };
		grenade_info.position = { grenade[ "x" ].get< float >( ), grenade[ "y" ].get< float >( ), grenade[ "z" ].get< float >( ) - 65.f };

		grenades::grenade_list[ grenade[ "map" ] ][ grenade[ "grenade_type" ] ].push_back( grenade_info );

		console::log< fmt::color::light_pink >( "[CONFIG] Loaded grenade {}", grenade_info.name );
	}
}
