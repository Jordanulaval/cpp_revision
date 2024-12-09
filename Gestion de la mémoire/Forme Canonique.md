### **Forme canonique de Coplien en détail**

La **forme canonique de Coplien** en C++ est un ensemble de règles qui permettent de gérer correctement les objets contenant des ressources dynamiques (comme des allocations mémoire) ou des structures complexes. Elle est essentielle pour éviter les problèmes de copie incorrecte et de gestion des ressources.

---

### **1. Pourquoi la forme canonique de Coplien ?**

#### **Problème : Gestion des ressources dynamiques**
- Lorsque des ressources (comme de la mémoire, des fichiers, ou des connexions réseau) sont allouées dynamiquement dans une classe, il est nécessaire de s'assurer qu'elles sont correctement gérées.
- Par défaut, le **constructeur de copie** et l'**opérateur d'assignation** font une **copie de surface (shallow copy)**, ce qui peut provoquer des **problèmes de double libération** ou des **fuites mémoire**.

#### **Solution :**
1. Implémenter une **copie en profondeur (deep copy)**.
2. Utiliser des **pointeurs intelligents** pour simplifier la gestion des ressources.

---

### **2. Méthodes à implémenter dans la forme canonique**

Pour une classe qui gère des ressources dynamiques, vous devez implémenter ces trois méthodes :

1. **Constructeur de copie** :
    - Permet de créer une copie indépendante d'un objet.

2. **Opérateur d'assignation (`operator=`)** :
    - Permet d'assigner un objet à un autre en copiant ses données.

3. **Destructeur** :
    - Libère les ressources dynamiques de manière sûre.

---

### **3. Exemple : Gestion avec la forme canonique**

#### **Classe `Equipe` avec gestion manuelle**
Voici une implémentation où nous gérons manuellement la mémoire sans pointeurs intelligents.

```c++
#include <iostream>
#include <vector>
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
    // Constructeur
    explicit Equipe(const std::string& nom) : m_nom(nom), m_membres(nullptr), m_taille(0) {}

    // Destructeur
    ~Equipe() {
        delete[] m_membres;
    }

    // Constructeur de copie (deep copy)
    Equipe(const Equipe& autre) : m_nom(autre.m_nom), m_taille(autre.m_taille) {
        m_membres = new Membre[m_taille];
        for (size_t i = 0; i < m_taille; ++i) {
            m_membres[i] = autre.m_membres[i];
        }
    }

    // Opérateur d'assignation (deep copy)
    Equipe& operator=(const Equipe& autre) {
        if (this != &autre) {
            delete[] m_membres;  // Libérer les anciennes ressources

            m_nom = autre.m_nom;
            m_taille = autre.m_taille;
            m_membres = new Membre[m_taille];
            for (size_t i = 0; i < m_taille; ++i) {
                m_membres[i] = autre.m_membres[i];
            }
        }
        return *this;
    }

    void ajouterMembre(const std::string& nom) {
        Membre* nouveauxMembres = new Membre[m_taille + 1];
        for (size_t i = 0; i < m_taille; ++i) {
            nouveauxMembres[i] = m_membres[i];
        }
        nouveauxMembres[m_taille] = Membre(nom);
        delete[] m_membres;
        m_membres = nouveauxMembres;
        ++m_taille;
    }

    void afficher() const {
        std::cout << "Equipe : " << m_nom << "\nMembres : ";
        for (size_t i = 0; i < m_taille; ++i) {
            std::cout << m_membres[i].getNom() << " ";
        }
        std::cout << std::endl;
    }

private:
    std::string m_nom;
    Membre* m_membres;  // Tableau dynamique de membres
    size_t m_taille;    // Taille du tableau
};

int main() {
    Equipe equipe1("Gagnants");
    equipe1.ajouterMembre("Alice");
    equipe1.ajouterMembre("Bob");

    Equipe equipe2 = equipe1;  // Appelle le constructeur de copie
    equipe2.ajouterMembre("Charlie");

    equipe1.afficher();
    equipe2.afficher();

    Equipe equipe3("Perdants");
    equipe3 = equipe1;  // Appelle l'opérateur d'assignation

    equipe3.afficher();

    return 0;
}
```

---

### **4. Simplification avec `std::unique_ptr`**

Avec C++11 et les **pointeurs intelligents**, vous n'avez plus besoin d'écrire manuellement le destructeur, le constructeur de copie et l'opérateur d'assignation.

#### **Exemple : Utilisation de `std::unique_ptr`**

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

    // Constructeur de copie (deep copy)
    Equipe(const Equipe& autre) : m_nom(autre.m_nom) {
        for (const auto& membre : autre.m_membres) {
            m_membres.push_back(std::make_unique<Membre>(*membre));
        }
    }

    // Opérateur d'assignation (deep copy)
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
    std::vector<std::unique_ptr<Membre>> m_membres;  // Pointeurs intelligents
};

int main() {
    Equipe equipe1("Gagnants");
    equipe1.ajouterMembre("Alice");
    equipe1.ajouterMembre("Bob");

    Equipe equipe2 = equipe1;  // Appelle le constructeur de copie
    equipe2.ajouterMembre("Charlie");

    equipe1.afficher();
    equipe2.afficher();

    Equipe equipe3("Perdants");
    equipe3 = equipe1;  // Appelle l'opérateur d'assignation

    equipe3.afficher();

    return 0;
}
```

---

### **5. Empêcher la copie d’un objet**

Si vous ne voulez pas que votre classe soit copiée, vous pouvez désactiver la copie de deux façons :

1. **Marquer les méthodes comme `= delete` :**
   ```c++
   class Equipe {
   public:
       Equipe(const std::string& nom) : m_nom(nom) {}
       Equipe(const Equipe&) = delete;             // Interdit le constructeur de copie
       Equipe& operator=(const Equipe&) = delete;  // Interdit l'opérateur d'assignation

   private:
       std::string m_nom;
   };
   ```

2. **Déclarer les méthodes en `private` :**
   ```c++
   class Equipe {
   public:
       Equipe(const std::string& nom) : m_nom(nom) {}

   private:
       Equipe(const Equipe&);             // Non accessible
       Equipe& operator=(const Equipe&);  // Non accessible
       std::string m_nom;
   };
   ```

#### **Avantage :**
- Le compilateur empêchera automatiquement toute tentative de copie ou d’assignation.

---

### **Résumé**

1. **Forme canonique de Coplien :**
    - Implémentez le constructeur de copie, l’opérateur d’assignation, et gérez correctement les ressources dynamiques.

2. **Utilisez des pointeurs intelligents (`std::unique_ptr`) :**
    - Simplifiez la gestion des ressources tout en évitant les fuites mémoire.

3. **Empêcher la copie :**
    - Si la copie n’est pas nécessaire ou risquée (objets gérant des ressources), désactivez-la en utilisant `= delete` ou en la rendant privée.

En appliquant ces principes, vous garantissez que vos classes gèrent les ressources de manière sécurisée et efficace.