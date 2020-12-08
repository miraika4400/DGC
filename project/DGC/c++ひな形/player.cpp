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
#include "destination.h"
#include "mouse.h"
#include "item.h"

//*****************************
// マクロ定義
//*****************************
#define MODEL_PATH "./data/Models/testplayer.x"       //モデルのパス
#define HIERARCHY_TEXT_PATH "./data/Texts/hierarchy/CatData_Choco.txt"       //モデルのパス
#define PLAYER_GRAVITY D3DXVECTOR3(0.0f,-40.0f,0.0f)   // 重力量
#define PLAYER_GRAVITY_RATE 0.1f                     // 重力の係数
#define PLAYER_DIRECTION_RATE 0.1f                   // 向きの係数
#define PLAYER_RADIUS 150
#define HIT_FRAME  100                               // ヒット状態のフレーム数

// 進化毎のパーツ数
#define EVOLUTION_0 2             // 初期
#define EVOLUTION_1 4             // 2段階目
#define EVOLUTION_2 8             // 3段階目
#define EVOLUTION_3 m_nNumModel   // 4段階目



//*****************************
// 静的メンバ変数宣言
//*****************************
//LPD3DXMESH   CPlayer::m_pMeshModel = NULL;   	//メッシュ情報へのポインタ
//LPD3DXBUFFER CPlayer::m_pBuffMatModel = NULL;	//マテリアル情報へのポインタ
//DWORD        CPlayer::m_nNumMatModel = 0;	    //マテリアル情報の数
//LPDIRECT3DTEXTURE9 CPlayer::m_apTexture[MAX_TEXTURE] = {}; // テクスチャ
CModel::Model CPlayer::m_model[MAX_PARTS_NUM] = {};
int CPlayer::m_nNumModel = 0;
int CPlayer::m_nNumEvolutionParts[MAX_EVOLUTION]=
{
	EVOLUTION_0,
	EVOLUTION_1,
	EVOLUTION_2,
	EVOLUTION_3,
};
//******************************
// コンストラクタ
//******************************
CPlayer::CPlayer() :CModelHierarchy(OBJTYPE_PLAYER)
{
	// 変数のクリア
	//m_move = VEC3_ZERO;         // 移動量
	m_nPlayerNum = 0;           // プレイヤー番号
	m_gravityVec = VEC3_ZERO;   // 重力量
	m_bGravity = true;          // 重力フラグ
	m_pCollision = NULL;        // コリジョン
	m_nNumCheckpoint = 0;       // チャックポイント数
	m_bGoal = false;            // ゴールフラグ
	m_bMove = false;            // 移動フラグ
	m_nChain = 0;               // チェイン数
	m_nCollectItem = 0;         // 回収したアイテム数
	m_nNumEvolution = 0;        // 進化回数
	m_pDest = NULL;             // 移動目標クラス
	m_bDriftLeft = false;       // ドリフト左
	m_bDriftRight = false;      // ドリフト右
	m_bHit = false;             // ヒット状態フラグ
	m_nCntHit = 0;              // ヒット状態解除時のカウント
	m_nMaxSpeed = PLAYER_SPEED; // 最大速度
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
	
	// 移動目標の生成
	pPlayer->m_pDest = CDestination::Create(nPlayerNum, pos);
	return pPlayer;
}

//******************************
// テクスチャのロード
//******************************
HRESULT CPlayer::Load(void)
{

	// モデルの読み込み
	LoadModels(HIERARCHY_TEXT_PATH, &m_model[0], &m_nNumModel);
	// 最終進化をパーツ数
	m_nNumEvolutionParts[MAX_EVOLUTION - 1] = m_nNumModel;

	return S_OK;
}

//******************************
// テクスチャのアンロード
//******************************
void CPlayer::Unload(void)
{
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		//メッシュの破棄
		if (m_model[nCnt].pMesh != NULL)
		{
			m_model[nCnt].pMesh->Release();
			m_model[nCnt].pMesh = NULL;
		}
		//マテリアルの破棄
		if (m_model[nCnt].pBuffMat != NULL)
		{
			m_model[nCnt].pBuffMat->Release();
			m_model[nCnt].pBuffMat = NULL;
		}
	}
}


//******************************
// 初期化処理
//******************************
HRESULT CPlayer::Init(void)
{
	if (FAILED(CModelHierarchy::Init(m_nNumEvolutionParts[m_nNumEvolution], &m_model[0], HIERARCHY_TEXT_PATH)))
	{
		return E_FAIL;
	}

	// モデル情報の割り当て
	//BindModel(m_model.pMesh, m_model.pBuffMat, m_model.nNumMat);
	//
	//// テクスチャの割り当て
	//for (int nCnt = 0; nCnt < (int)m_model.nNumMat; nCnt++)
	//{
	//	if (m_model.apTexture[nCnt] != NULL)
	//	{
	//		BindTexture(nCnt, m_model.apTexture[nCnt]);
	//	}
	//}

	// 変数の初期化
	m_bGravity = true;          // 重力フラグ
	m_nNumCheckpoint = 0;       // チェックポイント数
	m_bGoal = false;            // ゴールフラグ
	m_bMove = false;            // 移動フラグ
	m_nChain = 0;               // チェイン数
	m_nCollectItem = 0;         // 回収したアイテム数
	m_bDriftLeft = false;       // ドリフト左
	m_bDriftRight = false;      // ドリフト右
	m_bHit = false;             // ヒットフラグ
	m_nCntHit = 0;              // ヒット時のカウント
	m_nMaxSpeed = PLAYER_SPEED; // 最大速度

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CPlayer::Uninit(void)
{
	CModelHierarchy::Uninit();
}

//******************************
// 更新処理
//******************************
void CPlayer::Update(void)
{
	// 移動操作
	//MoveControll();
	// 重力
	Gravity();
	// ドリフトの処理
	Drift();

	// 当たり判定の位置更新
	m_pCollision->SetPos(GetPos());

	// ヒット状態の管理
	if (m_bHit)
	{// ヒット状態の時
		m_nCntHit--;
		if (m_nCntHit <= 0)
		{// カウントが0以下の時
			// ヒットフラグをfalseに
			m_bHit = false;
		}
		m_nMaxSpeed = PLAYER_SPEED_HIT;
	}
	else
	{
		m_nMaxSpeed = PLAYER_SPEED;
	}

#ifdef _DEBUG
	// デバッグコマンド

	// 進化
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_E))
	{
		Evolution();
	}

	// アイテムドロップ
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_D))
	{
		CItem::DropItemCircle(GetPos(), 5, m_nPlayerNum);
	}
	if (CManager::GetKeyboard()->GetKeyPress(DIK_S))
	{
		CItem::DropItem(GetPos(), m_nPlayerNum);
	}

	// ストップ
	if (CManager::GetKeyboard()->GetKeyPress(DIK_SPACE))
	{
		m_bMove = false;
	}
	else if (CManager::GetKeyboard()->GetKeyRelease(DIK_SPACE))
	{
		m_bMove = true;
	}

