### **L'Héritage : Synthèse**

---

### **Qu'est-ce que l'héritage ?**

L'héritage permet à une classe dérivée (ou enfant) de **réutiliser** les propriétés et les comportements définis dans une classe de base (ou parent). Cela simplifie le développement en partageant du code déjà testé et validé.

- **Avantage principal :** Réutilisation du code, gain de temps, et cohérence.
- **Analogie :** L'héritage est comme un arbre généalogique :
    - La **classe de base** est le parent commun.
    - Les **classes dérivées** sont ses descendants qui héritent de ses caractéristiques tout en ajoutant leurs propres spécificités.

**Exemple concret :**
- Une classe `Vehicule` comme base.
- Les classes `Voiture` et `Moto` héritent de `Vehicule`.

---

### **Fonctionnement des constructeurs dans l'héritage**

#### **1. Si la classe de base possède un constructeur par défaut :**
Le constructeur par défaut est appelé **automatiquement** lors de la création d'un objet dérivé.

**Exemple :**
```c++
class Base {
public:
    Base() {
        std::cout << "Constructeur de la classe Base appelé." << std::endl;
    }
};

class Derivee : public Base {
    // Aucun appel explicite requis
};

int main() {
    Derivee obj;  // Appelle automatiquement le constructeur par défaut de Base
    return 0;
}
```

**Sortie :**
```
Constructeur de la classe Base appelé.
```

---

#### **2. Si la classe de base n'a pas de constructeur par défaut :**
Dans ce cas, il est **obligatoire d'appeler explicitement** le constructeur de la classe de base depuis la classe dérivée.

**Exemple :**
```c++
class Base {
public:
    Base(int x) {
        std::cout << "Constructeur de la classe Base avec x = " << x << std::endl;
    }
};

class Derivee : public Base {
public:
    Derivee(int y) : Base(y) {  // Appel explicite
        std::cout << "Constructeur de la classe Derivee avec y = " << y << std::endl;
    }
};

int main() {
    Derivee obj(42);  // Passe 42 au constructeur de Base
    return 0;
}
```

**Sortie :**
```
Constructeur de la classe Base avec x = 42
Constructeur de la classe Derivee avec y = 42
```

---

#### **3. Transmettre des paramètres depuis la classe dérivée :**
Si la classe dérivée reçoit des paramètres nécessaires à la classe de base, utilisez une **liste d’initialisation** pour les transmettre.

**Exemple :**
```c++
class Base {
public:
    Base(const std::string& nom) {
        std::cout << "Constructeur de Base pour " << nom << std::endl;
    }
};

class Derivee : public Base {
public:
    Derivee(const std::string& prenom, const std::string& nom) : Base(nom) {
        std::cout << "Constructeur de Derivee pour " << prenom << " " << nom << std::endl;
    }
};

int main() {
    Derivee obj("Jordan", "Mathieu");
    return 0;
}
```

**Sortie :**
```
Constructeur de Base pour Mathieu
Constructeur de Derivee pour Jordan Mathieu
```

---

### **Construction et Destruction dans l'héritage**

1. **Construction :** Les constructeurs sont appelés de la classe de base (parent) à la classe dérivée (enfant).
2. **Destruction :** Les destructeurs sont appelés dans l’ordre inverse : de la classe dérivée vers la classe de base.

---

### **Contrôle d’accès dans l’héritage**

L’héritage affecte la visibilité des membres de la classe de base dans la classe dérivée. Voici un résumé des niveaux d’accès :

| Type de membre de la classe de base | Accessible dans la classe dérivée ? | Accessible en dehors ? |
|--------------------------------------|-------------------------------------|--------------------------|
| **Public**                           | Oui                                 | Oui                      |
| **Protected**                        | Oui                                 | Non                      |
| **Private**                          | Non                                 | Non                      |

---

### **Héritage vs Composition**

---

#### **1. Héritage :**
- **Relation :** "Est un" (**is-a**).
- Une classe dérivée hérite des comportements et propriétés de la classe de base.

**Exemple :**
```c++
class Vehicule {
public:
    Vehicule(const std::string& marque) : m_marque(marque) {}

    void afficher() const {
        std::cout << "Marque : " << m_marque << std::endl;
    }

protected:
    std::string m_marque;
};

class Voiture : public Vehicule {
public:
    Voiture(const std::string& marque, int nbPortes)
        : Vehicule(marque), m_nbPortes(nbPortes) {}

    void afficher() const {
        Vehicule::afficher();
        std::cout << "Nombre de portes : " << m_nbPortes << std::endl;
    }

private:
    int m_nbPortes;
};
```

