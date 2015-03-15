/**
  @file     stream_indent_begin.h
  @brief    specifies the beginning of indent.
  @author   HRYKY
  @version  $Id: stream_indent_begin.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef STREAM_INDENT_BEGIN_H_20140216174814408
#define STREAM_INDENT_BEGIN_H_20140216174814408
#include "hryky/definition.h"
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
namespace stream
{
namespace indent
{
	/// specifies the beginning of indent.
	class Begin;

} // namespace indent
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief specifies the beginning of indent.
 */
class hryky::stream::indent::Begin :
	public WithStreamOut<Begin>,
	public WithSwap<Begin>
{
public :

	typedef Begin this_type;

	/// default constructor.
	Begin();

	/// copy constructor.
	Begin(this_type const &);

	/// move constructor.
	Begin(this_type &&);

	/// destructor.
	~Begin();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

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
namespace indent
{
} // namespace indent
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
inline
hryky::stream::indent::Begin::Begin()
{
}
/**
  @brief copy constructor.
 */
inline
hryky::stream::indent::Begin::Begin(this_type const &)
{
}
/**
  @brief move constructor.
 */
inline
hryky::stream::indent::Begin::Begin(this_type &&)
{
}
/**
  @brief destructor.
 */
inline
hryky::stream::indent::Begin::~Begin()
{
}
/**
  @brief releases the internal resources.
 */
inline
void hryky::stream::indent::Begin::clear()
{
}
/**
  @brief interchanges the each internal resources of two instances.
 */
inline
void hryky::stream::indent::Begin::swap(this_type &)
{
}
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::stream::indent::Begin::write_to(StreamT & out) const
{
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
namespace indent
{
} // namespace indent
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // STREAM_INDENT_BEGIN_H_20140216174814408
// end of file
