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
#include "model_hierarchy.h"

//*****************************
// �}�N����`
//*****************************
#define MAX_EVOLUTION 4        // �i���̒i�K��
#define PLAYER_SPEED 100       // �v���C���[���x
#define PLAYER_MOVE_RATE 0.05f // �����̌W��

//*****************************
// �O���錾
//*****************************
class CCollision;

//*****************************
// �N���X��`
//*****************************

// �p�[�e�B�N���N���X
class CPlayer : public CModelHierarchy
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
	// �A�C�e�����̎擾�E�Z�b�g�E���Z
	int  GetItemNum(void) { return m_nCollectItem; }
	void SetItemNum(int nNum) { m_nCollectItem = nNum; }
	void AdtItemNum(void) { m_nCollectItem++; }
	// �`�F�C���|�C���g���̎擾�E�Z�b�g�E���Z
	int  GetChainNum(void) { return m_nChain; }
	void SetChainNum(int nNum) { m_nChain = nNum; }
	void AdtChainNum(void) { m_nChain++; }
	// �ړ��t���O�̎擾�E�Z�b�g
	bool GetMoveFlag(void) { return m_bMove; }
	void SetMoveFlag(bool bMove) { m_bMove = bMove; }

	// �v���C���[�ԍ��̎擾
	int GetPlayerNum(void) { return m_nPlayerNum; }

	void HitItem(bool bSafe);

	void ZeroMove(void) { m_move = VEC3_ZERO; }

private:
	void MoveControll(void);
	void Gravity(void);
	void Evolution(void);

	// �����o�ϐ�
	static CModel::Model m_model[MAX_PARTS_NUM];             // ���f���\����
	static int m_nNumModel;
	D3DXVECTOR3 m_move;        // �ړ���
	int m_nPlayerNum;          // �v���C���[�ԍ�
	D3DXVECTOR3 m_gravityVec;  // �d��
	bool m_bGravity;           // �d�̓t���O
	CCollision*m_pCollision;   // �R���W�����N���X�̃|�C���^
	int m_nNumCheckpoint;      // �`�F�b�N�|�C���g��
	bool m_bGoal;              // �S�[���t���O
	bool m_bMove;              // �ړ��ł����ԉ�����p
	int m_nChain;              // �`�F�C����
	int m_nCollectItem;        // ��������A�C�e����
	int m_nNumEvolution;       // �i����
	static int m_nNumEvolutionParts[MAX_EVOLUTION];
};

#endif