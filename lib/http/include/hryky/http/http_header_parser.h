/**
  @file         http_header_parser.h
  @brief        parses a text string of HTTP Message.
  @author       HRYKY
  @version      $Id: http_header_parser.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_PARSER_H_20130117231425635
#define HTTP_HEADER_PARSER_H_20130117231425635
#include "hryky/chrono.h"
#include "hryky/common.h"
#include "hryky/date.h"
#include "hryky/http/http_entity.h"
#include "hryky/http/http_header_accept_charset_content_entity.h"
#include "hryky/http/http_header_accept_charset_entity.h"
#include "hryky/http/http_header_accept_content_entity.h"
#include "hryky/http/http_header_accept_encoding_content_entity.h"
#include "hryky/http/http_header_accept_encoding_entity.h"
#include "hryky/http/http_header_accept_entity.h"
#include "hryky/http/http_header_accept_language_content_entity.h"
#include "hryky/http/http_header_accept_language_entity.h"
#include "hryky/http/http_header_cache_common.h"
#include "hryky/http/http_header_cache_control_entity.h"
#include "hryky/http/http_header_cache_directive_adapter.h"
#include "hryky/http/http_header_cache_directive_base.h"
#include "hryky/http/http_header_cache_directive_dispatcher_apply.h"
#include "hryky/http/http_header_comment_sequence.h"
#include "hryky/http/http_header_comment_string.h"
#include "hryky/http/http_header_connection_entity.h"
#include "hryky/http/http_header_content_length_entity.h"
#include "hryky/http/http_header_content_type_entity.h"
#include "hryky/http/http_header_date_entity.h"
#include "hryky/http/http_header_entity.h"
#include "hryky/http/http_header_field_adapter.h"
#include "hryky/http/http_header_field_base.h"
#include "hryky/http/http_header_field_common.h"
#include "hryky/http/http_header_field_entity.h"
#include "hryky/http/http_header_field_extension_entity.h"
#include "hryky/http/http_header_host_entity.h"
#include "hryky/http/http_header_location_entity.h"
#include "hryky/http/http_header_product_comment_base.h"
#include "hryky/http/http_header_product_comment_dispatcher_apply.h"
#include "hryky/http/http_header_product_comment_adapter.h"
#include "hryky/http/http_header_product_entity.h"
#include "hryky/http/http_header_server_entity.h"
#include "hryky/http/http_header_user_agent_entity.h"
#include "hryky/http/http_method_common.h"
#include "hryky/http/http_request_entity.h"
#include "hryky/http/http_request_line_entity.h"
#include "hryky/http/http_version_entity.h"
#include "hryky/ip.h"
#include "hryky/kind.h"
#include "hryky/parser.h"
#include "hryky/mempool/mempool_instantiate.h"
#include "hryky/shared_ptr.h"
#include "hryky/uri.h"
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
	/// parses a text string of HTTP Message.
	class Parser;

	typedef Parser parser_type;

namespace kmyacc
{
#include "hryky/http/http_header.y.h"
}

} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief parses a text string of HTTP Message.
 */
class hryky::http::header::Parser :
	public hryky::parser::Base<
		hryky::http::header::kmyacc::Parser<
			hryky::http::header::Parser> >,
	public WithStreamOut<Parser>,
	public WithSwap<Parser>
{
public :

	typedef Parser this_type;
	typedef hryky::parser::Base<kmyacc::Parser<this_type> > base_type;

	/// default constructor.
	Parser();

	/// copy constructor.
	Parser(this_type const &);

	/// move constructor.
	Parser(this_type && rhs);

	/// constructor with mempool.
	Parser(mempool_type const mempool);
	
	/// destructor.
	~Parser();

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

	/// creates a token which holds shared pointer.
	template <typename ValueT>
	token_type create_shared_ptr_token();

	/// creates a token which holds shared pointer.
	template <typename ValueT>
	token_type create_shared_ptr_token(ValueT * const ptr);

	/// creates a token which holds shared pointer.
	template <typename ValueT>
	token_type create_shared_ptr_token(ValueT const & ref);

	/// creates a token holding header field.
	template <typename ValueT>
	token_type create_field_token(ValueT const & src);

	/// creates a token holding cache directive.
	template <typename ValueT>
	token_type create_cache_directive_token(ValueT const & src);

	/// creates a token holding shared pointer.
	template <template <class> class AdapterT, typename ValueT>
	token_type create_adapter_token(ValueT const & src);

	/// assigns a destination to which the parsed result is stored.
	void entity(header_type * const src);
	
	/// retrieves the destination to which the parsed result is stored.
	header_type * entity();
	
	/// parses a token with checking the termination.
	result_type parse_token(
		token_type const & token, token_id_type const token_id);

protected :

private :

	header_type * entity_;
	uint32_t last_four_octets_;

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
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief creates a token which holds shared pointer.
 */
template <typename ValueT>
hryky::http::header::Parser::token_type
hryky::http::header::Parser::create_shared_ptr_token()
{
	return token_type(
		SharedPtr<ValueT, Null>(
			mempool::instantiate<ValueT>(this->mempool()).release(),
			this->mempool()),
		this->mempool());
}
/**
  @brief creates a token which holds shared pointer.
 */
template <typename ValueT>
hryky::http::header::Parser::token_type
hryky::http::header::Parser::create_shared_ptr_token(
	ValueT * const ptr)
{
	return token_type(
		SharedPtr<ValueT, Null>(ptr, this->mempool()),
		this->mempool());
}
/**
  @brief creates a token which holds shared pointer.
 */
template <typename ValueT>
hryky::http::header::Parser::token_type
hryky::http::header::Parser::create_shared_ptr_token(
	ValueT const & ref)
{
	return token_type(
		SharedPtr<ValueT, Null>(
			mempool::instantiate<ValueT>(this->mempool(), ref).release(),
			this->mempool()),
		this->mempool());
}
/**
  @brief creates a token holding header field.
 */
template <typename ValueT>
hryky::http::header::Parser::token_type
hryky::http::header::Parser::create_field_token(
	ValueT const & src)
{
	return this->create_adapter_token<
		header::field::Adapter>(src);
}
/**
  @brief creates a token holding cache directive.
 */
template <typename ValueT>
hryky::http::header::Parser::token_type 
hryky::http::header::Parser::create_cache_directive_token(
	ValueT const & src)
{
	return this->create_adapter_token<
		header::cache::directive::Adapter>(src);
}
/**
  @brief creates a token holding shared pointer.
 */
template <template <typename> class AdapterT, typename ValueT>
hryky::http::header::Parser::token_type
hryky::http::header::Parser::create_adapter_token(
	ValueT const & src)
{
	return token_type(
		SharedPtr<typename AdapterT<ValueT>::base_type::base_type, Null>(
			mempool::instantiate<AdapterT<ValueT> >(
				this->mempool(), src).release(),
			this->mempool()),
		this->mempool());
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::http::header::Parser::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << static_cast<base_type const>(*this);
	hryky_write_member(last_four_octets);

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
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_HEADER_PARSER_H_20130117231425635
// end of file
