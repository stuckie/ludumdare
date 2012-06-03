// Germies - started 4:30pm - 9 hours 30 mins remaining
// Main game finished midnight - 2 hours remaining
// total time to code - six and a half hours, wooo!

#include <string>
#include <iostream>
#include <cassert>
#include <ctime>

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_framerate.h>

//#define IS64BIT // uncomment for compiling on 64bit platforms. - added 22DEC after testing on 32bit Linux and Win7 and noticing everything was double speed!

#ifdef IS64BIT
	const int gTimeMultiply = 1;
#else
	const int gTimeMultiply = 2;
#endif

const int PLAYAREA_WIDTH = 8;
const int PLAYAREA_HEIGHT = 5;
const int PLAYAREA_LEFT = 1;
const int PLAYAREA_RIGHT = 7;
const int WAIT_AREA_LEFT = 0;
const int WAIT_AREA_RIGHT = PLAYAREA_WIDTH;
const int MAX_WAIT_AREA = PLAYAREA_HEIGHT;

const int OFFSET_X = 64;
const int OFFSET_Y = 64;

int gMouseX = 0;
int gMouseY = 0;
int gMouseDown = false;

SDL_Surface* gScreen;
SDL_Surface* gBackground;
SDL_Surface* gCell;
SDL_Surface* gWaitCell;

SDL_Surface* gRedGerm100;
SDL_Surface* gRedGerm75;
SDL_Surface* gRedGerm50;
SDL_Surface* gRedGerm25;
SDL_Surface* gRedGerm0;

SDL_Surface* gBlueGerm100;
SDL_Surface* gBlueGerm75;
SDL_Surface* gBlueGerm50;
SDL_Surface* gBlueGerm25;
SDL_Surface* gBlueGerm0;

SDL_Surface* gYellowGerm100;
SDL_Surface* gYellowGerm75;
SDL_Surface* gYellowGerm50;
SDL_Surface* gYellowGerm25;
SDL_Surface* gYellowGerm0;

SDL_Surface* gGreenGerm100;
SDL_Surface* gGreenGerm75;
SDL_Surface* gGreenGerm50;
SDL_Surface* gGreenGerm25;
SDL_Surface* gGreenGerm0;

SDL_Surface* gWhiteGerm100;
SDL_Surface* gWhiteGerm75;
SDL_Surface* gWhiteGerm50;
SDL_Surface* gWhiteGerm25;
SDL_Surface* gWhiteGerm0;

SDL_Surface* gDiseasedGerm;
SDL_Surface* gGameOverSprite;
SDL_Surface* gWarningSprite;

SDL_Surface* gFrom;
SDL_Surface* gTo;

SDL_Surface* gFont16;
SDL_Surface* gFont8;

Mix_Chunk* gGameOverSound;
Mix_Chunk* gWarningSound;
Mix_Chunk* gDiseasedSound;
Mix_Chunk* gDisappearSound;
Mix_Chunk* gSelectSound;
Mix_Chunk* gSwapSound;
Mix_Chunk* gSpawnSound;

Uint32 gLastTicks;
int gInfectionTimer;
int gWarningFlashTimer;
int gDiseaseTimer;

FPSmanager gFpsManager;
Uint8* gKeyboardBuffer;
bool gKeyBounce;
bool gWarning;
bool gGameOver;

enum GermType {
	RED
,	YELLOW
,	BLUE
,	GREEN
,	WHITE
,	DISEASED
};

struct Germ {
	int 		health;
	int		timeTillNextHealthDrop;
	GermType type;
};

struct Tile {
	Germ* germ;
};

struct Indicator {
	int 		gridX;
	int 		gridY;
	SDL_Surface* 	sprite;
};

struct Player {
	int		timeTillNextInfection;
	unsigned int 	score;
	int		gridX;
	int		gridY;
	Indicator*	indicatorFrom;
	Indicator*	indicatorTo;
	bool		selectedGerm;
};

Tile gPlayArea[PLAYAREA_HEIGHT][PLAYAREA_WIDTH]; // [x][y]

void setupTiles();
void spawnGerm();
Germ* newGerm();
void drawTiles();
void drawIndicators();
void drawFonts();
void drawGerm(Germ* germ, const int x, const int y);
void drawSprite(SDL_Surface* sprite, const int x, const int y);
void cleanupTiles();
void writeText(SDL_Surface* fontTex, const char* string, const int size, const int x, const int y);
void checkGrid();
void spreadInfection();
void swapGerm(const int fromX, const int fromY, const int toX, const int toY);
const bool squaredGerms(Germ* germ, const int x, const int y);
const int deleteGerm(Germ* germ);
void spreadDisease(Germ* germ, const int x, const int y);

