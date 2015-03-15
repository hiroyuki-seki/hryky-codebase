/**
  @file     shader_parameter.h
  @brief    qualifies a variable in regard to parameter of function.
  @author   HRYKY
  @version  $Id: shader_parameter.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_PARAMETER_H_20140823080136001
#define SHADER_PARAMETER_H_20140823080136001
#include "hryky/kind.h"
#include "hryky/shader/shader_with_code.h"
#include "hryky/with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
	/// qualifies a variable in regard to parameter of function.
	class Parameter;

	typedef Parameter parameter_type;

	class Coder;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief qualifies a variable in regard to parameter of function.
 */
class hryky::shader::Parameter :
	public WithCode<Parameter>,
	public WithStreamOut<Parameter>
{
public :

	struct Kind
	{
		enum Raw
		{
			none,
			in,
			out,
			inout,
			num,
		};
		static LiteralString<> const tokens[num];
	};
	typedef hryky::Kind<
		Kind, Kind::none, Kind::num, LiteralString<>, Kind::tokens>
			kind_type;

	typedef Parameter this_type;

	/// default constructor.
	Parameter();

	/// copy constructor.
	Parameter(this_type const &);

	/// move constructor.
	Parameter(this_type &&);

	/// destructor.
	~Parameter();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// writes out the Parameter Qualifier.
	Coder & code(Coder & coder) const;

protected :

private :

	kind_type kind_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::shader::Parameter::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
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
namespace shader
{
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // SHADER_PARAMETER_H_20140823080136001
// end of file
