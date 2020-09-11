#include "evenement.hpp"
#include "partition.hpp"
#include <algorithm>

#include <iostream>

struct Compare {
  bool operator() (const std::vector<Evenement> & a, std::vector<Evenement> & b) const {
    return a.back().fin() > b.back().fin();
  }
};

// Cette fonction prend en entree un vecteur d'evenements et retourne une partition de ces evenemnts.
// Chaque vecteur dans la partition correspond aux evenements auquels assiste un clown. L'ordre des
// evenements dans les vecteurs n'a aucune importance.
void partition(const std::vector<Evenement>& evenements,
	       std::vector<std::vector<Evenement> >& partition) {
	if (evenements.empty()) {
		return;
	}

	// Copie des événements dans un nouveau vecteur
	std::vector<Evenement> v(evenements); // Theta(n)

	// Tri des événements contenus dans le nouveau vecteur en ordre croissant de valeur de début
  std::stable_sort(v.begin(), v.end(), ComparateurDebut()); // O(n log n)

  // Création d'un monceau contenant les partitions
  std::vector<std::vector<Evenement>> q;
  std::make_heap(q.begin(), q.end(), Compare()); // O(3 * (end - start))

  // Création d'une partition contenant le premier événement et insertion dans le monceau
  std::vector<Evenement> first(1, Evenement(v.front()));
  q.push_back(first);
  std::push_heap(q.begin(), q.end(), Compare()); // O(log (end - start))

  // Pour tous les événements non traités
  for (unsigned long j = 1; j < v.size(); j++) {
    // La partition dont le dernier élément possède la plus petite valeur de fin est sur le dessus
    auto front = q.front().back();

    // Si l'événement n'est pas en conflit avec le dernier élément de la partition du dessus
    if (v.at(j).debut() >= front.fin()) {
      // On insère à la fin de la partition
      q.at(0).push_back(v.at(j));
      std::make_heap(q.begin(), q.end(), Compare()); // O(3 * (end - start))
    }
    else {
      // On crée une nouvelle partition
      std::vector<Evenement> event(1, v.at(j));
      q.push_back(event);
      std::push_heap(q.begin(), q.end(), Compare()); // O(log (end - start))
    }
  }

  // Theta(n)
  for (auto const & p : q)
    partition.push_back(p);
}
