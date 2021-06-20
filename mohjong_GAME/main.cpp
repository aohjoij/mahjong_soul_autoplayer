#include<DxLib.h>
#include<iostream>
#include <stdio.h>
#include<array>
#include<time.h>
#include<array>
#include<time.h>
using namespace std;
class player;

typedef class mohjong_game {
private:
	array<int, 34> HAIYAMA;		//牌山
	array<int, 34>HAIPAI;
	int Wind;					//場風
	int Turn;					//局
	int mainboard;
	int boardcentermain;
	int boardpoint;
	int point;
	
public:
	mohjong_game();				//コンストラクタ
	int GAME_3();				//ゲームを行う
	int GAME_4();				//ゲームを行う
	int draw();					//牌山からランダムに1枚返す
	int display(player* P,int t);				//盤面を表示する
	int show_turn() { return Turn; }

	array<int, 34>show_HAIYAMA() { return HAIYAMA; }
}MG;

class player {
private:
	array<int, 14> Hand;		//手牌
	array<int, 12>rotated;		//鳴き牌
	array<int, 34>handlist;
	array<int, 30>discards;		//捨て牌
	array<int, 4>chi;
	array<int, 4>pon;
	int my_wind;				//自風
	int reach;					//リーチ
	int point;					//持ち点
public:
	int handendx = 0;
	int handpreend = 0;
	player(int n, MG *mg);
	array<int, 14> show_hand() { return Hand; }
	array<int, 12> show_rotated() { return rotated; }
	array<int, 30> show_discards() { return discards; }
	array<int, 4>show_chi() { return chi; };
	array<int, 4>show_pon() { return pon; };

	int show_my_wind() { return my_wind; }
	void set_point(int p) { point = p; }
	void set_reach(int r) { reach = r; }
	int add_point(int p) { point += p;return point; }
	int draw(int d) { Hand[13] = d;handsort(13);return 1; }
	int show_reach() { return reach; }
	int discard(int t);
	void handsort(int n);
	int JG_chows();
	int JG_pungs(int p);
	int JG_tenpai(MG mg, int d);
	int JG_claim(MG mg);
	int JG_ron(MG mg, int r);
	int calculation_point(int L, MG mg);
	int calculation_point(int L, player target, MG mg);
	//特殊形
	int JG_KOKUSI();			//国士無双判定
	int JG_7Pairs();			//七対子判定
	//１飜
	int JG_Reach();				//立直判定
	int JG_Simples();			//断ヤオ判定
	int JG_Runs();				//平和判定
	int JG_Self_Draw();			//門前自摸判定
	int JG_First_Turn(MG mg, char t);		//一発判定
	int JG_Double_Runs();		//一盃口判定
	int JG_Final_TileR(MG mg);	//河底撈魚(ホウテイロン)判定
	int JG_Final_TileT(MG mg);	//海底摸月(ハイテイツモ)判定
	int JG_King_Tile();			//嶺上開花判定
	int JG_Double_Reach();		//二重立直判定
	int JG_Add_A_Quad();		//槍槓判定
	//２飜
	int JG_All_Triples();		//対々和判定
	int JG_Three_Color();		//三色同順判定
	int JG_Full_Stright();		//一気通貫判定
	int JG_Mixed_Outside_Hand();//混全帯判定
	int JG_Three_Triples(char t);		//三暗刻判定
	int JG_Little_Dragons();	//小三元判定
	int JG_All_Terminals_Honors();//混老頭判定
	int JG_Three_Color_Triples();//三色同刻判定
	int JG_Three_Quads();		//三槓子
	//３飜
	int JG_Half_Flush();		//混一色判定
	int JG_Pure_Outside_Hand();	//清全帯判定
	int JG_Double_Double_Runs();//二盃口判定
	//６飜
	int JG_Full_Flush();		//清一色判定
	//１３飜(役満)
	int JG_Four_Concealed_Triples(char t);//四暗刻判定
	int JG_Big_Dragons();		//大三元判定
	int JG_Four_Winds();		//大四喜か小四喜判定
	int JG_All_Honors();		//字一色判定
	int JG_All_Terminals();		//清老頭判定
	int JG_Blessing_of_Earth(MG mg);	//地和判定
	int JG_All_Green();			//緑一色判定
	int JG_Nine_Gates();		//九蓮宝燈判定
	int JG_Four_Quads();		//四槓子判定
	int JG_Blessing_of_Heaven(MG mg);//天和判定
};

int mouseX = 0;
int mouseY = 0;

void DrawBase();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdshow) 
{
	if (DxLib_Init() == -1) {
		return 0;
	}

	ChangeWindowMode(TRUE);
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetDrawScreen(DX_SCREEN_BACK);
	SetMouseDispFlag(TRUE);
	
	MG mg = MG();
	mg.GAME_4();
	
	WaitKey();
	DxLib_End();
	return 0;
}

