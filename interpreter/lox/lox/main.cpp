// lox.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "token_type.h"
#include "token.h"
#include "lox.h"
#include "Expr.h"
#include "ASTPrinter.h"

int main( int argc, char **argv )
{
    // Test AST
    //Expr *unary = new Binary(
    //    new Unary(
    //        Token( TokenType::MINUS, "-", Null{}, 1 ),
    //        new Literal( 123.0 ) ),
    //        Token( TokenType::STAR, "*", Null{}, 1 ),
    //    new Grouping(
    //        new Literal( 45.67 )
    //    )
    //);

    //ASTPrinter printer;
    //printer.Print( unary );

    //return 0;
    // Test ASR ends

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

