#pragma once

#include "../essdee/math.hpp"
#include "../essdee/offsets.hpp"
#include "../essdee/structs.hpp"

namespace rise::source2
{
    class render
    {
    public:
        using screen_text_line_fn = void( __fastcall* )(
            float x ,
            float y ,
            int line_offset ,
            const char* text ,
            int r ,
            int g ,
            int b ,
            int a ,
            float duration );

        using screen_text_pretty_fn = void( __fastcall* )(
            float x ,
            float y ,
            unsigned int line_offset ,
            const char* text ,
            char r ,
            char g ,
            char b ,
            char a ,
            float duration ,
            const char* font ,
            int size ,
            char bold );

        using text_3d_fn = void( __fastcall* )(
            const sdk::vec3* origin ,
            const char* text ,
            bool view_check ,
            float duration );

        using line_fn = void( __fastcall* )(
            const sdk::vec3* start ,
            const sdk::vec3* end ,
            int r ,
            int g ,
            int b ,
            bool z_test ,
            float duration );

        using circle_or_sphere_fn = void( __fastcall* )(
            int x ,
            int y ,
            int z ,
            float radius ,
            char r ,
            char g ,
            char b ,
            char a ,
            bool z_test ,
            float duration );

        using box_direction_fn = void( __fastcall* )(
            const sdk::vec3* center ,
            const sdk::vec3* mins ,
            const sdk::vec3* maxs ,
            const sdk::vec3* forward ,
            int r ,
            int g ,
            int b ,
            int a ,
            float duration );

        using clear_fn = void( __fastcall* )( );

        static bool init( );
        static bool ready( );

        static void screen_text_line( float x , float y , int line_offset , const char* text , sdk::color color , float duration );
        static void screen_text_pixels( float x , float y , int line_offset , const char* text , sdk::color color , float duration );
        static void screen_text_pretty( float x , float y , int line_offset , const char* text , sdk::color color , float duration , const char* font , int size , bool bold );
        static void screen_text_pretty_pixels( float x , float y , int line_offset , const char* text , sdk::color color , float duration , const char* font , int size , bool bold );
        static void text_3d( const sdk::vec3& origin , const char* text , bool view_check , float duration );
        static void line( const sdk::vec3& start , const sdk::vec3& end , sdk::color color , bool z_test , float duration );
        static void sphere( const sdk::vec3& center , float radius , sdk::color color , bool z_test , float duration );
        static void box_direction( const sdk::vec3& center , const sdk::vec3& mins , const sdk::vec3& maxs , const sdk::vec3& forward , sdk::color color , float duration );
        static void clear( );

    private:
        static sdk::vec2 normalize_pixels( float x , float y , const char* text , int font_size , bool bold );

        static inline sdk::module client_{};
        static inline screen_text_line_fn screen_text_line_ = nullptr;
        static inline screen_text_pretty_fn screen_text_pretty_ = nullptr;
        static inline text_3d_fn text_3d_ = nullptr;
        static inline line_fn line_ = nullptr;
        static inline circle_or_sphere_fn circle_or_sphere_ = nullptr;
        static inline box_direction_fn box_direction_ = nullptr;
        static inline clear_fn clear_ = nullptr;
    };
}
