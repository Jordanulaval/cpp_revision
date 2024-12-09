### **Comprendre `std::unique_ptr` en détail avec l'exemple :**
```c++
std::unique_ptr<Employe> ptEmploye (new Employe("harry"));
```

Cet exemple utilise **`std::unique_ptr`**, une classe de pointeur intelligent (smart pointer) en C++ introduite avec la bibliothèque standard C++11. Voici tout ce qu'il faut savoir à ce sujet.

---

### **1. Qu'est-ce qu'un `std::unique_ptr` ?**

Un **`std::unique_ptr`** est un **pointeur intelligent** qui possède et gère un objet alloué dynamiquement. Il garantit qu’un objet est **libéré automatiquement** dès que le `std::unique_ptr` qui le possède sort de sa portée.

- Contrairement aux pointeurs bruts (raw pointers), vous n’avez pas besoin d’appeler explicitement `delete`.
- **Propriété principale :**
    - Le `std::unique_ptr` est **unique** : un seul pointeur peut posséder un objet à la fois. La copie d’un `std::unique_ptr` n’est pas autorisée pour éviter plusieurs propriétaires.

---

### **2. Analyse de l'exemple**

```c++
std::unique_ptr<Employe> ptEmploye (new Employe("harry"));
```

- **`new Employe("harry")`** :
    - Alloue dynamiquement un objet `Employe` sur le tas avec le nom `"harry"`.

- **`std::unique_ptr<Employe>`** :
    - Crée un pointeur intelligent qui devient le **propriétaire unique** de l'objet `Employe` alloué dynamiquement.

- **Propriétés :**
    - Lorsque `ptEmploye` sort de sa portée (par exemple, à la fin de la fonction), le destructeur de `std::unique_ptr` est automatiquement appelé, ce qui libère la mémoire allouée pour `"harry"`.

---

### **3. Fonctionnalités et comportement**

#### **3.1. Automatisation de la gestion de mémoire**
Avec un `std::unique_ptr`, vous n’avez plus besoin d’appeler explicitement `delete`. Cela réduit le risque de **fuites de mémoire** et de **pointeurs pendants** (dangling pointers).

Exemple classique sans smart pointers :
```c++
Employe* p = new Employe("harry");
// Si vous oubliez `delete p;`, cela provoque une fuite de mémoire.
delete p;
```

Avec `std::unique_ptr` :
```c++
std::unique_ptr<Employe> ptEmploye (new Employe("harry"));
// Pas besoin de `delete` ; la mémoire est libérée automatiquement.
```

---

#### **3.2. Opérations interdites et autorisées**

1. **Copie interdite :**
    - Un `std::unique_ptr` ne peut pas être copié, car cela contredirait son caractère unique.
    - Exemple :
      ```c++
      std::unique_ptr<Employe> pt1(new Employe("harry"));
      std::unique_ptr<Employe> pt2 = pt1;  // ERREUR : Copie interdite
      ```

2. **Transfert de propriété (move)** :
    - Un `std::unique_ptr` peut être transféré en utilisant `std::move`, ce qui transfère la propriété d’un pointeur à un autre.
    - Exemple :
      ```c++
      std::unique_ptr<Employe> pt1(new Employe("harry"));
      std::unique_ptr<Employe> pt2 = std::move(pt1);  // OK : pt1 devient nul
      ```

---

#### **3.3. Accès à l’objet géré**

Vous pouvez accéder à l'objet pointé par un `std::unique_ptr` de manière similaire à un pointeur brut.

- **Opérateur `->` et `*` :**
    - Utilisez `->` pour accéder aux membres de l’objet géré.
    - Utilisez `*` pour accéder directement à l’objet.

Exemple :
```c++
ptEmploye->setNom("Harry Smith");  // Accès via `->`
std::cout << ptEmploye->getNom(); // Affiche "Harry Smith"
```

---

### **4. Meilleure pratique : Utiliser `std::make_unique`**

