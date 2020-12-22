////////////////////////////////////////////////////
//
//    Itemクラスの処理[Item.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "Item.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "player.h"
#include "checkpoint.h"
#include "wall.h"
#include "start.h"
#include "collision.h"
#include "destination.h"
//*****************************
// マクロ定義
//*****************************
#define MODEL_PATH_1         "./data/Models/item/item1.x"	// 赤モデルのパス
#define MODEL_PATH_2         "./data/Models/item/item1.x"	// 青モデルのパス
#define MODEL_PATH_3         "./data/Models/item/item1.x"	// 黄色モデルのパス
#define MODEL_PATH_4         "./data/Models/item/item1.x"	// 緑モデルのパス
#define MODEL_PATH_COLORLESS "./data/Models/item/item1.x"	// "./data/Models/player/player.x" //	// 無色モデルのパス

#define ITEM_RADIUS 70           // 半径
#define GET_COUNT   20           // 透明アイテム生成から取得可能までのフレーム数
#define DROP_CIRCLE_SPEED 10.0f  // 円形にドロップするとき飛んでいく移動量
#define DROP_DESTINATION  -10.0f // ドロップするとき落下速度の目標値
#define DROP_RATE         0.05f  // ドロップするとき落下速度の係数

//#define DROP_CIRCLE_FRAME 20.0f // 何フレームかけて飛ばすか

#define RED     D3DXCOLOR(1.0f,0.0f,0.0f,1.0f) // 赤
#define BLUE    D3DXCOLOR(0.0f,0.0f,1.0f,1.0f) // 青
#define YELLOW  D3DXCOLOR(1.0f,1.0f,0.0f,1.0f) // 黄
#define GREEN   D3DXCOLOR(0.0f,1.0f,0.0f,1.0f) // 緑

#ifdef _DEBUG
#endif

//*****************************
// 静的メンバ変数宣言
//*****************************
CModel::Model   CItem::m_model[CItem::ITEM_MAX] = {};   	//メッシュ情報へのポインタ
D3DXVECTOR3 CItem::m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // 全アイテム共通でロット固定

char *CItem::m_pTexPath[CItem::ITEM_MAX] =
{
	
	MODEL_PATH_1,
	MODEL_PATH_2,
	MODEL_PATH_3,
	MODEL_PATH_4,
	MODEL_PATH_COLORLESS
};

//******************************
// コンストラクタ
//******************************
CItem::CItem() :CModel(OBJTYPE_ITEM)
{
	// 変数のクリア
	m_pCollision = NULL;         // 当たり判定
	m_itemType = ITEM_COLORLESS; // アイテムタイプ
	m_bDrop = false;             // 落下中か判別
	m_move = VEC3_ZERO;          // ドロップ時の移動量
	m_nPlayerNum = -1;           // ドロップ時どのプレイヤーが落としたか
	m_nCntGet = 0;               // 透明アイテムは最初の数フレーム拾えないように
}

//******************************
// デストラクタ
//******************************
CItem::~CItem()
{
}

//******************************
// クリエイト
//******************************
CItem * CItem::Create(const D3DXVECTOR3 pos, const ITEM_TYPE type)
{
	// メモリの確保
	CItem *pItem;
	pItem = new CItem;
	
	// タイプの設定
	pItem->m_itemType = type;
	// 初期化
	pItem->Init();

	// 各値の代入・セット
	pItem->SetObjType(OBJTYPE_MAP); // オブジェクトタイプ
	pItem->SetPos(pos);             // 座標のセット

	// 当たり判定の生成
	pItem->m_pCollision=CCollision::CreateSphere(pos, ITEM_RADIUS);

	return pItem;
}

//******************************
// テクスチャのロード
//******************************
HRESULT CItem::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// コース数分ループ
	for (int nCntItem = 0; nCntItem < ITEM_MAX; nCntItem++)
	{
		//Xファイルの読み込み
		D3DXLoadMeshFromX(m_pTexPath[nCntItem],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_model[nCntItem].pBuffMat,
			NULL,
			&m_model[nCntItem].nNumMat,
			&m_model[nCntItem].pMesh);

		if (m_model[nCntItem].nNumMat != 0)
		{
			D3DXMATERIAL*pMat = (D3DXMATERIAL*)m_model[nCntItem].pBuffMat->GetBufferPointer();
			for (int nCnt = 0; nCnt < (int)m_model[nCntItem].nNumMat; nCnt++)
			{
				if (pMat[nCnt].pTextureFilename != NULL)
				{
					char cPath[64] = {};
					sprintf(cPath, "./data/Textures/%s", pMat[nCnt].pTextureFilename);
					// テクスチャの生成
					D3DXCreateTextureFromFile(pDevice, cPath, &m_model[nCntItem].apTexture[nCnt]);
				}
			}
		}
	}

	return S_OK;
}

