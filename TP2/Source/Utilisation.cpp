#include <iostream>
#include "Personne.h"
#include "Candidat.h"

using namespace std;
using namespace election;

int main()
{
    util::Date dateDeNaissance(21, 02, 1997);
    //Personne jordan("475 501 870", "Jordan", "Mathieu", "2635 rue de la picardie", dateDeNaissance);
    //util::Date dateNaissance2(18, 04, 2022);
    //Personne steeve("475 501 870", "Jordan", "Mathieu", "2635 rue de la picardie", dateDeNaissance);
    //cout<< jordan.reqPersonneFormate() <<endl;
    //cout<< steeve.reqPersonneFormate();

    Candidat miraly("475 501 870", "Miraly", "Mathieu", "2635 rue de la picardie", dateDeNaissance, BLOC_QUEBECOIS);
    cout << miraly.reqPersonneFormate();

    return 0;
}
