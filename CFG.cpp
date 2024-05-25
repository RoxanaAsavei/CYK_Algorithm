#include "CFG.h"

void CFG::citesteCFG() {
    std::ifstream fin("date.in");
    fin >> this->nrNeterminale;
    std::string neterminal;
    for(int i = 0; i < this->nrNeterminale; ++i) {
        fin >> neterminal;
        this->neterminale.emplace_back(neterminal);
        indiciNeterminale[neterminal] = i;
    }
    this->productii.resize(this->nrNeterminale);
    // pt fiecare neterminal pastram un vector productii[i] in care
    // se tin toate productii ce il au in stanga pe neterminale[i]

    fin >> this->nrProductii;
    std::string rightProductie;
    for(int i = 0; i < this->nrProductii; ++i) {
        fin >> neterminal >> rightProductie;
        this->productii[this->indiciNeterminale[neterminal]].emplace_back(rightProductie);
    }

    fin >> this->simbolStart;
    fin >> nrCuvinte;
    std::string cuvant;
    for(int i = 0; i < nrCuvinte; ++i) {
        fin >> cuvant;
        cuvinte.emplace_back(cuvant);
    }
}



bool CFG::acceptaCuvant(const std::string& cuvant) {
    int len = cuvant.length();
    std::vector <std::vector < std::vector < std::string> > > acceptat;
    acceptat.resize(len);
    for(int i = 0; i < len; ++i) {
        acceptat[i].resize(i + 1);
    }
    // se ia fiecare subsir de lungime 1 si verificam daca
    // se poate obtine
    for(int j = 0; j < len; ++j) {
        std::string litera(1, cuvant[j]);
        acceptat[len - 1][j] = Cauta(litera); // toate simbolurile care il au
        // in dreapta pe cuvant[j]
    }

    /***
     * pe linia len - 1 => subsiruri de lungime 1
     * pe linia len - 2 => subsiruri de lungime 2
     * pe linia len - 3 => subsisuri de lungime 3
     * .....................................
     * pe linia 0 => subsirul de lungime len
     */

    for(int i = len - 2; i >= 0; --i) {
        for(int j = 0; j <= i; ++j) {
            descompunere(i, j, acceptat, len);
        }
    }

    return apartine(simbolStart, acceptat[0][0]);
}

std::vector<std::string> CFG::Cauta(std::string& neterminal) {
    std::vector<std::string> ans;
    for(const auto& i : neterminale) {
        for(const auto& prod : productii[indiciNeterminale[i]]) {
            if(prod == neterminal) {
                ans.emplace_back(i);
            }
        }
    }
    return ans;
}

bool CFG::apartine(std::string &simbol, std::vector<std::string> &simboluri) {
    for(const auto& s : simboluri) {
        if(s == simbol) {
            return true;
        }
    }
    return false;
}

void CFG::apartenentaCuvinte() {
    for(auto const& cuvant : cuvinte) {
        if(acceptaCuvant(cuvant)) {
            std::cout << "ACCEPTAT\n";
        }
        else {
            std::cout << "RESPINS\n";
        }
    }
}

void CFG::descompunere(int linie, int coloana, std::vector <std::vector < std::vector < std::string> > >& acceptat, int n) {
    // rupem in 2 subsirul de lungime n - linie
    // care incepe la poz cuvant[coloana]
    std::set<std::string> solPartiala;
    for(int x = 1; x < n - linie; ++x) {
        int y = n - linie - x;
        /***
         * 2 subsiruri:
         * - 1 subsir de lungime x => linia n - x, incepand de pe pozitia coloana
         * - 1 subsir de lungime y => linia n - y, incepand de pe pozitia coloana + x
         */
        if(!acceptat[n - x][coloana].empty() and !acceptat[n - y][coloana + x].empty()) {
            for (const auto &simbol1: acceptat[n - x][coloana])
                for (const auto &simbol2: acceptat[n - y][coloana + x]) {
                    std::string drProd = simbol1 + simbol2;
                    std::vector<std::string> stgProd = Cauta(drProd);
                    for(const auto& neterm : stgProd) {
                        solPartiala.insert(neterm);
                    }
                }

        }
    }

    if(!solPartiala.empty()) {
        acceptat[linie][coloana].assign(solPartiala.begin(), solPartiala.end());
    }
}

