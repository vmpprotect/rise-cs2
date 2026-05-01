#include "render.hpp"

#include <Windows.h>

#include <cstring>

namespace rise::source2
{
    bool render::init( )
    {
        client_ = sdk::module( L"client.dll" );
        if ( !client_.valid( ) )
            return false;

        screen_text_line_ = client_.at< screen_text_line_fn >( offsets::client::debug_draw_screen_text_line );
        screen_text_pretty_ = client_.at< screen_text_pretty_fn >( offsets::client::debug_screen_text_pretty );
        text_3d_ = client_.at< text_3d_fn >( offsets::client::debug_draw_text_3d );
        line_ = client_.at< line_fn >( offsets::client::debug_draw_line );
        circle_or_sphere_ = client_.at< circle_or_sphere_fn >( offsets::client::debug_draw_circle_or_sphere );
        box_direction_ = client_.at< box_direction_fn >( offsets::client::debug_draw_box_direction );
        clear_ = client_.at< clear_fn >( offsets::client::debug_draw_clear );

        return ready( );
    }

    bool render::ready( )
    {
        return screen_text_line_ != nullptr && line_ != nullptr;
    }

    void render::screen_text_line( float x , float y , int line_offset , const char* text , sdk::color color , float duration )
    {
        if ( !screen_text_line_ )
            return;

        sdk::process_event( screen_text_line_ , x , y , line_offset , text , color.r , color.g , color.b , color.a , duration );
    }

    void render::screen_text_pixels( float x , float y , int line_offset , const char* text , sdk::color color , float duration )
    {
        const auto normalized = normalize_pixels( x , y , text , 16 , false );
        screen_text_line( normalized.x , normalized.y , line_offset , text , color , duration );
    }

    void render::screen_text_pretty( float x , float y , int line_offset , const char* text , sdk::color color , float duration , const char* font , int size , bool bold )
    {
        if ( !screen_text_pretty_ )
            return;

        sdk::process_event( screen_text_pretty_ , x , y , static_cast< unsigned int >( line_offset ) , text ,
            static_cast< char >( color.r ) , static_cast< char >( color.g ) , static_cast< char >( color.b ) , static_cast< char >( color.a ) ,
            duration , font , size , static_cast< char >( bold ) );
    }

    void render::screen_text_pretty_pixels( float x , float y , int line_offset , const char* text , sdk::color color , float duration , const char* font , int size , bool bold )
    {
        const auto normalized = normalize_pixels( x , y , text , size , bold );
        screen_text_pretty( normalized.x , normalized.y , line_offset , text , color , duration , font , size , bold );
    }

    void render::text_3d( const sdk::vec3& origin , const char* text , bool view_check , float duration )
    {
        if ( !text_3d_ )
            return;

        sdk::process_event( text_3d_ , &origin , text , view_check , duration );
    }

    void render::line( const sdk::vec3& start , const sdk::vec3& end , sdk::color color , bool z_test , float duration )
    {
        if ( !line_ )
            return;

        sdk::process_event( line_ , &start , &end , color.r , color.g , color.b , z_test , duration );
    }

    void render::sphere( const sdk::vec3& center , float radius , sdk::color color , bool z_test , float duration )
    {
        if ( !circle_or_sphere_ )
            return;

        sdk::process_event( circle_or_sphere_ ,
            static_cast< int >( center.x ) ,
            static_cast< int >( center.y ) ,
            static_cast< int >( center.z ) ,
            radius ,
            static_cast< char >( color.r ) ,
            static_cast< char >( color.g ) ,
            static_cast< char >( color.b ) ,
            static_cast< char >( color.a ) ,
            z_test ,
            duration );
    }

    void render::box_direction( const sdk::vec3& center , const sdk::vec3& mins , const sdk::vec3& maxs , const sdk::vec3& forward , sdk::color color , float duration )
    {
        if ( !box_direction_ )
            return;

        sdk::process_event( box_direction_ , &center , &mins , &maxs , &forward , color.r , color.g , color.b , color.a , duration );
    }

    void render::clear( )
    {
        if ( !clear_ )
            return;

        sdk::process_event( clear_ );
    }

    sdk::vec2 render::normalize_pixels( float x , float y , const char* text , int font_size , bool bold )
    {
        HWND foreground = GetForegroundWindow( );
        if ( !foreground )
            return { x , y };

        RECT client{};
        if ( !GetClientRect( foreground , &client ) )
            return { x , y };

        const int width = client.right - client.left;
        const int height = client.bottom - client.top;
        if ( width <= 0 || height <= 0 )
            return { x , y };

        const auto length = text ? std::strlen( text ) : 0;
        const auto bold_scale = bold ? 0.64f : 0.58f;
        const auto text_width = static_cast< float >( length ) * static_cast< float >( font_size ) * bold_scale;
        const auto text_height = static_cast< float >( font_size );
        const auto anchor_x = x + text_width;
        const auto anchor_y = y + text_height;

        return {
            1.0f - ( anchor_x / static_cast< float >( width ) ) ,
            1.0f - ( anchor_y / static_cast< float >( height ) )
        };
    }
}
