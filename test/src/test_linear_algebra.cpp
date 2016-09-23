/**
  @file     test_linear_algebra.cpp
  @brief    tests linear_algebra module.
  @author   HRYKY
  @version  $Id: test_linear_algebra.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/linear_algebra.h"
#include "hryky/coord.h"
//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace hryky
{
namespace test
{
namespace
{
	// enretisters a test.
	class Test : testing::unit::Base
	{
	public:
		typedef testing::unit::Base base_type;
		typedef Test this_type;

		/// constructor.
		Test();

	private:
		Test(this_type const &);
		this_type & operator=(this_type const &);
		
		/// tests linear_algebra module.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "linear_algebra";

	/// tests row and column vector.
	template <
		template <typename, size_t> class ContainerT,
		typename ValueT,
		size_t Size
	>
	bool test_row_column(testing::Log & log, testing::Random & random);

} // namespace "anonymous"
} // namespace test
} // namespace hryky
namespace hryky
{
namespace test
{
namespace
{
//------------------------------------------------------------------------------
// public member functions of Test
//------------------------------------------------------------------------------
/**
  @brief constructor.
 */
Test::Test()
	: base_type(g_testname)
{
}
//------------------------------------------------------------------------------
// private member functions of Test
//------------------------------------------------------------------------------
/**
  @brief tests linear_algebra module.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	if (!test_row_column<coord::Cartesian, float, 2>(log, random)) {
		return false;
	}

	{
		typedef Matrix<coord::Cartesian, float, 2, 2> lhs_type;
		typedef Matrix<coord::Cartesian, float, 2, 1> rhs_type;
		typedef Matrix<coord::Cartesian, float, 2, 1> result_type;

		result_type const result = lhs_type() * rhs_type();
	}
	
	return true;
}
/**
  @brief tests row and column vector.
 */
template <
	template <typename, size_t> class ContainerT,
	typename ValueT,
	size_t Size
>
bool test_row_column(testing::Log &, testing::Random &)
{
	typedef RowVector<ContainerT, ValueT, Size> row_type;
	typedef ColumnVector<ContainerT, ValueT, Size> column_type;

	{
		row_type const row;
		column_type const column;

		// calculates an inner product by <row,column>
		{
			row_type::value_type const inner_product = row * column;
			(void)inner_product;
		}
		/**
		  generates a new column vector by multiplication between
		  matrix and column.
		 */
		{
			typedef Matrix<
				ContainerT, ValueT, 3, Size> lhs_type;
			typedef ColumnVector<
				ContainerT, ValueT, 3> result_type;
			result_type const result = lhs_type() * column;
		}
		/**
		  generates a matrix by multiplication between column and row.
		 */
		{
			Matrix<ContainerT, ValueT, Size, Size> const
				matrix = column * row;
		}
		/**
		  generates a new row vector by multiplication between row and
		  matrix
		 */
		{
			typedef Matrix<
				ContainerT, ValueT, Size, 3> rhs_type;
			typedef RowVector<
				ContainerT, ValueT, 3> result_type;
			
			result_type const result = row * rhs_type();
		}
	}

	// confirms whether the operations of base class remains.
	{
		column_type column;
		column + column_type();
		column - column_type();
		column += column_type();
		column -= column_type();
		
		row_type row;
		row + row_type();
		row - row_type();
		row += row_type();
		row -= row_type();
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
