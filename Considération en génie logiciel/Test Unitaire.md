### Test Unitaire

#### **Synthèse sur les Tests Unitaires**

---

### **Pourquoi faire des tests unitaires ?**
1. **Vérification du comportement attendu :** S'assurer que les composantes logicielles fonctionnent comme prévu.
2. **Gestion des cas normaux et anormaux :**
   - **Cas normaux :** Tester les scénarios valides avec des assertions comme `EXPECT_TRUE`, `EXPECT_EQ`.
   - **Cas anormaux :** Tester les scénarios invalides avec des assertions comme `EXPECT_FALSE`, `EXPECT_NE`.
3. **Validation via l'interface publique de la classe :** Tester uniquement ce qui est exposé comme fonction publique (ne pas s’occuper des détails internes).

---

### **Objectifs des tests unitaires**
1. **Détecter rapidement les défauts :** Les tests unitaires constituent la première ligne de défense contre les bugs.
2. **Réduction des coûts :** Plus une anomalie est détectée tôt, plus elle est facile et économique à corriger.

   > *Chaque erreur détectée tôt peut représenter une économie de temps et d'argent !*

---

### **Mise en place d’un test unitaire**
1. **Structure et clarté :**
   - Les tests doivent être bien organisés et lisibles.
2. **Répétabilité :**
   - Les tests doivent être exécutables fréquemment, sans dépendre d’un état externe.
3. **Rapport clair :**
   - Chaque test doit fournir un résultat simple : **ok** ou **pas ok**.

---

### **Règles importantes**
1. Toutes les méthodes publiques **doivent être testées**.
2. Chaque méthode doit avoir **au moins un test dédié**.
3. **Un test = Un cas spécifique** :
   - Si une méthode a plusieurs scénarios possibles, chaque scénario doit avoir son propre test.

---

### **Types d’assertions dans Google Test**
1. **Non-fatales (`EXPECT_`) :**
   - Continuent le test même si une assertion échoue.
2. **Fatales (`ASSERT_`) :**
   - Interrompent le test dès qu’une assertion échoue.

---

### **Assertions courantes**
1. `ASSERT_TRUE()` / `EXPECT_TRUE()`: Vérifie si une condition est vraie.
2. `ASSERT_FALSE()` / `EXPECT_FALSE()`: Vérifie si une condition est fausse.
3. `ASSERT_EQ()` / `EXPECT_EQ()`: Vérifie l’égalité de deux valeurs.
4. `ASSERT_NE()` / `EXPECT_NE()`: Vérifie que deux valeurs ne sont pas égales.
5. `ASSERT_LT()` / `EXPECT_LT()`: Vérifie si une valeur est strictement inférieure à une autre.
6. `ASSERT_GT()` / `EXPECT_GT()`: Vérifie si une valeur est strictement supérieure à une autre.

---

### **Écrire un test unitaire simple**

Voici une base pour un test unitaire :
```cpp
TEST(NomDeLaSuiteDeTest, NomDuCasDeTest) {
    // Créer un objet à tester
    Candidat candidat("046 454 286", "Jordan", "Mathieu", "2635 Rue de la Picardie", dateNaissance, LIBERAL);

    // Vérifier les assertions
    ASSERT_EQ(candidat.reqNas(), "046 454 286");
    ASSERT_EQ(candidat.reqPrenom(), "Jordan");
    ASSERT_EQ(candidat.reqPartiPolitique(), LIBERAL);
}
```

---

### **Utilisation des Fixtures**
Les **fixtures** permettent de regrouper les configurations communes pour plusieurs tests.

#### Étapes pour créer une fixture :
1. Créer une classe dérivée de `::testing::Test`.
2. Déclarer les objets nécessaires dans la classe.
3. Utiliser la méthode `SetUp()` pour initialiser les objets avant chaque test.
4. Utiliser `TearDown()` pour nettoyer les ressources si nécessaire.
5. Écrire les tests avec `TEST_F()`.

---

#### **Exemple de Fixture**
```cpp
class UnCandidat : public ::testing::Test {
protected:
    util::Date f_dateNaissance{9, 2, 2003};
    Candidat f_candidat{"046 454 286", "Samy", "Mammeri", "Rue de l'Université", f_dateNaissance, LIBERAL};

    void SetUp() override {
        // Initialisations supplémentaires si nécessaire
    }

    void TearDown() override {
        // Nettoyage si nécessaire
    }
};
```

#### **Test utilisant la Fixture**
```cpp
TEST_F(UnCandidat, ReqPartiPolitique_appelNormal_retournePartiAssigne) {
    ASSERT_EQ(f_candidat.reqPartiPolitique(), LIBERAL);
}
```

---

### **Exemples de tests variés**

#### 1. **Test du constructeur avec entrées valides**
```cpp
TEST(CandidatTest, ConstructorValidInputs) {
    util::Date dateNaissance(21, 02, 1997);
    Candidat candidat("046 454 286", "Jordan", "Mathieu", "2635 Rue de la Picardie", dateNaissance, LIBERAL);

    ASSERT_EQ(candidat.reqNas(), "046 454 286");
    ASSERT_EQ(candidat.reqPrenom(), "Jordan");
    ASSERT_EQ(candidat.reqNom(), "Mathieu");
    ASSERT_EQ(candidat.reqAdresse(), "2635 Rue de la Picardie");
    ASSERT_EQ(candidat.reqPartiPolitique(), LIBERAL);
}
```

#### 2. **Test des invariants**
```cpp
TEST(CandidatTest, Invariants) {
    util::Date dateNaissance(21, 02, 1997);
    Candidat candidat("046 454 286", "Jordan", "Mathieu", "2635 Rue de la Picardie", dateNaissance, LIBERAL);

    ASSERT_TRUE(Personne::validerNas(candidat.reqNas()));
    ASSERT_FALSE(candidat.reqPrenom().empty());
    ASSERT_FALSE(candidat.reqNom().empty());
    ASSERT_FALSE(candidat.reqAdresse().empty());
    ASSERT_GE(candidat.reqPartiPolitique(), BLOC_QUEBECOIS);
    ASSERT_LE(candidat.reqPartiPolitique(), NOUVEAU_PARTI_DEMOCRATIQUE);
}
```

#### 3. **Test de la méthode `reqPersonneFormate`**
```cpp
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
```

---

### **Conclusion**
1. Les tests unitaires sont essentiels pour garantir la qualité du logiciel.
2. Une bonne structuration (avec ou sans fixtures) simplifie leur maintenance.
3. En combinant tests simples, assertions variées et tests fixtures, vous pouvez valider tous les aspects critiques de vos classes.

Les prochaines étapes peuvent inclure des tests avancés pour des fonctionnalités complexes comme les pointeurs ou la gestion de mémoire. 😊