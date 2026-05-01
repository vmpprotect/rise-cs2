#include "../../incl.h"

namespace
{
    std::atomic_bool g_running{ true };
    HMODULE g_module = nullptr;

    void draw_render_examples( )
    {
        const auto white = rise::sdk::color::white( );
        const auto red = rise::sdk::color::red( );
        const auto green = rise::sdk::color::green( );
        const auto blue = rise::sdk::color::blue( );
        const auto yellow = rise::sdk::color{ 255 , 220 , 0 , 255 };

        rise::source2::render::screen_text_pixels( 10.0f , 10.0f , 0 , "screen_text_pixels" , white , rise::settings::draw_duration );
        rise::source2::render::screen_text_pixels( 10.0f , 32.0f , 1 , "screen_text_line" , green , rise::settings::draw_duration );
        rise::source2::render::screen_text_pretty_pixels( 10.0f , 58.0f , 2 , "screen_text_pretty" , yellow , rise::settings::draw_duration , "Tahoma" , 22 , true );
        rise::source2::render::text_3d( { 0.0f , 0.0f , 96.0f } , "text_3d" , false , rise::settings::draw_duration );

        rise::source2::render::line(
            { 0.0f , 0.0f , 0.0f } ,
            { 0.0f , 0.0f , 512.0f } ,
            green ,
            false ,
            rise::settings::draw_duration );

        //rise::source2::render::sphere( { 96.0f , 0.0f , 64.0f } , 50.0f , blue , false , rise::settings::draw_duration );
        // ^ sphere just crashes?

        rise::source2::render::box_direction(
            { -96.0f , 0.0f , 64.0f } ,
            { -24.0f , -24.0f , -24.0f } ,
            { 24.0f , 24.0f , 24.0f } ,
            { 1.0f , 0.0f , 0.0f } ,
            red ,
            rise::settings::draw_duration );
    }

    DWORD WINAPI main_thread( LPVOID )
    {
        while ( !rise::source2::render::init( ) )
            Sleep( 100 );

        rise::logging::print( "rise-cs2 initialized" );

        while ( g_running.load( std::memory_order_relaxed ) )
        {
            if ( GetAsyncKeyState( VK_END ) & 1 )
                break;

            if ( GetAsyncKeyState( VK_DELETE ) & 1 )
                rise::source2::render::clear( );

            draw_render_examples( );

            Sleep( 16 );
        }

        FreeLibraryAndExitThread( g_module , 0 );
    }
}

BOOL APIENTRY DllMain( HMODULE module , DWORD reason , LPVOID )
{
    if ( reason == DLL_PROCESS_ATTACH )
    {
        g_module = module;
        DisableThreadLibraryCalls( module );

        const HANDLE thread = CreateThread( nullptr , 0 , main_thread , nullptr , 0 , nullptr );
        if ( thread )
            CloseHandle( thread );
    }
    else if ( reason == DLL_PROCESS_DETACH )
    {
        g_running.store( false , std::memory_order_relaxed );
    }

    return TRUE;
}