void DrawBase() {
	array<int, 34>HAIPAI;
	HAIPAI[0] = LoadGraph("pai-images/man1-66-90-l-emb.png");
	HAIPAI[1] = LoadGraph("pai-images/man2-66-90-l-emb.png");
	HAIPAI[2] = LoadGraph("pai-images/man3-66-90-l-emb.png");
	HAIPAI[3] = LoadGraph("pai-images/man4-66-90-l-emb.png");
	HAIPAI[4] = LoadGraph("pai-images/man5-66-90-l-emb.png");
	HAIPAI[5] = LoadGraph("pai-images/man6-66-90-l-emb.png");
	HAIPAI[6] = LoadGraph("pai-images/man7-66-90-l-emb.png");
	HAIPAI[7] = LoadGraph("pai-images/man8-66-90-l-emb.png");
	HAIPAI[8] = LoadGraph("pai-images/man9-66-90-l-emb.png");
	HAIPAI[9] = LoadGraph("pai-images/pin1-66-90-l-emb.png");
	HAIPAI[10] = LoadGraph("pai-images/pin2-66-90-l-emb.png");
	HAIPAI[11] = LoadGraph("pai-images/pin3-66-90-l-emb.png");
	HAIPAI[12] = LoadGraph("pai-images/pin4-66-90-l-emb.png");
	HAIPAI[13] = LoadGraph("pai-images/pin5-66-90-l-emb.png");
	HAIPAI[14] = LoadGraph("pai-images/pin6-66-90-l-emb.png");
	HAIPAI[15] = LoadGraph("pai-images/pin7-66-90-l-emb.png");
	HAIPAI[16] = LoadGraph("pai-images/pin8-66-90-l-emb.png");
	HAIPAI[17] = LoadGraph("pai-images/pin9-66-90-l-emb.png");
	HAIPAI[18] = LoadGraph("pai-images/sou1-66-90-l-emb.png");
	HAIPAI[19] = LoadGraph("pai-images/sou2-66-90-l-emb.png");
	HAIPAI[20] = LoadGraph("pai-images/sou3-66-90-l-emb.png");
	HAIPAI[21] = LoadGraph("pai-images/sou4-66-90-l-emb.png");
	HAIPAI[22] = LoadGraph("pai-images/sou5-66-90-l-emb.png");
	HAIPAI[23] = LoadGraph("pai-images/sou6-66-90-l-emb.png");
	HAIPAI[24] = LoadGraph("pai-images/sou7-66-90-l-emb.png");
	HAIPAI[25] = LoadGraph("pai-images/sou8-66-90-l-emb.png");
	HAIPAI[26] = LoadGraph("pai-images/sou9-66-90-l-emb.png");
	HAIPAI[27] = LoadGraph("pai-images/ji1-66-90-l-emb.png");
	HAIPAI[28] = LoadGraph("pai-images/ji2-66-90-l-emb.png");
	HAIPAI[29] = LoadGraph("pai-images/ji3-66-90-l-emb.png");
	HAIPAI[30] = LoadGraph("pai-images/ji4-66-90-l-emb.png");
	HAIPAI[31] = LoadGraph("pai-images/ji5-66-90-l-emb.png");
	HAIPAI[32] = LoadGraph("pai-images/ji6-66-90-l-emb.png");
	HAIPAI[33] = LoadGraph("pai-images/ji7-66-90-l-emb.png");
	int mainboard = LoadGraph("pai-images/boardmain.png"),
		boardcentermain = LoadGraph("pai-images/boardcentermain.png"),
		boardpoint = LoadGraph("pai-images/boardpoint.png"),
		point = LoadGraph("pai-images/tennbou-001.png");

	DrawExtendGraph(0, 0, 641, 481, mainboard, FALSE);
	DrawExtendGraph(240, 180, 401, 301, boardcentermain, FALSE);
	DrawExtendGraph(275, 275, 366, 296, boardpoint, FALSE);
	DrawExtendGraph(275, 185, 366, 206, boardpoint, FALSE);
	DrawExtendGraph(250, 205, 276, 276, boardpoint, FALSE);
	DrawExtendGraph(365, 205, 391, 276, boardpoint, FALSE);
	{
		array<int, 14> hand = { -1,-1,-1,-1,-1,-1,-1,-1,-1,15,11,11,11 };
		int counthand = 0;
		for (int i = 0;i < 14;i++) {
			if (hand[i] >= 0) {

				if (i != 13) {
					DrawExtendGraph(65 + counthand * 30, 420, 95 + counthand * 30, 470, HAIPAI[hand[i]], FALSE);
				}
				else if (i == 13) {
					DrawExtendGraph(65 + counthand * 30 + 15, 420, 95 + counthand * 30 + 15, 470, HAIPAI[hand[i]], FALSE);
				}
				counthand++;
			}

		}

		array<int, 12> rotated = { 15,16,17,21,22,23,15,15,15,-1,-1,-1 };
		array<int, 4>chi = { 15,22,-1,-1 };
		array<int, 4>pon = { 15,-1,-1,-1 };
		int p = 0;
		int c = 0;
		for (int i = 0;i < 12;i += 3) {
			if (rotated[i] >= 0) {
				int x = 0;
				if (rotated[i] == rotated[i + 1] && rotated[i + 1] == rotated[i + 2] && rotated[i] == pon[p]) {

					pon[p] = -1;
					p++;
					DrawRotaGraph3(480 - i / 3 * 110 + x + 50, 420 + 50 - 1, 0, 90, 1 / 2.2, 5. / 9, -3.14 / 2, HAIPAI[rotated[i]], FALSE);
					x += 50;
					DrawExtendGraph(480 - i / 3 * 110 + x, 420, 480 - i / 3 * 110 + x + 30, 470, HAIPAI[rotated[i + 1]], FALSE);
					x += 30;
					DrawExtendGraph(480 - i / 3 * 110 + x, 420, 480 - i / 3 * 110 + x + 30, 470, HAIPAI[rotated[i + 2]], FALSE);
					x += 30;
					break;

				}
				for (int j = 0;j < 3;j++) {

					if (rotated[i + j] == chi[c]) {
						chi[c] = -1;
						c++;
						DrawRotaGraph3(480 - i / 3 * 110 + x + 50, 420 + 50 - 1, 0, 90, 1 / 2.2, 5. / 9, -3.14 / 2, HAIPAI[rotated[i + j]], FALSE);
						x += 50;
					}
					else {
						DrawExtendGraph(480 - i / 3 * 110 + x, 420, 480 - i / 3 * 110 + x + 30, 470, HAIPAI[rotated[i + j]], FALSE);
						x += 30;
					}
				}
			}
		}
		int reach = 15;
		array<int, 30> discard;
		discard.fill(1);
		for (int i = 0;i < 4;i++) {
			int x = 0;

			for (int j = 0;j < 6;j++) {
				if (discard[i * 6 + j] >= 0) {
					if (reach == i * 6 + j) {
						DrawRotaGraph3(250 + j * 22 + 27, 305 + i * 27 + 27, 0, 90, 22. / 66, 27. / 90, -3.14 / 2, HAIPAI[discard[i * 6 + j]], FALSE);
						x++;
					}
					else {
						DrawExtendGraph(250 + j * 22 + x * 5, 305 + i * 27, 272 + j * 22 + x * 5, 332 + i * 27, HAIPAI[discard[i * 6 + j]], FALSE);
					}
				}
			}
		}
		if (reach >= 0)DrawRotaGraph3(293, 270, 0, 0, 0.5, 0.5, -3.1415 / 2, point, FALSE);
		if (reach >= 0)DrawRotaGraph3(353, 217, 0, 0, 0.5, 0.4, 0, point, FALSE);
		if (reach >= 0)DrawRotaGraph3(293, 215, 0, 0, 0.5, 0.5, -3.1415 / 2, point, FALSE);
		if (reach >= 0)DrawRotaGraph3(285, 217, 0, 0, 0.5, 0.4, 0, point, FALSE);
		int plpoint = 25000;


		DrawRotaFormatString(295, 277, 1.2, 1.2, 0, 0, 0, -256, 0U, 0, "%d", plpoint);
		DrawRotaFormatString(368, 268, 1.2, 1.2, 0, 0, -3.1415 / 2, -256, 0U, 0, "%d", plpoint);
		DrawRotaFormatString(350, 205, 1.2, 1.2, 0, 0, 3.1415, -256, 0U, 0, "%d", plpoint);
		DrawRotaFormatString(270, 215, 1.2, 1.2, 0, 0, 3.1415 / 2, -256, 0U, 0, "%d", plpoint);



		rotated.fill(-1);
		rotated = { 15,16,17,21,22,23,15,15,15,-1,-1,-1 };
		chi = { 15,22,-1,-1 };
		pon = { 15,-1,-1,-1 };
		p = 0;
		c = 0;
		int h = 150 / 4,
			w = 96 / 4,
			wwh = w + w + h;

		for (int i = 0;i < 12;i += 3) {
			if (rotated[i] >= 0) {
				int x = 0;
				if (rotated[i] == rotated[i + 1] && rotated[i + 1] == rotated[i + 2] && rotated[i] == pon[p]) {

					pon[p] = -1;
					p++;
					DrawRotaGraph3(630, wwh + i / 3 * wwh - x + 35, 0, 0, 1. * w / 66, 1. * h / 90, 3.14, HAIPAI[rotated[i]], FALSE);
					x += h;
					DrawRotaGraph3(630 - h, wwh + i / 3 * wwh - x + 35, 0, 0, 1. * w / 66, 1. * h / 90, -3.14 / 2, HAIPAI[rotated[i]], FALSE);
					x += w;
					DrawRotaGraph3(630 - h, wwh + i / 3 * wwh - x + 35, 0, 0, 1. * w / 66, 1. * h / 90, -3.14 / 2, HAIPAI[rotated[i]], FALSE);
					x += w;
					break;

				}
				for (int j = 0;j < 3;j++) {

					if (rotated[i + j] == chi[c]) {
						chi[c] = -1;
						c++;
						DrawRotaGraph3(630, wwh + i / 3 * wwh - x + 35, 0, 0, 1. * w / 66, 1. * h / 90, 3.14, HAIPAI[rotated[i + j]], FALSE);
						x += h;
					}
					else {
						DrawRotaGraph3(630 - h, wwh + i / 3 * wwh - x + 35, 0, 0, 1. * w / 66, 1. * h / 90, -3.14 / 2, HAIPAI[rotated[i + j]], FALSE);
						x += w;
					}
				}
			}
		}
		h = 27;
		w = 22;
		for (int i = 0;i < 4;i++) {
			int x = 0;
			for (int j = 0;j < 6;j++) {
				if (discard[i * 6 + j] >= 0) {
					if (reach == i * 7 + j) {
						DrawRotaGraph3(405 + (i + 1) * h, -j * w + 300, 0, 0, 1. * h / 90, 1. * w / 66, 3.14, HAIPAI[discard[i * 6 + j]], FALSE);
						x++;
					}
					else {
						DrawRotaGraph3(405 + (i)*h - 1, -j * w + 300 - x * (h - w), 0, 0, 1. * w / 66, 1. * h / 90, -3.14 / 2, HAIPAI[discard[i * 6 + j]], FALSE);
					}
				}
			}
		}
		rotated.fill(-1);
		rotated = { 15,16,17,21,22,23,15,15,15,-1,-1,-1 };
		chi = { 15,22,-1,-1 };
		pon = { 15,-1,-1,-1 };
		p = 0;
		c = 0;
		h = 150 / 4;
		w = 96 / 4;
		wwh = w + w + h;

		for (int i = 0;i < 12;i += 3) {
			if (rotated[i] >= 0) {
				int x = 0;
				if (rotated[i] == rotated[i + 1] && rotated[i + 1] == rotated[i + 2] && rotated[i] == pon[p]) {

					pon[p] = -1;
					p++;
					DrawRotaGraph3(35 + wwh + i / 3 * wwh - x, 10, 0, 0, 1. * w / 66, 1. * h / 90, 3.14 / 2, HAIPAI[rotated[i]], FALSE);
					x += h;
					DrawRotaGraph3(35 + wwh + i / 3 * wwh - x, h + 10, 0, 0, 1. * w / 66, 1. * h / 90, 3.14, HAIPAI[rotated[i]], FALSE);
					x += w;
					DrawRotaGraph3(35 + wwh + i / 3 * wwh - x, h + 10, 0, 0, 1. * w / 66, 1. * h / 90, 3.14, HAIPAI[rotated[i]], FALSE);
					x += w;
					break;

				}
				for (int j = 0;j < 3;j++) {

					if (rotated[i + j] == chi[c]) {
						chi[c] = -1;
						c++;
						DrawRotaGraph3(35 + wwh + i / 3 * wwh - x, 10, 0, 0, 1. * w / 66, 1. * h / 90, 3.14 / 2, HAIPAI[rotated[i]], FALSE);
						x += h;
					}
					else {
						DrawRotaGraph3(35 + wwh + i / 3 * wwh - x, h + 10, 0, 0, 1. * w / 66, 1. * h / 90, 3.14, HAIPAI[rotated[i]], FALSE);
						x += w;
					}
				}
			}
		}
		h = 27;
		w = 22;
		for (int i = 0;i < 4;i++) {
			int x = 0;
			for (int j = 0;j < 6;j++) {
				if (discard[i * 6 + j] >= 0) {
					if (reach == i * 7 + j) {
						DrawRotaGraph3(400 - j * w, 180 - (i + 1) * h, 0, 0, 1. * w / 66, 1. * h / 90, 3.14 / 2, HAIPAI[discard[i * 6 + j]], FALSE);
						x++;
					}
					else {
						DrawRotaGraph3(400 - j * w - x * (h - w), 180 - i * h, 0, 0, 1. * w / 66, 1. * h / 90, 3.14, HAIPAI[discard[i * 6 + j]], FALSE);
					}
				}
			}
		}


		rotated.fill(-1);
		rotated = { 15,16,17,21,22,23,15,15,15,-1,-1,-1 };
		chi = { 15,22,-1,-1 };
		pon = { 15,-1,-1,-1 };
		p = 0;
		c = 0;
		h = 150 / 4;
		w = 96 / 4;
		wwh = w + w + h;

		for (int i = 0;i < 12;i += 3) {
			if (rotated[i] >= 0) {
				int x = 0;
				if (rotated[i] == rotated[i + 1] && rotated[i + 1] == rotated[i + 2] && rotated[i] == pon[p]) {

					pon[p] = -1;
					p++;
					DrawRotaGraph3(10, 440 - wwh - i / 3 * wwh + x, 0, 0, 1. * w / 66, 1. * h / 90, 0, HAIPAI[rotated[i]], FALSE);
					x += h;
					DrawRotaGraph3(10 + h, 440 - wwh - i / 3 * wwh + x, 0, 0, 1. * w / 66, 1. * h / 90, 3.14 / 2, HAIPAI[rotated[i]], FALSE);
					x += w;
					DrawRotaGraph3(10 + h, 440 - wwh - i / 3 * wwh + x, 0, 0, 1. * w / 66, 1. * h / 90, 3.14 / 2, HAIPAI[rotated[i]], FALSE);
					x += w;
					break;

				}
				for (int j = 0;j < 3;j++) {

					if (rotated[i + j] == chi[c]) {
						chi[c] = -1;
						c++;
						DrawRotaGraph3(10, 440 - wwh - i / 3 * wwh + x, 0, 0, 1. * w / 66, 1. * h / 90, 0, HAIPAI[rotated[i]], FALSE);
						x += h;
					}
					else {
						DrawRotaGraph3(10 + h, 440 - wwh - i / 3 * wwh + x, 0, 0, 1. * w / 66, 1. * h / 90, 3.14 / 2, HAIPAI[rotated[i]], FALSE);
						x += w;
					}
				}
			}
		}
		h = 27;
		w = 22;
		for (int i = 0;i < 4;i++) {
			int x = 0;
			for (int j = 0;j < 6;j++) {
				if (discard[i * 6 + j] >= 0) {
					if (reach == i * 7 + j) {
						DrawRotaGraph3(240 - (i + 1) * h, 180 + j * w, 0, 0, 1. * w / 66, 1. * h / 90, 0, HAIPAI[discard[i * 6 + j]], FALSE);
						x++;
					}
					else {
						DrawRotaGraph3(240 - i * h, 180 + j * w + x * (h - w), 0, 0, 1. * w / 66, 1. * h / 90, 3.14 / 2, HAIPAI[discard[i * 6 + j]], FALSE);
					}
				}
			}
		}





	}
	ScreenFlip();

}


