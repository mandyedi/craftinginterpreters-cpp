#include "stdafx.h"
#include "Parser.h"
#include "Expr.h"
#include "lox.h"

Parser::Parser( std::vector<Token> *tokens )
	: Tokens( tokens )
	, Current( 0 )
{}

Parser::~Parser() {}

Expr *Parser::Expression()
{
	return Equality();
}

Expr *Parser::Equality()
{
	Expr *expr = Comparison();

	while ( Match( { TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL } ) )
	{
		const Token &op = Previous();
		Expr *right = Comparison();
		expr = new Binary( expr, op, right );
	}

	return expr;
}

Expr *Parser::Comparison()
{
	Expr *expr = Addition();

	while ( Match( { TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL } ) )
	{
		const Token &op = Previous();
		Expr *right = Addition();
		expr = new Binary( expr, op, right );
	}

	return expr;
}

Expr *Parser::Addition()
{
	Expr *expr = Multiplication();

	while ( Match( { TokenType::MINUS, TokenType::PLUS } ) )
	{
		Token op = Previous();
		Expr *right = Multiplication();
		expr = new Binary( expr, op, right );
	}

	return expr;
}

Expr *Parser::Multiplication() {
	Expr *expr = UnaryMethod();

	while ( Match( { TokenType::SLASH, TokenType::STAR } ) )
	{
		Token op = Previous();
		Expr *right = UnaryMethod();
		expr = new Binary( expr, op, right );
	}

	return expr;
}

Expr *Parser::UnaryMethod()
{
	if ( Match( { TokenType::BANG, TokenType::MINUS } ) )
	{
		Token op = Previous();
		Expr *right = UnaryMethod();
		return new Unary( op, right );
	}

	return Primary();
}

Expr *Parser::Primary()
{
	if ( Match( { TokenType::FALSE } ) )
	{
		return new Literal( false );
	}

	if ( Match( { TokenType::TRUE } ) )
	{
		return new Literal( true );
	}

	if ( Match( { TokenType::NIL } ) )
	{
		return new Literal( Null{} );
	}

	if ( Match( { TokenType::NUMBER, TokenType::STRING } ) )
	{
		return new Literal( Previous().Literal );
	}

	if ( Match( { TokenType::LEFT_PAREN } ) )
	{
		Expr *expr = Expression();
		Consume( TokenType::RIGHT_PAREN, "Expect ')' after expression." );
		return new Literal( false );
	}

	return nullptr;
}

Token Parser::Consume( TokenType type, std::string message )
{
	if ( Check( type ) )
	{
		return Advance();
	}

	throw Error( Peek(), message );
}

ParseError Parser::Error( Token token, const std::string &message )
{
	Lox::Error( token, message );
	return ParseError{};
}

void Parser::Synchronize()
{
	Advance();
	while ( IsAtEnd() == false )
	{
		if ( Previous().Type == TokenType::SEMICOLON )
		{
			return;
		}

		switch ( Peek().Type )
		{
			case TokenType::CLASS:
			case TokenType::FUN:
			case TokenType::VAR:
			case TokenType::FOR:
			case TokenType::IF:
			case TokenType::WHILE:
			case TokenType::PRINT:
			case TokenType::RETURN:
				return;
		}

		Advance();
	}
}

bool Parser::Match( const std::vector<TokenType> types )
{
	for ( auto &type : types )
	{
		if ( Check( type ) == true )
		{
			Advance();
			return true;
		}
	}

	return false;
}

bool Parser::Check( TokenType type )
{
	if ( IsAtEnd() == true )
	{
		return false;
	}

	return Peek().Type == type;
}

Token Parser::Advance()
{
	if ( IsAtEnd() == false )
	{
		Current++;
	}

	return Previous();
}

bool Parser::IsAtEnd()
{
	return Peek().Type == TokenType::EOFILE;
}

const Token &Parser::Peek()
{
	return Tokens->at( Current );
}

const Token &Parser::Previous()
{
	return Tokens->at( Current - 1 );
}
