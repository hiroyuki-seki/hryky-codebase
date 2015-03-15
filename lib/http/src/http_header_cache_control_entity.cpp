/**
  @file         http_header_cache_control_entity.cpp
  @brief        retains 'Cache-Control' field of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_cache_control_entity.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_header_cache_control_entity.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
namespace header
{
namespace cache
{
namespace control
{
namespace
{
} // namespace "anonymous"
} // namespace control
} // namespace cache
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// static variable
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// function prototype
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
hryky::http::header::cache::control::Entity::Entity()
{
}
/**
  @brief copy constructor.
 */
hryky::http::header::cache::control::Entity::Entity(this_type const &)
{
}
/**
  @brief move constructor.
 */
hryky::http::header::cache::control::Entity::Entity(this_type &&)
{
}
/**
  @brief constructor.
 */
hryky::http::header::cache::control::Entity::Entity(mempool_type const)
{
}
/**
  @brief destructor.
 */
hryky::http::header::cache::control::Entity::~Entity()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::header::cache::control::Entity::clear()
{
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::header::cache::control::Entity::swap(this_type &)
{
}
/**
  @brief appends a cache directive.
 */
bool hryky::http::header::cache::control::Entity::append(
	directive::kind_type const directive)
{
	switch (directive.raw()) {
	case directive::Kind::no_cache: break;
	case directive::Kind::no_store: break;
	case directive::Kind::max_age: break;
	case directive::Kind::max_stale: break;
	case directive::Kind::min_fresh: break;
	case directive::Kind::no_transform: break;
	case directive::Kind::only_if_cached: break;
	case directive::Kind::as_public: break;
	case directive::Kind::as_private: break;
	case directive::Kind::must_revalidate: break;
	case directive::Kind::proxy_revalidate: break;
	case directive::Kind::s_maxage: break;

	default:
		hryky_log_err(
			"invalid cache directive " << directive.raw());
		return false;
	}
	return true;
}
/**
  @brief appends a delta seconds of cache-directive.
 */
bool hryky::http::header::cache::control::Entity::append(
	directive::kind_type const & kind,
	seconds_type const &)
{
	switch (kind.raw()) {
	case directive::Kind::no_cache: break;
	case directive::Kind::no_store: break;
	case directive::Kind::max_age: break;
	case directive::Kind::max_stale: break;
	case directive::Kind::min_fresh: break;
	case directive::Kind::no_transform: break;
	case directive::Kind::only_if_cached: break;
	case directive::Kind::as_public: break;
	case directive::Kind::as_private: break;
	case directive::Kind::must_revalidate: break;
	case directive::Kind::proxy_revalidate: break;
	case directive::Kind::s_maxage: break;

	default:
		hryky_log_err(
			"invalid cache directive " << kind.raw());
		return false;
	}
	return true;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
namespace header
{
namespace cache
{
namespace control
{
namespace
{
} // namespace "anonymous"
} // namespace control
} // namespace cache
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