MG::mohjong_game() {

	srand((unsigned int)time(NULL));	//乱数用の種を時間で所得
	HAIPAI.fill(0);
	HAIPAI[0] = LoadGraph("pai-images/man1-66-90-l-emb.png");
	HAIPAI[1] = LoadGraph("pai-images/man2-66-90-l-emb.png");
	HAIPAI[2] = LoadGraph("pai-images/man3-66-90-l-emb.png");
	HAIPAI[3] = LoadGraph("pai-images/man4-66-90-l-emb.png");
	HAIPAI[4] = LoadGraph("pai-images/man5-66-90-l-emb.png");
	HAIPAI[5] = LoadGraph("pai-images/man6-66-90-l-emb.png");
	HAIPAI[6] = LoadGraph("pai-images/man7-66-90-l-emb.png");
	HAIPAI[7] = LoadGraph("pai-images/man8-66-90-l-emb.png");
	HAIPAI[8] = LoadGraph("pai-images/man9-66-90-l-emb.png");
	HAIPAI[9] = LoadGraph("pai-images/pin1-66-90-l-emb.png");
	HAIPAI[10] = LoadGraph("pai-images/pin2-66-90-l-emb.png");
	HAIPAI[11] = LoadGraph("pai-images/pin3-66-90-l-emb.png");
	HAIPAI[12] = LoadGraph("pai-images/pin4-66-90-l-emb.png");
	HAIPAI[13] = LoadGraph("pai-images/pin5-66-90-l-emb.png");
	HAIPAI[14] = LoadGraph("pai-images/pin6-66-90-l-emb.png");
	HAIPAI[15] = LoadGraph("pai-images/pin7-66-90-l-emb.png");
	HAIPAI[16] = LoadGraph("pai-images/pin8-66-90-l-emb.png");
	HAIPAI[17] = LoadGraph("pai-images/pin9-66-90-l-emb.png");
	HAIPAI[18] = LoadGraph("pai-images/sou1-66-90-l-emb.png");
	HAIPAI[19] = LoadGraph("pai-images/sou2-66-90-l-emb.png");
	HAIPAI[20] = LoadGraph("pai-images/sou3-66-90-l-emb.png");
	HAIPAI[21] = LoadGraph("pai-images/sou4-66-90-l-emb.png");
	HAIPAI[22] = LoadGraph("pai-images/sou5-66-90-l-emb.png");
	HAIPAI[23] = LoadGraph("pai-images/sou6-66-90-l-emb.png");
	HAIPAI[24] = LoadGraph("pai-images/sou7-66-90-l-emb.png");
	HAIPAI[25] = LoadGraph("pai-images/sou8-66-90-l-emb.png");
	HAIPAI[26] = LoadGraph("pai-images/sou9-66-90-l-emb.png");
	HAIPAI[27] = LoadGraph("pai-images/ji1-66-90-l-emb.png");
	HAIPAI[28] = LoadGraph("pai-images/ji2-66-90-l-emb.png");
	HAIPAI[29] = LoadGraph("pai-images/ji3-66-90-l-emb.png");
	HAIPAI[30] = LoadGraph("pai-images/ji4-66-90-l-emb.png");
	HAIPAI[31] = LoadGraph("pai-images/ji5-66-90-l-emb.png");
	HAIPAI[32] = LoadGraph("pai-images/ji6-66-90-l-emb.png");
	HAIPAI[33] = LoadGraph("pai-images/ji7-66-90-l-emb.png");
	mainboard = LoadGraph("pai-images/boardmain.png");
	boardcentermain = LoadGraph("pai-images/boardcentermain.png");
	boardpoint = LoadGraph("pai-images/boardpoint.png");
	point = LoadGraph("pai-images/tennbou-001.png");
	for (int i = 0;i < 34;i++)HAIYAMA[i] = 4;
	Wind = 0;
	Turn = 1;

	/*
	cout << "三麻 or 四麻 ?(please push 3 or 4)" << endl;
	int gamemode = 0;
	cin >> gamemode;
	while (gamemode != 3 && gamemode != 4) {
		cout << "please again !" << endl << "三麻 or 四麻 ?(please push 3 or 4)" << endl;
		cin >> gamemode;
	}
	if (gamemode == 3)GAME_3();
	else if (gamemode == 4)GAME_4();
	else cout << "error!" << endl;
	*/

}

int MG::GAME_3() { return 0; }
int MG::GAME_4() {

	player player[4] = { {0,this},{1,this},{2,this},{3,this} };
	for (int i = 0;i < 4;i++)player[i].set_point(25000);
	
	for (int i = 0, l = 0;i < 4;i++) {

		int gameend = 0;
		do {
			for (int j = 0;j < 4;j++) {
				Turn++;

				player[j].draw(draw());

				display(player,j);
				if (player[j].JG_claim(*this)) {

					char c='0';
					do {
						display(player,j);
						DrawString(0, 0, "TUMO?(y/n)", -25);
						ScreenFlip();
						WaitKey();
						//cout << "TUMO?(y/n)" << endl;
						//cin >> c;
						if (CheckHitKey(KEY_INPUT_Y))c = 'y';
						if (CheckHitKey(KEY_INPUT_N))c = 'n';
					} while (c != 'n' && c != 'N' && c != 'y' && c != 'Y');

					if (c == 'y' || c == 'Y') {

						gameend = 1;
						int p = player[j].calculation_point(l, *this);
						player[j].add_point(p);
						for (int k = 0;k < 4;k++) {
							if (k != j) {
								if (player[k].show_my_wind() == 0)player[k].add_point(p / 2);
								else player[k].add_point(p / 4);
							}
						}

						if (player[j].show_my_wind() == i) {

							i--;
							l++;
						}

					}
				}
				display(player,j);
				int d = player[j].discard(j);
				display(player, j);
				DrawString(0, 0, "/////////////////////////////////////////////////////////////////////\n////////////////////////////////////////////////////////////", -25);
				ScreenFlip();
				WaitKey();
				if (player[j].JG_tenpai(*this, d)) {

					char r='0';
					
					do {
						if (player[j].show_reach() < 0) {
							if (j != 0)r = 'y';
							display(player,j);
							DrawString(0, 0, "reach?(y/n)", -25);
							ScreenFlip();
							WaitKey();
							//cout << "reach?(y/n)" << endl;
							//cin >> r;
							if (CheckHitKey(KEY_INPUT_Y))r = 'y';
							if (CheckHitKey(KEY_INPUT_N))r = 'n';

						}

					} while (r != 'n' && r != 'N' && r != 'y' && r != 'Y');

					if (r == 'y' || r == 'Y') {

						player[j].set_reach(Turn);
					}

				}
				if (gameend)break;
				display(player, j);
				DrawString(0, 0, "000000000000000000000000000000000000000000000000000", -125);
				ScreenFlip();
				WaitKey();

				display(player,j);
				for (int k = 0;k < 4;k++) {
					int x = k + j;
					if (x > 3)x = j + k - 4;
					if (j != j + k) {

						if (player[x].JG_ron(*this, d)) {
							
							char r='0';
							if (j != 0)r = 'y';
							do {
								display(player,j);
								DrawString(0, 0, "reach?(y/n)", -20);
								ScreenFlip();
								WaitKey();
								//cout << "RON?(y/n)" << endl;
								//cin >> r;
								if (CheckHitKey(KEY_INPUT_Y))r = 'y';
								if (CheckHitKey(KEY_INPUT_N))r = 'n';

							} while (r != 'n' && r != 'N' && r != 'y' && r != 'Y');

							if (r == 'y' || r == 'Y') {
								int p = player[x].calculation_point(l, player[j], *this);
								player[x].add_point(p);
								player[j].add_point(-p);
								gameend = 1;

								if (player[x].show_my_wind() == i) {

									i--;
									l++;
								}
								if (gameend)break;
							}
						}
					}
					if (gameend)break;
				}
				display(player,j);
				if (gameend)break;
			}
			if (gameend)break;
			int u = 1;
			int s = 0;
			for (int h = 0;h < 34;h++) {
				if (HAIYAMA[h] != 0) {
					DrawFormatString(560, h * 15, 0, " %d : %d\n", h, HAIYAMA[h]);
					
					s += HAIYAMA[h];

					u = 0;
				}
			}
			DrawFormatString(400, 10, -125, " 残り山牌数＝%d \n", s);
			ScreenFlip();
			WaitKey();
			gameend = u;
		} while (!gameend);
		for (int j = 0;j < 4;j++) {
			if (player[j].add_point(0))break;
		}
	}
	
	return 0;
}

int MG::draw() {
	while (1) {
		int draw = rand() % 34;
		if (HAIYAMA[draw] > 0) {
			HAIYAMA[draw]--;
			return draw;
		}
	}

}

