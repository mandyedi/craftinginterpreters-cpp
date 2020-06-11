class Expr
{
public:
    virtual ~Expr() {}
};

class Binary : public Expr
{
public:
};

class Grouping : public Expr
{
public:
};

class Literal : public Expr
{
public:
};

class Unary : public Expr
{
public:
};

