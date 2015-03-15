/**
  @file     http_server.cpp
  @brief    starts HTTP Server.
  @author   HRYKY
  @version  $Id: http_server.cpp 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/http/http_server.h"
#include "hryky/is_null.h"
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
namespace
{
} // namespace "anonymous"
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
hryky::http::Server::Server()
{
}
/**
  @brief destructor.
 */
hryky::http::Server::~Server()
{
	this->clear();
}
/**
  @brief move constructor.
 */
hryky::http::Server::Server(this_type &&)
{
}
/**
  @brief releases the internal resources.
 */
void hryky::http::Server::clear()
{
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::http::Server::swap(this_type &)
{
}
/**
  @brief confirms whether the HTTP Server is down.
 */
bool hryky::http::Server::terminal() const
{
	return true;
}
/**
  @brief starts HTTP server.
 */
bool hryky::http::Server::open(char const * const document_root)
{
	if (hryky_is_null(document_root)) {
		hryky_log_err("DocumentRoot of HTTP Server has to be specified.");
		return false;
	}
	
	this->clear();
	
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
namespace
{
} // namespace "anonymous"
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
