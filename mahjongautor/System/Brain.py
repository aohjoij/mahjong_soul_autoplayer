import numpy as np
import mahjong as mj
from mahjong.tile import TilesConverter
from mahjong.shanten import Shanten
def brain(handlist):
    hand=[]
    S=JGshanten(hand)
    for i in range(34):
        for l in range(handlist[i]):
            hand.append(i//9*10+i%9+1)
    for i in range(14):

        if S==JGshanten(np.delete(hand,i)):
            return hand[i]

    return np.random.choice(hand,1)

def JGshanten(hands):
    hands=np.sort(hands)
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
    hands_tiles=TilesConverter.string_to_34_array(man, pin, sou, honors)
    shantenJG=Shanten()
    return shantenJG.calculate_shanten(hands_tiles)