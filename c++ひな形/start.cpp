////////////////////////////////////////////////////
//
//    Startクラスの処理[Start.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "Start.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "player.h"

#include <time.h>

//*****************************
// マクロ定義
//*****************************

// 座標
#define POS_EASY   D3DXVECTOR3(0.0f,0.0f,0.0f) // イージー
#define POS_NORMAL D3DXVECTOR3(0.0f,0.0f,0.0f) // ノーマル
#define POS_HARD   D3DXVECTOR3(0.0f,0.0f,0.0f) // ハード

#define SIZE  D3DXVECTOR3(50.0f,50.0f,0.0f) 

#define MAX_ANIMATION_X 4      // アニメーション数 横
#define MAX_ANIMATION_Y 1      // アニメーション数 縦

#define TEXTURE_PATH "./data/Textures/start_count.png"    //テクスチャのパス

//******************************
// 静的メンバ変数宣言
//******************************
LPDIRECT3DTEXTURE9  CStart::m_pTexture = NULL; // テクスチャポインタ
 
//******************************
// コンストラクタ
//******************************
CStart::CStart() :CScene3d(OBJTYPE_UI)
{
	m_type = CCourse::COURSE_EASY;
	m_nCntAnim = 0;
	m_nAnimX = 0;
	m_nAnimY = 0;
	m_currentTime = 0;
}

//******************************
// デストラクタ
//******************************
CStart::~CStart()
{
}

//******************************
// クリエイト
//******************************
CStart * CStart::Create(CCourse::COURSETYPE type)
{
	// メモリの確保
	CStart *pStart;
	pStart = new CStart;

	// タイプの設定
	pStart->m_type = type;
	// 初期化
	pStart->Init();

	return pStart;
}

//******************************
// テクスチャのロード
//******************************
HRESULT CStart::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH, &m_pTexture);

	return S_OK;
}

//******************************
// テクスチャのアンロード
//******************************
void CStart::Unload(void)
{

	// テクスチャの解放処理
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}


//******************************
// 初期化処理
//******************************
HRESULT CStart::Init(void)
{
	if (FAILED(CScene3d::Init()))
	{
		return E_FAIL;
	}

	// コースにっよって位置の分岐
	switch (m_type)
	{
	case CCourse::COURSE_EASY:
		// イージーコース
		SetPos(POS_EASY);
		break;
	case CCourse::COURSE_NORMAL:
		// ノーマルコース
		SetPos(POS_NORMAL);
		break;
	case CCourse::COURSE_HARD:
		// ハードコース
		SetPos(POS_HARD);
		break;
	default:
		break;
	}

	// サイズの設定
	SetSize(SIZE);

	// テクスチャ割り当て
	BindTexture(m_pTexture);

	// 開始時間を入れる
	m_currentTime = timeGetTime();

	// テクスチャUV座標の初期化
	m_nAnimX = 0;
	m_nAnimY = 0;

	// UV座標の設定
	D3DXVECTOR2 uv[NUM_VERTEX];
	float fu = 1.0f / MAX_ANIMATION_X;
	float fv = 1.0f / MAX_ANIMATION_Y;

	uv[0] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY);
	uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY);
	uv[2] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY + fv);
	uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY + fv);

	// UV座標セット
	SetTextureUV(uv);


	return S_OK;
}

//******************************
// 終了処理
//******************************
void CStart::Uninit(void)
{

	CScene3d::Uninit();
}

//******************************
// 更新処理
//******************************
void CStart::Update(void)
{
	// アニメーションが最大未満の時
	if (m_nAnimX + 1 < MAX_ANIMATION_X)
	{
		// 今時間の取得
		DWORD nowTime = timeGetTime();

		// 前回記憶した時間との差を算出
		int nTime = nowTime - m_currentTime;

		// 差が1秒（msec）を超えてたら
		if (nTime >= 1000)
		{
			// 前回記憶したタイムの更新
			m_currentTime = nowTime;

			// アニメーションを進める
			m_nAnimX++;

			// UV座標の設定
			D3DXVECTOR2 uv[NUM_VERTEX];
			float fu = 1.0f / MAX_ANIMATION_X;
			float fv = 1.0f / MAX_ANIMATION_Y;

			uv[0] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY);
			uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY);
			uv[2] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY + fv);
			uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY + fv);

			// UV座標セット
			SetTextureUV(uv);
		}

		if (m_nAnimX + 1 == MAX_ANIMATION_X)
		{
			// プレイヤー全員移動可能状態にする
			for (int nCntPlayer = 0; nCntPlayer < CGame::GetPlayerNum(); nCntPlayer++)
			{
				CGame::GetPlayer(nCntPlayer)->SetMoveFlag(true);
			}
		}
	}

}

//******************************
// 描画処理
//******************************
void CStart::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CScene3d::Draw();
}
