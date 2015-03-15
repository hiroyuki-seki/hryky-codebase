/**
  @file     socket_module.h
  @brief    manages the whole functionality of hryky::socket module.
  @author   HRYKY
  @version  $Id: socket_module.h 329 2014-02-24 08:13:29Z hryky.private@gmail.com $
 */
#ifndef SOCKET_MODULE_H_20140223101029090
#define SOCKET_MODULE_H_20140223101029090
#if HRYKY_PLATFORM_WINDOWS
#   include "hryky/socket/socket_module.win32.h"
#else
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace socket
{
	/// manages the whole functionality of hryky::socket module.
	class Module;

} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief manages the whole functionality of hryky::socket module.
 */
class hryky::socket::Module
{
public :

	typedef Module this_type;

	/// default constructor.
	Module();

	/// copy constructor.
	Module(this_type const &);

	/// move constructor.
	Module(this_type &&);

	/// destructor.
	~Module();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

protected :

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace socket
{
} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::socket::Module::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace socket
{
} // namespace socket
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif
#endif // SOCKET_MODULE_H_20140223101029090
// end of file
