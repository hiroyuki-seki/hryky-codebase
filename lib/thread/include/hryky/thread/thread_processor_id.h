/**
  @file     thread_processor_id.h
  @brief    retains the valid id of processor.
  @author   HRYKY
  @version  $Id: thread_processor_id.h 335 2014-03-16 03:00:56Z hryky.private@gmail.com $
 */
#ifndef THREAD_PROCESSOR_ID_H_20140310142958270
#define THREAD_PROCESSOR_ID_H_20140310142958270
#include "hryky/thread/thread_common.h"
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
namespace thread
{
	/// retains the valid id of processor.
	class ProcessorId;

} // namespace thread
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the valid id of processor.
 */
class hryky::thread::ProcessorId :
	public WithStreamOut<ProcessorId>,
	public WithSwap<ProcessorId>
{
public :

	typedef ProcessorId this_type;
	typedef raw_processor_id_type raw_type;

	/// default constructor.
	ProcessorId();

	/// copy constructor.
	ProcessorId(this_type const &);

	/// move constructor.
	ProcessorId(this_type &&);

	/// destructor.
	~ProcessorId();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// rotates the internal value.
	this_type & operator++();

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// retrieves the raw value.
	raw_type raw() const;

protected :

private :

	static raw_type const size_;

	raw_type raw_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace thread
{
} // namespace thread
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::thread::ProcessorId::write_to(StreamT & out) const
{
	out << this->raw_;
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
namespace thread
{
} // namespace thread
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // THREAD_PROCESSOR_ID_H_20140310142958270
// end of file
