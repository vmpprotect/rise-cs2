#pragma once

#include <cstddef>

namespace rise::source2::offsets::client
{
    inline std::uint64_t debug_draw_screen_text_line = 0x00AFD450; // 48 83 EC ? 48 8B 0D ? ? ? ? 48 85 C9 74 ? 8B 84 24 ? ? ? ? F3 0F 10 94 24
    inline std::uint64_t debug_screen_text_pretty = 0x00AFD4C0; // 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 1D ? ? ? ? 49 8B F9
    inline std::uint64_t debug_draw_text_3d = 0x00AFF7F0; // 48 83 EC ? 4C 8B D1 48 8B 0D ? ? ? ? 48 85 C9 74 ? ? ? ? 4C 8D 0D
    inline std::uint64_t debug_draw_line = 0x00AFAC50; // 48 83 EC ? 4C 8B D9 48 8B 0D ? ? ? ? 48 85 C9 74 ? 0F B6 84 24 ? ? ? ? F3 0F 10 8C 24 
    inline std::uint64_t debug_draw_circle_or_sphere = 0x00AF27F0; // 48 83 EC ? 4C 8B D1 48 8B 0D ? ? ? ? 48 85 C9 74 ? 0F B6 84 24
    inline std::uint64_t debug_draw_box_direction = 0x00AF22C0; // 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B E9 C7 44 24 ? 00 00 00 00
    inline std::uint64_t debug_draw_clear = 0x003B4730; // 48 83 EC ? 48 8B 0D ? ? ? ? 48 85 C9 74 ? ? ? ? 48 83 C4
}
