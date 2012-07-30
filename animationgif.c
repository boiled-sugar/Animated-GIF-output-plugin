//----------------------------------------------------------------------------------
//		�A�j���[�V����GIF�o�̓v���O�C��
//----------------------------------------------------------------------------------
#include <windows.h>
#include <math.h>
#include <wand/MagickWand.h>    //ImageMagick-6.7.8-7���g�p
                                //./configure --disable-shared --without-magick-plus-plus --with-quantum-depth=8 --disable-installed --without-bzlib
#include "output.h"


//---------------------------------------------------------------------
//		�o�̓v���O�C���\���̒�`
//---------------------------------------------------------------------
OUTPUT_PLUGIN_TABLE output_plugin_table = {
	0,  												//	�t���O NULL���ƌx��
	"�A�j���[�V����GIF�o��",							//	�v���O�C���̖��O
	"GIF File (*.gif)\0*.gif\0AllFile (*.*)\0*.*\0",	//	�o�̓t�@�C���̃t�B���^
	"�A�j���[�V����GIF�o�̓v���O�C�� ver.0.0.3",		//	�v���O�C���̏��
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
    const double mabiki = 1;    //2�ɂ����2�t���[����1�t���[���̊Ԉ���
                                //int���Ǝl�̌ܓ��̌v�Z���ł��Ȃ�
    if( oip->n > 500 / mabiki )
        if( MessageBox( NULL, (LPCSTR) "��ʂ̃t���[�����I������Ă��܂��B\n�{���ɑ��s���܂����H", (LPCSTR) "�A�j���[�V����GIF�o�̓v���O�C��", MB_YESNO | MB_ICONQUESTION )
            == IDNO )
            return TRUE;
    
    const int delay = round( mabiki * 100 * oip->scale / oip->rate );    //�Ԉ����~100���t���[�����[�g���l�̌ܓ�
    MagickWandGenesis();
    MagickWand *dest = NewMagickWand();
    
    for( int i = 0; i < oip->n; i = i + mabiki )
    {
        if( oip->func_is_abort() )
        {
            if( MessageBox( NULL, (LPCSTR) "�����܂ł̏o�̓f�[�^���A�j���[�V����GIF�ɏ������݂܂����H", (LPCSTR) "�A�j���[�V����GIF�o�̓v���O�C��", MB_YESNO | MB_ICONQUESTION )
                == IDYES )
                break;
            else
            {
                DestroyMagickWand( dest );
                MagickWandTerminus();
                return TRUE;
            }
        }
        oip->func_rest_time_disp( i, oip->n );
        
        int copy = 0;    //�R�s�[�t���[����
        for( int j = 1; i + j < oip->n; j++ )
        {
            if( oip->func_get_flag( i + j ) & OUTPUT_INFO_FRAME_FLAG_COPYFRAME )
                copy++;
            else
                break;
        }
        
        MagickWand *source = NewMagickWand();
        if( !MagickConstituteImage( source, oip->w, oip->h, "BGR", CharPixel, oip->func_get_video_ex( i, 0 ) ) )    //NULL���ƌx��
            MessageBox( NULL, (LPCSTR) "�f�[�^�擾���s", (LPCSTR) "�A�j���[�V����GIF�o�̓v���O�C��", MB_OK|MB_ICONSTOP );
        MagickFlipImage( source );    //AviUtl����̓{�g���A�b�v�œn����邪�AMagickConstituteImage�̓g�b�v�_�E���Œ�
        MagickSetImageDelay( source, delay * ( copy + 1 ) );    //�R�s�[�t���[����0�Ȃ�1�{
        //MagickSetImageDispose( source, 0 );
        MagickAddImage( dest, source );
        DestroyMagickWand( source );
        i = i + copy;    //�R�s�[�t���[�����������摗��
        oip->func_update_preview();
    }
    MagickSetFirstIterator( dest );
    MagickQuantizeImages( dest, 256, RGBColorspace, 0, FloydSteinbergDitherMethod, MagickFalse );
    //MagickSetFirstIterator( dest );
    //MagickSetImageIterations( dest, 0 );
    if( !MagickSetFormat( dest, "GIF" ) )
        MessageBox( NULL, (LPCSTR) "GIF�Z�b�g���s", (LPCSTR) "�A�j���[�V����GIF�o�̓v���O�C��", MB_OK|MB_ICONSTOP );
    dest = MagickOptimizeImageLayers( MagickCoalesceImages( dest ) );    //������dispose��1�ɂȂ�
    MagickOptimizeImageTransparency( dest );    //6.7.8-7�ȍ~���K�v
    if( !MagickWriteImages( dest, oip->savefile, MagickTrue ) )
        MessageBox( NULL, (LPCSTR) "�o�͎��s", (LPCSTR) "�A�j���[�V����GIF�o�̓v���O�C��", MB_OK|MB_ICONSTOP );
    
    DestroyMagickWand( dest );
    MagickWandTerminus();
    return TRUE;
}