//******************************
// テクスチャのアンロード
//******************************
void CItem::Unload(void)
{
	for (int nCnt = 0; nCnt < ITEM_MAX; nCnt++)
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
// 回転処理
//******************************
void CItem::ItemRotasion(void)
{
	m_rot.y += D3DXToRadian(3);
}

//******************************
// ドロップ
//******************************
void CItem::DropItem(const D3DXVECTOR3 pos,  const int nPlayerNum)
{
	// 透明アイテムの生成
	CItem*pItem = NULL;
	pItem = Create(pos, ITEM_COLORLESS);

	// ドロップ状態にする
	pItem->m_bDrop = true;
}

//******************************
// ドロップ
//******************************
void CItem::DropItemCircle(const D3DXVECTOR3 pos, const int nNumDrop, const int nPlayerNum)
{
	// ドロップする数ループ
	for (int nCnt = 0; nCnt < nNumDrop; nCnt++)
	{
		// 透明アイテムの生成
		CItem*pItem = NULL;
		pItem = Create(pos, ITEM_COLORLESS);

		if (pItem != NULL)
		{
			// ランダムな角度
			float fRandAngle = D3DXToRadian(rand() % 360);

			// 移動量の設定
			pItem->m_move.x = cosf(fRandAngle)*DROP_CIRCLE_SPEED;
			pItem->m_move.y = 20.0f;
			pItem->m_move.z = sinf(fRandAngle)*DROP_CIRCLE_SPEED;

			// プレイヤー番号の設定
			pItem->m_nPlayerNum = nPlayerNum;
			// ドロップ状態にする
			pItem->m_bDrop = true;
		}
	}
}

//******************************
// 初期化処理
//******************************
HRESULT CItem::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}

	// モデル割り当て
	BindModel(m_model[m_itemType].pMesh, m_model[m_itemType].pBuffMat, m_model[m_itemType].nNumMat);

	//テクスチャの割り当て
	for (int nCnt = 0; nCnt < (int)m_model[m_itemType].nNumMat; nCnt++)
	{
		BindTexture(nCnt, m_model[m_itemType].apTexture[nCnt]);
	}

	// カウントの初期化
	if (m_itemType == ITEM_COLORLESS)
	{// 透明アイテム時
		m_nCntGet = GET_COUNT;
	}
	else
	{// 色付きアイテム
		m_nCntGet = 0;
	}

	// プレイヤー番号の初期化
	m_nPlayerNum = -1;
	
	m_bDrop = true;
	return S_OK;
}

//******************************
// 終了処理
//******************************
void CItem::Uninit(void)
{
	if (m_pCollision != NULL)
	{
		m_pCollision->Uninit();
		m_pCollision = NULL;
	}
	CModel::Uninit();
}

//******************************
// 更新処理
//******************************
void CItem::Update(void)
{
	if (!m_bDrop)
	{// ドロップ状態じゃないとき
		
		if (m_nCntGet > 0)
		{// カウントが残ってるとき
			
			m_nCntGet--;
		}
		else
		{// カウントが残ってないとき

			// プレイヤーとの当たり判定
			CollisionPlayer();
		}
	}
	else
	{
		Move();
	}
}

//******************************
// 描画処理
//******************************
void CItem::Draw(void)
{
	//マテリアルデータへのポインタを取得
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)GetModelData()->pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_model[m_itemType].nNumMat; nCntMat++)
	{
			switch (m_itemType)
			{
			case ITEM_RED:
				pMat[nCntMat].MatD3D.Diffuse = RED;
				break;
			case ITEM_BLUE:
				pMat[nCntMat].MatD3D.Diffuse = BLUE;
				break;
			case ITEM_YELLOW:
				pMat[nCntMat].MatD3D.Diffuse = YELLOW;
				break;
			case ITEM_GREEN:
				pMat[nCntMat].MatD3D.Diffuse = GREEN;
				break;
			default:
				break;
			}
	}
#ifdef _DEBUG
#endif // _DEBUG
	SetRot(m_rot);
	CModel::Draw();
}

//******************************
// プレイヤーとの当たり判定
//******************************
void CItem::CollisionPlayer(void)
{
	// プレイヤー情報の取得
	CPlayer*pPlayer = (CPlayer*)GetTop(OBJTYPE_PLAYER);

	while (pPlayer != NULL)
	{
		// 当たり判定
		if (CCollision::CollisionSphere(m_pCollision, pPlayer->GetCollision()))
		{// 当たってた時
			if (pPlayer->GetPlayerNum() == m_itemType || m_itemType == ITEM_COLORLESS)
			{// 自分の色もしくは無色
				pPlayer->HitItem(true);
				Uninit();
			}
			else
			{// その他
				pPlayer->HitItem(false);
				Uninit();
			}
			break;
		}
		
		// ネクストのポインタに更新
		pPlayer = (CPlayer*)pPlayer->GetNext();
	}
}

//******************************
// 移動の処理
//******************************
void CItem::Move(void)
{
	m_move.y += (DROP_DESTINATION - m_move.y)*DROP_RATE;

	// 移動量を現在座標に足してセット
	SetPos(GetPos() + m_move);
	m_pCollision->SetPos(GetPos());
}
