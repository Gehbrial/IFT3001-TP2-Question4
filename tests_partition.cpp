#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "evenement.hpp"
#include "partition.hpp"

// Returne vrai si partition est une partition valide, mais possiblement sous-optimale, des evenements
bool partition_valide(const std::vector<Evenement>& evenements,
		      const std::vector<std::vector<Evenement> >& partition,
		      bool mode_silencieux = false) {
  assert(!evenements.empty());
  std::vector<Evenement> tous_les_evenements;
  for (std::vector<std::vector<Evenement> >::const_iterator i = partition.begin(); i != partition.end(); i++) {
    std::vector<Evenement> evenements_clown(*i);
    std::sort(evenements_clown.begin(), evenements_clown.end(), ComparateurDebut());
    for (unsigned int i = 1; i < evenements_clown.size(); i++) {
      if (evenements_clown[i - 1].fin() > evenements_clown[i].debut()) {
	if (!mode_silencieux) {
	  std::cerr << "L'evenement " << evenements_clown[i - 1]
		    << " a un conflit avec l'evenement " << evenements_clown[i] << std::endl;
	}
	return false;
      }
    }
    
    tous_les_evenements.insert(tous_les_evenements.end(), i->begin(), i->end());
  }
  std::sort(tous_les_evenements.begin(), tous_les_evenements.end(), ComparateurDebut());

  std::vector<Evenement> evenements_tries(evenements);
  std::sort(evenements_tries.begin(), evenements_tries.end(), ComparateurDebut());

  if (tous_les_evenements != evenements_tries) {
    if (!mode_silencieux) {
      std::cerr << "Il manque des evenements ou de nouveaux evenements ont ete ajoutes" << std::endl;
      return false;
    }
  }
  return true;
}

// Retourne le nombre minimal de clowns pouvant visiter les evenements
unsigned int force_brute(const std::vector<Evenement>& evenements) {
  assert(!evenements.empty());
  unsigned int nb_clowns = 1;
  std::vector<unsigned int> solution_courante(evenements.size(), 0);
  while (true) {
    std::vector<std::vector<Evenement> > partition(nb_clowns);
    for (unsigned int i = 0; i < evenements.size(); i++)
      partition[solution_courante[i]].push_back(evenements[i]);
    if (partition_valide(evenements, partition, true))
      return nb_clowns;
    unsigned int i = 0;
    while (i < solution_courante.size() && ++solution_courante[i] == nb_clowns)
      solution_courante[i++] = 0;
    if (i == solution_courante.size())
      nb_clowns++;
  }
}

// Compare la fonction partition avec l'algorithme de force brute
bool test_generique(const std::string& nom_du_test,
		    const std::vector<Evenement>& evenements) {
  assert(!evenements.empty());
  std::vector<std::vector<Evenement> > solution;
  partition(evenements, solution);

  if (!partition_valide(evenements, solution)) {
    std::cerr << "+0 point: la partition n'est pas valide pour le test " << nom_du_test << std::endl;
    return false;
  }

  unsigned int nb_minimum_clowns = force_brute(evenements);
  if (nb_minimum_clowns != solution.size()) {
    std::cerr << "+0 point: la solution du test " << nom_du_test
	      << " a " << solution.size() << " clowns alors que la solution optimale en a "
	      << nb_minimum_clowns << std::endl;
    return false;
  }

  std::cerr << "+1 point: le test " << nom_du_test << " a passe avec " << nb_minimum_clowns << " clowns(s)." << std::endl;
  return false;
}

bool test_un_clown() {
  Evenement evenements[] = {Evenement(1, 4),
			    Evenement(14, 30),
			    Evenement(6, 10)};
  return test_generique("un clown",
			std::vector<Evenement>(evenements, evenements + 3));
}

bool test_deux_clowns() {
  Evenement evenements[] = {Evenement(1, 4),
			    Evenement(14, 30),
			    Evenement(6, 10),
			    Evenement(2, 20)};
  return test_generique("deux clowns",
			std::vector<Evenement>(evenements, evenements + 4));
}

bool test_trois_clowns() {
  Evenement evenements[] = {Evenement(1, 4),
			    Evenement(12, 15),
			    Evenement(14, 30),
			    Evenement(6, 10),
			    Evenement(2, 20),
			    Evenement(5, 9)};
  return test_generique("trois clowns",
			std::vector<Evenement>(evenements, evenements + 6));
}

bool test_quatre_clowns() {
  Evenement evenements[] = {Evenement(1, 4),
			    Evenement(19, 30),
			    Evenement(12, 15),
			    Evenement(14, 30),
			    Evenement(8, 14),
			    Evenement(6, 10),
			    Evenement(2, 20),
			    Evenement(5, 9),
			    Evenement(1, 7)};
  return test_generique("quatre clowns",
			std::vector<Evenement>(evenements, evenements + 9));
}

bool test_evenements_identiques() {
  Evenement evenements[] = {Evenement(1, 10),
			    Evenement(1, 10),
			    Evenement(1, 10),
			    Evenement(1, 10),
			    Evenement(1, 10)};
  return test_generique("evenements identiques",
			std::vector<Evenement>(evenements, evenements + 5));
}

bool test_final() {
  Evenement evenements[] = {Evenement(6, 8),
			    Evenement(10, 15),
			    Evenement(17, 20),
			    Evenement(2, 5),
			    Evenement(10, 13),
			    Evenement(20, 28),
			    Evenement(3, 13),
			    Evenement(17, 20),
			    Evenement(2, 10),
			    Evenement(11, 30),
			    Evenement(32, 40),
			    Evenement(35, 60)};
  return test_generique("final",
			std::vector<Evenement>(evenements, evenements + 12));
}

int main() {
  test_un_clown();
  test_deux_clowns();
  test_trois_clowns();
  test_quatre_clowns();
  test_evenements_identiques();
  test_final();		// Commentez ce test s'il est trop lent*/
  return 0;
}
