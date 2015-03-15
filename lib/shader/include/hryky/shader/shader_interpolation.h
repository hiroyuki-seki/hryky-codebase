/**
  @file     shader_interpolation.h
  @brief    qualifies a variable with the type of interpolation.
  @author   HRYKY
  @version  $Id: shader_interpolation.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_INTERPOLATION_H_20140821222553601
#define SHADER_INTERPOLATION_H_20140821222553601
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
	/// qualifies a variable with the type of interpolation.
	class Interpolation;

	typedef Interpolation interpolation_type;

	class Coder;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief qualifies a variable with the type of interpolation.
 */
class hryky::shader::Interpolation :
	public WithCode<Interpolation>,
	public WithStreamOut<Interpolation>
{
public :

	struct Kind
	{
		enum Raw
		{
			none,
			smooth,
			flat,
			num,
		};
		static LiteralString<> const tokens[num];
	};
	typedef hryky::Kind<
		Kind, Kind::none, Kind::num, LiteralString<>, Kind::tokens>
			kind_type;

	typedef Interpolation this_type;

	/// default constructor.
	Interpolation();

	/// creates an instance with the kind.
	Interpolation(kind_type const & kind);

	/// copy constructor.
	Interpolation(this_type const &);

	/// move constructor.
	Interpolation(this_type &&);

	/// destructor.
	~Interpolation();

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

	/// writes out the Interpolation Qualifier.
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
StreamT & hryky::shader::Interpolation::write_to(StreamT & out) const
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
#endif // SHADER_INTERPOLATION_H_20140821222553601
// end of file
