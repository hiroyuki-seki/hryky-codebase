/**
  @file     rtiow_degree.h
  @brief    retains an angular by degree.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_DEGREE_H_20160818075947999
#define RTIOW_DEGREE_H_20160818075947999
#include "hryky/definition.h"
#include "hryky/clear.h"
#include "hryky/swap.h"
#include "hryky/pi.h"
#include "hryky/type_traits/add_const_reference.h"
#include "hryky/type_traits/add_const_pointer.h"
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
	/// retains an angular by degree.
	template <hryky_template_param>
	class Degree;

} // namespace rtiow
namespace stream
{
namespace map
{
	template <typename StreamT>
	class Scope;
	
} // namespace map
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains an angular by degree.
 */
template <typename ValueT = float>
class hryky::rtiow::Degree
{
public :

	typedef Degree<hryky_template_arg> this_type;
	typedef ValueT value_type;
	typedef typename AddPointer<ValueT>::type pointer;
	typedef typename AddConstPointer<ValueT>::type const_pointer;
	typedef typename AddReference<ValueT>::type reference;
	typedef typename AddConstReference<ValueT>::type const_reference;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// retrieves the value.
	value_type get() const;

	/// retrieves the reference as mutable.
	reference get();

	value_type value_;

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
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::rtiow::Degree<hryky_template_arg>::clear()
{
	hryky::clear(this->value_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::rtiow::Degree<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(value);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::rtiow::Degree<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
}
/**
  @brief retrieves the value.
 */
template <hryky_template_param>
typename hryky::rtiow::Degree<hryky_template_arg>::value_type 
hryky::rtiow::Degree<hryky_template_arg>::get() const
{
	return this->value_;
}
/**
  @brief retrieves the reference as mutable.
 */
template <hryky_template_param>
typename hryky::rtiow::Degree<hryky_template_arg>::reference
hryky::rtiow::Degree<hryky_template_arg>::get()
{
	return this->value_;
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
	/// creates a degree from the value.
	template <hryky_template_param>
	Degree<hryky_template_arg> degree(ValueT value);

} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a degree from the value.
 */
template <hryky_template_param>
hryky::rtiow::Degree<hryky_template_arg>
hryky::rtiow::degree(ValueT value)
{
	Degree<hryky_template_arg> const ret = {value};
	return ret;
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // RTIOW_DEGREE_H_20160818075947999
// end of file
