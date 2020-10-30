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

		// �Ō�ɂЂ�����Ԃ郂�[�V�����������邽�߂̎���
		if (timer->GetSecondsElapsedTime() >= 2)
		{
			// �����ŃQ�[�����I��������Ƃ�`����
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
		// ��������
	}
}

void GameManager::Drow()
{
	system->Draw(*manager);
	// �I�Z���̐΂̕`��
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
