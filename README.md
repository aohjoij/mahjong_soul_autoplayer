# mahjong_soul_autoplayer
auto play 「雀魂」

使った様子：https://youtu.be/VSJWE7hICeE

Python環境と以下のライブラリをインストールしておく必要がある。
<br><ol><li>numpy</li><li>mahjong</li><li>pyautogui</li><li>pywin32</li><li>keyboard</li><li>opencv-python</li><li>Pillow</li></ol>
<br>１．最初にブラウザで「雀魂」のロビーを表示しておく必要がある。(firefox, chrome推奨)
<br>２．起動はmain.pyを実行することでアプリウィンドウが表示される。
<br>３．アプリウィンドウからウィンドウが選択されると、ウィンドウをキャプチャし、ロビー画面が確認できれば、アプリウィンドウでゲームルールが選択できるようになる。
<br>４．ゲームルールが選択されると、自動プレイが開始される。
<br>５．終了はEキーを長押しすることで停止する。
