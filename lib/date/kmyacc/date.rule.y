/**
  @file date.rule.y
  @brief the 'rule' part of KMYACC grammar file for parsing the representation of Date.
  @version $Id: http.rule.y 179 2013-03-20 03:55:46Z hryky.private@gmail.com $

  @sa http://datatracker.ietf.org/doc/rfc2616/

 */
/**
  RFC2616, 3.3.1 Full Date.
 */
date :
	rfc1123_date
	| rfc850_date
	| asctime_date
	;
rfc1123_date :
	wkday ',' SP date1 SP time SP 'G' 'M' 'T'
	{
		hryky::date_type & date = *$4.cast<hryky::date_type>();
		date.week($1.cast<hryky::date::week_type::raw_type>());

		hryky::date_type const & time = *$6.cast<hryky::date_type>();
		date.time(time);

		$$ = $4;
	}
	;
rfc850_date :
	weekday ',' SP date2 SP time SP 'G' 'M' 'T'
	{
		hryky::date_type & date = *$4.cast<hryky::date_type>();
		date.week($1.cast<hryky::date::week_type::raw_type>());

		hryky::date_type const & time = *$6.cast<hryky::date_type>();
		date.time(time);

		$$ = $4;
	}
	;
asctime_date :
	wkday SP date3 SP time SP digits4
	{
		hryky::date_type & date = *$3.cast<hryky::date_type>();
		date.year($7.cast<hryky::date::year_type>());
		date.week($1.cast<hryky::date::week_type::raw_type>());

		hryky::date_type & time = *$5.cast<hryky::date_type>();
		date.time(time);

		$$ = $3;
	}
	;
date1 :
	digits2 SP month SP digits4
	{
		hryky::date_type date;
		date.year($1.cast<hryky::date::year_type>());
		date.month($3.cast<hryky::date::month_type::raw_type>());
		date.day($5.cast<hryky::date::day_type>());
		
		if (hryky_is_null($$ = token_type(date, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
date2 :
	digits2 '-' month '-' digits2
	{
		hryky::date_type date;
		date.year($1.cast<hryky::date::year_type>());
		date.month($3.cast<hryky::date::month_type::raw_type>());
		date.day($5.cast<hryky::date::day_type>());
		
		if (hryky_is_null($$ = token_type(date, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
date3 :
	month SP digits2
	{
		hryky::date_type date;
		date.month($1.cast<hryky::date::month_type::raw_type>());
		date.day($3.cast<hryky::date::day_type>());
		
		if (hryky_is_null($$ = token_type(date, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| month SP SP DIGIT
	{
		hryky::date_type date;
		date.month($1.cast<hryky::date::month_type::raw_type>());
		date.day(ascii::to_digit($3.cast<octet_type>()));
		
		if (hryky_is_null($$ = token_type(date, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
time :
	digits2 ':' digits2 ':' digits2
	{
		hryky::date_type date;
		date.hour($1.cast<hryky::date::hour_type>());
		date.minute($3.cast<hryky::date::minute_type>());
		date.second($5.cast<hryky::date::second_type>());
		
		if (hryky_is_null($$ = token_type(date, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
wkday :
	'M' 'o' 'n'
	{
		$$ = token_type(hryky::date::week::Kind::monday);
	}
	| 'T' 'u' 'e'
	{
		$$ = token_type(hryky::date::week::Kind::tuesday);
	}
	| 'W' 'e' 'd'
	{
		$$ = token_type(hryky::date::week::Kind::wednesday);
	}
	| 'T' 'h' 'u'
	{
		$$ = token_type(hryky::date::week::Kind::thursday);
	}
	| 'F' 'r' 'i'
	{
		$$ = token_type(hryky::date::week::Kind::friday);
	}
	| 'S' 'a' 't'
	{
		$$ = token_type(hryky::date::week::Kind::saturday);
	}
	| 'S' 'u' 'n'
	{
		$$ = token_type(hryky::date::week::Kind::sunday);
	}
	;
weekday :
	'M' 'o' 'n' 'd' 'a' 'y'
	{
		$$ = token_type(hryky::date::week::Kind::monday);
	}
	| 'T' 'u' 'e' 's' 'd' 'a' 'y'
	{
		$$ = token_type(hryky::date::week::Kind::tuesday);
	}
	| 'W' 'e' 'd' 'n' 'e' 's' 'd' 'a' 'y'
	{
		$$ = token_type(hryky::date::week::Kind::wednesday);
	}
	| 'T' 'h' 'u' 'r' 's' 'd' 'a' 'y'
	{
		$$ = token_type(hryky::date::week::Kind::thursday);
	}
	| 'F' 'r' 'i' 'd' 'a' 'y'
	{
		$$ = token_type(hryky::date::week::Kind::friday);
	}
	| 'S' 'a' 't' 'u' 'r' 'd' 'a' 'y'
	{
		$$ = token_type(hryky::date::week::Kind::saturday);
	}
	| 'S' 'u' 'n' 'd' 'a' 'y'
	{
		$$ = token_type(hryky::date::week::Kind::sunday);
	}
	;
month :
	'J' 'a' 'n'
	{
		$$ = token_type(hryky::date::month::Kind::january);
	}
	| 'F' 'e' 'b'
	{
		$$ = token_type(hryky::date::month::Kind::february);
	}
	| 'M' 'a' 'r'
	{
		$$ = token_type(hryky::date::month::Kind::march);
	}
	| 'A' 'p' 'r'
	{
		$$ = token_type(hryky::date::month::Kind::april);
	}
	| 'M' 'a' 'y'
	{
		$$ = token_type(hryky::date::month::Kind::may);
	}
	| 'J' 'u' 'n'
	{
		$$ = token_type(hryky::date::month::Kind::june);
	}
	| 'J' 'u' 'l'
	{
		$$ = token_type(hryky::date::month::Kind::july);
	}
	| 'A' 'u' 'g'
	{
		$$ = token_type(hryky::date::month::Kind::august);
	}
	| 'S' 'e' 'p'
	{
		$$ = token_type(hryky::date::month::Kind::september);
	}
	| 'O' 'c' 't'
	{
		$$ = token_type(hryky::date::month::Kind::october);
	}
	| 'N' 'o' 'v'
	{
		$$ = token_type(hryky::date::month::Kind::november);
	}
	| 'D' 'e' 'c'
	{
		$$ = token_type(hryky::date::month::Kind::december);
	}
	;