---

#### **2. Composition :**
- **Relation :** "A un" (**has-a**).
- Une classe inclut une autre classe comme attribut et délègue certaines responsabilités.

**Exemple :**
```c++
class Adresse {
public:
    Adresse(const std::string& rue, const std::string& ville) : m_rue(rue), m_ville(ville) {}

    void afficher() const {
        std::cout << m_rue << ", " << m_ville << std::endl;
    }

private:
    std::string m_rue;
    std::string m_ville;
};

class Maison {
public:
    Maison(const std::string& proprietaire, const Adresse& adresse)
        : m_proprietaire(proprietaire), m_adresse(adresse) {}

    void afficher() const {
        std::cout << "Propriétaire : " << m_proprietaire << std::endl;
        std::cout << "Adresse : ";
        m_adresse.afficher();
    }

private:
    std::string m_proprietaire;
    Adresse m_adresse;
};
```

---

### **Comparaison Héritage vs Composition**

| Aspect                | Héritage                                    | Composition                                   |
|-----------------------|---------------------------------------------|----------------------------------------------|
| **Relation**          | "Est un" (`is-a`)                          | "A un" (`has-a`)                             |
| **Dépendance**        | Forte : Les classes sont liées hiérarchiquement. | Faible : Les classes sont indépendantes.    |
| **Réutilisation**     | Réutilise directement les comportements de la classe de base. | Réutilise via délégation.                   |
| **Flexibilité**       | Moins flexible, modification de la base impacte tout. | Plus flexible, indépendant de la base.      |

---

### **Quand choisir l’un ou l’autre ?**

1. **Héritage :**
    - Si la relation est logique en termes de "est un".
    - Exemple : `Voiture` est un `Vehicule`.

2. **Composition :**
    - Si la relation est logique en termes de "a un".
    - Exemple : Une `Maison` a une `Adresse`.

---

### **Conclusion**

- L’héritage est utile pour des relations hiérarchiques fortes, où la classe dérivée est une spécialisation de la classe de base.
- La composition est plus adaptée pour des relations modulaires et flexibles, favorisant la réutilisation sans couplage fort.

### Ajout de Méthodes dans la Classe de Base

---

#### **Contexte**

Nous avons :
1. Une classe de base `Vehicule` qui représente un véhicule avec des caractéristiques générales (marque, modèle, etc.).
2. Une méthode statique dans `Vehicule` pour calculer la consommation d'essence sur une distance donnée.
3. Une classe dérivée `Voiture` qui hérite de `Vehicule`.

Nous voulons :
1. Ajouter une méthode **`calculerConsommation`** dans `Vehicule` pour calculer la consommation d'essence en fonction d'une distance et d'une consommation au litre.
2. Ajouter une méthode **`calculerAutonomie`** dans `Vehicule` pour estimer l'autonomie restante en fonction du carburant disponible.
3. Montrer que `Voiture` hérite automatiquement de ces méthodes.

---

### Étape 1 : La Classe de Base `Vehicule`

#### **Code :**
```c++
#include <iostream>
#include <string>

class Vehicule {
public:
    Vehicule(const std::string& marque, const std::string& modele, double reservoir)
        : m_marque(marque), m_modele(modele), m_reservoir(reservoir) {}

    // Méthode statique : Calcul de consommation pour une distance donnée
    static double calculerConsommation(double distance, double consommationParKm) {
        return distance * consommationParKm;
    }

    // Méthode pour calculer l'autonomie restante
    double calculerAutonomie(double consommationParKm) const {
        return m_reservoir / consommationParKm;
    }

    void afficherDetails() const {
        std::cout << "Marque : " << m_marque << ", Modèle : " << m_modele << ", Réservoir : " << m_reservoir << " litres\n";
    }

protected:
    std::string m_marque;
    std::string m_modele;
    double m_reservoir;  // Capacité du réservoir en litres
};
```

---

### Étape 2 : La Classe Dérivée `Voiture`

La classe `Voiture` hérite de `Vehicule`. Elle n'a pas besoin de redéfinir les méthodes `calculerConsommation` ou `calculerAutonomie`, car elles sont déjà disponibles grâce à l'héritage.

