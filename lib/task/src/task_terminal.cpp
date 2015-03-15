/**
  @file     task_terminal.cpp
  @brief    receives the completion of a conveyer.
  @author   HRYKY
  @version  $Id: task_terminal.cpp 370 2014-07-21 16:00:02Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/task/task_terminal.h"
#include "hryky/task/task_conveyer.h"
#include "hryky/mempool/mempool_instantiate.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace task
{
namespace
{
} // namespace "anonymous"
} // namespace task
} // namespace hryky
//------------------------------------------------------------------------------
// static variable
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// function prototype
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
hryky::task::Terminal::Terminal()
	: actives_()
{
}
/**
  @brief destructor.
 */
hryky::task::Terminal::~Terminal()
{
}
/**
  @brief activates a concurrent unit.
 */
void hryky::task::Terminal::activate(Conveyer & conveyer)
{
	this->actives_.acquire();
	conveyer.terminal(this);
}
/**
  @brief inactivates the concurrent unit.
 */
void hryky::task::Terminal::inactivate(Conveyer & conveyer)
{
	conveyer.terminal(hryky_nullptr);
	this->actives_.restore();
}
/**
  @brief waits until the all conveyers are completed.
 */
bool hryky::task::Terminal::join(duration_type const & duration)
{
	return this->actives_.join(duration);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace task
{
namespace
{
} // namespace "anonymous"
} // namespace task
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
