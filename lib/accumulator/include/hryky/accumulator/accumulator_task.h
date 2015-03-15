/**
  @file         accumulator_task.h
  @brief        A unit to accumulate values on the concurrent worker.
  @author       HRYKY
  @version      $Id: accumulator_task.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef ACCUMULATOR_TASK_H_20130325141232258
#define ACCUMULATOR_TASK_H_20130325141232258
#include "hryky/batch/batch_worker.h"
#include "hryky/clear.h"
#include "hryky/definition.h"
#include "hryky/std/std_numeric.h"
#include "hryky/type_traits/add_const_reference.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename InputIteratorT, typename ResultT
#define hryky_template_arg \
	InputIteratorT, ResultT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace accumulator
{
	/// A unit to accumulate values on the concurrent worker.
	template <hryky_template_param>
	class Task;

} // namespace accumulator
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief A unit to accumulate values on the concurrent worker.
 */
template <hryky_template_param>
class hryky::accumulator::Task :
	public WithStreamOut<Task<hryky_template_arg> >,
	public WithSwap<Task<hryky_template_arg> >
{
public :

	typedef Task<hryky_template_arg> this_type;
	typedef batch::Worker<this_type *> worker_type;

	/// default constructor.
	Task();

	/// constructor with the range of accumulation.
	Task(InputIteratorT begin, InputIteratorT end);

	/// copy constructor.
	Task(this_type const &);

	/// move constructor.
	Task(this_type &&);

	/// destructor.
	~Task();

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

	/// accumulates the values.
	void operator()(worker_type & worker);

	/// retrieves the result.
	typename AddConstReference<ResultT>::type result() const;

protected :

private :

	InputIteratorT begin_;
	InputIteratorT end_;
	ResultT result_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace accumulator
{
} // namespace accumulator
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::accumulator::Task<hryky_template_arg>::Task()
	: begin_()
	  , end_()
	  , result_()
{
}
/**
  @brief constructor with the range of accumulation.
 */
template <hryky_template_param>
hryky::accumulator::Task<hryky_template_arg>::Task(
	InputIteratorT begin, InputIteratorT end)
	: begin_(begin)
	  , end_(end)
	  , result_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::accumulator::Task<hryky_template_arg>::Task(this_type const & rhs)
	: hryky_copy_member(begin)
	  , hryky_copy_member(end)
	  , hryky_copy_member(result)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::accumulator::Task<hryky_template_arg>::Task(this_type && rhs)
	: hryky_move_member(begin)
	  , hryky_move_member(end)
	  , hryky_move_member(result)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::accumulator::Task<hryky_template_arg>::~Task()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::accumulator::Task<hryky_template_arg>::clear()
{
	hryky::clear(this->result_);
	hryky::clear(this->end_);
	hryky::clear(this->begin_);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::accumulator::Task<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(begin);
	hryky_write_member(end);
	hryky_write_member(result);
	
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::accumulator::Task<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(begin);
	hryky_swap_member(end);
	hryky_swap_member(result);
}
/**
  @brief accumulates the values.
 */
template <hryky_template_param>
void hryky::accumulator::Task<hryky_template_arg>::operator()(
	worker_type &)
{
	this->result_ = ::std::accumulate(this->begin_, this->end_, ResultT());
}
/**
  @brief retrieves the result.
 */
template <hryky_template_param>
typename hryky::AddConstReference<ResultT>::type
hryky::accumulator::Task<hryky_template_arg>::result() const
{
	return this->result_;
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
namespace accumulator
{

} // namespace accumulator
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // ACCUMULATOR_TASK_H_20130325141232258
// end of file