int MG::display(player* P,int t) {
	DrawExtendGraph(0, 0, 641, 481, mainboard, FALSE);
	DrawExtendGraph(240, 180, 401, 301, boardcentermain, FALSE);
	DrawExtendGraph(275, 275, 366, 296, boardpoint, FALSE);
	DrawExtendGraph(275, 185, 366, 206, boardpoint, FALSE);
	DrawExtendGraph(250, 205, 276, 276, boardpoint, FALSE);
	DrawExtendGraph(365, 205, 391, 276, boardpoint, FALSE);
	{
		DrawRotaFormatString(295, 277, 1.2, 1.2, 0, 0, 0, -256, 0U, 0, "%d", P[0].add_point(0));
		DrawRotaFormatString(368, 268, 1.2, 1.2, 0, 0, -3.1415 / 2, -256, 0U, 0, "%d", P[1].add_point(0));
		DrawRotaFormatString(350, 205, 1.2, 1.2, 0, 0, 3.1415, -256, 0U, 0, "%d", P[2].add_point(0));
		DrawRotaFormatString(270, 215, 1.2, 1.2, 0, 0, 3.1415 / 2, -256, 0U, 0, "%d", P[3].add_point(0));
		array<int, 14> hand = P[0].show_hand();
		int counthand = 0;
		for (int i = 0;i < 14;i++) {
			if (hand[i] >= 0) {

				if (i != 13) {
					DrawExtendGraph(65 + i * 30, 420, 95 + i * 30, 470, HAIPAI[hand[i]], FALSE);
					P[0].handpreend = 95 + i * 30;
				}
				else if (i == 13&&t==0) {
					DrawExtendGraph(65 + i * 30 + 30, 420, 95 + i * 30 + 30, 470, HAIPAI[hand[i]], FALSE);
					P[0].handendx = 95 + i * 30 + 30;
				}
				counthand++;
			}

		}
		array<int, 12> rotated;
		rotated.fill(-1);
		rotated = P[0].show_rotated();
		array<int, 4>chi = P[0].show_chi();
		array<int, 4>pon = P[0].show_pon();
		int p = 0;
		int c = 0;

		for (int i = 0;i < 12;i += 3) {
			if (rotated[i] >= 0) {
				int x = 0;
				if (rotated[i] == rotated[i + 1] && rotated[i + 1] == rotated[i + 2] && rotated[i] == pon[p]) {

					pon[p] = -1;
					p++;
					DrawRotaGraph3(480 - i / 3 * 110 + x + 50, 420 + 50 - 1, 0, 90, 1 / 2.2, 5. / 9, -3.14 / 2, HAIPAI[rotated[i]], FALSE);
					x += 50;
					DrawExtendGraph(480 - i / 3 * 110 + x, 420, 480 - i / 3 * 110 + x + 30, 470, HAIPAI[rotated[i + 1]], FALSE);
					x += 30;
					DrawExtendGraph(480 - i / 3 * 110 + x, 420, 480 - i / 3 * 110 + x + 30, 470, HAIPAI[rotated[i + 2]], FALSE);
					x += 30;
					break;

				}
				for (int j = 0;j < 3;j++) {

					if (rotated[i + j] == chi[c]) {
						chi[c] = -1;
						c++;
						DrawRotaGraph3(480 - i / 3 * 110 + x + 50, 420 + 50 - 1, 0, 90, 1 / 2.2, 5. / 9, -3.14 / 2, HAIPAI[rotated[i + j]], FALSE);
						x += 50;
					}
					else {
						DrawExtendGraph(480 - i / 3 * 110 + x, 420, 480 - i / 3 * 110 + x + 30, 470, HAIPAI[rotated[i + j]], FALSE);
						x += 30;
					}
				}
			}
			else
				break;
		}
		int reach = P[0].show_reach();
		if (reach >= 0)DrawRotaGraph3(290, 270, 0, 0, 0.5, 0.5, -3.1415 / 2, point, FALSE);
		array<int, 30> discard;
		discard.fill(-1);
		discard = P[0].show_discards();
		for (int i = 0;i < 4;i++) {
			int x = 0;
			for (int j = 0;j < 6;j++) {
				if (discard[i * 6 + j] >= 0) {
					if (reach == i * 6 + j) {
						DrawRotaGraph3(250 + j * 22 + 27, 305 + i * 27 + 27, 0, 90, 22. / 66, 27. / 90, -3.14 / 2, HAIPAI[discard[i * 6 + j]], FALSE);
						x++;
					}
					else {
						DrawExtendGraph(250 + j * 22 + x * 5, 305 + i * 27, 272 + j * 22 + x * 5, 332 + i * 27, HAIPAI[discard[i * 6 + j]], FALSE);
					}
				}
			}
		}







		hand = P[1].show_hand();
		counthand = 0;
		/*
		for (int i = 0;i < 14;i++) {
			if (hand[i] >= 0) {

				if (i != 13) {
					DrawExtendGraph(30 + i * 30, 420, 60 + i * 30, 470, HAIPAI[hand[i]], FALSE);
				}
				else if (i == 13) {
					DrawExtendGraph(30 + i * 30 + 30, 420, 60 + i * 30 + 30, 470, HAIPAI[hand[i]], FALSE);
				}
				counthand++;
			}

		}
		*/

		rotated.fill(-1);
		rotated = P[1].show_rotated();
		chi = P[1].show_chi();
		pon = P[1].show_pon();
		p = 0;
		c = 0;
		int h = 150 / 4,
			w = 96 / 4,
			wwh = w + w + h;

		for (int i = 0;i < 12;i += 3) {
			if (rotated[i] >= 0) {
				int x = 0;
				if (rotated[i] == rotated[i + 1] && rotated[i + 1] == rotated[i + 2] && rotated[i] == pon[p]) {

					pon[p] = -1;
					p++;
					DrawRotaGraph3(630, wwh + i / 3 * wwh - x + 35, 0, 0, 1. * w / 66, 1. * h / 90, 3.14, HAIPAI[rotated[i]], FALSE);
					x += h;
					DrawRotaGraph3(630 - h, wwh + i / 3 * wwh - x + 35, 0, 0, 1. * w / 66, 1. * h / 90, -3.14 / 2, HAIPAI[rotated[i]], FALSE);
					x += w;
					DrawRotaGraph3(630 - h, wwh + i / 3 * wwh - x + 35, 0, 0, 1. * w / 66, 1. * h / 90, -3.14 / 2, HAIPAI[rotated[i]], FALSE);
					x += w;
					break;

				}
				for (int j = 0;j < 3;j++) {

					if (rotated[i + j] == chi[c]) {
						chi[c] = -1;
						c++;
						DrawRotaGraph3(630, wwh + i / 3 * wwh - x + 35, 0, 0, 1. * w / 66, 1. * h / 90, 3.14, HAIPAI[rotated[i + j]], FALSE);
						x += h;
					}
					else {
						DrawRotaGraph3(630 - h, wwh + i / 3 * wwh - x + 35, 0, 0, 1. * w / 66, 1. * h / 90, -3.14 / 2, HAIPAI[rotated[i + j]], FALSE);
						x += w;
					}
				}
			}
			else
				break;
		}
		reach = P[1].show_reach();
		if (reach >= 0)DrawRotaGraph3(353, 217, 0, 0, 0.5, 0.4, 0, point, FALSE);
		discard.fill(-1);
		discard = P[1].show_discards();
		h = 27;
		w = 19;
		for (int i = 0;i < 4;i++) {
			int x = 0;
			for (int j = 0;j < 6;j++) {
				if (discard[i * 6 + j] >= 0) {
					if (reach == i * 7 + j) {
						DrawRotaGraph3(405 + (i + 1) * h, -j * w + 300, 0, 0, 1. * h / 90, 1. * w / 66, 3.14, HAIPAI[discard[i * 6 + j]], FALSE);
						x++;
					}
					else {
						DrawRotaGraph3(405 + (i)*h - 1, -j * w + 300 - x * (h - w), 0, 0, 1. * w / 66, 1. * h / 90, -3.14 / 2, HAIPAI[discard[i * 6 + j]], FALSE);
					}
				}
			}
		}
		rotated.fill(-1);
		rotated = P[2].show_rotated();
		chi = P[2].show_chi();
		pon = P[2].show_pon();
		p = 0;
		c = 0;
		h = 150 / 4;
		w = 96 / 4;
		wwh = w + w + h;

		for (int i = 0;i < 12;i += 3) {
			if (rotated[i] >= 0) {
				int x = 0;
				if (rotated[i] == rotated[i + 1] && rotated[i + 1] == rotated[i + 2] && rotated[i] == pon[p]) {

					pon[p] = -1;
					p++;
					DrawRotaGraph3(35 + wwh + i / 3 * wwh - x, 10, 0, 0, 1. * w / 66, 1. * h / 90, 3.14 / 2, HAIPAI[rotated[i]], FALSE);
					x += h;
					DrawRotaGraph3(35 + wwh + i / 3 * wwh - x, h + 10, 0, 0, 1. * w / 66, 1. * h / 90, 3.14, HAIPAI[rotated[i]], FALSE);
					x += w;
					DrawRotaGraph3(35 + wwh + i / 3 * wwh - x, h + 10, 0, 0, 1. * w / 66, 1. * h / 90, 3.14, HAIPAI[rotated[i]], FALSE);
					x += w;
					break;

				}
				for (int j = 0;j < 3;j++) {

					if (rotated[i + j] == chi[c]) {
						chi[c] = -1;
						c++;
						DrawRotaGraph3(35 + wwh + i / 3 * wwh - x, 10, 0, 0, 1. * w / 66, 1. * h / 90, 3.14 / 2, HAIPAI[rotated[i]], FALSE);
						x += h;
					}
					else {
						DrawRotaGraph3(35 + wwh + i / 3 * wwh - x, h + 10, 0, 0, 1. * w / 66, 1. * h / 90, 3.14, HAIPAI[rotated[i]], FALSE);
						x += w;
					}
				}
			}
		}
		reach = P[2].show_reach();
		if (reach >= 0)DrawRotaGraph3(293, 215, 0, 0, 0.5, 0.5, -3.1415 / 2, point, FALSE);
		discard.fill(-1);
		discard = P[2].show_discards();
		h = 27;
		w = 22;
		for (int i = 0;i < 4;i++) {
			int x = 0;
			for (int j = 0;j < 6;j++) {
				if (discard[i * 6 + j] >= 0) {
					if (reach == i * 7 + j) {
						DrawRotaGraph3(400 - j * w, 180 - (i + 1) * h, 0, 0, 1. * w / 66, 1. * h / 90, 3.14 / 2, HAIPAI[discard[i * 6 + j]], FALSE);
						x++;
					}
					else {
						DrawRotaGraph3(400 - j * w - x * (h - w), 180 - i * h, 0, 0, 1. * w / 66, 1. * h / 90, 3.14, HAIPAI[discard[i * 6 + j]], FALSE);
					}
				}
			}
		}

		rotated.fill(-1);
		rotated = P[3].show_rotated();
		chi = P[3].show_chi();
		pon = P[3].show_pon();
		p = 0;
		c = 0;
		h = 150 / 4;
		w = 96 / 4;
		wwh = w + w + h;

		for (int i = 0;i < 12;i += 3) {
			if (rotated[i] >= 0) {
				int x = 0;
				if (rotated[i] == rotated[i + 1] && rotated[i + 1] == rotated[i + 2] && rotated[i] == pon[p]) {

					pon[p] = -1;
					p++;
					DrawRotaGraph3(10, 440 - wwh - i / 3 * wwh + x, 0, 0, 1. * w / 66, 1. * h / 90, 0, HAIPAI[rotated[i]], FALSE);
					x += h;
					DrawRotaGraph3(10 + h, 440 - wwh - i / 3 * wwh + x, 0, 0, 1. * w / 66, 1. * h / 90, 3.14 / 2, HAIPAI[rotated[i]], FALSE);
					x += w;
					DrawRotaGraph3(10 + h, 440 - wwh - i / 3 * wwh + x, 0, 0, 1. * w / 66, 1. * h / 90, 3.14 / 2, HAIPAI[rotated[i]], FALSE);
					x += w;
					break;

				}
				for (int j = 0;j < 3;j++) {

					if (rotated[i + j] == chi[c]) {
						chi[c] = -1;
						c++;
						DrawRotaGraph3(10, 440 - wwh - i / 3 * wwh + x, 0, 0, 1. * w / 66, 1. * h / 90, 0, HAIPAI[rotated[i]], FALSE);
						x += h;
					}
					else {
						DrawRotaGraph3(10 + h, 440 - wwh - i / 3 * wwh + x, 0, 0, 1. * w / 66, 1. * h / 90, 3.14 / 2, HAIPAI[rotated[i]], FALSE);
						x += w;
					}
				}
			}
		}
		reach = P[3].show_reach();
		if (reach >= 0)DrawRotaGraph3(285, 217, 0, 0, 0.5, 0.4, 0, point, FALSE);
		discard.fill(-1);
		discard = P[3].show_discards();
		h = 27;
		w = 22;
		for (int i = 0;i < 4;i++) {
			int x = 0;
			for (int j = 0;j < 6;j++) {
				if (discard[i * 6 + j] >= 0) {
					if (reach == i * 7 + j) {
						DrawRotaGraph3(240 - (i + 1) * h, 180 + j * w, 0, 0, 1. * w / 66, 1. * h / 90, 0, HAIPAI[discard[i * 6 + j]], FALSE);
						x++;
					}
					else {
						DrawRotaGraph3(240 - i * h, 180 + j * w + x * (h - w), 0, 0, 1. * w / 66, 1. * h / 90, 3.14 / 2, HAIPAI[discard[i * 6 + j]], FALSE);
					}
				}
			}
		}
	}
	ScreenFlip();
	return 0;
}


