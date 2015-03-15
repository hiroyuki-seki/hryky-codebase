/**
  @file     shader_precision.h
  @brief    qualifies a variable in regard to its precision.
  @author   HRYKY
  @version  $Id: shader_precision.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_PRECISION_H_20140823085354037
#define SHADER_PRECISION_H_20140823085354037
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
	/// qualifies a variable in regard to its precision.
	class Precision;

	typedef Precision precision_type;

	class Coder;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief qualifies a variable in regard to its precision.
 */
class hryky::shader::Precision :
	public WithCode<Precision>,
	public WithStreamOut<Precision>
{
public :

	struct Kind
	{
		enum Raw
		{
			highp,
			mediump,
			lowp,
			num,
		};
		static LiteralString<> const tokens[num];
	};
	typedef hryky::Kind<
		Kind, Kind::highp, Kind::num, LiteralString<>, Kind::tokens>
			kind_type;

	typedef Precision this_type;

	/// default constructor.
	Precision();

	/// copy constructor.
	Precision(this_type const &);

	/// move constructor.
	Precision(this_type &&);

	/// destructor.
	~Precision();

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

	/// writes out the Precision Qualifier.
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
StreamT & hryky::shader::Precision::write_to(StreamT & out) const
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
#endif // SHADER_PRECISION_H_20140823085354037
// end of file
