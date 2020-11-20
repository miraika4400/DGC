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

//*****************************
// �}�N����`
//*****************************
#define MODEL_PATH "./data/Models/testplayer.x"       //���f���̃p�X
#define PLAYER_SPEED 100                               // �v���C���[���x
#define PLAYER_MOVE_RATE 0.05f                        // �����̌W��
#define PLAYER_GRAVITY D3DXVECTOR3(0.0f,-40.0f,0.0f)   // �d�͗�
#define PLAYER_GRAVITY_RATE 0.1f                     // �d�͂̌W��
#define PLAYER_DIRECTION_RATE 0.1f                   // �����̌W��
#define PLAYER_RADIUS 150

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
LPD3DXMESH   CPlayer::m_pMeshModel = NULL;   	//���b�V�����ւ̃|�C���^
LPD3DXBUFFER CPlayer::m_pBuffMatModel = NULL;	//�}�e���A�����ւ̃|�C���^
DWORD        CPlayer::m_nNumMatModel = 0;	    //�}�e���A�����̐�
LPDIRECT3DTEXTURE9 CPlayer::m_apTexture[MAX_TEXTURE] = {}; // �e�N�X�`��

//******************************
// �R���X�g���N�^
//******************************
CPlayer::CPlayer() :CModel(OBJTYPE_PLAYER)
{
	// �ϐ��̃N���A
	m_move = VEC3_ZERO;       // �ړ���
	m_nPlayerNum = 0;         // �v���C���[�ԍ�
	m_gravityVec = VEC3_ZERO; // �d�͗�
	m_bGravity = true;        // �d�̓t���O
	m_pCollision = NULL;      // �R���W����
	m_nNumCheckpoint = 0;     // �`���b�N�|�C���g��
	m_bGoal = false;          // �S�[���t���O
	m_bMove = false;          // �ړ��t���O
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

	return pPlayer;
}

//******************************
// �e�N�X�`���̃��[�h
//******************************
HRESULT CPlayer::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_PATH,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel,
		NULL,
		&m_nNumMatModel,
		&m_pMeshModel);

	// �p�X�̕�����i�[�p
	char chPath[64];

	// �e�N�X�`���̓ǂݍ���
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();
	for (int nCnt = 0; nCnt < (int)m_nNumMatModel; nCnt++)
	{
		if (pMat[nCnt].pTextureFilename != NULL)
		{
			// �e�N�X�`�����𕶎���ɕϊ�
			sprintf(chPath, "%s", pMat[nCnt].pTextureFilename);
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice, chPath, &m_apTexture[nCnt]);
		}
	}
	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CPlayer::Unload(void)
{
	//���b�V���̔j��
	if (m_pMeshModel != NULL)
	{
		m_pMeshModel->Release();
		m_pMeshModel = NULL;
	}
	//�}�e���A���̔j��
	if (m_pBuffMatModel != NULL)
	{
		m_pBuffMatModel->Release();
		m_pBuffMatModel = NULL;
	}
}


//******************************
// ����������
//******************************
HRESULT CPlayer::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}

	// ���f�����̊��蓖��
	BindModel(m_pMeshModel, m_pBuffMatModel, m_nNumMatModel);
	
	// �e�N�X�`���̊��蓖��
	for (int nCnt = 0; nCnt < (int)m_nNumMatModel; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			BindTexture(nCnt, m_apTexture[nCnt]);
		}
	}
	// �ϐ��̏�����
	m_bGravity = true;    // �d�̓t���O
	m_nNumCheckpoint = 0; // �`�F�b�N�|�C���g��
	m_bGoal = false;      // �S�[���t���O
	m_bMove = false;          // �ړ��t���O

	return S_OK;
}

//******************************
// �I������
//******************************
void CPlayer::Uninit(void)
{
	CModel::Uninit();
}

//******************************
// �X�V����
//******************************
void CPlayer::Update(void)
{
	// �ړ�����
	MoveControll();
	// �d��
	Gravity();
	
	// �����蔻��̈ʒu�X�V
	m_pCollision->SetPos(GetPos());
}

//******************************
// �`�揈��
//******************************
void CPlayer::Draw(void)
{
	CModel::Draw();
}

//******************************
// ����̊Ǘ�
//******************************
void CPlayer::MoveControll(void)
{
	// ���W
	D3DXVECTOR3 pos = GetPos();
	//�ړ��ʂ̖ڕW�l
	D3DXVECTOR3 moveDest = VEC3_ZERO;

	// �J�����̌����̎擾
	float fCameraAngle = CGame::GetCamera(m_nPlayerNum)->GetAngle();
#if 1
	if (m_bMove)
	{
		// �W���C�X�e�B�b�N�̎擾
		DIJOYSTATE js = CManager::GetJoypad()->GetStick(m_nPlayerNum);
		
		moveDest.x = cosf(fCameraAngle)* PLAYER_SPEED;
		moveDest.z = sinf(fCameraAngle)* PLAYER_SPEED;
	}
#else
	// �W���C�X�e�B�b�N�̎擾
	DIJOYSTATE js = CManager::GetJoypad()->GetStick(m_nPlayerNum);

	moveDest.x = cosf(fCameraAngle)* PLAYER_SPEED;
	moveDest.z = sinf(fCameraAngle)* PLAYER_SPEED;

#endif
	// ����
	m_move += (moveDest - m_move) * PLAYER_MOVE_RATE;

	// �ړ��ʂ𑫂�
	pos += m_move;

	// ���W�̃Z�b�g
	SetPos(pos);

	// �v���C���[�̌������J�����ɍ��킹��
	D3DXVECTOR3 rot=GetRot();
	rot.y = -(fCameraAngle - D3DXToRadian(90));
	SetRot(rot);
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
