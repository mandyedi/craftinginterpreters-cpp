#include "stdafx.h"
#include "lox.h"
#include "scanner.h"

const std::map<std::string, TokenType> Scanner::Keywords =
{
	{ "and",    TokenType::AND },
	{ "class",  TokenType::CLASS },
	{ "else",   TokenType::ELSE },
	{ "false",  TokenType::FALSE },
	{ "for",    TokenType::FOR },
	{ "fun",    TokenType::FUN },
	{ "if",     TokenType::IF },
	{ "nil",    TokenType::NIL },
	{ "or",     TokenType::OR },
	{ "print",  TokenType::PRINT },
	{ "return", TokenType::RETURN },
	{ "super",  TokenType::SUPER },
	{ "this",   TokenType::THIS },
	{ "true",   TokenType::TRUE },
	{ "var",    TokenType::VAR },
	{ "while",  TokenType::WHILE }
};

Scanner::Scanner( std::string &&source )
	: Source( std::move( source ) )
	, Start( 0 )
	, Current( 0 )
	, Line( 0 )
{}

Scanner::~Scanner()
{}

const std::list<Token>& Scanner::ScanTokens()
{
	while ( IsAtEnd() == false )
	{
		Start = Current;
		ScanToken();
	}

	Token token( TokenType::EOFILE, "", Null{}, Line );
	Tokens.push_back( std::move( token ) );

	return Tokens;
}

bool Scanner::IsAtEnd()
{
	return Current >= Source.size();
}

void Scanner::ScanToken()
{
	char c = Advance();
	switch ( c )
	{
	case '(': AddToken( TokenType::LEFT_PAREN ); break;
	case ')': AddToken( TokenType::RIGHT_PAREN ); break;
	case '{': AddToken( TokenType::LEFT_BRACE ); break;
	case '}': AddToken( TokenType::RIGHT_BRACE ); break;
	case ',': AddToken( TokenType::COMMA ); break;
	case '.': AddToken( TokenType::DOT ); break;
	case '-': AddToken( TokenType::MINUS ); break;
	case '+': AddToken( TokenType::PLUS ); break;
	case ';': AddToken( TokenType::SEMICOLON ); break;
	case '*': AddToken( TokenType::STAR ); break;
	case '!': AddToken( Match( '=' ) ? TokenType::BANG_EQUAL : TokenType::BANG ); break;
	case '=': AddToken( Match( '=' ) ? TokenType::EQUAL_EQUAL : TokenType::EQUAL ); break;
	case '<': AddToken( Match( '=' ) ? TokenType::LESS_EQUAL : TokenType::LESS ); break;
	case '>': AddToken( Match( '=' ) ? TokenType::GREATER_EQUAL : TokenType::GREATER ); break;
	case '/':
		if ( Match( '/' ) )
		{
			// A comment goes until the end of the line.
			while ( Peek() != '\n' && !IsAtEnd() )
			{
				Advance();
			}
		}
		else
		{
			AddToken( TokenType::SLASH );
		}
		break;
	case ' ':
	case '\r':
	case '\t':
		// Ignore whitespace.
		break;
	case '\n':
		Line++;
		break;
	case '"': String(); break;
	default:
		if ( IsDigit( c ) )
		{
			Number();
		}
		else if ( IsAlpha( c ) )
		{
			Identifier();
		}
		else
		{
			Lox::Error( Line, "Unexpected character." );
		}
		break;
	}
}

char Scanner::Advance()
{
	Current++;
	return Source[Current - 1];
}

void Scanner::AddToken( TokenType type )
{
	AddToken( type, Null{} );
}

void Scanner::AddToken( TokenType type, const Object& literal )
{
	unsigned int length = Current - Start;
	std::string lexeme = Source.substr( Start, length );
	Token token( type, lexeme, literal, Line );
	Tokens.push_back( std::move( token ) );
}

bool Scanner::Match( char expected )
{
	if ( IsAtEnd() )
	{
		return false;
	}

	if ( Source[Current] != expected )
	{
		return false;
	}

	Current++;
	return true;
}

char Scanner::Peek()
{
	if ( IsAtEnd() )
	{
		return '\0';
	}
	return Source[Current];
}

void Scanner::String()
{
	while ( Peek() != '"' && IsAtEnd() == false )
	{
		if ( Peek() == '\n' )
		{
			Line++;
		}
		Advance();
	}

	// Unterminated string.
	if ( IsAtEnd() )
	{
		Lox::Error( Line, "Unterminated string." );
		return;
	}

	// The closing ".
	Advance();

	// Trim the surrounding quotes.
	// If Lox supported escape sequences like \n, we’d unescape those here.
	unsigned int length = Current - Start;
	std::string value = Source.substr( Start + 1, length - 2 );
	AddToken( TokenType::STRING, value );
}

bool Scanner::IsDigit( char c )
{
	return c >= '0' && c <= '9';
}

void Scanner::Number()
{
	while ( IsDigit( Peek() ) )
	{
		Advance();
	}

	// Look for a fractional part.
	if ( Peek() == '.' && IsDigit( PeekNext() ) )
	{
		// Consume the "."
		Advance();

		while ( IsDigit( Peek() ) )
		{
			Advance();
		}
	}

	std::string s = Source.substr( Start, Current - Start );
	double number = std::stod( s );
	AddToken( TokenType::NUMBER, number );
}

char Scanner::PeekNext()
{
	if ( Current + 1 >= Source.size() )
	{
		return '\0';
	}
	return Source[Current + 1];
}

bool Scanner::IsAlpha( char c )
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::IsAlphaNumeric( char c )
{
	return IsAlpha( c ) || IsDigit( c );
}

void Scanner::Identifier()
{
	while ( IsAlphaNumeric( Peek() ) )
	{
		Advance();
	}

	unsigned int length = Current - Start;
	std::string s = Source.substr( Start, length );
	auto keyword = Keywords.find( s );
	if ( keyword == Keywords.end() )
	{
		AddToken( TokenType::IDENTIFIER );
	}
	else
	{
		AddToken( keyword->second );
	}
}