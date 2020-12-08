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
#define PLAYER_SPEED_HIT 20    // 障害物ヒット時のプレイヤー速度
#define PLAYER_MOVE_RATE 0.03f // 慣性の係数

//*****************************
// 前方宣言
//*****************************
class CCollision;
class CDestination;

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
	CDestination*GetDestination(void) { return m_pDest; }
	// 移動量の取得・セット
	/*D3DXVECTOR3  GetMove(void) { return m_move; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }*/
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
	// ドリフトフラグの取得・セット
	bool GetDriftLeft(void) { return m_bDriftLeft; }
	void SetDriftLeft(bool bDrift) { m_bDriftLeft = bDrift; }
	bool GetDriftRight(void) { return m_bDriftRight; }
	void SetDriftRight(bool bDrift) { m_bDriftRight = bDrift; }
	// ヒット状態の取得・セット
	bool  GetHitFrag(void) { return m_bHit; }
	void SetHitFrag(bool bHit) { m_bHit = bHit; }
	// チェインポイント数の取得・セット・加算
	int  GetMaxSpeed(void) { return m_nMaxSpeed; }
	void SetMaxSpeed(int nSpeed) { m_nMaxSpeed = nSpeed; }

	// プレイヤー番号の取得
	int GetPlayerNum(void) { return m_nPlayerNum; }

	void HitItem(bool bSafe);

	

private:
	void MoveControll(void);
	void Gravity(void);
	void Evolution(void);
	void Drift(void);

	// メンバ変数
	static CModel::Model m_model[MAX_PARTS_NUM];    // モデル構造体
	static int m_nNumModel;                         // モデルの数
	static int m_nNumEvolutionParts[MAX_EVOLUTION]; // 進化ごとのパーツ数
	//D3DXVECTOR3 m_move;        // 移動量
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
	CDestination *m_pDest;     // 移動移動目標
	bool m_bDriftLeft;         // ドリフト左
	bool m_bDriftRight;        // ドリフト右
	bool m_bHit;               // ヒット状態フラグ
	int m_nCntHit;             // ヒット状態解除時のカウント
	int m_nMaxSpeed;           // 最大速度
};

#endif