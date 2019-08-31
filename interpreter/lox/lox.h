#ifndef LOX_H
#define LOX_H

#include <string>

class Lox
{

public:

    Lox();
    ~Lox();

    void RunPrompt();

    void RunFile( const std::string &fileName );

    static void Error( int line, const std::string &message );

private:

    static bool HadError;

    std::string GetInput();

    void Run( const std::string &source );

    static void Report( int line, const std::string &where, const std::string &message );

};

#endif // LOX_H