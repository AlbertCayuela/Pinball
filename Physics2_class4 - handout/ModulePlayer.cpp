#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
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
	
		if (vides = 4 && creacioboles == false) {

			boles.add(App->physics->CreateBoles(446, 420, 30));

			creacioboles = true;


		}
		
		else if (creacioboles == false && vides < 3 && vides > 0) {
			boles.add(App->physics->CreateBoles(442, 414, 40));

			creacioboles = true;

		}

		//if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {

		//	boles.getFirst()->data->body->ApplyLinearImpulse({ 0, -10 }, { 0, 0 }, true);
		//}
		p2List_item<PhysBody*>* rip = boles.getFirst();


		while (rip != NULL) {

			int x, y;

			rip->data->GetPosition(x, y);
			App->renderer->Blit(bola, x, y, NULL, 1.0f, rip->data->GetRotation());
			rip = rip->next;

		}

		return UPDATE_CONTINUE;
	}
	




