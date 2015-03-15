/**
  @file         testing_random.h
  @brief        initializes the generator of pseudo random number.
  @author       HRYKY
  @version      $Id: testing_random.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef TESTING_RANDOM_H_20120501112547142
#define TESTING_RANDOM_H_20120501112547142
#include "hryky/random.h"
#include "hryky/with_stream_out.h"
#include "hryky/without_copy.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace testing
{
	/// initializes the generator of pseudo random number.
	class Random;

} // namespace testing
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief initializes the generator of pseudo random number.
 */
class hryky::testing::Random :
	public WithStreamOut<Random>,
	private WithoutCopy
{
public :

	typedef Random                  this_type;
	typedef random::generator_type  generator_type;
	typedef random::seed_type       seed_type;

	/// default constructor.
	Random();

	/// destructor.
	~Random();

	/// retrieves the generator of pseudo random number.
	generator_type & generator();

	/// resets the seed of the generator.
	Random & seed(seed_type src);

	/// retrieves the seed of this generator.
	seed_type seed() const;

	/// output the information of hryky::testing::Random.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

private :

	hryky_delete_this_copy_constructor(Random);
	hryky_delete_this_copy_assign_op(Random);

	generator_type  generator_;
	seed_type       seed_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace testing
{
namespace
{
} // namespace "anonymous"
} // namespace testing
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief output the information of hryky::testing::Random.
 */
template <typename StreamT>
StreamT &
hryky::testing::Random::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << stream::denote("seed") << this->seed();
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
namespace testing
{
} // namespace testing
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // TESTING_RANDOM_H_20120501112547142
// end of file
