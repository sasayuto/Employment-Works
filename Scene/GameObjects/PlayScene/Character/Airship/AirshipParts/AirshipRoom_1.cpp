#include "pch.h"
#include"AirshipRoom_1.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include<random>

const float AirshipRoom_01::FALL_SPEED_ACCELERATION	(0.12f / 60);	//落下の加速度			(m/s)
const float AirshipRoom_01::EXPLOSIVE_ROTATE			(120.0f / 60);	//モデルの回転の速さ	(°/s）
const float AirshipRoom_01::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//爆発の横のパワー		(m/s)
const float AirshipRoom_01::EXPLOSIVE_POWER(2.0f / 60);		//爆発の横のパワー		(m/s)

AirshipRoom_01::AirshipRoom_01(IAirshipComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	AirshipComponent(parent, position, angle)
{

	//モデルをセット
	SetPartModel(Resources::GetInstance()->GetAirshipRoomModel());
}

AirshipRoom_01::~AirshipRoom_01()
{

}

void AirshipRoom_01::Initialize()
{	
	//360度ランダムな方向を取得
	std::random_device seed;
	std::default_random_engine engine(seed());

	//ランダムな方向を作る
	std::uniform_real_distribution<> dist(0, 6.28f);
	float explosionSpeedX = static_cast<float>(dist(engine));

	//ランダムな回転をセット
	SetRandomRotate(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, explosionSpeedX));

	//キルの回転をセット
	SetKillRotate(GetRotate());

	//爆発力をランダムにする
	std::uniform_real_distribution<> power(5, 10);
	float explosionPower = static_cast<float>(power(engine)) / 60;

	//爆発力を重力に付ける
	SetGravity(-explosionPower);

	// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		playerPart->Initialize();
	}

	//当たり判定の初期化
	GetCollider()->Initialize(
		GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
		GetRotate(),
		GetPartModel()->meshes[0]->boundingBox.Extents
	);
}

void AirshipRoom_01::Update(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{	
	//モデル位置調整
	SetPosition(DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.2f, -6.2f, 20.5f), angle));

	//親の位置と合わせる
	SetPosition(position + GetPosition());

	//親の回転と合わせる
	SetRotate(angle);

	// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		playerPart->Update(GetPosition(), GetRotate());
	}

	//当たり判定の更新
	GetCollider()->Update(
		GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
		GetRotate()
		);
}

void AirshipRoom_01::Render()
{

	//スケーリング、位置調整、回転をさせる
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	// 飛行機の描画
	Draw::GetInstance()->ShadowMapRenderNoPicture(GetPartModel(), world);

		// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		playerPart->Render();
	}
}

void AirshipRoom_01::Explosion()
{
	using namespace DirectX;

	SimpleMath::Vector3 position = GetPosition();

	//ランダムな方向
	position += SimpleMath::Vector3::Transform(SimpleMath::Vector3(0, 0, EXPLOSIVE_RANDOM_POWER), GetRandomRotate());

	//破壊される方向に飛ばす
	position += SimpleMath::Vector3::Transform(SimpleMath::Vector3(0, 0, EXPLOSIVE_POWER), GetKillRotate());

	//重力をつける
	SetGravity(GetGravity() + FALL_SPEED_ACCELERATION);

	//キル座標に重力をつける
	position.y -= GetGravity();

	//爆発のクオータニオン回転
	SimpleMath::Quaternion q = SimpleMath::Quaternion::Identity;
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitX, XMConvertToRadians(EXPLOSIVE_ROTATE));
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, XMConvertToRadians(EXPLOSIVE_ROTATE));

	SetRotate(q * GetRotate());
	SetPosition(position);

	for (auto& playerPart : GetParts())
	{
		// パーツを更新する
		playerPart->Explosion();
	}

	//当たり判定の更新
	GetCollider()->Update(
		GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
		GetRotate()
	);

}

void AirshipRoom_01::Finalize()
{
}

void AirshipRoom_01::Speed()
{
	// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		playerPart->Speed();
	}
}


