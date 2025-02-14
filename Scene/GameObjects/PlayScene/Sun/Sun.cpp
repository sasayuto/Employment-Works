#include "pch.h"
#include"Sun.h"
#include<random>
using namespace DirectX;

//初期ポジション
const DirectX::SimpleMath::Vector3 Sun::INITIAL_POSITION(1100, 600, 600);

//初期回転
const DirectX::SimpleMath::Quaternion Sun::INITIAL_ROTATE(
	DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(0),						//X回転
		DirectX::XMConvertToRadians(0),						//Y回転
		DirectX::XMConvertToRadians(225)						//Z回転
	)
);

const float Sun::SUNSET_TIME(4);						//日没時間	()
const float Sun::LIGHT_INTENSITY_LOWER_LIMIT(0.0f);		//光の下限	(0〜)
const float Sun::LIGHT_INTENSITY_UPPER_LIMIT(1);		//光の上限	(0〜)
const float Sun::SUNSHINE_HOURS(180.0f / 100.0f);				//日照時間	(m/s)



Sun::Sun() :
	m_position(SimpleMath::Vector3::Zero),
	m_pSupplyPointModel(nullptr),
	m_rotate(DirectX::SimpleMath::Quaternion::Identity),
	m_rightDirect(DirectX::SimpleMath::Vector3::Zero),
	m_objectsRight(0)
{
}

Sun::~Sun()
{

}

void Sun::Initialize()
{
	//平面に回転するクオータニオン
	//４５度起き上がらせたx方向ベクトル(太陽の光の方向ベクトル)
	m_rightDirect = SimpleMath::Vector3::Transform(SimpleMath::Vector3::UnitX,INITIAL_ROTATE);

	//太陽の位置を計算
	m_position = m_rightDirect * INITIAL_POSITION;

	m_objectsRight = m_rightDirect.y * 1.7320509f * SUNSET_TIME;
	if (m_objectsRight >= LIGHT_INTENSITY_UPPER_LIMIT)
		m_objectsRight = LIGHT_INTENSITY_UPPER_LIMIT;

	if (m_objectsRight <= LIGHT_INTENSITY_LOWER_LIMIT)
		m_objectsRight = LIGHT_INTENSITY_LOWER_LIMIT;

}

void Sun::Update(const float& elapsedTime)
{
	//平面に回転するクオータニオン
	DirectX::SimpleMath::Quaternion q;
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, XMConvertToRadians(elapsedTime * SUNSHINE_HOURS));
	m_rotate = q * m_rotate;

	//４５度起き上がらせたx方向ベクトル(太陽の光の方向ベクトル)
	m_rightDirect = SimpleMath::Vector3::Transform(SimpleMath::Vector3::UnitX,m_rotate * INITIAL_ROTATE);

	//太陽の位置を計算
	m_position = m_rightDirect * INITIAL_POSITION;

	m_objectsRight = m_rightDirect.y * 1.7320509f * SUNSET_TIME;
	if (m_objectsRight >= LIGHT_INTENSITY_UPPER_LIMIT)
		m_objectsRight = LIGHT_INTENSITY_UPPER_LIMIT;

	if (m_objectsRight <= LIGHT_INTENSITY_LOWER_LIMIT)
		m_objectsRight = LIGHT_INTENSITY_LOWER_LIMIT;


}

void Sun::Render()
{
	//スケーリング、位置調整、回転をさせる
}

void Sun::Finalize()
{
}
