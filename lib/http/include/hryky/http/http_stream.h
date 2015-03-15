/**
  @file         http_stream.h
  @brief        writes and writes HTTP Message.
  @author       HRYKY
  @version      $Id: http_stream.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef HTTP_STREAM_H_20120805080153001
#define HTTP_STREAM_H_20120805080153001
#include "hryky/mempool/mempool_base.h"
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
	/// writes and writes HTTP Message.
	class Stream;

} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief writes and writes HTTP Message.
 */
class hryky::http::Stream
{
public :

	typedef Stream              this_type;

protected :

	/// default constructor.
	Stream();

	/// constructor.
	explicit Stream(mempool_type const mempool);

	/// destructor.
	~Stream();

private :

	hryky_delete_this_copy_constructor(Stream);
	hryky_delete_this_copy_assign_op(Stream);
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
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
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_STREAM_H_20120805080153001
// end of file
