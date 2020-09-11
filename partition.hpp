#ifndef PARTITION
#define PARTITION

#include <vector>
#include <evenement.hpp>

// Cette fonction prend en entree un vecteur d'evenements et retourne une partition de ces evenemnts.
// Chaque vecteur dans la partition correspond aux evenements auquels assiste un clown. L'ordre des
// evenements dans les vecteurs n'a aucune importance.
void partition(const std::vector<Evenement>& evenements,
	       std::vector<std::vector<Evenement> >& partition);

#endif