#### **Code :**
```c++
class Voiture : public Vehicule {
public:
    Voiture(const std::string& marque, const std::string& modele, double reservoir, int nbPortes)
        : Vehicule(marque, modele, reservoir), m_nbPortes(nbPortes) {}

    void afficherDetails() const {
        Vehicule::afficherDetails();  // Appel à la méthode de la classe de base
        std::cout << "Nombre de portes : " << m_nbPortes << "\n";
    }

private:
    int m_nbPortes;
};
```

---

### Étape 3 : Utilisation dans le `main`

Voici comment utiliser ces classes pour calculer la consommation et l'autonomie d'une voiture.

#### **Code :**
```c++
int main() {
    // Création d'une voiture
    Voiture maVoiture("Toyota", "Corolla", 50.0, 4);

    // Affichage des détails de la voiture
    maVoiture.afficherDetails();

    // Calcul de la consommation pour 100 km (5 litres/100 km -> 0.05 litres/km)
    double consommation = Vehicule::calculerConsommation(100, 0.05);
    std::cout << "Consommation pour 100 km : " << consommation << " litres\n";

    // Calcul de l'autonomie restante avec un réservoir plein
    double autonomie = maVoiture.calculerAutonomie(0.05);
    std::cout << "Autonomie restante : " << autonomie << " km\n";

    return 0;
}
```

---

### Résultat

**Sortie :**
```
Marque : Toyota, Modèle : Corolla, Réservoir : 50 litres
Nombre de portes : 4
Consommation pour 100 km : 5 litres
Autonomie restante : 1000 km
```

---

### **Explication Simple**

1. **Classe de Base (`Vehicule`) :**
    - Ajoute des méthodes utiles pour **tous les types de véhicules**, comme :
        - Calculer la consommation sur une distance donnée.
        - Estimer l'autonomie en fonction du carburant disponible.

2. **Classe Dérivée (`Voiture`) :**
    - Hérite directement des fonctionnalités de `Vehicule`.
    - N'a pas besoin de redéfinir les méthodes générales (réutilisation du code).
    - Peut ajouter des propriétés spécifiques (comme le nombre de portes).

3. **Utilisation des Méthodes :**
    - La méthode **statique `calculerConsommation`** est utilisée sans créer d'objet.
    - La méthode **`calculerAutonomie`** est utilisée sur une instance de `Voiture`, mais elle vient directement de `Vehicule`.

---

### **Résumé**

- **Avantage principal de l'héritage :** La classe dérivée (`Voiture`) peut directement utiliser les méthodes de la classe de base (`Vehicule`), même si elles sont ajoutées après sa définition.
- Si une autre classe, comme `Moto`, hérite de `Vehicule`, elle bénéficiera également des méthodes `calculerConsommation` et `calculerAutonomie`.

C’est une gestion efficace et modulaire du code ! 🚗

### **Qu'est-ce qu'une méthode statique ?**

---

Une **méthode statique** est une méthode d'une classe qui n'est **pas liée à une instance spécifique** de cette classe. Elle appartient directement à la classe elle-même et peut être appelée sans créer d'objet.

---

### **Caractéristiques d'une méthode statique**

1. **Accessible sans objet :**
    - Une méthode statique peut être appelée directement via le nom de la classe, sans avoir besoin de créer une instance.
    - **Exemple :**
      ```cpp
      MaClasse::maMethodeStatique();
      ```

2. **Pas d'accès aux membres non statiques :**
    - Une méthode statique ne peut pas accéder directement aux attributs ou méthodes non statiques de la classe, car elle n'est pas liée à une instance.
    - Elle peut uniquement utiliser des membres **statiques** (attributs ou méthodes).

3. **Utilité :**
    - Idéale pour des opérations **indépendantes d'une instance**.
    - Utilisée pour des **fonctionnalités globales** liées à la classe (par exemple, utilitaires, calculs, conversions).

---

### **À quoi sert une méthode statique ?**

1. **Fonctionnalités partagées :**
    - Fournir une fonctionnalité commune ou utilitaire qui ne dépend pas d'une instance spécifique.
    - Exemple : Une méthode qui effectue un calcul mathématique.

2. **Gestion d'états partagés :**
    - Manipuler des **attributs statiques**, c'est-à-dire des données partagées par toutes les instances de la classe.

3. **Simplification :**
    - Éviter la création d'instances inutiles pour des opérations simples.
    - Exemple : `std::pow()` est une fonction utilitaire en mathématiques.

---

### **Comment coder une méthode statique ?**

#### **Étape 1 : Déclarer la méthode dans la classe**
- Utilisez le mot-clé **`static`** pour déclarer la méthode comme statique.

