/**
  @file     stream_denote.h
  @brief    denominates the following element.
  @author   HRYKY
  @version  $Id: stream_denote.h 367 2014-07-13 10:35:21Z hryky.private@gmail.com $
 */
#ifndef STREAM_DENOTE_H_20140208173058396
#define STREAM_DENOTE_H_20140208173058396
#include "hryky/definition.h"
#include "hryky/retention/retention_value.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
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
namespace stream
{
	/// denominates the following element.
	template <hryky_template_param>
	class Denote;

} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief denominates the following element.
 */
template <hryky_template_param>
class hryky::stream::Denote :
	public WithSwap<Denote<hryky_template_arg> >,
	public WithStreamOut<Denote<hryky_template_arg> >,
	public retention::Value<ValueT>
{
public :
	typedef Denote<hryky_template_arg>              this_type;
	typedef retention::Value<ValueT>                retain_type;
	typedef typename retain_type::const_reference   const_reference;

	/// default constructor.
	Denote();

	/// copy constructor.
	Denote(this_type const &);

	/// move constructor.
	Denote(this_type &&);

	/// constructs with the initial value.
	Denote(initializer_type value);

	/// constructs with the initial value as rvalue.
	Denote(ValueT && value);

	/// destructor.
	~Denote();

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

	/// retrieves the literal string.
	const_reference get() const;

protected :

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace stream
{
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::stream::Denote<hryky_template_arg>::Denote()
	: retain_type()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::stream::Denote<hryky_template_arg>::Denote(this_type const & rhs)
	: retain_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::stream::Denote<hryky_template_arg>::Denote(this_type && rhs)
	: retain_type(::std::move(rhs))
{
}
/**
  @brief constructs with the initial value.
 */
template <hryky_template_param>
hryky::stream::Denote<hryky_template_arg>::Denote(initializer_type value)
	: retain_type(value)
{
}
/**
  @brief constructs with the initial value as rvalue.
 */
template <hryky_template_param>
hryky::stream::Denote<hryky_template_arg>::Denote(ValueT && value)
	: retain_type(::std::move(value))
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::stream::Denote<hryky_template_arg>::~Denote()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::stream::Denote<hryky_template_arg>::clear()
{
	this->retain_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::stream::Denote<hryky_template_arg>::swap(this_type & src)
{
	this->retain_type::swap(src);
}
/**
  @brief retrieves the literal string.
 */
template <hryky_template_param>
typename hryky::stream::Denote<hryky_template_arg>::const_reference 
hryky::stream::Denote<hryky_template_arg>::get() const
{
	return *this->retain_type::get();
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::stream::Denote<hryky_template_arg>::write_to(
	StreamT & out) const
{
	out << this->get() << ':';
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
namespace stream
{
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // STREAM_DENOTE_H_20140208173058396
// end of file
