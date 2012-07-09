@ECHO OFF
IF EXIST %TEMP%\magick-* (DEL /Q %TEMP%\magick-*) ELSE ECHO 一時ファイルは存在しません。 && PAUSE && EXIT
IF EXIST %TEMP%\magick-* (ECHO AviUtlを終了してから実行してください。) ELSE ECHO 一時ファイルを削除しました。
PAUSE
