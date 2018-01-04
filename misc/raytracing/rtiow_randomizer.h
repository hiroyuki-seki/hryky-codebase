/**
  @file     rtiow_randomizer.h
  @brief    collects functors to generate random values.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_RANDOMIZER_H_20160724153805318
#define RTIOW_RANDOMIZER_H_20160724153805318
#include <random>
#include "./rtiow_vec3.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename VectorT
#define hryky_template_arg \
	VectorT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
	/// collects functors to generate random values.
	template <hryky_template_param>
	class Randomizer;

} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief collects functors to generate random values.
 */
template <typename VectorT = hryky::rtiow::Vec3<> >
class hryky::rtiow::Randomizer
{
public :

	typedef Randomizer<hryky_template_arg> this_type;
	typedef VectorT vector_type;
	typedef typename vector_type::value_type value_type;

	/// default constructor.
	Randomizer();

	/// instantiates with the seed.
	template <typename SeedT>
	Randomizer(SeedT seed);

	/// move constructor.
	Randomizer(this_type &&);

	/// destructor.
	~Randomizer();

	/// generates a value.
	value_type operator()();

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// generates a point in a unit sphere.
	VectorT in_sphere();

	/// generates a point in a unit disk.
	VectorT in_disk();

protected :

private :
	hryky_delete_copy_constructor(Randomizer);
	hryky_delete_copy_assign_op(this_type);

	::std::mt19937 gen_;
	::std::uniform_real_distribution<float> dist_;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::rtiow::Randomizer<hryky_template_arg>::Randomizer()
	: gen_()
	  , dist_(0.0f, 1.0f)
{
}

/**
  @brief instantiates with the seed.
 */
template <hryky_template_param>
template <typename SeedT>
hryky::rtiow::Randomizer<hryky_template_arg>::Randomizer(SeedT seed)
	: gen_(seed)
	  , dist_(0.0f, 1.0f)
{
}

/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::rtiow::Randomizer<hryky_template_arg>::Randomizer(this_type && rhs)
	: hryky_move_member(gen)
	  , hryky_move_member(dist)
{
}

/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::rtiow::Randomizer<hryky_template_arg>::~Randomizer()
{
}

/**
  @brief generates a value.
 */
template <hryky_template_param>
typename hryky::rtiow::Randomizer<hryky_template_arg>::value_type 
hryky::rtiow::Randomizer<hryky_template_arg>::operator()()
{
	return value_type(this->dist_(this->gen_));
}

/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::rtiow::Randomizer<hryky_template_arg>::clear()
{
	hryky::clear(this->dist_);
	hryky::clear(this->gen_);
}

/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::rtiow::Randomizer<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(gen);
	hryky_swap_member(dist);
}

/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::rtiow::Randomizer<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
}

/**
  @brief generates a point in a unit sphere.
 */
template <hryky_template_param>
VectorT
hryky::rtiow::Randomizer<hryky_template_arg>::in_sphere()
{
	VectorT p;
	do {
		p = 2.0f * VectorT((*this)(), (*this)(), (*this)()) - 1.0f;
	} while (1.0f <= p.slength());
	return p;
}

/**
  @brief generates a point in a unit disk.
 */
template <hryky_template_param >
VectorT
hryky::rtiow::Randomizer<hryky_template_arg >::in_disk()
{
	VectorT p;
	do {
		p = 2.0f * VectorT((*this)(), (*this)(), 0.0f)
			- VectorT(1.0f, 1.0f, 0.0f);
	} while (1.0f <= dot(p, p));
	return p;
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
namespace rtiow
{
} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // RTIOW_RANDOMIZER_H_20160724153805318
// end of file
