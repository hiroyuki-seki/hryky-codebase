/**
  @file     symbolic_computation_matrix.h
  @brief    represents matrix as composition of symbols.
  @author   HRYKY
  @version  $Id: symbolic_computation_matrix.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef SYMBOLIC_COMPUTATION_MATRIX_H_20131110175940416
#define SYMBOLIC_COMPUTATION_MATRIX_H_20131110175940416
#include "hryky/symbolic_computation/symbolic_computation_vector.h"
#include "hryky/type_traits/value_type_of.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
	/// facilitates matrix having 2 rows and 2 columns.
	template <
		typename E11T, typename E12T, 
		typename E21T, typename E22T, 
		typename EvalT
	>
	class Matrix2x2;

	/// facilitates matrix having 3 rows and 3 columns.
	template <
		typename E11T, typename E12T, typename E13T,
		typename E21T, typename E22T, typename E23T,
		typename E31T, typename E32T, typename E33T,
		typename EvalT
	>
	class Matrix3x3;

	/// facilitates matrix having 4 rows and 4 columns.
	template <
		typename E11T, typename E12T, typename E13T, typename E14T,
		typename E21T, typename E22T, typename E23T, typename E24T,
		typename E31T, typename E32T, typename E33T, typename E34T,
		typename E41T, typename E42T, typename E43T, typename E44T,
		typename EvalT
	>
	class Matrix4x4;

} // namespace symbolic_computation
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief facilitates matrix having 2 rows and 2 columns.

   Although template parameters are row-major, the internal vectors are column-
  major.
 */
template <
	typename E11T, typename E12T, 
	typename E21T, typename E22T, 
	typename EvalT
>
class hryky::symbolic_computation::Matrix2x2 :
	public WithStreamOut<Matrix2x2<
		E11T, E12T, 
		E21T, E22T, 
		EvalT> >,
	public Evalable<Matrix2x2<
		E11T, E12T, 
		E21T, E22T, 
		EvalT>, EvalT>
{
private :
	typedef typename ValueTypeOf<EvalT>::type column_type;
	typedef
		V<V<E11T, V<E21T>, column_type>,
		V<V<E12T, V<E22T>, column_type>
	>, EvalT> impl;
public :
	typedef typename impl::type type;
};
/**
  @brief facilitates matrix having 3 rows and 3 columns.

   Although template parameters are row-major, the internal vectors are column-
  major.
 */
template <
	typename E11T, typename E12T, typename E13T,
	typename E21T, typename E22T, typename E23T,
	typename E31T, typename E32T, typename E33T,
	typename EvalT
>
class hryky::symbolic_computation::Matrix3x3 :
	public WithStreamOut<Matrix3x3<
		E11T, E12T, E13T,
		E21T, E22T, E23T,
		E31T, E32T, E33T,
		EvalT> >,
	public Evalable<Matrix3x3<
		E11T, E12T, E13T,
		E21T, E22T, E23T,
		E31T, E32T, E33T,
		EvalT>, EvalT>
{
private :
	typedef typename ValueTypeOf<EvalT>::type column_type;
	typedef
		V<V<E11T, V<E21T, V<E31T> >, column_type>,
		V<V<E12T, V<E22T, V<E32T> >, column_type>,
		V<V<E13T, V<E23T, V<E33T> >, column_type>
	> >, EvalT> impl;
public :
	typedef typename impl::type type;
};
/**
  @brief facilitates matrix having 3 rows and 3 columns.

   Although template parameters are row-major, the internal vectors are column-
  major.
 */
template <
	typename E11T, typename E12T, typename E13T, typename E14T,
	typename E21T, typename E22T, typename E23T, typename E24T,
	typename E31T, typename E32T, typename E33T, typename E34T,
	typename E41T, typename E42T, typename E43T, typename E44T,
	typename EvalT
>
class hryky::symbolic_computation::Matrix4x4 :
	public WithStreamOut<Matrix4x4<
		E11T, E12T, E13T, E14T,
		E21T, E22T, E23T, E24T,
		E31T, E32T, E33T, E34T,
		E41T, E42T, E43T, E44T,
		EvalT> >,
	public Evalable<Matrix4x4<
		E11T, E12T, E13T, E14T,
		E21T, E22T, E23T, E24T,
		E31T, E32T, E33T, E34T,
		E41T, E42T, E43T, E44T,
		EvalT>, EvalT>
{
private :
	typedef typename ValueTypeOf<EvalT>::type column_type;
	typedef
		V<V<E11T, V<E21T, V<E31T, V<E41T> > >, column_type>,
		V<V<E12T, V<E22T, V<E32T, V<E42T> > >, column_type>,
		V<V<E13T, V<E23T, V<E33T, V<E43T> > >, column_type>,
		V<V<E14T, V<E24T, V<E34T, V<E44T> > >, column_type>
	> > >, EvalT> impl;
public :
	typedef typename impl::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace symbolic_computation
{
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
#endif // SYMBOLIC_COMPUTATION_MATRIX_H_20131110175940416
// end of file
