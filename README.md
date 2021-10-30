# mahjong_soul_autoplayer
auto play 「雀魂」

使った様子：https://youtu.be/VSJWE7hICeE

Python環境と以下のライブラリをインストールしておく必要がある。
numpy、mahjong、pyautogui、pywin32、keyboard、opencv-python、Pillow
１．最初にブラウザで「雀魂」のロビーを表示しておく必要がある。(firefox, chrome推奨)
２．起動はmain.pyを実行することでアプリウィンドウが表示される。
３．アプリウィンドウからウィンドウが選択されると、ウィンドウをキャプチャし、ロビー画面が確認できれば、アプリウィンドウでゲームルールが選択できるようになる。
４．ゲームルールが選択されると、自動プレイが開始される。
５．終了はEキーを長押しすることで停止する。
