#include "camera.hpp"
#include "pixelmap.hpp"
#include "rayon.hpp"
#include "Scene.hpp"
#include <stdio.h>
#include "omp.h"
#include "time.h"

void Camera::Haut(const glm::vec3 & h) {

	haut = h - (dir * (dir * h));
	
	
	if (glm::length(haut) != 0.0)
		haut = glm::normalize(haut);
	
}

void Camera::Calculer_image(Pixelmap & pm, Scene &sc, int complexite) const {
	glm::vec3 foyer; // Foyer optique de la camera
	glm::vec3 droite; // Vecteur partant sur la droite dans le plan de l'ecran
	float dx, dy; // dimension des macro-pixels
	int x, y; // Position dans l'image du pixel en cours de calcul
	glm::vec3 hg; // Position du pixel au centre du premier macro-pixel de l'ecran (en haut a gauche)
	glm::vec3 pt; // Position de l'intersection entre le rayon a lancer et l'ecran
	Rayon ray; // Rayon a lancer
	glm::vec3 vect; // Vecteur directeur du rayon a lancer
	int index; // Indice du pixel traite

	// On calcule la position du foyer de la camera
	foyer = centre - (dir * dist);
	
	//std::cout << "centre : " << haut.x << " " << haut.y <<" " << haut.z << std::endl; 
	// On calcule le vecteur unitaire "droite" du plan
	droite = glm::cross(dir,haut);
	

	// On calcule le deltaX et le deltaY
	dx = largeur / pm.Largeur();
	dy = hauteur / pm.Hauteur();

	// On calcule la position du premier point de l'ecran que l'on calculera
	hg = centre + (droite * ((dx / 2) - (largeur / 2))) + (haut * ((hauteur / 2) - (dy / 2)));

	// Pour chaque pixel de l'image a calculer
	index = 0;
	omp_set_num_threads(4);
	omp_set_nested(true);
	//coef antialiassage
	float AA = 5.0f;
	const clock_t begin = clock();
	omp_lock_t loquet;
	omp_init_lock(&loquet);

	for (y = 0; y < pm.Hauteur(); y++) {
//#pragma omp parallel for private (ray, vect, pt, x)
		for (x = 0; x < pm.Largeur(); x++) {
			int compteur = x + y*pm.Largeur();
			// On calcule la position dans l'espace de ce point
			
			/*pt = hg + (droite * (dx * x)) - (haut * (dy * y));
			// On prepare le rayon qui part du foyer et qui passe par ce point
			ray.Orig(pt);
			vect = pt - foyer;
			vect = glm::normalize(vect);
			ray.Vect(vect);

			// Et on enregistre la couleur du rayon dans l'image
			glm::vec3 rayz = ray.Lancer(sc, complexite);
			//glm::vec3 rayz = ray.LancerRayMarching(sc);
			//#pragma omp critical
			pm.Map(compteur, rayz);*/

			/////////////////////////////////////////////////////////ANTI-ALIASING////////////////////////////////////////////////////////
			glm::vec3 accCouleur;
			for (int i = 0; i < AA; i++){
				for (int j = 0; j < AA; j++){
					pt = hg + (droite * (dx * x) + (dx/(AA*AA)*i) - (haut * (dy * y) + (dy/(AA*AA)*j)));
					ray.Orig(pt);
					vect = pt - foyer;
					vect = glm::normalize(vect);
					ray.Vect(vect);
					accCouleur += ray.Lancer(sc, complexite);
				}
			}
			
			accCouleur = accCouleur/(AA*AA);
			pm.Map(x + y*pm.Largeur(), accCouleur);
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
		//omp_destroy_lock(&loquet);
		std::cout << "Ligne " << y << std::endl; 
	}
	const clock_t end = clock();
	float elapsed = (end - begin) / CLOCKS_PER_SEC;
	std::cout << "Time : " << elapsed << "s" << std::endl;
}
