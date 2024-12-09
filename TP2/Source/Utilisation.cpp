#include <iostream>
#include "Personne.h"
using namespace std;
using namespace election;

int main()
{
    util::Date dateDeNaissance(21, 02, 1997);
    Personne jordan("475 501 870", "Jordan", "Mathieu", "2635 rue de la picardie", dateDeNaissance);
    util::Date dateNaissance2(18, 04, 2022);
    Personne steeve("475 501 870", "Jordan", "Mathieu", "2635 rue de la picardie", dateDeNaissance);
    cout<< jordan.reqPersonneFormate() <<endl;
    cout<< steeve.reqPersonneFormate();


    return 0;
}