player::player(int n, MG* mg) {
	my_wind = n;
	reach = -1;
	point = 25000;
	for (int i = 0;i < 13;i++)Hand[i] = mg[0].draw();
	Hand[13] = -1;
	for (int i = 0;i < 12;i++)rotated[i] = 0;
	rotated.fill(-1);
	discards.fill(-1);
	handlist.fill(0);
	chi.fill(-1);
	pon.fill(-1);
}

int player::discard(int t) {
	int d = -1, y = 0;
	//for (int i = 0;i < 14;i++)cout << "\t" << Hand[i];
	if (t == 0) {
		if (reach > 0)d = Hand[13];
		else {
			do {

				DrawString(30, 0, "What do you discard?:", 0);
				ScreenFlip();
				WaitKey();
				//cout << endl << "What do you discard?:";
				//cin >> d;
				GetMousePoint(&mouseX, &mouseY);
				if (mouseY >= 420 && mouseX >= 65 && mouseX <= handendx) {
					for (int i = 0;i * 30 + 65 < handpreend;i++) {
						if (mouseX >= i * 30 + 65 && mouseX < i * 30 + 95)d = Hand[i];
					}
					if (mouseX >= handendx - 30 && mouseX < handendx)d = Hand[13];
				}
				for (int i = 0;i < 14;i++) {
					if (Hand[i] == d)y = 1;
				}

				//cout << "error: This number is nothing in your hand!!PLEASE AGAIN!!" << endl;

			} while (!y);
		}
	}
	else
		d = Hand[rand() % 14];
	
	DrawFormatString(30, 0, 0,"What do you discard?: %d ", d);
	ScreenFlip();
	WaitKey();
	if (Hand[13] == d) {
		for (int j = 0;j < 30;j++) {
			if (discards[j] < 0) {
				discards[j] = Hand[13];
				break;
			}
		}
		return d;
	}
	for (int i = 12;i >= 0;i--) {
		if (Hand[i] == d) {
			
			for (int j = 0;j < 30;j++) {
				if (discards[j] < 0) {
					discards[j] = Hand[i];
					break;
				}
			}
			Hand[i] = Hand[13];
			handsort(13);
			return d;
		}
	}
	//cout << "ERROR" << endl;
	return -1;
}

void player::handsort(int n) {
	for (int i = 1;i < n;i++) {

		int j;
		int t = Hand[i];
		for (j = i;j > 0 && Hand[j - 1] > t;j--) {
			Hand[j] = Hand[j - 1];
			Hand[j - 1] = t;
		}
	}
}


int player::JG_chows() {
	int LIST[34];
	for (int i = 0;i < 34;i++)LIST[i] = handlist[i];

	for (int i = 0;i < 7;i++) {
		if (LIST[i] >= 1 && LIST[i + 1] >= 1 && LIST[i + 2] >= 1) {
			LIST[i]--;
			LIST[i + 1]--;
			LIST[i + 2]--;
			continue;
		}
	}
	for (int i = 9;i < 16;i++) {
		if (LIST[i] >= 1 && LIST[i + 1] >= 1 && LIST[i + 2] >= 1) {
			LIST[i]--;
			LIST[i + 1]--;
			LIST[i + 2]--;
			continue;
		}
	}
	for (int i = 18;i < 25;i++) {
		if (LIST[i] >= 1 && LIST[i + 1] >= 1 && LIST[i + 2] >= 1) {
			LIST[i]--;
			LIST[i + 1]--;
			LIST[i + 2]--;
			continue;
		}
	}
	int b = 1;
	for (int i = 0;i < 34;i++)
	{
		if (LIST[i] != 0)b = 0;
	}
	return b;
}

int player::JG_pungs(int p) {		//刻子を探し一つずつ取り除く、そのたびにcount_shows関数を実行する。pは再起用

	for (int i = p;i < 34;i++) {

		if (handlist[i] >= 3) {
			handlist[i] -= 3;
			if (JG_chows())return 1;
			JG_pungs(i + 1);
			handlist[i] += 3;
		}
	}
	return 0;

}

int player::JG_claim(MG mg) {
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 34;i++) {
		if (handlist[i] >= 2) {
			handlist[i] -= 2;
			if (JG_chows())return 1;
			if (JG_pungs(0))return 1;
			for (int j = 0;j < 34;j++)handlist[j] = 0;
			for (int j = 0;j < 14;j++)handlist[Hand[j]]++;
		}
	}
	if (JG_KOKUSI())return 1;
	if (JG_7Pairs())return 1;

	return 0;

}

int player::JG_tenpai(MG mg, int d) {		//dは捨て牌
	for (int k = 0;k < 34;k++) {
		Hand[13] = k;
		if (JG_claim(mg)) {
			Hand[13]--;
			return 1;
		}
	}
	return 0;
}

int player::JG_ron(MG mg, int r) {
	Hand[13] = r;
	if (JG_claim(mg))return 1;
	return 0;
}