#### **Étape 2 : Définir la méthode en dehors de la classe**
- N'ajoutez pas le mot-clé `static` lors de la définition, car il est déjà indiqué dans la déclaration.

---

### **Exemple : Méthode statique pour un calcul**

#### **Code complet :**
```c++
#include <iostream>
#include <cmath>  // Pour sqrt et pow

class MathUtils {
public:
    // Méthode statique pour calculer l'hypoténuse d'un triangle rectangle
    static double calculerHypotenuse(double a, double b) {
        return sqrt(pow(a, 2) + pow(b, 2));  // Théorème de Pythagore
    }
};

int main() {
    double a = 3.0;
    double b = 4.0;

    // Appel de la méthode statique sans créer d'objet
    double hypotenuse = MathUtils::calculerHypotenuse(a, b);

    std::cout << "L'hypoténuse est : " << hypotenuse << std::endl;

    return 0;
}
```

#### **Sortie :**
```
L'hypoténuse est : 5
```

---

### **Cas d'utilisation avancé : Attribut statique avec méthode statique**

Les **attributs statiques** sont partagés par toutes les instances de la classe. Une méthode statique peut manipuler ces attributs.

#### **Exemple : Gestion d'un compteur global**
```c++
#include <iostream>

class Compteur {
public:
    // Méthode statique pour incrémenter le compteur
    static void incrementerCompteur() {
        m_compteur++;
    }

    // Méthode statique pour obtenir la valeur du compteur
    static int getCompteur() {
        return m_compteur;
    }

private:
    static int m_compteur;  // Attribut statique
};

// Initialisation de l'attribut statique
int Compteur::m_compteur = 0;

int main() {
    // Appels aux méthodes statiques
    Compteur::incrementerCompteur();
    Compteur::incrementerCompteur();

    std::cout << "Compteur actuel : " << Compteur::getCompteur() << std::endl;

    return 0;
}
```

#### **Sortie :**
```
Compteur actuel : 2
```

---

### **Résumé**

- **Une méthode statique :**
    - Est liée à la classe, pas à une instance.
    - S'utilise pour des fonctionnalités globales ou des opérations indépendantes des objets.
    - S'appelle via `NomClasse::NomMethode`.

- **Avantages :**
    - Réduit la nécessité de créer des objets inutiles.
    - Fournit un moyen simple de partager des fonctionnalités communes.

- **Limitations :**
    - Ne peut pas accéder directement aux membres non statiques de la classe.
    - Doit être utilisée uniquement lorsque le comportement est réellement indépendant d'une instance.
---

### Méthodes dans une Classe Dérivée : Exemple avec Voiture

Pour simplifier et illustrer les concepts **remplacer**, **hériter**, et **augmenter**, utilisons une classe de base `Vehicule` et une classe dérivée `Voiture`.

---

### **1. Concepts avec des voitures**
1. **Remplacer une méthode :**
    - La classe dérivée redéfinit complètement une méthode de la classe de base pour en modifier le comportement.

2. **Hériter une méthode :**
    - La classe dérivée utilise directement la méthode de la classe de base, sans modification.

3. **Augmenter une méthode :**
    - La classe dérivée utilise la méthode de la classe de base et ajoute des comportements supplémentaires.

---

### **2. Classe de base : `Vehicule`**

Commençons avec une classe `Vehicule` qui contient des méthodes générales pour tous les véhicules :
- **`afficherDetails` :** Affiche les détails généraux du véhicule.
- **`deplacer` :** Change la position d'un véhicule (par exemple, sur une carte).

#### **Code :**
```c++
#include <iostream>
#include <string>

class Vehicule {
public:
    Vehicule(const std::string& marque, const std::string& modele, int position)
        : m_marque(marque), m_modele(modele), m_position(position) {}

    // Méthode générale pour afficher les détails
    virtual void afficherDetails() const {
        std::cout << "Marque : " << m_marque << ", Modèle : " << m_modele << ", Position : " << m_position << std::endl;
    }

    // Méthode pour déplacer le véhicule
    void deplacer(int nouvellePosition) {
        m_position = nouvellePosition;
    }

protected:
    std::string m_marque;
    std::string m_modele;
    int m_position;
};
```

---

### **3. Remplacer une méthode**

La classe dérivée `Voiture` remplace la méthode `afficherDetails` pour afficher des détails spécifiques aux voitures, comme le nombre de portes.

