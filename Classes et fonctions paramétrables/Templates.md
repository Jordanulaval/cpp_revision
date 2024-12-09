### **Classes et Fonctions Paramétrables avec Templates en C++ : Explications et Exemples**

---

### **1. Introduction aux Templates**

#### **Définition**
Un **template** en C++ est un mécanisme permettant de définir des **classes ou des fonctions génériques**. Cela signifie que vous pouvez écrire un seul morceau de code qui peut fonctionner pour **différents types de données**.

- **Pourquoi utiliser des templates ?**
    - Évite la répétition de code.
    - Permet de créer des abstractions puissantes.
    - Rend le code extensible pour plusieurs types de données.

#### **Applications typiques**
1. Classes paramétrées comme les piles, listes, vecteurs, etc.
2. Fonctions génériques comme les comparaisons (`max`, `min`).

---

### **2. Classes Paramétrables**

#### **Problème**
Si vous voulez créer une classe `Pile` (Stack) pour gérer des entiers, des chaînes, ou des objets, il serait fastidieux d’écrire une nouvelle classe pour chaque type.

#### **Solution : Templates de classe**
Les templates permettent de paramétrer la classe avec un type `T`.

#### **Exemple : Classe Pile avec un type fixe**
Voici une classe qui fonctionne uniquement avec des `double`.

```c++
#include <iostream>
#include <vector>

class Pile {
public:
    Pile(int capacite = 0) : m_capacite(capacite) {}

    bool estVide() const { return m_laPile.empty(); }
    void push(const double& element) { m_laPile.push_back(element); }
    double pop() {
        double top = m_laPile.back();
        m_laPile.pop_back();
        return top;
    }

private:
    std::vector<double> m_laPile;
    int m_capacite;
};
```

#### **Limitation :**
Cette classe ne fonctionne qu'avec `double`. Vous devez la réécrire pour d'autres types.

---

#### **Avec Template**

Voici la même classe rendue générique avec un **template** :

```c++
#include <iostream>
#include <vector>

template <typename T>
class TPile {
public:
    TPile(int capacite = 0) : m_capacite(capacite) {}

    bool estVide() const { return m_laPile.empty(); }
    void push(const T& element) { m_laPile.push_back(element); }
    T pop() {
        T top = m_laPile.back();
        m_laPile.pop_back();
        return top;
    }

private:
    std::vector<T> m_laPile;
    int m_capacite;
};
```

#### **Instanciation :**
Vous pouvez maintenant utiliser `TPile` avec différents types.

```c++
int main() {
    TPile<int> pileEntiers(10);
    pileEntiers.push(42);
    std::cout << "Top : " << pileEntiers.pop() << std::endl;

    TPile<std::string> pileChaines(5);
    pileChaines.push("Hello");
    std::cout << "Top : " << pileChaines.pop() << std::endl;

    return 0;
}
```

**Sortie :**
```
Top : 42
Top : Hello
```

---

### **3. Fonctionnalités d’une Classe Template**

#### **Support Multi-Type**
La classe `TPile` peut fonctionner avec n’importe quel type, qu’il soit intégré (comme `int`) ou utilisateur (comme une classe `Employe`).

#### **Exemple : Pile avec un type utilisateur**
```c++
class Employe {
public:
    Employe(const std::string& nom) : m_nom(nom) {}
    std::string getNom() const { return m_nom; }

private:
    std::string m_nom;
};

int main() {
    TPile<Employe> pileEmployes(3);
    pileEmployes.push(Employe("Alice"));
    pileEmployes.push(Employe("Bob"));

    std::cout << "Employé au sommet : " << pileEmployes.pop().getNom() << std::endl;

    return 0;
}
```

**Sortie :**
```
Employé au sommet : Bob
```

---

### **4. Fonctions Paramétrables**

#### **Fonction Template**
Une fonction template permet de généraliser un comportement pour différents types.

#### **Exemple : Comparer deux valeurs**
```c++
template <typename T>
T max(const T& a, const T& b) {
    return (a > b) ? a : b;
}

int main() {
    std::cout << "Max (int) : " << max(3, 5) << std::endl;
    std::cout << "Max (double) : " << max(2.5, 1.8) << std::endl;

    return 0;
}
```

**Sortie :**
```
Max (int) : 5
Max (double) : 2.5
```

---

### **5. Implémentation des Templates**

#### **Fichier unique**
Les templates doivent être définis et implémentés dans le même fichier `.h` ou `.hpp`, car le compilateur doit voir le code pour générer les classes ou fonctions spécifiques au type.

#### **Exemple : Fichier `.hpp`**
```c++
// TPile.hpp
#include <vector>

template <typename T>
class TPile {
public:
    TPile(int capacite = 0) : m_capacite(capacite) {}
    bool estVide() const { return m_laPile.empty(); }
    void push(const T& element) { m_laPile.push_back(element); }
    T pop() {
        T top = m_laPile.back();
        m_laPile.pop_back();
        return top;
    }

private:
    std::vector<T> m_laPile;
    int m_capacite;
};
```

Incluez ensuite le fichier `.hpp` dans votre programme.

```cpp
#include "TPile.hpp"
```

---

### **6. Limites et Préoccupations**

1. **Instanciation tardive :**
    - Les templates ne sont pas instanciés tant qu’ils ne sont pas utilisés, ce qui peut allonger le temps de compilation.

2. **Code binaire :**
    - Pour chaque type utilisé, le compilateur génère un code séparé, ce qui peut augmenter la taille du binaire.

3. **Types complexes :**
    - Assurez-vous que le type utilisé avec un template supporte les opérations nécessaires (comme `<`, `=` pour une fonction `max`).

---

### **7. Exemple Complet**

Voici un exemple combinant classe et fonction template.

```c++
#include <iostream>
#include <vector>
#include <string>

// Classe template
template <typename T>
class TPile {
public:
    TPile(int capacite = 0) : m_capacite(capacite) {}

    bool estVide() const { return m_laPile.empty(); }
    void push(const T& element) { m_laPile.push_back(element); }
    T pop() {
        T top = m_laPile.back();
        m_laPile.pop_back();
        return top;
    }

private:
    std::vector<T> m_laPile;
    int m_capacite;
};

// Fonction template
template <typename T>
T max(const T& a, const T& b) {
    return (a > b) ? a : b;
}

int main() {
    // Utilisation de la classe template
    TPile<int> pileEntiers(10);
    pileEntiers.push(10);
    pileEntiers.push(20);
    std::cout << "Sommet de la pile : " << pileEntiers.pop() << std::endl;

    // Utilisation de la fonction template
    std::cout << "Max : " << max(3.5, 2.1) << std::endl;

    return 0;
}
```

**Sortie :**
```
Sommet de la pile : 20
Max : 3.5
```

---

### **Résumé**

1. **Templates** :
    - Permettent de généraliser les classes et fonctions.
    - Réduisent la duplication de code.

2. **Classes Templates** :
    - Paramétrables avec des types (`TPile<int>`, `TPile<std::string>`).

3. **Fonctions Templates** :
    - Fonctionnent avec différents types (`max<int>`, `max<double>`).

4. **Meilleures Pratiques** :
    - Gardez les implémentations de templates dans le même fichier que leur déclaration.
    - Testez les templates avec différents types pour garantir leur robustesse.

Les templates sont essentiels pour écrire un code générique, réutilisable et efficace en C++.