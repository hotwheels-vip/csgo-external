#ifndef B578A151_D6BE_4EE1_88F1_0C960ADBC649
#define B578A151_D6BE_4EE1_88F1_0C960ADBC649

#include <unordered_map>

#include <d3d11.h>
#include <dxgi1_4.h>

#include "../../../dependencies/imgui/imgui.h"
#include "../../../dependencies/imgui/imgui_impl_dx11.h"
#include "../../../dependencies/imgui/imgui_impl_win32.h"

#include "../../sdk/structs/vector.hpp"

namespace grenades
{
	struct grenade_info {
		std::string name{ };

		sdk::vector position{ };
		sdk::vector angle{ };
	};

	inline std::unordered_map< std::string, std::unordered_map< int, std::vector< grenade_info > > > grenade_list{ };

	void render( );
	void update( );
} // namespace grenades

#endif // B578A151_D6BE_4EE1_88F1_0C960ADBC649
