#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
	ray_on = false;
	sensed = false;

	Bola.PushBack({ 92,107,30,30 });
	Bolas.PushBack({ 1,14,61,35 });
	Punts.PushBack({ 71,15,10,10 });
	PuntsEsquerra.PushBack({160,146,19,20});
	PuntsDreta.PushBack({109,141,19,17});
	PuntsDretaAbaix.PushBack({193,166,16,19});
	PuntAdalt.PushBack({85,182,18,12});
	FletxaEsquerra.PushBack({18,133,68,74});
	X20.PushBack({210,171,43,63});
	X5adalt.PushBack({129,185,22,19});
	Fliperdreta.PushBack({0,0,162,54});
	Fliperesquerra.PushBack({0,0,160,50});
	
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	colision = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	spritesheet = App->textures->Load("pinball/spritesheet.png");
	background = App->textures->Load("pinball/captura.png");
	circle = App->textures->Load("pinball/ball.png");
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	fliperDreta = App->textures->Load("pinball/fliperdreta.png");
	fliperEsquerra = App->textures->Load("pinball/fliperesquerre.png");
	


	//sensors
	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);
	sensor2 = App->physics->CreateRectangleSensor(21, 722, 10, 10);
	sensor3 = App->physics->CreateRectangleSensor(205, 18, 10, 10);
	sensor4 = App->physics->CreateRectangleSensor(388, 59, 10, 10);
	sensor5 = App->physics->CreateRectangleSensor(423, 252, 10, 10);
	sensorpunt1 = App->physics->CreateRectangleSensor(350, 71, 5, 6);
	sensorpunt2 = App->physics->CreateRectangleSensor(311, 71, 5, 6);
	sensorpunt3 = App->physics->CreateRectangleSensor(270, 71, 5, 6);
	sensorpuntesquerra1 = App->physics->CreateRectangleSensor(93, 315, 4, 4);
	sensorpuntesquerra2 = App->physics->CreateRectangleSensor(85, 333, 4, 4);
	sensorpuntesquerra3 = App->physics->CreateRectangleSensor(75, 350, 4, 4);
	sensorpuntdreta1 = App->physics->CreateRectangleSensor(275, 232, 4, 4);
	sensorpuntdreta2 = App->physics->CreateRectangleSensor(290, 250, 4, 4);
	sensorpuntdreta3 = App->physics->CreateRectangleSensor(300, 267, 4, 4);
	sensorpuntdretaabaix1 = App->physics->CreateRectangleSensor(402, 405, 4, 4);
	sensorpuntdretaabaix2 = App->physics->CreateRectangleSensor(412, 423, 4, 4);
	sensorpuntdretaabaix3 = App->physics->CreateRectangleSensor(422, 442, 4, 4);
	sensorpuntadalt = App->physics->CreateRectangleSensor(177, 67, 4, 4);
	sensorfletxaadaltesquerra = App->physics->CreateRectangleSensor(69, 26, 45, 15);
	sensorfletxaadaltesquerra1 = App->physics->CreateRectangleSensor(47,49, 20, 40);
	sensorfletxaadaltdreta = App->physics->CreateRectangleSensor(101, 26, 6, 6);
	sensorfletxadretaabaix = App->physics->CreateRectangleSensor(18, 242, 6, 6);
	BolaEsquina = App->physics->CreateRectangleSensor(85, 67, 50, 33);
	BolaSuperior = App->physics->CreateRectangleSensor(287, 137, 50, 33);
	BolaDreta = App->physics->CreateRectangleSensor(363, 137, 50, 33);
	BolaInferior = App->physics->CreateRectangleSensor(314,205,50,33);

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
	int Captura[160] = {
		434, 493,
		428, 445,
		402, 393,
		401, 306,
		428, 274,
		426, 268,
		428, 263,
		428, 255,
		424, 249,
		418, 245,
		413, 244,
		404, 248,
		397, 253,
		394, 246,
		430, 203,
		433, 68,
		416, 52,
		392, 41,
		376, 57,
		374, 84,
		367, 84,
		368, 60,
		384, 40,
		396, 37,
		420, 47,
		436, 64,
		432, 436,
		434, 495,
		479, 525,
		478, 63,
		465, 37,
		446, 19,
		421, 7,
		392, 1,
		358, 1,
		310, 5,
		280, 13,
		259, 32,
		253, 81,
		246, 80,
		222, 57,
		221, 29,
		216, 20,
		208, 15,
		201, 13,
		195, 17,
		189, 26,
		187, 40,
		186, 60,
		167, 61,
		158, 42,
		145, 26,
		129, 14,
		107, 6,
		88, 3,
		62, 6,
		45, 13,
		28, 25,
		14, 38,
		-1, 61,
		-1, 358,
		13, 396,
		32, 438,
		57, 463,
		60, 478,
		0, 520,
		1, 736,
		25, 738,
		37, 729,
		38, 716,
		38, 697,
		170, 798,
		4, 804,
		1, 1020,
		498, 1013,
		480, 804,
		304, 806,
		475, 670,
		479, 526,
		438, 494
	};

	PhysBody* reboundhard;
	PhysBody* reboundnormal;
	PhysBody* rebound;

	//Con rebote extra
	reboundhard = App->physics->CreateChain(0, 0, SobrePaletaesquerra, 8, b2_staticBody);
	reboundhard->body->GetFixtureList()->SetRestitution(1.5f);
	reboundhard = App->physics->CreateChain(0, 0, SobrePaletadreta, 8, b2_staticBody);
	reboundhard->body->GetFixtureList()->SetRestitution(1.5f);
	reboundhard = App->physics->CreateChain(0, 0, BolaSuperiorEsquerra, 22, b2_staticBody);
	reboundhard->body->GetFixtureList()->SetRestitution(1.5f);
	reboundhard = App->physics->CreateChain(0, 0, CercleCantoSuperior, 24, b2_staticBody);
	reboundhard->body->GetFixtureList()->SetRestitution(1.5f);
	reboundhard = App->physics->CreateChain(0, 0, BolaAbaix, 24, b2_staticBody);
	reboundhard->body->GetFixtureList()->SetRestitution(1.5f);

	reboundnormal = App->physics->CreateChain(0, 0, BolaSuperiorEsquerre, 22, b2_staticBody);
	reboundnormal->body->GetFixtureList()->SetRestitution(1.5f);

	//rebote normal
	App->physics->CreateChain(0, 0, Captura, 160, b2_staticBody);

	rebound = App->physics->CreateChain(0, 0, Paletadreta, 16, b2_staticBody);
	rebound->body->GetFixtureList()->SetRestitution(0.1f);

	rebound = App->physics->CreateChain(0, 0, Paletaesquerra, 16, b2_staticBody);
	rebound->body->GetFixtureList()->SetRestitution(0.1f);



	App->physics->CreateChain(0, 0, PaletaSuperior, 18, b2_staticBody);
	App->physics->CreateChain(0, 0, Diagonal, 10, b2_staticBody);




	App->physics->CreateChain(0, 0, PalDreta, 8, b2_staticBody);

	App->physics->CreateChain(0, 0, PalEsquerra, 8, b2_staticBody);

	App->physics->createFlipperR();
	App->physics->createFlipperL();
	App->physics->createFlipperLT();
	App->physics->createSpring();




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

	currentanimation1 = &Bolas;
	currentanimation2 = &Punts; 
	currentanimation3 = &PuntsEsquerra;
	currentanimation4 = &PuntsDreta;
	currentanimation5 = &PuntsDretaAbaix;
	currentanimation6 = &PuntAdalt;
	currentanimation7 = &FletxaEsquerra;
	currentanimation8 = &X20;
	currentanimation9 = &X5adalt;
	currentanimation10 = &Fliperdreta;
	currentanimation11 = &Fliperesquerra;

	App->renderer->Blit(fliperEsquerra, -27, 205, &(currentanimation11->GetCurrentFrame()), 1.0f, RADTODEG * App->physics->cosflipper3->GetAngle());
	App->renderer->Blit(fliperEsquerra, 70, 680, &(currentanimation11->GetCurrentFrame()), 1.0f, RADTODEG * App->physics->cosflipper2->GetAngle());
	App->renderer->Blit(fliperDreta, 255, 680, &(currentanimation10->GetCurrentFrame()), 1.0f, RADTODEG * App->physics->cosflipper1->GetAngle());

	if (bolaEsquina == true && cont1 <= 10)
	{
		App->renderer->Blit(spritesheet, 53, 67, &(currentanimation1->GetCurrentFrame()), 1.0f);
		cont1++;
		if (cont1 == 10) {
			bolaEsquina = false;
			cont1 = 0;
		}
	}

	if (bolaSuperior == true && cont2 <= 10) 
	{
		App->renderer->Blit(spritesheet, 257, 145, &(currentanimation1->GetCurrentFrame()), 1.0f);
		cont2++;
		if (cont2 == 10) {
			bolaSuperior = false;
			cont2 = 0;
		}
	}

	if (bolaDreta == true && cont3 <= 10) 
	{
		App->renderer->Blit(spritesheet, 332, 149, &(currentanimation1->GetCurrentFrame()), 1.0f);
		cont3++;
		if (cont3 == 10) {
			bolaDreta = false;
			cont3 = 0;
		}
	}

	if (bolaInferior == true && cont4 <= 10) 
	{
		App->renderer->Blit(spritesheet, 283, 209, &(currentanimation1->GetCurrentFrame()), 1.0f);
		cont4++;
		if (cont4 == 10) {
			bolaInferior = false;
			cont4 = 0;
		}
	}
	
	if (punt1 == true && colision == false) 
	{
		App->renderer->Blit(spritesheet, 344, 65, &(currentanimation2->GetCurrentFrame()), 1.0f);
		
	}
	else
	{
		punt1 = false;
	}

	if (punt2 == true && colision == false)
	{
		App->renderer->Blit(spritesheet, 304, 65, &(currentanimation2->GetCurrentFrame()), 1.0f);
	}
	else 
	{
		punt2 = false;
	}

	if (punt3 == true && colision == false) 
	{
		App->renderer->Blit(spritesheet, 265, 64, &(currentanimation2->GetCurrentFrame()), 1.0f);
	}
	else 
	{
		punt3 = false;
	}

	if (puntesquerra1 == true && colision==false) 
	{
		App->renderer->Blit(spritesheet, 85,305, &(currentanimation3->GetCurrentFrame()), 1.0f);	
	}
	else 
	{
		puntesquerra1 = false;
	}

	if (puntesquerra2 == true && colision == false)
	{
		App->renderer->Blit(spritesheet, 74, 323, &(currentanimation3->GetCurrentFrame()), 1.0f);
	}
	else 
	{
		puntesquerra2 = false;
	}
	if (puntesquerra3 == true && colision == false)
	{
		App->renderer->Blit(spritesheet, 65,338, &(currentanimation3->GetCurrentFrame()), 1.0f);
	}
	else
	{
		puntesquerra3 = false;
	}
	if (puntdreta1 == true && colision == false)
	{
		App->renderer->Blit(spritesheet, 266,224, &(currentanimation4->GetCurrentFrame()), 1.0f);
	}
	else
	{
		puntdreta1= false;
	}
	if (puntdreta2 == true && colision == false)
	{
		App->renderer->Blit(spritesheet, 282,238, &(currentanimation4->GetCurrentFrame()), 1.0f);
	}
	else
	{
		puntdreta2 = false;
	}
	if (puntdreta3 == true && colision == false)
	{
		App->renderer->Blit(spritesheet, 295,256, &(currentanimation4->GetCurrentFrame()), 1.0f);
	}
	else
	{
		puntdreta3 = false;
	}
	if (puntdretaabaix1 == true && colision == false)
	{
		App->renderer->Blit(spritesheet, 392,395, &(currentanimation5->GetCurrentFrame()), 1.0f);
	}
	else
	{
		puntdretaabaix1 = false;
	}
	if (puntdretaabaix2 == true && colision == false)
	{
		App->renderer->Blit(spritesheet, 403,414, &(currentanimation5->GetCurrentFrame()), 1.0f);
	}
	else
	{
		puntdretaabaix2 = false;
	}
	if (puntdretaabaix3 == true && colision == false)
	{
		App->renderer->Blit(spritesheet, 412,433, &(currentanimation5->GetCurrentFrame()), 1.0f);
	}
	else
	{
		puntdretaabaix3 = false;
	}
	if (puntadalt == true && colision == false)
	{
		App->renderer->Blit(spritesheet, 169,63, &(currentanimation6->GetCurrentFrame()), 1.0f);
	}
	else
	{
		puntadalt = false;
	}
	if (x20 == true && colision == false)
	{
		App->renderer->Blit(spritesheet, 0,615, &(currentanimation8->GetCurrentFrame()), 1.0f);
	}
	else
	{
		x20 = false;
	}
	if (x5adalt == true && colision == false)
	{
		App->renderer->Blit(spritesheet, 193,46, &(currentanimation9->GetCurrentFrame()), 1.0f);
	}
	else
	{
		x5adalt = false;
	}
	if (x5dreta == true && colision == false)
	{
		App->renderer->Blit(spritesheet, 390,92, &(currentanimation9->GetCurrentFrame()), 1.0f);
	}
	else
	{
		x5dreta = false;
	}
	/*if (fletxaesquerra1 == true && cont5 <= 300) {
		fletxaesquerra = true && cont5 <= 300;
		cont5++;
			App->renderer->Blit(spritesheet, 6,16, &(currentanimation7->GetCurrentFrame()), 1.0f);
			if (cont5 == 300) {
				fletxaesquerra=false;
				fletxaesquerra = false;
				cont5 = 0;
			}
		
	}
*/
	


	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 30));
		circles.getLast()->data->listener = this;
	}


	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		App->physics->cosflipper1->ApplyTorque(250.0, true);
	}
	else {
		if (App->physics->cosflipper1->IsAwake()) {
			App->physics->cosflipper1->ApplyTorque(-250.0, false);
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		App->physics->cosflipper2->ApplyTorque(-250.0, true);
		App->physics->cosflipper3->ApplyTorque(-250, true);
	}
	else {
		if (App->physics->cosflipper2->IsAwake()) {
			App->physics->cosflipper2->ApplyTorque(250.0, false);
		}
		if (App->physics->cosflipper3->IsAwake()) {
			App->physics->cosflipper3->ApplyTorque(250.0, false);
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		App->physics->muelle->ApplyForce(b2Vec2(0, -250), App->physics->muelle->GetLocalCenter(), true);
	}
	else {
		if (App->physics->muelle->IsAwake()) {
			App->physics->muelle->ApplyForce(b2Vec2(0, 250), App->physics->muelle->GetLocalCenter(), true);
		}
	}


	if (colision == true) {

		if (App->player->vides <= 4 && colision == true && App->player->vides > 0) {

			circles.add(App->physics->CreateCircle(446, 420, 30));
			circles.getLast()->data->listener = this;
			colision = false;
			App->player->vides--;

		}
	}
	currentime = SDL_GetTicks();
	if (currentime - lastime > 1000 && colisionx20) {
		circles.getLast()->data->body->ApplyLinearImpulse({ 0, -10 }, { 0,0 }, true);
		colisionx20 = false;

	}

	if (currentime - lastime > 1500 && rectanglex20) {
		App->physics->CreateRectangle(20, 687, 25, 3, 0.7f);
		rectanglex20 = false;
	}

	if (currentime - lastime2 > 500 && colisions345) {
		circles.getLast()->data->body->ApplyLinearImpulse({ 0, 6 }, { 0,0 }, true);
		circles.getLast()->data->body->SetGravityScale(1);
		colisions345 = false;
	}



		/*if (App->player->vides == 3 && colision == true) {

			circles.add(App->physics->CreateCircle(446, 420, 30));
			circles.getLast()->data->listener = this;
			colision = false;

			App->player->vides--;

		}

		if (App->player->vides == 2 && colision == true) {

			circles.add(App->physics->CreateCircle(446, 420, 30));
			circles.getLast()->data->listener = this;
			colision = false;
			App->player->vides--;

		}
		if (App->player->vides == 1 && colision == true) {

			circles.add(App->physics->CreateCircle(446, 420, 30));
			circles.getLast()->data->listener = this;
			colision = false;
			App->player->vides--;

		}
	}*/
	//else if (creacioboles == false && vides < 3 && vides > 0) {
	//	boles.add(App->physics->CreateCircle(442, 414, 40));

	//	creacioboles = true;

	//}
	//// Prepare for raycast ------------------------------------------------------

	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while (c != NULL)
	{
		currentanimation = &Bola;
		int x, y;
		c->data->GetPosition(x, y);
		//if (c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
			App->renderer->Blit(circle, x+15, y+15, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if (ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if (hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	c = ricks.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	// ray -----------------
	if (ray_on == true)
	{
		fVector destination(mouse.x - ray.x, mouse.y - ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if (normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	App->audio->PlayFx(bonus_fx);


	/*if(bodyA)
	{
	bodyA->GetPosition(x, y);
	App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}
	*/
	if (bodyB == sensor)
	{

		colision = true;

	}

	if (bodyB == sensor2) {

		colisionx20 = true;
		rectanglex20 = true;

		lastime = SDL_GetTicks();


	}

	
	if (bodyB == sensor3 || bodyB == sensor4 || bodyB == sensor5){
		lastime2 = SDL_GetTicks();

		circles.getLast()->data->body->SetGravityScale(0);
		colisions345 = true;
	}

	if (bodyB == BolaEsquina)
	{
		bolaEsquina = true;
	}

	if (bodyB == BolaSuperior) 
	{
		bolaSuperior = true;
	}

	if (bodyB == BolaDreta)
	{
		bolaDreta = true;
	}

	if(bodyB==BolaInferior)
	{
		bolaInferior = true;
	}
	if (bodyB == sensorpunt1) 
	{
		punt1 = true;
	}

	if (bodyB == sensorpunt2) 
	{
		punt2 = true;
	}

	if (bodyB == sensorpunt3)
	{

		punt3 = true;
	}
	if (bodyB == sensorpuntesquerra1) 
	{
		puntesquerra1 = true;
	}
	if (bodyB == sensorpuntesquerra2) 
	{
		puntesquerra2 = true;
	}
	if (bodyB == sensorpuntesquerra3) 
	{
		puntesquerra3 = true;
	}
	if (bodyB == sensorpuntdreta1)
	{
		puntdreta1= true;
	}
	if (bodyB == sensorpuntdreta2)
	{
		puntdreta2 = true;
	}
	if (bodyB == sensorpuntdreta3)
	{
		puntdreta3 = true;
	}
	if (bodyB == sensorpuntdretaabaix1)
	{
		puntdretaabaix1 = true;
	}
	if (bodyB == sensorpuntdretaabaix2)
	{
		puntdretaabaix2 = true;
	}
	if (bodyB == sensorpuntdretaabaix3)
	{
		puntdretaabaix3 = true;
	}
	if (bodyB == sensorpuntadalt)
	{
		puntadalt = true;
	}
	if (bodyB == sensorfletxaadaltesquerra)
	{
		fletxaesquerra = true;
	}
	if (bodyB == sensorfletxaadaltesquerra1)
	{
		fletxaesquerra1 = true;
	}
	if (bodyB == sensor2)
	{
		x20 = true;
	}
	if (bodyB == sensor3)
	{
		x5adalt = true;
	}
	if (bodyB == sensor4)
	{
		x5dreta = true;
	}
}

