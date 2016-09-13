#ifndef _EASYPACK_H
#define _EASYPACK_H

#ifdef ENABLE_BOOST_SERIALIZATION
#include "boost_serialization/BoostSerializationHead.hpp"
#endif

#ifdef ENABLE_MSGPACK
#include "messagepack/MessagePackHead.hpp"
#endif

#ifdef ENABLE_JSON
#include "json/JsonPackHead.hpp"
#endif

#endif
