////////////////////////////////////////////////////
//
//    カメラクラスの処理[camera.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "mouse.h"
#include "joypad.h"

//******************************
// マクロ定義
//******************************
#define CAMERA_DISTANCE 1000       // カメラと目標の距離
#define MOSE_SENSI_RATE 100.0f     // カメラのマウス感度
#define JOYPAD_SENSI_RATE 10000.0f // コントローラーのスティックの感度
//******************************
// 静的メンバ変数宣言
//******************************

//******************************
// コンストラクタ
//******************************
CCamera::CCamera()
{
	// 変数のクリア
	m_posV = VEC3_ZERO;
	m_posR = VEC3_ZERO;
	m_vecU = VEC3_ZERO;
	D3DXMatrixIdentity(&m_mtxProjection);
	D3DXMatrixIdentity(&m_mtxView);
	m_fRad = 0.0f;
	m_fTheta = 0.0f;
	m_fPhi = 0.0f;
	m_fAngle = 0.0f;
}

//******************************
// デストラクタ
//******************************
CCamera::~CCamera()
{
}

//******************************
// クリエイト
//******************************
CCamera * CCamera::Create(int nNmPlayer)
{

	CCamera *pCamera = new CCamera;
	
	// プレイヤー番号の取得
	pCamera->m_nNmPlayer = nNmPlayer;

	pCamera->Init();
	
	return pCamera;
}

//******************************
// 初期化処理
//******************************
HRESULT CCamera::Init(void)
{


	m_posV = D3DXVECTOR3(0.0f, 100.0f, -500.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_fRad = CAMERA_DISTANCE;
	m_fTheta = D3DXToRadian(-90);
	m_fPhi = D3DXToRadian(-70);

	// 球面座標の設定
	m_posV.x = m_posR.x + (m_fRad)* sinf(m_fPhi)*cosf(m_fTheta);
	m_posV.y = m_posR.y + (m_fRad)* cosf(m_fPhi);
	m_posV.z = m_posR.z + (m_fRad)* sinf(m_fPhi)*sinf(m_fTheta);

	// カメラの向き
	m_fAngle = atan2f(m_posR.y - m_posV.y, m_posR.y - m_posV.y);

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CCamera::Uninit(void)
{
}

//******************************
// 更新処理
//******************************
void CCamera::Update(void)
{
	// マウスでカメラ操作
	//m_fPhi += CManager::GetMouse()->GetMouseMove().y / 100.0f;
	m_fTheta -= CManager::GetMouse()->GetMouseMove().x / MOSE_SENSI_RATE;
	m_fTheta -= CManager::GetJoypad()->GetStick(m_nNmPlayer).lX / JOYPAD_SENSI_RATE;

	// 注視点をプレイヤーにする
	m_posR = CGame::GetPlayer(m_nNmPlayer)->GetPos();

	if (CManager::GetJoypad()->GetJoystickPress(0, m_nNmPlayer))
	{// バックミラーの処理

		// 球面座標の設定
		m_posV.x = m_posR.x + (m_fRad)* sinf(-m_fPhi)*cosf(m_fTheta);
		m_posV.y = m_posR.y + (m_fRad)* cosf(-m_fPhi);
		m_posV.z = m_posR.z + (m_fRad)* sinf(-m_fPhi)*sinf(m_fTheta);

		// カメラの向きの設定
		m_fAngle = atan2f(m_posV.z - m_posR.z, m_posV.x - m_posR.x);
	}
	else
	{
		// 球面座標の設定
		m_posV.x = m_posR.x + (m_fRad)* sinf(m_fPhi)*cosf(m_fTheta);
		m_posV.y = m_posR.y + (m_fRad)* cosf(m_fPhi);
		m_posV.z = m_posR.z + (m_fRad)* sinf(m_fPhi)*sinf(m_fTheta);

		// カメラの向きの設定
		m_fAngle = atan2f(m_posR.z - m_posV.z, m_posR.x - m_posV.x);
	}
	

}

//******************************
// カメラのセット
//******************************
void CCamera::SetCamera(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIXA16 matWorld;

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);
	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクトマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	int nPlayerNum = CGame::GetPlayerNum();
	float fWidth = CManager::GetRenderer()->GetViewPort(0).Width;
	float fHeight = CManager::GetRenderer()->GetViewPort(0).Height;


		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
			D3DXToRadian(60.0f),
			fWidth / fHeight, 10.0f, 1000000.0f);


	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}
