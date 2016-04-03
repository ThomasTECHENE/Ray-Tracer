#include <stdio.h>
#include "camera.hpp"
#include "pixelmap.hpp"
#include "rayon.hpp"
#include "Objet3D.hpp"
#include "plan.hpp"
#include "Sphere.hpp"
#include "Lumiere.hpp"
#include "Material.hpp"
#include "triangle.hpp"
#include "roundBoxRM.hpp"
#include "torusRM.hpp"
#include "boxRM.hpp"
#include "coneRM.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "OBJLoader.h"
#include "GeometricModel.h"
#include "GeometricModelLoader.h"

int main(void) {
	
	// Une image Pixelmap
	Pixelmap pixmap(900*2, 670*2);
	//Pixelmap pixmap(400, 300);
	// Une image Bitmap
	Image bitmap;

	//Définitions des matériaux
	Material DiffuseMirrorMaterial;
	DiffuseMirrorMaterial.setMaterial(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), 100, 1.1, 0.0, 0.0);
	Material MirrorMaterial;
	MirrorMaterial.setMaterial(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), 100, 1.0, 0.0, 0.0);
	Material CielMaterial;
	CielMaterial.setMaterial(glm::vec3(0.4, 0.7, 0.6), glm::vec3(0.4, 0.7, 0.6), glm::vec3(1.0, 1.0, 1.0), 100, 0.0, 0.0, 0.0);
	Material SkinMaterial;
	SkinMaterial.setMaterial(glm::vec3(0.6, 0.5, 0.3), glm::vec3(0.7, 0.6, 0.4), glm::vec3(1.0, 1.0, 1.0), 100, 0.0, 0.0, 0.0);
	Material RedMaterial;
	RedMaterial.setMaterial(glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), 100, 0.0, 0.0, 0.0);
	Material GreenMaterial;
	GreenMaterial.setMaterial(glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 1.0), 100, 0.0, 0.0, 0.0);
	Material RedRubberMat;
	RedRubberMat.setMaterial(glm::vec3(0.05, 0.0, 0.0), glm::vec3(0.5, 0.4, 0.4), glm::vec3(0.7, 0.04, 0.04), 10, 0.0, 0.0, 0.0);
	Material RedPlasticMat;
	RedPlasticMat.setMaterial(glm::vec3(0.0, 0.0, 0.0), glm::vec3 (0.5, 0.0, 0.0), glm::vec3(0.7, 0.6, 0.6), 32, 0.0, 0.0, 0.0);
	Material GreenRubberMat;
	GreenRubberMat.setMaterial(glm::vec3(0.0, 0.05, 0.0), glm::vec3(0.4, 0.5, 0.4), glm::vec3(0.04, 0.7, 0.04), 10, 0.0, 0.0, 0.0);
	Material BlueMaterial;
	BlueMaterial.setMaterial(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 100, 0.0, 0.0, 0.0);
	Material GlassMat;
	GlassMat.setMaterial(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1.0, 1.0, 1.0), 100, 0.0, 1.4, 1.0);
	Material WhiteMat;
	WhiteMat.setMaterial(glm::vec3(1.0, 0.89, 0.71), glm::vec3(1.0, 0.89, 0.71), glm::vec3(1.0, 1.0, 1.0), 100, 0.0, 0.0, 0.0);
	Material WhiteShinyMat;
	WhiteShinyMat.setMaterial(glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 200, 0.0, 0.0, 0.0);
	Material EmeraldMat;
	EmeraldMat.setMaterial(glm::vec3(0.0215, 0.1745, 0.0215), glm::vec3(0.07568, 0.61424, 0.07568), glm::vec3(0.633, 0.727811, 0.633), 76.8, 0.2, 0.0, 0.0);
	Material ObsidianMat;
	ObsidianMat.setMaterial(glm::vec3(0.05375, 0.05, 0.06625), glm::vec3(0.18275, 0.17, 0.22525), glm::vec3(0.332741, 0.328634, 0.346435), 38.4, 0.2, 0.0, 0.0);
	Material PearlMat;
	PearlMat.setMaterial(glm::vec3(0.25, 0.20725, 0.20725), glm::vec3(1, 0.829, 0.829), glm::vec3(0.296648, 0.296648, 0.296648), 11.264, 0.0, 0.0, 0.0);
	Material GoldMat;
	GoldMat.setMaterial(glm::vec3(0.24725, 0.1995, 0.0745), glm::vec3(0.75164, 0.60648, 0.22648), glm::vec3(0.628281, 0.555802, 0.366065), 51.2, 0.5, 0.0, 0.0);
	Material ChromeMat;
	ChromeMat.setMaterial(glm::vec3(0.25, 0.25, 0.25), glm::vec3(0.4, 0.4, 0.4), glm::vec3(0.774597, 0.774597, 0.774597), 76.8, 0.5, 0.0, 0.0);
	Material BronzeMat;
	BronzeMat.setMaterial(glm::vec3(0.2125, 0.1275, 0.054), glm::vec3(0.714, 0.4284, 0.18144), glm::vec3(0.393548, 0.271906, 0.166721), 25.6, 0.5, 0.0, 0.0);
	Material RubyMat;
	RubyMat.setMaterial(glm::vec3(0.1745, 0.01175, 0.01175), glm::vec3(0.61424, 0.04136, 0.04136), glm::vec3(0.727811, 0.626959, 0.626959), 76.8, 0.2, 0.0, 0.0);
	Material TurquoiseMat;
	TurquoiseMat.setMaterial(glm::vec3(0.1, 0.18725, 0.1745), glm::vec3(0.396, 0.74151, 0.69102), glm::vec3(0.297254, 0.30829, 0.306678), 12.8, 0.2, 0.0, 0.0);
	Material SilverMat;
	SilverMat.setMaterial(glm::vec3(0.19225, 0.19225, 0.19225), glm::vec3(0.50754, 0.50754, 0.50754), glm::vec3(0.508273, 0.508273, 0.508273), 51.2, 0.2, 0.0, 0.0);
	//scene
	Scene scene;
	//Initialisation des sources de lumières
	scene.light.setPosition(glm::vec3(0.0, 27.0, 110.0)); // position de la premiere source de lumiere
	scene.light2.setPosition(glm::vec3(0.0, 10.0, 12.0)); // position de la seconde source de lumiere
	
	// Initialisation des objets==============================

	//Modèle objet 3D
	//construction du modele
	//GeometricModel modele = GeometricModel("C:/Users/Thomas/Desktop/Raycasting/Release/teapot.obj", true);
	//tableau de faces
	//int nbF = modele.nb_faces;
	//Triangle tabTriangle[5000];
	/*float Tx = 1.0, Ty = 3.0, Tz = 30.0;
	//construction des triangles + ajout dans le tableau
	glm::mat4 translation = glm::mat4(1.0, 0.0, 0.0, Tx,
							0.0, 1.0, 0.0, Ty,
							0.0, 0.0, 1.0, Tz,
							0.0, 0.0, 0.0, 1.0);

	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(1.0, 3.0, 30.0));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(5.0, 5.0, 5.0));*/

	/*for (int i = 0; i < modele.nb_faces-1 ; i++){
		
		glm::vec3 sommet1 = glm::vec3(modele.listVertex[modele.listFaces[i].s1])*0.1f + glm::vec3(1.0, 3.0, 95.0);
		glm::vec3 sommet2 = glm::vec3(modele.listVertex[modele.listFaces[i].s2])*0.1f + glm::vec3(1.0, 3.0, 95.0);
		glm::vec3 sommet3 = glm::vec3(modele.listVertex[modele.listFaces[i].s3])*0.1f + glm::vec3(1.0, 3.0, 95.0);

		
		Triangle T = Triangle(sommet1, sommet2, sommet3);
		//Triangle T = Triangle(modele.listVertex[modele.listFaces[i].s1], modele.listVertex[modele.listFaces[i].s2], modele.listVertex[modele.listFaces[i].s3]);
		T.material = &RedMaterial;
		tabTriangle[i] = T;*/
		//ajout des triangles a la liste des objets de la scene
		//scene.ajouterObjet(&tabTriangle[i]);
	//}
	
	//Définiton des objets de la scène
	Plan p = Plan(glm::vec3(-1.0, 0.0, 0.0), 30); //mur gauche
	p.material = &GreenRubberMat;
	Plan p2 = Plan(glm::vec3(0.0, 0.0, -1.0), 170);//mur fond
	p2.material = &PearlMat;
	Plan p3 = Plan(glm::vec3(1.0, 0.0, 0.0), 30);//mur droite
	p3.material = &RedPlasticMat;
	Plan p4 = Plan(glm::vec3(0.0, 1.0, 0.0), 18);//sol
	p4.material = &PearlMat;
	Plan p5 = Plan(glm::vec3(0.0, -1.0, 0.0), 30);//plafond
	p5.material = &PearlMat;
	Plan p6 = Plan(glm::vec3(0.0, 0.0, 1.0), 30);//plan arriere
	p6.material = &PearlMat;
	Plan p7 = Plan(glm::vec3(0.0, -1.5, -1.5), 270);//planincliné fond haut
	p7.material = &MirrorMaterial;
	//Plan p8 = Plan(glm::vec3(0.0, 1.0, -1.0), 270);//planincliné fond haut
	//p8.material = &MirrorMaterial;

	Sphere s1 = Sphere(glm::vec3(-21.0, 0.0, 130.0), 3.0);
	s1.material = &GoldMat;
	Sphere s2 = Sphere(glm::vec3(-15.0, 0.0, 130.0), 3.0); 
	s2.material = &ChromeMat;
	Sphere s21 = Sphere(glm::vec3(-9.0, 0.0, 130.0), 3.0); // sphere gauche
	s21.material = &BronzeMat;
	Sphere s22 = Sphere(glm::vec3(9.0, 0.0, 130.0), 3.0); // sphere fond
	s22.material = &RubyMat;
	Sphere s23 = Sphere(glm::vec3(15.0, 0.0, 130.0), 3.0); // sphere face
	s23.material = &TurquoiseMat;
	Sphere s24 = Sphere(glm::vec3(21.0, 0.0, 130.0), 3.0);
	s24.material = &ObsidianMat;


	Sphere s3 = Sphere(glm::vec3(-10.0, 12.0, 100.0), 4.0);
	s3.material = &SkinMaterial;
	Sphere s4 = Sphere(glm::vec3(20.0, 0.0, 100.0), 8.0);
	s4.material = &PearlMat;

	Triangle t1 = Triangle(glm::vec3(0.0, -5.0, 95.0), glm::vec3(-14.0, 5.0, 95.0), glm::vec3(17.0, 0.0, 90.0));
	t1.material = &PearlMat;

	//grille de sphere
	Sphere g0 = Sphere(glm::vec3(-30.0, -10.0, 70.0), 3.0);
	g0.material = &PearlMat;
	Sphere g1 = Sphere(glm::vec3(30.0, -10.0, 110.0), 3.0);
	g1.material = &PearlMat;
	Sphere g2 = Sphere(glm::vec3(-30.0, -10.0, 110.0), 3.0);
	g2.material = &PearlMat;
	Sphere g3 = Sphere(glm::vec3(30.0, -10.0, 90.0), 3.0);
	g3.material = &PearlMat;

	Sphere g4 = Sphere(glm::vec3(-30.0, -10.0, 90.0), 3.0);
	g4.material = &PearlMat;
	Sphere g5 = Sphere(glm::vec3(30.0, -10.0, 130.0), 3.0);
	g5.material = &PearlMat;
	Sphere g6 = Sphere(glm::vec3(-30.0, -10.0, 130.0), 3.0);
	g6.material = &PearlMat;
	Sphere g7 = Sphere(glm::vec3(30.0, -10.0, 150.0), 3.0);
	g7.material = &PearlMat;

	Sphere g8 = Sphere(glm::vec3(-30.0, -10.0, 150.0), 3.0);
	g8.material = &PearlMat;
	Sphere g9 = Sphere(glm::vec3(30.0, -10.0, 170.0), 3.0);
	g9.material = &PearlMat;
	Sphere g10 = Sphere(glm::vec3(-30.0, -10.0, 170.0), 3.0);
	g10.material = &PearlMat;
	Sphere g11 = Sphere(glm::vec3(5.0, 14.0, 110.0), 0.5);
	g11.material = &PearlMat;

	Sphere g12 = Sphere(glm::vec3(11.0, 16.0, 110.0), 0.5);
	g12.material = &PearlMat;
	Sphere g13 = Sphere(glm::vec3(9.0, 16.0, 110.0), 0.5);
	g13.material = &PearlMat;
	Sphere g14 = Sphere(glm::vec3(7.0, 16.0, 110.0), 0.5);
	g14.material = &PearlMat;
	Sphere g15 = Sphere(glm::vec3(5.0, 16.0, 110.0), 0.5);
	g15.material = &PearlMat;

	//roundBox
	RoundBoxRM r1 = RoundBoxRM(glm::vec3(0.0, -12.0, 140.0), glm::vec3(5.0, 5.0, 0.0), 1.0);
	r1.material = &DiffuseMirrorMaterial;
	
	//Torus
	TorusRM tor1 = TorusRM(glm::vec3(-15.0, -8.0, 110.0), glm::vec2(5.0, 0.7));
	tor1.material = &ObsidianMat;
	Sphere lampe = Sphere(glm::vec3(15.0, -8.0, 110.0), 5.0f);
	lampe.material = &GlassMat;

	//Box
	BoxRM b1 = BoxRM(glm::vec3(-30.0, -35.0, 250.0), glm::vec3(15.0,15.0,15.0));
	b1.material = &DiffuseMirrorMaterial;
	//Cone
	ConeRM c1 = ConeRM(glm::vec3(0.0, -13.0, 120.0), glm::vec3(0.6, 0.8, 5.0));
	c1.material = &MirrorMaterial;

	// Ajouter les objets à la scene
	scene.ajouterObjet(&p);
	scene.ajouterObjet(&p2);
	scene.ajouterObjet(&p3);
	scene.ajouterObjet(&p4);
	scene.ajouterObjet(&p5);
	scene.ajouterObjet(&p6);
	scene.ajouterObjet(&p7);
	//scene.ajouterObjet(&p8);
	///////////////////////
	/*scene.ajouterObjet(&s1);
	scene.ajouterObjet(&s2);
	scene.ajouterObjet(&s21);
	scene.ajouterObjet(&s22);
	scene.ajouterObjet(&s23);
	scene.ajouterObjet(&s24);*/

	//scene.ajouterObjet(&s3);
	//scene.ajouterObjet(&s4);
	
	//scene.ajouterObjet(&t1);

	scene.ajouterObjet(&g0);
	scene.ajouterObjet(&g1);
	scene.ajouterObjet(&g2);
	scene.ajouterObjet(&g3);
	scene.ajouterObjet(&g4);
	scene.ajouterObjet(&g5);
	scene.ajouterObjet(&g6);
	scene.ajouterObjet(&g7);
	scene.ajouterObjet(&g8);
	scene.ajouterObjet(&g9);
	scene.ajouterObjet(&g10);
	/*scene.ajouterObjet(&g11);
	scene.ajouterObjet(&g12);
	scene.ajouterObjet(&g13);
	scene.ajouterObjet(&g14);
	scene.ajouterObjet(&g15);*/
	
	//scene.ajouterObjet(&r1);
	//scene.ajouterObjet(&b1);

	//scene.ajouterObjet(&tor1);
	scene.ajouterObjet(&lampe);
	scene.ajouterObjet(&c1);

	Sphere stest = Sphere(glm::vec3(-20.0, -10.0, 120.0), 5.0);
	stest.material = &DiffuseMirrorMaterial;
	//scene.ajouterObjet(&stest);


	// la Camera
	Camera cam;
	cam.Centre(glm::vec3(0, 5, 12));
	cam.Dir(glm::vec3(0, 0, 1));
	cam.Haut(glm::vec3(0, 1, 0));
	cam.Largeur((5.6 * 513) / 384);
	cam.Hauteur(5.6);

	cam.Calculer_image(pixmap, scene, 4);

	pixmap.Transferer(bitmap);
	bitmap.Enregistrer("image.bmp");

	return 0;
}
