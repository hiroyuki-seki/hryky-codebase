/**
  @file     test_flag.cpp
  @brief    tests hryky::Flag.
  @author   HRYKY
  @version  $Id: test_flag.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/flag.h"
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

		struct Kind
		{
			enum Raw
			{
				num0_,
				num1_,
				num2_,
				num3_,
				num4_,
				num5_,
				num6_,
				num7_,
				num8_,
				num9_,
				num10_,
				num11_,
				num12_,
				num13_,
				num14_,
				num15_,
				num16_,
				num17_,
				num18_,
				num19_,
				num20_,
				num21_,
				num22_,
				num23_,
				num24_,
				num25_,
				num26_,
				num27_,
				num28_,
				num29_,
				num30_,
				num31_,
				num32_,
				num_,
			};
		};

		/// constructor.
		Test();

	private:
		Test(this_type const &);
		this_type & operator=(this_type const &);
		
		/// tests hryky::Flag.
		virtual bool run_impl();

		/// tests the specified typed flag.
		template <typename FlagT>
		bool test_flag(testing::Log & log, testing::Random & random);

	};
	Test const g_test;

	extern LiteralString<> const g_tokens[Test::Kind::num_] = {
		LiteralString<>("num0"),
		LiteralString<>("num1"),
		LiteralString<>("num2"),
		LiteralString<>("num3"),
		LiteralString<>("num4"),
		LiteralString<>("num5"),
		LiteralString<>("num6"),
		LiteralString<>("num7"),
		LiteralString<>("num8"),
		LiteralString<>("num9"),
		LiteralString<>("num10"),
		LiteralString<>("num11"),
		LiteralString<>("num12"),
		LiteralString<>("num13"),
		LiteralString<>("num14"),
		LiteralString<>("num15"),
		LiteralString<>("num16"),
		LiteralString<>("num17"),
		LiteralString<>("num18"),
		LiteralString<>("num19"),
		LiteralString<>("num20"),
		LiteralString<>("num21"),
		LiteralString<>("num22"),
		LiteralString<>("num23"),
		LiteralString<>("num24"),
		LiteralString<>("num25"),
		LiteralString<>("num26"),
		LiteralString<>("num27"),
		LiteralString<>("num28"),
		LiteralString<>("num29"),
		LiteralString<>("num30"),
		LiteralString<>("num31"),
		LiteralString<>("num32"),
	};

	char const * const g_testname = "flag";

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
  @brief tests hryky::Flag.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << "random" << random;

	typedef Flag<Kind, Kind::num_, LiteralString<>, g_tokens> flag_type;
	typedef Flag<Kind, Kind::num1_, LiteralString<>, g_tokens> flag1_type;
	typedef Flag<Kind, Kind::num2_, LiteralString<>, g_tokens> flag2_type;
	typedef Flag<Kind, Kind::num3_, LiteralString<>, g_tokens> flag3_type;
	typedef Flag<Kind, Kind::num4_, LiteralString<>, g_tokens> flag4_type;
	typedef Flag<Kind, Kind::num5_, LiteralString<>, g_tokens> flag5_type;
	typedef Flag<Kind, Kind::num6_, LiteralString<>, g_tokens> flag6_type;
	typedef Flag<Kind, Kind::num7_, LiteralString<>, g_tokens> flag7_type;
	typedef Flag<Kind, Kind::num8_, LiteralString<>, g_tokens> flag8_type;
	typedef Flag<Kind, Kind::num9_, LiteralString<>, g_tokens> flag9_type;
	typedef Flag<Kind, Kind::num10_, LiteralString<>, g_tokens> flag10_type;
	typedef Flag<Kind, Kind::num11_, LiteralString<>, g_tokens> flag11_type;
	typedef Flag<Kind, Kind::num12_, LiteralString<>, g_tokens> flag12_type;
	typedef Flag<Kind, Kind::num13_, LiteralString<>, g_tokens> flag13_type;
	typedef Flag<Kind, Kind::num14_, LiteralString<>, g_tokens> flag14_type;
	typedef Flag<Kind, Kind::num15_, LiteralString<>, g_tokens> flag15_type;
	typedef Flag<Kind, Kind::num16_, LiteralString<>, g_tokens> flag16_type;
	typedef Flag<Kind, Kind::num17_, LiteralString<>, g_tokens> flag17_type;
	typedef Flag<Kind, Kind::num18_, LiteralString<>, g_tokens> flag18_type;
	typedef Flag<Kind, Kind::num19_, LiteralString<>, g_tokens> flag19_type;
	typedef Flag<Kind, Kind::num20_, LiteralString<>, g_tokens> flag20_type;
	typedef Flag<Kind, Kind::num21_, LiteralString<>, g_tokens> flag21_type;
	typedef Flag<Kind, Kind::num22_, LiteralString<>, g_tokens> flag22_type;
	typedef Flag<Kind, Kind::num23_, LiteralString<>, g_tokens> flag23_type;
	typedef Flag<Kind, Kind::num24_, LiteralString<>, g_tokens> flag24_type;
	typedef Flag<Kind, Kind::num25_, LiteralString<>, g_tokens> flag25_type;
	typedef Flag<Kind, Kind::num26_, LiteralString<>, g_tokens> flag26_type;
	typedef Flag<Kind, Kind::num27_, LiteralString<>, g_tokens> flag27_type;
	typedef Flag<Kind, Kind::num28_, LiteralString<>, g_tokens> flag28_type;
	typedef Flag<Kind, Kind::num29_, LiteralString<>, g_tokens> flag29_type;
	typedef Flag<Kind, Kind::num30_, LiteralString<>, g_tokens> flag30_type;
	typedef Flag<Kind, Kind::num31_, LiteralString<>, g_tokens> flag31_type;
	typedef Flag<Kind, Kind::num32_, LiteralString<>, g_tokens> flag32_type;

	if (!this->test_flag<flag_type>(log, random)) {
		hryky_log_alert("failed to test flag.");
		return false;
	}
	if (!this->test_flag<flag1_type>(log, random)) {
		hryky_log_alert("failed to test flag1.");
		return false;
	}
	if (!this->test_flag<flag2_type>(log, random)) {
		hryky_log_alert("failed to test flag2.");
		return false;
	}
	if (!this->test_flag<flag3_type>(log, random)) {
		hryky_log_alert("failed to test flag3.");
		return false;
	}
	if (!this->test_flag<flag4_type>(log, random)) {
		hryky_log_alert("failed to test flag4.");
		return false;
	}
	if (!this->test_flag<flag5_type>(log, random)) {
		hryky_log_alert("failed to test flag5.");
		return false;
	}
	if (!this->test_flag<flag6_type>(log, random)) {
		hryky_log_alert("failed to test flag6.");
		return false;
	}
	if (!this->test_flag<flag7_type>(log, random)) {
		hryky_log_alert("failed to test flag7.");
		return false;
	}
	if (!this->test_flag<flag8_type>(log, random)) {
		hryky_log_alert("failed to test flag8.");
		return false;
	}
	if (!this->test_flag<flag9_type>(log, random)) {
		hryky_log_alert("failed to test flag9.");
		return false;
	}
	if (!this->test_flag<flag10_type>(log, random)) {
		hryky_log_alert("failed to test flag10.");
		return false;
	}
	if (!this->test_flag<flag11_type>(log, random)) {
		hryky_log_alert("failed to test flag11.");
		return false;
	}
	if (!this->test_flag<flag12_type>(log, random)) {
		hryky_log_alert("failed to test flag12.");
		return false;
	}
	if (!this->test_flag<flag13_type>(log, random)) {
		hryky_log_alert("failed to test flag13.");
		return false;
	}
	if (!this->test_flag<flag14_type>(log, random)) {
		hryky_log_alert("failed to test flag14.");
		return false;
	}
	if (!this->test_flag<flag15_type>(log, random)) {
		hryky_log_alert("failed to test flag15.");
		return false;
	}
	if (!this->test_flag<flag16_type>(log, random)) {
		hryky_log_alert("failed to test flag16.");
		return false;
	}
	if (!this->test_flag<flag17_type>(log, random)) {
		hryky_log_alert("failed to test flag17.");
		return false;
	}
	if (!this->test_flag<flag18_type>(log, random)) {
		hryky_log_alert("failed to test flag18.");
		return false;
	}
	if (!this->test_flag<flag19_type>(log, random)) {
		hryky_log_alert("failed to test flag19.");
		return false;
	}
	if (!this->test_flag<flag20_type>(log, random)) {
		hryky_log_alert("failed to test flag20.");
		return false;
	}
	if (!this->test_flag<flag21_type>(log, random)) {
		hryky_log_alert("failed to test flag21.");
		return false;
	}
	if (!this->test_flag<flag22_type>(log, random)) {
		hryky_log_alert("failed to test flag22.");
		return false;
	}
	if (!this->test_flag<flag23_type>(log, random)) {
		hryky_log_alert("failed to test flag23.");
		return false;
	}
	if (!this->test_flag<flag24_type>(log, random)) {
		hryky_log_alert("failed to test flag24.");
		return false;
	}
	if (!this->test_flag<flag25_type>(log, random)) {
		hryky_log_alert("failed to test flag25.");
		return false;
	}
	if (!this->test_flag<flag26_type>(log, random)) {
		hryky_log_alert("failed to test flag26.");
		return false;
	}
	if (!this->test_flag<flag27_type>(log, random)) {
		hryky_log_alert("failed to test flag27.");
		return false;
	}
	if (!this->test_flag<flag28_type>(log, random)) {
		hryky_log_alert("failed to test flag28.");
		return false;
	}
	if (!this->test_flag<flag29_type>(log, random)) {
		hryky_log_alert("failed to test flag29.");
		return false;
	}
	if (!this->test_flag<flag30_type>(log, random)) {
		hryky_log_alert("failed to test flag30.");
		return false;
	}
	if (!this->test_flag<flag31_type>(log, random)) {
		hryky_log_alert("failed to test flag31.");
		return false;
	}
	if (!this->test_flag<flag32_type>(log, random)) {
		hryky_log_alert("failed to test flag32.");
		return false;
	}

	return true;
}
/**
  @brief tests the specified typed flag.
 */
