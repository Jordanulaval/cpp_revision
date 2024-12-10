#include "Candidat.h"
#include <sstream>

using namespace election;

Candidat::Candidat(const std::string& p_nas, const std::string& p_prenom, const std::string& p_nom, const std::string& p_adresse, const util::Date& p_dateNaissance, PartisPolitiques p_partiPolitique)
    : Personne(p_nas, p_prenom, p_nom, p_adresse, p_dateNaissance), m_partiPolitique(p_partiPolitique)
{
    //Contrat
}
PartisPolitiques Candidat::reqPartiPolitique() const
{
    return m_partiPolitique;
}

/*std::unique_ptr <Personne> Candidat::clone() const
{

}
*/

void Candidat::verifieInvariant() const
{
    std::cout << "Invariants";
}

std::string Candidat::reqPersonneFormate() const
{
    std::ostringstream os;
    os << "Candidat" << std::endl;
    os << "------------------------------------" << std::endl;
    os << Personne::reqPersonneFormate() << std::endl;
    return os.str();
}