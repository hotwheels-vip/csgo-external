//
// Created by liga on 7/3/2022.
//

#ifndef HOTWHEELS_CSGO_EXTERNAL_OFFSETS_HPP
#define HOTWHEELS_CSGO_EXTERNAL_OFFSETS_HPP

#include <iostream>

namespace offsets
{
	//signatures
	constexpr ptrdiff_t client_state = 0x58CFDC;
	constexpr ptrdiff_t client_state_get_local_player = 0x180;
	constexpr ptrdiff_t client_state_is_hltv = 0x4D48;
	constexpr ptrdiff_t client_state_map = 0x5DE58B16;
	constexpr ptrdiff_t client_state_map_directory = 0x188;
	constexpr ptrdiff_t client_state_max_player = 0x388;
	constexpr ptrdiff_t client_state_player_info = 0x52C0;
	constexpr ptrdiff_t client_state_state = 0x108;
	constexpr ptrdiff_t client_state_view_angles = 0x4D90;
	constexpr ptrdiff_t clientstate_delta_ticks = 0x174;
	constexpr ptrdiff_t clientstate_last_outgoing_command = 0x4D2C;
	constexpr ptrdiff_t clientstate_choked_commands = 0x4D30;
	constexpr ptrdiff_t clientstate_net_channel = 0x9C;
	constexpr ptrdiff_t entity_list = 0x4DDB8FC;
	constexpr ptrdiff_t force_attack = 0x320BDC8;
	constexpr ptrdiff_t force_attack2 = 0x320BDD4;
	constexpr ptrdiff_t force_backward = 0x320BE10;
	constexpr ptrdiff_t force_forward = 0x320BE04;
	constexpr ptrdiff_t force_jump = 0x52858A0;
	constexpr ptrdiff_t force_left = 0x320BE1C;
	constexpr ptrdiff_t force_right = 0x320BE28;
	constexpr ptrdiff_t game_dir = 0x62B900;
	constexpr ptrdiff_t game_rules_proxy = 0x52F90BC;
	constexpr ptrdiff_t get_all_classes = 0xDE9C9C;
	constexpr ptrdiff_t global_vars = 0x58CCE0;
	constexpr ptrdiff_t glow_object_manager = 0x5324590;
	constexpr ptrdiff_t input = 0x522CED0;
	constexpr ptrdiff_t interface_link_list = 0x96EF44;
	constexpr ptrdiff_t local_player = 0xDBF4BC;
	constexpr ptrdiff_t mouse_enable = 0xDC51C8;
	constexpr ptrdiff_t mouse_enable_ptr = 0xDC5198;
	constexpr ptrdiff_t player_resource = 0x320A160;
	constexpr ptrdiff_t radar_base = 0x5210674;
	constexpr ptrdiff_t sensitivity = 0xDC5064;
	constexpr ptrdiff_t sensitivity_ptr = 0xDC5038;
	constexpr ptrdiff_t set_clan_tag = 0x8A410;
	constexpr ptrdiff_t view_matrix = 0x4DCD214;
	constexpr ptrdiff_t weapon_table = 0x522D994;
	constexpr ptrdiff_t weapon_table_index = 0x326C;
	constexpr ptrdiff_t yaw_ptr = 0xDC4E28;
	constexpr ptrdiff_t zoom_sensitivity_ratio_ptr = 0xDCB610;
	constexpr ptrdiff_t send_packets = 0xD8452;
	constexpr ptrdiff_t direct3d_device9 = 0xA6050;
	constexpr ptrdiff_t studio_hdr = 0x2950;
	constexpr ptrdiff_t yaw_class_ptr = 0xDC4E28;
	constexpr ptrdiff_t pitch_class_ptr = 0x5210910;
	constexpr ptrdiff_t interface_engine_cvar = 0x3EA3C;
	constexpr ptrdiff_t convar_name_hash_table = 0x2F190;
	constexpr ptrdiff_t dormant = 0xED;
	constexpr ptrdiff_t model_ambient_min = 0x590054;
	constexpr ptrdiff_t set_abs_angles = 0x1E59F0;
	constexpr ptrdiff_t set_abs_origin = 0x1E5830;
	constexpr ptrdiff_t is_c4_owner = 0x3CB320;
	constexpr ptrdiff_t force_update_spectator_glow = 0x3BE2BA;
	constexpr ptrdiff_t anim_overlays = 0x2990;
	constexpr ptrdiff_t spawn_time = 0x103C0;
	constexpr ptrdiff_t find_hud_element = 0x349D59D0;
	constexpr ptrdiff_t is_local_player = 0x3628;

