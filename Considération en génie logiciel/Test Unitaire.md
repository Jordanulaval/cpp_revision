# Test Unitaire

### Synthèse sur les **Test Unitaires**

### Pourquoi on fait des tests?
1. Pour que les composantes de notre logiciel se comporte comme prévu
2. On test les cas normaux et anormaux
   1. Cas normaux : AjouterElementValide -> EXPECT_TRUE, EXPECT_EG, ect
   2. Cas anormaux : AjouterElementNonValide -> EXPECT_FALSE, EXPECT_NE, ect
3. Utilise l'interface publique de la classe


### C'est quoi le but de faire des tests??? 
1. Première ligne de défense contre les défauts du logiciel
2. Détecter anomalie le plus tôt possible
>Money is gained if on detecte l'erreur tôt $$$$$$$

### Comment j'mets ça en place moi mon test
1. J'fais pas n'importe quoi
2. Doit être structuré
3. Doit être répétable -> Je dois l'executer souvent
4. Doit fournir un rapport (ok, pas ok)

### Règles importantes à respecter
1. **TOUTES** les **méthodes** publiques doivent être testé (TOUTES).
2. Un test par méthode -> 10 méthodes, 10 tests
3. 1 test = 1 cas

### Types d'assertions
1. EXPECT_ (non-fatales)
2. ASSERT_ (fatale) C'est celle-ci qu'on utilise dans le cours pour tester nos trucs.

### Maintenant qu'on sait les assertions, on va allez cherchez les types (Ceux qu'on utilise le plus)
1. ASSERT_TRUE() //true
2. ASSERT_EXPECT_FALSE() //false
3. ASSERT_EQ() //equal
4. ASSERT_NE() //not equal
5. ASSERT_LT() //lower then
6. ASSERT_GT() //greater then

### Comment j'écris ça moi un test
1. J'appelle mon fichier ChoseTesteur
2. J'importe #include <gtest/gtest.h>
3. J'importe #include "ContratException.h"

Voici la base pour créer un test
```c++
TEST(NomDeLaSuitesDeTest/*ex: CandidatTest*/, nomDuTest/*ConstructeurValidInput*/)
{
    //Ce que je veux tester (Si les parametres sont valide par exemple
    //Je crée un instance de l'objet
    Candidat candidat("046 454 286", "Jordan", "Mathieu", "2635 Rue de la Picardie", dateNaissance, LIBERAL)
    
    //Testons les entrées des paramêtres
    ASSERT_EQ(/*Ce que je test*/, /*Ce à quoi sa va etre egale*/)
    ASSERT_EQ(Candidat.reqNas(), "046 454 286")
    
    //Cela ne va rien retourné 
}
```
Voici comment créer un test fixture.
1. Dériver la classe de ::testing::Test
2. Déclarer dans la classe tous les objets à utiliser
3. TEST_F pour un test fixture 

Gracieuseté du code de Samy, parce que je savais pas comment faire un test fixture dans le tp2