#### **Code :**
```c++
class Voiture : public Vehicule {
public:
    Voiture(const std::string& marque, const std::string& modele, int position, int nbPortes)
        : Vehicule(marque, modele, position), m_nbPortes(nbPortes) {}

    // Remplace la méthode afficherDetails
    void afficherDetails() const override {
        std::cout << "Voiture - Marque : " << m_marque << ", Modèle : " << m_modele
                  << ", Position : " << m_position << ", Portes : " << m_nbPortes << std::endl;
    }

private:
    int m_nbPortes;
};
```

#### **Explication :**
- `Voiture::afficherDetails` remplace `Vehicule::afficherDetails`.
- L'affichage est spécifique aux voitures et inclut des détails supplémentaires.

---

### **4. Hériter une méthode**

La classe dérivée `Voiture` peut utiliser directement la méthode `deplacer` de `Vehicule`, sans la redéfinir.

#### **Code dans le `main` :**
```c++
int main() {
    Voiture voiture("Toyota", "Corolla", 0, 4);

    // Utilisation directe de la méthode héritée
    voiture.afficherDetails();
    voiture.deplacer(10);
    voiture.afficherDetails();

    return 0;
}
```

#### **Sortie :**
```
Voiture - Marque : Toyota, Modèle : Corolla, Position : 0, Portes : 4
Voiture - Marque : Toyota, Modèle : Corolla, Position : 10, Portes : 4
```

#### **Explication :**
- `Voiture` utilise la méthode `deplacer` telle qu'elle est définie dans `Vehicule`.
- Aucune modification n'est nécessaire.

---

### **5. Augmenter une méthode**

La classe dérivée `Voiture` ajoute des fonctionnalités à la méthode `afficherDetails` :
- Elle appelle d'abord `Vehicule::afficherDetails`.
- Ensuite, elle ajoute des informations spécifiques (par exemple, l'état du véhicule).

#### **Code :**
```c++
class VoitureAvancee : public Vehicule {
public:
    VoitureAvancee(const std::string& marque, const std::string& modele, int position, int nbPortes, bool estElectrique)
        : Vehicule(marque, modele, position), m_nbPortes(nbPortes), m_estElectrique(estElectrique) {}

    // Augmente la méthode afficherDetails
    void afficherDetails() const override {
        Vehicule::afficherDetails();  // Appel à la méthode de la classe de base
        std::cout << "Portes : " << m_nbPortes << ", Électrique : " << (m_estElectrique ? "Oui" : "Non") << std::endl;
    }

private:
    int m_nbPortes;
    bool m_estElectrique;
};
```

#### **Code dans le `main` :**
```c++
int main() {
    VoitureAvancee voiture("Tesla", "Model 3", 0, 4, true);

    // Appelle la méthode augmentée
    voiture.afficherDetails();

    return 0;
}
```

#### **Sortie :**
```
Marque : Tesla, Modèle : Model 3, Position : 0
Portes : 4, Électrique : Oui
```

#### **Explication :**
- `VoitureAvancee::afficherDetails` appelle d'abord `Vehicule::afficherDetails`.
- Ensuite, elle ajoute des informations spécifiques, comme le nombre de portes et si la voiture est électrique.

---

### **Résumé des trois cas**

| Cas                | Explication                                                                                   | Exemple avec `Voiture`                                |
|---------------------|-----------------------------------------------------------------------------------------------|-------------------------------------------------------|
| **Remplacer**       | Redéfinir complètement une méthode de la classe de base.                                      | `Voiture::afficherDetails` remplace `Vehicule::afficherDetails`. |
| **Hériter**         | Utiliser une méthode de la classe de base sans modification.                                  | `Voiture::deplacer` utilise directement `Vehicule::deplacer`.   |
| **Augmenter**       | Appeler la méthode de la classe de base et ajouter du comportement supplémentaire.            | `VoitureAvancee::afficherDetails` augmente `Vehicule::afficherDetails`. |

---

### **Conclusion**

- **Remplacer :** Utile si le comportement de la classe de base ne correspond pas à celui attendu dans la classe dérivée.
- **Hériter :** Utilisé lorsque le comportement de la classe de base est adéquat.
- **Augmenter :** Idéal pour conserver le comportement de la classe de base tout en ajoutant des fonctionnalités spécifiques.

Ces mécanismes permettent de tirer parti de l’héritage tout en rendant les classes dérivées flexibles et adaptées à des besoins spécifiques. 🚗