/**
  @file     test_socket_udp.cpp
  @brief    tests the communication using UDP sockets.
  @author   HRYKY
  @version  $Id: test_socket_udp.cpp 370 2014-07-21 16:00:02Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/thread.h"
#include "hryky/socket.h"
#include "hryky/exclusion.h"
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

		/// tests the communication using UDP sockets.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "socket_udp";

	LiteralString<> const g_ping("ping");
	LiteralString<> const g_pong("pong");

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
  @brief tests the communication using UDP sockets.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << hryky_stream_denote(random);

	/**
	  creates the default pool of thread resources.
	 */
	thread::pool_type thread_pool;
	thread::pool::registry_type const enregister_thread_pool(&thread_pool);

	typedef exclusion::Counter<> join_type;
	typedef exclusion::Variable<bool> failure_type;
	typedef exclusion::Checkpoint<bool> checkpoint_type;

	join_type       join(2u);
	failure_type    failure;
	checkpoint_type peer1_bound, peer2_bound;

	if (!thread_pool.run([
		&join, &failure, &peer1_bound, &peer2_bound]() {
			join_type::AutoRestore const restore(join);
			auto fail = auto_assign(failure, true);
			auto fail_bound = auto_assign(peer1_bound, false);

			socket::Address address;
			if (!socket::FindAddress()
				.service("50001")
				.as_ipv4()
				.as_udp()
				.as_server()
				([&address](socket::Address const & found) {
					address = found;
					return true;
				})) {
				hryky_log_alert("The address of peer 1 is not found.");
				return;
			}
			hryky_log_debug("bound address is " << address);

			socket::Descriptor socket;
			if (!socket.bind(address)) {
				hryky_log_alert(
					"failed to name the listening socket.");
				return;
			}
			hryky_log_debug("The peer 1 is bound to " << address);

			fail_bound.disable();
			peer1_bound = true;

			bool communication = true;

			if (!peer2_bound.join([&socket, &communication](
				bool const bound) {
				auto fail_communication = auto_assign(communication, false);
				if (!bound) {
					hryky_log_alert("The target of peer1 failed to bind.");
					return;
				}

				socket::Address target;
				if (!socket::FindAddress()
					.service("50002")
					.as_ipv4()
					.as_udp()
					([&target](socket::Address const & found) {
						target = found;
						return true;
					})) {
					hryky_log_alert(
						"The address of the target is not found.");
					return;
				}

				if (!socket.sendto(LiteralString<>("ping"), target)) {
					hryky_log_alert(
						"failed to send data:"
						<< (json::writer()
							<< "to" << target));
					return;
				}

				Array<char, 4u> buffer = {0, };
				socket::Address received_addr;
				if (!socket.recvfrom(buffer, received_addr)) {
					hryky_log_alert(
						"peer1 failed to receive data");
					return;
				}

				hryky_log_debug(
					"peer1 received:"
					<< (json::writer()
						<< "data" << buffer
						<< "from" << received_addr));

				fail_communication.disable();
			}, chrono::seconds(10u))) {
				hryky_log_alert(
					"The target of peer1 isn't bound "
					"within the specified time.");
				return;
			}

			if (!communication) {
				hryky_log_alert(
					"failed to communicate with the target of peer1.");
				return;
			}

			fail.disable();
		})) {
		hryky_log_err(
			"failed to enregister a function to find an address.");
		return false;
	}
	
	if (!thread_pool.run([
		&join, &failure, &peer1_bound, &peer2_bound]() {
			join_type::AutoRestore const restore(join);
			auto fail = auto_assign(failure, true);
			auto fail_bound = auto_assign(peer2_bound, false);

			socket::Address address;
			if (!socket::FindAddress()
				.service("50002")
				.as_ipv4()
				.as_udp()
				.as_server()
				([&address](socket::Address const & found) {
					address = found;
					return true;
				})) {
				hryky_log_alert(
					"The address of peer 2 is not found.");
				return;
			}
			hryky_log_debug("bound address is " << address);

			socket::Descriptor socket;
			if (!socket.bind(address)) {
				hryky_log_alert("failed to name the listening socket.");
				return;
			}
			hryky_log_debug("The peer 2 is bound to " << address);

			fail_bound.disable();
			peer2_bound = true;

			bool communication = true;
			if (!peer1_bound.join([&socket, &communication](
				bool const bound) {
				auto fail_communication = auto_assign(communication, false);
				if (!bound) {
					hryky_log_alert("The target of peer2 failed to bind.");
					return;
				}

				socket::Address target;
				if (!socket::FindAddress()
					.service("50001")
					.as_ipv4()
					.as_udp()
					([&target](socket::Address const & found) {
						target = found;
						return true;
					})) {
					hryky_log_alert(
						"The address of the target is not found.");
					return;
				}

				if (!socket.sendto(LiteralString<>("pong"), target)) {
					hryky_log_alert(
						"failed to send data:"
						<< (json::writer()
							<< "to" << target));
					return;
				}

				Array<char, 4u> buffer = {0, };
				socket::Address received_addr;
				if (!socket.recvfrom(buffer, received_addr)) {
					hryky_log_alert(
						"peer2 failed to receive data");
					return;
				}

				hryky_log_debug(
					"peer2 received:"
					<< (json::writer()
						<< "data" << buffer
						<< "from" << received_addr));

				fail_communication.disable();
			}, chrono::seconds(10u))) {
				hryky_log_alert(
					"The target of peer2 isn't bound "
					"within the specified time.");
				return;
			}

			if (!communication) {
				hryky_log_alert(
					"failed to communicate with the target of peer2.");
				return;
			}

			fail.disable();
		})) {
		hryky_log_err(
			"failed to enregister a function to find an address.");
		return false;
	}

	if (!join.join(chrono::seconds(10u))) {
		hryky_log_err(
			"The function on threads doesn't ends in the constant time: "
			<< join);
		return false;
	}

	if (failure) {
		hryky_log_err("failed to find address.");
		return false;
	}

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
