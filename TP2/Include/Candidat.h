#ifndef CANDIDAT_H
#define CANDIDAT_H

#include "Personne.h"
namespace election
{
    enum PartisPolitiques
    {
        BLOC_QUEBECOIS,
        CONSERVATEUR,
        INDEPENDANT,
        LIBERAL,
        NOUVEAU_PARTI_DEMOCRATIQUE
    };


    class Candidat : public Personne
    {
    public:
        Candidat(const std::string& p_nas, const std::string& p_prenom, const std::string& p_nom, const std::string& p_adresse, const util::Date& p_dateNaissance, PartisPolitiques p_partiPolitique);
        PartisPolitiques reqPartiPolitique() const;

        //virtual std::unique_ptr <Personne> clone() const;

        std::string reqPersonneFormate() const;


    private:
        PartisPolitiques m_partiPolitique;
        virtual void verifieInvariant() const;
    };
}

#endif //CANDIDAT_H
