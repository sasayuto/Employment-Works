//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "ImaseLib/DebugFont.h"
#include"ImaseLib/SceneManager.h"
#include"UserResources.h"
#include"Scene/GameObjects/ScoreCalculation/ScoreCalculation.h"
// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game() = default;

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;


public:
    // 画面モードを設定する関数（TRUE：フルスクリーン）
    void SetFullscreenState(BOOL value);

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

private:
    //画面モード（TRUE:フルスクリーン）
    BOOL m_fullscreen;	

    // 共通ステートへのポインタ
    std::unique_ptr<DirectX::CommonStates> m_states;

    //ユーザーリソースへのポインタ
    std::unique_ptr<UserResources> m_userResources;

    //ユーザーリソースへのポインタ
    std::unique_ptr<ScoreCalculation> m_scoreCalculation;

    //シーンマネージャーのポインタ
    std::unique_ptr<Imase::SceneManager<UserResources>> m_sceneManager;




    ///かり

    bool m_colliderSceneFlag;
    bool m_PlaySceneFlag;

    bool m_debugFontDrawFlag;
};