Player gPlayer;

int main(int argc, char* argv[])
{
	srand(time(NULL));

	SDL_Init(SDL_INIT_EVERYTHING);

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16, MIX_DEFAULT_CHANNELS, 4096);
	Mix_AllocateChannels(10);

	gGameOverSound = Mix_LoadWAV("data/gameover.wav");
	gWarningSound = Mix_LoadWAV("data/warning.wav");
	gDiseasedSound = Mix_LoadWAV("data/disaeased.wav");
	gDisappearSound = Mix_LoadWAV("data/disappear.wav");
	gSelectSound = Mix_LoadWAV("data/select.wav");
	gSwapSound = Mix_LoadWAV("data/swap.wav");
	gSpawnSound = Mix_LoadWAV("data/spawn.wav");

	gScreen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);

	SDL_WM_SetCaption("Germies", "Germies");

	SDL_initFramerate(&gFpsManager);
	SDL_setFramerate(&gFpsManager, 60);

	setupTiles();
	gBackground = SDL_LoadBMP("data/background.bmp");

	gPlayer.timeTillNextInfection = 5;
	gPlayer.score = 0;
	gPlayer.selectedGerm = false;

	gLastTicks = 0;
	gInfectionTimer = 100;
	gWarningFlashTimer = 300;

	bool hasQuit(false);
	SDL_Event event;
	gWarning = false;
	gGameOver = false;
	while (false == hasQuit) {
		SDL_PumpEvents();
		gKeyboardBuffer = SDL_GetKeyState(NULL);

		hasQuit = gKeyboardBuffer[SDLK_ESCAPE];
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				hasQuit = true;

			if (event.type==SDL_MOUSEBUTTONDOWN) {
				gMouseX=(event.button.x/64) - 1;
				gMouseY=(event.button.y/64) - 1;
				if (gMouseDown == false) {
					if ((gMouseY > -1) && (gMouseY < PLAYAREA_HEIGHT) && (gMouseX > -1) && (gMouseX < PLAYAREA_WIDTH)) {
						gPlayer.gridX=gMouseX;
						gPlayer.gridY=gMouseY;
						if (false == gPlayer.selectedGerm) {
							gPlayer.selectedGerm = true;
							gPlayer.indicatorFrom->gridX = gPlayer.gridX;
							gPlayer.indicatorFrom->gridY = gPlayer.gridY;
							//Mix_PlayChannel(-1, gSelectSound, 0);
						}
						else {
							const int fromX(gPlayer.indicatorFrom->gridX);
							const int fromY(gPlayer.indicatorFrom->gridY);
							const int toX(gPlayer.gridX);
							const int toY(gPlayer.gridY);
							swapGerm(fromX, fromY, toX, toY);
						}
					}
				}
				gMouseDown = true;
			}

			if (event.type==SDL_MOUSEBUTTONUP) {
				gMouseDown = false;
			}
		}

		if (false == gGameOver) {
			// logic updates
			checkGrid();
			spreadInfection();
			gLastTicks = SDL_GetTicks();

			// update input/events
			if ((gKeyBounce == false) && (gKeyboardBuffer[SDLK_LEFT])) {
				if (gPlayer.gridX > 0)
					--gPlayer.gridX;
				gKeyBounce = true;
			}
			else if ((gKeyBounce == false) && (gKeyboardBuffer[SDLK_RIGHT])) {
				if (gPlayer.gridX < PLAYAREA_WIDTH - 1)
					++gPlayer.gridX;
				gKeyBounce = true;
			}
			else if ((gKeyBounce == false) && (gKeyboardBuffer[SDLK_UP])) {
				if (gPlayer.gridY > 0)
					--gPlayer.gridY;
				gKeyBounce = true;
			}
			else if ((gKeyBounce == false) && (gKeyboardBuffer[SDLK_DOWN])) {
				if (gPlayer.gridY < PLAYAREA_HEIGHT - 1)
					++gPlayer.gridY;
				gKeyBounce = true;
			}
			else if ((gKeyBounce == false) && (gKeyboardBuffer[SDLK_SPACE])) {
				if (false == gPlayer.selectedGerm) {
					gPlayer.selectedGerm = true;
					gPlayer.indicatorFrom->gridX = gPlayer.gridX;
					gPlayer.indicatorFrom->gridY = gPlayer.gridY;
					Mix_PlayChannel(-1, gSelectSound, 0);
				}
				else {
					const int fromX(gPlayer.indicatorFrom->gridX);
					const int fromY(gPlayer.indicatorFrom->gridY);
					const int toX(gPlayer.gridX);
					const int toY(gPlayer.gridY);
					swapGerm(fromX, fromY, toX, toY);
				}
				gKeyBounce = true;
			}
			else if (!(gKeyboardBuffer[SDLK_LEFT])
			&&	 !(gKeyboardBuffer[SDLK_RIGHT])
			&&	 !(gKeyboardBuffer[SDLK_UP])
			&&	 !(gKeyboardBuffer[SDLK_DOWN])
			&&	 !(gKeyboardBuffer[SDLK_SPACE])) {
				gKeyBounce = false;
			}
		}

		// update graphics
		SDL_framerateDelay(&gFpsManager);
		SDL_FillRect(SDL_GetVideoSurface(), NULL, 0);

		// draw background
		SDL_BlitSurface(gBackground, NULL, gScreen, NULL);

		// draw tiles
		drawTiles();

		// draw indicators
		drawIndicators();

		// draw fonts
		drawFonts();

		SDL_Flip(gScreen);

		// update sound?
	}

	cleanupTiles();
	SDL_FreeSurface(gBackground);
	SDL_FreeSurface(gScreen);
	SDL_FreeSurface(gCell);
	SDL_FreeSurface(gWaitCell);
	SDL_FreeSurface(gRedGerm100);
	SDL_FreeSurface(gRedGerm75);
	SDL_FreeSurface(gRedGerm50);
	SDL_FreeSurface(gRedGerm25);
	SDL_FreeSurface(gRedGerm0);
	SDL_FreeSurface(gBlueGerm100);
	SDL_FreeSurface(gBlueGerm75);
	SDL_FreeSurface(gBlueGerm50);
	SDL_FreeSurface(gBlueGerm25);
	SDL_FreeSurface(gBlueGerm0);
	SDL_FreeSurface(gGreenGerm100);
	SDL_FreeSurface(gGreenGerm75);
	SDL_FreeSurface(gGreenGerm50);
	SDL_FreeSurface(gGreenGerm25);
	SDL_FreeSurface(gGreenGerm0);
	SDL_FreeSurface(gYellowGerm100);
	SDL_FreeSurface(gYellowGerm75);
	SDL_FreeSurface(gYellowGerm50);
	SDL_FreeSurface(gYellowGerm25);
	SDL_FreeSurface(gYellowGerm0);
	SDL_FreeSurface(gWhiteGerm100);
	SDL_FreeSurface(gWhiteGerm75);
	SDL_FreeSurface(gWhiteGerm50);
	SDL_FreeSurface(gWhiteGerm25);
	SDL_FreeSurface(gWhiteGerm0);
	SDL_FreeSurface(gFrom);
	SDL_FreeSurface(gTo);
	SDL_FreeSurface(gFont16);
	SDL_FreeSurface(gFont8);
	SDL_FreeSurface(gGameOverSprite);
	SDL_FreeSurface(gWarningSprite);

	Mix_FreeChunk(gGameOverSound);
	Mix_FreeChunk(gWarningSound);
	Mix_FreeChunk(gDiseasedSound);
	Mix_FreeChunk(gDisappearSound);
	Mix_FreeChunk(gSelectSound);
	Mix_FreeChunk(gSwapSound);
	Mix_FreeChunk(gSpawnSound);

	Mix_CloseAudio();

	// Goodbye World
	return 0;
}

