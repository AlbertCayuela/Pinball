#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	background = App->textures->Load("pinball/captura.png");
	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	
	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);

	int Paletadreta[16] = {
		330, 709,
		422, 638,
		434, 604,
		435, 539,
		430, 538,
		429, 599,
		416, 635,
		325, 704
	};
	// Pivot 0, 0
	int Paletaesquerra[16] = {
		153, 706,
		61, 634,
		49, 599,
		50, 543,
		44, 543,
		43, 602,
		54, 636,
		149, 710
	};

	// Pivot 0, 0
	int SobrePaletaesquerra[8] = {
		154, 657,
		89, 519,
		87, 607,
		150, 663
	};

	// Pivot 0, 0
	int SobrePaletadreta[8] = {
		320, 657,
		386, 606,
		385, 519,
		317, 655
	};

	// Pivot 0, 0 Add
	int PaletaSuperior[18] = {
		59, 361,
		37, 348,
		31, 235,
		45, 223,
		50, 227,
		37, 242,
		44, 265,
		98, 287,
		60, 356
	};

	// Pivot 0, 0 add
	int Diagonal[10] = {
		313, 264,
		317, 259,
		276, 217,
		271, 221,
		309, 261
	};

	// Pivot 0, 0 add
	int BolaAbaix[24] = {
		315, 224,
		326, 221,
		336, 213,
		337, 203,
		329, 193,
		317, 190,
		304, 192,
		294, 199,
		291, 208,
		294, 217,
		301, 221,
		310, 223
	};

	// Pivot 0, 0
	int BolaSuperiorEsquerre[22] = {
		363, 153,
		375, 152,
		383, 146,
		386, 136,
		380, 126,
		368, 122,
		353, 123,
		343, 130,
		340, 142,
		347, 148,
		358, 153
	};
	// Pivot 0, 0
	int BolaSuperiorEsquerra[22] = {
		286, 156,
		300, 151,
		308, 143,
		307, 130,
		296, 122,
		283, 120,
		272, 125,
		264, 133,
		265, 143,
		273, 150,
		281, 155
	};

	// Pivot 0, 0
	int PalDreta[8] = {
		332, 83,
		332, 59,
		328, 59,
		328, 83
	};

	// Pivot 0, 0
	int PalEsquerra[8] = {
		292, 82,
		292, 58,
		287, 58,
		287, 82
	};

	// Pivot 0, 0
	int CercleCantoSuperior[24] = {
		85, 85,
		96, 81,
		106, 75,
		109, 64,
		103, 55,
		94, 50,
		79, 49,
		69, 55,
		62, 64,
		63, 74,
		72, 80,
		80, 85
	};


	// Pivot 0, 0
	int Captura[132] = {
		307, 800,
		476, 671,
		477, 522,
		432, 483,
		430, 448,
		402, 394,
		402, 307,
		426, 271,
		402, 246,
		431, 204,
		430, 65,
		394, 40,
		371, 58,
		373, 82,
		363, 82,
		362, 59,
		393, 33,
		436, 63,
		432, 439,
		477, 439,
		477, 61,
		461, 36,
		437, 15,
		409, 2,
		321, -1,
		292, 8,
		268, 18,
		250, 36,
		251, 77,
		225, 56,
		221, 35,
		218, 25,
		214, 19,
		207, 15,
		198, 16,
		192, 20,
		190, 28,
		189, 38,
		186, 60,
		167, 60,
		149, 31,
		135, 20,
		116, 8,
		96, 2,
		67, 3,
		44, 10,
		26, 23,
		15, 34,
		8, 47,
		0, 61,
		0, 359,
		12, 390,
		23, 420,
		36, 442,
		60, 460,
		59, 479,
		0, 520,
		0, 739,
		27, 736,
		38, 724,
		40, 696,
		168, 800,
		0, 797,
		-4, 1111,
		482, 1085,
		478, 801
	};

	PhysBody* reboundhard;
	PhysBody* reboundnormal;
	PhysBody* rebound;

	//Con rebote extra
	reboundhard = App->physics->CreateChain(0, 0, SobrePaletaesquerra, 8, b2_staticBody);
	reboundhard->body->GetFixtureList()->SetRestitution(2.0f);
	reboundhard = App->physics->CreateChain(0, 0, SobrePaletadreta, 8, b2_staticBody);
	reboundhard->body->GetFixtureList()->SetRestitution(2.0f);
	reboundhard = App->physics->CreateChain(0, 0, BolaSuperiorEsquerra, 22, b2_staticBody);
	reboundhard->body->GetFixtureList()->SetRestitution(2.0f);
	reboundhard = App->physics->CreateChain(0, 0, CercleCantoSuperior, 24, b2_staticBody);
	reboundhard->body->GetFixtureList()->SetRestitution(2.0f);
	reboundhard = App->physics->CreateChain(0, 0, BolaAbaix, 24, b2_staticBody);
	reboundhard->body->GetFixtureList()->SetRestitution(2.0f);

	reboundnormal = App->physics->CreateChain(0, 0, BolaSuperiorEsquerre, 22, b2_staticBody);
	reboundnormal->body->GetFixtureList()->SetRestitution(1.5f);

	//rebote normal
	App->physics->CreateChain(0, 0, Captura, 132, b2_staticBody);

	rebound=App->physics->CreateChain(0, 0, Paletadreta, 16, b2_staticBody);
	rebound->body->GetFixtureList()->SetRestitution(0.1f);
	
	rebound=App->physics->CreateChain(0, 0, Paletaesquerra, 16, b2_staticBody);
	rebound->body->GetFixtureList()->SetRestitution(0.1f);

	

	App->physics->CreateChain(0, 0, PaletaSuperior, 18, b2_staticBody);
	App->physics->CreateChain(0, 0, Diagonal, 10, b2_staticBody);
	
	

	
	App->physics->CreateChain(0, 0, PalDreta, 8, b2_staticBody);
	
	App->physics->CreateChain(0, 0, PalEsquerra, 8, b2_staticBody);
	

	



	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	App->renderer->Blit(background, 0, 0);
	

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25));
		circles.getLast()->data->listener = this;
	}


/* if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		int rick_head[64] = {
			14, 36,
			42, 40,
			40, 0,
			75, 30,
			88, 4,
			94, 39,
			111, 36,
			104, 58,
			107, 62,
			117, 67,
			109, 73,
			110, 85,
			106, 91,
			109, 99,
			103, 104,
			100, 115,
			106, 121,
			103, 125,
			98, 126,
			95, 137,
			83, 147,
			67, 147,
			53, 140,
			46, 132,
			34, 136,
			38, 126,
			23, 123,
			30, 114,
			10, 102,
			29, 90,
			0, 75,
			30, 62
		};

		ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64));
	}*/
	// Pivot 0, 0
	
	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	App->audio->PlayFx(bonus_fx);

	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
}
