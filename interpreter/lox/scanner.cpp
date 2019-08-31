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
    //       Scannner should be handle only a pointer to the soruce string and Lox manage the source string lifecycle.
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
    unsigned int length = Current - Start + 1;
    std::string text = Source.substr( Start, length );
    Token token( type, text, /*Object literal,*/ Line );
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
    unsigned int length = ( Current - 1 ) - ( Start + 1 ) + 1;
    std::string value = Source.substr( Start + 1, length );
    // todo: Implement value
    //       In the original interpreter value is a java Object that can hold a string or double type
    //       Use std::variant
    //       Also fix it in token.h
    AddToken( TokenType::STRING/*, value as string*/ );
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

    // todo: use variant for value
    AddToken( TokenType::NUMBER/*, value as double*/ );
}

char Scanner::PeekNext()
{
    if ( Current + 1 >= Source.size() )
    {
        return '\0';
    }
    return Source[Current + 1];
}