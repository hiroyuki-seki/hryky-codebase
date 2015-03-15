/**
  @file ip_v4.rule.y
  @brief the 'rule' part of KMYACC grammar file for IPv4 Address.
  @version $Id: uri.rule.y 127 2013-01-02 11:14:45Z hryky.private@gmail.com $

  @sa http://datatracker.ietf.org/doc/rfc3986/

 */

IPv4address :
	ipv4_dec_octet '.' ipv4_dec_octet '.' ipv4_dec_octet '.' ipv4_dec_octet
	{
		if (hryky_is_null($$ = token_type(
			ip::v4::Entity(
				$1.cast<ip::v4::segment_type>(),
				$3.cast<ip::v4::segment_type>(),
				$5.cast<ip::v4::segment_type>(),
				$7.cast<ip::v4::segment_type>()),
			this->derived()->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
ipv4_dec_octet :
	DIGIT
	{
		$$ = ascii::to_digit($1.cast<octet_type>());
	}
	| '1' DIGIT
	{
		$$ = 10 + ascii::to_digit($2.cast<octet_type>());
	}
	| '2' DIGIT
	{
		$$ = 20 + ascii::to_digit($2.cast<octet_type>());
	}
	| '3' DIGIT
	{
		$$ = 30 + ascii::to_digit($2.cast<octet_type>());
	}
	| '4' DIGIT
	{
		$$ = 40 + ascii::to_digit($2.cast<octet_type>());
	}
	| '5' DIGIT
	{
		$$ = 50 + ascii::to_digit($2.cast<octet_type>());
	}
	| '6' DIGIT
	{
		$$ = 60 + ascii::to_digit($2.cast<octet_type>());
	}
	| '7' DIGIT
	{
		$$ = 70 + ascii::to_digit($2.cast<octet_type>());
	}
	| '8' DIGIT
	{
		$$ = 80 + ascii::to_digit($2.cast<octet_type>());
	}
	| '9' DIGIT
	{
		$$ = 90 + ascii::to_digit($2.cast<octet_type>());
	}
	| '1' DIGIT DIGIT
	{
		uint8_t result = 0u;
		{
			result = ascii::to_digit($2.cast<octet_type>());
		}
		{
			result = static_cast<uint8_t>(
				result * 10u + ascii::to_digit($3.cast<octet_type>()));
		}
		$$ = 100u + result;
	}
	| '2' ipv4_digit_0_4 DIGIT
	{
		uint8_t result = 0u;
		{
			result = ascii::to_digit($2.cast<octet_type>());
		}
		{
			result = static_cast<uint8_t>(
				result * 10u + ascii::to_digit($3.cast<octet_type>()));
		}
		$$ = 200u + result;
	}
	| '2' '5' ipv4_digit_0_5
	{
		$$ = 250u + ascii::to_digit($3.cast<octet_type>());
	}
	;
ipv4_digit_1_9 :
	'1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9';
ipv4_digit_0_4 :
	'0' | '1' | '2' | '3' | '4';
ipv4_digit_0_5 :
	'0' | '1' | '2' | '3' | '4' | '5';
