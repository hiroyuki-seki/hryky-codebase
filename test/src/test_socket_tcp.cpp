/**
  @file     test_socket_tcp.cpp
  @brief    tests the connection by TCP on localhost.
  @author   HRYKY
  @version  $Id: test_socket_tcp.cpp 370 2014-07-21 16:00:02Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/socket.h"
#include "hryky/thread.h"
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
		
		/// tests the connection by TCP on localhost.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "socket_tcp";

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
  @brief tests the connection by TCP on localhost.
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
	checkpoint_type listening;

	if (!thread_pool.run([&join, &failure, &listening]() {
		join_type::AutoRestore const restore(join);
		auto fail = auto_assign(failure, true);
		auto fail_listening = auto_assign(listening, false);

		socket::Address address;
		if (!socket::FindAddress()
			.service("50001")
			.as_ipv6()
			.as_tcp()
			.as_server()
			([&address](socket::Address const & found) {
				address = found;
				return true;
			})) {
			hryky_log_alert("The address for TCP server is not found.");
			return;
		}
		hryky_log_debug("listening address is " << address);

		socket::Descriptor socket;
		if (!socket.bind(address)) {
			hryky_log_alert("failed to name the listening socket.");
			return;
		}

		if (!socket.listen(1u)) {
			hryky_log_alert("failed to prepare the listening socket.");
			return;
		}

		fail_listening.disable();
		listening = true;
		socket::Descriptor accepted = socket.accept();
		if (!accepted.opened()) {
			hryky_log_alert("failed to accept an incoming connection.");
			return;
		}
		hryky_log_info("server accepted " << accepted);

		Array<char, 4u> buffer = {0, };
		if (!accepted.recv(buffer)) {
			hryky_log_alert("failed to receive data from client.");
			return;
		}
		hryky_log_info("server received " << buffer);

		if (!accepted.send(g_pong)) {
			hryky_log_alert("failed to send data to client");
			return;
		}
		hryky_log_info("server sent " << g_pong);

		socket::Descriptor::received_type const received =
			accepted.recv(buffer);
		if (!received.shutdown()) {
			hryky_log_alert("failed to receive FIN from client.");
			return;
		}
		hryky_log_info("server received FIN");

		accepted.shutdown();

		fail.disable();
	})) {
		hryky_log_err(
			"failed to enregister a function to find an address.");
		return false;
	}

	if (!thread_pool.run([&join, &failure, &listening]() {
		join_type::AutoRestore const restore(join);
		auto fail = auto_assign(failure, true);

		socket::Address address;
		if (!socket::FindAddress()
			.service("50001")
			.as_ipv6()
			.as_tcp()
			.as_client()
			([&address](socket::Address const & found) {
				address = found;
				return true;
			})) {
			hryky_log_alert(
				"The destination address to TCP server is not found.");
			return;
		}
		hryky_log_debug(
			"destination address is "
			<< (json::writer() << hryky_stream_denote(address)));

		bool communication = true;

		if (!listening.join([&address, &communication](
			bool const is_listening) {
			auto fail_communication = auto_assign(communication, false);
			if (!is_listening) {
				hryky_log_alert("server is not listening.");
				return;
			}

			socket::Descriptor socket;
			if (!socket.connect(address)) {
				hryky_log_alert("failed to connect the server.");
				return;
			}
			
			if (!socket.send(g_ping)) {
				hryky_log_alert("failed to send data to server.");
				return;
			}
			hryky_log_info("client sent " << g_ping);
			
			Array<char, 4> buffer = {0,};
			if (!socket.recv(buffer)) {
				hryky_log_alert("failed to receive data from server.");
				return;
			}
			hryky_log_info("client received " << buffer);
			
			socket.shutdown_write();

			socket::Descriptor::received_type const received =
				socket.recv(buffer);
			if (!received.shutdown()) {
				hryky_log_alert("failed to received FIN.");
				return;
			}
			hryky_log_info("client received FIN");

			socket.shutdown_read();

			fail_communication.disable();
		}, chrono::seconds(10u))) {
			hryky_log_alert(
				"The communication from the client is out of time.");
			return;
		}

		if (!communication) {
			hryky_log_alert("failed to communicate with server.");
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
