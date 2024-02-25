#pragma once
#include "SDL/SDL.h"
#include <unordered_map>
#include <string>
#include <vector>

class Game{
public :
	enum GameState {
		State_Start,
		State_Playing,
		State_End
	};
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName);

	void AddAsteroid(class Asteroid* ast);
	void RemoveAsteroid(class Asteroid* ast);
	std::vector<class Asteroid*>& GetAsteroids() { return mAsteroids; }
	void SetPlayerAsteroid(class Player_Asteroid* ast);
	Player_Asteroid& GetPlayerAsteroid() { return *mPAsteroid; }

	int GetGameState() const { return mState; }
	void SetGameState(int state) { mState = state; }

	void GameBegin();
	void GamePlaying();
	void GameEnd();

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	bool mUpdatingActors;
	float mTimer;

	std::unordered_map<std::string, SDL_Texture*> mTextures;
	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;
	std::vector<class SpriteComponent*> mSprites;
	class Ship* mShip;
	class Player_Asteroid* mPAsteroid;
	std::vector<class Asteroid*> mAsteroids;
	float mGenerateFlex;
	int mBrokeCount;
	int mLevelUpCount;
	int mState;
};