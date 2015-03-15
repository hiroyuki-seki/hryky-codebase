/**
  @file uri_authority.rule.y
  @brief the 'rule' part of KMYACC grammar file for URI.
  @version $Id: uri.rule.y 230 2013-08-12 13:50:26Z hryky.private@gmail.com $

  @sa http://datatracker.ietf.org/doc/rfc3986/

 */

/**
  RFC3986, 3.2. Authority.
 */
authority :
	userinfo '@' uri_host uri_port
	{
		uri::authority_type authority(this->mempool());
		authority.userinfo(*$1.cast<uri::userinfo_type>());
		authority.host(*$3.cast<uri::host_type>());
		authority.port(*$4.cast<uri::port_type>());
		
		if (hryky_is_null($$ = token_type(authority, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| userinfo '@' uri_host
	{
		uri::authority_type authority(this->mempool());
		authority.userinfo(*$1.cast<uri::userinfo_type>());
		authority.host(*$3.cast<uri::host_type>());
		
		if (hryky_is_null($$ = token_type(authority, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| uri_host uri_port
	{
		uri::authority_type authority(this->mempool());
		authority.host(*$1.cast<uri::host_type>());
		authority.port(*$2.cast<uri::port_type>());
		
		if (hryky_is_null($$ = token_type(authority, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| uri_host
	{
		uri::authority_type authority(this->mempool());
		authority.host(*$1.cast<uri::host_type>());
		
		if (hryky_is_null($$ = token_type(authority, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC3986, 3.2.1. User Information.
  @note
  - shares the definition with reg_name to prevent the conflict.
 */
userinfo :
	reg_name_octets
	{
		if (hryky_is_null($$ = token_type(
			uri::userinfo_type(*$1.cast<octets_type>()),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| userinfo_colon
	{
		if (hryky_is_null($$ = token_type(
			uri::userinfo_type(*$1.cast<octets_type>()),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
userinfo_colon :
	':'
	{
		octets_type octets(this->mempool());
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = token_type(octets, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| userinfo_colon userinfo_colon_char
	{
		octets_type & octets = *$1.cast<octets_type>();
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	;
userinfo_colon_char :
	uri_unreserved
	| pct_encoded
	| uri_sub_delims
	| ':'
	;

/**
  RFC3986, 3.2.2. Host.

  @todo
  - The determination between IPv4address and reg_name is not supported in
    this parser.
 */
uri_host :
	'[' IPv6address ']'
	{
		uri::host_type host(this->mempool());
		host.ipv6(*$2.cast<ip::v6_type>());

		if (hryky_is_null($$ = token_type(host, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| '[' IPvFuture ']'
	{
		uri::host_type host(this->mempool());
		host.ipvf(*$2.cast<ip::vf_type>());

		if (hryky_is_null($$ = token_type(host, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	// | IPv4address
	| reg_name
	{
		uri::host_type host(this->mempool());
		host.regname(*$1.cast<uri::regname_type>());

		if (hryky_is_null($$ = token_type(host, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
/**
  @note
  - To distinguish from IPv4Address, a reg_name must exclude characters
    representing digits and period.
  - But, the invalid representation for IPv4Address is not distinguished easily.
    For exapmple, 256.0.0.1 is not valid IPv4Address. It must be parsed as
    reg_name.
  - The determination of IPAddress is delaied.
 */
reg_name :
	reg_name_octets
	{
		if (hryky_is_null($$ = token_type(
			uri::regname_type(*$1.cast<octets_type>()), this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
reg_name_octets :
	reg_name_char
	{
		octets_type octets(this->mempool());
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		
		if (hryky_is_null($$ = token_type(octets, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| '.' reg_name_octets
	{
		octets_type & octets = *$2.cast<octets_type>();
		octets_type::iterator const inserted =
			octets.insert(octets.begin(), $1.cast<octet_type>());
		if (inserted == octets.end()) {
			KMYACC_ABORT;
		}
		
		$$ = $2;
	}
	| DIGIT reg_name_octets
	{
		octets_type & octets = *$2.cast<octets_type>();
		octets_type::iterator const inserted =
			octets.insert(octets.begin(), $1.cast<octet_type>());
		if (inserted == octets.end()) {
			KMYACC_ABORT;
		}
		
		$$ = $2;
	}
	| reg_name_octets reg_name_char
	{
		octets_type & octets = *$1.cast<octets_type>();
		if (!octets.push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		
		$$ = $1;
	}
	;
reg_name_char :
	uri_unreserved
	| pct_encoded
	| uri_sub_delims
	;
uri_port :
	':' uri_port_digits
	{
		if (hryky_is_null($$ = token_type(
			uri::port_type($2.cast<uri::port_type::number_type>()),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
uri_port_digits :
	DIGIT
	{
		$$ = token_type(ascii::to_digit($1.cast<octet_type>()));
	}
	| uri_port_digits DIGIT
	{
		$$ = token_type(static_cast<uint16_t>(
			$1.cast<uint16_t>() * 10u
			+ ascii::to_digit($2.cast<octet_type>())));
	}
	;

