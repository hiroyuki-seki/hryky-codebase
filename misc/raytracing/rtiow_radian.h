/**
  @file     rtiow_radian.h
  @brief    retains an angular by radian.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_RADIAN_H_20160818082833019
#define RTIOW_RADIAN_H_20160818082833019
#include "hryky/definition.h"
#include "hryky/pi.h"
#include "hryky/clear.h"
#include "hryky/swap.h"
#include "hryky/type_traits/add_const_pointer.h"
#include "hryky/type_traits/add_const_reference.h"
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
	/// retains an angular by radian.
	template <hryky_template_param>
	class Radian;

	template <typename ValueT>
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
  @brief retains an angular by radian.
 */
template <typename ValueT>
class hryky::rtiow::Radian
{
public :

	typedef Radian<hryky_template_arg> this_type;
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
void hryky::rtiow::Radian<hryky_template_arg>::clear()
{
}

/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::rtiow::Radian<hryky_template_arg>::swap(this_type & src)
{
}

/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::rtiow::Radian<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
}

/**
  @brief retrieves the value.
 */
template <hryky_template_param>
typename hryky::rtiow::Radian<hryky_template_arg>::value_type 
hryky::rtiow::Radian<hryky_template_arg>::get() const
{
	return this->value_;
}

/**
  @brief retrieves the reference as mutable.
 */
template <hryky_template_param>
typename hryky::rtiow::Radian<hryky_template_arg>::reference
hryky::rtiow::Radian<hryky_template_arg>::get()
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
	/// creates a radian from the degree.
	template <hryky_template_param>
	Radian<hryky_template_arg> radian(
		Degree<hryky_template_arg> const & degree);

} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a radian from the degree.
 */
template <hryky_template_param>
hryky::rtiow::Radian<hryky_template_arg>
hryky::rtiow::radian(Degree<hryky_template_arg> const & degree)
{
	Radian<hryky_template_arg> const ret = {
		degree.get() * CalcPi<float, 23>::value / ValueT(180) };
	return ret;
}

//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // RTIOW_RADIAN_H_20160818082833019
// end of file
