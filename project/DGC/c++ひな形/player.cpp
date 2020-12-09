////////////////////////////////////////////////////
//
//    particle�N���X�̏���[particle.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"
#include "debug_log.h"
#include "collision.h"
#include "destination.h"
#include "mouse.h"
#include "item.h"

//*****************************
// �}�N����`
//*****************************
#define MODEL_PATH "./data/Models/testplayer.x"       //���f���̃p�X
#define HIERARCHY_TEXT_PATH "./data/Texts/hierarchy/CatData_Choco.txt"       //���f���̃p�X
#define PLAYER_GRAVITY D3DXVECTOR3(0.0f,-120.0f,0.0f)   // �d�͗�
#define PLAYER_GRAVITY_RATE 0.3f                     // �d�͂̌W��
#define PLAYER_DIRECTION_RATE 0.1f                   // �����̌W��
#define PLAYER_RADIUS 150                            // �����蔻��̔��a
#define HIT_FRAME  100                               // �q�b�g��Ԃ̃t���[����
#define ACCELERATION_FRAME  100                      // ���������t���[��
// �v���C���[���x
#define PLAYER_SPEED_E1 100       // �v���C���[���x*1�i�K��
#define PLAYER_SPEED_E2 120       // �v���C���[���x*2�i�K��
#define PLAYER_SPEED_E3 140       // �v���C���[���x*3�i�K��
#define PLAYER_SPEED_E4 160       // �v���C���[���x*4�i�K��
#define PLAYER_SPEED_HIT 20       // ��Q���q�b�g���̃v���C���[���x
// �����x
#define PLAYER_MOVE_RATE_E1 0.03f  // �����̌W��*1�i�K��
#define PLAYER_MOVE_RATE_E2 0.03f  // �����̌W��*2�i�K��
#define PLAYER_MOVE_RATE_E3 0.025f // �����̌W��*3�i�K��
#define PLAYER_MOVE_RATE_E4 0.02f  // �����̌W��*4�i�K��
// �i�����̃p�[�c��
#define EVOLUTION_0 2             // ����
#define EVOLUTION_1 4             // 2�i�K��
#define EVOLUTION_2 8             // 3�i�K��
#define EVOLUTION_3 m_nNumModel   // 4�i�K��

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
CModel::Model CPlayer::m_model[MAX_PARTS_NUM] = {};
int CPlayer::m_nNumModel = 0;
// �i�����Ƃ̃p�[�c��
int CPlayer::m_nNumEvolutionParts[MAX_EVOLUTION]=
{
	EVOLUTION_0,
	EVOLUTION_1,
	EVOLUTION_2,
	EVOLUTION_3,
};
// �i�����Ƃ̍ō����x
int CPlayer::m_nSpeedData[MAX_EVOLUTION] =
{
	PLAYER_SPEED_E1,       // �v���C���[���x*1�i�K��
	PLAYER_SPEED_E2,       // �v���C���[���x*2�i�K��
	PLAYER_SPEED_E3,       // �v���C���[���x*3�i�K��
	PLAYER_SPEED_E4,       // �v���C���[���x*4�i�K��
};

// �i�����Ƃ̉����x
float CPlayer::m_fRateData[MAX_EVOLUTION] =
{
	PLAYER_MOVE_RATE_E1,   // �����̌W��*1�i�K��
	PLAYER_MOVE_RATE_E2,   // �����̌W��*2�i�K��
	PLAYER_MOVE_RATE_E3,   // �����̌W��*3�i�K��
	PLAYER_MOVE_RATE_E4,   // �����̌W��*4�i�K��
};