void setupTiles()
{
	gCell = SDL_LoadBMP("data/cell.bmp");
	gWaitCell = SDL_LoadBMP("data/waitcell.bmp");

	gRedGerm100 = SDL_LoadBMP("data/red100.bmp");
	gRedGerm75 = SDL_LoadBMP("data/red75.bmp");
	gRedGerm50 = SDL_LoadBMP("data/red50.bmp");
	gRedGerm25 = SDL_LoadBMP("data/red25.bmp");
	gRedGerm0 = SDL_LoadBMP("data/red0.bmp");

	gBlueGerm100 = SDL_LoadBMP("data/blue100.bmp");
	gBlueGerm75 = SDL_LoadBMP("data/blue75.bmp");
	gBlueGerm50 = SDL_LoadBMP("data/blue50.bmp");
	gBlueGerm25 = SDL_LoadBMP("data/blue25.bmp");
	gBlueGerm0 = SDL_LoadBMP("data/blue0.bmp");

	gYellowGerm100 = SDL_LoadBMP("data/yellow100.bmp");
	gYellowGerm75 = SDL_LoadBMP("data/yellow75.bmp");
	gYellowGerm50 = SDL_LoadBMP("data/yellow50.bmp");
	gYellowGerm25 = SDL_LoadBMP("data/yellow25.bmp");
	gYellowGerm0 = SDL_LoadBMP("data/yellow0.bmp");

	gWhiteGerm100 = SDL_LoadBMP("data/white100.bmp");
	gWhiteGerm75 = SDL_LoadBMP("data/white75.bmp");
	gWhiteGerm50 = SDL_LoadBMP("data/white50.bmp");
	gWhiteGerm25 = SDL_LoadBMP("data/white25.bmp");
	gWhiteGerm0 = SDL_LoadBMP("data/white0.bmp");

	gGreenGerm100 = SDL_LoadBMP("data/green100.bmp");
	gGreenGerm75 = SDL_LoadBMP("data/green75.bmp");
	gGreenGerm50 = SDL_LoadBMP("data/green50.bmp");
	gGreenGerm25 = SDL_LoadBMP("data/green25.bmp");
	gGreenGerm0 = SDL_LoadBMP("data/green0.bmp");

	gDiseasedGerm = SDL_LoadBMP("data/diseased.bmp");

	gFrom = SDL_LoadBMP("data/from.bmp");
	gTo = SDL_LoadBMP("data/to.bmp");

	gFont16 = SDL_LoadBMP("data/font16x16.bmp");
	gFont8 = SDL_LoadBMP("data/font8x8.bmp");

	gGameOverSprite = SDL_LoadBMP("data/gameover.bmp");
	gWarningSprite = SDL_LoadBMP("data/warning.bmp");

	SDL_SetColorKey(gGameOverSprite, SDL_SRCCOLORKEY, SDL_MapRGB(gGameOverSprite->format, 255U, 0U, 255U));
	SDL_SetColorKey(gWarningSprite, SDL_SRCCOLORKEY, SDL_MapRGB(gWarningSprite->format, 255U, 0U, 255U));

	SDL_SetColorKey(gRedGerm100, SDL_SRCCOLORKEY, SDL_MapRGB(gRedGerm100->format, 255U, 0U, 255U));
	SDL_SetColorKey(gRedGerm75, SDL_SRCCOLORKEY, SDL_MapRGB(gRedGerm75->format, 255U, 0U, 255U));
	SDL_SetColorKey(gRedGerm50, SDL_SRCCOLORKEY, SDL_MapRGB(gRedGerm50->format, 255U, 0U, 255U));
	SDL_SetColorKey(gRedGerm25, SDL_SRCCOLORKEY, SDL_MapRGB(gRedGerm25->format, 255U, 0U, 255U));
	SDL_SetColorKey(gRedGerm0, SDL_SRCCOLORKEY, SDL_MapRGB(gRedGerm0->format, 255U, 0U, 255U));

	SDL_SetColorKey(gBlueGerm100, SDL_SRCCOLORKEY, SDL_MapRGB(gBlueGerm100->format, 255U, 0U, 255U));
	SDL_SetColorKey(gBlueGerm75, SDL_SRCCOLORKEY, SDL_MapRGB(gBlueGerm75->format, 255U, 0U, 255U));
	SDL_SetColorKey(gBlueGerm50, SDL_SRCCOLORKEY, SDL_MapRGB(gBlueGerm50->format, 255U, 0U, 255U));
	SDL_SetColorKey(gBlueGerm25, SDL_SRCCOLORKEY, SDL_MapRGB(gBlueGerm25->format, 255U, 0U, 255U));
	SDL_SetColorKey(gBlueGerm0, SDL_SRCCOLORKEY, SDL_MapRGB(gBlueGerm0->format, 255U, 0U, 255U));

	SDL_SetColorKey(gGreenGerm100, SDL_SRCCOLORKEY, SDL_MapRGB(gGreenGerm100->format, 255U, 0U, 255U));
	SDL_SetColorKey(gGreenGerm75, SDL_SRCCOLORKEY, SDL_MapRGB(gGreenGerm75->format, 255U, 0U, 255U));
	SDL_SetColorKey(gGreenGerm50, SDL_SRCCOLORKEY, SDL_MapRGB(gGreenGerm50->format, 255U, 0U, 255U));
	SDL_SetColorKey(gGreenGerm25, SDL_SRCCOLORKEY, SDL_MapRGB(gGreenGerm25->format, 255U, 0U, 255U));
	SDL_SetColorKey(gGreenGerm0, SDL_SRCCOLORKEY, SDL_MapRGB(gGreenGerm0->format, 255U, 0U, 255U));

	SDL_SetColorKey(gYellowGerm100, SDL_SRCCOLORKEY, SDL_MapRGB(gYellowGerm100->format, 255U, 0U, 255U));
	SDL_SetColorKey(gYellowGerm75, SDL_SRCCOLORKEY, SDL_MapRGB(gYellowGerm75->format, 255U, 0U, 255U));
	SDL_SetColorKey(gYellowGerm50, SDL_SRCCOLORKEY, SDL_MapRGB(gYellowGerm50->format, 255U, 0U, 255U));
	SDL_SetColorKey(gYellowGerm25, SDL_SRCCOLORKEY, SDL_MapRGB(gYellowGerm25->format, 255U, 0U, 255U));
	SDL_SetColorKey(gYellowGerm0, SDL_SRCCOLORKEY, SDL_MapRGB(gYellowGerm0->format, 255U, 0U, 255U));

	SDL_SetColorKey(gWhiteGerm100, SDL_SRCCOLORKEY, SDL_MapRGB(gWhiteGerm100->format, 255U, 0U, 255U));
	SDL_SetColorKey(gWhiteGerm75, SDL_SRCCOLORKEY, SDL_MapRGB(gWhiteGerm75->format, 255U, 0U, 255U));
	SDL_SetColorKey(gWhiteGerm50, SDL_SRCCOLORKEY, SDL_MapRGB(gWhiteGerm50->format, 255U, 0U, 255U));
	SDL_SetColorKey(gWhiteGerm25, SDL_SRCCOLORKEY, SDL_MapRGB(gWhiteGerm25->format, 255U, 0U, 255U));
	SDL_SetColorKey(gWhiteGerm0, SDL_SRCCOLORKEY, SDL_MapRGB(gWhiteGerm0->format, 255U, 0U, 255U));

	SDL_SetColorKey(gDiseasedGerm, SDL_SRCCOLORKEY, SDL_MapRGB(gDiseasedGerm->format, 255U, 0U, 255U));

	SDL_SetColorKey(gFrom, SDL_SRCCOLORKEY, SDL_MapRGB(gFrom->format, 255U, 0U, 255U));
	SDL_SetColorKey(gTo, SDL_SRCCOLORKEY, SDL_MapRGB(gTo->format, 255U, 0U, 255U));

	SDL_SetColorKey(gFont16, SDL_SRCCOLORKEY, SDL_MapRGB(gFont16->format, 255U, 0U, 255U));
	SDL_SetColorKey(gFont8, SDL_SRCCOLORKEY, SDL_MapRGB(gFont8->format, 255U, 0U, 255U));

	gPlayer.indicatorFrom = new Indicator;
	gPlayer.indicatorTo = new Indicator;

	gPlayer.indicatorFrom->sprite = gFrom;
	gPlayer.indicatorTo->sprite = gTo;


	for (int y = 1; y < PLAYAREA_HEIGHT - 1; ++y) {
		for (int x = PLAYAREA_LEFT + 1; x < PLAYAREA_RIGHT - 1; ++x) {
			gPlayArea[y][x].germ = newGerm();
		}
	}


	spawnGerm();
	spawnGerm();
	spawnGerm();
	spawnGerm();
	spawnGerm();
}

