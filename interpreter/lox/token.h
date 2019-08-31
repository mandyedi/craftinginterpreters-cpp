#ifndef TOKEN_H
#define TOKEN_H

#include "token_type.h"

// todo: Object literal
//       In the original code there is an extra variable: Object literal
//       But it is never used and null is passed to the addToken(TokenType type, Object literal) method

class Token
{

public:

    Token( TokenType type, const std::string &lexeme, /*Object literal,*/ int line )
    : Type( type )
    , Lexeme( lexeme )
    //, Literal( literal )
    , Line( line )
    {}

    ~Token(){}

    inline std::string GetString()
    {
        // todo: implement
        //std::string s = Type + " " + Lexeme /*+ " " + literal*/;
        return Lexeme;
    }

private:

    TokenType Type;
    std::string Lexeme;
    //Object literal;
    int Line; // [location]

};

#endif // TOKEN_H