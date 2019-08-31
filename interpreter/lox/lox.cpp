#include "stdafx.h"
#include "lox.h"
#include "scanner.h"

bool Lox::HadError = false;

Lox::Lox()
{}

Lox::~Lox()
{}

void Lox::RunPrompt()
{
    while ( true )
    {
        std::cout << "> ";

        std::string inputBuffer = GetInput();

        // todo: Where exit should be handled?
        if ( inputBuffer == "exit" )
        {
            std::cout << "exiting...\n";
            return;
        }

        Run( inputBuffer );

        HadError = false;
    }
}

std::string Lox::GetInput()
{
    std::string inputBuffer;

    int c = 0;

    bool run = true;
    while ( run )
    {
        c = getchar();

        if ( c == EOF || c == '\n' )
        {
            // todo: append "\n" ?
            run = false;
        }
        else
        {
            inputBuffer += (char)c;
        }
    }

    return inputBuffer;
}

void Lox::RunFile( const std::string &fileName )
{
    std::cout << "Load file: " << fileName << "\n";

    // todo: handle error such as file not found
    std::ifstream fs( fileName, std::ifstream::in );
    std::stringstream buffer;
    buffer << fs.rdbuf();
    Run( buffer.str() );

    // Indicate an error in the exit code.
    if ( HadError == true )
    {
        // todo: in original code we exit with 65
        //       research what should be do in a c++
        //System.exit(65);
    }
}

void Lox::Run( const std::string &source )
{
    Scanner scanner = Scanner( source );
    std::list<Token> tokens = scanner.ScanTokens();

    // For now, just print the tokens.
    for ( auto token : tokens )
    {
        std::cout << token.GetString() << " ";
    }
    std::cout << "\n";
}

void Lox::Error( int line, const std::string &message )
{
    Report( line, "", message );
}

void Lox::Report( int line, const std::string &where, const std::string &message )
{

    std::cout << "[line " << line << "] Error" << where << ": " << message << "\n";
    HadError = true;
}