//******************************
// �R���X�g���N�^
//******************************
CPlayer::CPlayer() :CModelHierarchy(OBJTYPE_PLAYER)
{
	// �ϐ��̃N���A
	//m_move = VEC3_ZERO;         // �ړ���
	m_nPlayerNum = 0;           // �v���C���[�ԍ�
	m_gravityVec = VEC3_ZERO;   // �d�͗�
	m_bGravity = true;          // �d�̓t���O
	m_pCollision = NULL;        // �R���W����
	m_nNumCheckpoint = 0;       // �`���b�N�|�C���g��
	m_bGoal = false;            // �S�[���t���O
	m_bMove = false;            // �ړ��t���O
	m_nChain = 0;               // �`�F�C����
	m_nCollectItem = 0;         // ��������A�C�e����
	m_nNumEvolution = 0;        // �i����
	m_pDest = NULL;             // �ړ��ڕW�N���X
	m_bDriftLeft = false;       // �h���t�g��
	m_bDriftRight = false;      // �h���t�g�E
	m_bHit = false;             // �q�b�g��ԃt���O
	m_nCntHit = 0;              // �q�b�g��ԉ������̃J�E���g
	m_nMaxSpeed = PLAYER_SPEED_E1; // �ő呬�x
	m_bAcceleration = false;      // �����t���O
	m_fMoveRate = PLAYER_MOVE_RATE_E1;// �����̌W��
}

//******************************
// �f�X�g���N�^
//******************************
CPlayer::~CPlayer()
{
}

//******************************
// �N���G�C�g
//******************************
CPlayer * CPlayer::Create(D3DXVECTOR3 pos,int nPlayerNum)
{
	// �������̊m��
	CPlayer *pPlayer;
	pPlayer = new CPlayer;
	pPlayer->m_nPlayerNum = nPlayerNum;
	// ������
	pPlayer->Init();
	
	// �e�l�̑���E�Z�b�g
	pPlayer->SetPos(pos);
	pPlayer->SetObjType(OBJTYPE_PLAYER); // �I�u�W�F�N�g�^�C�v
	// �����蔻��̐���
	pPlayer->m_pCollision = CCollision::CreateSphere(pos, PLAYER_RADIUS);
	
	// �ړ��ڕW�̐���
	pPlayer->m_pDest = CDestination::Create(nPlayerNum, pos);
	return pPlayer;
}

//******************************
// �e�N�X�`���̃��[�h
//******************************
HRESULT CPlayer::Load(void)
{

	// ���f���̓ǂݍ���
	LoadModels(HIERARCHY_TEXT_PATH, &m_model[0], &m_nNumModel);
	// �ŏI�i�����p�[�c��
	m_nNumEvolutionParts[MAX_EVOLUTION - 1] = m_nNumModel;

	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CPlayer::Unload(void)
{
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		//���b�V���̔j��
		if (m_model[nCnt].pMesh != NULL)
		{
			m_model[nCnt].pMesh->Release();
			m_model[nCnt].pMesh = NULL;
		}
		//�}�e���A���̔j��
		if (m_model[nCnt].pBuffMat != NULL)
		{
			m_model[nCnt].pBuffMat->Release();
			m_model[nCnt].pBuffMat = NULL;
		}
	}
}


//******************************
// ����������
//******************************
HRESULT CPlayer::Init(void)
{
	if (FAILED(CModelHierarchy::Init(m_nNumEvolutionParts[m_nNumEvolution], &m_model[0], HIERARCHY_TEXT_PATH)))
	{
		return E_FAIL;
	}

	// ���f�����̊��蓖��
	//BindModel(m_model.pMesh, m_model.pBuffMat, m_model.nNumMat);
	//
	//// �e�N�X�`���̊��蓖��
	//for (int nCnt = 0; nCnt < (int)m_model.nNumMat; nCnt++)
	//{
	//	if (m_model.apTexture[nCnt] != NULL)
	//	{
	//		BindTexture(nCnt, m_model.apTexture[nCnt]);
	//	}
	//}

	// �ϐ��̏�����
	m_bGravity = true;                 // �d�̓t���O
	m_nNumCheckpoint = 0;              // �`�F�b�N�|�C���g��
	m_bGoal = false;                   // �S�[���t���O
	m_bMove = false;                   // �ړ��t���O
	m_nChain = 0;                      // �`�F�C����
	m_nCollectItem = 0;                // ��������A�C�e����
	m_bDriftLeft = false;              // �h���t�g��
	m_bDriftRight = false;             // �h���t�g�E
	m_bHit = false;                    // �q�b�g�t���O
	m_nCntHit = 0;                     // �q�b�g���̃J�E���g
	m_nMaxSpeed = PLAYER_SPEED_E1;     // �ő呬�x
	m_bAcceleration = false;           // �����t���O
	m_fMoveRate = PLAYER_MOVE_RATE_E1; // �����̌W��

	return S_OK;
}

