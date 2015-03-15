/**
  @file         http_header_cache_directive_field.h
  @brief        retains 'field-name's of cache-directive.
  @author       HRYKY
  @version      $Id: http_header_cache_directive_field.h 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_CACHE_DIRECTIVE_FIELD_H_20130108220900589
#define HTTP_HEADER_CACHE_DIRECTIVE_FIELD_H_20130108220900589
#include "hryky/http/http_header_cache_directive_common.h"
#include "hryky/http/http_header_field_common.h"
#include "hryky/mempool/mempool_base.h"
#include "hryky/vector.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
namespace header
{
namespace cache
{
namespace directive
{
	/// retains 'field-name's of cache-directive.
	class Field;

	typedef Field field_type;

} // namespace directive
} // namespace cache
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains 'field-name's of cache-directive.
 */
class hryky::http::header::cache::directive::Field :
	public WithStreamOut<Field>,
	public WithSwap<Field>
{
public :

	typedef Field this_type;
	typedef Vector<header::field::kind_type> fields_type;

	/// default constructor.
	Field();

	/// constructs with kind and mempool.
	Field(Kind::Raw const kind, mempool_type const mempool);

	/// copy constructor.
	Field(this_type const &);

	/// move constructor.
	Field(this_type && rhs);

	/// constructor.
	Field(mempool_type const mempool);

	/// constructor with a kind of directive and an array of field-names.
	Field(Kind::Raw const kind, fields_type const & fields);

	/// destructor.
	~Field();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the kind of directive.
	kind_type const & kind() const;

	/// retrieves the beginning of the array of field-names.
	fields_type::const_iterator begin() const;

	/// retrieves the end of the array of field-names.
	fields_type::const_iterator end() const;

protected :

private :

	kind_type   kind_;
	fields_type fields_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
namespace header
{
namespace cache
{
namespace directive
{
} // namespace directive
} // namespace cache
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::http::header::cache::directive::Field::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(kind);
	hryky_write_member(fields);
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
namespace http
{
namespace header
{
namespace cache
{
namespace directive
{
} // namespace directive
} // namespace cache
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_CACHE_DIRECTIVE_FIELD_H_20130108220900589
// end of file
