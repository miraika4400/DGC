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
#define HIERARCHY_TEXT_PATH "./data/Texts/hierarchy/CatData_Choco.txt"       //���f���̃p�X
#define PLAYER_SPEED 100                               // �v���C���[���x
#define PLAYER_MOVE_RATE 0.05f                        // �����̌W��
#define PLAYER_GRAVITY D3DXVECTOR3(0.0f,-40.0f,0.0f)   // �d�͗�
#define PLAYER_GRAVITY_RATE 0.1f                     // �d�͂̌W��
#define PLAYER_DIRECTION_RATE 0.1f                   // �����̌W��
#define PLAYER_RADIUS 150

// �i�����̃p�[�c��
#define EVOLUTION_0 2             // ����
#define EVOLUTION_1 4             // 2�i�K��
#define EVOLUTION_2 8             // 3�i�K��
#define EVOLUTION_3 m_nNumModel   // 4�i�K��


//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
//LPD3DXMESH   CPlayer::m_pMeshModel = NULL;   	//���b�V�����ւ̃|�C���^
//LPD3DXBUFFER CPlayer::m_pBuffMatModel = NULL;	//�}�e���A�����ւ̃|�C���^
//DWORD        CPlayer::m_nNumMatModel = 0;	    //�}�e���A�����̐�
//LPDIRECT3DTEXTURE9 CPlayer::m_apTexture[MAX_TEXTURE] = {}; // �e�N�X�`��
CModel::Model CPlayer::m_model[MAX_PARTS_NUM] = {};
int CPlayer::m_nNumModel = 0;
int CPlayer::m_nNumEvolutionParts[MAX_EVOLUTION]=
{
	EVOLUTION_0,
	EVOLUTION_1,
	EVOLUTION_2,
	EVOLUTION_3,
};
//******************************
// �R���X�g���N�^
//******************************
CPlayer::CPlayer() :CModelHierarchy(OBJTYPE_PLAYER)
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
	m_nChain = 0;             // �`�F�C����
	m_nCollectItem = 0;       // ��������A�C�e����
	m_nNumEvolution = 0;      // �i����
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
	//// �f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	////X�t�@�C���̓ǂݍ���
	//D3DXLoadMeshFromX(MODEL_PATH,
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&m_model.pBuffMat,
	//	NULL,
	//	&m_model.nNumMat,
	//	&m_model.pMesh);

	//// �p�X�̕�����i�[�p
	//char chPath[64];

	//// �e�N�X�`���̓ǂݍ���
	//D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_model.pBuffMat->GetBufferPointer();
	//for (int nCnt = 0; nCnt < (int)m_model.nNumMat; nCnt++)
	//{
	//	if (pMat[nCnt].pTextureFilename != NULL)
	//	{
	//		// �e�N�X�`�����𕶎���ɕϊ�
	//		sprintf(chPath, "%s", pMat[nCnt].pTextureFilename);
	//		// �e�N�X�`���̓ǂݍ���
	//		D3DXCreateTextureFromFile(pDevice, chPath, &m_model.apTexture[nCnt]);
	//	}
	//}

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
	m_bGravity = true;    // �d�̓t���O
	m_nNumCheckpoint = 0; // �`�F�b�N�|�C���g��
	m_bGoal = false;      // �S�[���t���O
	m_bMove = false;      // �ړ��t���O
	m_nChain = 0;         // �`�F�C����
	m_nCollectItem = 0;   // ��������A�C�e����

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
	MoveControll();
	// �d��
	Gravity();
	
	// �����蔻��̈ʒu�X�V
	m_pCollision->SetPos(GetPos());

	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_E))
	{
		Evolution();
	}
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
	{
		m_nChain = 0;
		CDebugLog::Init();
		CDebugLog::Print("Out");
	}
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
#if 0
	if (m_bMove)
	{
		moveDest.x = cosf(fCameraAngle)* PLAYER_SPEED;
		moveDest.z = sinf(fCameraAngle)* PLAYER_SPEED;
	}
#else
	if (CManager::GetKeyboard()->GetKeyPress(DIK_W))
	{
		moveDest.x = cosf(fCameraAngle)* PLAYER_SPEED;
		moveDest.z = sinf(fCameraAngle)* PLAYER_SPEED;
	}

#endif
	// ����
	m_move += (moveDest - m_move) * PLAYER_MOVE_RATE;

	// �ړ��ʂ𑫂�
	pos += m_move;

	// ���W�̃Z�b�g
	SetPos(pos);

	// �v���C���[�̌������J�����ɍ��킹��
	D3DXVECTOR3 rot = GetRot();
	rot.y = -(fCameraAngle + D3DXToRadian(90));
	//rot.x += 0.01f;
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

void CPlayer::Evolution(void)
{
	// �i���񐔂̃J�E���g
	m_nNumEvolution++;
	if (m_nNumEvolution >= MAX_EVOLUTION)
	{// �i�������ő�𒴂��Ȃ��悤��
		m_nNumEvolution = MAX_EVOLUTION - 1;
	}

	// �p�[�c���̓ǂݍ���
	CModelHierarchy::Init(m_nNumEvolutionParts[m_nNumEvolution], &m_model[0], HIERARCHY_TEXT_PATH);
}
