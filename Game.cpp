#include "Game.h"
#include "SDL/SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "Ship.h"
#include "SpriteComponent.h"
#include "BGSpriteComponent.h"
#include "Random.h"
#include "Asteroid.h"

Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mTicksCount(0)
,mIsRunning(true)
,mUpdatingActors(false)
,mTimer(0.0f)
,mGenerateFlex(1.5f)
,mBrokeCount(0)
,mLevelUpCount(10)
{

}


bool Game::Initialize() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		SDL_Log("Unable to initialize SDL: $s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Chapter03", 100, 100, 1024, 768, 0);

	if (!mWindow) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		SDL_Log("Failed to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	LoadData();

	mTicksCount = SDL_GetTicks();
	mTimer = 0.0f;

	return true;
}

void Game::RunLoop() {
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown() {
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::ProcessInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}

	mUpdatingActors = true;
	for (auto actor : mActors) {
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;
}

void Game::UpdateGame() {
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16)) {
		;
	}

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}
	mTimer += deltaTime;
	mTicksCount = SDL_GetTicks();

	if (mBrokeCount >= mLevelUpCount) {
		mGenerateFlex -= 0.05f;
		if (mGenerateFlex < 0.02f) {
			mGenerateFlex = 0.02f;
		}
		mBrokeCount = 0;
		mLevelUpCount *= 1.1f;
	}
	if (mTimer >= mGenerateFlex) {
		new Asteroid(this);
		mTimer = 0.0f;
	}

	mUpdatingActors = true;
	for (auto actor : mActors) {
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;
	for (auto pending : mPendingActors) {
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	std::vector<Actor*> deadActors;
	for (auto actor : mActors) {
		if (actor->GetState() == Actor::EDead) {
			deadActors.emplace_back(actor);
		}
	}

	for (auto actor : deadActors) {
		delete actor;
		mBrokeCount++;
	}
}

void Game::GenerateOutput() {
	SDL_SetRenderDrawColor(mRenderer, 46, 139, 87, 255);
	SDL_RenderClear(mRenderer);
	for (auto sprite : mSprites) {
		sprite->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}

SDL_Texture* Game::GetTexture(const std::string& fileName) {
	SDL_Texture* tex = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end()) {
		tex = iter->second;
	}
	else {
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf) {
			SDL_Log("Failed to load texture file: %s", SDL_GetError());
			return nullptr;
		}
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex) {
			SDL_Log("Failed to convert surface to texture for: %s", SDL_GetError());
			return nullptr;
		}
		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}

void Game::LoadData() {
	mShip = new Ship(this);
	mShip->SetPosition(Vector2(512.0f, 768.0f-30.0f));
	mShip->SetRotation(Math::PiOver2);
	mShip->SetScale(Math::PiOver2/2);
	/*
	const int numAsterois = 20;
	for (int i = 0; i < numAsterois; i++) {
		new Asteroid(this);
	}*/
}

void Game::UnloadData() {
	while (!mActors.empty()) {
		delete mActors.back();
	}

	for (auto i : mTextures) {
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}


void Game::AddActor(Actor* actor) {
	if (mUpdatingActors) {
		mPendingActors.emplace_back(actor);
	}
	else {
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor) {
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end()) {
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end()) {
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}
void Game::AddSprite(SpriteComponent* sprite) {
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter) {
		if (myDrawOrder < (*iter)->GetDrawOrder()) {
			break;
		}
	}

	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite) {
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void Game::AddAsteroid(Asteroid* ast) {
	mAsteroids.emplace_back(ast);
}

void Game::RemoveAsteroid(Asteroid* ast) {
	auto iter = std::find(mAsteroids.begin(), mAsteroids.end(), ast);
	if (iter != mAsteroids.end()) {
		mAsteroids.erase(iter);
	}
}