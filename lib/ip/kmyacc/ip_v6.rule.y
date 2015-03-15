/**
  @file ip_v6.rule.y
  @brief the 'rule' part of KMYACC grammar file for IPv6 Address.
  @version $Id: uri.rule.y 127 2013-01-02 11:14:45Z hryky.private@gmail.com $

  @sa http://datatracker.ietf.org/doc/rfc3986/

 */

IPv6address :
	IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $13.cast<ip::v6_type>();
		ipv6->segment(0, $1.cast<ip::v6::segment_type>());
		ipv6->segment(1, $3.cast<ip::v6::segment_type>());
		ipv6->segment(2, $5.cast<ip::v6::segment_type>());
		ipv6->segment(3, $7.cast<ip::v6::segment_type>());
		ipv6->segment(4, $9.cast<ip::v6::segment_type>());
		ipv6->segment(5, $11.cast<ip::v6::segment_type>());
		$$ = $13;
	}
	| ':' ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $13.cast<ip::v6_type>();
		ipv6->segment(0, 0);
		ipv6->segment(1, $3.cast<ip::v6::segment_type>());
		ipv6->segment(2, $5.cast<ip::v6::segment_type>());
		ipv6->segment(3, $7.cast<ip::v6::segment_type>());
		ipv6->segment(4, $9.cast<ip::v6::segment_type>());
		ipv6->segment(5, $11.cast<ip::v6::segment_type>());
		$$ = $13;
	}
	| ':' ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $11.cast<ip::v6_type>();
		ipv6->segment(0, 0);
		ipv6->segment(1, 0);
		ipv6->segment(2, $3.cast<ip::v6::segment_type>());
		ipv6->segment(3, $5.cast<ip::v6::segment_type>());
		ipv6->segment(4, $7.cast<ip::v6::segment_type>());
		ipv6->segment(5, $9.cast<ip::v6::segment_type>());
		$$ = $11;
	}
	| IPv6_h16 ':' ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $12.cast<ip::v6_type>();
		ipv6->segment(0, $1.cast<ip::v6::segment_type>());
		ipv6->segment(1, 0);
		ipv6->segment(2, $4.cast<ip::v6::segment_type>());
		ipv6->segment(3, $6.cast<ip::v6::segment_type>());
		ipv6->segment(4, $8.cast<ip::v6::segment_type>());
		ipv6->segment(5, $10.cast<ip::v6::segment_type>());
		$$ = $12;
	}
	| ':' ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $9.cast<ip::v6_type>();
		ipv6->segment(0, 0);
		ipv6->segment(1, 0);
		ipv6->segment(2, 0);
		ipv6->segment(3, $3.cast<ip::v6::segment_type>());
		ipv6->segment(4, $5.cast<ip::v6::segment_type>());
		ipv6->segment(5, $7.cast<ip::v6::segment_type>());
		$$ = $9;
	}
	| IPv6_h16 ':' ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $10.cast<ip::v6_type>();
		ipv6->segment(0, $1.cast<ip::v6::segment_type>());
		ipv6->segment(1, 0);
		ipv6->segment(2, 0);
		ipv6->segment(3, $4.cast<ip::v6::segment_type>());
		ipv6->segment(4, $6.cast<ip::v6::segment_type>());
		ipv6->segment(5, $8.cast<ip::v6::segment_type>());
		$$ = $10;
	}
	| IPv6_h16 ':' IPv6_h16 ':' ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $12.cast<ip::v6_type>();
		ipv6->segment(0, $1.cast<ip::v6::segment_type>());
		ipv6->segment(1, $3.cast<ip::v6::segment_type>());
		ipv6->segment(2, 0);
		ipv6->segment(3, $6.cast<ip::v6::segment_type>());
		ipv6->segment(4, $8.cast<ip::v6::segment_type>());
		ipv6->segment(5, $10.cast<ip::v6::segment_type>());
		$$ = $12;
	}
	| ':' ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $7.cast<ip::v6_type>();
		ipv6->segment(0, 0);
		ipv6->segment(1, 0);
		ipv6->segment(2, 0);
		ipv6->segment(3, 0);
		ipv6->segment(4, $3.cast<ip::v6::segment_type>());
		ipv6->segment(5, $5.cast<ip::v6::segment_type>());
		$$ = $7;
	}
	| IPv6_h16 ':' ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $8.cast<ip::v6_type>();
		ipv6->segment(0, $1.cast<ip::v6::segment_type>());
		ipv6->segment(1, 0);
		ipv6->segment(2, 0);
		ipv6->segment(3, 0);
		ipv6->segment(4, $4.cast<ip::v6::segment_type>());
		ipv6->segment(5, $6.cast<ip::v6::segment_type>());
		$$ = $8;
	}
	| IPv6_h16 ':' IPv6_h16 ':' ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $10.cast<ip::v6_type>();
		ipv6->segment(0, $1.cast<ip::v6::segment_type>());
		ipv6->segment(1, $3.cast<ip::v6::segment_type>());
		ipv6->segment(2, 0);
		ipv6->segment(3, 0);
		ipv6->segment(4, $6.cast<ip::v6::segment_type>());
		ipv6->segment(5, $8.cast<ip::v6::segment_type>());
		$$ = $10;
	}
	| IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $12.cast<ip::v6_type>();
		ipv6->segment(0, $1.cast<ip::v6::segment_type>());
		ipv6->segment(1, $3.cast<ip::v6::segment_type>());
		ipv6->segment(2, $5.cast<ip::v6::segment_type>());
		ipv6->segment(3, 0);
		ipv6->segment(4, $8.cast<ip::v6::segment_type>());
		ipv6->segment(5, $10.cast<ip::v6::segment_type>());
		$$ = $12;
	}
	| ':' ':' IPv6_h16 ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $5.cast<ip::v6_type>();
		ipv6->segment(0, 0);
		ipv6->segment(1, 0);
		ipv6->segment(2, 0);
		ipv6->segment(3, 0);
		ipv6->segment(4, 0);
		ipv6->segment(5, $3.cast<ip::v6::segment_type>());
		$$ = $5;
	}
	| IPv6_h16 ':' ':' IPv6_h16 ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $6.cast<ip::v6_type>();
		ipv6->segment(0, $1.cast<ip::v6::segment_type>());
		ipv6->segment(1, 0);
		ipv6->segment(2, 0);
		ipv6->segment(3, 0);
		ipv6->segment(4, 0);
		ipv6->segment(5, $4.cast<ip::v6::segment_type>());
		$$ = $6;
	}
	| IPv6_h16 ':' IPv6_h16 ':' ':' IPv6_h16 ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $8.cast<ip::v6_type>();
		ipv6->segment(0, $1.cast<ip::v6::segment_type>());
		ipv6->segment(1, $3.cast<ip::v6::segment_type>());
		ipv6->segment(2, 0);
		ipv6->segment(3, 0);
		ipv6->segment(4, 0);
		ipv6->segment(5, $6.cast<ip::v6::segment_type>());
		$$ = $8;
	}
	| IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' ':' IPv6_h16 ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $10.cast<ip::v6_type>();
		ipv6->segment(0, $1.cast<ip::v6::segment_type>());
		ipv6->segment(1, $3.cast<ip::v6::segment_type>());
		ipv6->segment(2, $5.cast<ip::v6::segment_type>());
		ipv6->segment(3, 0);
		ipv6->segment(4, 0);
		ipv6->segment(5, $8.cast<ip::v6::segment_type>());
		$$ = $10;
	}
	| IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' ':' IPv6_h16 ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $12.cast<ip::v6_type>();
		ipv6->segment(0, $1.cast<ip::v6::segment_type>());
		ipv6->segment(1, $3.cast<ip::v6::segment_type>());
		ipv6->segment(2, $5.cast<ip::v6::segment_type>());
		ipv6->segment(3, $7.cast<ip::v6::segment_type>());
		ipv6->segment(4, 0);
		ipv6->segment(5, $10.cast<ip::v6::segment_type>());
		$$ = $12;
	}
	| ':' ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $3.cast<ip::v6_type>();
		ipv6->segment(0, 0);
		ipv6->segment(1, 0);
		ipv6->segment(2, 0);
		ipv6->segment(3, 0);
		ipv6->segment(4, 0);
		ipv6->segment(5, 0);
		$$ = $3;
	}
	| IPv6_h16 ':' ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $4.cast<ip::v6_type>();
		ipv6->segment(0, $1.cast<ip::v6::segment_type>());
		ipv6->segment(1, 0);
		ipv6->segment(2, 0);
		ipv6->segment(3, 0);
		ipv6->segment(4, 0);
		ipv6->segment(5, 0);
		$$ = $4;
	}
	| IPv6_h16 ':' IPv6_h16 ':' ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $6.cast<ip::v6_type>();
		ipv6->segment(0, $1.cast<ip::v6::segment_type>());
		ipv6->segment(1, $3.cast<ip::v6::segment_type>());
		ipv6->segment(2, 0);
		ipv6->segment(3, 0);
		ipv6->segment(4, 0);
		ipv6->segment(5, 0);
		$$ = $6;
	}
	| IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $8.cast<ip::v6_type>();
		ipv6->segment(0, $1.cast<ip::v6::segment_type>());
		ipv6->segment(1, $3.cast<ip::v6::segment_type>());
		ipv6->segment(2, $5.cast<ip::v6::segment_type>());
		ipv6->segment(3, 0);
		ipv6->segment(4, 0);
		ipv6->segment(5, 0);
		$$ = $8;
	}
	| IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $10.cast<ip::v6_type>();
		ipv6->segment(0, $1.cast<ip::v6::segment_type>());
		ipv6->segment(1, $3.cast<ip::v6::segment_type>());
		ipv6->segment(2, $5.cast<ip::v6::segment_type>());
		ipv6->segment(3, $7.cast<ip::v6::segment_type>());
		ipv6->segment(4, 0);
		ipv6->segment(5, 0);
		$$ = $10;
	}
	| IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' ':' IPv6_ls32
	{
		ip::v6_type * ipv6 = $12.cast<ip::v6_type>();
		ipv6->segment(0, $1.cast<ip::v6::segment_type>());
		ipv6->segment(1, $3.cast<ip::v6::segment_type>());
		ipv6->segment(2, $5.cast<ip::v6::segment_type>());
		ipv6->segment(3, $7.cast<ip::v6::segment_type>());
		ipv6->segment(4, $9.cast<ip::v6::segment_type>());
		ipv6->segment(5, 0);
		$$ = $12;
	}
	| ':' ':' IPv6_h16
	{
		if (hryky_is_null($$ = token_type(
			ip::v6_type(
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				$3.cast<ip::v6::segment_type>()),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| IPv6_h16 ':' ':' IPv6_h16
	{
		if (hryky_is_null($$ = token_type(
			ip::v6_type(
				$1.cast<ip::v6::segment_type>(),
				0,
				0,
				0,
				0,
				0,
				0,
				$4.cast<ip::v6::segment_type>()),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| IPv6_h16 ':' IPv6_h16 ':' ':' IPv6_h16
	{
		if (hryky_is_null($$ = token_type(
			ip::v6_type(
				$1.cast<ip::v6::segment_type>(),
				$3.cast<ip::v6::segment_type>(),
				0,
				0,
				0,
				0,
				0,
				$6.cast<ip::v6::segment_type>()),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' ':' IPv6_h16
	{
		if (hryky_is_null($$ = token_type(
			ip::v6_type(
				$1.cast<ip::v6::segment_type>(),
				$3.cast<ip::v6::segment_type>(),
				$5.cast<ip::v6::segment_type>(),
				0,
				0,
				0,
				0,
				$8.cast<ip::v6::segment_type>()),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' ':' IPv6_h16
	{
		if (hryky_is_null($$ = token_type(
			ip::v6_type(
				$1.cast<ip::v6::segment_type>(),
				$3.cast<ip::v6::segment_type>(),
				$5.cast<ip::v6::segment_type>(),
				$7.cast<ip::v6::segment_type>(),
				0,
				0,
				0,
				$10.cast<ip::v6::segment_type>()),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' ':' IPv6_h16
	{
		if (hryky_is_null($$ = token_type(
			ip::v6_type(
				$1.cast<ip::v6::segment_type>(),
				$3.cast<ip::v6::segment_type>(),
				$5.cast<ip::v6::segment_type>(),
				$7.cast<ip::v6::segment_type>(),
				$9.cast<ip::v6::segment_type>(),
				0,
				0,
				$12.cast<ip::v6::segment_type>()),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' ':' IPv6_h16
	{
		if (hryky_is_null($$ = token_type(
			ip::v6_type(
				$1.cast<ip::v6::segment_type>(),
				$3.cast<ip::v6::segment_type>(),
				$5.cast<ip::v6::segment_type>(),
				$7.cast<ip::v6::segment_type>(),
				$9.cast<ip::v6::segment_type>(),
				$11.cast<ip::v6::segment_type>(),
				0,
				$14.cast<ip::v6::segment_type>()),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| ':' ':'
	{
		if (hryky_is_null($$ = token_type(
			ip::v6_type(
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| IPv6_h16 ':' ':'
	{
		if (hryky_is_null($$ = token_type(
			ip::v6_type(
				$1.cast<ip::v6::segment_type>(),
				0,
				0,
				0,
				0,
				0,
				0,
				0),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| IPv6_h16 ':' IPv6_h16 ':' ':'
	{
		if (hryky_is_null($$ = token_type(
			ip::v6_type(
				$1.cast<ip::v6::segment_type>(),
				$3.cast<ip::v6::segment_type>(),
				0,
				0,
				0,
				0,
				0,
				0),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' ':'
	{
		if (hryky_is_null($$ = token_type(
			ip::v6_type(
				$1.cast<ip::v6::segment_type>(),
				$3.cast<ip::v6::segment_type>(),
				$5.cast<ip::v6::segment_type>(),
				0,
				0,
				0,
				0,
				0),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' ':'
	{
		if (hryky_is_null($$ = token_type(
			ip::v6_type(
				$1.cast<ip::v6::segment_type>(),
				$3.cast<ip::v6::segment_type>(),
				$5.cast<ip::v6::segment_type>(),
				$7.cast<ip::v6::segment_type>(),
				0,
				0,
				0,
				0),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' ':'
	{
		if (hryky_is_null($$ = token_type(
			ip::v6_type(
				$1.cast<ip::v6::segment_type>(),
				$3.cast<ip::v6::segment_type>(),
				$5.cast<ip::v6::segment_type>(),
				$7.cast<ip::v6::segment_type>(),
				$9.cast<ip::v6::segment_type>(),
				0,
				0,
				0),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' ':'
	{
		if (hryky_is_null($$ = token_type(
			ip::v6_type(
				$1.cast<ip::v6::segment_type>(),
				$3.cast<ip::v6::segment_type>(),
				$5.cast<ip::v6::segment_type>(),
				$7.cast<ip::v6::segment_type>(),
				$9.cast<ip::v6::segment_type>(),
				$11.cast<ip::v6::segment_type>(),
				0,
				0),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' IPv6_h16 ':' ':'
	{
		if (hryky_is_null($$ = token_type(
			ip::v6_type(
				$1.cast<ip::v6::segment_type>(),
				$3.cast<ip::v6::segment_type>(),
				$5.cast<ip::v6::segment_type>(),
				$7.cast<ip::v6::segment_type>(),
				$9.cast<ip::v6::segment_type>(),
				$11.cast<ip::v6::segment_type>(),
				$13.cast<ip::v6::segment_type>(),
				0),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
IPv6_ls32 :
	IPv6_h16 ':' IPv6_h16
	{
		if (hryky_is_null($$ = token_type(ip::v6_type(), this->mempool()))) {
			KMYACC_ABORT;
		}
		ip::v6_type * ipv6 = $$.cast<ip::v6_type>();

		ipv6->segment(
			ip::v6::g_segments_size - 2,
			$1.cast<ip::v6::segment_type>());
		ipv6->segment(
			ip::v6::g_segments_size - 1,
			$3.cast<ip::v6::segment_type>());
	}
	| IPv4address
	{
		if (hryky_is_null($$ = token_type(ip::v6_type(), this->mempool()))) {
			KMYACC_ABORT;
		}
		ip::v6_type * ipv6 = $$.cast<ip::v6_type>();
		ip::v4_type const * ipv4 = $1.cast<ip::v4_type>();

		typedef ip::v6::segment_type segment_type;

		ipv6->segment(
			ip::v6::g_segments_size - 2,
			static_cast<segment_type>(
				(ipv4->segment(0) << 8) | ipv4->segment(1)));
		ipv6->segment(
			ip::v6::g_segments_size - 1,
			static_cast<segment_type>(
				(ipv4->segment(2) << 8) | ipv4->segment(3)));
	}
	;
IPv6_h16 :
	HEX
	{
		$$ = ascii::to_hexdig($1.cast<octet_type>());
	}
	| HEX HEX
	{
		uint16_t result = 0u;
		{
			result = ascii::to_hexdig($1.cast<octet_type>());
		}
		{
			result = static_cast<uint16_t>(
				(result << 4) | ascii::to_hexdig($2.cast<octet_type>()));
		}
		
		$$ = result;
	}
	| HEX HEX HEX
	{
		uint16_t result = 0u;
		{
			result = ascii::to_hexdig($1.cast<octet_type>());
		}
		{
			result = static_cast<uint16_t>(
				(result << 4) | ascii::to_hexdig($2.cast<octet_type>()));
		}
		{
			result = static_cast<uint16_t>(
				(result << 4) | ascii::to_hexdig($3.cast<octet_type>()));
		}
		
		$$ = result;
	}
	| HEX HEX HEX HEX
	{
		uint16_t result = 0u;
		{
			result = ascii::to_hexdig($1.cast<octet_type>());
		}
		{
			result = static_cast<uint16_t>(
				(result << 4) | ascii::to_hexdig($2.cast<octet_type>()));
		}
		{
			result = static_cast<uint16_t>(
				(result << 4) | ascii::to_hexdig($3.cast<octet_type>()));
		}
		{
			result = static_cast<uint16_t>(
				(result << 4) | ascii::to_hexdig($4.cast<octet_type>()));
		}
		
		$$ = result;
	}
	;
