# rise-cs2

source-2 render/debug SDK layer for CS2.

no external libraries used for rendering or hooking of any kind.

all we're doing here is just invoking functions from client.dll to render text, boxes, spheres, lines ,etc.

now all you need is world to screen and an entity loop and you have a fully engine rendered internal

https://streamable.com/jqd8xw
## render examples

```cpp
rise::source2::render::init( );

rise::source2::render::screen_text_pixels(
    10.0f ,
    10.0f ,
    0 ,
    "screen_text_pixels" ,
    rise::sdk::color::white( ) ,
    0.05f );

rise::source2::render::screen_text_line(
    0.88f ,
    0.92f ,
    1 ,
    "screen_text_line" ,
    rise::sdk::color::green( ) ,
    0.05f );

rise::source2::render::screen_text_pixels(
    10.0f ,
    32.0f ,
    1 ,
    "screen_text_line" ,
    rise::sdk::color::green( ) ,
    0.05f );

rise::source2::render::screen_text_pretty(
    0.88f ,
    0.88f ,
    2 ,
    "screen_text_pretty" ,
    { 255 , 220 , 0 , 255 } ,
    0.05f ,
    "Tahoma" ,
    22 ,
    true );

rise::source2::render::screen_text_pretty_pixels(
    10.0f ,
    58.0f ,
    2 ,
    "screen_text_pretty" ,
    { 255 , 220 , 0 , 255 } ,
    0.05f ,
    "Tahoma" ,
    22 ,
    true );

rise::source2::render::text_3d(
    { 0.0f , 0.0f , 96.0f } ,
    "text_3d" ,
    false ,
    0.05f );

rise::source2::render::line(
    { 0.0f , 0.0f , 0.0f } ,
    { 0.0f , 0.0f , 512.0f } ,
    rise::sdk::color::green( ) ,
    false ,
    0.05f );

rise::source2::render::sphere(
    { 96.0f , 0.0f , 64.0f } ,
    50.0f ,
    rise::sdk::color::blue( ) ,
    false ,
    0.05f );

rise::source2::render::box_direction(
    { -96.0f , 0.0f , 64.0f } ,
    { -24.0f , -24.0f , -24.0f } ,
    { 24.0f , 24.0f , 24.0f } ,
    { 1.0f , 0.0f , 0.0f } ,
    rise::sdk::color::red( ) ,
    0.05f );

rise::source2::render::clear( );
```

The sample DLL in `source/rise/entry.cpp` draws every render option each
frame. Press `DELETE` to call `clear( )`, or `END` to stop and unload.
