////////////////////////////////////////////////////
//
//    �J�����N���X�̏���[camera.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "mouse.h"
#include "joypad.h"
#include "destination.h"
#include "scene.h"

//******************************
// �}�N����`
//******************************
#define CAMERA_DISTANCE 1500       // �J�����ƖڕW�̋���
#define HEIGHT_RATE 0.1f           // ���������킹��Ƃ��̌W��
#define THETA_DIFFERENCE D3DXToRadian(60) // �V�[�^�ƃV�[�^�̖ڕW�l�̍��̍ő�

//******************************
// �ÓI�����o�ϐ��錾
//******************************

//******************************
// �R���X�g���N�^
//******************************
CCamera::CCamera()
{
	// �ϐ��̃N���A
	m_posV = VEC3_ZERO;
	m_posR = VEC3_ZERO;
	m_vecU = VEC3_ZERO;
	D3DXMatrixIdentity(&m_mtxProjection);
	D3DXMatrixIdentity(&m_mtxView);
	m_fRad = 0.0f;
	m_fTheta = 0.0f;
	m_fThetaDest = 0.0f;
	m_fPhi = 0.0f;
	m_fPhiDest = 0.0f;
	m_fAngle = 0.0f;
	m_bBackMirror = false;
}

//******************************
// �f�X�g���N�^
//******************************
CCamera::~CCamera()
{
}

//******************************
// �N���G�C�g
//******************************
CCamera * CCamera::Create(int nNmPlayer)
{

	CCamera *pCamera = new CCamera;
	
	// �v���C���[�ԍ��̎擾
	pCamera->m_nPlayerNum = nNmPlayer;

	pCamera->Init();
	
	return pCamera;
}

//******************************
// ����������
//******************************
HRESULT CCamera::Init(void)
{
	// �ϐ��̏�����
	m_posV = D3DXVECTOR3(0.0f, 100.0f, -500.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_fRad = CAMERA_DISTANCE;
	m_fTheta     = D3DXToRadian(-90);
	m_fThetaDest = D3DXToRadian(-90);
	m_fPhi     = D3DXToRadian(-70);
	m_fPhiDest = D3DXToRadian(-70);

	m_bBackMirror = false;

	// ���ʍ��W�̐ݒ�
	m_posV.x = m_posR.x + (m_fRad)* sinf(m_fPhi)*cosf(m_fTheta);
	m_posV.y = m_posR.y + (m_fRad)* cosf(m_fPhi);
	m_posV.z = m_posR.z + (m_fRad)* sinf(m_fPhi)*sinf(m_fTheta);

	// �J�����̌���
	m_fAngle = atan2f(m_posR.y - m_posV.y, m_posR.y - m_posV.y);
	
	return S_OK;
}

//******************************
// �I������
//******************************
void CCamera::Uninit(void)
{
}

//******************************
// �X�V����
//******************************
void CCamera::Update(void)
{
	// �}�E�X�ŃJ��������
	//m_fPhi += CManager::GetMouse()->GetMouseMove().y / 100.0f;
	/*m_fTheta -= CManager::GetMouse()->GetMouseMove().x / MOUSE_SENSI_RATE;
	m_fTheta -= CManager::GetJoypad()->GetStick(m_nNmPlayer).lX / JOYPAD_SENSI_RATE;*/

	// ���X�g�̐擪�̎擾
	CDestination*pDest = (CDestination*)CScene::GetTop(CScene::OBJTYPE_DESTINATION);

	while (pDest != NULL)
	{
		if (pDest->GetPlayerNum()==m_nPlayerNum)
		{
			// �����_�̐ݒ�
			m_posR = pDest->GetPos();
			// �V�[�^�̖ڕW�l�̐ݒ�
			m_fThetaDest = (-pDest->GetRot().y) + D3DXToRadian(-90);

			// �V�[�^�̖ڕW�l�̍��̏���A����
			if (m_fThetaDest - m_fTheta >= THETA_DIFFERENCE)
			{
				m_fTheta = m_fThetaDest + -THETA_DIFFERENCE;
			}
			if (m_fThetaDest - m_fTheta <= -THETA_DIFFERENCE)
			{
				 m_fTheta = m_fThetaDest + THETA_DIFFERENCE;
			}

			break;
		}

		// ���X�g�̎��̃|�C���^�ɂ���
		pDest = (CDestination*)pDest->GetNext();
	}

	//// �����_���v���C���[�ɂ���
	//m_posR = CGame::GetPlayer(m_nPlayerNum)->GetPos();
	
	// ���̉�]
	m_fTheta += ((m_fThetaDest - m_fTheta))*HEIGHT_RATE;


	if (CManager::GetJoypad()->GetJoystickTrigger(0, m_nPlayerNum)|| CManager::GetJoypad()->GetJoystickPress(0, m_nPlayerNum))
	{
		m_fPhi = m_fPhiDest;
	}

	if (CManager::GetJoypad()->GetJoystickPress(0, m_nPlayerNum))
	{// �o�b�N�~���[�̏���

		// �J�����Ƃ̋����̒���
		m_fRad = CAMERA_DISTANCE*0.7f;
		// ����
		m_fPhi += ((m_fPhiDest - m_fPhi))*HEIGHT_RATE;
		// �o�b�N�~���[bool
		m_bBackMirror = true;
		// ���ʍ��W�̐ݒ�
		m_posV.x = m_posR.x + (m_fRad)* sinf(-m_fPhi)*cosf(m_fTheta);
		m_posV.y = m_posR.y + (m_fRad)* cosf(-m_fPhi);
		m_posV.z = m_posR.z + (m_fRad)* sinf(-m_fPhi)*sinf(m_fTheta);

		// �J�����̌����̐ݒ�
		m_fAngle = atan2f(m_posV.z - m_posR.z, m_posV.x - m_posR.x);
	}
	else
	{
		// �J�����Ƃ̋����̒���
		m_fRad = CAMERA_DISTANCE;
		// ����
		m_fPhi += ((m_fPhiDest - m_fPhi))*HEIGHT_RATE;
		// �o�b�N�~���[bool
		m_bBackMirror = false;
		// ���ʍ��W�̐ݒ�
		m_posV.x = m_posR.x + (m_fRad)* sinf(m_fPhi)*cosf(m_fTheta);
		m_posV.y = m_posR.y + (m_fRad)* cosf(m_fPhi);
		m_posV.z = m_posR.z + (m_fRad)* sinf(m_fPhi)*sinf(m_fTheta);

		// �J�����̌����̐ݒ�
		m_fAngle = atan2f(m_posR.z - m_posV.z, m_posR.x - m_posV.x);
	}
}

//******************************
// �J�����̃Z�b�g
//******************************
void CCamera::SetCamera(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIXA16 matWorld;

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);
	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);
	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�v���W�F�N�g�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(50.0f), 
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 1000000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 255, 0, 255), 1.0f, 0);

}
