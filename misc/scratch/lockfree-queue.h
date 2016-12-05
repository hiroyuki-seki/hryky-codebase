
bool push()
{
	size_t const read = this->read_;
	
	size_t write = this->write_;
	bool full = this->full_;

	if (full && read == write) {
		return;
	}

	/// ...

	this->write_ = write;
	this->full_ = write == read;
}

bool pop()
{
	size_t const write = this->write_;
	bool const full = this->full_;
	
	size_t read = this->read_;

	if (!full && read == write) {
		return;
	}

	/// ...

	this->read_ = read;
}