Depuis C++14, il est recommandé d’utiliser `std::make_unique` au lieu de l’opérateur `new` pour initialiser un `std::unique_ptr`.

#### **Pourquoi ?**
- Plus sûr : Évite des problèmes subtils liés à l’allocation.
- Plus lisible et concis.

#### **Exemple équivalent :**
```c++
// Avec new (moins recommandé)
std::unique_ptr<Employe> ptEmploye(new Employe("harry"));

// Avec std::make_unique (recommandé)
auto ptEmploye = std::make_unique<Employe>("harry");
```

---

### **5. Gestion des ressources avec `std::unique_ptr`**

Un `std::unique_ptr` peut gérer tout type de ressources nécessitant un nettoyage manuel (par exemple, un fichier, une connexion réseau, etc.).

Exemple avec un fichier :
```c++
#include <memory>
#include <cstdio>  // Pour FILE

struct FileDeleter {
    void operator()(FILE* file) const {
        if (file) fclose(file);
    }
};

int main() {
    // `std::unique_ptr` gère un fichier ouvert
    std::unique_ptr<FILE, FileDeleter> fichier(fopen("example.txt", "r"));
    if (fichier) {
        // Lire ou écrire dans le fichier
    }
    // Le fichier est automatiquement fermé à la sortie du scope
    return 0;
}
```

---

### **6. Comparaison avec les autres smart pointers**

| **Pointeur intelligent** | **Propriétaire unique** | **Partageable** | **Référence comptée** | **Exemple d’utilisation**            |
|---------------------------|--------------------------|------------------|------------------------|---------------------------------------|
| `std::unique_ptr`         | Oui                     | Non              | Non                    | Gestion exclusive d’un objet         |
| `std::shared_ptr`         | Non                     | Oui              | Oui                    | Partage d’un objet entre plusieurs propriétaires |
| `std::weak_ptr`           | Non                     | Oui              | Oui (pas propriétaire) | Éviter les références circulaires avec `std::shared_ptr` |

---

### **7. Points importants à retenir**

1. **Automatisation :**
    - `std::unique_ptr` automatise la gestion de mémoire en libérant l’objet lorsqu’il sort de portée.

2. **Propriétaire unique :**
    - Un seul `std::unique_ptr` peut posséder un objet donné. Cela garantit un contrôle strict sur l’allocation dynamique.

3. **Transfert sécurisé :**
    - Utilisez `std::move` pour transférer la propriété à un autre `std::unique_ptr`.

4. **Pas de duplication :**
    - La copie d’un `std::unique_ptr` est interdite pour éviter plusieurs propriétaires du même objet.

5. **Utilisez `std::make_unique` :**
    - Préférez `std::make_unique` pour plus de sécurité et de lisibilité.

---

### **Exemple complet**
Voici un exemple qui montre toutes les fonctionnalités principales d’un `std::unique_ptr`.

```c++
#include <iostream>
#include <memory>
#include <string>

class Employe {
public:
    Employe(const std::string& nom) : m_nom(nom) {
        std::cout << "Constructeur d'Employe : " << m_nom << std::endl;
    }
    ~Employe() {
        std::cout << "Destructeur d'Employe : " << m_nom << std::endl;
    }
    void afficher() const {
        std::cout << "Nom de l'employé : " << m_nom << std::endl;
    }

private:
    std::string m_nom;
};

int main() {
    // Création d'un Employé avec unique_ptr
    auto employe1 = std::make_unique<Employe>("Harry");

    // Accès à l'objet via unique_ptr
    employe1->afficher();

    // Transfert de propriété
    auto employe2 = std::move(employe1);  // employe1 devient nul

    if (!employe1) {
        std::cout << "employe1 ne possède plus d'objet." << std::endl;
    }

    employe2->afficher();  // Toujours accessible via employe2

    // Fin de portée : employe2 est détruit, mémoire libérée automatiquement
    return 0;
}
```

