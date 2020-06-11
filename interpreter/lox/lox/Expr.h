#ifndef EXPR_H
#define EXPR_H
#include "Token.h"

class Expr
{
public:
    virtual ~Expr() {}
};

class Binary : public Expr
{
public:
    Binary( Expr left, Token op, Expr right )
    : Left(left)
    , Op(op)
    , Right(right)
{}

    const Expr Left;
    const Token Op;
    const Expr Right;
};

class Grouping : public Expr
{
public:
    Grouping( Expr expression )
    : Expression(expression)
{}

    const Expr Expression;
};

class Literal : public Expr
{
public:
    Literal( Object value )
    : Value(value)
{}

    const Object Value;
};

class Unary : public Expr
{
public:
    Unary( Token op, Expr right )
    : Op(op)
    , Right(right)
{}

    const Token Op;
    const Expr Right;
};

#endif EXPR_H // EXPR_H
