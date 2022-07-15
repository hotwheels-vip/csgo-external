//
// Created by liga on 7/7/2022.
//

#include "menu.hpp"

#include <Windows.h>
#include <filesystem>
#include <iostream>

#include <ShlObj.h>

#include "../../../dependencies/hash/hash.hpp"
#include "../../../dependencies/imgui/imgui.h"
#include "../../../dependencies/xor/xor.hpp"
#include "../../helpers/configs/config.hpp"
#include "../../helpers/console/console.hpp"
#include "../../helpers/driver/driver.hpp"
#include "../../sdk/structs/game.hpp"
#include "../../sdk/structs/offsets.hpp"

void menu::routine( float ease_animation )
{
#ifdef _DEBUG
	ImGui::ShowDemoWindow( );
#endif

	float current_position{ };

	ImGui::SetNextWindowSize( ImVec2( 175, 0 ) );
	ImGui::SetNextWindowPos( ImVec2( 10.f + ( 5.f + 175.f ) * current_position++ * ease_animation, 10 ) );
	if ( ImGui::Begin( _( "Aimbot" ), nullptr, ImGuiWindowFlags_AlwaysAutoResize ) ) {
		ImGui::Checkbox( _( "RCS" ), g_config.find< bool >( __( "aimbot_rcs" ) ) );

		if ( *g_config.find< bool >( __( "aimbot_rcs" ) ) ) {
			ImGui::PushItemWidth( -1 );
			ImGui::SliderFloat( _( "##RCS X" ), g_config.find< float >( __( "aimbot_rcs_x" ) ), 0, 150.f, _( "X: %0.1f%" ) );
			ImGui::SliderFloat( _( "##RCS Y" ), g_config.find< float >( __( "aimbot_rcs_y" ) ), 0, 150.f, _( "Y: %0.1f%" ) );
			ImGui::SliderFloat( _( "##RCS SMOOTH" ), g_config.find< float >( __( "aimbot_rcs_smooth" ) ), 0, 2.f, _( "Smooth: %0.1f%" ) );

			ImGui::PopItemWidth( );

			ImGui::Checkbox( _( "RCS Error" ), g_config.find< bool >( __( "aimbot_rcs_error" ) ) );
		}

		ImGui::End( );
	}

	ImGui::SetNextWindowSize( ImVec2( 175, 0 ) );
	ImGui::SetNextWindowPos( ImVec2( 10.f + ( 5.f + 175.f ) * current_position++ * ease_animation, 10 ) );
	if ( ImGui::Begin( _( "Visuals" ), nullptr, ImGuiWindowFlags_AlwaysAutoResize ) ) {
		ImGui::Checkbox( _( "Boxes" ), g_config.find< bool >( __( "visuals_boxes" ) ) );
		ImGui::SameLine( );

		ImGui::ColorEdit4( _( "##Boxes Color" ), reinterpret_cast< float* >( g_config.find< ImVec4 >( __( "visuals_boxes_color" ) ) ),
		                   ImGuiColorEditFlags_NoInputs );

		ImGui::Checkbox( _( "Names" ), g_config.find< bool >( __( "visuals_names" ) ) );
		ImGui::SameLine( );

		ImGui::ColorEdit4( _( "##Names Color" ), reinterpret_cast< float* >( g_config.find< ImVec4 >( __( "visuals_names_color" ) ) ),
		                   ImGuiColorEditFlags_NoInputs );

		ImGui::Checkbox( _( "Weapons" ), g_config.find< bool >( __( "visuals_weapons" ) ) );
		ImGui::SameLine( );

		ImGui::ColorEdit4( _( "##Weapons Color" ), reinterpret_cast< float* >( g_config.find< ImVec4 >( __( "visuals_weapons_color" ) ) ),
		                   ImGuiColorEditFlags_NoInputs );

		ImGui::Checkbox( _( "Weapon Icons" ), g_config.find< bool >( __( "visuals_weapons_icons" ) ) );

		ImGui::Checkbox( _( "Health Bars" ), g_config.find< bool >( __( "visuals_health_bars" ) ) );
		ImGui::SameLine( );

		ImGui::ColorEdit4( _( "##Health Bars Color" ), reinterpret_cast< float* >( g_config.find< ImVec4 >( __( "visuals_health_bars_color" ) ) ),
		                   ImGuiColorEditFlags_NoInputs );

		ImGui::Checkbox( _( "Recoil Crosshair" ), g_config.find< bool >( __( "visuals_recoil_crosshair" ) ) );
		ImGui::SameLine( );

		ImGui::ColorEdit4( _( "##Recoil Crosshair Color" ),
		                   reinterpret_cast< float* >( g_config.find< ImVec4 >( __( "visuals_recoil_crosshair_color" ) ) ),
		                   ImGuiColorEditFlags_NoInputs );

		ImGui::End( );
	}

	ImGui::SetNextWindowSize( ImVec2( 175, 0 ) );
	ImGui::SetNextWindowPos( ImVec2( 10.f + ( 5.f + 175.f ) * current_position++ * ease_animation, 10 ) );
	if ( ImGui::Begin( _( "Movement" ), nullptr, ImGuiWindowFlags_AlwaysAutoResize ) ) {
		ImGui::Checkbox( _( "Bunny Hop" ), g_config.find< bool >( __( "movement_bunny_hop" ) ) );

		if ( *g_config.find< bool >( __( "movement_bunny_hop" ) ) ) {
			ImGui::PushItemWidth( -1 );
			ImGui::SliderInt( _( "##Bhop Delay" ), g_config.find< int >( __( "movement_bunny_hop_delay" ) ), 0, 100, _( "Delay: %dms" ) );
			ImGui::PopItemWidth( );

			if ( ImGui::IsItemHovered( ) ) {
				ImGui::SetTooltip( _( "Delay is randomized" ) );
			}

			ImGui::Checkbox( _( "Bunny Hop Error" ), g_config.find< bool >( __( "movement_bunny_hop_error" ) ) );
		}

		ImGui::End( );
	}

	ImGui::SetNextWindowSize( ImVec2( 175, 0 ) );
	ImGui::SetNextWindowPos( ImVec2( 10.f + ( 5.f + 175.f ) * current_position++ * ease_animation, 10 ) );
	if ( ImGui::Begin( _( "Misc" ), nullptr, ImGuiWindowFlags_AlwaysAutoResize ) ) {
		ImGui::Checkbox( _( "Smooth Open" ), g_config.find< bool >( __( "menu_open_smooth" ) ) );
		if ( ImGui::Button( _( "Force Full Update" ) ) ) {
			static auto engine_dll = driver::base_address( __( "engine.dll" ) );

			auto client_state = driver::read< std::uint32_t >( reinterpret_cast< PVOID >( engine_dll + offsets::client_state ) );

			driver::write< int >( reinterpret_cast< PVOID >( client_state + offsets::clientstate_delta_ticks ), -1 );
		}

		ImGui::End( );
	}

	ImGui::SetNextWindowSize( ImVec2( 175, 0 ) );
	ImGui::SetNextWindowPos( ImVec2( 10.f + ( 5.f + 175.f ) * current_position++ * ease_animation, 10 ) );
	if ( ImGui::Begin( _( "Configs" ), nullptr, ImGuiWindowFlags_AlwaysAutoResize ) ) {
		static CHAR my_documents[ MAX_PATH ]{ };
		static HRESULT result = SHGetFolderPath( nullptr, CSIDL_PERSONAL, nullptr, SHGFP_TYPE_CURRENT, my_documents );

		if ( result == S_OK ) {
			static std::string config_name{ };

			if ( ImGui::BeginListBox( _( "##Configs" ), ImVec2( 158, 75 ) ) ) {
				if ( ImGui::BeginPopupContextWindow( _( "##Configs Context" ) ) ) {
					static char config_name[ 64 ]{ };

					ImGui::PushItemWidth( 150 );
					ImGui::InputText( _( "##Configs Name" ), config_name, 64 );
					ImGui::PopItemWidth( );

					if ( ImGui::Button( _( "Create" ), ImVec2( 150, 0 ) ) ) {
						std::string config_path{ my_documents };
						config_path += _( "\\hotwheels\\" );
						config_path += config_name;
						config_path += _( ".vip" );

						if ( !std::filesystem::exists( config_path ) ) {
							console::log< fmt::color::light_pink >( _( "[CONFIG] Created config {}.vip" ), config_name );

							g_config.save( config_path );

							ImGui::CloseCurrentPopup( );
						}
					}

					ImGui::EndPopup( );
				}

				std::string config_path{ my_documents };

				config_path += _( "\\hotwheels\\" );

				std::filesystem::directory_iterator end{ };

				for ( std::filesystem::directory_iterator it{ config_path }; it != end; ++it ) {
					if ( std::filesystem::is_regular_file( it->status( ) ) ) {
						std::string file_name{ it->path( ).filename( ).string( ) };

						bool selected = config_name == file_name;

						if ( ImGui::Selectable( file_name.c_str( ), selected ) ) {
							config_name = file_name;
						}

						if ( ImGui::BeginPopupContextItem( ( std::string( _( "##Configs Popup " ) ) + file_name ).c_str( ) ) ) {
							if ( ImGui::Button( ( std::string( _( "Delete " ) ) + file_name ).c_str( ) ) ) {
								console::log< fmt::color::light_pink >( _( "[CONFIG] Deleted config {}" ), file_name );

								std::filesystem::remove( it->path( ) );
								ImGui::CloseCurrentPopup( );
							}

							ImGui::EndPopup( );
						}
					}
				}

				ImGui::EndListBox( );
			}

			if ( ImGui::Button( _( "Save" ), ImVec2( ImGui::GetWindowSize( ).x * 0.43f, 0 ) ) ) {
				g_config.save( std::string( my_documents ) + _( "/hotwheels/" ) + config_name );
			}
			ImGui::SameLine( );
			if ( ImGui::Button( _( "Load" ), ImVec2( ImGui::GetWindowSize( ).x * 0.43f, 0 ) ) ) {
				g_config.load( std::string( my_documents ) + _( "/hotwheels/" ) + config_name );
			}
		}

		ImGui::End( );
	}

	ImGui::SetNextWindowSize( ImVec2( 500, 0 ) );
	ImGui::SetNextWindowPos( ImVec2( 10.f + ( 5.f + 175.f ) * current_position++ * ease_animation, 10 ) );
	if ( ImGui::Begin( _( "Players" ), nullptr, ImGuiWindowFlags_AlwaysAutoResize ) ) {
		std::vector< sdk::player* > players_team{ };
		std::vector< sdk::player* > players_enemies{ };

		for ( auto index = 0; index < 64; index++ ) {
			auto player = sdk::game::get_entity( index );

			if ( player ) {
				auto team = player->team_id( );

				auto local_player = sdk::game::local_player( );

				if ( !local_player )
					continue;

				if ( !player->player_info( ).name )
					continue;

				if ( player->competitive_rank( ).empty( ) )
					continue;

				if ( team == local_player->team_id( ) ) {
					players_team.push_back( player );
				} else {
					players_enemies.push_back( player );
				}
			}
		}

		ImGui::Columns( 3, _( "Teammates" ), true );
		ImGui::Separator( );

		ImGui::Text( _( "Name" ) );
		ImGui::NextColumn( );

		ImGui::Text( _( "Rank" ) );
		ImGui::NextColumn( );

		ImGui::Text( _( "Money" ) );
		ImGui::NextColumn( );
		ImGui::Separator( );

		for ( auto& player : players_team ) {
			ImGui::TextColored( ImVec4( 0.7019f, 0.9725f, 1.f, 1.f ), _( "%s" ), player->player_info( ).name );
			ImGui::NextColumn( );
			ImGui::Text( _( "%s" ), player->competitive_rank( ).data( ) );
			ImGui::NextColumn( );
			ImGui::Text( _( "$%d" ), player->money( ) );
			ImGui::NextColumn( );

			ImGui::Separator( );
		}

		for ( auto& player : players_enemies ) {
			ImGui::TextColored( ImVec4( 1.f, 0.7019f, 0.7019f, 1.f ), _( "%s" ), player->player_info( ).name );
			ImGui::NextColumn( );
			ImGui::Text( _( "%s" ), player->competitive_rank( ).data( ) );
			ImGui::NextColumn( );
			ImGui::Text( _( "$%d" ), player->money( ) );
			ImGui::NextColumn( );

			ImGui::Separator( );
		}

		ImGui::Columns( 1 );
		ImGui::End( );
	}
}