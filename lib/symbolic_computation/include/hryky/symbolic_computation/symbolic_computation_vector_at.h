/**
  @file     symbolic_computation_vector_at.h
  @brief    retrieves the type at the specified position in vector.
  @author   HRYKY
  @version  $Id: symbolic_computation_vector_at.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_VECTOR_AT_H_20131111230035625
#define SYMBOLIC_COMPUTATION_VECTOR_AT_H_20131111230035625
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename VectorT, size_t Pos
#define hryky_template_arg \
	VectorT, Pos
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// retrieves the type at the specified position in vector.
	template <hryky_template_param>
	class VectorAt;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the type at the specified position in vector.
 */
template <typename VectorT, size_t Pos>
class hryky::symbolic_computation::VectorAt
{
private :
	typedef typename VectorT::type target;
public :
	typedef typename VectorAt<typename target::rest_type, Pos - 1>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
/**
  @brief finds the element at the specified position.
 */
template <typename VectorT>
class VectorAt<VectorT, 0>
{
private :
	typedef typename VectorT::type target;
public :
	typedef typename target::element_type type;
};
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
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
namespace symbolic_computation
{
} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SYMBOLIC_COMPUTATION_VECTOR_AT_H_20131111230035625
// end of file
