//=============================================================================
//
// scene2d�w�b�_ [scene2d.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//*****************************
//�N���X��`
//*****************************

//2d�|���S���N���X
class CScene2d : public CScene
{
public:
	// �����o�֐�
	CScene2d(int nPriority = OBJTYPE_NONE);
	~CScene2d();
	static CScene2d *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(const LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }

	// ���S���W�̃Z�b�g�A�擾
	void SetPos(const D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	// ��]�p�x�̃Z�b�g�A�擾
	void SetAngle(const float fAngle) { m_fAngle = fAngle; }
	float GetAngle(void) { return m_fAngle; }
	// �T�C�Y�̃Z�b�g�A�擾
	void SetSize(const D3DXVECTOR3 size);
	D3DXVECTOR3 GetSize(void) { return m_size; }
	// �J���[�̃Z�b�g�A�擾
	void SetColor(const D3DXCOLOR col);                  
	D3DXCOLOR GetColor(void) { return m_col; }

	void SetTextureUV(const D3DXVECTOR2 uv[NUM_VERTEX]); // �e�N�X�`����UV���W�̃Z�b�g
	
private:
	// �����o�ϐ�
	LPDIRECT3DTEXTURE9		m_pTexture;	 // �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	 // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3	m_pos;                   // �|���S���̈ʒu
	float m_fAngle;                      // �|���S���̉�]�p�x
    D3DXVECTOR3 m_size;                  // �|���S���̃T�C�Y
	D3DXCOLOR m_col;
};

#endif