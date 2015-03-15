/**
  @file     ssl_module.cpp
  @brief    initializes OpenSSL library.
  @author   HRYKY
  @version  $Id: ssl_module.cpp 350 2014-04-24 10:10:31Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/clear.h"
#include "hryky/ssl/ssl_common.h"
#include "hryky/ssl/ssl_module.h"
#include "hryky/swap.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace ssl
{
namespace
{
} // namespace "anonymous"
} // namespace ssl
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
hryky::ssl::Module::Module()
	: initialized_()
{
	SSL_load_error_strings();
	ERR_load_BIO_strings();
	OpenSSL_add_all_algorithms();
	this->initialized_ = true;
}
/**
  @brief move constructor.
 */
hryky::ssl::Module::Module(this_type && rhs)
	: hryky_move_member(initialized)
{
	hryky::clear(rhs.initialized_);
}
/**
  @brief destructor.
 */
hryky::ssl::Module::~Module()
{
	this->clear();
}
/**
  @brief releases the internal resources.
 */
void hryky::ssl::Module::clear()
{
	hryky::clear(this->initialized_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::ssl::Module::swap(this_type & src)
{
	hryky_swap_member(initialized)
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
// defines functions used in this file
//------------------------------------------------------------------------------
namespace hryky
{
namespace ssl
{
namespace
{
} // namespace "anonymous"
} // namespace ssl
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