void spawnGerm()
{
	Mix_PlayChannel(-1, gSpawnSound, 0);

	// index being which side; 0 - left, 1 - right
	int index(WAIT_AREA_LEFT);
	int chance(rand() % 100);
	if (chance > 50)
		index = WAIT_AREA_RIGHT - 1;

	bool isSpace(false);
	int spaceRemaining = MAX_WAIT_AREA;
	for (int space = 0; space < MAX_WAIT_AREA; ++space) {
		--spaceRemaining;
		if (0 == gPlayArea[space][index].germ) {
			gPlayArea[space][index].germ = newGerm();
			isSpace = true;
			break;
		}
	}

	if (false == isSpace) { // try the other side...
		if (index == WAIT_AREA_LEFT)
			index = WAIT_AREA_RIGHT - 1;
		else
			index = WAIT_AREA_LEFT;

		for (int space = 0; space < MAX_WAIT_AREA; ++space) {
			--spaceRemaining;
			if (0 == gPlayArea[space][index].germ) {
				gPlayArea[space][index].germ = newGerm();
				isSpace = true;
				break;
			}
		}

		if (false == isSpace) { // still no room at the Inn, GAME OVER
			gGameOver = true;
			Mix_PlayChannel(-1, gGameOverSound, 0);
		}
	}

	if (spaceRemaining < MAX_WAIT_AREA/2) {
		gWarning = true;
		Mix_PlayChannel(-1, gWarningSound, 0);
	}
}

