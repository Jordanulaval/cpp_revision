# Semaine 7 : Contrat, Test Unitaire

### Synthèse sur la **Théorie du Contrat**

La **théorie du contrat** en génie logiciel repose sur l’idée d’établir une relation claire entre le client (utilisateur d’un composant ou d’une méthode) et le fournisseur (le composant ou la méthode elle-même), en spécifiant explicitement les attentes et garanties.

---

### **Concepts clés :**
1. **Définition d’un contrat :**
    - Le contrat sert à protéger les deux parties :
        - **Client :** Définit les obligations et garantit un résultat attendu.
        - **Fournisseur :** Établit les exigences minimales à respecter pour éviter d'être tenu responsable de problèmes externes.

2. **Éléments d’un contrat logiciel :**
    - **Préconditions :**
        - Conditions à respecter avant l’appel d’une méthode.
        - Si elles ne sont pas respectées, l’exécution de la méthode peut être refusée.
    - **Postconditions :**
        - Garanties fournies après l’exécution d’une méthode.
    - **Invariants :**
        - Conditions qui doivent toujours être vraies pendant tout le cycle de vie d’un objet.

3. **Fiabilité grâce au contrat :**
    - Chaque service d’un logiciel est défini de manière non ambiguë grâce à un contrat explicite.
    - Les contrats clarifient les spécifications, les rendant testables et intégrées au code source.

---

### **Implémentation en C++ :**
1. **Langage de base :**
    - Le C++ ne supporte pas directement les contrats. Ils sont généralement implémentés avec des **assertions**.

2. **Utilisation d’assertions :**
    - Les assertions vérifient les préconditions, postconditions et invariants au moment de l'exécution :
      ```cpp
      assert(condition_logique);
      ```

3. **Macros pour simplifier l’usage :**
    - Préconditions : `PRECONDITION(test_logique);`
    - Postconditions : `POSTCONDITION(test_logique);`
    - Assertions générales : `ASSERTION(test_logique);`
    - Invariants : `INVARIANT(test_logique);`

4. **Hiérarchie d’exceptions pour les contrats :**
    - Une architecture d’exceptions personnalisées permet de gérer les violations de contrat :
        - `PreconditionException`
        - `PostconditionException`
        - `InvariantException`

---

### **Avantages :**
- **Clarté des spécifications :**
    - Les attentes et les garanties sont clairement exprimées et intégrées au code.
- **Fiabilité accrue :**
    - Les contrats permettent de vérifier automatiquement la conformité du code.
- **Réutilisation des composants :**
    - Les spécifications explicites rendent les composants logiciels plus robustes et réutilisables.

---

### **Exemple :**
Implémentation d’un constructeur avec préconditions et postconditions :
```cpp
Personne::Personne(const std::string& p_nom, const std::string& p_prenom) 
    : m_nom(p_nom), m_prenom(p_prenom) 
{
    PRECONDITION(!p_prenom.empty());
    PRECONDITION(!p_nom.empty());
    POSTCONDITION(m_prenom == p_prenom);
    POSTCONDITION(m_nom == p_nom);
    INVARIANTS();
}

void Personne::verifieInvariant() const {
    INVARIANT(!m_prenom.empty());
    INVARIANT(!m_nom.empty());
}
```

---

### **Règles de simplification :**
1. Une condition doit être vérifiée soit dans les préconditions, soit dans le corps de la méthode, mais jamais dans les deux.
2. Les vérifications par contrat doivent être désactivables en production mais réactivables pour la maintenance.
3. Une méthode ne devrait pas gérer toutes les entrées possibles. Une précondition forte augmente la responsabilité du client.

---

### **Conclusion :**
La théorie du contrat apporte une approche méthodique et fiable au développement logiciel, où les obligations et garanties sont explicites et testables. Elle améliore la robustesse du code, facilite la maintenance et encourage la réutilisation des composants.


### Implémentation de la théorie du contrat

Voici une procédure détaillée et optimisée pour implémenter la théorie du contrat dans un projet C++.

---

### Étapes pour implémenter la théorie du contrat :

1. **Créer le fichier `ContratException.h` :**
    - Inclure la bibliothèque `stdexcept`.
    - Créer une classe de base `ContratException` qui dérive de `std::logic_error`.
    - Ajouter les classes dérivées suivantes :
        - `AssertionException`
        - `PreconditionException`
        - `PostconditionException`
        - `InvariantException`.

2. **Créer des macros pour simplifier l’utilisation :**
    - Ajouter une macro pour les invariants :
      ```cpp
      #define INVARIANTS() verifieInvariant()
      ```

