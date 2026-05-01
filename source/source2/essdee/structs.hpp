#pragma once

#include <Windows.h>

#include <cstddef>
#include <cstdint>

#define declare_member( type , name , offset ) \
    type& name( ) \
    { \
        return *reinterpret_cast< type* >( reinterpret_cast< std::uintptr_t >( this ) + offset ); \
    } \
    const type& name( ) const \
    { \
        return *reinterpret_cast< const type* >( reinterpret_cast< std::uintptr_t >( this ) + offset ); \
    }

#define apply_member( type , name , offset ) \
    type* name( ) \
    { \
        return reinterpret_cast< type* >( reinterpret_cast< std::uintptr_t >( this ) + offset ); \
    } \
    const type* name( ) const \
    { \
        return reinterpret_cast< const type* >( reinterpret_cast< std::uintptr_t >( this ) + offset ); \
    }

#define declare_member_bit( bit , name , offset ) \
    bool name( ) const \
    { \
        const auto value = *reinterpret_cast< const std::uint8_t* >( reinterpret_cast< std::uintptr_t >( this ) + offset ); \
        return ( value & ( 1u << bit ) ) != 0; \
    }

namespace rise::sdk
{
    class module
    {
    public:
        module( ) = default;

        explicit module( const wchar_t* name )
            : base_( reinterpret_cast< std::uintptr_t >( GetModuleHandleW( name ) ) )
        {
        }

        bool valid( ) const
        {
            return base_ != 0;
        }

        std::uintptr_t base( ) const
        {
            return base_;
        }

        template < typename type >
        type at( std::ptrdiff_t offset ) const
        {
            if ( !valid( ) )
                return nullptr;

            return reinterpret_cast< type >( base_ + offset );
        }

    private:
        std::uintptr_t base_ = 0;
    };

    template < typename fn , typename... args >
    decltype( auto ) process_event( fn function , args... arguments )
    {
        return function( arguments... );
    }
}
