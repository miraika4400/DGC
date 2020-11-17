//=============================================================================
//
// playerヘッダ [player.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _PLAYER_H_
#define _PLAYER_H_

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
class CPlayer : public CModel
{
public:

	//メンバ関数
	CPlayer();
	~CPlayer();
	static CPlayer *Create(D3DXVECTOR3 pos,int nPlayerNum);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	
	CCollision*GetCollision(void) { return m_pCollision; }

	// 重力フラグの取得・セット
	bool GetActiveGravity(void) { return m_bGravity; }
	void SetActiveGravity(bool bBool) { m_bGravity = bBool; }
	// チェックポイント数の取得・セット・加算
	int GetCheckNum(void) { return m_nNumCheckpoint; }
	void SetCheckNum(int nNum) { m_nNumCheckpoint = nNum; }
	void AddCheckNum(void) { m_nNumCheckpoint++; }
	// 移動フラグの取得・セット
	bool GetMoveFlag(void) { return m_bMove; }
	void SetMoveFlag(bool bMove) { m_bMove = bMove; }

	void ZeroMove(void) { m_move = VEC3_ZERO; }
private:
	void MoveControll(void);
	void Gravity(void);
	// メンバ変数
	static LPD3DXMESH m_pMeshModel;	                    //メッシュ情報へのポインタ
	static LPD3DXBUFFER m_pBuffMatModel;	            //マテリアル情報へのポインタ
	static DWORD m_nNumMatModel;	                    //マテリアル情報の数
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE]; // テクスチャ
	D3DXVECTOR3 m_move;        // 移動量
	int m_nPlayerNum;          // プレイヤー番号
	D3DXVECTOR3 m_gravityVec;  // 重力
	bool m_bGravity;           // 重力フラグ
	CCollision*m_pCollision;   // コリジョンクラスのポインタ
	int m_nNumCheckpoint;      // チェックポイント数
	bool m_bGoal;              // ゴールフラグ
	bool m_bMove;              // 移動できる状態化判定用
};

#endif