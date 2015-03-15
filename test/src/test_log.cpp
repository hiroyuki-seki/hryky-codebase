/*
  @file         test_log.cpp
  @brief        tests log modules.
  @author       HRYKY
  @version      $Id: test_log.cpp 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/log.h"
#include "hryky/testing.h"
#include "hryky/with_stream_out.h"
#include "hryky/type_traits/is_same.h"
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
	// enregisters a test
	class Test : hryky::testing::unit::Base
	{
	public :
		typedef testing::unit::Base base_type;
		typedef Test this_type;
		
		Test()
			: testing::unit::Base("log")
		{
		}
	private :
		Test(this_type const &);
		this_type & operator=(this_type const &);
		
		// tests log modules.
		virtual bool run_impl();
	};
	Test const g_test;

} // namespace "anonymous"

	// This class can be used as the second.
	template <typename UserStreamT = json::Writer<> >
	class UserValue :
		public WithStreamOut<UserValue<UserStreamT> >
	{
	public :
		UserValue(int value)
			: value_(value)
		{
		}
		
		int value() const
		{
			return this->value_;
		}

		template <typename StreamT>
		StreamT & write_to(StreamT & out) const
		{
			stream::map::Scope<StreamT> const map(out);
			hryky_write_member(value);
			return out;
		}
		
	private :
		int value_;
	};

	class Integer :
		public WithStreamOut<Integer>
	{
	public :
		Integer()
		{
		}

		template <typename StreamT>
		StreamT & write_to(StreamT & stream) const
		{
			stream << 0u;
			return stream;
		}
	};

} // namespace test
} // namespace hryky
//------------------------------------------------------------------------------
// global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace test
{
namespace
{
/**
  @brief tests log modules.
 */
bool Test::run_impl()
{
	// prints key-value pair literally.
	hryky_log_debug("int_value_1:" << int(1));

	auto out = json::writer();
	typedef decltype(out) stream_type;
	{
		// instantiates map.
		stream::map::Scope<stream_type> const first_map(out);

		// aggregates multiple key-value pairs.
		(out
		 << "int_10" << 10
		 << "float_10.0f" << 10.0f
		 << "bool_true" << true);

		// aggregates multiple values
		
		{
			out << "array";
			stream::array::Scope<stream_type> const array(out);

			out << 30 << 30.0f << true << "30";
		}

		// appends another map as a child.
		{
			out << "aggregation";
			stream::map::Scope<stream_type> const second_map(out);

			(out
			 << "int_20" << int(20)
			 << "float_20.0f" << float(20.0f)
			 << "bool_true" << bool(true)
			 << stream::denote("user_value") << UserValue<>(4));
		}

		// appends multiple valus by container.
		{
			out << "vector";
			Vector<int32_t> vec;
			vec.push_back(10);
			vec.push_back(20);
			vec.push_back(30);
			out << vec;
		}

		// appends strings.
		{
			out << "strings";
			stream::array::Scope<stream_type> const array(out);

			(out
			 << String<>("10")
			 << LiteralString<>("20")
			 << "30");
		}
	}

	// log the formatted hierarchy.
	hryky_log_debug("result:" << out);

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
