/**

  @file         neon_math_matrix.h
  @brief        operations of matrix by Neon.
  @since        2012-05-29T11:30:17+0900
  @author       HRYKY
  @version      $Id: neon_math_matrix.h 83 2012-07-17 16:04:24Z hryky.private@gmail.com $
 */
#ifndef NEON_MATH_MATRIX_H_20120529113017146
#define NEON_MATH_MATRIX_H_20120529113017146
#include <stdint.h>
//------------------------------------------------------------------------------
// macro definition
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace neon
{
namespace math
{
	/// operations of matrix by Neon.
	struct Matrix;

} // namespace math
} // namespace neon
} // namespace hryky
//------------------------------------------------------------------------------
// class declarations
//------------------------------------------------------------------------------
/**
  @brief        operations of matrix by Neon.
  @since        2012-05-29T11:30:17+0900

  @attention    the memory arrangement of elements is column-major.
 */
struct hryky::neon::math::Matrix
{
public :

	typedef Matrix this_type;///< self.

	/// tests hryky::neon::math::Matrix.
	static bool test();

	/// default constructor.
	Matrix();

	/// destructor.
	~Matrix();

	/// copy constructor.
	explicit Matrix(this_type const &);

	/// assignment operator.
	this_type & operator=(this_type const & rhs);

	/// fills the all members by zero.
	void clear();

	static size_t const rows_       = 4;
	static size_t const columns_    = 4;

	union
	{
		float units_[rows_ * columns_];
		float row_column_[columns_][rows_];

		struct
		{
			float u11_, u21_, u31_, u41_;
			float u12_, u22_, u32_, u42_;
			float u13_, u23_, u33_, u43_;
			float u14_, u24_, u34_, u44_;
		};
	};

};
//------------------------------------------------------------------------------
// class specializations
//------------------------------------------------------------------------------
namespace hryky
{
namespace neon
{
namespace math
{
} // namespace math
} // namespace neon
} // namespace hryky
//------------------------------------------------------------------------------
// public member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// global function prototypes
//------------------------------------------------------------------------------
namespace hryky
{
namespace neon
{
namespace math
{
} // namespace math
} // namespace neon
} // namespace hryky
//------------------------------------------------------------------------------
// global function definitions
//------------------------------------------------------------------------------
#endif // NEON_MATH_MATRIX_H_20120529113017146
// end of file
