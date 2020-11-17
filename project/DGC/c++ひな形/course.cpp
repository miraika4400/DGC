////////////////////////////////////////////////////
//
//    course�N���X�̏���[course.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "course.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "player.h"
#include "checkpoint.h"
#include "wall.h"
#include "start.h"

//*****************************
// �}�N����`
//*****************************
#define MODEL_PATH "./data/Models/Syokyuu_Course.x"    //���f���̃p�X
#define HOVER_HEIGHT 50
//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
LPD3DXMESH   CCourse::m_pMeshModel[CCourse::COURSE_MAX] = {};   	//���b�V�����ւ̃|�C���^
LPD3DXBUFFER CCourse::m_pBuffMatModel[CCourse::COURSE_MAX] = {};	//�}�e���A�����ւ̃|�C���^
DWORD        CCourse::m_nNumMatModel[CCourse::COURSE_MAX] = {};	    //�}�e���A�����̐�
// �e�N�X�`���̃p�X�̊i�[
char *CCourse::m_pTexPath[CCourse::COURSE_MAX] =
{
	MODEL_PATH,
	MODEL_PATH,
	MODEL_PATH
};
//******************************
// �R���X�g���N�^
//******************************
CCourse::CCourse():CModel(OBJTYPE_MAP)
{
}

//******************************
// �f�X�g���N�^
//******************************
CCourse::~CCourse()
{
}

//******************************
// �N���G�C�g
//******************************
CCourse * CCourse::Create(COURSETYPE type)
{
	// �������̊m��
	CCourse *pMap;
	pMap = new CCourse;
	// �^�C�v�̐ݒ�
	pMap->m_courseType = type;
	// ������
	pMap->Init();

	// �e�l�̑���E�Z�b�g
	pMap->SetObjType(OBJTYPE_MAP); // �I�u�W�F�N�g�^�C�v
	
	return pMap;
}

//******************************
// �e�N�X�`���̃��[�h
//******************************
HRESULT CCourse::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	// �R�[�X�������[�v
	for (int nCntCourse = 0; nCntCourse < COURSE_MAX; nCntCourse++)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(m_pTexPath[nCntCourse],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMatModel[nCntCourse],
			NULL,
			&m_nNumMatModel[nCntCourse],
			&m_pMeshModel[nCntCourse]);

	}

	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CCourse::Unload(void)
{
	for (int nCnt = 0; nCnt < COURSE_MAX; nCnt++)
	{
		//���b�V���̔j��
		if (m_pMeshModel[nCnt] != NULL)
		{
			m_pMeshModel[nCnt]->Release();
			m_pMeshModel[nCnt] = NULL;
		}

		//�}�e���A���̔j��
		if (m_pBuffMatModel[nCnt] != NULL)
		{
			m_pBuffMatModel[nCnt]->Release();
			m_pBuffMatModel[nCnt] = NULL;
		}
	}
}


//******************************
// ����������
//******************************
HRESULT CCourse::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}

	// �e�N�X�`�����蓖��
	BindModel(m_pMeshModel[m_courseType],m_pBuffMatModel[m_courseType],m_nNumMatModel[m_courseType]);
	// �`�F�b�N�|�C���g�̐���
	CCheckPoint::Create(m_courseType);
	// �ǂ̐���
	CWall::Create(m_courseType);
	// �X�^�[�g�̐���
	CStart::Create(m_courseType);
	return S_OK;
}

//******************************
// �I������
//******************************
void CCourse::Uninit(void)
{
	CModel::Uninit();
}

//******************************
// �X�V����
//******************************
void CCourse::Update(void)
{
	// �����蔻��
	CollisionPlayer();
}

//******************************
// �`�揈��
//******************************
void CCourse::Draw(void)
{
	CModel::Draw();
}

//******************************
// �R�[�X���̓����蔻��
//******************************
void CCourse::CollisionPlayer(void)
{
	// �v���C���[�������[�v
	for (int nCntPlayer = 0; nCntPlayer < CGame::GetPlayerNum(); nCntPlayer++)
	{
		// �v���C���[���W�̎擾
		D3DXVECTOR3 playerPos = CGame::GetPlayer(nCntPlayer)->GetPos();

		BOOL bHit = FALSE;     // ���C���������Ă��邩
		float fDistance = 0.0f;// ���C���������Ă��鋗��

		// ���C
		D3DXIntersect(m_pMeshModel[m_courseType],
			&playerPos,
			&D3DXVECTOR3(0.0f, -1.0f, 0.0f),
			&bHit,
			NULL,
			NULL,
			NULL,
			&fDistance,
			NULL,
			NULL);

		if (bHit)
		{// ���C���������Ă�����

			if (fDistance <= HOVER_HEIGHT-1)
			{// ���ƃv���C���[�̋��������ȏ�ɕۂ�
				
				// �v���C���[�̍��W�̍X�V
				playerPos.y = (playerPos.y - fDistance) + HOVER_HEIGHT;
				CGame::GetPlayer(nCntPlayer)->SetPos(playerPos);

				if (CGame::GetPlayer(nCntPlayer)->GetActiveGravity())
				{// �d�̓t���O�������Ă���Ƃ�
					// �d�͂�؂�
					CGame::GetPlayer(nCntPlayer)->SetActiveGravity(false);
				}
			}
			else if (fDistance >= HOVER_HEIGHT - 1 && fDistance <= HOVER_HEIGHT + 20)
			{// ������x�͈̔͂�������R�[�X�ɋz���t����
				
		        // �v���C���[�̍��W�̍X�V
				playerPos.y = (playerPos.y - fDistance) + HOVER_HEIGHT;
				CGame::GetPlayer(nCntPlayer)->SetPos(playerPos);

				if (CGame::GetPlayer(nCntPlayer)->GetActiveGravity())
				{// �d�̓t���O�������Ă���Ƃ�
				    // �d�͂�؂�
					CGame::GetPlayer(nCntPlayer)->SetActiveGravity(false);
				}
			}
			else
			{// �����痣�ꂷ���Ă���
				if (!CGame::GetPlayer(nCntPlayer)->GetActiveGravity())
				{// �d�̓t���O�������ĂȂ��Ƃ�
				 // �d�̓t���O�����Ă�
					CGame::GetPlayer(nCntPlayer)->SetActiveGravity(true);
				}
			}
		}
		else
		{// �����̉��ɏ����Ȃ�
			if (!CGame::GetPlayer(nCntPlayer)->GetActiveGravity())
			{// �d�̓t���O�������ĂȂ��Ƃ�
			    // �d�̓t���O�����Ă�
				CGame::GetPlayer(nCntPlayer)->SetActiveGravity(true);
			}
		}
	}
}
