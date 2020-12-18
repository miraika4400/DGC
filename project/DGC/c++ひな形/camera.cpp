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

//******************************
// �}�N����`
//******************************
#define CAMERA_DISTANCE 1000       // �J�����ƖڕW�̋���
#define MOSE_SENSI_RATE 100.0f     // �J�����̃}�E�X���x
#define JOYPAD_SENSI_RATE 10000.0f // �R���g���[���[�̃X�e�B�b�N�̊��x
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
	m_fPhi = 0.0f;
	m_fAngle = 0.0f;
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
	pCamera->m_nNmPlayer = nNmPlayer;

	pCamera->Init();
	
	return pCamera;
}

//******************************
// ����������
//******************************
HRESULT CCamera::Init(void)
{


	m_posV = D3DXVECTOR3(0.0f, 100.0f, -500.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_fRad = CAMERA_DISTANCE;
	m_fTheta = D3DXToRadian(-90);
	m_fPhi = D3DXToRadian(-70);

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
	m_fTheta -= CManager::GetMouse()->GetMouseMove().x / MOSE_SENSI_RATE;
	m_fTheta -= CManager::GetJoypad()->GetStick(m_nNmPlayer).lX / JOYPAD_SENSI_RATE;

	// �����_���v���C���[�ɂ���
	m_posR = CGame::GetPlayer(m_nNmPlayer)->GetPos();

	if (CManager::GetJoypad()->GetJoystickPress(0, m_nNmPlayer))
	{// �o�b�N�~���[�̏���

		// ���ʍ��W�̐ݒ�
		m_posV.x = m_posR.x + (m_fRad)* sinf(-m_fPhi)*cosf(m_fTheta);
		m_posV.y = m_posR.y + (m_fRad)* cosf(-m_fPhi);
		m_posV.z = m_posR.z + (m_fRad)* sinf(-m_fPhi)*sinf(m_fTheta);

		// �J�����̌����̐ݒ�
		m_fAngle = atan2f(m_posV.z - m_posR.z, m_posV.x - m_posR.x);
	}
	else
	{
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

	int nPlayerNum = CGame::GetPlayerNum();
	float fWidth = CManager::GetRenderer()->GetViewPort(0).Width;
	float fHeight = CManager::GetRenderer()->GetViewPort(0).Height;


		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
			D3DXToRadian(60.0f),
			fWidth / fHeight, 10.0f, 1000000.0f);


	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}
