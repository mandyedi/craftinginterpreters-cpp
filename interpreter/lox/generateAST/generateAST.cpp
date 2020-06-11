// generateAST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
    Tool for generateing abstract syntax tree
    Output is Expr.cpp
*/

#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>

void defineAst(std::ofstream& outputStream, const std::string& baseName, const std::vector<std::string>& types);
void defineType(std::ofstream& outputStream, const std::string& baseName, const std::string& className, const std::string& fieldList);
void split(const std::string& line, char delimiter, std::vector<std::string>& tokens);
std::string trim(const std::string& line);

class A
{
public:
    A(int x) : X(x) {}

    const int X;
};

int main(int argc, char** argv)
{
    std::ofstream outputStream;
    outputStream.open("..\\lox\\Expr.h");

    defineAst(outputStream, "Expr", {
        "Binary   : Expr left, Token op, Expr right",
        "Grouping : Expr expression",
        "Literal  : Object value",
        "Unary    : Token op, Expr right"
        });

    outputStream.close();

    return 0;
}

void defineAst(std::ofstream& outputStream, const std::string& baseName, const std::vector<std::string>& types)
{
    outputStream << "#ifndef EXPR_H\n#define EXPR_H\n";
    outputStream << "#include \"Token.h\"\n\n";
    outputStream << "class " << baseName << "\n{\n";
    outputStream << "public:\n";
    outputStream << "    virtual ~" << baseName << "() {}\n";
    outputStream << "};\n\n";

    for (auto& type : types)
    {
        std::vector<std::string> tokens;
        split(type, ':', tokens);
        std::string className = trim(tokens[0]);
        std::string fields = trim(tokens[1]);
        defineType(outputStream, baseName, className, fields);
    }

    outputStream << "#endif EXPR_H // EXPR_H\n";
}

void defineType(std::ofstream& outputStream, const std::string& baseName, const std::string& className, const std::string& fieldList)
{
    outputStream << "class " << className << " : public " << baseName << "\n{\n";
    outputStream << "public:\n";

    // Constructor
    outputStream << "    " << className << "( " << fieldList << " )\n";
    // Store paramters
    std::vector<std::string> fields;
    split(fieldList, ',', fields);
    for (unsigned int i = 0; i < fields.size(); i++)
    {
        std::vector<std::string> fieldItems;
        split(trim(fields[i]), ' ', fieldItems);
        std::string name = trim(fieldItems[1]);
        std::string nameCap = name;
        nameCap[0] = std::toupper(nameCap[0]);
        outputStream << "    " << (i == 0 ? ": " : ", ") << nameCap << "(" << name << ")\n" ;
    }
    outputStream << "{}\n\n";

    // Paramters
    for ( auto& field : fields )
    {
        field = trim(field);
        // Class parameters needs to be capitalzed
        std::size_t pos = field.find(" ");
        if (pos != std::string::npos && pos + 1 < field.size())
        {
            field[pos + 1] = std::toupper(field[pos + 1]);
        }

        outputStream << "    const " << field << ";\n";
    }

    outputStream << "};\n\n";
}

void split(const std::string& line, char delimiter, std::vector<std::string>& tokens)
{
    tokens.clear();
    std::stringstream lineStream(line);
    std::string token;
    while (getline(lineStream, token, delimiter))
    {
        tokens.push_back(token);
    }
}

std::string trim(const std::string& line)
{
    const std::string spaces = " \t\v\r\n\f";

    size_t start = line.find_first_not_of(spaces);
    std::string trimmedLine = (start == std::string::npos) ? "" : line.substr(start);

    size_t end = trimmedLine.find_last_not_of(spaces);
    trimmedLine = (end == std::string::npos) ? "" : trimmedLine.substr(0, end + 1);

    return trimmedLine;
}

