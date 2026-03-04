// include chugin header
#include "chugin.h"

// Include sole UUID header
#include "sole.hpp"

// general includes
#include <string>
#include <iostream>

// declaration of chugin functions
CK_DLL_SFUN( uuid_uuid0 );
CK_DLL_SFUN( uuid_uuid1 );
CK_DLL_SFUN( uuid_uuid4 );

// this is a special offset reserved for chugin internal data
t_CKINT uuid_data_offset = 0;

// class constructor and function registration
CK_DLL_INFO( UUID )
{
    QUERY->setinfo( QUERY, CHUGIN_INFO_CHUGIN_VERSION, "v0.1.0" );
    QUERY->setinfo( QUERY, CHUGIN_INFO_AUTHORS, "Gregg Oliva" );
    QUERY->setinfo( QUERY, CHUGIN_INFO_DESCRIPTION, "Generates a Universally Unique Identifier (UUID) as a string. Uses the `sole` UUID c++ library.");
    QUERY->setinfo( QUERY, CHUGIN_INFO_URL, "" );
    QUERY->setinfo( QUERY, CHUGIN_INFO_EMAIL, "" );
}

CK_DLL_QUERY( UUID )
{
    QUERY->setname( QUERY, "UUID" );
    QUERY->begin_class( QUERY, "UUID", "Object" );

    QUERY->add_sfun( QUERY, uuid_uuid0, "string", "uuid0" );
    QUERY->doc_func( QUERY, "Generates a UUID version 0 string (16-bit PID + 48-bit MAC address + 60-bit clock with a resolution of 100ns since Unix epoch)" );

    QUERY->add_sfun( QUERY, uuid_uuid1, "string", "uuid1" );
    QUERY->doc_func( QUERY, "Generates a UUID version 1 string (48-bit MAC address + 60-bit clock with a resolution of 100 ns)" );

    QUERY->add_sfun( QUERY, uuid_uuid4, "string", "uuid4" );
    QUERY->doc_func( QUERY, "Generates a UUID version 4 string (122-bits of randomness)" );

    uuid_data_offset = QUERY->add_mvar( QUERY, "int", "@uuid_data", false );
    QUERY->end_class( QUERY );
    return TRUE;
}

// example implementation for setter
CK_DLL_SFUN( uuid_uuid0 )
{
    std::string uuidStr = sole::uuid0().str();
    RETURN->v_string = (Chuck_String*)API->object->create_string(VM, uuidStr.c_str(), false);
}

CK_DLL_SFUN( uuid_uuid1 )
{
    std::string uuidStr = sole::uuid1().str();
    RETURN->v_string = (Chuck_String*)API->object->create_string(VM, uuidStr.c_str(), false);
}

CK_DLL_SFUN( uuid_uuid4 )
{
    std::string uuidStr = sole::uuid4().str();
    RETURN->v_string = (Chuck_String*)API->object->create_string(VM, uuidStr.c_str(), false);
}
