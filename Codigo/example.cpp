#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include"z3++.h"

using namespace z3;

clock_t start, end;
double tempo;

/**
   Demonstration of how Z3 can be used to prove validity of
   De Morgan's Duality Law: {e not(x and y) <-> (not x) or ( not y) }
*/
void satisfabilidade() {
    start = clock();

    std::cout << "Satisfiability\n";
    
    context c;

    expr_vector k = c.parse_file("2SAT.cnf.smt2");
    
    solver s(c);
    s.add(k);
    std::cout << s << "\n";
    std::cout << s.to_smt2() << "\n";
    switch (s.check()) {
        case unsat:   std::cout << "Not Satisfable\n"; break;
        case sat:     std::cout << "Satisfiable\n"; std::cout << s.get_model() << std::endl;break;
        case unknown: std::cout << "unknown\n"; break;
    }

    end = clock();
    tempo = ((double) (end-start)) / CLOCKS_PER_SEC;
}

int main() {
    try {
        satisfabilidade(); std::cout << "\n";

        FILE* arquivo = fopen("Tempos.txt","a");

        fprintf(arquivo, "%f\n", tempo);

        fclose(arquivo);
    }
    catch (exception & ex) {
        std::cout << "unexpected error: " << ex << "\n";
    }

    Z3_finalize_memory();
    return 0;
}
