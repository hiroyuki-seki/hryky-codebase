/**
  @file         flow_control_common.h
  @brief        The common definitions to control the disposal of nodes.
  @author       HRYKY
  @version      $Id: flow_control_common.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef FLOW_CONTROL_COMMON_H_20130324012601726
#define FLOW_CONTROL_COMMON_H_20130324012601726
#include "hryky/kind.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace flow
{
namespace control
{
	struct Kind
	{
		enum Raw
		{
			next,
			again,
			abort,
			num,
		};
	};
	typedef hryky::Kind<Kind> kind_type;
	
} // namespace control

// The syntax sugar for execution of the succeeding node.
control::Kind::Raw const next = control::Kind::next;

// The syntax sugar for repetition of the current node.
control::Kind::Raw const again = control::Kind::again;

} // namespace flow
} // namespace hryky
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace flow
{
namespace control
{
} // namespace control
} // namespace flow
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // FLOW_CONTROL_COMMON_H_20130324012601726
// end of file
