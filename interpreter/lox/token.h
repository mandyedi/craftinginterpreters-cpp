#ifndef TOKEN_H
#define TOKEN_H

#include "token_type.h"

struct Null
{
	template<typename T>
	bool operator==( T const& rhs ) const
	{
		return false;
	}

	bool operator==( Null const& rhs ) const
	{
		return true;
	}

	bool operator<( Null const& rhs ) const
	{
		return false;
	}
};

typedef std::variant<Null, double, std::string> Object;

class Token
{

public:

	// todo: should I use std::move instead of const refs?
	Token( TokenType type, const std::string& lexeme, const Object& literal, int line )
		: Type( type )
		, Lexeme( lexeme )
		, Literal( literal )
		, Line( line )
	{}

	~Token() {}

	inline std::string GetString()
	{
		std::string literalString = TokenTypeString[(unsigned int)Type] + " " + Lexeme + " ";
		if ( Type == TokenType::NUMBER )
		{
			literalString += std::to_string( std::get<double>( Literal ) );
		}
		else if ( Type == TokenType::STRING )
		{
			literalString += std::get<std::string>( Literal );
		}
		return literalString;
	}

private:

	TokenType	Type;
	std::string Lexeme;
	Object		Literal;
	int			Line;

};

#endif // TOKEN_H