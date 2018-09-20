#include "SDL.h"

class Game {
public:
	Game() {}
	~Game() {}

	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	SDL_Texture* m_pTextrue;
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;
	void render();
	void update();
	void handleEvents();
	void clean();
	bool running() { return m_bRunning; }
	bool m_bRunning;
private:
	SDL_Window * m_pWindow;
	SDL_Renderer *m_pRenderer;

};