#endif
}

//******************************
// 描画処理
//******************************
void CPlayer::Draw(void)
{
	CModelHierarchy::Draw();
}

//******************************
// アイテムに当たったときの処理
//******************************
void CPlayer::HitItem(bool bSafe)
{
	if (bSafe)
	{// 自分アイテムの当たったとき
		m_nCollectItem++;
		m_nChain++;
		CDebugLog::Init();
		CDebugLog::Print("Safe");
	}
	else
	{// 自分以外のアイテムに当たったとき
		m_nChain = 0;
		CDebugLog::Init();
		CDebugLog::Print("Out");
		m_bHit = true;
		m_nCntHit = HIT_FRAME;

		CItem::DropItemCircle(GetPos(), 5, m_nPlayerNum);
		CGame::GetCamera(m_nPlayerNum)->Shake(true);
	}
}

//******************************
// 操作の管理
//******************************
void CPlayer::MoveControll(void)
{
//	// 座標
//	D3DXVECTOR3 pos = GetPos();
//	//移動量の目標値
//	D3DXVECTOR3 moveDest = VEC3_ZERO;
//
//	// カメラの向きの取得
//	float fCameraAngle = CGame::GetCamera(m_nPlayerNum)->GetAngle();
//#if 0
//	if (m_bMove)
//	{
//		moveDest.x = cosf(fCameraAngle)* PLAYER_SPEED;
//		moveDest.z = sinf(fCameraAngle)* PLAYER_SPEED;
//	}
//
//#else
//	if (CManager::GetKeyboard()->GetKeyPress(DIK_W))
//	{
//		moveDest.x = cosf(fCameraAngle)* PLAYER_SPEED;
//		moveDest.z = sinf(fCameraAngle)* PLAYER_SPEED;
//	}
//
//#endif
//	// 慣性
//	m_move += (moveDest - m_move) * PLAYER_MOVE_RATE;
//
//	// 移動量を足す
//	pos += m_move;
//
//	// 座標のセット
//	SetPos(pos);
//
//	// プレイヤーの向きをカメラに合わせる
//	D3DXVECTOR3 rot = GetRot();
//	rot.y = -(fCameraAngle + D3DXToRadian(90));
//	//rot.x += 0.01f;
//	SetRot(rot);
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

//******************************
// 進化
//******************************
void CPlayer::Evolution(void)
{
	// 進化回数のカウント
	m_nNumEvolution++;
	if (m_nNumEvolution >= MAX_EVOLUTION)
	{// 進化数が最大を超えないように
		m_nNumEvolution = MAX_EVOLUTION - 1;
	}

	// パーツ数の読み込み
	CModelHierarchy::Init(m_nNumEvolutionParts[m_nNumEvolution], &m_model[0], HIERARCHY_TEXT_PATH);
}

//******************************
// ドリフト
//******************************
void CPlayer::Drift(void)
{
	float fDistance = 0.0f;// 移動目標との距離

	if (!m_bDriftLeft && !m_bDriftRight)
	{// ドリフトがファルス状態の時

		// キーボード
		if (CManager::GetKeyboard()->GetKeyPress(DIK_LSHIFT))
		{
			if (CManager::GetMouse()->GetMouseMove().x > 0)
			{// 右ドリフト
				m_bDriftRight = true;	
				
			}
			else if (CManager::GetMouse()->GetMouseMove().x < 0)
			{// 左ドリフト
				m_bDriftLeft = true;
			}
		}

		// コントローラー
		if (CManager::GetJoypad()->GetJoystickPress(5, m_nPlayerNum))
		{
			if (CManager::GetJoypad()->GetStick(m_nPlayerNum).lX >= 10)
			{// 右ドリフト
				m_bDriftRight = true;
			}
			else if (CManager::GetJoypad()->GetStick(m_nPlayerNum).lX <= -10)
			{// 左ドリフト
				m_bDriftLeft = true;
			}
		}
	}
	else
	{
		// ドリフト状態の解除
		if (CManager::GetJoypad()->GetJoystickRelease(5, m_nPlayerNum) || CManager::GetKeyboard()->GetKeyRelease(DIK_LSHIFT))
		{
			m_bDriftLeft = false;
			m_bDriftRight = false;
		}
	}
	//if (m_pDest->GetDistanceDest() != fDistance)
	//{
	//	m_pDest->SetDistanceDest(fDistance);
	//}
}
