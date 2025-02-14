#pragma once
#include"Turret.h"

class BulletManager;
class Player;
class AirshipManager;
class Floor;
class SandstormManager;

//敵の管理者のクラスを定義する
class TurretManager
{
public:
	//キル数のゲッター、セッター
	unsigned int GetKillCount() const { return m_killCount; }
	void SetKillCount(const unsigned int& killCount) { m_killCount = killCount; }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TurretManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TurretManager();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="bulletManager">球のアドレス</param>
	/// 
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="bulletManager">球のアドレス</param>
	/// <param name="airhhipManager">飛行船の管理者のアドレス</param>
	/// <param name="floor">床のアドレス</param>
	/// <param name="sandstormManager">砂嵐の管理者のアドレス</param>
	void Intialize(
		BulletManager* bulletManager, 
		AirshipManager* airhhipManager = nullptr,
		Floor* floor =nullptr,
		SandstormManager* sandstormManager =nullptr
	);

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="elapsedTime">フレーム時間</param>
	void Update(const float& elapsedTime);

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize();

	/// <summary>
	/// プレイヤーと当たり判定
	/// </summary>
	/// <param name="player">プレイヤーのアドレス</param>
	void CheckHitCharacter(Player* player);

	/// <summary>
	/// 自動生成
	/// </summary>
	void AutoGenerated();

private:
	//敵の配列のポインタ
	std::vector<std::unique_ptr<Turret>> m_turretList;

	//キル数
	unsigned int m_killCount;

	//生成時間
	float m_generationTime;
};