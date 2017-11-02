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
	PhysBody* sensorfletxaadaltesquerra1;
	PhysBody* sensorfletxaadaltdreta;
	PhysBody* sensorfletxaadaltdreta1;
	PhysBody* sensorfletxadretaabaix;
	PhysBody* BolaEsquina;
	PhysBody* BolaSuperior;
	PhysBody* BolaDreta;
	PhysBody* BolaInferior;
	PhysBody* reboundhard;
	PhysBody* reboundhard1;
	PhysBody* reboundhard2;
	PhysBody* reboundnormal;
	PhysBody* rebound;


	bool sensed= false;
	bool bolaEsquina = false;
	bool bolaSuperior = false;
	bool bolaDreta = false;
	bool bolaInferior = false;
	bool punt1 = false;
	bool punt2 = false;
	bool punt3 = false;
	bool puntesquerra1 = false;
	bool puntesquerra2 = false;
	bool puntesquerra3 = false;
	bool puntdreta1 = false;
	bool puntdreta2 = false;
	bool puntdreta3 = false;
	bool puntdretaabaix1 = false;
	bool puntdretaabaix2 = false;
	bool puntdretaabaix3 = false;
	bool puntadalt = false;
	bool fletxaesquerra = true;
	bool x20 = false;
	bool x5adalt=false;
	bool x5dreta = false;
	bool fliperdreta = false;
	bool fliperesquerra = false;
	bool foC = true;
	bool x10;

	Animation Bola;
	Animation Bolas;
	Animation Punts;
	Animation PuntsEsquerra;
	Animation PuntsDreta;
	Animation PuntsDretaAbaix;
	Animation PuntAdalt;
	Animation FletxaDreta;
	Animation FletxaEsquerra;
	Animation Fletxaabaix;
	Animation X20;
	Animation X5adalt;
	Animation Fliperdreta;
	Animation Fliperesquerra;
	Animation Num0;
	Animation Num1;
	Animation Num2;
	Animation Num3;
	Animation foc;
	Animation X10;

	Animation* currentanimation = nullptr;
	Animation* currentanimation1 = nullptr;
	Animation* currentanimation2 = nullptr;
	Animation* currentanimation3 = nullptr;
	Animation* currentanimation4 = nullptr;
	Animation* currentanimation5 = nullptr;
	Animation* currentanimation6 = nullptr;
	Animation* currentanimation7 = nullptr;
	Animation* currentanimation8 = nullptr;
	Animation* currentanimation9 = nullptr;
	Animation* currentanimation10 = nullptr;
	Animation* currentanimation11 = nullptr;
	Animation* currentanimation12 = nullptr;
	Animation* currentanimation13 = nullptr;
	Animation* currentanimation14 = nullptr;
	Animation* currentanimation15 = nullptr;
	Animation* currentanimation16 = nullptr;
	Animation* currentanimation17 = nullptr;
	Animation* currentanimation18 = nullptr;
	Animation* currentanimation19 = nullptr;
	

	SDL_Texture* spritesheet;
	SDL_Texture* background;
	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* fliperDreta;
	SDL_Texture* fliperEsquerra;
	SDL_Texture* Foc;

	uint bonus_fx;
	uint paletes;
	uint paletesabaix;
	uint randompoint;
	uint motlla;
	uint boles;

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
	int cont5 = 0;
	

	uint currentime, lastime, currentime2, lastime2;
};