int player::calculation_point(int L, MG mg) {				//点数計算ツモver
	int p = 0;
	p += JG_Blessing_of_Heaven(mg);
	p += JG_Blessing_of_Earth(mg);
	p += JG_KOKUSI();
	p += JG_Four_Concealed_Triples('t');
	p += JG_Big_Dragons();
	p += JG_Four_Winds();
	p += JG_All_Honors();
	p += JG_All_Terminals();
	p += JG_All_Green();
	p += JG_Nine_Gates();
	p += JG_Four_Quads();
	if (p > 0) {
		int i = p / 13;
		if (my_wind == 0) return 48000 * i;
		else return 36000 * i;
	}
	p += JG_Reach();
	p += JG_Double_Reach();
	p += JG_First_Turn(mg, 't');
	p += JG_Self_Draw();
	p += JG_Final_TileT(mg);
	p += JG_King_Tile();
	p += JG_Simples();
	p += JG_All_Terminals_Honors();
	if (JG_Full_Flush()) {
		p += JG_Full_Flush();
	}
	else if (JG_Half_Flush()) {
		p += JG_Half_Flush();
	}
	if (JG_7Pairs()) {
		p += JG_7Pairs();
		if (p >= 13) {
			if (my_wind == 0) return 48000;
			else return 36000;
		}
		else if (p >= 11) {
			if (my_wind == 0) return 36000;
			else return 24000;
		}
		else if (p >= 8) {
			if (my_wind == 0) return 24000;
			else return 16000;
		}
		else if (p >= 6) {
			if (my_wind == 0) return 18000;
			else return 12000;
		}
		else if (p >= 4) {
			if (my_wind == 0) return 12000;
			else return 8000;
		}
		else if (p >= 3) {
			if (my_wind == 0) return 7700;
			else return 5200;
		}
		else if (p >= 2) {
			if (my_wind == 0) return 3900;
			else return 2600;
		}
		else if (p >= 1) {
			if (my_wind == 0) return 2000;
			else return 1300;
		}
	}
	p += JG_Runs();
	p += JG_Double_Double_Runs();
	p += JG_All_Triples();
	p += JG_Three_Color();
	p += JG_Full_Stright();
	if (JG_Pure_Outside_Hand()) {
		p += JG_Pure_Outside_Hand();
	}
	else if (JG_Mixed_Outside_Hand()) {
		p += JG_Mixed_Outside_Hand();
	}
	p += JG_Three_Triples('t');
	p += JG_Little_Dragons();
	p += JG_Three_Color_Triples();
	p += JG_Three_Quads();
	p += JG_Double_Double_Runs();
	if (p >= 13) {
		if (my_wind == 0) return 48000;
		else return 36000;
	}
	else if (p >= 11) {
		if (my_wind == 0) return 36000;
		else return 24000;
	}
	else if (p >= 8) {
		if (my_wind == 0) return 24000;
		else return 16000;
	}
	else if (p >= 6) {
		if (my_wind == 0) return 18000;
		else return 12000;
	}
	else if (p >= 4) {
		if (my_wind == 0) return 12000;
		else return 8000;
	}
	else if (p >= 3) {
		if (my_wind == 0) return 7700;
		else return 5200;
	}
	else if (p >= 2) {
		if (my_wind == 0) return 3900;
		else return 2600;
	}
	else if (p >= 1) {
		if (my_wind == 0) return 2000;
		else return 1300;
	}
	return 0;
}

int player::calculation_point(int L, player target, MG mg) {	//点数計算ロンver
	int p = 0;

	p += JG_Blessing_of_Earth(mg);
	p += JG_KOKUSI();
	p += JG_Four_Concealed_Triples('r');
	p += JG_Big_Dragons();
	p += JG_Four_Winds();
	p += JG_All_Honors();
	p += JG_All_Terminals();
	p += JG_All_Green();
	p += JG_Nine_Gates();
	p += JG_Four_Quads();
	if (p > 0) {
		int i = p / 13;
		if (my_wind == 0) return 48000 * i;
		else return 36000 * i;
	}
	p += JG_Reach();
	p += JG_Double_Reach();
	p += JG_First_Turn(mg, 'r');
	p += JG_Final_TileR(mg);
	p += JG_King_Tile();
	p += JG_Simples();
	p += JG_All_Terminals_Honors();
	if (JG_Full_Flush()) {
		p += JG_Full_Flush();
	}
	else if (JG_Half_Flush()) {
		p += JG_Half_Flush();
	}
	if (JG_7Pairs()) {
		p += JG_7Pairs();
		if (p >= 13) {
			if (my_wind == 0) return 48000;
			else return 36000;
		}
		else if (p >= 11) {
			if (my_wind == 0) return 36000;
			else return 24000;
		}
		else if (p >= 8) {
			if (my_wind == 0) return 24000;
			else return 16000;
		}
		else if (p >= 6) {
			if (my_wind == 0) return 18000;
			else return 12000;
		}
		else if (p >= 4) {
			if (my_wind == 0) return 12000;
			else return 8000;
		}
		else if (p >= 3) {
			if (my_wind == 0) return 7700;
			else return 5200;
		}
		else if (p >= 2) {
			if (my_wind == 0) return 3900;
			else return 2600;
		}
		else if (p >= 1) {
			if (my_wind == 0) return 2000;
			else return 1300;
		}
	}
	p += JG_Runs();
	p += JG_Double_Double_Runs();
	p += JG_All_Triples();
	p += JG_Three_Color();
	p += JG_Full_Stright();
	if (JG_Pure_Outside_Hand()) {
		p += JG_Pure_Outside_Hand();
	}
	else if (JG_Mixed_Outside_Hand()) {
		p += JG_Mixed_Outside_Hand();
	}
	p += JG_Three_Triples('r');
	p += JG_Little_Dragons();
	p += JG_Three_Color_Triples();
	p += JG_Three_Quads();
	p += JG_Double_Double_Runs();
	if (p >= 13) {
		if (my_wind == 0) return 48000;
		else return 36000;
	}
	else if (p >= 11) {
		if (my_wind == 0) return 36000;
		else return 24000;
	}
	else if (p >= 8) {
		if (my_wind == 0) return 24000;
		else return 16000;
	}
	else if (p >= 6) {
		if (my_wind == 0) return 18000;
		else return 12000;
	}
	else if (p >= 4) {
		if (my_wind == 0) return 12000;
		else return 8000;
	}
	else if (p >= 3) {
		if (my_wind == 0) return 7700;
		else return 5200;
	}
	else if (p >= 2) {
		if (my_wind == 0) return 3900;
		else return 2600;
	}
	else if (p >= 1) {
		if (my_wind == 0) return 2000;
		else return 1300;
	}
	return 0;

}
//ここから下役判定
int player::JG_KOKUSI() {				//国士無双判定
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }

	if ((handlist[0] == 1 || handlist[0] == 2) &&
		(handlist[8] == 1 || handlist[8] == 2) &&
		(handlist[9] == 1 || handlist[9] == 2) &&
		(handlist[17] == 1 || handlist[17] == 2) &&
		(handlist[18] == 1 || handlist[18] == 2) &&
		(handlist[26] == 1 || handlist[26] == 2) &&
		(handlist[27] == 1 || handlist[27] == 2) &&
		(handlist[28] == 1 || handlist[28] == 2) &&
		(handlist[29] == 1 || handlist[29] == 2) &&
		(handlist[30] == 1 || handlist[30] == 2) &&
		(handlist[31] == 1 || handlist[31] == 2) &&
		(handlist[32] == 1 || handlist[32] == 2) &&
		(handlist[33] == 1 || handlist[33] == 2)) {
		if (Hand[13] == 0 || Hand[13] == 8 ||
			Hand[13] == 9 || Hand[13] == 17 ||
			Hand[13] == 18 || Hand[13] == 26 ||
			Hand[13] == 27 || Hand[13] == 28 ||
			Hand[13] == 29 || Hand[13] == 30 ||
			Hand[13] == 31 || Hand[13] == 32 ||
			Hand[13] == 33)
			return 13;
	}
	return 0;
}
int player::JG_7Pairs() {				// 七対子判定
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }

	int t = 0;
	for (int i = 0;i < 34;i++) {
		if (handlist[i] == 2) t++;
	}
	if (t == 7)return 2;
	return 0;
}

//１飜
int player::JG_Reach() {					//立直判定

	if (reach > 0)return 1;
	return 0;
}
int player::JG_Simples() {					//断ヤオ判定
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
	for (int i = 0;i < 26;i % 9 == 0 ? i++ : i += 8) {
		if (handlist[i] > 0)return 0;
	}
	for (int i = 27;i < 34;i++) {
		if (handlist[i] > 0)return 0;
	}
	return 1;
}
int player::JG_Runs() {						//平和判定
	int p = 0;
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 31;i++) {
		if (handlist[i] >= 2) {
			handlist[i] -= 2;
			int chows[4] = { -1,-1,-1,-1 };
			int c = 0;
			int LIST[34];
			for (int j = 0;j < 34;j++)LIST[j] = handlist[j];

			for (int j = 0;j < 7;j++) {
				if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
					LIST[j]--;
					LIST[j + 1]--;
					LIST[j + 2]--;
					chows[c] = j;
					c++;
					continue;
				}
			}
			for (int j = 9;j < 16;j++) {
				if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
					LIST[j]--;
					LIST[j + 1]--;
					LIST[j + 2]--;
					chows[c] = i;
					c++;
					continue;
				}
			}
			for (int j = 18;j < 25;j++) {
				if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
					LIST[j]--;
					LIST[j + 1]--;
					LIST[j + 2]--;
					chows[c] = i;
					c++;
					continue;
				}
			}
			if (c == 4) {
				for (int j = 0;j < 4;j++) {
					if (Hand[13] == chows[j] || Hand[13] == chows[j] + 2) {
						return 1;
					}
				}
			}

			handlist.fill(0);
			for (int j = 0;j < 14;j++)handlist[Hand[j]]++;
		}
	}
	return 0;
}

int player::JG_Self_Draw() {				//門前自摸判定

	if (rotated[0] >= 0)
		return 0;
	else
		return 1;

}
int player::JG_First_Turn(MG mg, char t) {				//一発判定
	if (t == 't') {
		if (reach == mg.show_turn() + 1)return 1;
	}
	else if (t == 'r') {
		if (reach == mg.show_turn())return 1;
	}
	return 0;
}
int player::JG_Double_Runs() {				//一盃口判定
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 34;i++) {
		if (handlist[i] >= 2) {
			handlist[i] -= 2;
			if (JG_chows() || JG_pungs(0)) {
				int chows[4] = { -1,-1,-1,-1 };
				int c = 0;
				int LIST[34];
				for (int j = 0;j < 34;j++)LIST[j] = handlist[j];

				for (int j = 0;j < 7;j++) {
					if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
						LIST[j]--;
						LIST[j + 1]--;
						LIST[j + 2]--;
						chows[c] = j;
						c++;
						continue;
					}
				}
				for (int j = 9;j < 16;j++) {
					if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
						LIST[j]--;
						LIST[j + 1]--;
						LIST[j + 2]--;
						chows[c] = i;
						c++;
						continue;
					}
				}
				for (int j = 18;j < 25;j++) {
					if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
						LIST[j]--;
						LIST[j + 1]--;
						LIST[j + 2]--;
						chows[c] = i;
						c++;
						continue;
					}
				}
				if (c > 1) {
					for (int j = 0;j < c - 1;j++) {
						for (int k = 0;k < c;k++) {
							if (chows[j] == chows[k])return 1;
						}
					}
				}
			}
			for (int j = 0;j < 34;j++)handlist[j] = 0;
			for (int j = 0;j < 14;j++)handlist[Hand[j]]++;
		}
	}
	return 0;
}

