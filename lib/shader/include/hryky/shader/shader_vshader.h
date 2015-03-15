/**
  @file     shader_vshader.h
  @brief    creates a source for vertex shader.
  @author   HRYKY
  @version  $Id: shader_vshader.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_VSHADER_H_20140825100247085
#define SHADER_VSHADER_H_20140825100247085
#include "hryky/shader/shader_source.h"
#include "hryky/shader/shader_variable_ptr.h"
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
	/// creates a source for vertex shader.
	class Vshader;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief creates a source for vertex shader.
 */
class hryky::shader::Vshader :
	public Source<Vshader>
{
public :

	typedef Vshader this_type;
	typedef Source<this_type> base_type;

	/// default constructor.
	Vshader();

	/// copy constructor.
	Vshader(this_type const &);

	/// move constructor.
	Vshader(this_type &&);

	/// destructor.
	~Vshader();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// creates the built-in variable gl_Position.
	VariablePtr<Vector<float, 4> > position() const;

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
StreamT &
hryky::shader::Vshader::write_to(StreamT & out) const
{
	return this->base_type::write_to(out);
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
#endif // SHADER_VSHADER_H_20140825100247085
// end of file
