// lox.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "token_type.h"
#include "token.h"
#include "lox.h"

int main( int argc, char **argv )
{
    Lox lox;

    if ( argc == 1 )
    {
        lox.RunPrompt();
    }
    else if ( argc == 2 )
    {
        std::string fileName( argv[1] );
        lox.RunFile( fileName );
    }
    else
    {
        std::cout << "Usage: jlox [script]\n";
    }

    return 0;
}