template <typename FlagT>
bool Test::test_flag(testing::Log & log, testing::Random & random)
{
	// randomizes operation.
	random::Uniform<uint8_t> operation_dist(
		random.generator(), 0, 2);
	
	// randomizes a position of flag.
	random::Uniform<FlagT::size_type> index_dist(
		random.generator(), 0, FlagT::num - 1);
	log.writer() << "index_dist" << index_dist;
	
	// randomizes the number of iteration.
	random::Uniform<size_t> iteration_dist(
		random.generator(), 0x100, 0x1000);

	typedef typename FlagT::const_reference const_reference;
	typedef typename FlagT::reference       reference;
	typedef typename FlagT::size_type       size_type;
	
	FlagT flag;

	if (!flag.none()) {
		hryky_log_alert(
			"The default value must be off. "
			<< (json::writer()
			<< stream::denote("flag") << flag));
		return false;
	}
	
	if (flag.all()) {
		hryky_log_alert(
			"The default value must be off. "
			<< (json::writer()
			<< stream::denote("flag") << flag));
		return false;
	}

	// checks value after default construct
	{
		if (!flag.every_at([](
			const_reference element, size_type const index) {
			if (element) {
				hryky_log_alert(
					"The default value must be off. "
					<< (json::writer()
					<< stream::denote("index") << index
					));
				return false;
			}
			return true;
		})) {
			hryky_log_alert("failure of " << flag);
			return false;
		}
	}

	// checks value after copy constructor.
	{
		if (!flag.every_at([](
			const_reference element, size_type const index) {
			if (element) {
				hryky_log_alert(
					"The default value must be off. "
					<< (json::writer()
					<< stream::denote("index") << index
					));
				return false;
			}
			return true;
		})) {
			hryky_log_alert("failure of " << flag);
			return false;
		}
	}

	// checks assignment of true.
	{
		if (!flag.every_at([&flag](
			reference element, size_type const index) {
			element = true;

			if (!element) {
				hryky_log_alert(
					"The assigned value must be on. "
					<< (json::writer()
					<< stream::denote("index") << index
					));
				return false;
			}
			
			if (!flag.any()) {
				hryky_log_alert(
					"any of the bits must be on. "
					<< (json::writer()
					<< stream::denote("index") << index
					));
				return false;
			}
			return true;
		})) {
			hryky_log_alert("failure of " << flag);
			return false;
		}
	}

	if (!flag.all()) {
		hryky_log_alert(
			"The all values must be on. "
			<< (json::writer()
			<< stream::denote("flag") << flag
			));
		return false;
	}

	// checks assignment of false.
	{
		if (!flag.every_at([](
			reference element, size_type const index) {
			element = false;

			if (element) {
				hryky_log_alert(
					"The value must be off. "
					<< (json::writer()
					<< stream::denote("index") << index
					));
				return false;
			}
			return true;
		})) {
			hryky_log_alert("failure of " << flag);
			return false;
		}
	}

	if (!flag.none()) {
		hryky_log_alert(
			"The all values must be off. "
			<< (json::writer()
			<< stream::denote("flag") << flag
			));
		return false;
	}

	{
		size_t count = 0;
		size_t const iteration_size = iteration_dist();
		for (; iteration_size != count; ++count) {
			FlagT::size_type const index = index_dist();
			bool prev_value = flag.test(index);
			
			uint8_t const operation = operation_dist();
			switch (operation) {
			case 0: // on
				flag.on(index);
				if (!flag.test(index)) {
					hryky_log_alert(
						"on() must enable the bit. "
						<< (json::writer()
						<< stream::denote("flag") << flag
						<< stream::denote("index") << index
						<< stream::denote("prev") << prev_value
						));
					return false;
				}
				break;
				
			case 1: // off
				flag.off(index);
				if (flag.test(index)) {
					hryky_log_alert(
						"off() must disable the bit. "
						<< (json::writer()
						<< stream::denote("flag") << flag
						<< stream::denote("index") << index
						<< stream::denote("prev") << prev_value
						));
					return false;
				}
				break;
				
			case 2: // flip
				flag.flip(index);
				if ((prev_value && flag.test(index))
					|| (!prev_value && !flag.test(index))) {
					hryky_log_alert(
						"flip() must invert the bit. "
						<< (json::writer()
						<< stream::denote("flag") << flag
						<< stream::denote("index") << index
						<< stream::denote("prev") << prev_value
						));
					return false;
				}
				break;

			default:
				hryky_log_alert("unexpected operation");
				return false;
			}
		}
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
