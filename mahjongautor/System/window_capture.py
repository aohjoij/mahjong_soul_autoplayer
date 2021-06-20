import cv2
import win32gui
import numpy as np
from PIL import ImageGrab
def window_capture(windowtitle):
    hnd = win32gui.FindWindow(None, windowtitle)
    img_xy=win32gui.GetWindowRect(hnd)
    img=np.asarray(ImageGrab.grab(bbox=(img_xy)))
    img=cv2.cvtColor(img,cv2.COLOR_RGB2BGR)
    #cv2.imshow("image",img)
    return img,hnd,img_xy