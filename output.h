//----------------------------------------------------------------------------------
//	�o�̓v���O�C�� �w�b�_�[�t�@�C�� for AviUtl version 0.99g4 �ȍ~
//	By �j�d�m����
//----------------------------------------------------------------------------------

//	�o�͏��\����
typedef struct {
	int		flag;			//	�t���O
							//	OUTPUT_INFO_FLAG_VIDEO	: �摜�f�[�^����
							//	OUTPUT_INFO_FLAG_AUDIO	: �����f�[�^����
							//	OUTPUT_INFO_FLAG_BATCH	: �o�b�`�o�͒�
	int		w,h;			//	�c���T�C�Y
	int		rate,scale;		//	�t���[�����[�g
	int		n;				//	�t���[����
	int		size;			//	�P�t���[���̃o�C�g��
	int		audio_rate;		//	�����T���v�����O���[�g
	int		audio_ch;		//	�����`�����l����
	int		audio_n;		//	�����T���v�����O��
	int		audio_size;		//	�����P�T���v���̃o�C�g��
	LPSTR	savefile;		//	�Z�[�u�t�@�C�����ւ̃|�C���^
	void	*(*func_get_video)( int frame );
							//	DIB�`��(RGB24bit)�̉摜�f�[�^�ւ̃|�C���^���擾���܂��B
							//	frame	: �t���[���ԍ�
							//	�߂�l	: �f�[�^�ւ̃|�C���^
							//			  �摜�f�[�^�|�C���^�̓��e�͎��ɊO���֐����g�������C���ɏ�����߂��܂ŗL��
	void	*(*func_get_audio)( int start,int length,int *readed );
							//	16bitPCM�`���̉����f�[�^�ւ̃|�C���^���擾���܂��B
							//	start	: �J�n�T���v���ԍ�
							//	length	: �ǂݍ��ރT���v����
							//	readed	: �ǂݍ��܂ꂽ�T���v����
							//	�߂�l	: �f�[�^�ւ̃|�C���^
							//			  �����f�[�^�|�C���^�̓��e�͎��ɊO���֐����g�������C���ɏ�����߂��܂ŗL��
	BOOL	(*func_is_abort)( void );
							//	���f���邩���ׂ܂��B
							//	�߂�l	: TRUE�Ȃ璆�f
	BOOL	(*func_rest_time_disp)( int now,int total );
							//	�c�莞�Ԃ�\�������܂��B
							//	now		: �������Ă���t���[���ԍ�
							//	total	: �������鑍�t���[����
							//	�߂�l	: TRUE�Ȃ琬��
	int		(*func_get_flag)( int frame );
							//	�t���O���擾���܂��B
							//	frame	: �t���[���ԍ�
							//	�߂�l	: �t���O
							//  OUTPUT_INFO_FRAME_FLAG_KEYFRAME		: �L�[�t���[������
							//  OUTPUT_INFO_FRAME_FLAG_COPYFRAME	: �R�s�[�t���[������
	BOOL	(*func_update_preview)( void );
							//	�v���r���[��ʂ��X�V���܂��B
							//	�Ō��func_get_video�œǂݍ��܂ꂽ�t���[�����\������܂��B
							//	�߂�l	: TRUE�Ȃ琬��
	void	*(*func_get_video_ex)( int frame,DWORD format );
							//	DIB�`���̉摜�f�[�^���擾���܂��B
							//	frame	: �t���[���ԍ�
							//	format	: �摜�t�H�[�}�b�g( NULL = RGB24bit / 'Y''U''Y''2' = YUY2 / 'Y''C''4''8' = PIXEL_YC )
							//			  ��PIXEL_YC�`�� �� YUY2�t�B���^���[�h�ł͎g�p�o���܂���B
							//	�߂�l	: �f�[�^�ւ̃|�C���^
							//			  �摜�f�[�^�|�C���^�̓��e�͎��ɊO���֐����g�������C���ɏ�����߂��܂ŗL��
} OUTPUT_INFO;
#define	OUTPUT_INFO_FLAG_VIDEO	1
#define	OUTPUT_INFO_FLAG_AUDIO	2
#define	OUTPUT_INFO_FLAG_BATCH	4
#define	OUTPUT_INFO_FRAME_FLAG_KEYFRAME		1
#define	OUTPUT_INFO_FRAME_FLAG_COPYFRAME	2

//	�o�̓v���O�C���\����
typedef	struct {
	int		flag;			//	�t���O
	LPSTR	name;			//	�v���O�C���̖��O
	LPSTR	filefilter;		//	�t�@�C���̃t�B���^
	LPSTR	information;	//	�v���O�C���̏��
	BOOL	(*func_init)( void );
							//	DLL�J�n���ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	BOOL	(*func_exit)( void );
							//	DLL�I�����ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	BOOL	(*func_output)( OUTPUT_INFO *oip );
							//	�o�͎��ɌĂ΂��֐��ւ̃|�C���^
	BOOL	(*func_config)( HWND hwnd,HINSTANCE dll_hinst );
							//	�o�͐ݒ�̃_�C�A���O��v�����ꂽ���ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	int		(*func_config_get)( void *data,int size );
							//	�o�͐ݒ�f�[�^���擾���鎞�ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
							//	data	: �ݒ�f�[�^���������ރo�b�t�@�ւ̃|�C���^ (NULL�Ȃ�ݒ�f�[�^�T�C�Y��Ԃ�����)
							//	size	: �ݒ�f�[�^���������ރo�b�t�@�̃T�C�Y
							//	�߂�l	: �ݒ�f�[�^�̃T�C�Y
	int		(*func_config_set)( void *data,int size );
							//	�o�͐ݒ�f�[�^��ݒ肷�鎞�ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
							//	data	: �ݒ�f�[�^�ւ̃|�C���^
							//	size	: �ݒ�f�[�^�̃T�C�Y
							//	�߂�l	: �g�p�����ݒ�f�[�^�̃T�C�Y
	int		reserve[16];	//	�g���p�ɗ\�񂳂�Ă܂�
} OUTPUT_PLUGIN_TABLE;

BOOL func_init( void );
BOOL func_exit( void );
BOOL func_output( OUTPUT_INFO *oip );
BOOL func_config( HWND hwnd,HINSTANCE hinst );
int func_config_get( void *data,int size );
int func_config_set( void *data,int size );


