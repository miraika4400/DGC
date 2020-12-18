//=============================================================================
//
// camera�w�b�_ [camera.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "scene2d.h"

//*****************************
// �N���X��`
//*****************************

//�J�����N���X
class CCamera
{
public:
	//�����o�֐�
	CCamera();
	~CCamera();

	static CCamera *Create(int nNmPlayer);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	D3DXVECTOR3 GetPos(void) { return m_posV; }

	D3DXMATRIX GetViewMtx(void) { return m_mtxView; }
	D3DXMATRIX GetProjectionMtx(void) { return m_mtxProjection; }
	float GetAngle(void) { return m_fAngle; }
	D3DXVECTOR3 GetposV(void) { return m_posV; }
	D3DXVECTOR3 GetposR(void) { return m_posR; }
private:
	// �����o�ϐ�
	D3DXVECTOR3 m_posV;//�J�����̍��W
	D3DXVECTOR3 m_posR;//�����_
	D3DXVECTOR3 m_vecU;//������x�N�g��
	D3DXMATRIX  m_mtxProjection;//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX  m_mtxView;//�r���[�}�g���b�N�X
	int m_nNmPlayer;      // �ǂ̃v���C���[�̃J������
	float m_fAngle;
	// ���ʍ��W
	float m_fRad;   // �ڕW����̋���
	float m_fTheta;  // �p�x�V�[�^
	float m_fPhi;    // �p�x�t�@�C
};

#endif