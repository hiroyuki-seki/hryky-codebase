/**
  @file     task_terminal.h
  @brief    receives the completion of a conveyer.
  @author   HRYKY
  @version  $Id: task_terminal.h 370 2014-07-21 16:00:02Z hryky.private@gmail.com $
 */
#ifndef TASK_TERMINAL_H_20130331214052570
#define TASK_TERMINAL_H_20130331214052570
#include "hryky/exclusion/exclusion_counter.h"
#include "hryky/without_copy.h"
#include "hryky/with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace task
{
	/// receives the completion of a conveyer.
	class Terminal;

	class Conveyer;

} // namespace task
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief receives the completion of a conveyer.
 */
class hryky::task::Terminal :
	public WithStreamOut<Terminal>,
	private WithoutCopy
{
public :

	typedef Terminal                    this_type;
	typedef exclusion::duration_type    duration_type;

	class AutoInactivate
	{
	public :
		typedef AutoInactivate this_type;
		
		AutoInactivate(Terminal & terminal, Conveyer & conveyer)
			: terminal_(terminal)
			  , conveyer_(conveyer)
			  , disable_()
		{}

		~AutoInactivate()
		{
			if (!this->disable_) {
				this->terminal_.inactivate(this->conveyer_);
			}
		}

		void disable()
		{
			this->disable_ = true;
		}

	private :
		hryky_delete_this_copy_constructor(AutoInactivate);
		hryky_delete_this_copy_assign_op(AutoInactivate);

		Terminal & terminal_;
		Conveyer & conveyer_;
		bool disable_;
	};

	/// default constructor.
	Terminal();

	/// constructor with the memory pool.
	Terminal(mempool::Ptr const & mempool);

	/// destructor.
	~Terminal();

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// activates a concurrent unit.
	void activate(Conveyer & conveyer);

	/// inactivates the concurrent unit.
	void inactivate(Conveyer & conveyer);

	/// waits until the all conveyers are completed.
	bool join(duration_type const & duration);

protected :

private :

	typedef exclusion::Counter<> counter_type;

	hryky_delete_this_copy_constructor(Terminal);
	hryky_delete_this_copy_assign_op(Terminal);

	counter_type actives_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace task
{
} // namespace task
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::task::Terminal::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << stream::denote("intrusive_ptr_trait")
		<< static_cast<intrusive_ptr_trait const>(*this);
	hryky_write_member(actives);

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
namespace task
{
} // namespace task
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // TASK_TERMINAL_H_20130331214052570
// end of file
