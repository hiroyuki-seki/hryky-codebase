/**
  @file         http_header_field_dispatcher_base.h
  @brief        base class to be dispatched the class derived from http::header::field::Base.
  @author       HRYKY
  @version      $Id: http_header_field_dispatcher_base.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef HTTP_HEADER_FIELD_DISPATCHER_BASE_H_20130106150940298
#define HTTP_HEADER_FIELD_DISPATCHER_BASE_H_20130106150940298
#include "hryky/http/http_header_accept_charset_entity.h"
#include "hryky/http/http_header_accept_encoding_entity.h"
#include "hryky/http/http_header_accept_entity.h"
#include "hryky/http/http_header_accept_language_entity.h"
#include "hryky/http/http_header_cache_control_entity.h"
#include "hryky/http/http_header_connection_entity.h"
#include "hryky/http/http_header_content_length_entity.h"
#include "hryky/http/http_header_content_type_entity.h"
#include "hryky/http/http_header_date_entity.h"
#include "hryky/http/http_header_expires_entity.h"
#include "hryky/http/http_header_field_extension_entity.h"
#include "hryky/http/http_header_host_entity.h"
#include "hryky/http/http_header_location_entity.h"
#include "hryky/http/http_header_server_entity.h"
#include "hryky/http/http_header_user_agent_entity.h"
#include "hryky/without_new.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_virtual_destructor
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
namespace field
{
namespace dispatcher
{
	/// base class to be dispatched the class derived from http::header::field::Base.
	class Base;

} // namespace dispatcher

typedef dispatcher::Base dispatcher_type;

} // namespace field
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief base class to be dispatched the class derived from http::header::field::Base.
 */
class hryky::http::header::field::dispatcher::Base :
	private WithoutNew
{
public :

	typedef Base this_type;

	/// dispatches http::header::accept_type.
	bool operator()(accept_type & src)
	{
		return this->on_accept(src);
	}

	/// dispatches http::header::accept::charset_type.
	bool operator()(accept::charset_type & src)
	{
		return this->on_accept_charset(src);
	}

	/// dispatches http::header::accept::encoding_type.
	bool operator()(accept::encoding_type & src)
	{
		return this->on_accept_encoding(src);
	}

	/// dispatches http::header::accept::language_type.
	bool operator()(accept::language_type & src)
	{
		return this->on_accept_language(src);
	}

	/// dispatches http::header::connection_type.
	bool operator()(connection_type & src)
	{
		return this->on_connection(src);
	}

	/// dispatches http::header::content::length_type.
	bool operator()(content::length_type & src)
	{
		return this->on_content_length(src);
	}

	/// dispatches http::header::content::type_type.
	bool operator()(content::type_type & src)
	{
		return this->on_content_type(src);
	}

	/// dispatches http::header::cache::control_type.
	bool operator()(cache::control_type & src)
	{
		return this->on_cache_control(src);
	}

	/// dispatches http::header::date_type.
	bool operator()(date_type & src)
	{
		return this->on_date(src);
	}

	/// dispatches http::header::expires_type.
	bool operator()(expires_type & src)
	{
		return this->on_expires(src);
	}

	/// dispatches http::header::field::extension_type.
	bool operator()(field::extension_type & src)
	{
		return this->on_field_extension(src);
	}

	/// dispatches http::header::host_type.
	bool operator()(host_type & src)
	{
		return this->on_host(src);
	}

	/// dispatches http::header::location_type.
	bool operator()(location_type & src)
	{
		return this->on_location(src);
	}

	/// dispatches http::header::user_agent_type.
	bool operator()(user_agent_type & src)
	{
		return this->on_user_agent(src);
	}

	/// dispatches http::header::server_type.
	bool operator()(server_type & src)
	{
		return this->on_server(src);
	}

protected :

	/// default constructor.
	Base();

	/// copy constructor.
	Base(this_type const &);

	/// move constructor.
	Base(this_type && rhs);

	/// destructor.
	~Base();

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

private :

	/// dispatches http::header::accept_type.
	virtual bool on_accept(accept_type &)
	{
		return true;
	}

	/// dispatches http::header::accept::charset_type.
	virtual bool on_accept_charset(accept::charset_type &)
	{
		return true;
	}

	/// dispatches http::header::accept::encoding_type.
	virtual bool on_accept_encoding(accept::encoding_type &)
	{
		return true;
	}

	/// dispatches http::header::accept::language_type.
	virtual bool on_accept_language(accept::language_type &)
	{
		return true;
	}

	/// dispatches http::header::connection_type.
	virtual bool on_connection(connection_type &)
	{
		return true;
	}

	/// dispatches http::header::content::length_type.
	virtual bool on_content_length(content::length_type &)
	{
		return true;
	}

	/// dispatches http::header::content::type_type.
	virtual bool on_content_type(content::type_type &)
	{
		return true;
	}

	/// dispatches http::header::cache::control_type.
	virtual bool on_cache_control(cache::control_type &)
	{
		return true;
	}

	/// dispatches http::header::date_type.
	virtual bool on_date(date_type &)
	{
		return true;
	}

	/// dispatches http::header::expires_type.
	virtual bool on_expires(expires_type &)
	{
		return true;
	}

	/// dispatches http::header::field::extension_type.
	virtual bool on_field_extension(field::extension_type &)
	{
		return true;
	}

	/// dispatches http::header::host_type.
	virtual bool on_host(host_type &)
	{
		return true;
	}

	/// dispatches http::header::location_type.
	virtual bool on_location(location_type &)
	{
		return true;
	}

	/// dispatches http::header::user_agent_type.
	virtual bool on_user_agent(user_agent_type &)
	{
		return true;
	}

	/// dispatches http::header::server_type.
	virtual bool on_server(server_type &)
	{
		return true;
	}
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
namespace field
{
namespace dispatcher
{
} // namespace dispatcher
} // namespace field
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
hryky::http::header::field::dispatcher::Base::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
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
namespace field
{
namespace dispatcher
{
} // namespace dispatcher
} // namespace field
} // namespace header
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // HTTP_HEADER_FIELD_DISPATCHER_BASE_H_20130106150940298
// end of file
