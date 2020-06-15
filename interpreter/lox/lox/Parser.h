#ifndef PARSER_H
#define PARSER_H

#include "token.h"

class Expr;

class Parser
{
public:
	Parser( std::vector<Token> *tokens );
	~Parser();

private:

	Expr *Expression();
	Expr *Equality();
	Expr *Comparison();
	Expr *Addition();
	Expr *Multiplication();
	Expr *UnaryMethod();
	Expr *Primary();

	Token Consume( TokenType type, std::string message );

	bool Match( const std::vector<TokenType> types );
	bool Check( TokenType type );
	Token Advance();
	bool IsAtEnd();
	const Token &Peek();
	const Token &Previous();

	const std::vector<Token> *Tokens;
	int Current;
};

#endif // PARSER_H
