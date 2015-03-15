/**
  @file     ssl_module.h
  @brief    initializes OpenSSL library.
  @author   HRYKY
  @version  $Id: ssl_module.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef SSL_MODULE_H_20140222132736227
#define SSL_MODULE_H_20140222132736227
#include "hryky/definition.h"
#include "hryky/with_swap.h"
#include "hryky/with_stream_out.h"
#include "hryky/without_copy.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace ssl
{
	/// initializes OpenSSL library.
	class Module;

} // namespace ssl
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief initializes OpenSSL library.
 */
class hryky::ssl::Module :
	public WithSwap<Module>,
	public WithStreamOut<Module>,
	private WithoutCopy
{
public :

	typedef Module this_type;

	/// default constructor.
	Module();

	/// move constructor.
	Module(this_type &&);

	/// destructor.
	~Module();

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

	hryky_delete_this_copy_constructor(Module);
	hryky_delete_this_copy_assign_op(Module);

	bool initialized_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace ssl
{
} // namespace ssl
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::ssl::Module::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(initialized);
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
namespace ssl
{
} // namespace ssl
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // SSL_MODULE_H_20140222132736227
// end of file
