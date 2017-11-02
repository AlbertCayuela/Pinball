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
	
	PhysBody* sensor;
	PhysBody* sensor2;
	PhysBody* sensor3;
	PhysBody* sensor4;
	PhysBody* sensor5;
	bool sensed;

	Animation Bola;
	Animation* currentanimation = nullptr;

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
	uint currentime, lastime, currentime2, lastime2;
};
