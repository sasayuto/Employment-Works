#pragma once
#include "StepTimer.h"

// IPlayerStateインターフェイスを定義する 
class IState
{
public:
	/// <summary>
	/// 初期化する
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// 処理を実行する
	/// </summary>
	/// <param name="elapsedTime">フレーム時間</param>
	virtual void Update(const float& elapsedTime) = 0;

	/// <summary>
	/// 描画する
	/// </summary>
	virtual void Render() = 0;

	/// <summary>
	/// 後始末をする
	/// </summary>
	virtual void Finalize() = 0;

		/// <summary>
	/// 後始末をする
	/// </summary>
	virtual void Motion(const float& elapsedTime) = 0;

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~IState() = default;
};
