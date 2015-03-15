/**
  @file     shader_arguments.h
  @brief    bundles arguments.
  @author   HRYKY
  @version  $Id: shader_arguments.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_ARGUMENTS_H_20140824151047299
#define SHADER_ARGUMENTS_H_20140824151047299
#include "hryky/shader/shader_block.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
	/// bundles arguments.
	class Arguments;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief bundles arguments.
 */
class hryky::shader::Arguments :
	public Block<Arguments>
{
public :

	typedef Arguments this_type;
	typedef Block<this_type> base_type;

	/// default constructor.
	Arguments();

	/// copy constructor.
	Arguments(this_type const &);

	/// move constructor.
	Arguments(this_type &&);

	/// destructor.
	~Arguments();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to_impl(StreamT & out) const;

	/// writes the declaration of each argument.
	Coder & declare_impl(Coder & coder) const;

protected :

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT &
hryky::shader::Arguments::write_to_impl(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	(out
	 << stream::denote("block")
	 << *static_cast<base_type const *>(this));
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
namespace shader
{
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // SHADER_ARGUMENTS_H_20140824151047299
// end of file
