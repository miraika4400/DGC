//=============================================================================
//
// itemヘッダ [item.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _ITEM_H_
#define _ITEM_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "model.h"

//*****************************
// マクロ定義
//*****************************

//*****************************
// 前方宣言
//*****************************
class CCollision;

//*****************************
// クラス定義
//*****************************

// パーティクルクラス
class CItem : public CModel
{
public:
	//==========================
	// 列挙
	//==========================
	// アイテムタイプ
	typedef enum
	{
		
		ITEM_RED = 0,        // 赤
		ITEM_BLUE,           // 青
		ITEM_YELLOW,         // 黄
		ITEM_GREEN,          // 緑
		ITEM_COLORLESS,      // 無色アイテム
		ITEM_MAX
	}ITEM_TYPE;

	//==========================
	//メンバ関数
	//==========================
	CItem();
	~CItem();
	static CItem *Create(D3DXVECTOR3 pos, ITEM_TYPE type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void ItemRotasion(void);
private:
	void CollisionPlayer(void);

	static Model m_model[ITEM_MAX];          // モデル構造体
	static char *m_pTexPath[ITEM_MAX];       // テクスチャのパス
	CCollision*m_pCollision;                 // 当たり判定
	ITEM_TYPE m_itemType;                    // アイテムタイプ
	static D3DXVECTOR3 m_rot;                // 全アイテム共通でロット固定
};
#endif