//******************************
// �I������
//******************************
void CPlayer::Uninit(void)
{
	CModelHierarchy::Uninit();
}

//******************************
// �X�V����
//******************************
void CPlayer::Update(void)
{
	// �ړ�����
	//MoveControll();
	// �d��
	Gravity();
	// �h���t�g�̏���
	Drift();

	// �����蔻��̈ʒu�X�V
	m_pCollision->SetPos(GetPos());

	// �q�b�g��Ԃ̊Ǘ�
	if (m_bHit)
	{// �q�b�g��Ԃ̎�
		m_nCntHit--;
		if (m_nCntHit <= 0)
		{// �J�E���g��0�ȉ��̎�
			// �q�b�g�t���O��false��
			m_bHit = false;
		}
		m_nMaxSpeed = PLAYER_SPEED_HIT;
	}
	else
	{
		// �ō����x�̍X�V
		m_nMaxSpeed = m_nSpeedData[m_nNumEvolution];
	}

#ifdef _DEBUG
	// �f�o�b�O�R�}���h

	// �i��
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_E))
	{
		Evolution();
	}

	// �A�C�e���h���b�v
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_D))
	{
		CItem::DropItemCircle(GetPos(), 5, m_nPlayerNum);
	}
	if (CManager::GetKeyboard()->GetKeyPress(DIK_S))
	{
		CItem::DropItem(GetPos(), m_nPlayerNum);
	}

	// �X�g�b�v
	if (CManager::GetKeyboard()->GetKeyPress(DIK_SPACE))
	{
		m_bMove = false;
	}
	else if (CManager::GetKeyboard()->GetKeyRelease(DIK_SPACE))
	{
		m_bMove = true;
	}

#endif
}

//******************************
// �`�揈��
//******************************
void CPlayer::Draw(void)
{
	CModelHierarchy::Draw();
}

//******************************
// �A�C�e���ɓ��������Ƃ��̏���
//******************************
void CPlayer::HitItem(bool bSafe)
{
	if (bSafe)
	{// �����A�C�e���̓��������Ƃ�
		m_nCollectItem++;
		m_nChain++;
		CDebugLog::Init();
		CDebugLog::Print("Safe");
	}
	else
	{// �����ȊO�̃A�C�e���ɓ��������Ƃ�
		m_nChain = 0;
		CDebugLog::Init();
		CDebugLog::Print("Out");
		m_bHit = true;
		m_nCntHit = HIT_FRAME;

		CItem::DropItemCircle(GetPos(), 5, m_nPlayerNum);
		CGame::GetCamera(m_nPlayerNum)->Shake(true);
	}
}

