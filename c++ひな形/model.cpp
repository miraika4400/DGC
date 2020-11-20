//=============================================================================
//
// ���f������ [model.cpp]
// Author : �R�c�ˑ�
//
//=============================================================================
#include "model.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//���f���N���X�̃R���X�g���N�^
//=============================================================================
CModel::CModel(int nPliority) :CScene(nPliority)
{
	// �ϐ��̃N���A
	m_pBuffMatModel = NULL;
	m_pMeshModel = NULL;
	m_nNumMatModel = 0;
	m_pos = VEC3_ZERO;
	m_rot = VEC3_ZERO;
	memset(&m_apTexture, 0, sizeof(m_apTexture));
}

//=============================================================================
//���f���N���X�̃f�X�g���N�^
//=============================================================================
CModel::~CModel()
{
}

//=============================================================================
//���f���N���X�̃N���G�C�g����
//=============================================================================
CModel * CModel::Create(D3DXVECTOR3 pos)
{
	//���f���N���X�̃|�C���^�ϐ�
	CModel *pModel = NULL;

	//�������m��
	pModel = new CModel;

	//���������m�ۂł��Ă�����
	if (pModel != NULL)
	{
		//�����������Ăяo��
		pModel->Init();
		pModel->m_pos = pos;
	}
	//�������m�ۂɎ��s�����Ƃ�
	else
	{
		return NULL;
	}

	return pModel;
}

//=============================================================================
//���f���N���X�̏���������
//=============================================================================
HRESULT CModel::Init()
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�ʒu�̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�����̏�����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//=============================================================================
//���f���N���X�̏I������
//=============================================================================
void CModel::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
//���f���N���X�̍X�V����
//=============================================================================
void CModel::Update(void)
{
}

//=============================================================================
//���f���N���X�̕`�揈��
//=============================================================================
void CModel::Draw(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;	//���݂̃}�e���A���ێ��p
	D3DXMATERIAL*pMat;	//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorldModel);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorldModel, &m_mtxWorldModel, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorldModel, &m_mtxWorldModel, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldModel);

	//���݂̃}�e���A�����擾����
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
	{
		//�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
		pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		// �e�N�X�`��
		pDevice->SetTexture(0, m_apTexture[nCntMat]);
		//���f���p�[�c�̕`��
		m_pMeshModel->DrawSubset(nCntMat);
	}

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
//���f���N���X�̃��b�V�����̎擾
//=============================================================================
LPD3DXMESH CModel::GetMesh(void) const
{
	return m_pMeshModel;
}

//=============================================================================
//���f���N���X�̈ʒu���̐ݒ�
//=============================================================================
void CModel::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
//���f���N���X�̈ʒu���̎擾
//=============================================================================
D3DXVECTOR3 CModel::GetPos(void) const
{
	return m_pos;
}

//=============================================================================
//���f���N���X�̌����̐ݒ�
//=============================================================================
void CModel::SetRot(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
//���f���N���X�̌����̎擾
//=============================================================================
D3DXVECTOR3 CModel::GetRot(void) const
{
	return m_rot;
}


//=============================================================================
// ���f���̊��蓖��
//=============================================================================
void CModel::BindModel(LPD3DXMESH pMeshModel, LPD3DXBUFFER pBuffMatModel, DWORD nNumMatModel)
{
	m_pMeshModel = pMeshModel;
	m_pBuffMatModel = pBuffMatModel;
	m_nNumMatModel = nNumMatModel;
}

//=============================================================================
// ���f���̃e�N�X�`�����蓖��
//=============================================================================
void CModel::BindTexture(const int nIndex, const LPDIRECT3DTEXTURE9 pTexture)
{
	m_apTexture[nIndex] = pTexture;
}
