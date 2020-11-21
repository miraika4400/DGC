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

//*****************************
// マクロ定義
//*****************************
#define MODEL_PATH_COLORLESS "./data/Models/Item_model/cube02.x"	// 無色モデルのパス
#define MODEL_PATH_1         "./data/Models/Item_model/cube02.x"	// 赤モデルのパス
#define MODEL_PATH_2         "./data/Models/Item_model/cube02.x"	// 青モデルのパス
#define MODEL_PATH_3         "./data/Models/Item_model/cube02.x"	// 黄色モデルのパス
#define MODEL_PATH_4         "./data/Models/Item_model/cube02.x"	// 緑モデルのパス

#define ITEM_RADIUS 70   // 半径

#ifdef _DEBUG

#define RED     D3DXCOLOR(1.0f,0.0f,0.0f,1.0f) // 赤
#define BLUE    D3DXCOLOR(0.0f,0.0f,1.0f,1.0f) // 青
#define YELLOW  D3DXCOLOR(1.0f,1.0f,0.0f,1.0f) // 黄
#define GREEN   D3DXCOLOR(0.0f,1.0f,0.0f,1.0f) // 緑

#endif

//*****************************
// 静的メンバ変数宣言
//*****************************
CModel::Model   CItem::m_model[CItem::ITEM_MAX] = {};   	//メッシュ情報へのポインタ
D3DXVECTOR3 CItem::m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // 全アイテム共通でロット固定

char *CItem::m_pTexPath[CItem::ITEM_MAX] =
{
	MODEL_PATH_COLORLESS,
	MODEL_PATH_1,
	MODEL_PATH_2,
	MODEL_PATH_3,
	MODEL_PATH_4
};

//******************************
// コンストラクタ
//******************************
CItem::CItem() :CModel(OBJTYPE_MAP)
{
	// 変数のクリア
	m_pCollision = NULL;         // 当たり判定
	m_itemType = ITEM_COLORLESS; // アイテムタイプ
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
CItem * CItem::Create(D3DXVECTOR3 pos, ITEM_TYPE type)
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
	// プレイヤーとの当たり判定
	CollisionPlayer();
}

//******************************
// 描画処理
//******************************
void CItem::Draw(void)
{
	
#ifdef _DEBUG
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
#endif // _DEBUG
	SetRot(m_rot);
	CModel::Draw();
}

//******************************
// 回転処理
//******************************
void CItem::ItemRotasion(void)
{
	m_rot.y += D3DXToRadian(3);
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