void drawTiles()
{
	for (int y = 0; y < PLAYAREA_HEIGHT; ++y) {
		for (int x = 0; x < PLAYAREA_WIDTH; ++x) {
			int posX = (OFFSET_X) + (64 * x);
			int posY = (OFFSET_Y) + (64 * y);
			if ((x == 0) || (x == PLAYAREA_WIDTH - 1))
				drawSprite(gWaitCell, posX, posY);
			else
				drawSprite(gCell, posX, posY);
			if (gPlayArea[y][x].germ) {
				drawGerm(gPlayArea[y][x].germ, posX, posY);
			}
		}
	}
}

void drawGerm(Germ* germ, const int x, const int y)
{
	SDL_Surface* sprite;
	if (germ->health <= 0) {
		germ->type = DISEASED;
		Mix_PlayChannel(-1, gDiseasedSound, 0);
	}

	switch(germ->type) {
		case RED:
			if (germ->health > 80)
				sprite = gRedGerm100;
			else if (germ->health > 60)
				sprite = gRedGerm75;
			else if (germ->health > 40)
				sprite = gRedGerm50;
			else if (germ->health > 20)
				sprite = gRedGerm25;
			else
				sprite = gRedGerm0;
			break;
		case YELLOW:
			if (germ->health > 80)
				sprite = gYellowGerm100;
			else if (germ->health > 60)
				sprite = gYellowGerm75;
			else if (germ->health > 40)
				sprite = gYellowGerm50;
			else if (germ->health > 20)
				sprite = gYellowGerm25;
			else
				sprite = gYellowGerm0;
			break;
		case WHITE:
			if (germ->health > 80)
				sprite = gWhiteGerm100;
			else if (germ->health > 60)
				sprite = gWhiteGerm75;
			else if (germ->health > 40)
				sprite = gWhiteGerm50;
			else if (germ->health > 20)
				sprite = gWhiteGerm25;
			else
				sprite = gWhiteGerm0;
			break;
		case BLUE:
			if (germ->health > 80)
				sprite = gBlueGerm100;
			else if (germ->health > 60)
				sprite = gBlueGerm75;
			else if (germ->health > 40)
				sprite = gBlueGerm50;
			else if (germ->health > 20)
				sprite = gBlueGerm25;
			else
				sprite = gBlueGerm0;
			break;
		case GREEN:
			if (germ->health > 80)
				sprite = gGreenGerm100;
			else if (germ->health > 60)
				sprite = gGreenGerm75;
			else if (germ->health > 40)
				sprite = gGreenGerm50;
			else if (germ->health > 20)
				sprite = gGreenGerm25;
			else
				sprite = gGreenGerm0;
			break;
		case DISEASED:
			sprite = gDiseasedGerm;
			break;
		default:
			break;
	}

	drawSprite(sprite, x, y);
}

