#pragma once

#include <cstdint>

namespace rise::sdk
{
    struct vec2
    {
        float x;
        float y;
    };

    struct vec3
    {
        float x;
        float y;
        float z;
    };

    struct vec4
    {
        float x;
        float y;
        float z;
        float w;
    };

    struct color
    {
        std::uint8_t r;
        std::uint8_t g;
        std::uint8_t b;
        std::uint8_t a;

        static constexpr color white( std::uint8_t alpha = 255 )
        {
            return { 255 , 255 , 255 , alpha };
        }

        static constexpr color red( std::uint8_t alpha = 255 )
        {
            return { 255 , 0 , 0 , alpha };
        }

        static constexpr color green( std::uint8_t alpha = 255 )
        {
            return { 0 , 255 , 0 , alpha };
        }

        static constexpr color blue( std::uint8_t alpha = 255 )
        {
            return { 0 , 120 , 255 , alpha };
        }
    };

    struct matrix3x4
    {
        float data[ 3 ][ 4 ];
    };

    struct matrix4x4
    {
        float data[ 4 ][ 4 ];
    };
}
