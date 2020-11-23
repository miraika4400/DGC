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
#include "model_hierarchy.h"

//*****************************
// マクロ定義
//*****************************
#define MAX_EVOLUTION 4        // 進化の段階数
#define PLAYER_SPEED 100       // プレイヤー速度
#define PLAYER_MOVE_RATE 0.05f // 慣性の係数

//*****************************
// 前方宣言
//*****************************
class CCollision;

//*****************************
// クラス定義
//*****************************

// パーティクルクラス
class CPlayer : public CModelHierarchy
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
	// アイテム数の取得・セット・加算
	int  GetItemNum(void) { return m_nCollectItem; }
	void SetItemNum(int nNum) { m_nCollectItem = nNum; }
	void AdtItemNum(void) { m_nCollectItem++; }
	// チェインポイント数の取得・セット・加算
	int  GetChainNum(void) { return m_nChain; }
	void SetChainNum(int nNum) { m_nChain = nNum; }
	void AdtChainNum(void) { m_nChain++; }
	// 移動フラグの取得・セット
	bool GetMoveFlag(void) { return m_bMove; }
	void SetMoveFlag(bool bMove) { m_bMove = bMove; }

	// プレイヤー番号の取得
	int GetPlayerNum(void) { return m_nPlayerNum; }

	void HitItem(bool bSafe);

	void ZeroMove(void) { m_move = VEC3_ZERO; }

private:
	void MoveControll(void);
	void Gravity(void);
	void Evolution(void);

	// メンバ変数
	static CModel::Model m_model[MAX_PARTS_NUM];             // モデル構造体
	static int m_nNumModel;
	D3DXVECTOR3 m_move;        // 移動量
	int m_nPlayerNum;          // プレイヤー番号
	D3DXVECTOR3 m_gravityVec;  // 重力
	bool m_bGravity;           // 重力フラグ
	CCollision*m_pCollision;   // コリジョンクラスのポインタ
	int m_nNumCheckpoint;      // チェックポイント数
	bool m_bGoal;              // ゴールフラグ
	bool m_bMove;              // 移動できる状態化判定用
	int m_nChain;              // チェイン数
	int m_nCollectItem;        // 回収したアイテム数
	int m_nNumEvolution;       // 進化回数
	static int m_nNumEvolutionParts[MAX_EVOLUTION];
};

#endif