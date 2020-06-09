
#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include <stack>
#include <cctype>
#include <optional>
#include <sstream>
#include <algorithm>
using namespace std;

#include "bintree_eda.h"
#include <unordered_map>


/* ======================================================================
 * Analizador léxico/sintáctico del lenguaje Calculon++
 * Adaptado del original de Manuel Montenegro
 * ====================================================================== */


class Lexer {
public:
    Lexer(std::istream& in) : in(in) { }

    std::string peek() {
        if (next != "") {
            return next;
        }
        else {
            next = read_next();
            return next;
        }
    }

    std::string get() {
        std::string result = peek();
        next = "";
        return result;
    }

private:
    std::istream& in;

    std::string read_next() {
        ostringstream result;
        char current;
        in >> current;
        while (iswspace(current)) {
            in >> current;
        }


        if (isdigit(current)) {
            result << current;
            while (isdigit(cin.peek())) {
                in >> current;
                result << current;
            }
        }
        else if (isalpha(current)) {
            result << current;
            while (isalnum(cin.peek())) {
                in >> current;
                result << current;
            }
        }
        else if (current == '+' || current == '-' || current == '*' || current == ';' || current == '(' || current == ')') {
            result << current;
        }
        else if (current == ':') {
            result << current;
            in >> current;
            if (current != '=') throw std::domain_error("invalid token: :" + current);
            result << current;
        }
        else {
            throw std::domain_error("invalid_token: " + current);
        }

        return result.str();
    }

private:
    std::string next;
};

using AST = bintree<std::string>;

class Parser {
public:
    Parser(std::istream& in) : l(in) { }

    AST parse() {
        return S();
    }

private:
    Lexer l;

    bool is_identifier(const std::string& token) {
        return (!token.empty() && isalpha(token[0]));
    }

    bool is_identifier_or_number(const std::string& token) {
        return (!token.empty() && isalnum(token[0]));
    }


    AST S() {
        std::string identifier = l.get();
        if (!is_identifier(identifier)) throw std::domain_error("identifier expected, found " + identifier);

        std::string equal = l.get();
        if (equal != ":=") throw std::domain_error(":= expected, found " + equal);

        AST rhs = E();

        std::string semicolon = l.get();
        if (semicolon != ";") throw std::domain_error("; expected, found " + semicolon);

        return { { identifier }, ":=", rhs };
    }

    AST E() {
        AST term = T();
        return Ep(term);
    }

    AST Ep(const AST& left) {
        std::string op = l.peek();
        if (op == "+" || op == "-") {
            l.get();
            AST term = T();
            return Ep({ left, op, term });
        }
        else {
            return left;
        }
    }

    AST T() {
        AST factor = F();
        return Tp(factor);
    }

    AST Tp(const AST& left) {
        std::string op = l.peek();
        if (op == "*") {
            l.get();
            AST factor = F();
            return Tp({ left, "*", factor });
        }
        else {
            return left;
        }
    }

    AST F() {
        std::string next = l.get();
        if (is_identifier_or_number(next)) {
            return { next };
        }
        else if (next == "(") {
            AST inner = E();
            std::string closing = l.get();
            if (closing != ")") throw std::domain_error(") expected, found " + closing);
            return inner;
        }
        else {
            throw std::domain_error("number or identifier expected, found " + next);
        }
    }
};


// Función que lee una instrucción de la entrada y devuelve su AST
AST parse(std::istream& in = std::cin) {
    return Parser(in).parse();
}

int evaluar(bintree<string> arbol, const unordered_map<string, int>& mapaVariables)
{
    string dato = arbol.root();
    if (arbol.left().empty()) //Es un dato
    {
        if (dato[0] < '0' || dato[0]>'9') //Si no es número
        {
            return mapaVariables.at(dato); //Devolvemos el valor de la variable
        }
        else
        {
            return stoi(dato); //El valor del número
        }
    }
    else //Es una operación
    {
        switch (dato[0])
        {
        case '+':
            return evaluar(arbol.left(), mapaVariables) + evaluar(arbol.right(), mapaVariables);
            break;
        case '-':
            return evaluar(arbol.left(), mapaVariables) - evaluar(arbol.right(), mapaVariables);
            break;
        case '*':
            return evaluar(arbol.left(), mapaVariables) * evaluar(arbol.right(), mapaVariables);
            break;
        }
    }
}

bool resuelveCaso() {
    //Cada procesamiento de una operación es lineal en la cantidad de símbolos, ya que la evaluación
    //de una expresión es una recursión de la forma
    // Si el árbol es un solo nodo -> T(arbol) es constante
    // Si el árbol tiene hijos -> T(arbol) = constante + T(hijoIzq) + T(hijoDer)
    // Y esta recursión tiene coste lineal en el número de nodos
    // El acceso al mapa no ordenado es constante
    // Luego hay que ordenar y sacar los valores de las variables, O(v log v)
    // Por lo que todo el coste es O(s+vlog(v)), donde s es el número de símbolos y v el número de variables
    int n;
    cin >> n;
    if (n)
    {
        unordered_map<string, int> mapaVariables; //Mapa para guardar las variables
        //Procesamos las instrucciones
        for (int i = 0; i < n; i++)
        {
            auto arbol = parse(); //Procesar
            assert(arbol.root() == ":=");
            mapaVariables[arbol.left().root()] = evaluar(arbol.right(),mapaVariables); //Ejecutar
            
        }
        //Procesar y ordenar salida
        vector<pair<string, int>> datosVariables;
        for (auto valor : mapaVariables)
        {
            datosVariables.push_back({ valor.first,valor.second });
        }
        sort(datosVariables.begin(), datosVariables.end());
        for (auto valor : datosVariables)
        {
            cout << valor.first << " = " << valor.second << "\n";
        }
        cout << "---\n";


        return true;
    }
    return false;
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}

/*
 3
 x := 3;
 y := 5;
 z := x + y;
 2
 b := 5 + 6 * 3;
 a := b - 1;
 3
 x := 1;
 x := x * 2;
 x := x * 2;
 0
 */
