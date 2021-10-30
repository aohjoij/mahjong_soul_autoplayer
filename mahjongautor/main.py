#tkinter
import tkinter as tk
from tkinter import ttk
Window_Title="mahjong_Autor"
Window_Size ="640x480"
#winxpgui
import win32gui
#ctypes
import ctypes
#keyboard 
import keyboard 
#time
import time
#cv2
import cv2
#System(original)
#from System import system_main as SM
from System import game_play as gp
from System import game_search as gs
from System import select_match as sm
from System import window_capture as wc
class MAINFRAME:
    def __init__(self):

        #ウィンドウハンドル一覧を取得
        self.all_Window_list=[]
        self.sus_Window_list=[]
        self.sus_Window_titles=[]

        self.Window_handle_reload()
        #ウィンドウ作成
        self.win = tk.Tk()
        #タイトル設定
        self.win.title(Window_Title)
        #サイズ設定
        self.win.geometry(Window_Size)

        def start_click():
            if self.Window_List.get() in self.sus_Window_titles:
                for X in self.sus_Window_list:
                    if self.Window_List.get() in X:
                        print(X)
                        self.windowtitle=X[1]
                        self.start_System()
            return

        # ラベルを作成
        self.label = tk.Label(self.win, text='ウィンドウを選択してください')

        #ウィンドウ選択ドロップダウンリスト作成
        self.Window_List = ttk.Combobox(self.win,state='readonly',values=self.sus_Window_titles,width=97)

        # reloadボタンを作成
        self.reload_icon=tk.PhotoImage(file="reload_icon.png")
        self.reloadButton = tk.Button(self.win, text='', image=self.reload_icon,command=self.reload_click)

        #startボタンを作成
        self.startButton = tk.Button(self.win, text='start', command=start_click)

        #その他
        self.phase=0
        self.win.title(Window_Title + "（ ゲームモードを選択してください ）")
        self.label0 = tk.Label(self.win, text='マッチングするランクを設定してください')
        self.match_floor_List = ttk.Combobox(self.win,state='readonly',values=["銅の間","銀の間","金の間","玉の間","王座の間"],width=10)
        self.label2 = tk.Label(self.win, text='マッチングするルールを選択してください')
        self.match_rule_List = ttk.Combobox(self.win,state='readonly',values=["四人東","四人南","三人東","三人南"],width=10)
        self.startSystemButton = tk.Button(self.win, text='start', command=lambda:self.System())
        self.labelf=tk.Label(self.win, text='実行中...(Eキー長押しで終了)')

        #いろいろ配置
        self.label.grid(column=0,row=0,columnspan=2)
        self.Window_List.grid(column=0,row=1,padx=3)
        self.reloadButton.grid(column=1,row=1,padx=3)
        self.startButton.grid(column=0,row=2,columnspan=2)
        
        #ウィンドウ出力
        self.win.mainloop()
        return
        
    

    def Window_handle_reload(self):
        self.all_Window_list.clear()
        self.sus_Window_list.clear()
        self.sus_Window_titles.clear()
        user32 = ctypes.WinDLL("user32")
        EnumWindowsProc = ctypes.WINFUNCTYPE(ctypes.c_bool, ctypes.c_void_p, ctypes.c_void_p)
        user32.EnumWindows.restype = ctypes.c_bool
        user32.EnumWindows.argtypes = (EnumWindowsProc, ctypes.c_void_p)
        user32.GetWindowTextW.restype = ctypes.c_int32
        user32.GetWindowTextW.argtypes = (ctypes.c_void_p, ctypes.c_wchar_p, ctypes.c_int32)

        def callback(hWnd, lParam):
            windowText = ctypes.create_unicode_buffer(1024)
            user32.GetWindowTextW(hWnd, windowText, len(windowText))
            self.all_Window_list.append(["{0:x}".format(hWnd),"{0}".format(windowText.value)])
            return True

        user32.EnumWindows(EnumWindowsProc(callback), None)
        for X in self.all_Window_list:
            if (("Chrome" in X[1]) or ("Firefox" in X[1]) or ("Edge" in X[1]) or ("雀魂" in X[1])):
                self.sus_Window_list.append(X)
                self.sus_Window_titles.append(X[1])
        del user32
        return


    
    def make_window(self):
        def start_click():
            if self.Window_List.get() in self.sus_Window_titles:
                for X in self.sus_Window_list:
                    if self.Window_List.get() in X:
                        print(X)
                        self.windowtitle=X[1]
                        self.start_System()
            return
        self.label.grid_forget()
        self.Window_List.grid_forget()
        self.reloadButton.grid_forget()
        self.startButton.grid_forget()
        # ラベルを作成
        self.label = tk.Label(self.win, text='ウィンドウを選択してください')

        #ウィンドウ選択ドロップダウンリスト作成
        self.Window_List = ttk.Combobox(self.win,state='readonly',values=self.sus_Window_titles,width=97)

        # reloadボタンを作成
        self.reload_icon=tk.PhotoImage(file="reload_icon.png")
        self.reloadButton = tk.Button(self.win, text='', image=self.reload_icon,command=self.reload_click)

        #startボタンを作成
        self.startButton = tk.Button(self.win, text='start', command=start_click)

        #いろいろ配置
        self.label.grid(column=0,row=0,columnspan=2)
        self.Window_List.grid(column=0,row=1,padx=3)
        self.reloadButton.grid(column=1,row=1,padx=3)
        self.startButton.grid(column=0,row=2,columnspan=2)

        #ウィンドウ出力
        self.win.mainloop()
        return

    def reload_click(self):
        self.Window_handle_reload()
        self.make_window()
        return

    def start_System(self):
        
        self.label0.grid_forget()
        self.match_floor_List.grid_forget()
        self.label2.grid_forget()
        self.match_rule_List.grid_forget()
        self.startSystemButton.grid_forget()
        try:
            self.hnd = win32gui.FindWindow(None, self.windowtitle)
        except :
            return
        self.phase = 0
        self.img_data = wc.window_capture(self.windowtitle)
        self.gsresult = gs.game_is_true(self.img_data)
        if(self.gsresult[0]):
            self.phase = 1
            print(self.gsresult[1])
        else:
            self.reload_click()
        #マッチング設定等させる
        #~~~~~~~~~~~~~~~~~
        #設定いろいろ配置
        self.label0.grid(column=0,row=3,columnspan=2)
        self.match_floor_List.grid(column=0,row=4,columnspan=2)
        self.label2.grid(column=0,row=5,columnspan=2)
        self.match_rule_List.grid(column=0,row=6,columnspan=2)
        self.startSystemButton.grid(column=0,row=7,columnspan=2)
        #出力
        self.win.mainloop()
        #~~~~~~~~~~~~~~~~~
        
        return

    def System(self):
        print("start")
        #今までのオブジェクト排除
        self.label.grid_forget()
        self.Window_List.grid_forget()
        self.reloadButton.grid_forget()
        self.startButton.grid_forget()
        self.label0.grid_forget()
        self.match_floor_List.grid_forget()
        self.label2.grid_forget()
        self.match_rule_List.grid_forget()
        self.startSystemButton.grid_forget()

        self.win.title("mahjongAutor（" + self.windowtitle + "）")
        self.win.geometry("640x50")
        self.finishSystemButton = tk.Button(self.win, text='finish', command=lambda:exit())
        self.labelf.pack()
        self.finishSystemButton.pack()

        self.win.after(100,self.main_system_loop)
        self.win.mainloop()
        
        return
    def main_system_loop(self):
        self.main_system()
        self.win.after(100,self.main_system_loop)
        return

    def main_system(self):
        if keyboard.is_pressed('e') == True:
            exit()
        try:
            self.img_data = wc.window_capture(self.windowtitle)
        except:
            return
        self.gsresult = gs.game_is_true(self.img_data)
        if(self.gsresult[0]):
            self.phase = 1
        #phase1 選ばれたマッチングを開始後phase2に移行
        if self.phase==1:
            #結果はture or falseで返す
            if sm.select_match(self.match_floor_List.get(),self.match_rule_List.get(),self.img_data):
                self.phase=2
        #phase2 盤面が開始されたことを確認後phase3に移行
        elif self.phase==2:
            #結果はture or falseで返す
            #if ms.match_start(self.img_data):
            self.phase=3
        #phase3 実際にプレイを開始
        elif self.phase==3:
            gp.game_play(self.img_data)
        
        return

test=MAINFRAME()
