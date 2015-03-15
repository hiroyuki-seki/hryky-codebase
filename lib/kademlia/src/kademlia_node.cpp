/**
  @file     kademlia_node.cpp
  @brief    The information of a node in the Kademlia network.
  @author   HRYKY
  @version  $Id: kademlia_node.cpp 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/kademlia/kademlia_node.h"
#include "hryky/clear.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace kademlia
{
namespace
{
} // namespace "anonymous"
} // namespace kademlia
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
hryky::kademlia::Node::Node()
	: ip_()
{
}
/**
  @brief copy constructor.
 */
hryky::kademlia::Node::Node(this_type const & rhs)
	: hryky_copy_member(ip)
{
}
/**
  @brief move constructor.
 */
hryky::kademlia::Node::Node(this_type && rhs)
	: hryky_move_member(ip)
{
}
/**
  @brief destructor.
 */
hryky::kademlia::Node::~Node()
{
}
/**
  @brief releases the internal resources.
 */
void hryky::kademlia::Node::clear()
{
	hryky::clear(this->ip_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
void hryky::kademlia::Node::swap(this_type & src)
{
	hryky_swap_member(ip);
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
namespace kademlia
{
namespace
{
} // namespace "anonymous"
} // namespace kademlia
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