void drawSprite(SDL_Surface* sprite, const int x, const int y)
{
	SDL_Rect position;
	position.x = x;
	position.y = y;
	position.w = sprite->w;
	position.h = sprite->h;

	SDL_Rect clip;
	clip.x = 0;
	clip.y = 0;
	clip.w = sprite->w;
	clip.h = sprite->h;

	SDL_BlitSurface(sprite, &clip, SDL_GetVideoSurface(), &position);
}

void cleanupTiles()
{
	for (int x = 0; x < PLAYAREA_WIDTH; ++x) {
		for (int y = 0; y < PLAYAREA_HEIGHT; ++y) {
			if (gPlayArea[y][x].germ) {
				delete gPlayArea[y][x].germ;
				gPlayArea[y][x].germ = 0;
			}
		}
	}
}

void drawIndicators()
{
	if (gPlayer.selectedGerm) {
		int posX = (OFFSET_X) + (64 * gPlayer.indicatorFrom->gridX);
		int posY = (OFFSET_Y) + (64 * gPlayer.indicatorFrom->gridY);
		drawSprite(gPlayer.indicatorFrom->sprite, posX, posY);
	}

	int posX = (OFFSET_X) + (64 * gPlayer.gridX);
	int posY = (OFFSET_Y) + (64 * gPlayer.gridY);
	drawSprite(gPlayer.indicatorTo->sprite, posX, posY);
}

void drawFonts()
{
	char scoreBuffer[50];
	sprintf(scoreBuffer, "SCORE: %d", gPlayer.score);
	writeText(gFont16, scoreBuffer, 16, 180, 400);

	char infectionBuffer[50];
	sprintf(infectionBuffer, "NEXT INFECTION: %d", gPlayer.timeTillNextInfection);
	writeText(gFont16, infectionBuffer, 16, 160, 40);

	if (gGameOver)
		drawSprite(gGameOverSprite, 160, 120);

	if (gWarning) {
		drawSprite(gWarningSprite, 160, 120);
		int deltaTicks((SDL_GetTicks() - gLastTicks) / 10);
		gWarningFlashTimer -= deltaTicks;
		if (gWarningFlashTimer <= 0) {
			gWarning = false;
			gWarningFlashTimer = 300;
		}
	}
}

