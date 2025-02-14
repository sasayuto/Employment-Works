﻿//--------------------------------------------------------------------------------------
// File: DebugFont.h
//
// デバッグ用文字フォント描画クラス
//
// Usage: DebugFontクラスは2D版、DebugFont3Dクラスは3D版です。
//        AddString関数で文字列を登録します。登録された情報は描画後クリアされます。
//        デバッグ用の文字列の表示などに使用してください。
//		  ※デバッグ用なので深度バッファはみていません。（必ず描画される）
//
// Date: 2023.3.13
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include <vector>
#include <string>
#include "SimpleMath.h"
#include "CommonStates.h"
#include "Effects.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"

class SingletonDebugFont
{
private:

	// 文字列情報
	struct String
	{
		// 位置
		DirectX::SimpleMath::Vector2 pos;

		// 文字列
		std::wstring string;

		// 色
		DirectX::SimpleMath::Color color;

		// スケール
		float scale = 1.0f;
	};

	// 表示文字列の配列
	std::vector<String> m_strings;

	// 表示文字列の配列
	static std::unique_ptr<SingletonDebugFont> m_SingletonDebugFont;


protected:

	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	// スプライトフォント
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;

	// フォントの縦サイズ
	float m_fontHeight;

public:


	/// <summary>
	/// Resoucesクラスのインスタンスを取得する
	/// </summary>
	/// <returns>Resoucesクラスのインスタンス</returns>
	static SingletonDebugFont* GetInstance();

	// コンストラクタ
	SingletonDebugFont();

	// デストラクタ
	virtual ~SingletonDebugFont();

	// 描画する文字列を登録する関数
	void AddString(
		const wchar_t* string,
		DirectX::SimpleMath::Vector2 pos,
		DirectX::FXMVECTOR color = DirectX::Colors::White,
		float scale = 1.0f);

	// 描画関数
	void Initialize(ID3D11Device* device, ID3D11DeviceContext* context, wchar_t const* fileName);

	// 描画関数
	void Render(DirectX::CommonStates* states);

	// フォントの高さを取得する関数
	float GetFontHeight() { return m_fontHeight; }
};

class SingletonDebugFont3D : protected SingletonDebugFont
{
private:

	// 文字列情報
	struct String
	{
		// 位置
		DirectX::SimpleMath::Vector3 pos;

		// 文字列
		std::wstring string;

		// 色
		DirectX::SimpleMath::Color color;

		// スケール
		float scale = 1.0f;
	};

	// 表示文字列の配列
	std::vector<String> m_strings;

	// エフェクト
	std::unique_ptr<DirectX::BasicEffect> m_effect;

	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

public:

	// コンストラクタ
	SingletonDebugFont3D(
		ID3D11Device* device,
		ID3D11DeviceContext* context,
		wchar_t const* fileName);

	// デストラクタ
	~SingletonDebugFont3D();

	// 描画する文字列を登録する関数
	void AddString(
		const wchar_t* string,
		DirectX::SimpleMath::Vector3 pos,
		DirectX::FXMVECTOR color = DirectX::Colors::White,
		float scale = 1.0f);

	// 描画関数
	void Render(
		ID3D11DeviceContext* context,
		DirectX::CommonStates* states,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj);

	// フォントの高さを取得する関数
	float GetFontHeight() { return m_fontHeight; }
};

