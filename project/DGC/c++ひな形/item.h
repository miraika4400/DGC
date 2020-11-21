//=============================================================================
//
// item�w�b�_ [item.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _ITEM_H_
#define _ITEM_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "model.h"

//*****************************
// �}�N����`
//*****************************

//*****************************
// �O���錾
//*****************************
class CCollision;

//*****************************
// �N���X��`
//*****************************

// �p�[�e�B�N���N���X
class CItem : public CModel
{
public:
	//==========================
	// ��
	//==========================
	// �A�C�e���^�C�v
	typedef enum
	{
		
		ITEM_RED = 0,        // ��
		ITEM_BLUE,           // ��
		ITEM_YELLOW,         // ��
		ITEM_GREEN,          // ��
		ITEM_COLORLESS,      // ���F�A�C�e��
		ITEM_MAX
	}ITEM_TYPE;

	//==========================
	//�����o�֐�
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

	static Model m_model[ITEM_MAX];          // ���f���\����
	static char *m_pTexPath[ITEM_MAX];       // �e�N�X�`���̃p�X
	CCollision*m_pCollision;                 // �����蔻��
	ITEM_TYPE m_itemType;                    // �A�C�e���^�C�v
	static D3DXVECTOR3 m_rot;                // �S�A�C�e�����ʂŃ��b�g�Œ�
};
#endif