////////////////////////////////////////////////////
//
//    particleクラスの処理[particle.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"
#include "debug_log.h"
#include "collision.h"

//*****************************
// マクロ定義
//*****************************
#define MODEL_PATH "./data/Models/testplayer.x"       //モデルのパス
#define PLAYER_SPEED 100                               // プレイヤー速度
#define PLAYER_MOVE_RATE 0.05f                        // 慣性の係数
#define PLAYER_GRAVITY D3DXVECTOR3(0.0f,-40.0f,0.0f)   // 重力量
#define PLAYER_GRAVITY_RATE 0.1f                     // 重力の係数
#define PLAYER_DIRECTION_RATE 0.1f                   // 向きの係数
#define PLAYER_RADIUS 150

//*****************************
// 静的メンバ変数宣言
//*****************************
LPD3DXMESH   CPlayer::m_pMeshModel = NULL;   	//メッシュ情報へのポインタ
LPD3DXBUFFER CPlayer::m_pBuffMatModel = NULL;	//マテリアル情報へのポインタ
DWORD        CPlayer::m_nNumMatModel = 0;	    //マテリアル情報の数
LPDIRECT3DTEXTURE9 CPlayer::m_apTexture[MAX_TEXTURE] = {}; // テクスチャ

//******************************
// コンストラクタ
//******************************
CPlayer::CPlayer() :CModel(OBJTYPE_PLAYER)
{
	// 変数のクリア
	m_move = VEC3_ZERO;       // 移動量
	m_nPlayerNum = 0;         // プレイヤー番号
	m_gravityVec = VEC3_ZERO; // 重力量
	m_bGravity = true;        // 重力フラグ
	m_pCollision = NULL;      // コリジョン
	m_nNumCheckpoint = 0;     // チャックポイント数
	m_bGoal = false;          // ゴールフラグ
	m_bMove = false;          // 移動フラグ
}

//******************************
// デストラクタ
//******************************
CPlayer::~CPlayer()
{
}

//******************************
// クリエイト
//******************************
CPlayer * CPlayer::Create(D3DXVECTOR3 pos,int nPlayerNum)
{
	// メモリの確保
	CPlayer *pPlayer;
	pPlayer = new CPlayer;
	pPlayer->m_nPlayerNum = nPlayerNum;
	// 初期化
	pPlayer->Init();
	
	// 各値の代入・セット
	pPlayer->SetPos(pos);
	pPlayer->SetObjType(OBJTYPE_PLAYER); // オブジェクトタイプ
	// 当たり判定の生成
	pPlayer->m_pCollision = CCollision::CreateSphere(pos, PLAYER_RADIUS);

	return pPlayer;
}

//******************************
// テクスチャのロード
//******************************
HRESULT CPlayer::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_PATH,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel,
		NULL,
		&m_nNumMatModel,
		&m_pMeshModel);

	// パスの文字列格納用
	char chPath[64];

	// テクスチャの読み込み
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();
	for (int nCnt = 0; nCnt < (int)m_nNumMatModel; nCnt++)
	{
		if (pMat[nCnt].pTextureFilename != NULL)
		{
			// テクスチャ名を文字列に変換
			sprintf(chPath, "%s", pMat[nCnt].pTextureFilename);
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, chPath, &m_apTexture[nCnt]);
		}
	}
	return S_OK;
}

//******************************
// テクスチャのアンロード
//******************************
void CPlayer::Unload(void)
{
	//メッシュの破棄
	if (m_pMeshModel != NULL)
	{
		m_pMeshModel->Release();
		m_pMeshModel = NULL;
	}
	//マテリアルの破棄
	if (m_pBuffMatModel != NULL)
	{
		m_pBuffMatModel->Release();
		m_pBuffMatModel = NULL;
	}
}


//******************************
// 初期化処理
//******************************
HRESULT CPlayer::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}

	// モデル情報の割り当て
	BindModel(m_pMeshModel, m_pBuffMatModel, m_nNumMatModel);
	
	// テクスチャの割り当て
	for (int nCnt = 0; nCnt < (int)m_nNumMatModel; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			BindTexture(nCnt, m_apTexture[nCnt]);
		}
	}
	// 変数の初期化
	m_bGravity = true;    // 重力フラグ
	m_nNumCheckpoint = 0; // チェックポイント数
	m_bGoal = false;      // ゴールフラグ
	m_bMove = false;          // 移動フラグ

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CPlayer::Uninit(void)
{
	CModel::Uninit();
}

//******************************
// 更新処理
//******************************
void CPlayer::Update(void)
{
	// 移動操作
	MoveControll();
	// 重力
	Gravity();
	
	// 当たり判定の位置更新
	m_pCollision->SetPos(GetPos());
}

//******************************
// 描画処理
//******************************
void CPlayer::Draw(void)
{
	CModel::Draw();
}

//******************************
// 操作の管理
//******************************
void CPlayer::MoveControll(void)
{
	// 座標
	D3DXVECTOR3 pos = GetPos();
	//移動量の目標値
	D3DXVECTOR3 moveDest = VEC3_ZERO;

	// カメラの向きの取得
	float fCameraAngle = CGame::GetCamera(m_nPlayerNum)->GetAngle();
#if 1
	if (m_bMove)
	{
		// ジョイスティックの取得
		DIJOYSTATE js = CManager::GetJoypad()->GetStick(m_nPlayerNum);
		
		moveDest.x = cosf(fCameraAngle)* PLAYER_SPEED;
		moveDest.z = sinf(fCameraAngle)* PLAYER_SPEED;
	}
#else
	// ジョイスティックの取得
	DIJOYSTATE js = CManager::GetJoypad()->GetStick(m_nPlayerNum);

	moveDest.x = cosf(fCameraAngle)* PLAYER_SPEED;
	moveDest.z = sinf(fCameraAngle)* PLAYER_SPEED;

#endif
	// 慣性
	m_move += (moveDest - m_move) * PLAYER_MOVE_RATE;

	// 移動量を足す
	pos += m_move;

	// 座標のセット
	SetPos(pos);

	// プレイヤーの向きをカメラに合わせる
	D3DXVECTOR3 rot=GetRot();
	rot.y = -(fCameraAngle - D3DXToRadian(90));
	SetRot(rot);
}

//******************************
// 重力の管理
//******************************
void CPlayer::Gravity(void)
{
	if (m_bGravity)
	{// 重力フラグが立ってたら

		// 重力量の設定
		m_gravityVec += (PLAYER_GRAVITY - m_gravityVec)*PLAYER_GRAVITY_RATE;

		// 座標に重力量のプラス
		SetPos(GetPos() + m_gravityVec);

	}
	else
	{// 重力フラグが立ってないとき
		// 初期化
		m_gravityVec = VEC3_ZERO;
	}
}
