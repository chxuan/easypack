#ifndef _EASYPACK_H
#define _EASYPACK_H

#ifdef ENABLE_BOOST_SERIALIZATION
#include "boost_serialization/boost_serialization_head.hpp"
#endif

#ifdef ENABLE_MSGPACK
#include "messagepack/message_pack_head.hpp"
#endif

#ifdef ENABLE_JSON
#include "json/json_pack_head.hpp"
#endif

#endif
