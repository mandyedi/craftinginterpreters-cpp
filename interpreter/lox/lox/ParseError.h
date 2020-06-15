#ifndef PARSEERROR_H
#define PARSEERROR_H

#include <stdexcept>

class ParseError : public std::runtime_error
{
public:
	ParseError()
		: std::runtime_error( "" )
	{}

	ParseError( Token token, const std::string &message )
		: std::runtime_error( message )
		, Token_( token )
	{}

	const Token Token_;
};

#endif // PARSEERROR_H