int player::JG_Final_TileR(MG mg) {				//河底撈魚(ホウテイロン)判定
	array<int, 34>HAIYAMA = mg.show_HAIYAMA();
	for (int i = 0;i < 34;i++) {
		if (HAIYAMA[i] != 0)return 0;
	}
	return 1;
}
int player::JG_Final_TileT(MG mg) {				//海底摸月(ハイテイツモ)判定
	array<int, 34>HAIYAMA = mg.show_HAIYAMA();
	for (int i = 0;i < 34;i++) {
		if (HAIYAMA[i] != 0)return 0;
	}
	return 1;
}
int player::JG_King_Tile() {				//嶺上開花判定
	return 0;
}
int player::JG_Double_Reach() {				//二重立直判定
	if (reach == 1)return 1;
	return 0;
}
int player::JG_Add_A_Quad() {				//槍槓判定
	return 0;
}
//２飜
int player::JG_All_Triples() {				//対々和判定
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
	for (int i = 0;i < 34;i++) {
		if (handlist[i] == 2) {
			handlist[i] -= 2;
			for (int j = 0;j < 34;j++) { if (!(handlist[j] == 0 || handlist[j] >= 3))return 2; }
			return 0;
		}
	}
	return 0;
}

int player::JG_Three_Color() {				//三色同順判定
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
	for (int i = 0;i < 34;i++) {
		if (handlist[i] >= 2) {
			handlist[i] -= 2;
			if (JG_chows() || JG_pungs(0)) {
				int chows[4] = { -1,-1,-1,-1 };
				int c = 0;
				int LIST[34];
				for (int j = 0;j < 34;j++)LIST[j] = handlist[j];

				for (int j = 0;j < 7;j++) {
					if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
						LIST[j]--;
						LIST[j + 1]--;
						LIST[j + 2]--;
						chows[c] = j;
						c++;
						continue;
					}
				}
				for (int j = 9;j < 16;j++) {
					if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
						LIST[j]--;
						LIST[j + 1]--;
						LIST[j + 2]--;
						chows[c] = i;
						c++;
						continue;
					}
				}
				for (int j = 18;j < 25;j++) {
					if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
						LIST[j]--;
						LIST[j + 1]--;
						LIST[j + 2]--;
						chows[c] = i;
						c++;
						continue;
					}
				}
				if (c >= 3) {
					for (int j = 0;j < c - 2;j++) {
						for (int k = 0;k < c - 1;k++) {
							if (chows[j] + 9 == chows[k]) {
								for (int m = 0;m < c;m++) {
									if (chows[k] + 9 == chows[m])
										if (rotated[0] >= 0)
											return 1;
										else
											return 2;

								}
							}
						}
					}
				}
			}
			handlist.fill(0);
			for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
			for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
		}
	}
	return 0;
}
int player::JG_Full_Stright() {				//一気通貫判定
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
	for (int i = 0;i < 34;i++) {
		if (handlist[i] >= 2) {
			handlist[i] -= 2;
			if (JG_chows() || JG_pungs(0)) {
				int chows[4] = { -1,-1,-1,-1 };
				int c = 0;
				int LIST[34];
				for (int j = 0;j < 34;j++)LIST[j] = handlist[j];

				for (int j = 0;j < 7;j++) {
					if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
						LIST[j]--;
						LIST[j + 1]--;
						LIST[j + 2]--;
						chows[c] = j;
						c++;
						continue;
					}
				}
				for (int j = 9;j < 16;j++) {
					if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
						LIST[j]--;
						LIST[j + 1]--;
						LIST[j + 2]--;
						chows[c] = i;
						c++;
						continue;
					}
				}
				for (int j = 18;j < 25;j++) {
					if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
						LIST[j]--;
						LIST[j + 1]--;
						LIST[j + 2]--;
						chows[c] = i;
						c++;
						continue;
					}
				}
				if (c >= 3) {
					for (int j = 0;j < c - 2;j++) {
						if (chows[j] % 9 == 0) {
							for (int k = j + 1;k < c - 1;k++) {
								if (chows[j] + 3 == chows[k]) {
									for (int m = k + 1;m < c;m++) {
										if (chows[k] + 3 == chows[m])
											if (rotated[0] >= 0)
												return 1;
											else
												return 2;
									}
								}

							}
						}
					}
				}
			}
			handlist.fill(0);
			for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
			for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
		}
	}
	return 0;
}
int player::JG_Mixed_Outside_Hand() {		//混全帯判定
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
	for (int i = 0;i < 34;i++) {
		if (!(i % 9 != 0 && i % 9 != 8 && i > 26)) {
			if (handlist[i] >= 2) {
				handlist[i] -= 2;
				if (JG_chows() || JG_pungs(0)) {
					int chows[4] = { -1,-1,-1,-1 };
					int c = 0;
					int LIST[34];
					for (int j = 0;j < 34;j++)LIST[j] = handlist[j];

					for (int j = 0;j < 7;j++) {
						if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
							LIST[j]--;
							LIST[j + 1]--;
							LIST[j + 2]--;
							chows[c] = j;
							c++;
							continue;
						}
					}
					for (int j = 9;j < 16;j++) {
						if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
							LIST[j]--;
							LIST[j + 1]--;
							LIST[j + 2]--;
							chows[c] = i;
							c++;
							continue;
						}
					}
					for (int j = 18;j < 25;j++) {
						if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
							LIST[j]--;
							LIST[j + 1]--;
							LIST[j + 2]--;
							chows[c] = i;
							c++;
							continue;
						}
					}

					for (int j = 0;j < c;j++) {
						if (chows[j] % 9 != 0 && chows[j] != 6)return 0;
					}
					for (int j = 0;j < 27;j++) {
						if (j % 9 != 0 && j % 9 != 8) {
							if (handlist[j] > 0) {
								return 0;
							}
						}

					}
					if (rotated[0] >= 0)
						return 1;
					else
						return 2;
				}
				handlist.fill(0);
				for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
				for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
			}
		}
	}
	return 0;
}
int player::JG_Three_Triples(char t) {			//三暗刻判定
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
	for (int i = 0;i < 34;i++) {
		if (handlist[i] >= 2) {
			handlist[i] -= 2;
			if (JG_chows() || JG_pungs(0)) {
				int LIST[34];
				for (int j = 0;j < 34;j++)LIST[j] = handlist[j];
				for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)LIST[rotated[i]]--; }
				int pungs[4] = { -1,-1,-1,-1 };
				int p = 0;
				for (int k = 0;k < 34;k++) {
					if (LIST[k] == 3) {
						pungs[p] = k;
						p++;
					}
				}
				if (p == 4) {
					return 2;
				}

				for (int j = 0;j < 7;j++) {
					if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
						LIST[j]--;
						LIST[j + 1]--;
						LIST[j + 2]--;
						int pungs[4] = { -1,-1,-1,-1 };
						int p = 0;
						for (int k = 0;k < 34;k++) {
							if (LIST[k] == 3) {
								pungs[p] = k;
								p++;
							}
						}
						if (p == 3) {
							if (t == 't')return 2;
							else if (t == 'r') {
								if (Hand[13] == j == Hand[13] == j + 1 || Hand[13] == j + 2) {
									return 2;
								}
							}
						}
						LIST[j]++;
						LIST[j + 1]++;
						LIST[j + 2]++;
					}

				}
				for (int j = 9;j < 16;j++) {
					if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
						LIST[j]--;
						LIST[j + 1]--;
						LIST[j + 2]--;
						int pungs[4] = { -1,-1,-1,-1 };
						int p = 0;
						for (int k = 0;k < 34;k++) {
							if (LIST[k] == 3) {
								pungs[p] = k;
								p++;
							}
						}
						if (p == 3) {
							if (t == 't')return 2;
							else if (t == 'r') {
								if (Hand[13] == j == Hand[13] == j + 1 || Hand[13] == j + 2) {
									return 2;
								}
							}
						}
						LIST[j]++;
						LIST[j + 1]++;
						LIST[j + 2]++;
					}
				}
				for (int j = 18;j < 25;j++) {
					if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
						LIST[j]--;
						LIST[j + 1]--;
						LIST[j + 2]--;
						int pungs[4] = { -1,-1,-1,-1 };
						int p = 0;
						for (int k = 0;k < 34;k++) {
							if (LIST[k] == 3) {
								pungs[p] = k;
								p++;
							}
						}
						if (p == 3) {
							if (t == 't')return 2;
							else if (t == 'r') {
								if (Hand[13] == j == Hand[13] == j + 1 || Hand[13] == j + 2) {
									return 2;
								}
							}
						}
						LIST[j]++;
						LIST[j + 1]++;
						LIST[j + 2]++;

					}
				}

			}
			handlist.fill(0);
			for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
			for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
		}
	}
	return 0;

}
int player::JG_Little_Dragons() {			//小三元判定

	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
	int c = 0, p = 0;
	for (int i = 31;i < 34;i++) {
		if (handlist[i] == 3)c++;
		else if (handlist[i] == 2)p++;
	}
	if (c == 2 && p == 1)return 2;
	return 0;
}

