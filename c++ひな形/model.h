//=============================================================================
//
// モデル処理 [model.h]
// Author : 山田陵太
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "scene.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_TEXTURE 64

//=============================================================================
//モデルクラス
//=============================================================================
class CModel : public CScene
{
public:
	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CModel(int nPriority = OBJTYPE_NONE);
	~CModel();

	static CModel *Create(D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPD3DXMESH GetMesh(void)const;

	void SetPos(const D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void)const;
	void SetRot(const D3DXVECTOR3 rot);
	D3DXVECTOR3 GetRot(void)const;
	void BindModel(LPD3DXMESH pMeshModel, LPD3DXBUFFER pBuffMatModel, DWORD nNumMatModel);
	void BindTexture(const int nIndex,const LPDIRECT3DTEXTURE9 pTexture);
private:
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE]; // テクスチャ
	LPD3DXMESH m_pMeshModel;	//メッシュ情報へのポインタ
	LPD3DXBUFFER m_pBuffMatModel;	//マテリアル情報へのポインタ
	DWORD m_nNumMatModel;	//マテリアル情報の数
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_rot;	//向き
	D3DXMATRIX m_mtxWorldModel;	//ワールドマトリックス
};
#endif 