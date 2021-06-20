#ゲームをプレイする
import pyautogui as pag
import cv2
import win32gui
import numpy as np
from PIL import ImageGrab
import time
import mahjong as mj
from mahjong.tile import TilesConverter
from mahjong.shanten import Shanten

pag.FAILSAFE=False
def game_play(img_data):
    #exit()
    img_data=window_capture(img_data[1])
    height  =img_data[2][3]-img_data[2][1]
    width   =img_data[2][2]-img_data[2][0]
    resizeX =(width)/1920
    resizeY =(height-100)/1080
    resize=1
    if resizeX>=resizeY:
        resize=resizeY
    else:
        resize=resizeX
    img_decide=cv2.imread("System/mahjong_UI/OK.png")
    img_decide=cv2.resize(img_decide,(int(img_decide.shape[1]*resize),int(img_decide.shape[0]*resize)))
    result=cv2.matchTemplate(img_data[0], img_decide, cv2.TM_CCORR_NORMED)
    #探索した最も類似した点等の価値と座標を代入
    minVal, maxVal, minLoc, maxLoc=cv2.minMaxLoc(result)
    if 0.95 < maxVal:
        pag.click(maxLoc[0]+img_data[2][0],maxLoc[1]+img_data[2][1])
        pag.moveTo(img_data[2][0]+width//2,img_data[2][1]+height//2)
    #もし自動和了でなければ押す
    img_autoclear=cv2.imread("System/mahjong_UI/auto_clear.png")
    img_autoclear=cv2.resize(img_autoclear,(int(img_autoclear.shape[1]*resize),int(img_autoclear.shape[0]*resize)))
    result=cv2.matchTemplate(img_data[0], img_autoclear, cv2.TM_CCORR_NORMED)
    #探索した最も類似した点等の価値と座標を代入
    minVal, maxVal, minLoc, maxLoc=cv2.minMaxLoc(result)
    if 0.95 < maxVal:
        pag.click(maxLoc[0]+img_data[2][0],maxLoc[1]+img_data[2][1])
        pag.moveTo(img_data[2][0]+width//2,img_data[2][1]+height//2)
    #立直か判断
    img_reach=cv2.imread("System/mahjong_UI/REACH.png")
    img_reach=cv2.resize(img_reach,(int(img_reach.shape[1]*resize),int(img_reach.shape[0]*resize)))
    result=cv2.matchTemplate(img_data[0], img_reach, cv2.TM_CCORR_NORMED)
    #探索した最も類似した点等の価値と座標を代入
    minVal, maxVal, minLoc, maxLoc=cv2.minMaxLoc(result)
    if 0.95 < maxVal:
        pag.click(maxLoc[0]+img_data[2][0],maxLoc[1]+img_data[2][1])
        pag.click(maxLoc[0]+img_data[2][0],maxLoc[1]+img_data[2][1])
        pag.moveTo(img_data[2][0]+width//2,img_data[2][1]+height//2)
    
    #ペーがあればペー
    img_pee=cv2.imread("System/mahjong_UI/PEE.png")
    img_pee=cv2.resize(img_pee,(int(img_pee.shape[1]*resize),int(img_pee.shape[0]*resize)))
    result=cv2.matchTemplate(img_data[0], img_pee, cv2.TM_CCORR_NORMED)
    #探索した最も類似した点等の価値と座標を代入
    minVal, maxVal, minLoc, maxLoc=cv2.minMaxLoc(result)
    if 0.95 < maxVal:
        pag.click(maxLoc[0]+img_data[2][0],maxLoc[1]+img_data[2][1])
        pag.click(maxLoc[0]+img_data[2][0],maxLoc[1]+img_data[2][1])
    
    #スキップがあればスキップ
    img_skip=cv2.imread("System/mahjong_UI/SKIP.png")
    img_skip=cv2.resize(img_skip,(int(img_skip.shape[1]*resize),int(img_skip.shape[0]*resize)))
    result=cv2.matchTemplate(img_data[0], img_skip, cv2.TM_CCORR_NORMED)
    #探索した最も類似した点等の価値と座標を代入
    minVal, maxVal, minLoc, maxLoc=cv2.minMaxLoc(result)
    if 0.95 < maxVal:
        pag.click(maxLoc[0]+img_data[2][0],maxLoc[1]+img_data[2][1])
        pag.click(maxLoc[0]+img_data[2][0],maxLoc[1]+img_data[2][1])
    
    #自分のターンかどうか判定
    pag.moveTo(img_data[2][0],img_data[2][1])
    img_myturn=cv2.imread("System/mahjong_UI/MY_TURN.png")
    img_myturn=cv2.resize(img_myturn,(int(img_myturn.shape[1]*resize),int(img_myturn.shape[0]*resize)))
    result=cv2.matchTemplate(img_data[0], img_myturn, cv2.TM_CCORR_NORMED)
    myturn=False
    #探索した最も類似した点等の価値と座標を代入
    minVal, maxVal, minLoc, maxLoc=cv2.minMaxLoc(result)
    if 0.98 < maxVal:
        myturn=True
        time.sleep(0.1)
    #自分のターンなら手牌を抽出し、関数Brainを実行
    if myturn:
        img_handhorizon=cv2.imread("System/mahjong_UI/triangle.png")
        img_handhorizon=cv2.resize(img_handhorizon,(int(img_handhorizon.shape[1]*resize),int(img_handhorizon.shape[0]*resize)))
        result=cv2.matchTemplate(img_data[0], img_handhorizon, cv2.TM_CCORR_NORMED)
        minVal, maxVal, minLoc, maxLoc=cv2.minMaxLoc(result)
        img_tile=cv2.imread("System/mahjong_UI/man_1r.png")
        img_tile=cv2.resize(img_tile,(int(img_tile.shape[1]*resize),int(img_tile.shape[0]*resize)))
        img_hands,hand_Loc=window_handcapture((maxLoc[0],maxLoc[1]+img_tile.shape[1]),img_data)
        print(img_hands.shape)
        #cv2.imshow("img",img_hands)
        handlist=np.zeros((34,3),dtype="int32")
        for i in range(1,10):
            img_tile=cv2.imread("System/mahjong_UI/man_"+str(i)+"r.png")
            img_tile=cv2.resize(img_tile,(int(img_tile.shape[1]*resize),int(img_tile.shape[0]*resize)))
            for l in range(4):
                result=cv2.matchTemplate(img_hands, img_tile, cv2.TM_CCORR_NORMED)
                minVal, maxVal, minLoc, maxLoc=cv2.minMaxLoc(result)
                #print(str(i)+str(maxVal))
                if 0.987 < maxVal:
                    print("man_"+str(i)+"："+str(maxVal))
                    ads=maxLoc[0]
                    handlist[i-1][0]+=1
                    handlist[i-1][1]=maxLoc[0]
                    handlist[i-1][2]=maxLoc[1]
                    for k in range(maxLoc[0],maxLoc[0]+int(img_tile.shape[1]*0.9)):
                        for m in range(maxLoc[1],maxLoc[1]+int(img_tile.shape[0]*0.9)):
                            img_hands[m][k]=[0,0,255]
                else:
                    break

            img_tile=cv2.imread("System/mahjong_UI/pin_"+str(i)+"r.png")
            img_tile=cv2.resize(img_tile,(int(img_tile.shape[1]*resize),int(img_tile.shape[0]*resize)))
            for l in range(4):
                result=cv2.matchTemplate(img_hands, img_tile, cv2.TM_CCORR_NORMED)
                minVal, maxVal, minLoc, maxLoc=cv2.minMaxLoc(result)
                if 0.987 < maxVal:
                    print("pin_"+str(i)+"："+str(maxVal))
                    handlist[i-1+9][0]+=1
                    handlist[i-1+9][1]=maxLoc[0]
                    handlist[i-1+9][2]=maxLoc[1]
                    for k in range(maxLoc[0],maxLoc[0]+int(img_tile.shape[1]*0.9)):
                        for m in range(maxLoc[1],maxLoc[1]+int(img_tile.shape[0]*0.9)):
                            img_hands[m][k]=[0,0,255]
                else:
                    break

            img_tile=cv2.imread("System/mahjong_UI/sou_"+str(i)+"r.png")
            img_tile=cv2.resize(img_tile,(int(img_tile.shape[1]*resize),int(img_tile.shape[0]*resize)))
            for l in range(4):
                result=cv2.matchTemplate(img_hands, img_tile, cv2.TM_CCORR_NORMED)
                minVal, maxVal, minLoc, maxLoc=cv2.minMaxLoc(result)
                if 0.987 < maxVal:
                    print("sou_"+str(i)+"："+str(maxVal))
                    handlist[i-1+18][0]+=1
                    handlist[i-1+18][1]=maxLoc[0]
                    handlist[i-1+18][2]=maxLoc[1]
                    for k in range(maxLoc[0],maxLoc[0]+int(img_tile.shape[1]*0.9)):
                        for m in range(maxLoc[1],maxLoc[1]+int(img_tile.shape[0]*0.9)):
                            img_hands[m][k]=[0,0,255]
                else:
                    break

            if i==9:
                img_tile=cv2.imread("System/mahjong_UI/pin_"+str(i)+"rg.png")
                img_tile=cv2.resize(img_tile,(int(img_tile.shape[1]*resize),int(img_tile.shape[0]*resize)))

                for l in range(4):
                    result=cv2.matchTemplate(img_hands, img_tile, cv2.TM_CCORR_NORMED)
                    minVal, maxVal, minLoc, maxLoc=cv2.minMaxLoc(result)
                    print("pin_"+str(i)+"："+str(maxVal))
                    if 0.98 < maxVal:
                        print("pin_"+str(i)+"rg："+str(maxVal))
                        handlist[i-1+9][0]+=1
                        handlist[i-1+9][1]=maxLoc[0]
                        handlist[i-1+9][2]=maxLoc[1]
                        for k in range(maxLoc[0],maxLoc[0]+int(img_tile.shape[1]*0.9)):
                            for m in range(maxLoc[1],maxLoc[1]+int(img_tile.shape[0]*0.9)):
                                img_hands[m][k]=[0,0,255]
                    else:
                        break
            if i<8 and i!=5:
                img_tile=cv2.imread("System/mahjong_UI/hon_"+str(i)+"r.png")
                img_tile=cv2.resize(img_tile,(int(img_tile.shape[1]*resize),int(img_tile.shape[0]*resize)))
                for l in range(4):
                    result=cv2.matchTemplate(img_hands, img_tile, cv2.TM_CCORR_NORMED)
                    minVal, maxVal, minLoc, maxLoc=cv2.minMaxLoc(result)
                    if 0.987 < maxVal:
                        print("hon_"+str(i)+"："+str(maxVal))
                        handlist[i-1+27][0]+=1
                        handlist[i-1+27][1]=maxLoc[0]
                        handlist[i-1+27][2]=maxLoc[1]
                        for k in range(maxLoc[0],maxLoc[0]+int(img_tile.shape[1]*0.9)):
                            for m in range(maxLoc[1],maxLoc[1]+int(img_tile.shape[0]*0.9)):
                                img_hands[m][k]=[0,0,255]
                    else:
                        break

            if i==5:
                img_tile=cv2.imread("System/mahjong_UI/man_"+str(i)+"dr.png")
                img_tile=cv2.resize(img_tile,(int(img_tile.shape[1]*resize),int(img_tile.shape[0]*resize)))
                for l in range(4):
                    result=cv2.matchTemplate(img_hands, img_tile, cv2.TM_CCORR_NORMED)
                    minVal, maxVal, minLoc, maxLoc=cv2.minMaxLoc(result)
                    if 0.987 < maxVal:
                        print("man_"+str(i)+"d："+str(maxVal))
                        handlist[i-1][0]+=1
                        handlist[i-1][1]=maxLoc[0]
                        handlist[i-1][2]=maxLoc[1]
                        for k in range(maxLoc[0],maxLoc[0]+int(img_tile.shape[1]*0.9)):
                            for m in range(maxLoc[1],maxLoc[1]+int(img_tile.shape[0]*0.9)):
                                img_hands[m][k]=[0,0,255]
                    else:
                        break

                img_tile=cv2.imread("System/mahjong_UI/pin_"+str(i)+"dr.png")
                img_tile=cv2.resize(img_tile,(int(img_tile.shape[1]*resize),int(img_tile.shape[0]*resize)))
                for l in range(4):
                    result=cv2.matchTemplate(img_hands, img_tile, cv2.TM_CCORR_NORMED)
                    minVal, maxVal, minLoc, maxLoc=cv2.minMaxLoc(result)
                    if 0.987 < maxVal:
                        print("pin_"+str(i)+"d："+str(maxVal))
                        handlist[i-1+9][0]+=1
                        handlist[i-1+9][1]=maxLoc[0]
                        handlist[i-1+9][2]=maxLoc[1]
                        for k in range(maxLoc[0],maxLoc[0]+int(img_tile.shape[1]*0.9)):
                            for m in range(maxLoc[1],maxLoc[1]+int(img_tile.shape[0]*0.9)):
                                img_hands[m][k]=[0,0,255]
                    else:
                        break

                img_tile=cv2.imread("System/mahjong_UI/sou_"+str(i)+"dr.png")
                img_tile=cv2.resize(img_tile,(int(img_tile.shape[1]*resize),int(img_tile.shape[0]*resize)))
                for l in range(4):
                    result=cv2.matchTemplate(img_hands, img_tile, cv2.TM_CCORR_NORMED)
                    minVal, maxVal, minLoc, maxLoc=cv2.minMaxLoc(result)
                    if 0.987 < maxVal:
                        print("sou_"+str(i)+"d："+str(maxVal))
                        handlist[i-1+18][0]+=1
                        handlist[i-1+18][1]=maxLoc[0]
                        handlist[i-1+18][2]=maxLoc[1]
                        for k in range(maxLoc[0],maxLoc[0]+int(img_tile.shape[1]*0.9)):
                            for m in range(maxLoc[1],maxLoc[1]+int(img_tile.shape[0]*0.9)):
                                img_hands[m][k]=[0,0,255]
                    else:
                        break
                
                img_tile=cv2.imread("System/mahjong_UI/hon_"+str(i)+"r.png")
                img_tile=cv2.resize(img_tile,(int(img_tile.shape[1]*resize),int(img_tile.shape[0]*resize)))
                for l in range(4):
                    result=cv2.matchTemplate(img_hands, img_tile, cv2.TM_CCORR_NORMED)
                    minVal, maxVal, minLoc, maxLoc=cv2.minMaxLoc(result)
                    if 0.999 < maxVal:
                        print("hon_"+str(i)+"："+str(maxVal))
                        handlist[i-1+27][0]+=1
                        handlist[i-1+27][1]=maxLoc[0]
                        handlist[i-1+27][2]=maxLoc[1]
                        for k in range(maxLoc[0],maxLoc[0]+int(img_tile.shape[1]*0.9)):
                            for m in range(maxLoc[1],maxLoc[1]+int(img_tile.shape[0]*0.9)):
                                img_hands[m][k]=[0,0,255]
                    else:
                        break
        #print(handlist)
        #cv2.imshow("img",img_hands)
        #cv2.waitKey()
        if(np.sum(handlist,axis=0)[0]==14):
            discard_tile=brain(handlist[:,0])
            discard_tile=discard_tile//10*9+discard_tile%10-1
            print(discard_tile)
            pag.click(hand_Loc[0]+handlist[discard_tile][1],hand_Loc[1]+handlist[discard_tile][2])
            pag.click(hand_Loc[0]+handlist[discard_tile][1],hand_Loc[1]+handlist[discard_tile][2])
            pag.moveTo(img_data[2][0]+width//2,img_data[2][1]+height//2)

    #関数Brainからの結果から手牌を捨てる
    return

def window_capture(hnd):
    img_xy=win32gui.GetWindowRect(hnd)
    img=np.asarray(ImageGrab.grab(bbox=(img_xy)))
    img=cv2.cvtColor(img,cv2.COLOR_RGB2BGR)
    #cv2.imshow("image",img)
    return img,hnd,img_xy

def window_handcapture(Loc,img_data):
    img=np.asarray(ImageGrab.grab(bbox=(img_data[2][0],Loc[1]+img_data[2][1],img_data[2][2],img_data[2][3])))
    img=cv2.cvtColor(img,cv2.COLOR_RGB2BGR)
    #cv2.imshow("image",img)
    return img,[img_data[2][0],Loc[1]+img_data[2][1],img_data[2][2],img_data[2][3]]

def brain(handlist):
    hl=[]
    for i in range(34):
        for l in range(handlist[i]):
            hl.append(i//9*10+i%9+1)
    S=JGshanten(hl)
    for i in range(13,-1,-1):
        hand=[]
        for l in range(14):
            if i!=l:
                hand.append(hl[l])
        if S>=JGshantenG(hand):
            return hl[i]

    return np.random.choice(hand)

def JGshanten(hands):
    man=''
    pin=''
    sou=''
    honors=''
    for i in range(0,14):
        if hands[i]//10==0:
            man+=str(hands[i]%10)
        elif hands[i]//10==1:
            pin+=str(hands[i]%10)
        elif hands[i]//10==2:
            sou+=str(hands[i]%10)
        elif hands[i]//10==3:
            honors+=str(hands[i]%10)
    print(man+","+pin+","+sou+","+honors)
    hands_tiles=TilesConverter.string_to_34_array(man, pin, sou, honors)
    shantenJG=Shanten()
    return shantenJG.calculate_shanten(hands_tiles)

def JGshantenG(hands):
    man=''
    pin=''
    sou=''
    honors=''
    for i in range(0,13):
        if hands[i]//10==0:
            man+=str(hands[i]%10)
        elif hands[i]//10==1:
            pin+=str(hands[i]%10)
        elif hands[i]//10==2:
            sou+=str(hands[i]%10)
        elif hands[i]//10==3:
            honors+=str(hands[i]%10)
    print(man+","+pin+","+sou+","+honors)
    hands_tiles=TilesConverter.string_to_34_array(man, pin, sou, honors)
    shantenJG=Shanten()
    return shantenJG.calculate_shanten(hands_tiles)