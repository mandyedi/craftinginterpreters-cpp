#include "stdafx.h"
#include "ASTPrinter.h"

void ASTPrinter::Print( Expr *expr )
{
	expr->Accept( this );
}

void ASTPrinter::VisitBinaryExpr( Binary *expr )
{
    Parenthesize( expr->Op.Lexeme, { expr->Left, expr->Right } );
}

void ASTPrinter::VisitGroupingExpr( Grouping *expr )
{
    Parenthesize( "group", { expr->Expression } );
}

void ASTPrinter::VisitLiteralExpr( Literal *expr )
{
    if ( auto value = std::get_if<Null>(&expr->Value) )
    {
        std::cout << "nil";
    }
    else if ( auto value = std::get_if<double>( &expr->Value ) )
    {
        std::cout << *value;
    }
    else if ( auto value = std::get_if<std::string>( &expr->Value ) )
    {
        std::cout << *value;
    }
}

void ASTPrinter::VisitUnaryExpr( Unary *expr )
{
    Parenthesize( expr->Op.Lexeme, { expr->Right } );
}

void ASTPrinter::Parenthesize( const std::string &name, const std::vector<Expr *> exprs )
{
    std::cout << "(" << name;
    for ( auto *expr : exprs )
    {
        std::cout << " ";
        expr->Accept( this );
    }
    std::cout << ")";
}