3. **Implémenter les classes dans `ContratException.cpp` :**
   Voici un exemple d'implémentation :

   ```cpp
   #include "ContratException.h"
   #include <sstream>

   ContratException::ContratException(const std::string& p_fichier, unsigned int p_ligne, const std::string& p_expression, const std::string& p_msg)
       : logic_error(p_msg), m_fichier(p_fichier), m_ligne(p_ligne), m_expression(p_expression)
   {
   }

   std::string ContratException::reqTexteException() const
   {
       std::ostringstream os;
       os << "Message    : " << what() << "\n";
       os << "Fichier    : " << m_fichier << "\n";
       os << "Ligne      : " << m_ligne << "\n";
       os << "Expression : " << m_expression << "\n";
       return os.str();
   }

   AssertionException::AssertionException(const std::string& p_fichier, unsigned int p_ligne, const std::string& p_expression)
       : ContratException(p_fichier, p_ligne, p_expression, "ERREUR ASSERTION")
   {
   }

   PreconditionException::PreconditionException(const std::string& p_fichier, unsigned int p_ligne, const std::string& p_expression)
       : ContratException(p_fichier, p_ligne, p_expression, "ERREUR PRECONDITION")
   {
   }

   PostconditionException::PostconditionException(const std::string& p_fichier, unsigned int p_ligne, const std::string& p_expression)
       : ContratException(p_fichier, p_ligne, p_expression, "ERREUR POSTCONDITION")
   {
   }

   InvariantException::InvariantException(const std::string& p_fichier, unsigned int p_ligne, const std::string& p_expression)
       : ContratException(p_fichier, p_ligne, p_expression, "ERREUR INVARIANT")
   {
   }
   ```

4. **Utiliser le contrat dans une classe de base :**

   **Fichier `Candidat.h` :**
    - Définir la classe `Candidat` en dérivant de `Personne`.
    - Ajouter une méthode privée `verifieInvariant()`.

   ```cpp
   #ifndef CANDIDAT_H
   #define CANDIDAT_H

   #include "Personne.h"
   #include <string>
   #include <memory>

   namespace elections
   {
   class Candidat : public Personne
   {
   public:
       Candidat(const std::string& p_nas, const std::string& p_prenom,
                const std::string& p_nom, const std::string& p_adresse,
                const util::Date& p_dateNaissance, PartisPolitiques p_partiPolitique);

       PartisPolitiques reqPartiPolitique() const;
       virtual std::unique_ptr<Personne> clone() const;
       virtual std::string reqPersonneFormate() const;

   private:
       PartisPolitiques m_partiPolitique;
       virtual void verifieInvariant() const;
   };
   }
   #endif
   ```

   **Fichier `Candidat.cpp` :**
    - Implémenter le constructeur avec des préconditions et postconditions.
    - Ajouter la méthode `verifieInvariant()` pour valider les invariants.

   ```cpp
   #include "Candidat.h"
   #include "ContratException.h"

   elections::Candidat::Candidat(const std::string& p_nas,
                                  const std::string& p_prenom,
                                  const std::string& p_nom,
                                  const std::string& p_adresse,
                                  const util::Date& p_dateNaissance,
                                  PartisPolitiques p_partiPolitique)
       : Personne(p_nas, p_prenom, p_nom, p_adresse, p_dateNaissance),
         m_partiPolitique(p_partiPolitique)
   {
       PRECONDITION(p_partiPolitique >= BLOC_QUEBECOIS && p_partiPolitique <= NOUVEAU_PARTI_DEMOCRATIQUE);
       PRECONDITION(validerNas(p_nas));
       PRECONDITION(!p_prenom.empty());
       PRECONDITION(!p_nom.empty());
       PRECONDITION(!p_adresse.empty());
       PRECONDITION(util::Date::validerDate(p_dateNaissance.reqJour(), p_dateNaissance.reqMois(), p_dateNaissance.reqAnnee()));

       POSTCONDITION(reqNas() == p_nas);
       POSTCONDITION(reqPrenom() == p_prenom);
       POSTCONDITION(reqNom() == p_nom);
       POSTCONDITION(reqAdresse() == p_adresse);
       POSTCONDITION(reqDateNaissance() == p_dateNaissance);
       POSTCONDITION(reqPartiPolitique() == p_partiPolitique);

       INVARIANTS();
   }

   void elections::Candidat::verifieInvariant() const
   {
       INVARIANT(m_partiPolitique >= BLOC_QUEBECOIS && m_partiPolitique <= NOUVEAU_PARTI_DEMOCRATIQUE);
       INVARIANT(validerNas(reqNas()));
       INVARIANT(!reqPrenom().empty());
       INVARIANT(!reqNom().empty());
       INVARIANT(!reqAdresse().empty());
       INVARIANT(util::Date::validerDate(reqDateNaissance().reqJour(), reqDateNaissance().reqMois(), reqDateNaissance().reqAnnee()));
   }
   ```

---

### Points à retenir :
1. **Préconditions :** Valider que les paramètres passés sont valides avant d’exécuter la méthode.
2. **Postconditions :** Garantir que l’état attendu après l’exécution est respecté.
3. **Invariants :** Vérifier que les règles de cohérence des objets sont respectées à tout moment.
4. **Macros :** Simplifient l’écriture et permettent de désactiver les vérifications en mode release pour améliorer les performances.

Avec cette approche, le code est robuste, clair et facile à maintenir, tout en intégrant une gestion explicite des erreurs et des validations.

---

### **Points supplémentaires à considérer :**

