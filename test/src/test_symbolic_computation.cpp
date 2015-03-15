/**
  @file         test_symbolic_computation.cpp
  @brief        tests for retantion of arbitrary types.
  @author       HRYKY
  @version      $Id: test_symbolic_computation.cpp 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/symbolic_computation.h"
#include "hryky/coord.h"
#include "hryky/linear_algebra.h"
#include "hryky/unroll.h"
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
	namespace sc = hryky::symbolic_computation;

	typedef float eval_type;
	typedef sc::Integer<eval_type, 0> zero;
	typedef sc::Integer<eval_type, 1> one;
	typedef sc::Integer<eval_type, 2> two;
	typedef sc::Integer<eval_type, 3> three;
	typedef sc::Integer<eval_type, 4> four;
	typedef sc::Integer<eval_type, 5> five;
	typedef sc::Integer<eval_type, 6> six;
	typedef sc::Integer<eval_type, 7> seven;
	typedef sc::Integer<eval_type, 8> eight;
	typedef sc::Integer<eval_type, 9> nine;
	typedef sc::Integer<eval_type, 10> ten;

	typedef sc::Variable<eval_type, 0, 'x'> x;
	typedef sc::Variable<eval_type, 1, 'y'> y;
	typedef sc::Variable<eval_type, 2, 'z'> z;
	typedef sc::Variable<eval_type, 0xFFFF, 'k'> k;

	typedef sc::Complement<x> c_x;
	typedef sc::Complement<y> c_y;
	typedef sc::Complement<z> c_z;

	typedef sc::Fraction<eval_type, 1, 2> half;
	typedef sc::Fraction<eval_type, 1, 3> third;
	typedef sc::Fraction<eval_type, 1, 4> quarter;
	typedef sc::Fraction<eval_type, 1, 5> fifth;
	typedef sc::Fraction<eval_type, 1, 6> sixth;
	typedef sc::Fraction<eval_type, 1, 7> seventh;
	typedef sc::Fraction<eval_type, 1, 8> eighth;
	typedef sc::Fraction<eval_type, 1, 9> ninth;
	typedef sc::Fraction<eval_type, 1, 10> tenth;

	typedef sc::Pi<eval_type> pi;

	typedef ostream::String<String<> > os_type;

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
		
		/// tests for retantion of arbitrary types.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "symbolic_computation";

	/// confirms which the answer is correct.
	template <typename FunctionT, typename ParametersT>
	bool verify(
		FunctionT const function,
		ParametersT const & parameters,
		typename FunctionT::eval_type const & correct,
		testing::Log & log);

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
  @brief tests for retantion of arbitrary types.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

#if 1
	// 1/2 + 3 * 1/3
	{
		typedef sc::Add<
			half, sc::Mul<three, third> > function;

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct = 1.0f / 2.0f + 3.0f * 1.0f / 3.0f;

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// x + y + z + 0.5
	{
		typedef sc::Add<
			sc::Add<
				sc::Add<x, y>, z>, half> function;

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			parameters[0] + parameters[1] + parameters[2] + 0.5f;

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// x + 0 + z + 0.5
	{
		typedef sc::Add<
			sc::Add<
				sc::Add<x, zero>, z>, half> function;

		static_assert(
			IsSame<
				sc::Add<sc::Add<x, z>, half>::type,
				sc::Simplify<function>::type
			>::type::value,
			"x + 0 + z + 0.5 => x + z + 0.5");

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			parameters[0] + parameters[2] + 0.5f;

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// 0 + y + z + 0.5
	{
		typedef sc::Add<
			sc::Add<
				sc::Add<zero, y>, z>, half> function;

		static_assert(
			IsSame<
				sc::Add<sc::Add<y, z>, half>::type,
				sc::Simplify<function>::type
			>::type::value,
			"0 + y + z + 0.5 => y + z + 0.5");

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			parameters[1] + parameters[2] + 0.5f;

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// x + y + 0 + 0.5
	{
		typedef sc::Add<
			sc::Add<
				sc::Add<x, y>, zero>, half> function;

		static_assert(
			IsSame<
				sc::Add<sc::Add<x, y>, half>::type,
				sc::Simplify<function>::type
			>::type::value,
			"x + y + 0 + 0.5 => x + y + 0.5");

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			parameters[0] + parameters[1] + 0.5f;

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// x + y - x + 0.5
	{
		typedef sc::Add<
			sc::Sub<
				sc::Add<x, y>, x>, half> function;

		static_assert(
			IsSame<sc::Simplify<sc::Sub<x, x> >::type, zero>::type::value,
			"x - x => 0");

		static_assert(
			IsSame<
				sc::Simplify<sc::Sub<sc::Add<x, y>, x> >::type,
				y::type
			>::type::value,
			"x + y - x => y");

		static_assert(
			IsSame<
				sc::Add<y, half>::type,
				sc::Simplify<function>::type
			>::type::value,
			"x + y - x + 0.5 => y + 0.5");

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			parameters[0] + parameters[1] - parameters[0] + 0.5f;

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// x * y * z * 0.5
	{
		typedef sc::Mul<
			sc::Mul<
				sc::Mul<x, y>, z>, half> function;

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			parameters[0] * parameters[1] * parameters[2] * 0.5f;

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// x / (y / z + 0.5)
	{
		typedef sc::Divide<
			x,
			sc::Add<sc::Divide<y, z>, half>
			> function;

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			parameters[0] / (parameters[1] / parameters[2] + 0.5f);

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// x + (-x)
	{
		typedef sc::Add<x, c_x> function;

		static_assert(
			IsSame<
				sc::Integer<eval_type, 0>::type,
				sc::Simplify<function>::type
			>::type::value,
			"x+(-x) => 0");

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			parameters[0] - parameters[0];

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}
	
	// x + (-x) + z + 0.5
	{
		typedef sc::Add<
			sc::Add<
				sc::Add<x, c_x>, z>, half> function;

		static_assert(
			IsSame<
				sc::Add<z,half>::type,
				sc::Simplify<function>::type
			>::type::value,
			"x+(-x)+z+0.5 => z+0.5");

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			parameters[0] - parameters[0] + parameters[2] + 0.5f;

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}
	
	// x - x + z + 0.5
	{
		typedef sc::Add<
			sc::Add<
				sc::Sub<x, x>, z>, half> function;

		static_assert(
			IsSame<
				sc::Add<z,half>::type,
				sc::Simplify<function>::type
			>::type::value,
			"x-x+z+0.5 => z+0.5");

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			parameters[0] - parameters[0] + parameters[2] + 0.5f;

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// y ^ 3 + 0.5
	{
		typedef sc::Add<
			sc::IntPower<y, 3>, half> function;
		
		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			parameters[1] * parameters[1] * parameters[1] + 0.5f;

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}
	
	// y * y * y + 0.5
	{
		typedef sc::Add<
			sc::Mul<
				sc::Mul<y, y>, y>, half> function;

		static_assert(
			IsSame<
				sc::Simplify<sc::Mul<y,y> >::type,
				sc::IntPower<y,2>::type
			>::type::value,
			"y*y => y^2");

		static_assert(
			IsSame<
				sc::Simplify<sc::Mul<sc::Mul<y,y>,y> >::type,
				sc::IntPower<y,3>::type
			>::type::value,
			"y*y*y => y^3");

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			parameters[1] * parameters[1] * parameters[1] + 0.5f;

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}
	
	// (y / y) * y + 0.5
	{
		typedef sc::Add<
			sc::Mul<
				sc::Divide<y, y>, y>, half> function;

		static_assert(
			IsSame<
				sc::Simplify<function>::type,
				sc::Add<y,half>::type
			>::type::value,
			"(y/y)*y+0.5 => y+0.5");

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			(parameters[1] / parameters[1]) * parameters[1] + 0.5f;

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}
	
	// (y * y) / y + 0.5
	{
		typedef sc::Add<
			sc::Divide<
				sc::Mul<y, y>, y>, half> function;

		static_assert(
			IsSame<
				sc::Simplify<function>::type,
				sc::Add<y,half>::type
			>::type::value,
			"(y*y)/y+0.5 => y+0.5");

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			(parameters[1] * parameters[1]) / parameters[1] + 0.5f;

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// (2 + (2 + 1)) - ((y / y) + 2) + 0.5
	{
		typedef sc::Add<
			sc::Sub<
				sc::Add<two, sc::Add<two, one> >,
				sc::Add<
					sc::Divide<y, y>, two> >, half> function;

		static_assert(
			IsSame<
				sc::Simplify<function>::type,
				sc::Fraction<eval_type,5,2>::type
			>::type::value,
			"(2+(2+1))-((y/y)+2)+(1/2) => (5/2)");

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			(2.0f + (2.0f + 1.0f)) - ((parameters[1] / parameters[1]) + 2.0f) + 0.5f;

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}
	
	// 2 * (2 + 1) - (y / y) * 2 + 0.5
	{
		typedef sc::Add<
			sc::Sub<
				sc::Mul<two, sc::Add<two, one> >,
				sc::Mul<
					sc::Divide<y, y>, two> >, half> function;

		static_assert(
			IsSame<
				sc::Simplify<function>::type,
				sc::Fraction<eval_type,9,2>::type
			>::type::value,
			"(2*(2+1))-((y/y)*2)+(1/2) => (9/2)");

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			2.0f * (2.0f + 1.0f) - (parameters[1] / parameters[1]) * 2.0f + 0.5f;

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}
	
	// ((((2 + x) + 3) + y) + 2) + 0.5
	{
		typedef sc::Add<
			sc::Add<
				sc::Add<
					sc::Add<
						sc::Add<two, x>,
						three>, y>, two>, half> function;

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			2.0f + parameters[0] + 3.0f + parameters[1] + 2.0f + 0.5f;

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}
	
	// ((((2 - x) - 3) - y) - 2) + 0.5
	{
		typedef sc::Add<
			sc::Sub<
				sc::Sub<
					sc::Sub<
						sc::Sub<two, x>,
						three>, y>, two>, half> function;

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			2.0f - parameters[0] - 3.0f - parameters[1] - 2.0f + 0.5f;

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}
	
	// 2 * y * 3 * y * 2 + 0.5
	{
		typedef sc::Add<
			sc::Mul<
				sc::Mul<
					sc::Mul<
						sc::Mul<two, y>,
						three>, y>, two>, half> function;

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			2.0f * parameters[1] * 3.0f * parameters[1] * 2.0f + 0.5f;

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}
	
	// 2 / y / 3 / y / 2 + 0.5
	{
		typedef sc::Add<
			sc::Divide<
				sc::Divide<
					sc::Divide<
						sc::Divide<two, y>,
						three>, y>, two>, half> function;

		static_assert(
			IsSame<
				sc::Simplify<sc::IntPower<sc::IntPower<y,-1>,2> >::type,
				sc::IntPower<y,-2>::type
			>::type::value,
			"(y^-1)^2 => y^-2");

		static_assert(
			IsSame<
				sc::Simplify<sc::Divide<sc::Divide<one,y>,y> >::type,
				sc::Divide<one, sc::IntPower<y,2> >::type
			>::type::value,
			"1/y/y => 1/y^2");
		

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			2.0f / (parameters[1] * 3.0f * parameters[1] * 2.0f) + 0.5f;

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}
	
	// 2 * (3 * y + 3) / y / 2 + 0.5
	{
		typedef sc::Add<sc::Mul<three, y>, three>
			op_3y_3;
		typedef sc::Mul<two, op_3y_3>
			op_2op_3y_3;
		
		typedef sc::Add<
			sc::Divide<
				sc::Divide<op_2op_3y_3, y>, two>, half> function;

		static_assert(
			sc::Dividable<three, three>::value,
			"3/3 is dividable");
		static_assert(
			sc::Dividable<sc::Mul<three, y>, three>::value,
			"3*y/3 is dividable");
		static_assert(
			sc::Dividable<op_3y_3, three>::value,
			"(3*y+3)/3 is dividable");

		static_assert(
			IsSame<
				sc::Simplify<op_2op_3y_3>::type,
				sc::Mul<six, sc::Add<y, one> >::type
			>::type::value,
			"2*(3*y+3) => 6*y+6");
		
		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			2.0f * (3.0f * parameters[1] + 3.0f) / parameters[1] / 2.0f + 0.5f;

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}
	
	// 2 * (3 * y - 3) / y / 2 + 0.5
	{
		typedef sc::Sub<sc::Mul<three, y>, three>
			op_3y_n3;
		typedef sc::Mul<two, op_3y_n3>
			op_2op_3y_n3;
		
		typedef sc::Add<
			sc::Divide<
				sc::Divide<op_2op_3y_n3, y>, two>, half> function;

		static_assert(
			IsSame<
				sc::Simplify<op_2op_3y_n3>::type,
				sc::Mul<six, sc::Sub<y, one> >::type
			>::type::value,
			"2*(3*y-3) => 6*(y-1)");
		
		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			2.0f * (3.0f * parameters[1] - 3.0f) / parameters[1] / 2.0f + 0.5f;

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}
	
	// 2 * (3 * y + x * y) / y / 2 + 0.5
	{
		typedef sc::Add<
			sc::Mul<three, y>, sc::Mul<x, y> >
				op_3y_xy;
		typedef sc::Mul<two, op_3y_xy>
			op_2op_3y_xy;
		
		typedef sc::Add<
			sc::Divide<
				sc::Divide<op_2op_3y_xy, y>, two>, half> function;

		static_assert(
			IsSame<
				sc::Simplify<sc::Divide<op_3y_xy, y> >::type,
				sc::Add<three, x>::type
			>::type::value,
			"(3*y+x*y)/y => 3+x");
		
		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct = (
			2.0f * (3.0f * parameters[1] + parameters[0] * parameters[1]) /
			parameters[1] / 2.0f + 0.5f);

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// ((3 + (z * (3 + y))) + (z * (3 + y)))
	{
		typedef sc::Add<
			sc::Add<three, sc::Mul<z, sc::Add<three, y> > >,
			sc::Mul<z, sc::Add<three, y> >
		>::type function;

		typedef sc::Simplify<function> simplified;
	}

	// ln(1)
	{
		typedef sc::Ln<
			sc::Integer<eval_type, 1> > function;

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct = hryky::ln(1.0f);
		
		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// y^y
	{
		typedef sc::Power<y, y> function;

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct = hryky::pow(parameters[1], parameters[1]);
		
		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}
	
	// e^y
	{
		typedef sc::Power<sc::Napier<eval_type>, y> function;

		static_assert(
			IsSame<
				sc::Simplify<sc::Add<
					sc::Mul<zero, sc::Napier<eval_type> >,
					sc::Mul<zero, y>
				> >::type,
				zero
			>::type::value,
			"(0*e)+(0*y) == 0");
		static_assert(
			IsSame<
				sc::Simplify<sc::Mul<zero, x> >::type,
				zero
			>::type::value,
			"(0*x) == 0");

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct = hryky::exp(parameters[1]);
		
		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// (x, y, z)
	{
		typedef sc::Vector3<x, y, z, coord::Cartesian3<eval_type> >
			function;

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		coord::Cartesian3<eval_type> const correct(
			parameters[0], parameters[1], parameters[2]);
		
		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// (x, y, z) + (y, x, z)
	{
		typedef coord::Cartesian3<eval_type> vector_type;
		typedef sc::Add<
			sc::Vector3<x, y, z, vector_type>,
			sc::Vector3<y, x, z, vector_type> > function;

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		vector_type const correct = (
			vector_type(parameters[0], parameters[1], parameters[2]) +
			vector_type(parameters[1], parameters[0], parameters[2]));
		
		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// ((x,y,z),(y,z,x),(z,x,y))
	{
		typedef Matrix<coord::Cartesian, eval_type, 3, 3> matrix_type;
		typedef sc::Matrix3x3<
			x, z, y,
			y, x, z,
			z, y, x,
			matrix_type
		> function;

		static_assert(
			sc::IsSquareMatrix<function>::value,
			"function is not a square matrix.");

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };

		// hryky::Matrix is column-major.
		matrix_type correct;
		correct[0][0] = parameters[0];
		correct[0][1] = parameters[1];
		correct[0][2] = parameters[2];
		correct[1][0] = parameters[2];
		correct[1][1] = parameters[0];
		correct[1][2] = parameters[1];
		correct[2][0] = parameters[1];
		correct[2][1] = parameters[2];
		correct[2][2] = parameters[0];
		
		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// ((1,0,0),(0,1,0),(0,0,1))
	{
		typedef Matrix<coord::Cartesian, eval_type, 3, 3> matrix_type;
		typedef sc::IdentityMatrix<3, matrix_type> function;

		static_assert(
			sc::IsIdentityMatrix<function>::value,
			"function is not an identity matrix.");

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };

		// hryky::Matrix is column-major.
		matrix_type correct;
		correct[0][0] = 1.0f;
		correct[0][1] = 0.0f;
		correct[0][2] = 0.0f;
		correct[1][0] = 0.0f;
		correct[1][1] = 1.0f;
		correct[1][2] = 0.0f;
		correct[2][0] = 0.0f;
		correct[2][1] = 0.0f;
		correct[2][2] = 1.0f;
		
		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// (3.0f + 2.0f * 4.0f)!
	{
		typedef sc::Factorial<sc::Add<three, sc::Mul<two, four> > >
			function;

		static_assert(
			IsSame<
				sc::Simplify<function>::type,
				sc::Integer<eval_type, hryky::Factorial<11>::value>::type
			>::type::value,
			"(3+2*4)! => 11!");

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct = eval_type(hryky::Factorial<11>::value);

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// (3.0f + y * 4.0f)!
	{
		typedef sc::Factorial<sc::Add<three, sc::Mul<y, four> > >
			function;

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct = eval_type(hryky::Factorial<11>::value);

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// substitute(z*(x+z*(x+y)), x, 3.0) => (z*(3+z*(3+y)))
	{
		typedef sc::Mul<z, sc::Add<x, sc::Mul<z, sc::Add<x,y> > > >
			substituted;
		typedef sc::Substitute<substituted, x, three> function;

		static_assert(
			IsSame<
				function::type,
				sc::Mul<
					z, sc::Add<
						three, sc::Mul<z, sc::Add<three, y> > > >::type
			>::value,
			"substitute(z*(x+z*(x+y)), x, 3.0) => (z*(3+z*(3+y)))");

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct = 
			parameters[2] * (3.0f + parameters[2] * (3.0f + parameters[1]));

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// sum{k:0->10}(x + k*y + k)
	{
		typedef sc::Sum<
			sc::Add<x, sc::Add<sc::Mul<k, y>, k> >,
			k,
			zero,
			ten
		> function;

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type correct = 0.0f;
		hryky::Unroll<11>::foreach_at([&correct, &parameters](
			size_t const index) {
			correct += parameters[0] + index * parameters[1] + index;
		});
		
		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// sin(pi/4)
	{
		typedef sc::Sin<sc::Divide<pi, four>, eval_type> function;

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct =
			hryky::sin(hryky::Pi<eval_type>::value / 4.0f);

		static_assert(
			!sc::Reduce<sc::Divide<pi, four> >::value,
			"failed");
		
		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// (5*((y+1)+(2*x))+49*(y+1))+(y+1)
	{
		typedef sc::Add<
			sc::Add<
				sc::Mul<
					five,
					sc::Add<sc::Add<y, one>, sc::Mul<two, x> >
				>,
				sc::Mul<
					sc::Integer<eval_type, 49>,
					sc::Add<y, one>
				>
			>,
			sc::Add<y, one>
		> function;

		typedef sc::Scatter<function> scatterred;
		typedef sc::Align<scatterred> aligned;
		typedef sc::Simplify<aligned> simplified;
		typedef sc::Gather<simplified> gathered;
	
		(log.writer() << "scatter "
			<< (json::writer()
			<< stream::denote("function") << function()
			<< stream::denote("scatterred") << scatterred()
			<< stream::denote("aligned") << aligned()
			<< stream::denote("simplified") << simplified()
			<< stream::denote("gathered") << gathered()
			));
	}

	// (6/(2*y))
	{
		typedef sc::Divide<six, sc::Mul<two, y> > function;

		static_assert(
			sc::Dividable<six, two>::value,
			"6%2=0");

		static_assert(
			sc::Reduce<function>::value,
			"failed");

		typedef sc::Divide<sc::Sub<sc::Mul<three, y>, three>, sc::IntPower<y, 2> >
			function2;

		static_assert(
			sc::Reduce<sc::Sub<function, function2> >::value,
			"failed");
	}

	// (2 + (d/dx)*(d/dy)*(d/dz))*(3x*(y^2)*z) => 6x*(y^2)*z + 6y
	{
		typedef sc::Mul<
			sc::Mul<
				sc::Differentiator<x>,
				sc::Differentiator<y>
			>,
			sc::Differentiator<z>
		> differentiator;

		typedef sc::Mul<three, sc::Mul<sc::Mul<x, sc::IntPower<y,2> >, z> >
			differentiated;

		static_assert(
			IsSame<
			sc::Simplify<sc::Mul<differentiator, differentiated> >::type,
			sc::Mul<six, y>::type
			>::value,
			"(d^3/dxdydz)*(3x*y^2*z) => 6y");

		log.writer() << "differential operator" << differentiator();

		typedef sc::Simplify<sc::Mul<
			sc::Add<
				two,
				differentiator
			>,
			sc::Mul<three, sc::Mul<sc::Mul<x, sc::IntPower<y,2> >, z> >
		> > function;

		eval_type const parameters[] = { 1.0f, 2.0f, 3.0f, };
		eval_type const correct = (
			6.0f * parameters[0] * parameters[1] * parameters[1] * parameters[2] +
			6.0f * parameters[1]);

		if (!verify(function(), parameters, correct, log)) {
			return false;
		}
	}

	// ((d/dx)^3)*(x^4) => 24*x
	{
		typedef sc::IntPower<sc::Differentiator<x>, 3>
			differentiator;

		log.writer() << "differential operator" << differentiator();

		typedef sc::IntPower<x, 4> differentiated;

		static_assert(
			IsSame<
			sc::Simplify<sc::Mul<differentiator, differentiated> >::type,
			sc::Mul<sc::Integer<eval_type, 24>, x>::type
			>::value,
			"((d/dx)^3)*(x^4) => 24*x");
	}

	// search in (x^3)*y+z
	{
		typedef sc::Add<sc::Mul<sc::IntPower<x, 3>, y>, z>
			function;

		{
			typedef sc::Search<function, x> searched;

			static_assert(
				searched::value,
				"(x^3)*y+z includes x");
		}
		
		{
			typedef sc::Search<function, k> searched;

			static_assert(
				!searched::value,
				"(x^3)*y+z doesn't include k");
		}
	}
#endif

	// expands sin(x) by Maclaurin series.
	{
		typedef sc::Sin<x, eval_type> op;
		typedef sc::MaclaurinSeriesC<op, 0, x> expand_zero;
		typedef sc::MaclaurinSeriesC<op, 1, x> expand_first;
		typedef sc::MaclaurinSeriesC<op, 3, x> expand_third;
		typedef sc::MaclaurinSeriesC<op, 5, x> expand_fifth;
		typedef sc::MaclaurinSeriesC<op, 7, x> expand_seventh;
		typedef sc::MaclaurinSeriesC<op, 9, x> expand_ninth;
		typedef sc::MaclaurinSeriesC<op, 11, x> expand_eleventh;

		log.writer() << "Maclaurin series "
			<< (json::writer()
			<< stream::denote("op") << op()
			<< stream::denote("zero") << sc::Simplify<expand_zero>()
			<< stream::denote("first") << sc::Simplify<expand_first>()
			<< stream::denote("third") << sc::Simplify<expand_third>()
			<< stream::denote("fifth") << sc::Simplify<expand_fifth>()
			<< stream::denote("seventh") << sc::Simplify<expand_seventh>()
			<< stream::denote("ninth") << sc::Simplify<expand_ninth>()
			<< stream::denote("eleventh") << sc::Simplify<expand_eleventh>()
			);
	}

	return true;
}
/**
  @brief confirms which the answer is correct.
 */