**Sortie :**
```
Constructeur d'Employe : Harry
Nom de l'employé : Harry
employe1 ne possède plus d'objet.
Nom de l'employé : Harry
Destructeur d'Employe : Harry
```

---

### **Résumé**
- `std::unique_ptr` est un smart pointer qui garantit une gestion de mémoire sûre et efficace.
- Il est particulièrement utile pour éviter les fuites de mémoire.
- En l’utilisant correctement avec `std::move` et `std::make_unique`, vous bénéficiez d’un code plus sûr et plus lisible.

### **Comprendre les copies d'objets en C++ : Shallow Copy vs Deep Copy**

En C++, lorsque vous copiez un objet, vous pouvez effectuer une **copie de surface (shallow copy)** ou une **copie en profondeur (deep copy)**. Voici tout ce que vous devez savoir, expliqué avec des exemples et des concepts associés.

---

### **1. Shallow Copy (Copie de surface)**

Une **copie de surface** signifie que seules les **adresses mémoire** ou références sont copiées. Les deux objets partagent alors la même mémoire sous-jacente. Cela peut causer des problèmes si un des objets est modifié ou détruit, car cela affectera également l'autre.

#### **Exemple :**
Imaginons une classe `Liste` qui contient un pointeur vers une zone de mémoire allouée dynamiquement.

```c++
#include <iostream>
#include <vector>
#include <string>

class Liste {
public:
    Liste(const std::vector<std::string>& elements) {
        m_elements = new std::vector<std::string>(elements);
    }

    // Constructeur de copie par défaut (shallow copy)
    Liste(const Liste& autre) = default;

    void afficher() const {
        for (const auto& elem : *m_elements) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    ~Liste() {
        delete m_elements;  // Libère la mémoire
    }

private:
    std::vector<std::string>* m_elements;  // Alloué dynamiquement
};

int main() {
    Liste liste1({"Alice", "Bob", "Charlie"});
    Liste liste2 = liste1;  // Copie de surface (shallow copy par défaut)

    liste1.afficher();
    liste2.afficher();

    return 0;  // CRASH : liste1 et liste2 partagent la même mémoire
}
```

#### **Problème :**
- Lorsque `liste1` est détruite, la mémoire pointée par `m_elements` est libérée.
- Ensuite, quand `liste2` est détruite, elle tente de libérer la même mémoire, causant un crash (double free).

---

### **2. Deep Copy (Copie en profondeur)**

Une **copie en profondeur** signifie que chaque ressource est dupliquée, ce qui rend les objets complètement indépendants. Cela est souvent nécessaire lorsque des ressources dynamiques (comme des pointeurs ou des fichiers) sont utilisées.

#### **Implémentation d'une copie en profondeur :**
Voici un exemple corrigé de la classe `Liste` avec un constructeur de copie personnalisé pour effectuer une deep copy.

```c++
class Liste {
public:
    Liste(const std::vector<std::string>& elements) {
        m_elements = new std::vector<std::string>(elements);
    }

    // Constructeur de copie pour deep copy
    Liste(const Liste& autre) {
        m_elements = new std::vector<std::string>(*autre.m_elements);
    }

    // Opérateur de copie pour deep copy
    Liste& operator=(const Liste& autre) {
        if (this != &autre) {  // Éviter l'auto-assignation
            delete m_elements;  // Libérer la ressource existante
            m_elements = new std::vector<std::string>(*autre.m_elements);
        }
        return *this;
    }

    void afficher() const {
        for (const auto& elem : *m_elements) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    ~Liste() {
        delete m_elements;
    }

private:
    std::vector<std::string>* m_elements;
};

int main() {
    Liste liste1({"Alice", "Bob", "Charlie"});
    Liste liste2 = liste1;  // Copie en profondeur

    liste2.afficher();

    liste1.afficher();
    return 0;  // Pas de crash !
}
```

---

### **3. Cas pratique : Gestion avec `std::unique_ptr`**

