/**
  @file     shader_fshader.h
  @brief    creates a fragment shader.
  @author   HRYKY
  @version  $Id: shader_fshader.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_FSHADER_H_20140825172550392
#define SHADER_FSHADER_H_20140825172550392
#include "hryky/shader/shader_source.h"
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
	/// creates a fragment shader.
	class Fshader;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief creates a fragment shader.
 */
class hryky::shader::Fshader :
	public Source<Fshader>
{
public :

	typedef Source<Fshader> base_type;

	typedef Fshader this_type;

	/// default constructor.
	Fshader();

	/// copy constructor.
	Fshader(this_type const &);

	/// move constructor.
	Fshader(this_type &&);

	/// destructor.
	~Fshader();

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

protected :

private :

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
StreamT & hryky::shader::Fshader::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << stream::denote("Source<Fshader>") << *static_cast<Source<Fshader> const *>(this);
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
#endif // SHADER_FSHADER_H_20140825172550392
// end of file
