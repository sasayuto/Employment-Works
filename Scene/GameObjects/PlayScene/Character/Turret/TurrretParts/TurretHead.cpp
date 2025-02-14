#include "pch.h"
#include"TurretHead.h"
#include"TurretPartFactory.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include<random>

const float TurretHead::FALL_SPEED_ACCELERATION	(0.12f / 60);	//落下の加速度			(m/s)
const float TurretHead::EXPLOSIVE_ROTATE			(120.0f / 60);	//モデルの回転の速さ	(°/s）
const float TurretHead::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//爆発の横のパワー		(m/s)
const float TurretHead::EXPLOSIVE_POWER(2.0f / 60);		//爆発の横のパワー		(m/s)
const int TurretHead::MAX_HP(5000);	//HP


TurretHead::TurretHead(BulletManager* bulletManager,
	ITurretComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	TurretComponent(
		bulletManager,
		parent,
		position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0, 14.67f, -1.4f), angle),
		angle
	),
	m_headAngle(DirectX::SimpleMath::Quaternion::Identity)
{

	//モデルをセット
	SetPartModel(Resources::GetInstance()->GetTurretHeadModel());
	AddPart(TurretPartFactory::CreateTurretCancer_Middle(bulletManager, this, GetPosition(), GetRotate()));
	AddPart(TurretPartFactory::CreateTurretCancer_Right(bulletManager, this, GetPosition(), GetRotate()));
	AddPart(TurretPartFactory::CreateTurretCancer_Left(bulletManager, this, GetPosition(), GetRotate()));
	//当たり判定の初期化
	//注意ADDをした順番を当たり判定を更新するときに使うので覚えておいて
	GetCollider()->AddCollider(
		Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
			GetPosition(),
			GetRotate(),
			DirectX::SimpleMath::Vector3::Zero,
			DirectX::SimpleMath::Quaternion::Identity,
			GetPartModel()->meshes[0]->boundingBox.Extents
		)
	);
	GetCollider()->AddCollider(
		Collider::MultipleHitDeterminationFactory::CreateSphereCollider(
			GetPosition(),
			DirectX::SimpleMath::Vector3(0, -5, 0),
			14
		)
	);

}

TurretHead::~TurretHead()
{

}

void TurretHead::Initialize()
{
	//360度ランダムな方向を取得
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::uniform_real_distribution<> dist(0, 6.28f);
	float explosionSpeedX = static_cast<float>(dist(engine));

	//ランダムな回転をセット
	SetRandomRotate(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, explosionSpeedX));
	
	//HPをセット
	SetHp(MAX_HP);
	//爆発力をランダムにする
	std::uniform_real_distribution<> power(5, 10);
	float explosionPower = static_cast<float>(power(engine)) / 60;

	//爆発力を重力に付ける
	SetGravity(-explosionPower);

	//生きてる状態にする
	SetSurvival(true);

	//timerを初期化
	SetTimer(0.0f);

	////当たり判定の初期化
	//GetCollider()->Initialize(
	//	GetPosition(),
	//	GetRotate(),
	//	GetPartModel()->meshes[0]->boundingBox.Extents
	//);

	// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		playerPart->Initialize();
	}
	m_AngleSpeed = 0;
}

void TurretHead::Update(const float& elapsedTime, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//HPが０以下だったら殺す
	if (GetHp() < 0.0f)
		SetSurvival(false);

	//親が動かないから更新しない//
	//親の位置と合わせる
	SetPosition(position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0, 14.67f, -1.4f), angle));
	
	m_AngleSpeed += 0.001f;
	m_AngleSpeed *= 0.99f;
	//頭のX軸回転を作る
	DirectX::SimpleMath::Quaternion headAngleX =
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
			DirectX::SimpleMath::Vector3::UnitY,
			DirectX::XMConvertToRadians(m_AngleSpeed)
		);
	m_headAngle = headAngleX * m_headAngle;

	//親の回転と合わせる
	SetRotate(m_headAngle * angle);

	//当たり判定の更新
	GetCollider()->AllUpdate(
		GetPosition(),
		GetRotate()
	);

	// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		if (playerPart->GetSurvival())	playerPart->Update(elapsedTime, GetPosition(), GetRotate());
		else							playerPart->Explosion(elapsedTime);
	}
}
void TurretHead::Explosion(const float& elapsedTime)
{
	//アニメーションを超えたら更新しない
	if (GetTimer() >= Bench::ANIMATION_TIME)
		return;

	//時間を計測
	SetTimer(GetTimer() + elapsedTime);

	DirectX::SimpleMath::Vector3 position = GetPosition();

	//ランダムな方向
	position += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0, 0, EXPLOSIVE_RANDOM_POWER), GetRandomRotate());

	////破壊される方向に飛ばす(反射ベクトル)
	//position += -GetReflectionVector() * EXPLOSIVE_POWER;

	//重力をつける
	SetGravity(GetGravity() + FALL_SPEED_ACCELERATION);

	//キル座標に重力をつける
	position.y -= GetGravity();

	//爆発のクオータニオン回転
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::Identity;
	q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(EXPLOSIVE_ROTATE));
	q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(EXPLOSIVE_ROTATE));

	SetRotate(q * GetRotate());
	SetPosition(position);

	//当たり判定の更新
	GetCollider()->AllUpdate(
		GetPosition(),
		GetRotate()
	);
	// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		playerPart->Explosion(elapsedTime);
	}
}

void TurretHead::Render()
{
	//アニメーションを超えたら描画しない
	if (GetTimer() >= Bench::ANIMATION_TIME)
		return;

	//スケーリング、位置調整、回転をさせる
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

	// 飛行機の描画
	Draw::GetInstance()->Render(GetPartModel(), world);
	GetCollider()->Render(GetRotate());
	// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		playerPart->Render();
	}
}


void TurretHead::Finalize()
{
}