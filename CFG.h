#ifndef TEMA3LFA_CFG_H
#define TEMA3LFA_CFG_H
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <set>

class CFG {
    int nrNeterminale;
    std::vector<std::string> neterminale;
    int nrProductii;
    std::vector<std::vector<std::string> > productii;
    std::string simbolStart;
    std::map <std::string, int> indiciNeterminale;
    int nrCuvinte;
    std::vector<std::string> cuvinte;

public:
    CFG() = default;
    void citesteCFG();
    bool acceptaCuvant(const std::string& cuvant);
    std::vector<std::string> Cauta(std::string& neterminal);
    static bool apartine(std::string& simbol, std::vector<std::string>& simboluri);
    void descompunere(int linie, int coloana, std::vector <std::vector < std::vector < std::string> > >& acceptat, int n);
    void apartenentaCuvinte();
};


#endif //TEMA3LFA_CFG_H
