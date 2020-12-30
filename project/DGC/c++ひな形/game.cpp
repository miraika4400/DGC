////////////////////////////////////////////////////
//
//    �Q�[���N���X�̏���[game.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//=============================
// �C���N���[�h
//=============================
#include "game.h"
#include "bg.h"
#include "number.h"
#include "score.h" 
#include "mouse.h"
#include "camera.h"
#include "fade.h"
#include "keyboard.h"
#include "particle.h"
#include "time.h"
#include "course.h"
#include "player.h"
#include "light.h"
#include "item.h"
#include "rank.h"
#include "file.h"

//=============================
// �}�N����`
//=============================
#define FILE_NAME "data/data.txt"

//=============================
// �ÓI�����o�ϐ��錾
//=============================
CCamera *CGame::m_pCamera[MAX_PLAYER_NUM] = {};   // �J����
CPlayer *CGame::m_pPlayer[MAX_PLAYER_NUM] = {};   // �v���C���[
CLight *CGame::m_pLight = NULL;		// ���C�g�N���X�̃|�C���^�ϐ�
int CGame::m_nNumPlayer = 1;        // �v���C���[�l��

//=============================
// �R���X�g���N�^
//=============================
CGame::CGame()
{
}

//=============================
// �f�X�g���N�^
//=============================
CGame::~CGame()
{
}

//=============================
// �N���G�C�g
//=============================
CGame * CGame::Create()
{
	// �������̊m��
	CGame *pGame = new CGame;
	// ������
	pGame->Init(); 
	return pGame;
}

//=============================
// ����������
//=============================
HRESULT CGame::Init(void)
{
	// �|�[�Y�̏�����
	CManager::SetActivePause(false);

	// �}�b�v�̐���
	CCourse::Create(CCourse::COURSE_EASY);
	for (int nCntPlayer = 0; nCntPlayer < m_nNumPlayer; nCntPlayer++)
	{
		// �v���C���[�̐���
		m_pPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 300.0f), nCntPlayer);
		// �J�����̐���
		m_pCamera[nCntPlayer] = CCamera::Create(nCntPlayer);
	}
	//���C�g�N���X�̐���
	m_pLight = new CLight;
	// ������
	if (m_pLight != NULL)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}
	
	CItem::Create(D3DXVECTOR3(0.0    , 50.0f, -1000.0f), CItem::ITEM_COLORLESS);
	CItem::Create(D3DXVECTOR3(500.0f , 50.0f, -1000.0f), CItem::ITEM_RED);
	CItem::Create(D3DXVECTOR3(-500.0f, 50.0f, -1000.0f), CItem::ITEM_BLUE);
	CItem::Create(D3DXVECTOR3(0.0    , 50.0f, -1500.0f), CItem::ITEM_YELLOW);
	CItem::Create(D3DXVECTOR3(0.0    , 50.0f, -2000.0f), CItem::ITEM_GREEN);

    // �A�C�e���z�u
    CFile::Create()->Read(FILE_NAME);

	return S_OK;
}

//=============================
// �I������
//=============================
void CGame::Uninit(void)
{
	// �J����
	for (int nCntCamera = 0; nCntCamera < m_nNumPlayer; nCntCamera++)
	{
		if (m_pCamera[nCntCamera] != NULL)
		{
			m_pCamera[nCntCamera]->Uninit();
			delete m_pCamera[nCntCamera];
			m_pCamera[nCntCamera] = NULL;
		}
	}
	// ���C�g
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	// �J������
	Release();

    CFile::GetInstance()->Uninit();
}


//=============================
// �X�V����
//=============================
void CGame::Update(void)
{
	// �A�C�e����]
	CItem::ItemRotasion();

	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN))
	{
		CManager::GetFade()->SetFade(CManager::MODE_RESULT);
	}
	// �J�����N���X�̃A�b�v�f�[�g
	for (int nCntPlayer = 0; nCntPlayer < m_nNumPlayer; nCntPlayer++)
	{
		if (m_pCamera[nCntPlayer] != NULL)
		{
			m_pCamera[nCntPlayer]->Update();
		}
	}
	CRank::RankManage();
}


//=============================
// �`�揈��
//=============================
void CGame::Draw(void)
{
}