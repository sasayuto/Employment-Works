#pragma once
#include"CrabRobot.h"

class BulletManager;
class Player;
class AirshipManager;
class Floor;
class SandstormManager;

/// <summary>
/// 蟹ロボットの管理者のクラスを定義する
/// </summary>
class CrabRobotManager
{
public:
	//キル数のゲッター、セッター
	unsigned int GetKillCount() const { return m_killCount; }
	void SetKillCount(const unsigned int& killCount) { m_killCount = killCount; }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CrabRobotManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CrabRobotManager();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="bulletManager">球の管理者のアドレス</param>
	/// <param name="airshipManager">飛行船の管理者のアドレス</param>
	/// <param name="floor">床のアドレス</param>
	/// <param name="sandstormManager">砂嵐のアドレス</param>
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
	std::vector<std::unique_ptr<CrabRobot>> m_crabRobotList;

	//キル数
	unsigned int m_killCount;

	//生成時間
	float m_generationTime;
};