//******************************
// ����̊Ǘ�
//******************************
void CPlayer::MoveControll(void)
{
//	// ���W
//	D3DXVECTOR3 pos = GetPos();
//	//�ړ��ʂ̖ڕW�l
//	D3DXVECTOR3 moveDest = VEC3_ZERO;
//
//	// �J�����̌����̎擾
//	float fCameraAngle = CGame::GetCamera(m_nPlayerNum)->GetAngle();
//#if 0
//	if (m_bMove)
//	{
//		moveDest.x = cosf(fCameraAngle)* PLAYER_SPEED;
//		moveDest.z = sinf(fCameraAngle)* PLAYER_SPEED;
//	}
//
//#else
//	if (CManager::GetKeyboard()->GetKeyPress(DIK_W))
//	{
//		moveDest.x = cosf(fCameraAngle)* PLAYER_SPEED;
//		moveDest.z = sinf(fCameraAngle)* PLAYER_SPEED;
//	}
//
//#endif
//	// ����
//	m_move += (moveDest - m_move) * PLAYER_MOVE_RATE;
//
//	// �ړ��ʂ𑫂�
//	pos += m_move;
//
//	// ���W�̃Z�b�g
//	SetPos(pos);
//
//	// �v���C���[�̌������J�����ɍ��킹��
//	D3DXVECTOR3 rot = GetRot();
//	rot.y = -(fCameraAngle + D3DXToRadian(90));
//	//rot.x += 0.01f;
//	SetRot(rot);
}

//******************************
// �d�͂̊Ǘ�
//******************************
void CPlayer::Gravity(void)
{
	if (m_bGravity)
	{// �d�̓t���O�������Ă���

		// �d�͗ʂ̐ݒ�
		m_gravityVec += (PLAYER_GRAVITY - m_gravityVec)*PLAYER_GRAVITY_RATE;

		// ���W�ɏd�͗ʂ̃v���X
		SetPos(GetPos() + m_gravityVec);

	}
	else
	{// �d�̓t���O�������ĂȂ��Ƃ�
		// ������
		m_gravityVec = VEC3_ZERO;
	}
}

//******************************
// �i��
//******************************
void CPlayer::Evolution(void)
{
	// �i���񐔂̃J�E���g
	m_nNumEvolution++;
	if (m_nNumEvolution >= MAX_EVOLUTION)
	{// �i�������ő�𒴂��Ȃ��悤��
		m_nNumEvolution = MAX_EVOLUTION - 1;
	}
	// �ō����x�̍X�V
	m_nMaxSpeed = m_nSpeedData[m_nNumEvolution];
	// �����x
	m_fMoveRate = m_fRateData[m_nNumEvolution];
	// �p�[�c���̓ǂݍ���
	CModelHierarchy::Init(m_nNumEvolutionParts[m_nNumEvolution], &m_model[0], HIERARCHY_TEXT_PATH);
}

//******************************
// �h���t�g
//******************************
void CPlayer::Drift(void)
{
	float fDistance = 0.0f;// �ړ��ڕW�Ƃ̋���

	if (!m_bDriftLeft && !m_bDriftRight)
	{// �h���t�g���t�@���X��Ԃ̎�

		// �L�[�{�[�h
		if (CManager::GetKeyboard()->GetKeyPress(DIK_LSHIFT))
		{
			if (CManager::GetMouse()->GetMouseMove().x > 0)
			{// �E�h���t�g
				m_bDriftRight = true;	
				
			}
			else if (CManager::GetMouse()->GetMouseMove().x < 0)
			{// ���h���t�g
				m_bDriftLeft = true;
			}
		}

		// �R���g���[���[
		if (CManager::GetJoypad()->GetJoystickPress(5, m_nPlayerNum))
		{
			if (CManager::GetJoypad()->GetStick(m_nPlayerNum).lX >= 10)
			{// �E�h���t�g
				m_bDriftRight = true;
			}
			else if (CManager::GetJoypad()->GetStick(m_nPlayerNum).lX <= -10)
			{// ���h���t�g
				m_bDriftLeft = true;
			}
		}
	}
	else
	{
		// �h���t�g��Ԃ̉���
		if (CManager::GetJoypad()->GetJoystickRelease(5, m_nPlayerNum) || CManager::GetKeyboard()->GetKeyRelease(DIK_LSHIFT))
		{
			m_bDriftLeft = false;
			m_bDriftRight = false;
		}
	}
	//if (m_pDest->GetDistanceDest() != fDistance)
	//{
	//	m_pDest->SetDistanceDest(fDistance);
	//}
}
