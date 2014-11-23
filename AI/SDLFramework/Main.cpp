#include <iostream>
#include "Config.h"
#include "FWApplication.h"
#include <SDL_events.h>
#include "SDL_timer.h"
#include <time.h>
#include "Controller.h"

int main(int args[])
{
	Controller* controller = new Controller();

	//auto window = Window::CreateSDLWindow();
	auto application = new FWApplication();
	if (!application->GetWindow())
	{
		LOG("Couldn't create window...");
		return EXIT_FAILURE;
	}
	
	application->SetTargetFPS(60);
	application->SetColor(Color(255, 10, 40, 255));
	
	/* initialize random seed: */
	srand(time(NULL));

	//SDL_Texture Cow & Rabbit
	SDL_Texture* textureCow = application->LoadTexture("cow-2.png");
	SDL_Texture* textureRabbit = application->LoadTexture("rabbit-3.png");


	//while (true){}
	while (application->IsRunning())
	{
		application->StartTick();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				application->Quit();
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){
				case SDLK_SPACE:
					std::cout << "Space pressed" << std::endl;
					application->RemoveTexture(textureCow);
					application->RemoveTexture(textureRabbit);
					
					controller->AStar();
					textureCow = application->LoadTexture("cow-2.png");
					textureRabbit = application->LoadTexture("rabbit-3.png");
					break;
				default:
					break;
				}
			}
		}
		
		application->SetColor(Color(0, 0, 0, 255));
		application->DrawText("", 800 / 2, 600 / 2);
		
		int height = 10;
		int width = 10;

		int mid_height = height / 2;
		int mid_width = width / 2;

		//Draw vertices
		for (auto vertex : *controller->getVertices()){
			application->DrawRect(vertex->getX(), vertex->getY(), height, width, true);
		}
		//Draw edges
		for (auto edge : *controller->getEdges()){
			application->DrawLine(edge->getSource()->getX() + mid_width, edge->getSource()->getY() + mid_height, 
				edge->getTarget()->getX() + mid_width, edge->getTarget()->getY() + mid_height);

			//Draw weight
			application->DrawText(std::to_string(edge->getWeight()), (edge->getSource()->getX() + edge->getTarget()->getX()) / 2, (edge->getSource()->getY() + edge->getTarget()->getY()) / 2);
		}

		application->DrawTexture(textureCow, controller->getVertexCow()->getX(), controller->getVertexCow()->getY(), 48, 48);
		application->DrawTexture(textureRabbit, controller->getVertexRabbit()->getX(), controller->getVertexRabbit()->getY(), 48, 48);


		// For the background
		application->SetColor(Color(255, 255, 255, 255));

		application->UpdateGameObjects();
		application->RenderGameObjects();
		application->EndTick();
	}
	
	delete controller;
	application->RemoveTexture(textureCow);
	application->RemoveTexture(textureRabbit);
	delete application;

	return EXIT_SUCCESS;
}