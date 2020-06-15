#ifndef SCANNER_H
#define SCANNER_H

#include "Token.h"

class Scanner
{

public:

    Scanner( std::string &&source, std::vector<Token> *tokens );
    ~Scanner();

    // todo: consider using unique ptr for tokens vector
    void ScanTokens();

private:

    std::string      Source;
    std::vector<Token> *Tokens;
    int              Start;
    unsigned int     Current;
    int              Line;

	static const std::unordered_map<std::string, TokenType> Keywords;

    bool IsAtEnd();
    void ScanToken();
    char Advance();
	void AddToken( TokenType type );
    void AddToken( TokenType type, const Object &literal );
    bool Match( char expected );
    char Peek();
    void String();
    bool IsDigit( char c );
    void Number();
    char PeekNext();
	bool IsAlpha( char c );
	bool IsAlphaNumeric( char c );
	void Identifier();
};

#endif // SCANNER_H