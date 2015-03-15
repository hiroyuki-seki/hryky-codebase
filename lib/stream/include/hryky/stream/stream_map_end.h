/**
  @file     stream_map_end.h
  @brief    indicates the end of associative array.
  @author   HRYKY
  @version  $Id: stream_map_end.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef STREAM_MAP_END_H_20140208181210425
#define STREAM_MAP_END_H_20140208181210425
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
namespace map
{
	/// indicates the end of associative array.
	class End;

} // namespace map
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief indicates the end of associative array.
 */
class hryky::stream::map::End :
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
namespace map
{
} // namespace map
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
inline
hryky::stream::map::End::End()
{
}
/**
  @brief copy constructor.
 */
inline
hryky::stream::map::End::End(this_type const &)
{
}
/**
  @brief move constructor.
 */
inline
hryky::stream::map::End::End(this_type &&)
{
}
/**
  @brief destructor.
 */
inline
hryky::stream::map::End::~End()
{
}
/**
  @brief releases the internal resources.
 */
inline
void hryky::stream::map::End::clear()
{
}
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::stream::map::End::write_to(StreamT & out) const
{
	out << "}";
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
inline
void hryky::stream::map::End::swap(this_type &)
{
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
namespace map
{
} // namespace map
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // STREAM_MAP_END_H_20140208181210425
// end of file
