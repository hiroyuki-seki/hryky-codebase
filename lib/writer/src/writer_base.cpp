/**
  @file         writer_base.cpp
  @brief        base class to write data polymorphically.
  @author       HRYKY
  @version      $Id: writer_base.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/writer/writer_base.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace writer
{
namespace
{
} // namespace "anonymous"
} // namespace writer
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
  @brief interchanges the each internal resources of two instances.
 */
void hryky::writer::Base::swap(this_type &)
{
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
hryky::writer::Base::Base()
{
}
/**
  @brief copy constructor.
 */
hryky::writer::Base::Base(this_type const &)
{
}
/**
  @brief move constructor.
 */
hryky::writer::Base::Base(this_type &&)
{
}
/**
  @brief destructor.
 */
hryky::writer::Base::~Base()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::writer::Base::clear()
{
}
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
namespace writer
{
namespace
{
} // namespace "anonymous"
} // namespace writer
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
