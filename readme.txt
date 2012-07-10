-----------------------------------------------------------------------
アニメーションGIF出力プラグイン v0.0.2
-----------------------------------------------------------------------

Copyright (c) 2012 Hiroki Taniura (boiled.sugar at gmail dot com)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.


【これは何？】
AviUtlから直接アニメーションGIFを出力するプラグインがなかったので作ってみました。
画像処理はImageMagick-6.7.8-1を使用しています。
ランタイム等は特に必要無いはずです。

【使用方法】
出力範囲を選択し、プラグイン出力→アニメーションGIF出力
表示タイミングはAviUtlのフレームレートをそのまま使いますが、
1/100秒単位で四捨五入されるため、多少の誤差が出ます。
例えば24fpsのアニメを出力すると、4/100秒で画像が切り替わることになるので、25fpsとなります。
コピーフレームに対応しており、コピーフレーム数分だけ前のフレームの表示時間が長くなります。
つまり後のフレームの表示タイミングはそのままでフレームの間引きができます。
出力中AviUtlが応答なしになっても多分処理中なので強制終了しないでください。
フレームを全部出力した後の処理にも結構時間がかかります。

【注意事項】
短い範囲を選択して使用することをお勧めします。
長い範囲を選択すると大量にメモリを消費します。
上限値はLargeAddresAware無効時は約1.7GB、有効時は約2.2GBのようです。
それを超えるとTEMPに大量の一時ファイルが物凄い勢いで作成されます。
どうしても長い範囲を出力したいなら試してもいいかもしれませんが、
ドライブを埋め尽くしてもまだメモリが足りなかった場合はエラーで止まります。
またウィルス対策ソフトが一時ファイルに反応して遅くなるので、一時的に無効化をお勧めします。
一時ファイルができてしまった場合、削除は手動で行わなければならないようです。
添付のCleanTEMP.batを実行するか、手動で%TEMP%\magick-*を削除してください。

実験してみたところ、640x360を2000フレーム出力すると4GBのRAMDISKが溢れました。
1000フレームだとメモリ消費量は2.2GB以下に収まりました。
とりあえず500フレームを超えた場合警告を出すようにしていますが
画像サイズも影響するので注意してください。
40フレームだとメモリ消費量は200MB程度です。


【ライセンス】
MIT Licenseです。

【レポジトリ】
https://github.com/boiled-sugar/Animated-GIF-output-plugin/

【変更履歴】
0.0.3
・表示タイミングを四捨五入に
　以前は切り捨てられていました。

0.0.2
・コピーフレームに対応
・高速化・メモリ消費量低減
　ImageMagickのOpenMPを有効化してColorDepthを8に変更したことによるもので
　プラグイン本体の処理はそのままです。

0.0.1
・とりあえず作成
