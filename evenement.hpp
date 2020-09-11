#ifndef EVENEMENT
#define EVENEMENT

#include <assert.h>
#include <iostream>

class Evenement {
private:
  unsigned int m_debut;
  unsigned int m_fin;
public:
  Evenement(unsigned int debut, unsigned int fin)
    : m_debut(debut),
      m_fin(fin)
  {
    assert(debut < fin);
  }

  Evenement(const Evenement& evenement)
    : m_debut(evenement.m_debut),
      m_fin(evenement.m_fin)
  {}

  unsigned int debut() const {
    return m_debut;
  }

  unsigned int fin() const {
    return m_fin;
  }

  bool operator==(const Evenement& e) const {
    return e.m_debut == m_debut && e.m_fin == m_fin;
  }

  friend std::ostream& operator<<(std::ostream& os, const Evenement& e) {
    return os << "[" << e.debut() << ", " << e.fin() << ")";
  }
};

// Comparateurs. Utile pour les fonctions de tri de la STL

class ComparateurFin {
public:
  ComparateurFin() {}
  bool operator() (const Evenement& a, const Evenement& b) {
    return ((a.fin() == b.fin()) && (a.debut() < b.debut())) || a.fin() < b.fin();
  }
};

class ComparateurDebut {
public:
  ComparateurDebut() {}
  bool operator() (const Evenement& a, const Evenement& b) {
    return ((a.debut() == b.debut()) && (a.fin() < b.fin())) || (a.debut() < b.debut());
  }
};


#endif
