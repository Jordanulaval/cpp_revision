/**
 * \file ContratExceptions.h
 * \brief Déclaration des classes pour la gestion des exceptions de contrat.
 * \author Jordan Mathieu
 * \version 1.0
 * \date 26 novembre 2024
 *
 * Ce fichier contient les déclarations des classes d'exceptions utilisées pour
 * gérer les violations de contrat (assertions, préconditions, postconditions, invariants).
 */

#ifndef CONTRATEXCEPTIONS_H
#define CONTRATEXCEPTIONS_H

#include <stdexcept>
#include <string>
#include <iostream>

/**
 * \class ContratException
 * \brief Classe de base pour les exceptions liées aux violations de contrat.
 *
 * Cette classe abstraite permet de gérer les viSolations de contrat en fournissant
 * des informations détaillées telles que le fichier source, la ligne de l'erreur, l'expression échouée,
 * et un message d'erreur explicite.
 */
class ContratException : public std::logic_error
{
public:
    /**
     * \brief Constructeur de la classe ContratException.
     *
     * \param[in] p_fichier Nom du fichier source où l'exception a été levée.
     * \param[in] p_ligne Numéro de la ligne dans le fichier source.
     * \param[in] p_expression Expression logique qui a échoué.
     * \param[in] p_message Message personnalisé décrivant l'erreur.
     */
    ContratException(const std::string& p_fichier, unsigned int p_ligne,
                     const std::string& p_expression, const std::string& p_message);

    /**
     * \brief Destructeur par défaut.
     */
    ~ContratException() noexcept override = default;

    /**
     * \brief Retourne une description détaillée de l'exception.
     *
     * La description inclut le message d'erreur, le fichier, la ligne et l'expression concernée.
     *
     * \return Une chaîne contenant les détails de l'exception.
     */
    std::string reqTexteException() const;

private:
    std::string m_expression; /**< Expression ayant échoué. */
    std::string m_fichier;    /**< Nom du fichier source où l'erreur est survenue. */
    unsigned int m_ligne;     /**< Ligne dans le fichier source où l'erreur a été levée. */
};

/**
 * \class AssertionException
 * \brief Classe pour la gestion des erreurs d'assertion.
 *
 * Cette exception est levée lorsqu'une assertion échoue.
 */
class AssertionException : public ContratException
{
public:
    /**
     * \brief Constructeur de la classe AssertionException.
     *
     * \param[in] p_fichier Nom du fichier source.
     * \param[in] p_ligne Ligne où l'exception a été levée.
     * \param[in] p_expression Expression logique qui a échoué.
     */
    AssertionException(const std::string& p_fichier, unsigned int p_ligne, const std::string& p_expression);
};

/**
 * \class PreconditionException
 * \brief Classe pour la gestion des erreurs de précondition.
 *
 * Cette exception est levée lorsqu'une précondition échoue.
 */
class PreconditionException : public ContratException
{
public:
    /**
     * \brief Constructeur de la classe PreconditionException.
     *
     * \param[in] p_fichier Nom du fichier source.
     * \param[in] p_ligne Ligne où l'exception a été levée.
     * \param[in] p_expression Expression logique qui a échoué.
     */
    PreconditionException(const std::string& p_fichier, unsigned int p_ligne, const std::string& p_expression);
};

/**
 * \class PostconditionException
 * \brief Classe pour la gestion des erreurs de postcondition.
 *
 * Cette exception est levée lorsqu'une postcondition échoue.
 */
class PostconditionException : public ContratException
{
public:
    /**
     * \brief Constructeur de la classe PostconditionException.
     *
     * \param[in] p_fichier Nom du fichier source.
     * \param[in] p_ligne Ligne où l'exception a été levée.
     * \param[in] p_expression Expression logique qui a échoué.
     */
    PostconditionException(const std::string& p_fichier, unsigned int p_ligne, const std::string& p_expression);
};

/**
 * \class InvariantException
 * \brief Classe pour la gestion des erreurs d'invariant.
 *
 * Cette exception est levée lorsqu'un invariant de classe échoue.
 */
class InvariantException : public ContratException
{
public:
    /**
     * \brief Constructeur de la classe InvariantException.
     *
     * \param[in] p_fichier Nom du fichier source.
     * \param[in] p_ligne Ligne où l'exception a été levée.
     * \param[in] p_expression Expression logique qui a échoué.
     */
    InvariantException(const std::string& p_fichier, unsigned int p_ligne, const std::string& p_expression);
};

// --- Définition des macros de contrôle de la théorie du contrat

#if !defined(NDEBUG)
// --- Mode debug

#  define INVARIANTS() \
verifieInvariant()

#  define ASSERTION(f)     \
if (!(f)) throw AssertionException(__FILE__,__LINE__, #f);
#  define PRECONDITION(f)  \
if (!(f)) throw PreconditionException(__FILE__, __LINE__, #f);
#  define POSTCONDITION(f) \
if (!(f)) throw PostconditionException(__FILE__, __LINE__, #f);
#  define INVARIANT(f)   \
if (!(f)) throw InvariantException(__FILE__,__LINE__, #f);

// --- LE MODE RELEASE
#else

#  define PRECONDITION(f);
#  define POSTCONDITION(f);
#  define INVARIANTS();
#  define INVARIANT(f);
#  define ASSERTION(f);



#endif  // --- if !defined (NDEBUG)
#endif //CONTRATEXCEPTIONS_H