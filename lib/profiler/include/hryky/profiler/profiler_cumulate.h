/**
  @file         profiler_cumulate.h
  @brief        cumulates an elapsed time.
  @author       HRYKY
  @version      $Id: profiler_cumulate.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef PROFILER_CUMULATE_H_20111213230405627
#define PROFILER_CUMULATE_H_20111213230405627
#include "hryky/type_traits/add_reference.h"
#include "hryky/clock.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace profiler
{
	/// cumulates an elapsed time.
	template < typename DurationT >
	class Cumulate;
}
}
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief cumulates an elapsed time.
 */
template < typename DurationT = clock::duration_type>
class hryky::profiler::Cumulate
{
public :

	typedef hryky::profiler::Cumulate<DurationT>        this_type;
	typedef DurationT                                   value_type;
	typedef typename AddReference<DurationT>::type      reference;

	/// instance type.
	typedef Cumulate * instance_type;

	/// constructor.
	Cumulate(typename reference dest);

	/// destructor.
	~Cumulate();

protected :

private :

	hryky_delete_default_constructor(Cumulate);
	hryky_delete_this_copy_constructor(Cumulate);
	hryky_delete_this_copy_assign_op(Cumulate);

	reference           dest_;  ///< cumulated destination
	clock::time_point   start_; ///< The beginning of the measured interval.

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructor.
 */
template <typename DurationT>
hryky::profiler::Cumulate<DurationT>::Cumulate(reference dest)
	: dest_(dest)
	  , start_(clock::clock_type::now())
{
	return;
}
/**
  @brief destructor.
 */
template <typename DurationT>
hryky::profiler::Cumulate<DurationT>::~Cumulate()
{
	clock::duration_type const duration =
		clock::clock_type::now() - this->start_;

	this->dest_ += DurationT(duration);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
#endif // PROFILER_CUMULATE_H_20111213230405627
// end of file
