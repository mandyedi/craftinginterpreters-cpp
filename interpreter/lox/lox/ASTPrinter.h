#ifndef ASTPRINTER_H
#define ASTPRINTER_H

#include "Expr.h"

class ASTPrinter : public Visitor
{
public:
	ASTPrinter() {}
	~ASTPrinter() {}

	void Print( Expr *expr );
    void VisitBinaryExpr( Binary *expr ) override;
    void VisitGroupingExpr( Grouping *expr ) override;
    void VisitLiteralExpr( Literal *expr ) override;
    void VisitUnaryExpr( Unary *expr ) override;

private:
    void Parenthesize( const std::string &name, const std::vector<Expr *> exprs );
};

#endif // ASTPRINTER_H
