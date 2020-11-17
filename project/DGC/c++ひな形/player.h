//=============================================================================
//
// player�w�b�_ [player.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _PLAYER_H_
#define _PLAYER_H_

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
class CPlayer : public CModel
{
public:

	//�����o�֐�
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

	// �d�̓t���O�̎擾�E�Z�b�g
	bool GetActiveGravity(void) { return m_bGravity; }
	void SetActiveGravity(bool bBool) { m_bGravity = bBool; }
	// �`�F�b�N�|�C���g���̎擾�E�Z�b�g�E���Z
	int GetCheckNum(void) { return m_nNumCheckpoint; }
	void SetCheckNum(int nNum) { m_nNumCheckpoint = nNum; }
	void AddCheckNum(void) { m_nNumCheckpoint++; }
	// �ړ��t���O�̎擾�E�Z�b�g
	bool GetMoveFlag(void) { return m_bMove; }
	void SetMoveFlag(bool bMove) { m_bMove = bMove; }

	void ZeroMove(void) { m_move = VEC3_ZERO; }
private:
	void MoveControll(void);
	void Gravity(void);
	// �����o�ϐ�
	static LPD3DXMESH m_pMeshModel;	                    //���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMatModel;	            //�}�e���A�����ւ̃|�C���^
	static DWORD m_nNumMatModel;	                    //�}�e���A�����̐�
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE]; // �e�N�X�`��
	D3DXVECTOR3 m_move;        // �ړ���
	int m_nPlayerNum;          // �v���C���[�ԍ�
	D3DXVECTOR3 m_gravityVec;  // �d��
	bool m_bGravity;           // �d�̓t���O
	CCollision*m_pCollision;   // �R���W�����N���X�̃|�C���^
	int m_nNumCheckpoint;      // �`�F�b�N�|�C���g��
	bool m_bGoal;              // �S�[���t���O
	bool m_bMove;              // �ړ��ł����ԉ�����p
};

#endif