/**
  @file     gcd.h
  @brief    computes the greatest common divisor (G.C.D.) by Euclidean algorithm.
  @author   HRYKY
  @version  $Id: gcd.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef GCD_H_20130513165235369
#define GCD_H_20130513165235369
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	int Lhs, int Rhs
#define hryky_template_arg \
	Lhs, Rhs
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// calculates the greatest common divisor at compile time.
	template <hryky_template_param>
	class Gcd;

	/// normalizes the sign of term.
	template <
		hryky_template_param,
		bool LhsIsNegative = (0 > Lhs),
		bool RhsIsNegative = (0 > Rhs)
	>
	class GcdUnsigned;

	/// calculates the greatest common divisor by Euclidean algorithm.
	template <hryky_template_param>
	class GcdRaw;

} // namespace hryky
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief calculates the greatest common divisor at compile time.
 */
template <hryky_template_param>
class hryky::Gcd
{
public :
	static_assert(Lhs != 0, "LHS of G.C.D. must not be zero.");
	static_assert(Rhs != 0, "RHS of G.C.D. must not be zero.");
	
	static int const value = GcdUnsigned<Lhs, Rhs>::value;
};
/**
  @brief normalizes the sign of term.
 */
template <hryky_template_param, bool LhsIsNegative, bool RhsIsNegative>
class hryky::GcdUnsigned
{
public :
	static int const value = GcdRaw<Lhs, Rhs>::value;
};
/**
  @brief calculates the greatest common divisor by Euclidean algorithm.
 */
template <hryky_template_param>
class hryky::GcdRaw
{
public :
	static int const value = GcdRaw<Rhs, Lhs % Rhs>::value;
};
//------------------------------------------------------------------------------
// class specialization
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief inverses the signs of LHS and RHS.
 */
template <hryky_template_param>
class GcdUnsigned<Lhs, Rhs, true, true>
{
public :
	static int const value = GcdRaw<-Lhs, -Rhs>::value;
};
/**
  @brief inverses the sign of LHS.
 */
template <hryky_template_param>
class GcdUnsigned<Lhs, Rhs, true, false>
{
public :
	static int const value = GcdRaw<-Lhs, Rhs>::value;
};
/**
  @brief inverses the sign of RHS.
 */
template <hryky_template_param>
class GcdUnsigned<Lhs, Rhs, false, true>
{
public :
	static int const value = GcdRaw<Lhs, -Rhs>::value;
};
/**
  @brief solves the G.C.D.
 */
template <int Lhs>
class GcdRaw<Lhs, 0>
{
public :
	static int const value = Lhs;
};
} // namespace hryky
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
	/// computes the greatest common divisor (G.C.D.) by Euclidean algorithm.
	template <typename ValueT>
	ValueT gcd(ValueT const lhs, ValueT const rhs);

	/**
	  computes the G.C.D. under the assumption of the vaild magnitude
	  relationship.

	  lhs must be greater than rhs.
	 */
	template <typename ValueT>
	ValueT gcd_raw(ValueT const lhs, ValueT const rhs);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief computes the greatest common divisor (G.C.D.) by Euclidean algorithm.
 */
template <typename ValueT>
ValueT hryky::gcd(ValueT const lhs, ValueT const rhs)
{
	return lhs > rhs ? gcd_raw(lhs, rhs) : gcd_raw(rhs, lhs);
}
/**
  @brief computes the G.C.D. under the assumption of the vaild magnitude
    relationship.
 */
template <typename ValueT>
ValueT hryky::gcd_raw(ValueT const lhs, ValueT const rhs)
{
	return 0 == rhs ? lhs : gcd_raw(rhs, lhs % rhs);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // GCD_H_20130513165235369
// end of file
