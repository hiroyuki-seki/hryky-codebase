/**
  @file     clock_elapse.h
  @brief    measures an elapsed time.
  @author   HRYKY
  @version  $Id: clock_elapse.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef CLOCK_ELAPSE_H_20140712173138396
#define CLOCK_ELAPSE_H_20140712173138396
#include "hryky/clock/clock_common.h"
#include "hryky/with_swap.h"
#include "hryky/with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace clock
{
	/// measures an elapsed time.
	class Elapse;

} // namespace clock
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief measures an elapsed time.
 */
class hryky::clock::Elapse :
	public WithStreamOut<Elapse>,
	public WithSwap<Elapse>
{
public :

	typedef Elapse this_type;

	/// default constructor.
	Elapse();

	/// copy constructor.
	Elapse(this_type const &);

	/// move constructor.
	Elapse(this_type &&);

	/// destructor.
	~Elapse();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// retrieves the current elapsed time.
	duration_type operator()() const;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

private :

	time_point start_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace clock
{
} // namespace clock
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT &
hryky::clock::Elapse::write_to(StreamT & out) const
{
	out << chrono::fmilliseconds((*this)());
	
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
namespace clock
{
} // namespace clock
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // CLOCK_ELAPSE_H_20140712173138396
// end of file
