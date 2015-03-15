/**
  @file     stream_array_scope.h
  @brief    encloses the following elements with an array.
  @author   HRYKY
  @version  $Id: stream_array_scope.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef STREAM_ARRAY_SCOPE_H_20140208181820429
#define STREAM_ARRAY_SCOPE_H_20140208181820429
#include "hryky/without_copy.h"
#include "hryky/retention/retention_reference.h"
#include "hryky/stream/stream_array_begin.h"
#include "hryky/stream/stream_array_end.h"
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
namespace stream
{
namespace array
{
	/// encloses the following elements with an array.
	template <hryky_template_param>
	class Scope;

} // namespace array
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief encloses the following elements with an array.
 */
template <hryky_template_param>
class hryky::stream::array::Scope :
	public retention::Reference<ValueT>,
	public WithSwap<Scope<hryky_template_arg> >,
	private WithoutCopy
{
public :

	typedef retention::Reference<ValueT>    retention_type;
	typedef Scope<hryky_template_arg>       this_type;

	/// constructs with a stream.
	Scope(initializer_type value);

	/// move constructor.
	Scope(this_type &&);

	/// destructor.
	~Scope();

	/// move assignment operator.
	hryky_move_assign_op;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

protected :

private :

	hryky_delete_default_constructor(Scope);
	hryky_delete_this_copy_constructor(Scope);
	hryky_delete_this_copy_assign_op(Scope);

	/// releases the internal resources.
	void clear();

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	bool valid_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace stream
{
namespace array
{
} // namespace array
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructs with a stream.
 */
template <hryky_template_param>
hryky::stream::array::Scope<hryky_template_arg>::Scope(initializer_type value)
	: retention_type(value)
	  , valid_()
{
	(*this->get()) << Begin();
	this->valid_ = true;
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::stream::array::Scope<hryky_template_arg>::Scope(this_type && rhs)
	: retention_type(::std::move(rhs))
	  , hryky_move_member(valid)
{
	rhs.valid_ = false;
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::stream::array::Scope<hryky_template_arg>::~Scope()
{
	if (this->valid_) {
		(*this->get()) << End();
		this->valid_ = false;
	}
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::stream::array::Scope<hryky_template_arg>::swap(this_type & src)
{
	this->retention_type::swap(src);
	hryky_swap_member(valid);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::stream::array::Scope<hryky_template_arg>::clear()
{
	this->retention_type::clear();
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::stream::array::Scope<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << stream::denote("retention_type")
		<< static_cast<retention_type const>(*this);
	return out;
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace stream
{
namespace array
{
	/// instantiates array::Scope<> from an arbitrary stream.
	template <hryky_template_param>
	Scope<hryky_template_arg> scope(ValueT & stream);

} // namespace array
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief instantiates array::Scope<> from an arbitrary stream.
 */
template <hryky_template_param>
hryky::stream::array::Scope<hryky_template_arg>
hryky::stream::array::scope(ValueT & stream)
{
	return Scope<hryky_template_arg>(stream);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // STREAM_ARRAY_SCOPE_H_20140208181820429
// end of file
