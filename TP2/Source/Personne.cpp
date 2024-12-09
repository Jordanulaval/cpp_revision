#include "Personne.h"
#include <sstream>
#include <regex>
#include <algorithm>

using namespace std;

using namespace election;


Personne::Personne(const std::string& p_nas, const std::string& p_prenom, const std::string& p_nom, const std::string& p_adresse, const util::Date& p_dateNaissance)
    : m_nas(p_nas), m_prenom(p_prenom), m_nom(p_nom), m_adresse(p_adresse), m_dateNaissance(p_dateNaissance)
{
    PRECONDITION(!p_nas.empty());
    PRECONDITION(validerNas(p_nas));
    PRECONDITION(!p_prenom.empty());
    PRECONDITION(!p_adresse.empty());
    PRECONDITION(util::Date::validerDate(p_dateNaissance.reqJour(), p_dateNaissance.reqMois(), p_dateNaissance.reqAnnee()));

    POSTCONDITION(m_nas == p_nas);
    POSTCONDITION(m_prenom == p_prenom);
    POSTCONDITION(m_nom == p_nom);
    POSTCONDITION(m_adresse == p_adresse);
    POSTCONDITION(m_dateNaissance == p_dateNaissance);


    INVARIANTS();
}

std::string Personne::reqNas() const
{
    return m_nas;
}
std::string Personne::reqPrenom() const
{
    return m_prenom;
}
std::string Personne::reqNom() const
{
    return m_nom;
}
std::string Personne::reqAdresse() const
{
    return m_adresse;
}
util::Date Personne::reqDateNaissance() const
{
    return m_dateNaissance;
}

void Personne::asgAdresse(const std::string& p_nouvelleAdresse)
{
    PRECONDITION(!p_nouvelleAdresse.empty());
    m_adresse = p_nouvelleAdresse;
    POSTCONDITION(m_adresse == p_nouvelleAdresse);
    INVARIANTS();
}

bool Personne::operator==(const Personne& p_autrePersonne) const
{
    return m_nas == p_autrePersonne.m_nas &&
            m_prenom == p_autrePersonne.m_prenom &&
                m_nom == p_autrePersonne.m_nom &&
                    m_adresse == p_autrePersonne.m_adresse &&
                        m_dateNaissance == p_autrePersonne.m_dateNaissance;
}

std::string Personne::reqPersonneFormate() const
{
    std::ostringstream os;
    os << "NAS               : " << reqNas() <<std::endl;
    os << "Prenom            : " << reqPrenom() <<std::endl;
    os << "Nom               : " << reqNom() << std::endl;
    os << "Date de naissance : " << m_dateNaissance.reqDateFormatee() << std::endl;
    os << "Adresse           : " << reqAdresse() << std::endl;
    return os.str();
}

void Personne::verifieInvariant() const
{
    INVARIANT(validerNas(m_nas));
    INVARIANT(!m_nas.empty());
    INVARIANT(!m_prenom.empty());
    INVARIANT(!m_nom.empty());
    INVARIANT(!m_adresse.empty());
    INVARIANT(util::Date::validerDate(m_dateNaissance.reqJour(), m_dateNaissance.reqMois(), m_dateNaissance.reqAnnee()));

}

bool Personne::validerNas(const std::string& p_nas)
{
    bool estValide = true;
    std::regex nasPattern("^\\d{3} \\d{3} \\d{3}$");

    if (!std::regex_match(p_nas, nasPattern))
    {
        estValide = false;
    }
    if (estValide)
    {
        std::string nasSansEspaces = p_nas;
        nasSansEspaces.erase(std::remove_if(nasSansEspaces.begin(), nasSansEspaces.end(), ::isspace), nasSansEspaces.end());

        std::vector<int> multiplicateur = {1, 2, 1, 2, 1, 2, 1, 2, 1};
        int somme = 0;

        for (size_t i = 0; i < nasSansEspaces.size(); ++i)
        {
            int produit = (nasSansEspaces[i] - '0') * multiplicateur[i];
            somme += (produit >= 10) ? (produit - 9) : produit;
        }

        if (somme % 10 != 0)
        {
            estValide = false;
        }
    }
    return estValide;
}