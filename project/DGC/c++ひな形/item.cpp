////////////////////////////////////////////////////
//
//    Item�N���X�̏���[Item.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "Item.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "player.h"
#include "checkpoint.h"
#include "wall.h"
#include "start.h"
#include "collision.h"

//*****************************
// �}�N����`
//*****************************
#define MODEL_PATH_COLORLESS "./data/Models/Item_model/cube02.x"	// ���F���f���̃p�X
#define MODEL_PATH_1         "./data/Models/Item_model/cube02.x"	// �ԃ��f���̃p�X
#define MODEL_PATH_2         "./data/Models/Item_model/cube02.x"	// ���f���̃p�X
#define MODEL_PATH_3         "./data/Models/Item_model/cube02.x"	// ���F���f���̃p�X
#define MODEL_PATH_4         "./data/Models/Item_model/cube02.x"	// �΃��f���̃p�X

#define ITEM_RADIUS 70   // ���a

#ifdef _DEBUG

#define RED     D3DXCOLOR(1.0f,0.0f,0.0f,1.0f) // ��
#define BLUE    D3DXCOLOR(0.0f,0.0f,1.0f,1.0f) // ��
#define YELLOW  D3DXCOLOR(1.0f,1.0f,0.0f,1.0f) // ��
#define GREEN   D3DXCOLOR(0.0f,1.0f,0.0f,1.0f) // ��

#endif

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
CModel::Model   CItem::m_model[CItem::ITEM_MAX] = {};   	//���b�V�����ւ̃|�C���^
D3DXVECTOR3 CItem::m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // �S�A�C�e�����ʂŃ��b�g�Œ�

char *CItem::m_pTexPath[CItem::ITEM_MAX] =
{
	MODEL_PATH_COLORLESS,
	MODEL_PATH_1,
	MODEL_PATH_2,
	MODEL_PATH_3,
	MODEL_PATH_4
};

//******************************
// �R���X�g���N�^
//******************************
CItem::CItem() :CModel(OBJTYPE_MAP)
{
	// �ϐ��̃N���A
	m_pCollision = NULL;         // �����蔻��
	m_itemType = ITEM_COLORLESS; // �A�C�e���^�C�v
}

//******************************
// �f�X�g���N�^
//******************************
CItem::~CItem()
{
}

//******************************
// �N���G�C�g
//******************************
CItem * CItem::Create(D3DXVECTOR3 pos, ITEM_TYPE type)
{
	// �������̊m��
	CItem *pItem;
	pItem = new CItem;
	
	// �^�C�v�̐ݒ�
	pItem->m_itemType = type;
	// ������
	pItem->Init();

	// �e�l�̑���E�Z�b�g
	pItem->SetObjType(OBJTYPE_MAP); // �I�u�W�F�N�g�^�C�v
	pItem->SetPos(pos);             // ���W�̃Z�b�g

	// �����蔻��̐���
	pItem->m_pCollision=CCollision::CreateSphere(pos, ITEM_RADIUS);

	return pItem;
}

//******************************
// �e�N�X�`���̃��[�h
//******************************
HRESULT CItem::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �R�[�X�������[�v
	for (int nCntItem = 0; nCntItem < ITEM_MAX; nCntItem++)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(m_pTexPath[nCntItem],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_model[nCntItem].pBuffMat,
			NULL,
			&m_model[nCntItem].nNumMat,
			&m_model[nCntItem].pMesh);
	}

	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CItem::Unload(void)
{
	for (int nCnt = 0; nCnt < ITEM_MAX; nCnt++)
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
HRESULT CItem::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}

	// ���f�����蓖��
	BindModel(m_model[m_itemType].pMesh, m_model[m_itemType].pBuffMat, m_model[m_itemType].nNumMat);
	
	return S_OK;
}

//******************************
// �I������
//******************************
void CItem::Uninit(void)
{
	if (m_pCollision != NULL)
	{
		m_pCollision->Uninit();
		m_pCollision = NULL;
	}
	CModel::Uninit();
}

//******************************
// �X�V����
//******************************
void CItem::Update(void)
{
	// �v���C���[�Ƃ̓����蔻��
	CollisionPlayer();
}

//******************************
// �`�揈��
//******************************
void CItem::Draw(void)
{
	
#ifdef _DEBUG
	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)GetModelData()->pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_model[m_itemType].nNumMat; nCntMat++)
	{
			switch (m_itemType)
			{
			case ITEM_RED:
				pMat[nCntMat].MatD3D.Diffuse = RED;
				break;
			case ITEM_BLUE:
				pMat[nCntMat].MatD3D.Diffuse = BLUE;
				break;
			case ITEM_YELLOW:
				pMat[nCntMat].MatD3D.Diffuse = YELLOW;
				break;
			case ITEM_GREEN:
				pMat[nCntMat].MatD3D.Diffuse = GREEN;
				break;
			default:
				break;
			}
	}
#endif // _DEBUG
	SetRot(m_rot);
	CModel::Draw();
}

//******************************
// ��]����
//******************************
void CItem::ItemRotasion(void)
{
	m_rot.y += D3DXToRadian(3);
}

//******************************
// �v���C���[�Ƃ̓����蔻��
//******************************
void CItem::CollisionPlayer(void)
{
	// �v���C���[���̎擾
	CPlayer*pPlayer = (CPlayer*)GetTop(OBJTYPE_PLAYER);

	while (pPlayer != NULL)
	{
		// �����蔻��
		if (CCollision::CollisionSphere(m_pCollision, pPlayer->GetCollision()))
		{// �������Ă���
			if (pPlayer->GetPlayerNum() == m_itemType || m_itemType == ITEM_COLORLESS)
			{// �����̐F�������͖��F
				pPlayer->HitItem(true);
				Uninit();
			}
			else
			{// ���̑�
				pPlayer->HitItem(false);
				Uninit();
			}
			break;
		}
		
		// �l�N�X�g�̃|�C���^�ɍX�V
		pPlayer = (CPlayer*)pPlayer->GetNext();
	}
}