template <typename FunctionT, typename ParametersT>
bool verify(
	FunctionT const function,
	ParametersT const & parameters,
	typename FunctionT::eval_type const & correct,
	testing::Log & log)
{
	typedef testing::Log::writer_type log_writer_type;
	
	typedef sc::Simplify<FunctionT> simplified;
	typedef typename simplified::eval_type eval_type;
	
	eval_type const answer = simplified::eval(parameters);

	if (correct != answer) {
		hryky_log_alert(
			"failed to eval the operation. "
			<< (json::writer()
			<< stream::denote("correct") << correct
			<< stream::denote("wrong") << answer
			<< stream::denote("op") << function
			<< stream::denote("simplified") << simplified()
			));
		return false;
	}

	log.writer() << function;
	testing::Log::map_type const map(log.writer());

	(log.writer()
	 << stream::denote("op") << function
	 << stream::denote("simplified") << simplified()
	 << stream::denote("answer") << answer);

	{
		os_type os;
		log.writer() << (os << "d(" << simplified() << ")");
		testing::Log::map_type const map(log.writer());

		(log.writer()
		 << stream::denote("WRT x") << sc::D<FunctionT, x>()
		 << stream::denote("WRT y") << sc::D<FunctionT, y>()
		 << stream::denote("WRT Z") << sc::D<FunctionT, z>()
		 );
	}
	{
		os_type os;
		log.writer() << (os << "simplified d(" << simplified() << ")");
		testing::Log::map_type const map(log.writer());

		(log.writer()
		 << stream::denote("simplified WRT x") << sc::Simplify<sc::D<FunctionT, x> >()
		 << stream::denote("simplified WRT y") << sc::Simplify<sc::D<FunctionT, y> >()
		 << stream::denote("simplified WRT Z") << sc::Simplify<sc::D<FunctionT, z> >()
		 );
	}
	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
