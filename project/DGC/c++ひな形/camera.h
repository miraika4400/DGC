//=============================================================================
//
// cameraヘッダ [camera.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "scene2d.h"

//*****************************
// クラス定義
//*****************************

//カメラクラス
class CCamera
{
public:
	//メンバ関数
	CCamera();
	~CCamera();

	static CCamera *Create(int nNmPlayer);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	D3DXVECTOR3 GetPos(void) { return m_posV; }

	D3DXMATRIX GetViewMtx(void) { return m_mtxView; }
	D3DXMATRIX GetProjectionMtx(void) { return m_mtxProjection; }
	float GetAngle(void) { return m_fAngle; }
	D3DXVECTOR3 GetposV(void) { return m_posV; }
	D3DXVECTOR3 GetposR(void) { return m_posR; }
private:
	// メンバ変数
	D3DXVECTOR3 m_posV;//カメラの座標
	D3DXVECTOR3 m_posR;//注視点
	D3DXVECTOR3 m_vecU;//上方向ベクトル
	D3DXMATRIX  m_mtxProjection;//プロジェクションマトリックス
	D3DXMATRIX  m_mtxView;//ビューマトリックス
	int m_nNmPlayer;      // どのプレイヤーのカメラか
	float m_fAngle;
	// 球面座標
	float m_fRad;   // 目標からの距離
	float m_fTheta;  // 角度シータ
	float m_fPhi;    // 角度ファイ
};

#endif