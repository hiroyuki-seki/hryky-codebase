/**
  @file     rtiow_greater.h
  @brief    verifies an inspected value is greater than the ratained value.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_GREATER_H_20160717113835151
#define RTIOW_GREATER_H_20160717113835151
#include "hryky/definition.h"
#include "hryky/clear.h"
#include "hryky/swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT
#define hryky_template_arg \
	ValueT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
	/// verifies an inspected value is greater than the ratained value.
	template <hryky_template_param>
	class Greater;

} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief verifies an inspected value is greater than the ratained value.
 */
template <typename ValueT = float>
class hryky::rtiow::Greater
{
public :

	typedef Greater<hryky_template_arg> this_type;

	/// default constructor.
	Greater();

	/// instantiates with a value.
	Greater(ValueT const & value);

	/// copy constructor.
	Greater(this_type const &);

	/// move constructor.
	Greater(this_type &&);

	/// destructor.
	~Greater();

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
	StreamT & write_to(StreamT & out) const;

	/// confirms whether a value is in the range.
	template <typename SrcT>
	bool verify(SrcT src) const;

protected :

private :

	ValueT value_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::rtiow::Greater<hryky_template_arg>::Greater()
	: value_()
{
}
/**
  @brief instantiates with a value.
 */
template <hryky_template_param>
hryky::rtiow::Greater<hryky_template_arg>::Greater(ValueT const & value)
	: value_(value)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::rtiow::Greater<hryky_template_arg>::Greater(this_type const & rhs)
	: hryky_copy_member(value)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::rtiow::Greater<hryky_template_arg>::Greater(this_type && rhs)
	: hryky_move_member(value)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::rtiow::Greater<hryky_template_arg>::~Greater()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::rtiow::Greater<hryky_template_arg>::clear()
{
	hryky::clear(this->value_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::rtiow::Greater<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(value);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::rtiow::Greater<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return out;
}
/**
  @brief confirms whether a value is in the range.
 */
template <hryky_template_param>
template <typename SrcT>
bool hryky::rtiow::Greater<hryky_template_arg>::verify(SrcT src) const
{
	return this->value_ < src;
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
namespace rtiow
{
} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // RTIOW_GREATER_H_20160717113835151
// end of file
