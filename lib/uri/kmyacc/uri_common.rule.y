/**
  @file uri_common.rule.y
  @brief the 'rule' part of KMYACC grammar file for the common representation of URI.
  @version $Id: uri.rule.y 230 2013-08-12 13:50:26Z hryky.private@gmail.com $

  @sa http://datatracker.ietf.org/doc/rfc3986/

 */

/**
  RFC3986, 2.1. Percent-Encoding.
 */
pct_encoded :
	'%' HEX HEX
	{
		uint8_t result = 0u;
		{
			result = ascii::to_hexdig($2.cast<uint8_t>());
		}
		{
			result = static_cast<uint8_t>(
				(result << 4) | ascii::to_hexdig($3.cast<uint8_t>()));
		}
		$$ = result;
	}
	;

/**
  RFC3986, 2.2. Reserved Characters.
 */
uri_gen_delims :
	':' | '/' | '?' | '#' | '[' | ']' | '@';
uri_sub_delims :
	'!' | '$' | '&' | '\'' | '(' | ')' | '*' | '+' | ',' | ';' | '=';
uri_reserved :
	uri_gen_delims | uri_sub_delims;

/**
  RFC3986, 2.3. Unreserved Characters.
 */
uri_unreserved :
	uri_unreserved_ipv4 | uri_unreserved_no_ipv4;
uri_unreserved_no_ipv4 :
	ALPHA | '-' | '_' | '~';
uri_unreserved_ipv4 :
	DIGIT | '.';
uri_unreserved_ipv4s :
	uri_unreserved_ipv4
	| uri_unreserved_ipv4s uri_unreserved_ipv4;