```c++
class UnCandidat : public ::testing::Test
{
public:
    UnCandidat() :
        f_dateNaissance(9, 2, 2003),
        f_candidat("046 454 286", "Samy", "Mammeri",
                  "Rue de l Universite", f_dateNaissance, LIBERAL) {}

    Date f_dateNaissance;  /**< Date de naissance utilisée pour les tests */
    Candidat f_candidat;   /**< Instance de Candidat utilisée pour les tests */
};

```
Maintenant qu'on a un TEST Fixture, utilise ont le pour tester :D 
```c++
TEST_F(UnCandidat/*Mettre le nom du TEST fixture dérivée*/, reqPartiPolitique_appelNormal_retournePartiAssigne/*Même chose qu'avant ici*/)
{
//Dans le fonc ce que ça fait, c'est que tu es pas toujours obliger d'instancier un objet. 
// Tu réutilises ton objet instancer depuis le début
ASSERT_EQ(LIBERAL, f_candidat.reqPartiPolitique());
}
```
### Différent test pour plein de méthode
Voici mon interface Candidat.cpp
```c++
    Candidat::Candidat(const std::string& p_nas,
                       const std::string& p_prenom,
                       const std::string& p_nom,
                       const std::string& p_adresse,
                       const util::Date& p_dateNaissance,
                       PartisPolitiques p_partiPolitique)
        : Personne(p_nas, p_prenom, p_nom, p_adresse, p_dateNaissance),
          m_partiPolitique(p_partiPolitique)
    {
    }

    PartisPolitiques Candidat::reqPartiPolitique() const
    {
        return m_partiPolitique;
    }

    std::string Candidat::reqPersonneFormate() const
    {
        std::ostringstream os;
        os << "Candidat" << endl;
        os << "----------------------------------------------" << endl;
        os << Personne::reqPersonneFormate();
        os << "Parti politique : " << reqNomPartiPolitique() << endl;

        return os.str();
    }

    void Candidat::verifieInvariant() const
    {
    }

    std::string Candidat::reqNomPartiPolitique() const
    {
        switch (m_partiPolitique)
        {
        case BLOC_QUEBECOIS: return "BLOC QUEBECOIS";
        case CONSERVATEUR: return "CONSERVATEUR";
        case INDEPENDANT: return "INDEPENDANT";
        case LIBERAL: return "LIBERAL";
        case NOUVEAU_PARTI_DEMOCRATIQUE: return "NOUVEAU_PARTI_DEMOCRATIQUE";
        default: return "MAUVAISE ENTRER DE PARTIE";
        }
    }
    std::unique_ptr<Personne> Candidat::clone() const
    {
        return unique_ptr<Personne>(new Candidat(*this));
    }
}
```
### Testons
Voici maintenant mon fichier CandidatTesteur.cpp
```c++
TEST(CandidatTest, ConstructorValidInputs) {
util::Date dateNaissance(21, 02, 1997);
Candidat candidat("046 454 286", "Jordan", "Mathieu", "2635 Rue de la Picardie", dateNaissance, LIBERAL);

    ASSERT_EQ(candidat.reqNas(), "046 454 286");
    ASSERT_EQ(candidat.reqPrenom(), "Jordan");
    ASSERT_EQ(candidat.reqNom(), "Mathieu");
    ASSERT_EQ(candidat.reqAdresse(), "2635 Rue de la Picardie");
    ASSERT_EQ(candidat.reqDateNaissance(), dateNaissance);
    ASSERT_EQ(candidat.reqPartiPolitique(), LIBERAL);
}

  TEST(CandidatTest, ConstructorInvalidNas) {
  util::Date dateNaissance(21, 02, 1997);

  ASSERT_THROW(
  Candidat("invalid_nas", "Jordan", "Mathieu", "2635 Rue de la Picardie", dateNaissance, LIBERAL),
  PreconditionException
  );
  }

  TEST(CandidatTest, ConstructorInvalidPartiPolitique) {
  util::Date dateNaissance(21, 02, 1997);

  ASSERT_THROW(
  Candidat("046 454 286", "Jordan", "Mathieu", "2635 Rue de la Picardie", dateNaissance, static_cast<PartisPolitiques>(-1)),
  PreconditionException
  );
  }

  TEST(CandidatTest, ConstructorInvalidPrenom) {
  util::Date dateNaissance(21, 02, 1997);
  ASSERT_THROW(
  Candidat("046 454 286", "", "Mathieu", "2635 Rue de la Picardie", dateNaissance, LIBERAL),
  PreconditionException
  );
  }

  TEST(CandidatTest, ConstructorInvalidNom) {
  util::Date dateNaissance(21, 02, 1997);
  ASSERT_THROW(
  Candidat("046 454 286", "Jordan", "", "2635 Rue de la Picardie", dateNaissance, LIBERAL),
  PreconditionException
  );
  }

  TEST(CandidatTest, ConstructorInvalidAdresse) {
  util::Date dateNaissance(21, 02, 1997);
  ASSERT_THROW(
  Candidat("046 454 286", "Jordan", "Mathieu", "", dateNaissance, LIBERAL),
  PreconditionException
  );
  }

  TEST(CandidatTest, Invariants) {
  util::Date dateNaissance(21, 02, 1997);
  Candidat candidat("046 454 286", "Jordan", "Mathieu", "2635 Rue de la Picardie", dateNaissance, LIBERAL);

  ASSERT_GE(candidat.reqPartiPolitique(), BLOC_QUEBECOIS);
  ASSERT_LE(candidat.reqPartiPolitique(), NOUVEAU_PARTI_DEMOCRATIQUE);
  ASSERT_TRUE(Personne::validerNas(candidat.reqNas()));
  ASSERT_FALSE(candidat.reqPrenom().empty());
  ASSERT_FALSE(candidat.reqNom().empty());
  ASSERT_FALSE(candidat.reqAdresse().empty());
  }

  TEST(CandidatTest, ReqNomPartiPolitique) {
  util::Date dateNaissance(21, 02, 1997);

  Candidat candidatBloc("046 454 286", "Jordan", "Mathieu", "2635 Rue de la Picardie", dateNaissance, BLOC_QUEBECOIS);
  ASSERT_EQ(candidatBloc.reqNomPartiPolitique(), "BLOC QUEBECOIS");

  Candidat candidatConservateur("046 454 286", "Jordan", "Mathieu", "2635 Rue de la Picardie", dateNaissance, CONSERVATEUR);
  ASSERT_EQ(candidatConservateur.reqNomPartiPolitique(), "CONSERVATEUR");

  Candidat candidatIndependant("046 454 286", "Jordan", "Mathieu", "2635 Rue de la Picardie", dateNaissance, INDEPENDANT);
  ASSERT_EQ(candidatIndependant.reqNomPartiPolitique(), "INDEPENDANT");

  Candidat candidatLiberal("046 454 286", "Jordan", "Mathieu", "2635 Rue de la Picardie", dateNaissance, LIBERAL);
  ASSERT_EQ(candidatLiberal.reqNomPartiPolitique(), "LIBERAL");

  Candidat candidatNpd("046 454 286", "Jordan", "Mathieu", "2635 Rue de la Picardie", dateNaissance, NOUVEAU_PARTI_DEMOCRATIQUE);
  ASSERT_EQ(candidatNpd.reqNomPartiPolitique(), "NOUVEAU_PARTI_DEMOCRATIQUE");
  }

  TEST(CandidatTest, ReqPersonneFormate) {
  util::Date dateNaissance(21, 02, 1997);
  Candidat candidat("046 454 286", "Jordan", "Mathieu", "2635 Rue de la Picardie", dateNaissance, LIBERAL);

  std::string expected = "Candidat\n"
  "----------------------------------------------\n"
  "NAS              : 046 454 286\n"
  "Prenom           : Jordan\n"
  "Nom              : Mathieu\n"
  "Date de naissance: Vendredi le 21 fevrier 1997\n"
  "Adresse          : 2635 Rue de la Picardie\n"
  "Parti politique : LIBERAL\n";

  ASSERT_EQ(candidat.reqPersonneFormate(), expected);
  }

  TEST(CandidatTest, CloneCopyIdentique) {
  util::Date dateNaissance(21, 02, 1997);
  Candidat candidat("046 454 286", "Jordan", "Mathieu", "2635 Rue de la Picardie", dateNaissance, LIBERAL);

  auto clone = candidat.clone();

  ASSERT_EQ(clone->reqNas(), candidat.reqNas());
  ASSERT_EQ(clone->reqPrenom(), candidat.reqPrenom());
  ASSERT_EQ(clone->reqNom(), candidat.reqNom());
  ASSERT_EQ(clone->reqAdresse(), candidat.reqAdresse());
  ASSERT_EQ(clone->reqDateNaissance(), candidat.reqDateNaissance());

  auto* clonedCandidat = dynamic_cast<Candidat*>(clone.get());
  ASSERT_NE(clonedCandidat, nullptr);
  ASSERT_EQ(clonedCandidat->reqPartiPolitique(), candidat.reqPartiPolitique());
  }

  TEST(CandidatTest, HeritierPersonne) {
  util::Date dateNaissance(21, 02, 1997);
  Candidat candidat("046 454 286", "Jordan", "Mathieu", "2635 Rue de la Picardie", dateNaissance, LIBERAL);

  ASSERT_EQ(candidat.reqNas(), "046 454 286");
  ASSERT_EQ(candidat.reqPrenom(), "Jordan");
  ASSERT_EQ(candidat.reqNom(), "Mathieu");
  ASSERT_EQ(candidat.reqAdresse(), "2635 Rue de la Picardie");
  ASSERT_EQ(candidat.reqDateNaissance(), dateNaissance);
  }
  ```
Je vais revenir plus tard sur comment tester des méthodes un peu plus compliquer, tel que les pointeurs, ect. 


