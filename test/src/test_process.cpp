/**
  @file     test_process.cpp
  @brief    tests hryky::process module.
  @author   HRYKY
  @version  $Id: test_process.cpp 362 2014-07-07 09:43:31Z hryky.private@gmail.com $
 */
#include "precompiled.h"
#include "hryky/testing.h"
#include "hryky/windows.h"
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

		/// tests hryky::process module.
		virtual bool run_impl();

	};
	Test const g_test;

	char const * const g_testname = "process";

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
  @brief tests hryky::process module.
 */
bool Test::run_impl()
{
	// initializes logging.
	testing::Log log(*this);

	// initializes the generator of pseudo random number.
	testing::Random random;
	log.writer() << hryky_stream_denote(random);

	::STARTUPINFOW start_info;
	hryky::memset(&start_info, 0, sizeof(start_info));
	start_info.cb = sizeof(start_info);
	
	::PROCESS_INFORMATION process_info;
	hryky::memset(&process_info, 0, sizeof(process_info));

	String<WCHAR> executable;
	String<WCHAR> test_name;
	{
		::LPWSTR const commandline = ::GetCommandLineW();
		int argc = 0;
		::LPWSTR * const argv = ::CommandLineToArgvW(commandline, &argc);

		if (2 < argc) {
			hryky_log_info("Child Process");
			return true;
		}
		executable = argv[0];
		test_name = argv[1];
	}

	String<WCHAR> commandline = executable + L" " + test_name + L" 1";

	// Start the child process.
	if(!::CreateProcessW(
		executable.c_str(),// module name.
		const_cast<WCHAR *>(commandline.c_str()),// arguments
		NULL,// Process handle not inheritable
		NULL,// Thread handle not inheritable
		FALSE,// Set handle inheritance to FALSE
		CREATE_SUSPENDED,// No creation flags
		NULL,// Use parent's environment block
		NULL,// Use parent's starting directory
		&start_info,// Pointer to STARTUPINFO structure
		&process_info// Pointer to PROCESS_INFORMATION structure
		)) {
		hryky_log_alert("failed to create a child process.");
		return false;
	}

	::ResumeThread(process_info.hThread);

	// Wait until child process exits.
	::WaitForSingleObject(process_info.hProcess, INFINITE);

	// Close process and thread handles.
	::CloseHandle(process_info.hProcess);
	::CloseHandle(process_info.hThread);

	return true;
}
} // namespace "anonymous"
} // namespace test
} // namespace hryky