#### 1. **Rôle des exceptions dans la théorie du contrat**
- Tu mentionnes les classes d’exceptions (`PreconditionException`, `PostconditionException`, etc.), mais tu pourrais détailler davantage leur rôle :
    - Elles doivent non seulement signaler une violation de contrat, mais aussi faciliter le débogage en fournissant des informations claires (comme la ligne, le fichier, ou l'expression fautive).
    - Pourquoi utiliser des exceptions spécifiques (par exemple, pour distinguer les préconditions non respectées des postconditions non garanties) ?
- Exemple d'utilisation dans un environnement complexe (ex. : API ou système multi-composants).

#### 2. **Désactivation en mode production**
- Les **assertions et macros** (comme `PRECONDITION`, `POSTCONDITION`, `INVARIANT`) ne devraient pas impacter les performances en mode production.
- Ajoute une condition pour les désactiver en mode release :
  ```cpp
  #ifdef NDEBUG
      #define PRECONDITION(test) ((void)0)
  #else
      #define PRECONDITION(test) assert(test)
  #endif
  ```
- Cette optimisation peut être essentielle pour des projets où la performance est critique.

#### 3. **Exemples de contexte**
- Mentionne où et pourquoi la théorie du contrat est particulièrement utile :
    - **Développement de bibliothèques ou frameworks** : Les contrats garantissent que les utilisateurs du code suivent les règles définies.
    - **Projets complexes** : Réduisent les ambiguïtés entre équipes et augmentent la fiabilité.
- Inclure un exemple concret montrant un écosystème où la théorie du contrat joue un rôle clé.

#### 4. **Différenciation des responsabilités**
- Explicite davantage la distinction entre **responsabilités du client** et **responsabilités du fournisseur**.
    - **Client :** Fournir des données valides pour garantir le bon fonctionnement (ex. : respecter les préconditions).
    - **Fournisseur :** Fournir les garanties spécifiées (ex. : respecter les postconditions et maintenir les invariants).
- Clarifie dans quels cas ces responsabilités peuvent être partagées ou ajustées.

#### 5. **Éviter les vérifications redondantes**
- Si les **préconditions** sont vérifiées par le client, elles ne doivent pas l’être à nouveau par le fournisseur.
- Évite les redondances, notamment dans des systèmes distribués où plusieurs couches vérifient les mêmes règles.

#### 6. **Automatisation des tests avec contrats**
- Les tests unitaires peuvent intégrer les contrats pour détecter automatiquement les violations.
- Utilise des frameworks comme Google Test ou doctest pour exécuter des tests intégrant préconditions, postconditions et invariants.
- Exemple :
  ```cpp
  TEST(Candidat, Constructor_InvalidNas)
  {
      EXPECT_THROW(Candidat("", "Jean", "Dupont", "Adresse", Date(1,1,2000), BLOC_QUEBECOIS), PreconditionException);
  }
  ```

#### 7. **Utilisation d'invariants dans des scénarios dynamiques**
- Si ta classe évolue avec le temps (modifications de données, transitions d’état, etc.), assure-toi que les **invariants** tiennent compte de ces scénarios.
- Exemple : Si un objet `Candidat` change de parti politique, les invariants doivent être vérifiés après cette opération.

#### 8. **Documentation et communication**
- Assure-toi de documenter clairement :
    - Les préconditions, postconditions et invariants pour chaque méthode.
    - Les limites ou cas non pris en charge par le contrat (ce qui est volontairement laissé en dehors du contrat).
- Exemple de documentation pour une méthode dans Doxygen :
  ```cpp
  /**
   * @brief Construit un candidat avec les informations fournies.
   * @pre p_nas est valide et non vide.
   * @pre p_prenom, p_nom et p_adresse sont non vides.
   * @post L’objet candidat est correctement initialisé avec les paramètres fournis.
   * @invariant m_partiPolitique est dans l’intervalle valide.
   */
  ```

---

### **Outils ou concepts complémentaires :**

1. **Contrats dans les langages modernes :**
    - Certains langages comme Python, Eiffel ou D permettent d'intégrer directement la théorie du contrat. Bien que C++ ne le supporte pas nativement, mentionner ces outils peut élargir ta perspective.

2. **Liens avec les principes SOLID :**
    - La théorie du contrat s’aligne particulièrement avec le principe **Responsibility Segregation** de SOLID, renforçant la modularité et la séparation des responsabilités.

3. **Exemple d’architecture globale :**
    - Montre comment intégrer la théorie du contrat dans un système complet avec plusieurs modules/classes. Par exemple :
        - API de gestion d’utilisateurs : Validation des entrées par les préconditions.
        - Base de données : Garanties de stockage par les postconditions.
        - Service de notification : Vérification des états par les invariants.

---

### **Résumé des ajouts possibles :**
- Rôle détaillé des exceptions.
- Désactivation des assertions en mode production.
- Cas d’utilisation concrets et pertinence dans des projets complexes.
- Précision sur la responsabilité client/fournisseur.
- Automatisation des tests autour des contrats.
- Documentation claire et explicite pour les méthodes.
- Liens avec les concepts modernes et principes d'architecture.

En intégrant ces éléments, ta couverture de la théorie du contrat sera encore plus exhaustive et applicable à des projets professionnels. 😊