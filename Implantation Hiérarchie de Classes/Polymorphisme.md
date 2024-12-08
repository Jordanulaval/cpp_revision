### Les 3 formes de polymorphismes
1. Polymorphisme ad hoc
   1. Surcharge de méthode

Créer plusieurs Méthode avec le même noms pour des cas différents

Example avec additionner et plusieurs cas:
````c++
class Calculatrice {
public:
    // Addition de deux entiers
    int additionner(int a, int b) {
        return a + b;
    }

    // Addition de trois entiers
    int additionner(int a, int b, int c) {
        return a + b + c;
    }

    // Addition de deux nombres à virgule flottante
    double additionner(double a, double b) {
        return a + b;
    }
};

int main() {
    Calculatrice calc;

    std::cout << "Addition de 2 et 3 : " << calc.additionner(2, 3) << std::endl;
    std::cout << "Addition de 2, 3 et 4 : " << calc.additionner(2, 3, 4) << std::endl;
    std::cout << "Addition de 1.5 et 2.5 : " << calc.additionner(1.5, 2.5) << std::endl;

    return 0;
}
````

2. Polymorphisme paramêtrisables (On na pas vue en cours)
3. Polymorphisme pur (celui qu'on va voir en détail ici)

### Qu'est-ce que le polymorphisme pur

### **Méthodes virtuelles et héritage : Explications claires**

---

#### **Qu'est-ce qu'une méthode virtuelle ?**
Une méthode virtuelle est une méthode dans une classe de base qui peut être **redéfinie** dans une classe dérivée. Cela permet d'adapter le comportement de la méthode à chaque type spécifique dans une hiérarchie de classes.

---

#### **Avantages des méthodes virtuelles avec l'héritage**
1. **Extensibilité :**
    - Les programmes deviennent **extensibles**, car les classes dérivées peuvent ajouter ou redéfinir des comportements spécifiques tout en héritant des fonctionnalités existantes.

2. **Traitement générique :**
    - Permet de **manipuler toute une famille de classes (hiérarchie)** à partir de la classe de base, sans connaître le type exact de chaque objet.
    - Évite d’utiliser des structures conditionnelles comme `switch` ou `if-else` pour identifier le type d'une classe.

3. **Méthodes adaptées au besoin :**
    - Le comportement est déterminé dynamiquement (à l'exécution) selon le type réel de l'objet.

---

#### **Comment cela fonctionne ?**
1. **Classe de base :**
    - Une méthode est déclarée **`virtual`** dans la classe de base.
2. **Classe dérivée :**
    - La classe dérivée peut redéfinir la méthode pour apporter un comportement spécifique.
3. **Appel via un pointeur ou une référence :**
    - Lorsqu’une méthode virtuelle est appelée via un **pointeur** ou une **référence** à la classe de base, la version adaptée à l'objet dérivé est exécutée (polymorphisme).

---

### **Exemple Simple**

#### **Classe de base : `Vehicule`**
```c++
#include <iostream>
#include <string>

class Vehicule {
public:
    Vehicule(const std::string& marque) : m_marque(marque) {}

    // Méthode virtuelle
    virtual void afficherDetails() const {
        std::cout << "Véhicule : Marque = " << m_marque << std::endl;
    }

protected:
    std::string m_marque;
};
```

#### **Classe dérivée : `Voiture`**
```c++
class Voiture : public Vehicule {
public:
    Voiture(const std::string& marque, int nbPortes)
        : Vehicule(marque), m_nbPortes(nbPortes) {}

    // Redéfinition de la méthode virtuelle
    void afficherDetails() const override {
        std::cout << "Voiture : Marque = " << m_marque << ", Portes = " << m_nbPortes << std::endl;
    }

private:
    int m_nbPortes;
};
```

#### **Classe dérivée : `Moto`**
```c++
class Moto : public Vehicule {
public:
    Moto(const std::string& marque, bool aCaisse)
        : Vehicule(marque), m_aCaisse(aCaisse) {}

    // Redéfinition de la méthode virtuelle
    void afficherDetails() const override {
        std::cout << "Moto : Marque = " << m_marque << ", Avec caisse = " << (m_aCaisse ? "Oui" : "Non") << std::endl;
    }

private:
    bool m_aCaisse;
};
```

#### **Utilisation générique dans le `main`**
```c++
int main() {
    Vehicule* v1 = new Voiture("Toyota", 4);
    Vehicule* v2 = new Moto("Yamaha", true);

    // Appels polymorphiques
    v1->afficherDetails();  // Appelle Voiture::afficherDetails
    v2->afficherDetails();  // Appelle Moto::afficherDetails

    delete v1;
    delete v2;

    return 0;
}
```

---

#### **Résultat :**
```
Voiture : Marque = Toyota, Portes = 4
Moto : Marque = Yamaha, Avec caisse = Oui
```

---

### **Explications clés**
1. **Polymorphisme dynamique :**
    - Bien que `v1` et `v2` soient de type `Vehicule*`, les méthodes redéfinies dans `Voiture` et `Moto` sont appelées. Cela est possible grâce au mot-clé **`virtual`**.

2. **Traitement générique :**
    - Le code manipule tous les objets (`Voiture`, `Moto`, etc.) via des pointeurs à `Vehicule`. Il n’est pas nécessaire d'utiliser des `switch` ou `if-else` pour déterminer leur type.

3. **Extensibilité :**
    - Si une nouvelle classe dérivée, comme `Camion`, est ajoutée avec sa propre version de `afficherDetails`, le programme fonctionnera sans modification du code existant.

---

### **Résumé**
- **Méthodes virtuelles :** Permettent de redéfinir des comportements spécifiques dans des classes dérivées.
- **Avantages :**
    - Évite le code conditionnel complexe.
    - Permet de traiter une hiérarchie de classes de manière générique.
    - Rend le code extensible et adaptable.
- **Utilisation :**
    - Déclarer une méthode virtuelle dans la classe de base avec le mot-clé `virtual`.
    - Redéfinir cette méthode dans les classes dérivées si nécessaire.
    - Appeler les méthodes via des pointeurs ou références à la classe de base pour bénéficier du polymorphisme dynamique.
---
Une fonction virtuelle doit avoir le même prototype (même signature et même type de retour) dans toutes la hiérarchie.
Une fois qu'une fonction a été déclarée virtuelle, elle le demeure dans toute la hiérarchie à partir de ce point
Bonne pratique : déclarer virtual les fonctions qui le sont et à tous les niveaux (par soucis de transparence).

Cette phrase explique une **propriété fondamentale des méthodes virtuelles en C++** : **l'héritabilité du comportement virtuel**. Voici une explication simple et claire :

---

### **Explication**
1. **Méthode déclarée virtuelle :**
    - Une fois qu'une méthode est déclarée comme **`virtual`** dans une classe de base, elle reste virtuelle dans toutes les classes dérivées qui héritent de cette classe.

2. **Conséquence :**
    - Cela signifie que toute classe dérivée peut redéfinir la méthode pour apporter un comportement spécifique.
    - Même si la déclaration **`virtual`** n'est pas explicitement répétée dans la classe dérivée, la méthode reste virtuelle dans cette classe.

3. **Polymorphisme garanti :**
    - Lorsque vous appelez cette méthode via un **pointeur** ou une **référence** à la classe de base, la version de la méthode correspondant au type réel de l'objet (et non à son type déclaré) sera exécutée.

---

### **Exemple**

#### Classe de base
```c++
#include <iostream>

class Vehicule {
public:
    // Méthode virtuelle dans la classe de base
    virtual void afficherDetails() const {
        std::cout << "Détails généraux du véhicule." << std::endl;
    }
};
```

#### Classe dérivée (premier niveau)
```c++
class Voiture : public Vehicule {
public:
    // Redéfinition de la méthode virtuelle
    void afficherDetails() const override {
        std::cout << "Détails spécifiques à la voiture." << std::endl;
    }
};
```

#### Classe dérivée (deuxième niveau)
```c++
class VoitureElectrique : public Voiture {
public:
    // Redéfinition encore possible car la méthode reste virtuelle
    void afficherDetails() const override {
        std::cout << "Détails spécifiques à la voiture électrique." << std::endl;
    }
};
```

#### Utilisation
```c++
int main() {
    Vehicule* v1 = new Vehicule();
    Vehicule* v2 = new Voiture();
    Vehicule* v3 = new VoitureElectrique();

    v1->afficherDetails();  // Appelle Vehicule::afficherDetails
    v2->afficherDetails();  // Appelle Voiture::afficherDetails
    v3->afficherDetails();  // Appelle VoitureElectrique::afficherDetails

    delete v1;
    delete v2;
    delete v3;

    return 0;
}
```

---

### **Résultat**
```
Détails généraux du véhicule.
Détails spécifiques à la voiture.
Détails spécifiques à la voiture électrique.
```

---

### **Pourquoi cela fonctionne ?**
1. **Une seule déclaration `virtual` suffit :**
    - La méthode **`afficherDetails`** est déclarée virtuelle une fois dans `Vehicule`. Cela garantit qu'elle reste virtuelle pour toutes les classes dérivées (comme `Voiture` et `VoitureElectrique`).

2. **Polymorphisme dynamique :**
    - Lorsqu'une méthode virtuelle est appelée via un **pointeur** ou une **référence** à la classe de base, la version correspondant au **type réel** de l'objet est exécutée, même si ce type est dérivé.

3. **Pas besoin de répéter `virtual` :**
    - Bien que redéfinir une méthode virtuelle nécessite d'utiliser le mot-clé **`override`** (optionnel mais recommandé), la méthode reste virtuelle même si `virtual` n'est pas explicitement réécrit.

---

### **Résumé**
- Une méthode **déclarée virtuelle dans une classe de base** conserve son caractère virtuel **dans toutes les classes dérivées**.
- Cela garantit que vous pouvez redéfinir la méthode dans les classes dérivées et utiliser le **polymorphisme dynamique** pour appeler la version appropriée à l'exécution.
- Vous n’avez pas besoin de répéter **`virtual`**, mais utiliser **`override`** est une bonne pratique pour clarifier que la méthode redéfinit une méthode virtuelle existante.

### **Comprendre l’utilisation d’une hiérarchie avec polymorphisme dynamique**

Pour expliquer ces concepts de manière claire, nous allons utiliser l'exemple des **voitures** au lieu des polygones, tout en abordant les principes suivants :

1. **Hiérarchie des classes :**
    - Une classe de base `Vehicule`.
    - Des classes dérivées comme `Voiture`, `Moto`, etc.

2. **Polymorphisme dynamique :**
    - Utiliser un vecteur de **pointeurs** à la classe de base pour stocker différents types d’objets dérivés.
    - Appeler les **méthodes virtuelles** dynamiquement en fonction du type réel des objets.

---

### **1. La hiérarchie des classes**

#### Classe de base : `Vehicule`

Nous définissons une méthode virtuelle `afficherDetails()` dans `Vehicule`, qui sera redéfinie par les classes dérivées.

```c++
#include <iostream>
#include <vector>
#include <string>

class Vehicule {
public:
    Vehicule(const std::string& marque) : m_marque(marque) {}

    // Méthode virtuelle pour afficher les détails
    virtual void afficherDetails() const {
        std::cout << "Véhicule de marque : " << m_marque;
    }

    virtual ~Vehicule() {}  // Destructeur virtuel pour éviter les fuites de mémoire

protected:
    std::string m_marque;
};
```

#### Classe dérivée : `Voiture`

Ajoute un attribut spécifique aux voitures (par exemple, le nombre de portes) et redéfinit la méthode `afficherDetails()`.

```c++
class Voiture : public Vehicule {
public:
    Voiture(const std::string& marque, int nbPortes)
        : Vehicule(marque), m_nbPortes(nbPortes) {}

    // Redéfinition de la méthode pour afficher des détails spécifiques
    void afficherDetails() const override {
        std::cout << "Voiture de marque : " << m_marque << ", Nombre de portes : " << m_nbPortes;
    }

private:
    int m_nbPortes;
};
```

#### Classe dérivée : `Moto`

Ajoute un attribut spécifique aux motos (par exemple, présence d’un side-car) et redéfinit `afficherDetails()`.

```c++
class Moto : public Vehicule {
public:
    Moto(const std::string& marque, bool sideCar)
        : Vehicule(marque), m_sideCar(sideCar) {}

    // Redéfinition de la méthode pour afficher des détails spécifiques
    void afficherDetails() const override {
        std::cout << "Moto de marque : " << m_marque << ", Avec side-car : " << (m_sideCar ? "Oui" : "Non");
    }

private:
    bool m_sideCar;
};
```

---

### **2. Stocker différents objets dans un vecteur générique**

Le polymorphisme permet de manipuler différents types de véhicules (voitures, motos, etc.) à travers un **vecteur de pointeurs à la classe de base `Vehicule`**.

#### Création et stockage des objets

```c++
int main() {
    // Création d'un vecteur de pointeurs à des objets Vehicule
    std::vector<Vehicule*> garage;

    // Création de différents véhicules
    Voiture voiture1("Toyota", 4);
    Voiture voiture2("Tesla", 4);
    Moto moto1("Harley-Davidson", true);
    Moto moto2("Yamaha", false);

    // Ajout des objets dans le vecteur
    garage.push_back(&voiture1);
    garage.push_back(&voiture2);
    garage.push_back(&moto1);
    garage.push_back(&moto2);

    // Traitement générique du vecteur
    for (unsigned i = 0; i < garage.size(); ++i) {
        garage[i]->afficherDetails();
        std::cout << std::endl;
    }

    return 0;
}
```

---

### **3. Fonctionnement du polymorphisme dynamique**

#### **Appels dynamiques :**
- **Pointeur ou référence :** Lorsqu’une méthode virtuelle est appelée via un pointeur ou une référence à la classe de base (`Vehicule*`), c’est la version de la méthode redéfinie dans la classe dérivée qui est exécutée.
- **Type réel de l'objet :** Le programme détermine le type réel de chaque objet à **l’exécution** et appelle la méthode appropriée.

---

### **4. Résultat attendu**

Lors de l'exécution, le programme produit la sortie suivante :

```
Voiture de marque : Toyota, Nombre de portes : 4
Voiture de marque : Tesla, Nombre de portes : 4
Moto de marque : Harley-Davidson, Avec side-car : Oui
Moto de marque : Yamaha, Avec side-car : Non
```

---

### **Points importants à retenir**

1. **Hiérarchie de classes :**
    - `Vehicule` est une classe de base.
    - `Voiture` et `Moto` sont des classes dérivées avec des attributs et des comportements spécifiques.

2. **Méthodes virtuelles :**
    - La méthode `afficherDetails` est déclarée **virtuelle** dans `Vehicule`.
    - Chaque classe dérivée redéfinit cette méthode pour afficher des informations spécifiques.

3. **Polymorphisme dynamique :**
    - Le vecteur `std::vector<Vehicule*>` contient des pointeurs à des objets dérivés (`Voiture`, `Moto`).
    - L’appel à `afficherDetails()` est **résolu dynamiquement** à l'exécution en fonction du type réel de l'objet.

4. **Avantage :**
    - Ce mécanisme permet de manipuler tous les types de véhicules de manière générique, sans avoir besoin d’utiliser des structures conditionnelles (`if-else`, `switch`).

---

### **Application générale :**

Cette approche est utile pour traiter des **familles d’objets** (hiérarchies) de manière uniforme. Le polymorphisme dynamique rend le code **extensible** : si une nouvelle classe dérivée (`Camion`, par exemple) est ajoutée, il n’est pas nécessaire de modifier le code existant pour gérer cette nouvelle classe.

---

### **1. Suis-je obligé de redéfinir une fonction virtuelle dans une classe dérivée ?**

**Non, vous n'êtes pas obligé.**

- Si une classe dérivée ne redéfinit pas une méthode virtuelle, elle **hérite directement** de la version de la classe de base.
- Cela signifie que la classe dérivée peut utiliser la méthode telle qu'elle est définie dans la classe de base, sans modification.

#### Exemple :
```c++
#include <iostream>

class Vehicule {
public:
    virtual void afficherDetails() const {
        std::cout << "Détails généraux du véhicule." << std::endl;
    }
};

class Voiture : public Vehicule {
    // Pas de redéfinition de la méthode afficherDetails()
};

int main() {
    Voiture voiture;
    voiture.afficherDetails();  // Utilise la méthode de la classe de base

    return 0;
}
```

**Sortie :**
```
Détails généraux du véhicule.
```

**Conclusion :**
- Une classe dérivée **hérite automatiquement** de la méthode virtuelle si elle ne la redéfinit pas.
- Cela est utile si le comportement de la méthode dans la classe de base est suffisant.

---

### **2. Puis-je utiliser une fonction virtuelle, même si je ne suis pas dans la classe de base ?**

**Oui, vous pouvez l’utiliser via une instance ou un pointeur d’une classe dérivée.**

- Une méthode virtuelle peut être appelée depuis une instance ou un pointeur de la classe dérivée, car elle est **héritée**.
- Le comportement dépendra de la version de la méthode redéfinie (ou non) dans la classe dérivée.

#### Exemple avec redéfinition dans une classe dérivée :
```c++
#include <iostream>

class Vehicule {
public:
    virtual void afficherDetails() const {
        std::cout << "Détails généraux du véhicule." << std::endl;
    }
};

class Voiture : public Vehicule {
public:
    void afficherDetails() const override {
        std::cout << "Voiture avec des détails spécifiques." << std::endl;
    }
};

int main() {
    Voiture voiture;

    // Appel direct à la méthode virtuelle via l'objet dérivé
    voiture.afficherDetails();  // Appelle la version redéfinie dans Voiture

    return 0;
}
```

**Sortie :**
```
Voiture avec des détails spécifiques.
```

#### Exemple avec pointeur vers la classe de base (polymorphisme) :
```c++
int main() {
    Vehicule* vehicule = new Voiture();

    // Appel polymorphique via un pointeur à la classe de base
    vehicule->afficherDetails();  // Appelle toujours la version redéfinie dans Voiture

    delete vehicule;
    return 0;
}
```

**Sortie :**
```
Voiture avec des détails spécifiques.
```

**Conclusion :**
- Une fonction virtuelle peut être utilisée dans **une classe dérivée**, qu’elle soit redéfinie ou non.
- Si elle est appelée via un **pointeur ou une référence à la classe de base**, la **version appropriée** (déterminée à l’exécution) sera exécutée.

---

### **Résumé des points importants**

1. **Redéfinir une fonction virtuelle :**
    - Pas obligatoire.
    - Si non redéfinie, la classe dérivée utilisera la version héritée de la classe de base.

2. **Utilisation hors de la classe de base :**
    - Une fonction virtuelle héritée peut être utilisée dans la classe dérivée sans problème.
    - Vous pouvez appeler la méthode via une instance de la classe dérivée ou un pointeur à la classe de base (polymorphisme).

3. **Polymorphisme dynamique :**
    - Lorsqu’une méthode virtuelle est appelée via un pointeur ou une référence à la classe de base, la version spécifique à l’objet réel est exécutée.
    - Cela fonctionne même si vous ne redéfinissez pas la méthode dans la classe dérivée.

---

### **Exemple combiné pour tout clarifier :**
```c++
#include <iostream>

class Vehicule {
public:
    virtual void afficherDetails() const {
        std::cout << "Détails généraux du véhicule." << std::endl;
    }
};

class Voiture : public Vehicule {
    // Pas de redéfinition
};

class Moto : public Vehicule {
public:
    void afficherDetails() const override {
        std::cout << "Moto avec des détails spécifiques." << std::endl;
    }
};

int main() {
    Vehicule vehicule;
    Voiture voiture;
    Moto moto;

    // Appels directs
    vehicule.afficherDetails();  // Classe de base
    voiture.afficherDetails();  // Utilise la version de Vehicule
    moto.afficherDetails();     // Version redéfinie dans Moto

    // Pointeurs à la classe de base
    Vehicule* ptrVehicule = &vehicule;
    Vehicule* ptrVoiture = &voiture;
    Vehicule* ptrMoto = &moto;

    ptrVehicule->afficherDetails();  // Classe de base
    ptrVoiture->afficherDetails();  // Classe de base (héritée)
    ptrMoto->afficherDetails();     // Version redéfinie

    return 0;
}
```

**Sortie :**
```
Détails généraux du véhicule.
Détails généraux du véhicule.
Moto avec des détails spécifiques.
Détails généraux du véhicule.
Détails généraux du véhicule.
Moto avec des détails spécifiques.
```

Cela montre :
1. La méthode de la classe de base est utilisée si elle n’est pas redéfinie dans la classe dérivée.
2. Le polymorphisme dynamique appelle la version correcte selon le type réel de l’objet.

--- 

### **Qu'est-ce qu'une classe abstraite ?**

Une **classe abstraite** est une classe qui ne peut pas être instanciée directement. Elle sert de modèle pour d'autres classes. Une classe abstraite contient généralement une ou plusieurs **méthodes virtuelles pures**, qui doivent être redéfinies dans les classes dérivées.

---

### **Pourquoi utiliser une classe abstraite ?**

1. **Définir une interface commune :**
    - Elle impose aux classes dérivées de fournir une implémentation spécifique des méthodes définies comme **virtuelles pures**.

2. **Créer des hiérarchies d'objets polymorphiques :**
    - Permet de manipuler différents types d'objets dérivés de manière uniforme via un pointeur ou une référence à la classe de base abstraite.

---

### **Comment créer une classe abstraite ?**

Une classe devient abstraite si elle contient **au moins une méthode virtuelle pure**. Une méthode virtuelle pure est déclarée en utilisant `= 0` dans sa déclaration.

---

### **Exemple avec les voitures**

#### **Étape 1 : Définir une classe abstraite**

On crée une classe abstraite `Vehicule` pour représenter le concept général de véhicule. Elle contient une méthode virtuelle pure `afficherDetails()`.

```c++
#include <iostream>
#include <string>

class Vehicule {
public:
    Vehicule(const std::string& marque) : m_marque(marque) {}

    // Méthode virtuelle pure
    virtual void afficherDetails() const = 0;

    virtual ~Vehicule() {}  // Destructeur virtuel pour éviter les fuites de mémoire

protected:
    std::string m_marque;
};
```

**Détails :**
1. **`virtual void afficherDetails() const = 0;`**
    - Cette méthode est virtuelle pure.
    - Les classes dérivées **doivent** fournir une implémentation.

2. **Pas d'instanciation possible :**
    - Vous ne pouvez pas créer d'objets de type `Vehicule` directement.
    - Cela garantit que `Vehicule` est uniquement utilisée comme base pour les classes dérivées.

---

#### **Étape 2 : Créer des classes dérivées**

On dérive deux classes : `Voiture` et `Moto`. Ces classes redéfinissent la méthode virtuelle pure `afficherDetails`.

```c++
class Voiture : public Vehicule {
public:
    Voiture(const std::string& marque, int nbPortes)
        : Vehicule(marque), m_nbPortes(nbPortes) {}

    void afficherDetails() const override {
        std::cout << "Voiture de marque : " << m_marque << ", Nombre de portes : " << m_nbPortes << std::endl;
    }

private:
    int m_nbPortes;
};

class Moto : public Vehicule {
public:
    Moto(const std::string& marque, bool sideCar)
        : Vehicule(marque), m_sideCar(sideCar) {}

    void afficherDetails() const override {
        std::cout << "Moto de marque : " << m_marque << ", Avec side-car : " << (m_sideCar ? "Oui" : "Non") << std::endl;
    }

private:
    bool m_sideCar;
};
```

---

#### **Étape 3 : Utiliser les classes dérivées via la classe abstraite**

Créez un vecteur de pointeurs à `Vehicule` et ajoutez-y des objets de type `Voiture` et `Moto`. Vous pouvez appeler la méthode `afficherDetails` grâce au polymorphisme.

```c++
int main() {
    // Vecteur de pointeurs à la classe abstraite
    std::vector<Vehicule*> garage;

    // Création de véhicules
    Voiture voiture1("Toyota", 4);
    Voiture voiture2("Tesla", 4);
    Moto moto1("Harley-Davidson", true);
    Moto moto2("Yamaha", false);

    // Ajout au vecteur
    garage.push_back(&voiture1);
    garage.push_back(&voiture2);
    garage.push_back(&moto1);
    garage.push_back(&moto2);

    // Traitement générique
    for (auto vehicule : garage) {
        vehicule->afficherDetails();  // Appel polymorphique
    }

    return 0;
}
```

---

### **Résultat**

**Sortie :**
```
Voiture de marque : Toyota, Nombre de portes : 4
Voiture de marque : Tesla, Nombre de portes : 4
Moto de marque : Harley-Davidson, Avec side-car : Oui
Moto de marque : Yamaha, Avec side-car : Non
```

---

### **Points importants**

1. **Classe abstraite :**
    - `Vehicule` est abstraite car elle contient une méthode virtuelle pure (`afficherDetails`).
    - Elle ne peut pas être instanciée directement.

2. **Méthode virtuelle pure :**
    - Déclarez une méthode virtuelle pure avec `= 0`.
    - Toutes les classes dérivées doivent la redéfinir.

3. **Destructeur virtuel :**
    - Toujours définir un destructeur virtuel dans une classe abstraite pour éviter des comportements indéfinis lors de la destruction d'objets via un pointeur à la classe de base.

4. **Polymorphisme dynamique :**
    - Permet d’appeler la méthode appropriée selon le type réel de l’objet, même si le type déclaré est celui de la classe de base.

---

### **Résumé**
Une **classe abstraite** est une classe conçue pour être utilisée comme base pour des classes dérivées. Elle est utile pour :
- Définir une interface commune.
- Forcer les classes dérivées à implémenter certaines méthodes.
- Manipuler des objets dérivés de manière générique via le polymorphisme dynamique.