int player::JG_All_Terminals_Honors() {		//混老頭判定
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
	for (int i = 0;i < 27;i++) {
		if (i % 9 != 0 && i % 9 != 8)return 0;
	}
	for (int i = 27;i < 34;i++) { if (handlist[i] > 0)return 2; }
	return 0;
}
int player::JG_Three_Color_Triples() {		//三色同刻判定
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
	for (int i = 0;i < 34;i++) {
		if (handlist[i] >= 2) {
			handlist[i] -= 2;
			if (JG_chows() || JG_pungs(0)) {
				int LIST[34];
				for (int j = 0;j < 34;j++)LIST[j] = handlist[j];
				for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)LIST[rotated[i]]--; }
				int pungs[4] = { -1,-1,-1,-1 };
				int p = 0;
				for (int k = 0;k < 34;k++) {
					if (LIST[k] == 3) {
						pungs[p] = k;
						p++;
					}
				}
				if (p == 4) {
					for (int j = 0;j < 4;j++) {
						for (int k = j + 1;k < 4;k++) {
							for (int l = k + 1;l < 4;l++) {
								if (pungs[j] + 9 == pungs[k] && pungs[k] + 9 == pungs[l])return 2;
							}
						}
					}
				}

				for (int j = 0;j < 7;j++) {
					if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
						LIST[j]--;
						LIST[j + 1]--;
						LIST[j + 2]--;
						int pungs[4] = { -1,-1,-1,-1 };
						int p = 0;
						for (int k = 0;k < 34;k++) {
							if (LIST[k] == 3) {
								pungs[p] = k;
								p++;
							}
						}
						if (p == 3) {
							if (pungs[0] + 9 == pungs[1] && pungs[1] + 9 == pungs[2])return 2;
						}
						LIST[j]++;
						LIST[j + 1]++;
						LIST[j + 2]++;
					}

				}
				for (int j = 9;j < 16;j++) {
					if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
						LIST[j]--;
						LIST[j + 1]--;
						LIST[j + 2]--;
						int pungs[4] = { -1,-1,-1,-1 };
						int p = 0;
						for (int k = 0;k < 34;k++) {
							if (LIST[k] == 3) {
								pungs[p] = k;
								p++;
							}
						}
						if (p == 3) {
							if (pungs[0] + 9 == pungs[1] && pungs[1] + 9 == pungs[2])return 2;
						}
						LIST[j]++;
						LIST[j + 1]++;
						LIST[j + 2]++;
					}
				}
				for (int j = 18;j < 25;j++) {
					if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
						LIST[j]--;
						LIST[j + 1]--;
						LIST[j + 2]--;
						int pungs[4] = { -1,-1,-1,-1 };
						int p = 0;
						for (int k = 0;k < 34;k++) {
							if (LIST[k] == 3) {
								pungs[p] = k;
								p++;
							}
						}
						if (p == 3) {
							if (pungs[0] + 9 == pungs[1] && pungs[1] + 9 == pungs[2])return 2;
						}
						LIST[j]++;
						LIST[j + 1]++;
						LIST[j + 2]++;

					}
				}

			}
			handlist.fill(0);
			for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
			for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
		}
	}
	return 0;
}
int player::JG_Three_Quads() {				//三槓子
	return 0;
}
//３飜
int player::JG_Half_Flush() {				//混一色判定
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
	int p = 0, c = 0;
	for (int i = 26;i < 34;i++)p += handlist[i];

	for (int i = 0;i < 7;i++) c += handlist[i];
	if (p + c == 14) {
		if (rotated[0] >= 0)
			return 2;
		else
			return 3;
	}
	c = 0;
	for (int i = 9;i < 16;i++) c += handlist[i];
	if (p + c == 14) {
		if (rotated[0] >= 0)
			return 2;
		else
			return 3;
	}
	c = 0;
	for (int i = 18;i < 25;i++) c += handlist[i];
	if (p + c == 14) {
		if (rotated[0] >= 0)
			return 2;
		else
			return 3;
	}
	return 0;
}
int player::JG_Pure_Outside_Hand() {		//清全帯判定
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
	for (int i = 0;i < 34;i++) {
		if (!(i % 9 != 0 && i % 9 != 8 && i > 26)) {
			if (handlist[i] >= 2) {
				handlist[i] -= 2;
				if (JG_chows() || JG_pungs(0)) {
					int chows[4] = { -1,-1,-1,-1 };
					int c = 0;
					int LIST[34];
					for (int j = 0;j < 34;j++)LIST[j] = handlist[j];

					for (int j = 0;j < 7;j++) {
						if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
							LIST[j]--;
							LIST[j + 1]--;
							LIST[j + 2]--;
							chows[c] = j;
							c++;
							continue;
						}
					}
					for (int j = 9;j < 16;j++) {
						if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
							LIST[j]--;
							LIST[j + 1]--;
							LIST[j + 2]--;
							chows[c] = i;
							c++;
							continue;
						}
					}
					for (int j = 18;j < 25;j++) {
						if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
							LIST[j]--;
							LIST[j + 1]--;
							LIST[j + 2]--;
							chows[c] = i;
							c++;
							continue;
						}
					}

					for (int j = 0;j < c;j++) {
						if (chows[j] % 9 != 0 && chows[j] != 6)return 0;
					}
					for (int j = 0;j < 27;j++) {
						if (j % 9 != 0 && j % 9 != 8) {
							if (handlist[j] > 0) {
								return 0;
							}
						}

					}
					for (int j = 27;j < 34;j++) { if (handlist[j] > 0)return 0; }
					if (rotated[0] >= 0)
						return 1;
					else
						return 2;
				}
				handlist.fill(0);
				for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
				for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
			}
		}
	}
	return 0;

}
int player::JG_Double_Double_Runs() {		//二盃口判定
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 34;i++) {
		if (handlist[i] >= 2) {
			handlist[i] -= 2;
			if (JG_chows() || JG_pungs(0)) {
				int chows[4] = { -1,-1,-1,-1 };
				int c = 0;
				int LIST[34];
				for (int j = 0;j < 34;j++)LIST[j] = handlist[j];

				for (int j = 0;j < 7;j++) {
					if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
						LIST[j]--;
						LIST[j + 1]--;
						LIST[j + 2]--;
						chows[c] = j;
						c++;
						continue;
					}
				}
				for (int j = 9;j < 16;j++) {
					if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
						LIST[j]--;
						LIST[j + 1]--;
						LIST[j + 2]--;
						chows[c] = i;
						c++;
						continue;
					}
				}
				for (int j = 18;j < 25;j++) {
					if (LIST[j] >= 1 && LIST[j + 1] >= 1 && LIST[j + 2] >= 1) {
						LIST[j]--;
						LIST[j + 1]--;
						LIST[j + 2]--;
						chows[c] = i;
						c++;
						continue;
					}
				}
				if (chows[0] == chows[1] && chows[2] == chows[3])return 3;
			}
			for (int j = 0;j < 34;j++)handlist[j] = 0;
			for (int j = 0;j < 14;j++)handlist[Hand[j]]++;
		}
	}
	return 0;
}
//６飜
int player::JG_Full_Flush() {				//清一色判定
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
	int c = 0;

	for (int i = 0;i < 7;i++) c += handlist[i];
	if (c == 14) {
		if (rotated[0] >= 0)
			return 1;
		else
			return 2;
	}
	c = 0;
	for (int i = 9;i < 16;i++) c += handlist[i];
	if (c == 14) {
		if (rotated[0] >= 0)
			return 5;
		else
			return 6;
	}
	c = 0;
	for (int i = 18;i < 25;i++) c += handlist[i];
	if (c == 14) {
		if (rotated[0] >= 0)
			return 5;
		else
			return 6;
	}
	return 0;
}
//１３飜(役満)
int player::JG_Four_Concealed_Triples(char t) {	//四暗刻判定
	int p = 0;
	int c[4] = { -1,-1,-1,-1 };
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 34;i++) {
		if (handlist[i] == 3) {
			c[p] = i;
			p++;
		}
	}
	if (p == 4) {
		if (t == 't')
			return 13;
		else {
			for (int i = 0;i < p;i++) {
				if (c[p] == Hand[13])return 0;
			}
			return 13;
		}
	}
	return 0;
}
int player::JG_Big_Dragons() {				//大三元判定
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
	if (handlist[31] == 3 && handlist[32] == 3 && handlist[33] == 3)return 13;
	return 0;
}
int player::JG_Four_Winds() {				//大四喜か小四喜判定
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
	int T = 0, H = 0;
	for (int i = 0;i < 31;i++) {
		if (handlist[i] == 3)T++;
		else if (handlist[i] == 2)H++;
	}
	if (T == 4)return 26;
	else if (T == 3 && H == 1)return 13;
	return 0;
}
int player::JG_All_Honors() {				//字一色判定
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
	for (int i = 0;i < 27;i++) {
		if (handlist[i] > 0)return 0;
	}
	return 0;
}
int player::JG_All_Terminals() {			//清老頭判定
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
	for (int i = 0;i < 27;i++) {
		if (i % 9 != 0 && i % 9 != 8)return 0;
	}
	return 13;

}
int player::JG_Blessing_of_Earth(MG mg) {	//地和判定
	if (mg.show_turn() == 1 && my_wind != 0)return 13;
	return 0;
}
int player::JG_All_Green() {				//緑一色判定
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 12;i++) { if (rotated[i] >= 0)handlist[rotated[i]]++; }
	for (int i = 0;i < 34;i++) {
		if (i != 19 && i != 20 && i != 21 && i != 23 && i != 25 && i != 31) {
			if (handlist[i] > 0)return 0;
		}
	}
	return 13;
}
int player::JG_Nine_Gates() {				//九蓮宝燈判定
	handlist.fill(0);
	for (int i = 0;i < 14;i++) { if (Hand[i] >= 0)handlist[Hand[i]]++; }
	for (int i = 0;i < 3;i++) {
		if (Hand[0] / 9 == i) {
			int p = i * 9;
			if (handlist[p] > 2 && handlist[p + 1] > 0 &&
				handlist[p + 2] > 0 && handlist[p + 3] > 0 &&
				handlist[p + 4] > 0 && handlist[p + 5] > 0 &&
				handlist[p + 6] > 0 && handlist[p + 7] > 0 && handlist[p + 8] > 2) {
				return 13;
			}
		}
	}
	return 0;
}
int player::JG_Four_Quads() {				//四槓子判定
	return 0;
}
int player::JG_Blessing_of_Heaven(MG mg) {		//天和判定
	if (mg.show_turn() == 1 && my_wind == 0)return 13;
	return 0;
}