Lorsque vous utilisez des **pointeurs intelligents**, comme `std::unique_ptr`, le comportement par défaut empêche une **copie de surface**. Voici une implémentation d'un deep copy avec `std::unique_ptr`.

#### **Exemple de classe `Equipe` :**

```c++
#include <iostream>
#include <vector>
#include <memory>
#include <string>

class Membre {
public:
    explicit Membre(const std::string& nom) : m_nom(nom) {}
    std::string getNom() const { return m_nom; }

private:
    std::string m_nom;
};

class Equipe {
public:
    explicit Equipe(const std::string& nom) : m_nom(nom) {}

    // Constructeur de copie pour deep copy
    Equipe(const Equipe& autre) : m_nom(autre.m_nom) {
        for (const auto& membre : autre.m_membres) {
            m_membres.push_back(std::make_unique<Membre>(*membre));
        }
    }

    // Opérateur de copie pour deep copy
    Equipe& operator=(const Equipe& autre) {
        if (this != &autre) {
            m_nom = autre.m_nom;
            m_membres.clear();
            for (const auto& membre : autre.m_membres) {
                m_membres.push_back(std::make_unique<Membre>(*membre));
            }
        }
        return *this;
    }

    void ajouterMembre(const std::string& nom) {
        m_membres.push_back(std::make_unique<Membre>(nom));
    }

    void afficher() const {
        std::cout << "Equipe : " << m_nom << "\nMembres : ";
        for (const auto& membre : m_membres) {
            std::cout << membre->getNom() << " ";
        }
        std::cout << std::endl;
    }

private:
    std::string m_nom;
    std::vector<std::unique_ptr<Membre>> m_membres;
};

int main() {
    Equipe equipe1("Gagnants");
    equipe1.ajouterMembre("Alice");
    equipe1.ajouterMembre("Bob");

    // Constructeur de copie
    Equipe equipe2 = equipe1;

    // Opérateur de copie
    Equipe equipe3("Perdants");
    equipe3 = equipe1;

    equipe1.afficher();
    equipe2.afficher();
    equipe3.afficher();

    return 0;
}
```

#### **Résultat attendu :**
```
Equipe : Gagnants
Membres : Alice Bob 
Equipe : Gagnants
Membres : Alice Bob 
Equipe : Gagnants
Membres : Alice Bob 
```

---

### **4. Points importants**

1. **Constructeur de copie :**
    - Appelé lorsqu’un objet est **copié** à sa création (par exemple, `Equipe equipe2 = equipe1;`).
    - Par défaut, le C++ effectue une copie de surface.

2. **Opérateur de copie (`=`) :**
    - Appelé lorsqu’un objet existant est **assigné** à un autre (par exemple, `equipe3 = equipe1;`).
    - Implémentez une copie en profondeur pour éviter les problèmes liés à l’allocation dynamique.

3. **Gestion de l’auto-assignation :**
    - Vérifiez toujours si `this != &autre` avant de libérer la mémoire et de copier les ressources.

4. **Utilisez des smart pointers :**
    - Avec `std::unique_ptr` et `std::make_unique`, vous pouvez implémenter facilement une gestion propre de la mémoire sans risque de fuites.

---

### **Résumé des bonnes pratiques**

- **Copie de surface :**
    - Réalisée par défaut si aucune méthode spéciale n’est implémentée.
    - Peut provoquer des problèmes avec des ressources dynamiques.

- **Copie en profondeur :**
    - Nécessite d’implémenter le constructeur de copie et l’opérateur de copie si des ressources dynamiques (pointeurs, fichiers, etc.) sont utilisées.
    - Préférez `std::unique_ptr` ou `std::shared_ptr` pour une gestion automatique des ressources.

- **Smart pointers :**
    - Évitez de gérer manuellement la mémoire. Utilisez les fonctionnalités modernes de C++ comme `std::unique_ptr` et `std::make_unique`.

En suivant ces règles, vous pourrez gérer les copies d’objets de manière sûre et efficace.