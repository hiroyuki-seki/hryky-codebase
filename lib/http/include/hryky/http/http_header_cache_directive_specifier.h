/**
  @file         http_header_cache_directive_specifier.h
  @brief        specifies the kind of cache directive of HTTP Header.
  @author       HRYKY
  @version      $Id: http_header_cache_directive_specifier.h 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_CACHE_DIRECTIVE_SPECIFIER_H_20130107233028646
#define HTTP_HEADER_CACHE_DIRECTIVE_SPECIFIER_H_20130107233028646
#include "hryky/http/http_header_cache_directive_common.h"
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
	/// specifies the kind of cache directive of HTTP Header.
	class Specifier;

typedef directive::Specifier specifier_type;

} // namespace directive

} // namespace cache
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief specifies the kind of cache directive of HTTP Header.
 */
class hryky::http::header::cache::directive::Specifier :
	public WithStreamOut<Specifier>,
	public WithSwap<Specifier>
{
public :

	typedef Specifier this_type;

	/// default constructor.
	Specifier();

	/// copy constructor.
	Specifier(this_type const &);

	/// move constructor.
	Specifier(this_type && rhs);

	/// constructor.
	Specifier(kind_type const & kind);

	/// destructor.
	~Specifier();

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

protected :

private :

	kind_type kind_;

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
hryky::http::header::cache::directive::Specifier::write_to(
	StreamT & out) const
{
	out << this->kind_;
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
#endif // HTTP_HEADER_CACHE_DIRECTIVE_SPECIFIER_H_20130107233028646
// end of file
