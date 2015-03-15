/**
  @file     stream_indent_end.h
  @brief    specifies the end of indent.
  @author   HRYKY
  @version  $Id: stream_indent_end.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef STREAM_INDENT_END_H_20140216175101410
#define STREAM_INDENT_END_H_20140216175101410
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
	/// specifies the end of indent.
	class End;

} // namespace indent
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief specifies the end of indent.
 */
class hryky::stream::indent::End :
	public WithStreamOut<End>,
	public WithSwap<End>
{
public :

	typedef End this_type;

	/// default constructor.
	End();

	/// copy constructor.
	End(this_type const &);

	/// move constructor.
	End(this_type &&);

	/// destructor.
	~End();

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
hryky::stream::indent::End::End()
{
}
/**
  @brief copy constructor.
 */
inline
hryky::stream::indent::End::End(this_type const &)
{
}
/**
  @brief move constructor.
 */
inline
hryky::stream::indent::End::End(this_type &&)
{
}
/**
  @brief destructor.
 */
inline
hryky::stream::indent::End::~End()
{
}
/**
  @brief releases the internal resources.
 */
inline
void hryky::stream::indent::End::clear()
{
}
/**
  @brief interchanges the each internal resources of two instances.
 */
inline
void hryky::stream::indent::End::swap(this_type &)
{
}
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::stream::indent::End::write_to(StreamT & out) const
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
#endif // STREAM_INDENT_END_H_20140216175101410
// end of file
