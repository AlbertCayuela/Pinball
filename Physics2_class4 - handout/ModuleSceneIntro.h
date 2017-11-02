#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Animation.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;
	
	//sensores
	PhysBody* sensor;
	PhysBody* sensor2;
	PhysBody* sensor3;
	PhysBody* sensor4;
	PhysBody* sensor5;
	PhysBody* sensorpunt1;
	PhysBody* sensorpunt2;
	PhysBody* sensorpunt3;
	PhysBody* sensorpuntesquerra1;
	PhysBody* sensorpuntesquerra2;
	PhysBody* sensorpuntesquerra3;
	PhysBody* sensorpuntdreta1;
	PhysBody* sensorpuntdreta2;
	PhysBody* sensorpuntdreta3;
	PhysBody* sensorpuntdretaabaix1;
	PhysBody* sensorpuntdretaabaix2;
	PhysBody* sensorpuntdretaabaix3;
	PhysBody* sensorpuntadalt;
	PhysBody* sensorfletxaadaltesquerra;
	PhysBody* sensorfletxaadaltdreta;
	PhysBody* sensorfletxadretaabaix;
	PhysBody* BolaEsquina;
	PhysBody* BolaSuperior;
	PhysBody* BolaDreta;
	PhysBody* BolaInferior;

	bool sensed;
	bool bolaEsquina = false;
	bool bolaSuperior = false;
	bool bolaDreta = false;
	bool bolaInferior = false;

	Animation Bola;
	Animation Bolas;

	Animation* currentanimation = nullptr;
	Animation* currentanimation1 = nullptr;

	SDL_Texture* spritesheet;
	SDL_Texture* background;
	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	uint bonus_fx;
	p2Point<int> ray;

	bool ray_on;
	bool colision = false;
	bool colisionx20 = false;
	bool rectanglex20 = false;
	bool colisions345 = false;

	int cont = 0;
	int cont1 = 0;
	int cont2 = 0;
	int cont3 = 0;
	int cont4 = 0;

	uint currentime, lastime, currentime2, lastime2;
};
