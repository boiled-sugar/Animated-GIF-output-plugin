//----------------------------------------------------------------------------------
//		�A�j���[�V����GIF�o�̓v���O�C��
//----------------------------------------------------------------------------------
#include <windows.h>
#include <wand/MagickWand.h>

#include "output.h"


//---------------------------------------------------------------------
//		�o�̓v���O�C���\���̒�`
//---------------------------------------------------------------------
OUTPUT_PLUGIN_TABLE output_plugin_table = {
	0,  												//	�t���O NULL���ƌx��
	"�A�j���[�V����GIF�o��",							//	�v���O�C���̖��O
	"GIF File (*.gif)\0*.gif\0AllFile (*.*)\0*.*\0",	//	�o�̓t�@�C���̃t�B���^
	"�A�j���[�V����GIF�o�̓v���O�C�� ver.0.0.1",		//	�v���O�C���̏��
	NULL,												//	DLL�J�n���ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	NULL,												//	DLL�I�����ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	func_output,										//	�o�͎��ɌĂ΂��֐��ւ̃|�C���^
	NULL,					        					//	�o�͐ݒ�̃_�C�A���O��v�����ꂽ���ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	NULL,				            					//	�o�͐ݒ�f�[�^���擾���鎞�ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	NULL            ,									//	�o�͐ݒ�f�[�^��ݒ肷�鎞�ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
};


//---------------------------------------------------------------------
//		�o�̓v���O�C���\���̂̃|�C���^��n���֐�
//---------------------------------------------------------------------
EXTERN_C OUTPUT_PLUGIN_TABLE __declspec(dllexport) * __stdcall GetOutputPluginTable( void )
{
	return &output_plugin_table;
}


//---------------------------------------------------------------------
//		�o�̓v���O�C�������{��
//---------------------------------------------------------------------
BOOL func_output( OUTPUT_INFO *oip )
{
    const int mabiki = 1;    //2�ɂ����2�t���[����1�t���[���̊Ԉ���
    
    if( oip->n > 400 / mabiki )
        if( MessageBox( NULL, (LPCSTR) "��ʂ̃t���[�����I������Ă��܂��B\n�{���ɑ��s���܂����H", (LPCSTR) "�A�j���[�V����GIF�o�̓v���O�C��", MB_YESNO | MB_ICONQUESTION )
            == IDNO )
            return FALSE;
    
    const int delay = mabiki * 100 * oip->scale / oip->rate;    //�Ԉ����~100���t���[�����[�g
    MagickWandGenesis();
    MagickWand *dest = NewMagickWand();
    
    for( int i = 0; i < oip->n; i = i + mabiki )
    {
        if( oip->func_is_abort() )
            break;
        oip->func_rest_time_disp( i, oip->n );
        MagickWand *source = NewMagickWand();
        if( !MagickConstituteImage( source, oip->w, oip->h, "BGR", CharPixel, oip->func_get_video_ex( i, 0 ) ) )    //NULL���ƌx��
            MessageBox( NULL, (LPCSTR) "�f�[�^�擾���s", (LPCSTR) "�A�j���[�V����GIF�o�̓v���O�C��", MB_OK|MB_ICONSTOP );
        MagickFlipImage( source );    //AviUtl����̓{�g���A�b�v�œn����邪�AMagickConstituteImage�̓g�b�v�_�E���Œ�
        MagickSetImageDelay( source, delay );
        MagickAddImage( dest, source );
        DestroyMagickWand( source );
        oip->func_update_preview();
    }
    if( !MagickSetFormat( dest, "GIF" ) || !MagickSetImageType( dest, PaletteType ) )
        MessageBox( NULL, (LPCSTR) "GIF�Z�b�g���s", (LPCSTR) "�A�j���[�V����GIF�o�̓v���O�C��", MB_OK|MB_ICONSTOP );
    if( !MagickWriteImages( MagickCoalesceImages( dest ), oip->savefile, MagickTrue ) )
        MessageBox( NULL, (LPCSTR) "�o�͎��s", (LPCSTR) "�A�j���[�V����GIF�o�̓v���O�C��", MB_OK|MB_ICONSTOP );
    
    DestroyMagickWand( dest );
    MagickWandTerminus();
    return TRUE;
}
