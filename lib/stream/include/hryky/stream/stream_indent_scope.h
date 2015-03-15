/**
  @file     stream_indent_scope.h
  @brief    indicates a stream to indent all lines during the current scope.
  @author   HRYKY
  @version  $Id: stream_indent_scope.h 364 2014-07-12 01:03:03Z hryky.private@gmail.com $
 */
#ifndef STREAM_INDENT_SCOPE_H_20140216175648414
#define STREAM_INDENT_SCOPE_H_20140216175648414
#include "hryky/retention/retention_reference.h"
#include "hryky/stream/stream_indent_begin.h"
#include "hryky/stream/stream_indent_end.h"
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
namespace indent
{
	/// indicates a stream to indent all lines during the current scope.
	template <hryky_template_param>
	class Scope;

} // namespace indent
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief indicates a stream to indent all lines during the current scope.
 */
template <hryky_template_param>
class hryky::stream::indent::Scope :
	public retention::Reference<ValueT>
{
public :

	typedef Scope<hryky_template_arg>       this_type;
	typedef retention::Reference<ValueT>    retention_type;

	/// constructs with a stream.
	Scope(initializer_type value);

	/// destructor.
	~Scope();

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

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace stream
{
namespace indent
{
} // namespace indent
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructs with a stream.
 */
template <hryky_template_param>
hryky::stream::indent::Scope<hryky_template_arg>::Scope(initializer_type value)
	: retention_type(value)
{
	*this->get() << Begin();
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::stream::indent::Scope<hryky_template_arg>::~Scope()
{
	*this->get() << End();
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
void hryky::stream::indent::Scope<hryky_template_arg>::clear()
{
	this->retention_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::stream::indent::Scope<hryky_template_arg>::swap(this_type & src)
{
	this->retention_type::swap(src);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::stream::indent::Scope<hryky_template_arg>::write_to(StreamT & out) const
{
	return this->retention_type::write_to(out);
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace stream
{
namespace indent
{
} // namespace indent
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
#endif // STREAM_INDENT_SCOPE_H_20140216175648414
// end of file
