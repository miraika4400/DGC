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
#include "destination.h"
#include "scene.h"

//******************************
// マクロ定義
//******************************
#define CAMERA_DISTANCE 1500       // カメラと目標の距離
#define HEIGHT_RATE 0.1f           // 高さを合わせるときの係数
#define THETA_DIFFERENCE D3DXToRadian(60) // シータとシータの目標値の差の最大

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
	m_fThetaDest = 0.0f;
	m_fPhi = 0.0f;
	m_fPhiDest = 0.0f;
	m_fAngle = 0.0f;
	m_bBackMirror = false;
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
	pCamera->m_nPlayerNum = nNmPlayer;

	pCamera->Init();
	
	return pCamera;
}

//******************************
// 初期化処理
//******************************
HRESULT CCamera::Init(void)
{
	// 変数の初期化
	m_posV = D3DXVECTOR3(0.0f, 100.0f, -500.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_fRad = CAMERA_DISTANCE;
	m_fTheta     = D3DXToRadian(-90);
	m_fThetaDest = D3DXToRadian(-90);
	m_fPhi     = D3DXToRadian(-70);
	m_fPhiDest = D3DXToRadian(-70);

	m_bBackMirror = false;

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
	/*m_fTheta -= CManager::GetMouse()->GetMouseMove().x / MOUSE_SENSI_RATE;
	m_fTheta -= CManager::GetJoypad()->GetStick(m_nNmPlayer).lX / JOYPAD_SENSI_RATE;*/

	// リストの先頭の取得
	CDestination*pDest = (CDestination*)CScene::GetTop(CScene::OBJTYPE_DESTINATION);

	while (pDest != NULL)
	{
		if (pDest->GetPlayerNum()==m_nPlayerNum)
		{
			// 注視点の設定
			m_posR = pDest->GetPos();
			// シータの目標値の設定
			m_fThetaDest = (-pDest->GetRot().y) + D3DXToRadian(-90);

			// シータの目標値の差の上限、下限
			if (m_fThetaDest - m_fTheta >= THETA_DIFFERENCE)
			{
				m_fTheta = m_fThetaDest + -THETA_DIFFERENCE;
			}
			if (m_fThetaDest - m_fTheta <= -THETA_DIFFERENCE)
			{
				 m_fTheta = m_fThetaDest + THETA_DIFFERENCE;
			}

			break;
		}

		// リストの次のポインタにする
		pDest = (CDestination*)pDest->GetNext();
	}

	//// 注視点をプレイヤーにする
	//m_posR = CGame::GetPlayer(m_nPlayerNum)->GetPos();
	
	// 横の回転
	m_fTheta += ((m_fThetaDest - m_fTheta))*HEIGHT_RATE;


	if (CManager::GetJoypad()->GetJoystickTrigger(0, m_nPlayerNum)|| CManager::GetJoypad()->GetJoystickPress(0, m_nPlayerNum))
	{
		m_fPhi = m_fPhiDest;
	}

	if (CManager::GetJoypad()->GetJoystickPress(0, m_nPlayerNum))
	{// バックミラーの処理

		// カメラとの距離の調整
		m_fRad = CAMERA_DISTANCE*0.7f;
		// 高さ
		m_fPhi += ((m_fPhiDest - m_fPhi))*HEIGHT_RATE;
		// バックミラーbool
		m_bBackMirror = true;
		// 球面座標の設定
		m_posV.x = m_posR.x + (m_fRad)* sinf(-m_fPhi)*cosf(m_fTheta);
		m_posV.y = m_posR.y + (m_fRad)* cosf(-m_fPhi);
		m_posV.z = m_posR.z + (m_fRad)* sinf(-m_fPhi)*sinf(m_fTheta);

		// カメラの向きの設定
		m_fAngle = atan2f(m_posV.z - m_posR.z, m_posV.x - m_posR.x);
	}
	else
	{
		// カメラとの距離の調整
		m_fRad = CAMERA_DISTANCE;
		// 高さ
		m_fPhi += ((m_fPhiDest - m_fPhi))*HEIGHT_RATE;
		// バックミラーbool
		m_bBackMirror = false;
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

	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(50.0f), 
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 1000000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 255, 0, 255), 1.0f, 0);

}
