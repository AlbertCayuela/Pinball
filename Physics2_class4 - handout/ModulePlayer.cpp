#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	score = 0;
	vides = 5;
	highscore = score;
	LOG("Loading player");
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	//print tittle
	char title[80];
	int n = sprintf_s(title, "Droid Pinball - SCORE: %i  HIGHSCORE: %i  LIFES: %i", score, highscore, vides-1);
	App->window->SetTitle(title);

	
	
		return UPDATE_CONTINUE;
	}
	




