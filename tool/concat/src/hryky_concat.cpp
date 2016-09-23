/**
  @file         hryky_concat.cpp
  @brief        concatenates files.
  @since        2012-12-29T01:56:00+0900
  @author       HRYKY
  @version      $Id: hryky_concat.cpp 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#if defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable:4820)
#   pragma warning(disable:4514)
#endif

#include <cstdio>

#include <fcntl.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

//------------------------------------------------------------------------------
// macro
//------------------------------------------------------------------------------
#define HRYKY_NULL 0
//------------------------------------------------------------------------------
// anonymous namespace
//------------------------------------------------------------------------------
namespace
{
	struct AutoClose {
		AutoClose(FILE * file) : file_(file) {}
		~AutoClose() {
			if (HRYKY_NULL != this->file_) {
				std::fclose(this->file_);
				this->file_ = HRYKY_NULL;
			}
		}

		FILE * file_;
	};

	size_t const g_buffer_size = 0x400;
	
} // namespace "anonymous"
//------------------------------------------------------------------------------
// global functions
//------------------------------------------------------------------------------
/**
  @brief        entry point.
  @since        2012-12-29T01:56:29+0900
 */
int main(int argc, char * argv[])
{
	if (3 > argc) {
		std::fprintf(
			stderr,
			"ERROR : "
			"invalid arguments : "
			"the number of arguments must be more than 1.\n");
		return 1;
	}

	char const * const out_name = argv[1];

	FILE * const out = std::fopen(out_name, "wb");
	if (HRYKY_NULL == out) {
		std::fprintf(
			stderr,
			"ERROR : "
			"failed to open %s for output.\n",
			out_name);
		return 1;
	}
	AutoClose const close_out(out);

	int index = 2;
	for (; argc != index; ++index) {
		char const * const in_name = argv[index];

		int const in_fd = ::_open(in_name, _O_RDONLY | _O_BINARY);
		if (-1 == in_fd) {
			std::fprintf(
				stderr,
				"ERROR: failed to open %s.\n", in_name);
			return 1;
		}
		
		FILE * const in = ::_fdopen(in_fd, "rb");
		if (HRYKY_NULL == in) {
			std::fprintf(
				stderr,
				"ERROR : "
				"failed to open %s for input.\n",
				in_name);
			return 1;
		}
		AutoClose const close_in(in);

		struct stat status;
		if (0 != fstat(in_fd, &status)) {
			std::fprintf(
				stderr,
				"ERROR : failed to retrieves the status of file.\n");
			return 1;
		}
		size_t const in_size = static_cast<size_t>(status.st_size);
		
		size_t total_read_size = 0;

		while (0 == feof(in)) {
			unsigned char buffer[g_buffer_size];
			size_t const rest_size = in_size - total_read_size;
			if (0 == rest_size) {
				break;
			}
			size_t const size =
				g_buffer_size < rest_size ? g_buffer_size : rest_size;
			size_t const read_size = std::fread(buffer, size, 1, in);
			if (1 != read_size) {
				std::fprintf(
					stderr,
					"ERROR : "
					"failed to read the %zx byte from input %s.\n",
					size,
					in_name);
				return 1;
			}
			if (1 != std::fwrite(buffer, size, 1, out)) {
				std::fprintf(
					stderr,
					"ERROR : "
					"failed to write a buffer out to %s.\n",
					out_name);
				return 1;
			}
			total_read_size += size;
		}
	}
	
	return 0;
}
//------------------------------------------------------------------------------
// static functions
//------------------------------------------------------------------------------
namespace
{
} // namespace "anonymous"
//------------------------------------------------------------------------------
// explicit instantiation
//------------------------------------------------------------------------------
// end of file