void writeText(SDL_Surface* fontTex, const char* string, const int size, const int x, const int y)
{
	int len(strlen(string));
	for (int index = 0; index < len; ++index) {
		const char glyph(string[index]);
		SDL_Rect clip;
		clip.x = 0;
		clip.y = (glyph - 33) * size;
		clip.w = size;
		clip.h = size;

		SDL_Rect position;
		position.x = x + (index * size);
		position.y = y;
		position.w = size;
		position.h = size;
		SDL_BlitSurface(fontTex, &clip, gScreen, &position);
	}
}

Germ* newGerm()
{
	Germ* germ(new Germ);
	germ->health = 100;
	germ->timeTillNextHealthDrop = 1;

	const int chance(rand()%5);
	if (chance == 0)
		germ->type = RED;
	else if (chance == 1)
		germ->type = YELLOW;
	else if (chance == 2)
		germ->type = BLUE;
	else if (chance == 3)
		germ->type = GREEN;
	else
		germ->type = WHITE;

	return germ;
}

void checkGrid()
{
	for (int y = 0; y < PLAYAREA_HEIGHT; ++y) {
		for (int x = 0; x < PLAYAREA_WIDTH; ++x) {
			if (gPlayArea[y][x].germ) {
				Germ* germ(gPlayArea[y][x].germ);
				if (squaredGerms(germ, x, y))
					return;
			}
		}
	}
}

const bool squaredGerms(Germ* germ, const int x, const int y)
{
	int matched(0);
	const GermType type(germ->type);
	if (type == DISEASED)
		return false;

	Germ* matchedGerms[3];
	// check up, upleft, left
	if (y > 0) {
		if (gPlayArea[y-1][x].germ)
			if (gPlayArea[y-1][x].germ->type == type) {
				matchedGerms[matched] = gPlayArea[y-1][x].germ;
				matched++;
			}
		if (x > PLAYAREA_LEFT) {
			if (gPlayArea[y-1][x-1].germ)
				if (gPlayArea[y-1][x-1].germ->type == type) {
					matchedGerms[matched] = gPlayArea[y-1][x-1].germ;
					matched++;
				}
		}
	}
	if (x > PLAYAREA_LEFT) {
		if (gPlayArea[y][x-1].germ)
			if (gPlayArea[y][x-1].germ->type == type) {
				matchedGerms[matched] = gPlayArea[y][x-1].germ;
				matched++;
			}
	}
	if (matched != 3)
		matched = 0;

	// check up, upright, right
	if (matched == 0) {
		if (y > 0) {
			if (gPlayArea[y-1][x].germ)
				if (gPlayArea[y-1][x].germ->type == type) {
					matchedGerms[matched] = gPlayArea[y-1][x].germ;
					matched++;
				}
			if (x < PLAYAREA_RIGHT) {
				if (gPlayArea[y-1][x+1].germ)
					if (gPlayArea[y-1][x+1].germ->type == type) {
						matchedGerms[matched] = gPlayArea[y-1][x+1].germ;
						matched++;
					}
			}
		}
		if (x < PLAYAREA_RIGHT) {
			if (gPlayArea[y][x+1].germ)
				if (gPlayArea[y][x+1].germ->type == type) {
					matchedGerms[matched] = gPlayArea[y][x+1].germ;
					matched++;
				}
		}
		if (matched != 3)
			matched = 0;
	}

	// check down, downleft, left
	if (matched == 0) {
		if (y < PLAYAREA_HEIGHT - 1) {
			if (gPlayArea[y+1][x].germ)
				if (gPlayArea[y+1][x].germ->type == type) {
					matchedGerms[matched] = gPlayArea[y+1][x].germ;
					matched++;
				}
			if (x > PLAYAREA_LEFT) {
				if (gPlayArea[y+1][x-1].germ)
					if (gPlayArea[y+1][x-1].germ->type == type) {
						matchedGerms[matched] = gPlayArea[y+1][x-1].germ;
						matched++;
					}
			}
		}
		if (x > PLAYAREA_LEFT) {
			if (gPlayArea[y][x-1].germ)
				if (gPlayArea[y][x-1].germ->type == type) {
					matchedGerms[matched] = gPlayArea[y][x-1].germ;
					matched++;
				}
		}
		if (matched != 3)
			matched = 0;
	}

	// check down, downright, right
	if (matched == 0) {
		if (y < PLAYAREA_HEIGHT - 1) {
			if (gPlayArea[y+1][x].germ)
				if (gPlayArea[y+1][x].germ->type == type) {
					matchedGerms[matched] = gPlayArea[y+1][x].germ;
					matched++;
				}
			if (x < PLAYAREA_RIGHT) {
				if (gPlayArea[y+1][x+1].germ)
					if (gPlayArea[y+1][x+1].germ->type == type) {
						matchedGerms[matched] = gPlayArea[y+1][x+1].germ;
						matched++;
					}
			}
		}
		if (x < PLAYAREA_RIGHT) {
			if (gPlayArea[y][x+1].germ)
				if (gPlayArea[y][x+1].germ->type == type) {
					matchedGerms[matched] = gPlayArea[y][x+1].germ;
					matched++;
				}
		}
		if (matched != 3)
			matched = 0;
	}

	if (matched == 3) {
		int score = 0;
		for (int index = 0; index < 3; ++index)
			score += deleteGerm(matchedGerms[index]);

		score += deleteGerm(germ);
		score += type * 10;
		gPlayer.score += score;
		Mix_PlayChannel(-1, gDisappearSound, 0);
		return true;
	}

	return false;
}

