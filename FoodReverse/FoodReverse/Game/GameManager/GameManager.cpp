#include "GameManager.h"

void GameManager::Update(Library::Key& key)
{
	system->Update(key, *manager, *ui,is_pass);
	
	if (system->IsEndGame(*manager) == false)
	{
		timer->TimerReset();
		ui->SetStoneCount(system->StoneCounter(*manager));
	}
	else
	{
		is_pass = false;

		// ÅŒã‚É‚Ð‚Á‚­‚è•Ô‚éƒ‚[ƒVƒ‡ƒ“‚ðŒ©‚¹‚é‚½‚ß‚ÌŽžŠÔ
		if (timer->GetSecondsElapsedTime() >= 2)
		{
			// ‚±‚±‚ÅƒQ[ƒ€‚ªI‚í‚Á‚½‚±‚Æ‚ð“`‚¦‚é
			IsGameEnd = true;

			save->SetLastFiled(*manager);
			WinnerDistinction();
		}
	}

	ui->Update();
}

void GameManager::WinnerDistinction()
{
	StoneCount count = system->StoneCounter(*manager);

	if (count.black_ > count.white_)
	{
		save->SetWinner(Player::Player_1);
	}
	else if(count.black_ < count.white_)
	{
		save->SetWinner(Player::Player_2);
	}
	else if(count.white_ == count.black_)
	{
		// ˆø‚«•ª‚¯
	}
}

void GameManager::Drow()
{
	system->Draw(*manager);
	// ƒIƒZƒ‚ÌÎ‚Ì•`‰æ
	manager->Draw();

	ui->Draw(is_pass);
}

void GameManager::Initialize()
{
	manager = new CellManager();
	system = new GameSystem(*manager);
	ui = new Ui();

	timer = new Timer();
	save = &Save::get_instance();
}

void GameManager::Delete()
{
	save->SetLastFiled(*manager);

	delete manager;
	delete system;
	delete ui;

	delete timer;
}
