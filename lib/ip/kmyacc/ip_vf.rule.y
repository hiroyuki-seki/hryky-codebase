/**
  @file ip_vf.rule.y
  @brief the 'rule' part of KMYACC grammar file for future IP Address.
  @version $Id: uri.rule.y 127 2013-01-02 11:14:45Z hryky.private@gmail.com $

  @sa http://datatracker.ietf.org/doc/rfc3986/

 */

/**
  RFC3986, 3.2.2. Host
 */
IPvFuture :
	'v' IPvFuture_version_major '.' IPvFuture_version_minor
	{
		if (is_null($$ = token_type(
			ip::vf_type(
				$2.cast<ip::vf_type::major_type>(),
				*$4.cast<ip::vf_type::minor_type>()),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
IPvFuture_version_major :
	HEX
	{
		$$ = ascii::to_hexdig($1.cast<octet_type>());
	}
	| IPvFuture_version_major HEX
	{
		ip::vf_type::major_type major = $1.cast<ip::vf_type::major_type>();
		major = (major << 4) | ascii::to_hexdig($1.cast<octet_type>());

		$$ = major;
	}
	;
IPvFuture_version_minor :
	IPvFuture_version_minor_char
	{
		ip::vf_type::minor_type minor(this->mempool());
		if (!minor.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}

		if (is_null($$ = token_type(minor, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| IPvFuture_version_minor IPvFuture_version_minor_char
	{
		ip::vf_type::minor_type & minor = *$1.cast<ip::vf_type::minor_type>();
		if (!minor.push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}

		if (is_null($$ = token_type(minor, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
IPvFuture_version_minor_char :
	ALPHA | '-' | '_' | '~' | DIGIT | '.' | '!' | '$' | '&' | '\'' | '(' | ')'
	| '*' | '+' | ',' | ';' | '=' | ':'
	;
