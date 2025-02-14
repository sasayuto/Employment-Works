//--------------------------------------------------------------------------------------
// File: ChangeSoundOptionScene.h
//
// シーンの雛型に使用してください
//
//--------------------------------------------------------------------------------------
#pragma once
#include"../StateOptionScene.h"
class ChangeSoundOptionScene : public StateOptionScene::State
{
public:


	ChangeSoundOptionScene(StateOptionScene::FSM* fsm);
	~ChangeSoundOptionScene();

	// 初期化
	void Initialize() override;

	// 更新
	void Update(const float& elapsedTime) override;

	// 描画
	void Render() override;

	// 終了処理
	void Finalize() override;

	void Enter()override;
	void Exit() override;

	// デバイスに依存するリソースを作成する関数
	void CreateDeviceDependentResources() override;


public:

private:
	//
	StateOptionScene::FSM* m_fsm;

	// マウストラッカー
	DirectX::Mouse::ButtonStateTracker m_mstracker;

};

