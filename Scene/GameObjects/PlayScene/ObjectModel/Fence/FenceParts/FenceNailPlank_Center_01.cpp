#include "pch.h"
#include"FenceNailPlank_Center_01.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"FencePartFactory.h"
#include<random>

const float FenceNailPlank_Center_01::FALL_SPEED_ACCELERATION	(0.18f / 60);	//落下の加速度			(m/s)
const float FenceNailPlank_Center_01::EXPLOSIVE_ROTATE			(50.0f / 60);	//モデルの回転の速さ	(°/s）
const float FenceNailPlank_Center_01::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//爆発の横のパワー		(m/s)
const float FenceNailPlank_Center_01::EXPLOSIVE_POWER(2.0f / 60);		//爆発の横のパワー		(m/s)

FenceNailPlank_Center_01::FenceNailPlank_Center_01(IMoveObjectsComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	MoveObjectsComponent(
		parent,
		DirectX::SimpleMath::Vector3(3.33f, -0.4f, 0.28f),
		position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(2.4f, 4, 0), angle),
		angle,
		FALL_SPEED_ACCELERATION,
		EXPLOSIVE_ROTATE,
		EXPLOSIVE_RANDOM_POWER,
		EXPLOSIVE_POWER
	)
{
	//モデルをセット
	SetPartModel(Resources::GetInstance()->GetFenceNailPlank_Center_01Model());
}

const float FenceNailPlank_Center_02::FALL_SPEED_ACCELERATION(0.18f / 60);	//落下の加速度			(m/s)
const float FenceNailPlank_Center_02::EXPLOSIVE_ROTATE(50.0f / 60);	//モデルの回転の速さ	(°/s）
const float FenceNailPlank_Center_02::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//爆発の横のパワー		(m/s)
const float FenceNailPlank_Center_02::EXPLOSIVE_POWER(2.0f / 60);		//爆発の横のパワー		(m/s)

FenceNailPlank_Center_02::FenceNailPlank_Center_02(IMoveObjectsComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	MoveObjectsComponent(
		parent,
		DirectX::SimpleMath::Vector3(3.3f, -0.4f, 0.28f),
		position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(2.4f, 4, 0), angle),
		angle,
		FALL_SPEED_ACCELERATION,
		EXPLOSIVE_ROTATE,
		EXPLOSIVE_RANDOM_POWER,
		EXPLOSIVE_POWER
	)
{
	//モデルをセット
	SetPartModel(Resources::GetInstance()->GetFenceNailPlank_Center_02Model());
}
const float FenceNailPlank_Center_03::FALL_SPEED_ACCELERATION(0.18f / 60);	//落下の加速度			(m/s)
const float FenceNailPlank_Center_03::EXPLOSIVE_ROTATE(50.0f / 60);	//モデルの回転の速さ	(°/s）
const float FenceNailPlank_Center_03::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//爆発の横のパワー		(m/s)
const float FenceNailPlank_Center_03::EXPLOSIVE_POWER(2.0f / 60);		//爆発の横のパワー		(m/s)


FenceNailPlank_Center_03::FenceNailPlank_Center_03(IMoveObjectsComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	MoveObjectsComponent(
		parent,
		DirectX::SimpleMath::Vector3(3.05f, -1.4f, 0.28f),
		position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(2.4f, 4, 0), angle),
		angle,
		FALL_SPEED_ACCELERATION,
		EXPLOSIVE_ROTATE,
		EXPLOSIVE_RANDOM_POWER,
		EXPLOSIVE_POWER
	)
{
	//モデルをセット
	SetPartModel(Resources::GetInstance()->GetFenceNailPlank_Center_03Model());
}