void spreadInfection()
{
	int deltaTicks((SDL_GetTicks() - gLastTicks) / 10);
	gInfectionTimer -= deltaTicks;

	if (gInfectionTimer <= 0) {
		deltaTicks = 1;
		gInfectionTimer = 100 * gTimeMultiply;
	}
	else
		deltaTicks = 0;

	gPlayer.timeTillNextInfection -= deltaTicks;

	if (gPlayer.timeTillNextInfection <= 0) {
		gPlayer.timeTillNextInfection = 5 + (rand() % 5);
		spawnGerm();
		spawnGerm();
		spawnGerm();
	}

	for (int y = 0; y < PLAYAREA_HEIGHT; ++y) {
		for (int x = 0; x < PLAYAREA_WIDTH; ++x) {
			if (gPlayArea[y][x].germ) {
				Germ* germ(gPlayArea[y][x].germ);
				germ->timeTillNextHealthDrop -= deltaTicks;
				if (germ->timeTillNextHealthDrop <= 0) {
					germ->health -= 1;
					germ->timeTillNextHealthDrop = 1;
				}
				if (germ->type == DISEASED)
					spreadDisease(germ, x, y);
			}
		}
	}
}

void spreadDisease(Germ* germ, const int x, const int y)
{
	gDiseaseTimer -= 1;
	if (gDiseaseTimer > 0)
		return;

	if (y > 0) {
		if (gPlayArea[y-1][x].germ)
			gPlayArea[y-1][x].germ->health -= 1;
	}
	if (x > PLAYAREA_LEFT) {
		if (gPlayArea[y][x-1].germ)
			gPlayArea[y][x-1].germ->health -= 1;
	}
	if (x < PLAYAREA_RIGHT) {
		if (gPlayArea[y][x+1].germ)
			gPlayArea[y][x+1].germ->health -= 1;
	}
	if (y < PLAYAREA_HEIGHT - 1) {
		if (gPlayArea[y+1][x].germ)
			gPlayArea[y+1][x].germ->health -= 1;
	}

	gDiseaseTimer = 10;
}

void swapGerm(const int fromX, const int fromY, const int toX, const int toY)
{
	int deltaX(fromX - toX);
	int deltaY(fromY - toY);

	if (deltaX < 0)
		deltaX *= -1;
	if (deltaY < 0)
		deltaY *= -1;

	const int delta(deltaX + deltaY);
	if (delta == 1) {
		Germ* swapGerm(gPlayArea[toY][toX].germ);
		gPlayArea[toY][toX].germ = gPlayArea[fromY][fromX].germ;
		gPlayArea[fromY][fromX].germ = swapGerm;
		gPlayer.selectedGerm = false;
		Mix_PlayChannel(-1, gSwapSound, 0);
	}
}

const int deleteGerm(Germ* germ)
{
	if (0 == germ)
		return 0;

	for (int y = 0; y < PLAYAREA_HEIGHT; ++y) {
		for (int x = 0; x < PLAYAREA_WIDTH; ++x) {
			if (gPlayArea[y][x].germ == germ) {
				const int score(100 - gPlayArea[y][x].germ->health);
				delete gPlayArea[y][x].germ;
				gPlayArea[y][x].germ = 0;
				return score;
			}
		}
	}

	return 0;
}


