#ifndef SCANNER_H
#define SCANNER_H

#include "Token.h"

class Scanner
{

public:

    Scanner( const std::string &source );
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

    bool IsAtEnd();
    void ScanToken();
    char Advance();
    void AddToken( TokenType type );

};

#endif // SCANNER_H