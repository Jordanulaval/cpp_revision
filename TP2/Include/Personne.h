#ifndef PERSONNE_H
#define PERSONNE_H
#include <string>
#include "Date.h"
#include <memory>
#include "ContratException.h"


namespace election
{
    class Personne
    {
    public:
        Personne(const std::string& p_nas, const std::string& p_prenom, const std::string& p_nom, const std::string& p_adresse, const util::Date& p_dateNaissance);

        virtual ~Personne(){};

        std::string reqNas() const;
        std::string reqPrenom() const;
        std::string reqNom() const;
        std::string reqAdresse() const;
        util::Date reqDateNaissance() const;

        void asgAdresse(const std::string& p_nouvelleAdresse);

        bool operator==(const Personne& p_autrePersonne) const;

        //virtual std::unique_ptr<Personne> clone() const; //on va la mettre = 0 pour creer la classe abstraite

        std::string reqPersonneFormate() const;

        static bool validerNas(const std::string& p_nas);


    private:
        std::string m_nas;
        std::string m_prenom;
        std::string m_nom;
        std::string m_adresse;
        util::Date m_dateNaissance;
        virtual void verifieInvariant() const ;
    };
}

#endif //PERSONNE_H
