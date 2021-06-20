#ロビー画面からマッチ申請する（設定によってマッチを選択）
import pyautogui as pag
import time
import cv2
import win32gui
import numpy as np
from PIL import ImageGrab

def select_match(matching_floor,matching_rule,img_data):
    b=False
    #ウィンドウサイズから拡大縮小率出力
    height  =img_data[2][3]-img_data[2][1]
    width   =img_data[2][2]-img_data[2][0]
    resizeX =(width)/1920
    resizeY =(height-100)/1080
    resize=1
    if resizeX>=resizeY:
        resize=resizeY
    else:
        resize=resizeX
    #銅の間,銀の間,金の間,玉の間,王座の間から選択
    matching_floor_img=cv2.imread('System/mahjong_UI/rank_match.png')
    matching_floor_img=cv2.resize(matching_floor_img,(int(matching_floor_img.shape[1]*resize),int(matching_floor_img.shape[0]*resize)))
    #探索結果をresultに代入
    result=cv2.matchTemplate(img_data[0], matching_floor_img, cv2.TM_CCORR_NORMED)
    #探索した最も類似した点等の価値と座標を代入
    minVal, maxVal, minLoc, maxLoc=cv2.minMaxLoc(result)
    #print("dani"+str(maxVal))
    if 0.90 < maxVal:
        print(maxLoc+(img_data[2][0],img_data[2][1]))
        pag.click(maxLoc[0]+img_data[2][0],maxLoc[1]+img_data[2][1])
        pag.click(maxLoc[0]+img_data[2][0],maxLoc[1]+img_data[2][1])
        pag.moveTo(img_data[2][0]+width//2,img_data[2][1]+height//2)
        time.sleep(2)


    if matching_floor=="銅の間":
        matching_floor_img=cv2.imread('System/mahjong_UI/bronze_floor.png')
    elif matching_floor=="銀の間":
        matching_floor_img=cv2.imread('System/mahjong_UI/silver_floor.png')
    elif matching_floor=="金の間":
        matching_floor_img=cv2.imread('System/mahjong_UI/gold_floor.png')
    elif matching_floor=="玉の間":
        matching_floor_img=cv2.imread('System/mahjong_UI/diamond_floor.png')
    elif matching_floor=="王座の間":
        matching_floor_img=cv2.imread('System/mahjong_UI/king_floor.png')

    img_data=window_captureB(img_data[1])
    matching_floor_img=cv2.resize(matching_floor_img,(int(matching_floor_img.shape[1]*resize),int(matching_floor_img.shape[0]*resize)))
    result=cv2.matchTemplate(img_data[0], matching_floor_img, cv2.TM_CCORR_NORMED)
    minVal, maxVal, minLoc, maxLoc=cv2.minMaxLoc(result)
    #print("rank"+str(maxVal))
    if 0.90 < maxVal:
        pag.click(maxLoc[0]+img_data[2][0],maxLoc[1]+img_data[2][1])
        pag.click(maxLoc[0]+img_data[2][0],maxLoc[1]+img_data[2][1])
        pag.moveTo(img_data[2][0]+width//2,img_data[2][1]+height//2)
        time.sleep(2)


    
    #四人東,四人南,三人東,三人南から選択
    if matching_rule=="四人東":
        matching_rule_img=cv2.imread('System/mahjong_UI/four_east.png')
    elif matching_rule=="四人南":
        matching_rule_img=cv2.imread('System/mahjong_UI/four_south.png')
    elif matching_rule=="三人東":
        matching_rule_img=cv2.imread('System/mahjong_UI/three_east.png')
    elif matching_rule=="三人南":
        matching_rule_img=cv2.imread('System/mahjong_UI/three_south.png')

    img_data=window_captureB(img_data[1])
    matching_rule_img=cv2.resize(matching_rule_img,(int(matching_rule_img.shape[1]*resize),int(matching_rule_img.shape[0]*resize)))
    result=cv2.matchTemplate(img_data[0], matching_rule_img, cv2.TM_CCORR_NORMED)
    minVal, maxVal, minLoc, maxLoc=cv2.minMaxLoc(result)
    #print("rule"+str(maxVal))
    pag.moveTo(maxLoc[0]+img_data[2][0],maxLoc[1]+img_data[2][1])
    pag.scroll(-100)
    time.sleep(0.5)
    if 0.90 < maxVal:
        
        pag.click(maxLoc[0]+img_data[2][0],maxLoc[1]+img_data[2][1])
        pag.click(maxLoc[0]+img_data[2][0],maxLoc[1]+img_data[2][1])
        pag.moveTo(img_data[2][0]+width//2,img_data[2][1]+height//2)
        time.sleep(2)
        b=True
    return b

def window_captureB(windowhnd):
    img_xy=win32gui.GetWindowRect(windowhnd)
    img=np.asarray(ImageGrab.grab(bbox=(img_xy)))
    img=cv2.cvtColor(img,cv2.COLOR_RGB2BGR)
    #cv2.imshow("image",img)
    return img,windowhnd,img_xy
