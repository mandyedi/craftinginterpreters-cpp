#ifndef SCANNER_H
#define SCANNER_H

#include "Token.h"

class Scanner
{

public:

    Scanner( std::string &&source );
    ~Scanner();

    // todo: it does not seem good to return like this
    //       return is going to copy the list
    std::list<Token> ScanTokens();

private:

    // todo: init memeber vars here, which c++ version supports it?
    std::string      Source;
    std::list<Token> Tokens;
    int              Start      /*= 0*/;
    unsigned int     Current    /*= 0*/;
    int              Line       /*= 1*/;

	static const std::map<std::string, TokenType> Keywords;

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