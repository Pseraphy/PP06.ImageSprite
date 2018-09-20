#include "Game.h"
#include<iostream>
#include<SDL_image.h>

using namespace std;
Game *g_game = 0;


bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, fullscreen);



		if (m_pWindow != 0)
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
		}
		SDL_Surface* pTempSurface = IMG_Load("assets/animate.png");
	//	SDL_Surface* pTempSurface = IMG_Load("assets/animate-alpha.png");
		m_pTextrue = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
		
		SDL_FreeSurface(pTempSurface);
		
		SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
		
		//SDL_QueryTexture(m_pTextrue, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);

		m_sourceRectangle.w = 128;
		m_sourceRectangle.h = 82;
	}
	else {
		return false;
	}
	m_bRunning = true;
	return true;

	/*
	SDL_Surface* pTempSurface = SDL_LoadBMP("assets/rider.bmp");
	m_pTextrue = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	SDL_QueryTexture(m_pTextrue, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);*/
}
void Game::render()
{


	m_destinationRectangle.x = m_sourceRectangle.x = 0;
	m_destinationRectangle.y = m_sourceRectangle.y = 0;
	m_destinationRectangle.w = m_sourceRectangle.w;
	m_destinationRectangle.h = m_sourceRectangle.h;

	SDL_RenderClear(m_pRenderer);

	SDL_RenderCopy(m_pRenderer, m_pTextrue, &m_sourceRectangle, &m_destinationRectangle);
	SDL_RenderPresent(m_pRenderer);

}

void Game::clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
void Game::handleEvents()
{

	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		default:
			break;

		}
	}
}
void Game::update()
{
	m_sourceRectangle.x = 128 * int(((SDL_GetTicks() / 100) % 6));
}
int main(int argc, char* argv[])
{
	g_game = new Game();
	g_game->init("Chapter 1", 100, 100, 640, 480, false);


	while (g_game->running())
	{
		g_game->handleEvents();
		g_game->update();
		g_game->render();

	}

	g_game->clean();
	return 0;

}