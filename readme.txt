-----------------------------------------------------------------------
アニメーションGIF出力プラグイン v0.01
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
画像処理はImageMagickを使用しています。
ランタイム等は特に必要無いはずです。

【使用方法】
出力範囲を選択し、プラグイン出力→アニメーションGIF出力
表示タイミングはAviUtlのフレームレートをそのまま使いますが、
1/100秒単位のため、多少の誤差が出ます。
例えば24fpsのアニメを出力すると、4/100秒で画像が切り替わることになるので、25fpsとなります。
AviUtlが応答なしになっても多分処理中なので強制終了しないでください。

【注意事項】
短い範囲を選択して使用することをお勧めします。
試しに640x360を2209フレーム出力してみたのですが、AviUtlが1.7GBほどメモリを消費し、
TEMPに大量のファイルが作成され、4GBのRAMDISKを埋め尽くしてエラーで止まりました。
40フレームだとメモリ消費量は300MBほどで、一時ファイルも作成されません。
色々試した結果、約1.7GBがメモリ消費量の上限でそれを超えると一時ファイルが作成されるようです。
400フレームだとメモリ消費量は1.3GB程で、500フレームだとメモリ消費量が上限に達し、
TEMPの消費は400MBほどでした。
そこで選択範囲が400フレームより多い場合に本当に続行するか尋ねるようにしましたが、
画像サイズも影響するので十分に注意してください。
一時ファイルができてしまった場合、削除は手動で行わなければならないようです。
手動で%TEMP%\magick*を削除してください。

【ライセンス】
MIT Licenseです。

【レポジトリ】
https://github.com/boiled-sugar/Animated-GIF-output-plugin/