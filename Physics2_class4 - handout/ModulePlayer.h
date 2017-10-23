#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"


struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	p2List<PhysBody*> boles;
	SDL_Texture* bola;
	int vides = 4;

	bool creacioboles = false;



};