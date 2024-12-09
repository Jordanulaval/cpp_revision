### Gestion des Erreurs et Exceptions en C++ : Explications Complètes avec Exemples

---

### **1. Qu'est-ce qu'une exception en C++ ?**

Une exception est un mécanisme utilisé pour **signaler et gérer les erreurs** dans un programme C++. Au lieu de gérer chaque erreur immédiatement dans le code, on peut "lancer" une exception et transférer le contrôle à une autre partie du programme, qui décidera comment gérer cette erreur.

---

### **2. Pourquoi utiliser des exceptions ?**

1. Permet de **séparer le code normal** du code de gestion des erreurs.
2. Gère des erreurs complexes qui peuvent survenir **à différents niveaux** dans un programme.
3. Offre un **transfert de contrôle** clair et structuré lorsqu'une erreur est détectée.

---

### **3. Les blocs `try`, `catch` et `throw`**

- **`throw`** : Permet de lancer une exception lorsqu'une erreur est détectée.
- **`try`** : Enclôt le code susceptible de lancer une exception.
- **`catch`** : Capture et gère l'exception.

#### Exemple de base :
```c++
#include <iostream>
#include <stdexcept> // Pour les exceptions standard

double divise(int numerateur, int denominateur) {
    if (denominateur == 0) {
        throw std::invalid_argument("Division par zéro !");
    }
    return static_cast<double>(numerateur) / denominateur;
}

int main() {
    try {
        std::cout << "Résultat : " << divise(10, 0) << std::endl; // Lancer une exception
    } catch (const std::invalid_argument& e) {
        std::cerr << "Erreur : " << e.what() << std::endl; // Gestion de l'exception
    }
    return 0;
}
```

**Sortie :**
```
Erreur : Division par zéro !
```

---

### **4. Types d'exceptions en C++**

#### **4.1. Hiérarchie des exceptions standard**

Les exceptions standard sont définies dans `<stdexcept>` et suivent une hiérarchie claire :

| Classe d'Exception       | Description                              |
|--------------------------|------------------------------------------|
| `std::exception`         | Classe de base pour toutes les exceptions. |
| `std::logic_error`       | Erreurs liées à une logique incorrecte (compile-time). |
| `std::runtime_error`     | Erreurs détectées à l'exécution.         |
| `std::invalid_argument`  | Argument invalide dans une fonction.     |
| `std::out_of_range`      | Accès en dehors des limites autorisées.  |
| `std::overflow_error`    | Débordement arithmétique.               |
| `std::underflow_error`   | Sous-débordement arithmétique.          |

#### Exemple :
```c++
#include <iostream>
#include <stdexcept>

void verifierTaille(int taille) {
    if (taille < 0) {
        throw std::out_of_range("Taille négative non autorisée !");
    }
}

int main() {
    try {
        verifierTaille(-5);
    } catch (const std::out_of_range& e) {
        std::cerr << "Exception attrapée : " << e.what() << std::endl;
    }
    return 0;
}
```

**Sortie :**
```
Exception attrapée : Taille négative non autorisée !
```

---

### **5. Gestion de plusieurs exceptions**

On peut gérer plusieurs exceptions en combinant plusieurs blocs `catch`.

#### Exemple :
```c++
#include <iostream>
#include <stdexcept>

int main() {
    try {
        throw std::overflow_error("Débordement détecté !");
    } catch (const std::overflow_error& e) {
        std::cerr << "Overflow : " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime : " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Exception inconnue !" << std::endl;
    }
    return 0;
}
```

---

### **6. Attraper toutes les exceptions**

Pour attraper n'importe quel type d'exception, utilisez `catch (...)`.

#### Exemple :
```c++
#include <iostream>

int main() {
    try {
        throw 42; // Lance une exception non-standard (entier)
    } catch (...) {
        std::cerr << "Une exception a été levée." << std::endl;
    }
    return 0;
}
```

---

### **7. Relancer une exception**

Dans un bloc `catch`, on peut relancer une exception pour qu'elle soit gérée ailleurs.

#### Exemple :
```c++
#include <iostream>

void fonction() {
    try {
        throw std::runtime_error("Erreur détectée !");
    } catch (...) {
        std::cerr << "Relance de l'exception..." << std::endl;
        throw; // Relancer l'exception
    }
}

int main() {
    try {
        fonction();
    } catch (const std::exception& e) {
        std::cerr << "Exception attrapée : " << e.what() << std::endl;
    }
    return 0;
}
```

---

### **8. Gestion des ressources et exceptions**

#### **Problème des fuites de mémoire**
Lorsqu'une exception est levée, les objets alloués dynamiquement peuvent ne pas être libérés.

```c++
#include <iostream>

int main() {
    int* p = new int(10); // Allocation dynamique
    try {
        throw std::runtime_error("Erreur !");
    } catch (...) {
        // L'exception est gérée, mais la mémoire n'est pas libérée.
    }
    return 0; // Fuite mémoire !
}
```

---

#### **Solution : RAII avec `std::unique_ptr`**

Utilisez des **pointeurs intelligents** pour gérer automatiquement la mémoire.

```c++
#include <iostream>
#include <memory>

int main() {
    auto p = std::make_unique<int>(10); // Mémoire gérée automatiquement
    try {
        throw std::runtime_error("Erreur !");
    } catch (...) {
        std::cerr << "Exception attrapée." << std::endl;
    }
    return 0; // Pas de fuite mémoire
}
```

---

### **9. Exceptions et pile d'appel**

Quand une exception est levée, tous les objets situés entre `throw` et `catch` sur la pile d'appel sont détruits grâce à leurs destructeurs.

#### Exemple :
```c++
#include <iostream>

class Ressource {
public:
    Ressource() { std::cout << "Ressource acquise." << std::endl; }
    ~Ressource() { std::cout << "Ressource libérée." << std::endl; }
};

void fonction() {
    Ressource r;
    throw std::runtime_error("Erreur !");
}

int main() {
    try {
        fonction();
    } catch (const std::exception& e) {
        std::cerr << "Exception : " << e.what() << std::endl;
    }
    return 0;
}
```

**Sortie :**
```
Ressource acquise.
Ressource libérée.
Exception : Erreur !
```

---

### **Résumé**

1. **Exceptions en C++** :
    - Mécanisme structuré pour gérer les erreurs.
    - Utilisez `throw`, `try`, et `catch`.

2. **Types d'exceptions** :
    - Standard (`std::exception`, `std::logic_error`, etc.).
    - Personnalisées (héritant de `std::exception`).

3. **Meilleures pratiques** :
    - **Relance** une exception si elle n'est pas gérable localement.
    - Évitez les fuites de mémoire en utilisant des **pointeurs intelligents**.
    - Gérer proprement les ressources avec RAII (Resource Acquisition Is Initialization).

4. **Atouts des exceptions** :
    - Réduit le code de gestion des erreurs dans les blocs principaux.
    - Offre une gestion hiérarchique et modulaire des erreurs.

5. **Problèmes potentiels** :
    - Complexité ajoutée au code.
    - Peut ralentir légèrement l'exécution.

Avec ces bases, vous pouvez écrire des programmes robustes et sûrs tout en gérant les erreurs de manière élégante.