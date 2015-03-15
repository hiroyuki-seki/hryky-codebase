/**
  @file     stream_array_begin.h
  @brief    indicates the beginning of array.
  @author   HRYKY
  @version  $Id: stream_array_begin.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef STREAM_ARRAY_BEGIN_H_20140208182144431
#define STREAM_ARRAY_BEGIN_H_20140208182144431
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
	/// indicates the beginning of array.
	class Begin;

} // namespace array
} // namespace stream
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief indicates the beginning of array.
 */
class hryky::stream::array::Begin :
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
hryky::stream::array::Begin::Begin()
{
}
/**
  @brief copy constructor.
 */
inline
hryky::stream::array::Begin::Begin(this_type const &)
{
}
/**
  @brief move constructor.
 */
inline
hryky::stream::array::Begin::Begin(this_type &&)
{
}
/**
  @brief destructor.
 */
inline
hryky::stream::array::Begin::~Begin()
{
}
/**
  @brief releases the internal resources.
 */
inline
void hryky::stream::array::Begin::clear()
{
}
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::stream::array::Begin::write_to(StreamT & out) const
{
	out << "[";
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
inline
void hryky::stream::array::Begin::swap(this_type &)
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
#endif // STREAM_ARRAY_BEGIN_H_20140208182144431
// end of file
