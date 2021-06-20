#img_dataからゲーム（ロビー画面）かどうか判断する
import cv2


def game_is_true(img_data):
    #ウィンドウサイズから拡大縮小
    height  =img_data[2][3]-img_data[2][1]
    width   =img_data[2][2]-img_data[2][0]
    resizeX =(width)/1920
    resizeY =(height-100)/1080
    resize=1
    if resizeX>=resizeY:
        resize=resizeY
    else:
        resize=resizeX

    #判定用画像読み込み
    search_target=cv2.imread('System/mahjong_UI/rank_match.png')
    #判定用画像をウィンドウサイズに適するサイズに変更
    search_target=cv2.resize(search_target,(int(search_target.shape[1]*resize),int(search_target.shape[0]*resize)))
    #確認用
    #cv2.imshow("image",search_target)
    #探索結果をresultに代入
    result=cv2.matchTemplate(img_data[0], search_target, cv2.TM_CCORR_NORMED)
    #探索した最も類似した点等の価値と座標を代入
    minVal, maxVal, minLoc, maxLoc=cv2.minMaxLoc(result)
    #print(maxVal)
    if 0.90 < maxVal:
        return True, maxLoc
    else:
        return False, maxLoc
    return False, maxLoc
