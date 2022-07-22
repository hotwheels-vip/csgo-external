#include "grenades.hpp"

#include "../../cheat.hpp"

#include "../overlay/overlay.hpp"

#include "../../helpers/console/console.hpp"
#include "../../helpers/driver/driver.hpp"
#include "../../helpers/math/math.hpp"

#include "../../sdk/enums/flags.hpp"
#include "../../sdk/enums/weapon_id.hpp"
#include "../../sdk/structs/game.hpp"
#include "../../sdk/structs/offsets.hpp"
#include "../../sdk/structs/vector.hpp"

void grenades::render( )
{
	VM_TIGER_WHITE_START

	auto draw_list = ImGui::GetBackgroundDrawList( );

	auto player = sdk::game::local_player( );

	if ( !player )
		return;

	auto weapon = player->get_weapon( )->weapon_id( );

	if ( weapon != sdk::weapon_hegrenade && weapon != sdk::weapon_flashbang && weapon != sdk::weapon_smokegrenade && weapon != sdk::weapon_molotov )
		return;

	auto grenade_type = weapon == sdk::weapon_hegrenade ? 2 : weapon == sdk::weapon_flashbang ? 1 : weapon == sdk::weapon_smokegrenade ? 0 : 3;

	for ( auto& map : grenade_list ) {
		std::string map_name = cheat::bsp_parser.map_name.substr( cheat::bsp_parser.map_name.find_last_of( "\\/" ) + 1 );

		if ( map.first + ".bsp" == map_name ) {
			for ( auto& grenade : map.second ) {
				if ( grenade.first == grenade_type ) {
					for ( auto& grenade_info : grenade.second ) {
						auto screen_position = math::world_to_screen( grenade_info.position );

						if ( screen_position.second && grenade_info.position.dist_to( player->origin( ) ) < 1000 &&
						     grenade_info.position.dist_to( player->origin( ) ) > 5 ) {
							auto last_position = sdk::vector{ };

							for ( float faces{ }; faces < PI * 2; faces += ( PI * 2 ) / 30 ) {
								auto offset = sdk::vector( cosf( faces ), sinf( faces ) ) * 5.f; // 5.f is the radius of the circle

								auto screen_offset = math::world_to_screen( grenade_info.position + offset );

								draw_list->AddLine( *reinterpret_cast< ImVec2* >( last_position.is_zero( ) ? &screen_offset.first : &last_position ),
								                    *reinterpret_cast< ImVec2* >( &screen_offset.first ), ImColor( 255, 255, 255, 255 ), 1.f );

								last_position = screen_offset.first;
							}
						}

						auto client_state = driver::read< std::uint32_t >( reinterpret_cast< void* >( cheat::engine_dll + offsets::client_state ) );
						auto view_angles =
							driver::read< sdk::vector >( reinterpret_cast< PVOID >( client_state + offsets::client_state_view_angles ) );

						float x1 = overlay::screen_w / 2.f;
						float y1 = overlay::screen_h / 2.f;

						float x2 = overlay::screen_w / static_cast< float >( player->default_fov( ) );
						float y2 = overlay::screen_h / static_cast< float >( player->default_fov( ) );

						x1 -= x2 * ( grenade_info.angle.y - view_angles.y ) / 2;
						y1 += y2 * ( grenade_info.angle.x - view_angles.x );

						x1 = std::floor( x1 );
						y1 = std::floor( y1 );

						auto origin           = screen_position.first + sdk::vector{ 0.f, 0.f, 10.f };
						auto origin_direction = sdk::vector{ x1, y1, 0.f };

						if ( grenade_info.position.dist_to( player->origin( ) ) < 90 ) {
							draw_list->AddCircleFilled( *reinterpret_cast< ImVec2* >( &origin_direction ), 4.f, ImColor( 0, 0, 0, 255 ), 30 );
							draw_list->AddCircleFilled( *reinterpret_cast< ImVec2* >( &origin_direction ), 3.f, ImColor( 255, 255, 255, 255 ), 30 );

							auto text_size     = ImGui::CalcTextSize( grenade_info.name.c_str( ) );
							auto text_position = origin_direction + sdk::vector{ -( text_size.x / 2.f ), text_size.y / 2.f + sqrtf( 4.f ), 0.f };

							draw_list->AddText( ImVec2( text_position.x + 1, text_position.y + 1 ),
							                    ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, 1.f - 0.5f ) ), grenade_info.name.c_str( ) );
							draw_list->AddText( ImVec2( text_position.x - 1, text_position.y + 1 ),
							                    ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, 1.f - 0.5f ) ), grenade_info.name.c_str( ) );
							draw_list->AddText( ImVec2( text_position.x + 1, text_position.y - 1 ),
							                    ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, 1.f - 0.5f ) ), grenade_info.name.c_str( ) );
							draw_list->AddText( ImVec2( text_position.x - 1, text_position.y - 1 ),
							                    ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, 1.f - 0.5f ) ), grenade_info.name.c_str( ) );

							draw_list->AddText( ImVec2( text_position.x, text_position.y + 1 ),
							                    ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, 1.f - 0.5f ) ), grenade_info.name.c_str( ) );
							draw_list->AddText( ImVec2( text_position.x, text_position.y + 1 ),
							                    ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, 1.f - 0.5f ) ), grenade_info.name.c_str( ) );
							draw_list->AddText( ImVec2( text_position.x + 1, text_position.y ),
							                    ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, 1.f - 0.5f ) ), grenade_info.name.c_str( ) );
							draw_list->AddText( ImVec2( text_position.x - 1, text_position.y ),
							                    ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, 1.f - 0.5f ) ), grenade_info.name.c_str( ) );

							draw_list->AddText( ImVec2( text_position.x, text_position.y ), ImGui::GetColorU32( ImVec4( 1.f, 1.f, 1.f, 1.f ) ),
							                    grenade_info.name.c_str( ) );
						}
					}
				}
			}
		}
	}

	VM_TIGER_WHITE_END
}

void grenades::update( ) { }