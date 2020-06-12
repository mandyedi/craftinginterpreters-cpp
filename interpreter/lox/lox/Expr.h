#ifndef EXPR_H
#define EXPR_H

/*
    This file is automatically generated by generateAST on every lox build.
    Any manually added or changed content is going to be removed.
*/

#include "Token.h"

class Visitor
{
public:
    virtual ~Visitor() {};
    virtual void VisitBinaryExpr( class Binary *expr ) = 0;
    virtual void VisitGroupingExpr( class Grouping *expr ) = 0;
    virtual void VisitLiteralExpr( class Literal *expr ) = 0;
    virtual void VisitUnaryExpr( class Unary *expr ) = 0;
};

class Expr
{
public:
    virtual ~Expr() {}
    virtual void Accept( class Visitor *visitor ) = 0;
};

class Binary : public Expr
{
public:
    Binary( Expr *left, Token op, Expr *right )
    : Left(left)
    , Op(op)
    , Right(right)
{}

    void Accept( Visitor *visitor ) override
    {
        return visitor->VisitBinaryExpr( this );
    }

    Expr *Left;
    Token Op;
    Expr *Right;
};

class Grouping : public Expr
{
public:
    Grouping( Expr *expression )
    : Expression(expression)
{}

    void Accept( Visitor *visitor ) override
    {
        return visitor->VisitGroupingExpr( this );
    }

    Expr *Expression;
};

class Literal : public Expr
{
public:
    Literal( Object value )
    : Value(value)
{}

    void Accept( Visitor *visitor ) override
    {
        return visitor->VisitLiteralExpr( this );
    }

    Object Value;
};

class Unary : public Expr
{
public:
    Unary( Token op, Expr *right )
    : Op(op)
    , Right(right)
{}

    void Accept( Visitor *visitor ) override
    {
        return visitor->VisitUnaryExpr( this );
    }

    Token Op;
    Expr *Right;
};

#endif EXPR_H // EXPR_H
