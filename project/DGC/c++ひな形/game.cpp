////////////////////////////////////////////////////
//
//    ゲームクラスの処理[game.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "game.h"
#include "bg.h"
#include "number.h"
#include "score.h" 
#include "mouse.h"
#include "camera.h"
#include "fade.h"
#include "keyboard.h"
#include "particle.h"
#include "time.h"
#include "course.h"
#include "player.h"
#include "light.h"
#include "item.h"
#include "rank.h"
#include "file.h"

//=============================
// マクロ定義
//=============================
#define FILE_NAME "data/data.txt"

//=============================
// 静的メンバ変数宣言
//=============================
CCamera *CGame::m_pCamera[MAX_PLAYER_NUM] = {};   // カメラ
CPlayer *CGame::m_pPlayer[MAX_PLAYER_NUM] = {};   // プレイヤー
CLight *CGame::m_pLight = NULL;		// ライトクラスのポインタ変数
int CGame::m_nNumPlayer = 1;        // プレイヤー人数

//=============================
// コンストラクタ
//=============================
CGame::CGame()
{
}

//=============================
// デストラクタ
//=============================
CGame::~CGame()
{
}

//=============================
// クリエイト
//=============================
CGame * CGame::Create()
{
	// メモリの確保
	CGame *pGame = new CGame;
	// 初期化
	pGame->Init(); 
	return pGame;
}

//=============================
// 初期化処理
//=============================
HRESULT CGame::Init(void)
{
	// ポーズの初期化
	CManager::SetActivePause(false);

	// マップの生成
	CCourse::Create(CCourse::COURSE_EASY);
	for (int nCntPlayer = 0; nCntPlayer < m_nNumPlayer; nCntPlayer++)
	{
		// プレイヤーの生成
		m_pPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 300.0f), nCntPlayer);
		// カメラの生成
		m_pCamera[nCntPlayer] = CCamera::Create(nCntPlayer);
	}
	//ライトクラスの生成
	m_pLight = new CLight;
	// 初期化
	if (m_pLight != NULL)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}
	
	CItem::Create(D3DXVECTOR3(0.0    , 50.0f, -1000.0f), CItem::ITEM_COLORLESS);
	CItem::Create(D3DXVECTOR3(500.0f , 50.0f, -1000.0f), CItem::ITEM_RED);
	CItem::Create(D3DXVECTOR3(-500.0f, 50.0f, -1000.0f), CItem::ITEM_BLUE);
	CItem::Create(D3DXVECTOR3(0.0    , 50.0f, -1500.0f), CItem::ITEM_YELLOW);
	CItem::Create(D3DXVECTOR3(0.0    , 50.0f, -2000.0f), CItem::ITEM_GREEN);

    // アイテム配置
    CFile::Create()->Read(FILE_NAME);

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CGame::Uninit(void)
{
	// カメラ
	for (int nCntCamera = 0; nCntCamera < m_nNumPlayer; nCntCamera++)
	{
		if (m_pCamera[nCntCamera] != NULL)
		{
			m_pCamera[nCntCamera]->Uninit();
			delete m_pCamera[nCntCamera];
			m_pCamera[nCntCamera] = NULL;
		}
	}
	// ライト
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	// 開放処理
	Release();

    CFile::GetInstance()->Uninit();
}


//=============================
// 更新処理
//=============================
void CGame::Update(void)
{
	// アイテム回転
	CItem::ItemRotasion();

	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN))
	{
		CManager::GetFade()->SetFade(CManager::MODE_RESULT);
	}
	// カメラクラスのアップデート
	for (int nCntPlayer = 0; nCntPlayer < m_nNumPlayer; nCntPlayer++)
	{
		if (m_pCamera[nCntPlayer] != NULL)
		{
			m_pCamera[nCntPlayer]->Update();
		}
	}
	CRank::RankManage();
}


//=============================
// 描画処理
//=============================
void CGame::Draw(void)
{
}