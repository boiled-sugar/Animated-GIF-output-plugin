//----------------------------------------------------------------------------------
//		アニメーションGIF出力プラグイン
//----------------------------------------------------------------------------------
#include <windows.h>
#include <math.h>
#include <wand/MagickWand.h>    //ImageMagick-6.7.8-7を使用
                                //./configure --disable-shared --without-magick-plus-plus --with-quantum-depth=8 --disable-installed --without-bzlib
#include "output.h"


//---------------------------------------------------------------------
//		出力プラグイン構造体定義
//---------------------------------------------------------------------
OUTPUT_PLUGIN_TABLE output_plugin_table = {
	0,  												//	フラグ NULLだと警告
	"アニメーションGIF出力",							//	プラグインの名前
	"GIF File (*.gif)\0*.gif\0AllFile (*.*)\0*.*\0",	//	出力ファイルのフィルタ
	"アニメーションGIF出力プラグイン ver.0.0.3",		//	プラグインの情報
	NULL,												//	DLL開始時に呼ばれる関数へのポインタ (NULLなら呼ばれません)
	NULL,												//	DLL終了時に呼ばれる関数へのポインタ (NULLなら呼ばれません)
	func_output,										//	出力時に呼ばれる関数へのポインタ
	NULL,					        					//	出力設定のダイアログを要求された時に呼ばれる関数へのポインタ (NULLなら呼ばれません)
	NULL,				            					//	出力設定データを取得する時に呼ばれる関数へのポインタ (NULLなら呼ばれません)
	NULL            ,									//	出力設定データを設定する時に呼ばれる関数へのポインタ (NULLなら呼ばれません)
};


//---------------------------------------------------------------------
//		出力プラグイン構造体のポインタを渡す関数
//---------------------------------------------------------------------
EXTERN_C OUTPUT_PLUGIN_TABLE __declspec(dllexport) * __stdcall GetOutputPluginTable( void )
{
	return &output_plugin_table;
}


//---------------------------------------------------------------------
//		出力プラグイン処理本体
//---------------------------------------------------------------------
BOOL func_output( OUTPUT_INFO *oip )
{
    const double mabiki = 1;    //2にすると2フレーム中1フレームの間引き
                                //intだと四捨五入の計算ができない
    if( oip->n > 500 / mabiki )
        if( MessageBox( NULL, (LPCSTR) "大量のフレームが選択されています。\n本当に続行しますか？", (LPCSTR) "アニメーションGIF出力プラグイン", MB_YESNO | MB_ICONQUESTION )
            == IDNO )
            return TRUE;
    
    const int delay = round( mabiki * 100 * oip->scale / oip->rate );    //間引き×100÷フレームレートを四捨五入
    MagickWandGenesis();
    MagickWand *dest = NewMagickWand();
    
    for( int i = 0; i < oip->n; i = i + mabiki )
    {
        if( oip->func_is_abort() )
        {
            if( MessageBox( NULL, (LPCSTR) "ここまでの出力データをアニメーションGIFに書き込みますか？", (LPCSTR) "アニメーションGIF出力プラグイン", MB_YESNO | MB_ICONQUESTION )
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
        
        int copy = 0;    //コピーフレーム数
        for( int j = 1; i + j < oip->n; j++ )
        {
            if( oip->func_get_flag( i + j ) & OUTPUT_INFO_FRAME_FLAG_COPYFRAME )
                copy++;
            else
                break;
        }
        
        MagickWand *source = NewMagickWand();
        if( !MagickConstituteImage( source, oip->w, oip->h, "BGR", CharPixel, oip->func_get_video_ex( i, 0 ) ) )    //NULLだと警告
            MessageBox( NULL, (LPCSTR) "データ取得失敗", (LPCSTR) "アニメーションGIF出力プラグイン", MB_OK|MB_ICONSTOP );
        MagickFlipImage( source );    //AviUtlからはボトムアップで渡されるが、MagickConstituteImageはトップダウン固定
        MagickSetImageDelay( source, delay * ( copy + 1 ) );    //コピーフレーム数0なら1倍
        //MagickSetImageDispose( source, 0 );
        MagickAddImage( dest, source );
        DestroyMagickWand( source );
        i = i + copy;    //コピーフレーム数分だけ先送り
        oip->func_update_preview();
    }
    MagickSetFirstIterator( dest );
    MagickQuantizeImages( dest, 256, RGBColorspace, 0, FloydSteinbergDitherMethod, MagickFalse );
    //MagickSetFirstIterator( dest );
    //MagickSetImageIterations( dest, 0 );
    if( !MagickSetFormat( dest, "GIF" ) )
        MessageBox( NULL, (LPCSTR) "GIFセット失敗", (LPCSTR) "アニメーションGIF出力プラグイン", MB_OK|MB_ICONSTOP );
    dest = MagickOptimizeImageLayers( MagickCoalesceImages( dest ) );    //ここでdisposeが1になる
    MagickOptimizeImageTransparency( dest );    //6.7.8-7以降が必要
    if( !MagickWriteImages( dest, oip->savefile, MagickTrue ) )
        MessageBox( NULL, (LPCSTR) "出力失敗", (LPCSTR) "アニメーションGIF出力プラグイン", MB_OK|MB_ICONSTOP );
    
    DestroyMagickWand( dest );
    MagickWandTerminus();
    return TRUE;
}
