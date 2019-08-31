#include "stdafx.h"
#include "lox.h"
#include "scanner.h"

Scanner::Scanner( const std::string &source )
: Source( source ) // todo: is it ok? reserach modenr c++ solutions
, Start( 0 )
, Current( 0 )
, Line( 0 )
{}

Scanner::~Scanner()
{}

std::list<Token> Scanner::ScanTokens()
{
    while ( IsAtEnd() == false )
    {
        Start = Current;
        ScanToken();
    }

    // todo: std::move https://en.cppreference.com/w/cpp/container/list/push_back
    //       reserach std::move
    //       Scanne should be handle only a pointer to the soruce string and Lox manage the source string lifeczcle.
    Token token( TokenType::EOFILE, "", Line );
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
        default:
            Lox::Error( Line, "Unexpected character." );
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
    unsigned int length = Current - Start + 1;
    std::string text = Source.substr( Start, length );
    Token token( type, text, Line );
    Tokens.push_back( std::move( token ) );
}