	//netvars
	constexpr ptrdiff_t armor_value = 0x117CC;
	constexpr ptrdiff_t collision = 0x320;
	constexpr ptrdiff_t collision_group = 0x474;
	constexpr ptrdiff_t local = 0x2FCC;
	constexpr ptrdiff_t move_type = 0x25C;
	constexpr ptrdiff_t account = 0x117B8;
	constexpr ptrdiff_t original_owner_xuid_high = 0x31D4;
	constexpr ptrdiff_t original_owner_xuid_low = 0x31D0;
	constexpr ptrdiff_t aim_punch_angle = 0x303C;
	constexpr ptrdiff_t aim_punch_angle_vel = 0x3048;
	constexpr ptrdiff_t gun_game_immunity = 0x9990;
	constexpr ptrdiff_t has_defuser = 0x117DC;
	constexpr ptrdiff_t has_helment = 0x117C0;
	constexpr ptrdiff_t in_reload = 0x32B5;
	constexpr ptrdiff_t is_defusing = 0x997C;
	constexpr ptrdiff_t is_scoped = 0x9974;
	constexpr ptrdiff_t spotted = 0x93D;
	constexpr ptrdiff_t spotted_by_mask = 0x980;
	constexpr ptrdiff_t bone_matrix = 0x26A8;
	constexpr ptrdiff_t accuracy_penalty = 0x3340;
	constexpr ptrdiff_t flags = 0x104;
	constexpr ptrdiff_t fallback_wear = 0x31E0;
	constexpr ptrdiff_t flash_duration = 0x10470;
	constexpr ptrdiff_t flash_max_alpha = 0x1046C;
	constexpr ptrdiff_t next_primary_attack = 0x3248;
	constexpr ptrdiff_t active_weapon = 0x2F08;
	constexpr ptrdiff_t my_weapons = 0x2E08;
	constexpr ptrdiff_t observer_target = 0x339C;
	constexpr ptrdiff_t owner = 0x29DC;
	constexpr ptrdiff_t owner_entity = 0x14C;
	constexpr ptrdiff_t account_id = 0x2FD8;
	constexpr ptrdiff_t clip_1 = 0x3274;
	constexpr ptrdiff_t competitive_ranking = 0x1A84;
	constexpr ptrdiff_t competitive_wins = 0x1B88;
	constexpr ptrdiff_t crosshair_id = 0x11838;
	constexpr ptrdiff_t entity_quality = 0x2FBC;
	constexpr ptrdiff_t fov_start = 0x31F8;
	constexpr ptrdiff_t fov = 0x31F4;
	constexpr ptrdiff_t glow_index = 0x10488;
	constexpr ptrdiff_t health = 0x100;
	constexpr ptrdiff_t item_definition_index = 0x2FBA;
	constexpr ptrdiff_t item_id_high = 0x2FD0;
	constexpr ptrdiff_t observer_mode = 0x3388;
	constexpr ptrdiff_t shots_fired = 0x103E0;
	constexpr ptrdiff_t state = 0x3268;
	constexpr ptrdiff_t team_num = 0xF4;
	constexpr ptrdiff_t life_state = 0x25F;
	constexpr ptrdiff_t fallback_paint_kit = 0x31D8;
	constexpr ptrdiff_t fallback_seed = 0x31DC;
	constexpr ptrdiff_t fallback_stat_trak = 0x31E4;
	constexpr ptrdiff_t force_bone = 0x268C;
	constexpr ptrdiff_t tick_base = 0x3440;
	constexpr ptrdiff_t rgfl = 0x444;
	constexpr ptrdiff_t custom_name = 0x304C;
	constexpr ptrdiff_t last_place_name = 0x35C4;
	constexpr ptrdiff_t origin = 0x138;
	constexpr ptrdiff_t velocity = 0x114;
	constexpr ptrdiff_t view_offset = 0x108;
	constexpr ptrdiff_t view_punch_angle = 0x3030;
	constexpr ptrdiff_t third_person_view_angles = 0x31E8;
	constexpr ptrdiff_t render = 0x70;
	constexpr ptrdiff_t c4_blow = 0x29A0;
	constexpr ptrdiff_t timer_length = 0x29A4;
	constexpr ptrdiff_t defuse_length = 0x29B8;
	constexpr ptrdiff_t defuse_count_down = 0x29BC;
	constexpr ptrdiff_t gamerules_data = 0x0;
	constexpr ptrdiff_t survivial_rules = 0xD00;
	constexpr ptrdiff_t survival_game_rule_decision_types = 0x1328;
	constexpr ptrdiff_t is_valve_ds = 0x7C;
	constexpr ptrdiff_t freeze_period = 0x20;
	constexpr ptrdiff_t bomb_planted = 0x9A5;
	constexpr ptrdiff_t is_queued_matching = 0x74;
	constexpr ptrdiff_t simulation_time = 0x268;
	constexpr ptrdiff_t lower_body_yaw_target = 0x9ADC;
	constexpr ptrdiff_t eye_angles_x = 0x117D0;
	constexpr ptrdiff_t eye_angles_y = 0x117D4;
	constexpr ptrdiff_t next_external = 0x2D80;
	constexpr ptrdiff_t most_recenty_model_bone_counter = 0x2690;
	constexpr ptrdiff_t last_bone_setup_time = 0x2928;
	constexpr ptrdiff_t started_arming = 0x3400;
	constexpr ptrdiff_t use_custom_bloom_scale = 0x9DA;
	constexpr ptrdiff_t use_custom_auto_exposure_min = 0x9D8;
	constexpr ptrdiff_t use_custom_auto_exposure_max = 0x9D9;
	constexpr ptrdiff_t custom_bloom_scale = 0x9E4;
	constexpr ptrdiff_t custom_auto_exposure_min = 0x9DC;
	constexpr ptrdiff_t custom_auto_exposure_max = 0x9E0;
	constexpr ptrdiff_t default_fov           = 0x333C;
	constexpr ptrdiff_t entity_index          = 0x64;
} // namespace offsets

#endif // HOTWHEELS_CSGO_EXTERNAL_OFFSETS_HPP
