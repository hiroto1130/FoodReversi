#include "GameManager.h"

void GameManager::Update()
{
}

void GameManager::Drow()
{
	manager->Draw();
}

void GameManager::Initialize()
{
	manager = new CellManager();
}

void GameManager::Delete()
{
	delete manager;
}
