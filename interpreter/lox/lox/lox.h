#ifndef LOX_H
#define LOX_H

#include "token.h"

class Lox
{

public:

    Lox();
    ~Lox();

    void RunPrompt();

    void RunFile( const std::string &fileName );

    static void Error( unsigned int line, const std::string &message );

    static void Error( Token token, const std::string &message );

private:

    static bool HadError;

    std::string GetInput();

    void Run( std::string &source );

    static void Report( int line, const std::string &where, const std::string &message );

};

#endif // LOX_H