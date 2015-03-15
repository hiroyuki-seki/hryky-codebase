/**
  @file     stream_array_end.h
  @brief    indicates the end of array.
  @author   HRYKY
  @version  $Id: stream_array_end.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef STREAM_ARRAY_END_H_20140208182251432
#define STREAM_ARRAY_END_H_20140208182251432
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
namespace array
{
	/// indicates the end of array.
	class End;

} // namespace array
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief indicates the end of array.
 */
class hryky::stream::array::End :
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
namespace array
{
} // namespace array
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
inline
hryky::stream::array::End::End()
{
}
/**
  @brief copy constructor.
 */
inline
hryky::stream::array::End::End(this_type const &)
{
}
/**
  @brief move constructor.
 */
inline
hryky::stream::array::End::End(this_type &&)
{
}
/**
  @brief destructor.
 */
inline
hryky::stream::array::End::~End()
{
}
/**
  @brief releases the internal resources.
 */
inline
void hryky::stream::array::End::clear()
{
}
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::stream::array::End::write_to(StreamT & out) const
{
	out << "]";
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
inline
void hryky::stream::array::End::swap(this_type &)
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
namespace array
{
} // namespace array
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // STREAM_ARRAY_END_H_20140208182251432
// end of file
