/**
 * \file ContratException.cpp
 * \brief Implémentation des classes pour la gestion des exceptions de contrat.
 * \author Jordan Mathieu
 * \version 1.0
 * \date 26 novembre 2024
 *
 * Ce fichier contient l'implémentation des méthodes des classes d'exceptions
 * utilisées pour gérer les violations de contrat dans le programme.
 */

#include "ContratException.h"
#include <sstream>

using namespace std;

/**
 * \brief Constructeur de la classe ContratException.
 *
 * Initialise une exception avec les détails fournis : fichier, ligne, expression, et message.
 *
 * \param[in] p_fichier Nom du fichier source où l'exception est levée.
 * \param[in] p_ligne Numéro de la ligne dans le fichier source.
 * \param[in] p_expression Expression qui a échoué.
 * \param[in] p_msg Message décrivant l'erreur.
 */
ContratException::ContratException(const std::string& p_fichier, unsigned int p_ligne, const std::string& p_expression, const std::string& p_msg)
    : logic_error(p_msg), m_fichier(p_fichier), m_ligne(p_ligne), m_expression(p_expression)
{
}

/**
 * \brief Retourne une description détaillée de l'exception.
 *
 * La description inclut le message d'erreur, le fichier source, la ligne, et l'expression ayant échoué.
 *
 * \return Une chaîne contenant les détails de l'exception.
 */
std::string ContratException::reqTexteException() const
{
    ostringstream os;
    os << "Message    : " << what() << endl;
    os << "Fichier    : " << m_fichier << endl;
    os << "Ligne      : " << m_ligne << endl;
    os << "Expression : " << m_expression << endl;

    return os.str();
}

/**
 * \brief Constructeur de la classe AssertionException.
 *
 * Initialise une exception pour les erreurs d'assertion.
 *
 * \param[in] p_fichier Nom du fichier source où l'exception est levée.
 * \param[in] p_ligne Numéro de la ligne dans le fichier source.
 * \param[in] p_expression Expression qui a échoué.
 */
AssertionException::AssertionException(const std::string& p_fichier, unsigned int p_ligne, const std::string& p_expression)
    : ContratException(p_fichier, p_ligne, p_expression, "ERREUR ASSERTION")
{
}

/**
 * \brief Constructeur de la classe PreconditionException.
 *
 * Initialise une exception pour les erreurs de précondition.
 *
 * \param[in] p_fichier Nom du fichier source où l'exception est levée.
 * \param[in] p_ligne Numéro de la ligne dans le fichier source.
 * \param[in] p_expression Expression qui a échoué.
 */
PreconditionException::PreconditionException(const std::string& p_fichier, unsigned int p_ligne, const std::string& p_expression)
    : ContratException(p_fichier, p_ligne, p_expression, "ERREUR PRECONDITION")
{
}

/**
 * \brief Constructeur de la classe PostconditionException.
 *
 * Initialise une exception pour les erreurs de postcondition.
 *
 * \param[in] p_fichier Nom du fichier source où l'exception est levée.
 * \param[in] p_ligne Numéro de la ligne dans le fichier source.
 * \param[in] p_expression Expression qui a échoué.
 */
PostconditionException::PostconditionException(const std::string& p_fichier, unsigned int p_ligne, const std::string& p_expression)
    : ContratException(p_fichier, p_ligne, p_expression, "ERREUR POSTCONDITION")
{
}

/**
 * \brief Constructeur de la classe InvariantException.
 *
 * Initialise une exception pour les erreurs d'invariant.
 *
 * \param[in] p_fichier Nom du fichier source où l'exception est levée.
 * \param[in] p_ligne Numéro de la ligne dans le fichier source.
 * \param[in] p_expression Expression qui a échoué.
 */
InvariantException::InvariantException(const std::string& p_fichier, unsigned int p_ligne, const std::string& p_expression)
    : ContratException(p_fichier, p_ligne, p_expression, "ERREUR INVARIANT")
{
}