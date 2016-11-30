#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include <windows.h>

#define blue 9 
#define def 15
#define red 12 
#define yellow 14 
#define green 10 
#define pink 13
#define gray 8
#define purple 4
#define wb 99999
#define bluegreen 11
#define test
void INIT_SET();//各局ごとの初期化
void PRINT(unsigned char *line,unsigned int f);//麻雀牌の表示
void SORT(unsigned char *line);//麻雀牌のソート（バブルソート）
void SELECT();//切る牌の選択
void TUMO();//山から１牌のツモ
void GAME();//２人用麻雀
void START();//麻雀の開始
void YAKU(int cnt,int tumo_f );//役判定
void SCORE(int num,int tumo_f);//あがり点数の計算
int AGARI(int nAdd,unsigned char *line);//あがり判定
void HENKAN(unsigned char *line,int n);
void SHUNTU(int *r);
void KOUTU(int *r);
void color(int i);
void TENPAI();
void AITE();
void AGA_PRINT();
void RYUUKYOKU();
void KYOKU_PRINT();
void DORA();
#define TEPAI (14)           //手牌はツモって１４枚
#define MJ_PAI (34)           //全麻雀牌は３４種類
#define MJ_PAI_FULL (136)         //全麻雀牌は１３６枚
#define TUMO_CNT (28)    //ツモれる回数
int ScoreTableHigh_Ron[2][15] = {
 { // 子用
  0, 0, 0, 0, 0, // 0 ～ 4役
  8000, 12000, 12000, 16000, 16000, 16000,
  24000, 24000, 24000, 32000,
 },
 { // 親用
  0, 0, 0, 0, 0, // 0 ～ 4役
  12000, 18000, 18000, 24000, 24000, 24000,
  36000, 36000, 36000, 48000,
 },
};
int ScoreTableLow_Ron[2][4][10] = {
 { // 子用
  // １役, 20/30/40/50/60/70/80/90/100/110
  { 0, 1000, 1300, 1600, 2000, 2300, 2600, 2900, 3200, 0, },
  // ２役, 20/30/40/50/60/70/80/90/100/110
  { 0, 2000, 2600, 3200, 3900, 4500, 5200, 5800, 6400, 7100, },
  // ３役, 20/30/40/50/60/70/80/90/100/110
  { 0, 3900, 5200, 6400, 7700, 8000, 8000, 8000, 8000, 8000, },
  // ４役, 20/30/40/50/60/70/80/90/100/110
  { 0, 7700, 8000, 8000, 8000, 8000, 8000, 8000, 8000, 8000, },
 },
 { // 親用
  // １役, 20/30/40/50/60/70/80/90/100/110
  { 0, 1500, 2000, 2400, 2900, 3400, 3900, 4400, 4800, 0, },
  // ２役, 20/30/40/50/60/70/80/90/100/110
  { 0, 2900, 3900, 4800, 5800, 6800, 7700, 8700, 9600, 10400, },
  // ３役, 20/30/40/50/60/70/80/90/100/110
  { 0, 5800, 7700, 9600, 11600, 12000, 12000, 12000, 12000, 12000, },
  // ４役, 20/30/40/50/60/70/80/90/100/110
  { 0, 11600, 12000, 12000, 12000, 12000, 12000, 12000, 12000, 12000, },
 }
};
char yaku_name[][16] = {
 "立直",//0
 "ダブル立直",
 "一発",
 "門前清自摸和",
 "平和",
 "断幺九",
 "一盃口",
 "二盃口",
 "全帯公",
 "純正全帯幺",
 "混老頭",//10
 "対々和",
 "混一色",
 "清一色",
 "一気通貫",
 "三色同順",
 "三色同刻",
 "七対子",
 "三暗刻",
 "小三元",
 "三槓子",//20
 "嶺上開花",
 "搶槓",
 "海底",
 "役牌（東）",
 "役牌（南）",
 "役牌（西）",
 "役牌（北）",
 "役牌（白）",
 "役牌（発）",
 "役牌（中）",//30
 "流し満貫",
 "ドラ",
 "緑一色",//33役満
 "四暗刻",
 "大三元",
 "小四喜",
 "大四喜",
 "清老頭",
 "字一色",
 "国士無双",//40
 "九蓮宝燈",
 "四槓子",
 "天和",
 "地和",
 "人和",//45
};
int yaku_f[45];//うえのyaku_nameと対応するフラグ
char yaku_han[][16]={
 "1翻",
 "2翻",
 "1翻",
 "1翻",
 "1翻",
 "1翻",
 "1翻",
 "3翻",
 "2翻",
 "3翻",
 "2翻",
 "2翻",
 "3翻",
 "6翻",
 "2翻",
 "2翻",
 "2翻",
 "2翻",
 "2翻",
 "4翻",
 "2翻",
 "1翻",
 "1翻",
 "1翻",
 "1翻",
 "1翻",
 "1翻",
 "1翻",
 "1翻",
 "1翻",
 "1翻",
 "満貫"
};
char mangan[][16]={
 "",
 "満貫",
 "ハネ満",//6~
 "倍満",//8~
 "3倍満",//11~
 "役満"
};
char ba[][4]={
 "東","南","西","北"};
 int ba_num=0;
unsigned char marhjang[] = {
 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, // 萬子0~8
 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, // 筒子9~17
 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, // 索子18~26
 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,    // 東南西北白発中27~33
};
unsigned char marhjang2[] = {
 0,0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, // 萬子
 0,0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, // 筒子
 0,0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, // 索子
 0,0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,    // 東南西北白発中
};
int table_num[MJ_PAI];//麻雀卓の山の牌ごとの個数
unsigned char table[MJ_PAI_FULL];                           //麻雀卓の山
int t_cnt=0;            //山の牌カウント
unsigned char wanpai[14];//王牌
unsigned char print_wanpai1[250];//王牌の表示の為の配列
unsigned char print_wanpai2[250];//王牌の表示の為の配列
int kyoutaku;//供託＝何本場か
int kyoku=1;//何局目か
unsigned char print_dora1[10];
unsigned char print_dora2[10];
unsigned char line_dora[2];
typedef struct{            //構造体
 unsigned char line[TEPAI];                              //手牌
 unsigned char sutepai[60];        //捨て牌
 unsigned int sutenum;         //ユーザの捨て牌の数
 unsigned char pnum[MJ_PAI];        //手牌の牌ごとの数
 unsigned char cpline[TEPAI];       //lineのコピー
 unsigned char cpnum[MJ_PAI];        //pnumのコピー
 unsigned char print_line1[250];       //ユーザの手配の表示の為の配列（１２３４５６７８９）
 unsigned char print_line2[250];       //ユーザの手配の表示の為の配列（萬筒索東南西北白発中)
 int table[38];/* ×　　一萬　二萬　三萬　四萬　五萬　六萬　七萬　八萬　九萬
       [0]   [1]   [2]   [3]   [4]   [5]   [6]   [7]   [8]   [9]
       ×　　一筒　二筒　三筒　四筒　五筒　六筒　七筒　八筒　九筒
       [10]  [11]  [12]  [13]  [14]  [15]  [16]  [17]  [18]  [19]
       ×　　一索　二策　三索　四索　五索　六索　七索　八索　九索
       [20]  [21]  [22]  [23]  [24]  [25]  [26]  [27]  [28]  [29]
       ×　　東　　南　　西　　北　　白　　發　　中
       [30]  [31]  [32]  [33]  [34]  [35]  [36]  [37] 
      手牌の牌ごとの枚数のための配列*/
 int koutu;//こうつのかず
 int shuntu;//順子の数
 unsigned char atamapai;
 int agari;
 int a_cnt;
 int ri_ti;//りーちしたかどうか
 int tumokaisuu;//何回ツモってるか
 int tensuu;//点数
 int han;//何翻か
 int tumokaisuu_ri_ti_go;//リーチ後のツモ回数（一発判定）
 unsigned char agaripai[10];
 int kiripai[38];//marjangと同じ型
 unsigned char shuntu_pai[3][3];
 unsigned char koutu_pai[3][3];
 int fu;//符
 int dora_num;
 //unsigned int agaricnt;         //アガリカウント
}PLAYER;
PLAYER member[4];           //0はユーザ、1はとりあえず相手
PLAYER *pl;             //pl[0]がユーザ
 

////////////////////////////////////////////////////////////////////////////////////////
void SCORE(int num,int tumo_f){
 int i;
 pl->fu=20;
 if(tumo_f==1){// 面前でロンあがりの時
  pl->fu+=10;
 } else {
     // 全部順子の時
     if ( pl->shuntu == 4 ) {
      pl->fu += 10;
     }
    }
 // 刻子・槓子・雀頭による加算
 // 刻子
 for(i=0;i<pl->koutu;i++){
  if ( ( pl->koutu_pai[i][0]==marhjang2[1] || pl->koutu_pai[i][0]==marhjang2[9] || pl->koutu_pai[i][0]==marhjang2[11] || pl->koutu_pai[i][0]==marhjang2[19] || pl->koutu_pai[i][0]==marhjang2[21] || pl->koutu_pai[i][0]==marhjang2[29])
  ||( pl->koutu_pai[i][0]>=marhjang2[31] && pl->koutu_pai[i][0]<=marhjang2[37]) ){
   pl->fu+=8;
  }else{
   pl->fu+=4;
  }
 }
 // 雀頭
 if( pl->atamapai>=marhjang2[31] && pl->atamapai<=marhjang2[37]){
  pl->fu+=2;
 }
 if(tumo_f==0 && yaku_f[4]==0){
  pl->fu+=2;
 }
 if(yaku_f[17]==1){
  pl->fu=50;
 }
 if(pl->fu%10!=0){
  pl->fu=(pl->fu/10+1)*10;
 }
 
}
void YAKU(int cnt,int tumo_f){
 int i,j,z,k;
 int pin_f=0;//ピンフフラグ
 int tan_f=0;//たんやおフラグ
 int pe_ko=0;
 int pe_ko_f=0;//いーぺーこー＆りゃんぺーこーフラグ
 int honrou=0;//ホンロウトウフラグ
 int tin=0;//チンイツふらぐ
 int tin_ji=0;//ホンイツふらぐ
 unsigned char max=0,min=0x60;
 int n[ 3 ] = { 0, 0, 0 };
 HENKAN(pl->line,0);
 if(pl->ri_ti==1){//りーち
  yaku_f[0]=1;
  pl->han+=1;
 }
 if(pl->ri_ti==1 && pl->tumokaisuu==0){//ダブルりーち
  yaku_f[1]=1;
  yaku_f[0]=0;
  pl->han+=1;
 }
 if(pl->ri_ti==1 && pl->tumokaisuu_ri_ti_go<=1){//一発
  yaku_f[2]=1;
  pl->han+=1;
 }
 if(tumo_f==0){//ツモ
  yaku_f[3]=1;
  pl->han+=1;
 }
 //ピンフ
 if(pl->shuntu==4){
  for(j=0;j<pl->shuntu;j++){
  if ( ( pl->line[13]==pl->shuntu_pai[j][0] ) || ( pl->line[13]==pl->shuntu_pai[j][2] ) ){
   pin_f=1;
   break;
  }
  
  }
 if( (pl->atamapai>=marhjang[27]) && (pl->atamapai<=marhjang[33]) ){
  pin_f=0;
 }
 if(pin_f==1){
     yaku_f[4]=1;
     pl->han+=1;
 }
 }
 //たんやお
 //tan_f=0;
 for(i=0;i<=13;i++){
  if ( (pl->line[i]==marhjang[0] || pl->line[i]==marhjang[8] || pl->line[i]==marhjang[9] || pl->line[i]==marhjang[17] || pl->line[i]==marhjang[18] || pl->line[i]==marhjang[26]) ||
  (pl->line[i]>=marhjang[27] && pl->line[i]<=marhjang[33]) ){
   tan_f=1;
 break;
  }
 }
 if(tan_f==0){
  yaku_f[5]=1;
 pl->han+=1;
 }
 //いーぺーこー＆りゃんぺーこー
 if(pl->shuntu>=2){
  for(i=0;i<pl->shuntu;i++){
  for(j=0;j<pl->shuntu;j++){
     if( ( pl->shuntu_pai[i][0]==pl->shuntu_pai[j][0] ) && (pl->shuntu_pai[i][1]==pl->shuntu_pai[j][1] ) && (pl->shuntu_pai[i][2]==pl->shuntu_pai[j][2] ) ){
    pe_ko++;
    if(pe_ko==pl->shuntu+2){
     pe_ko_f=1;
    }
    if(pe_ko==pl->shuntu+4){
     pe_ko_f=2;
    }
     } 
   }
  }
 if(pe_ko_f==1){//いーぺーこーなら
  yaku_f[6]=1;
  pl->han+=1;
 }
 if(pe_ko_f==2){//りゃんぺーこーなら
  yaku_f[7]=1;
  pl->han+=3;
 }
 //printf("i-pe-%d\n",pe_ko);
 }
 //チャンタ＆純チャン＆ホンロウトウ
 if( (pl->atamapai==marhjang[0] || pl->atamapai==marhjang[8] || pl->atamapai==marhjang[9] || pl->atamapai==marhjang[17] || pl->atamapai==marhjang[18] || pl->atamapai==marhjang[26]) ||
 (pl->atamapai>=marhjang[27] && pl->atamapai<=marhjang[33]) ){
  for(i=0;i<=13;i++){
  if ( (pl->line[i]>=marhjang[1] && pl->line[i]<=marhjang[7]) || (pl->line[i]>=marhjang[10] && pl->line[i]<=marhjang[16]) || (pl->line[i]>=marhjang[19] && pl->line[i]<=marhjang[25]) ){
   honrou=3;//たんやお系の場合
   break;
  }
  else if(pl->line[i]>=marhjang[27] && pl->line[i]<=marhjang[33]){
   honrou=2;//チャンタ系の場合
   break;
  }
  }
 if(honrou==2){//チャンタのとき
  yaku_f[8]=1;
  pl->han+=2;
 }
 else if( ( honrou==0 && cnt==2 ) || ( honrou==0 && pl->koutu==4 ) ){//ホンロウトウのとき
  yaku_f[10]=1;
  pl->han+=2;
 }
 else if(honrou!=3){//純チャンのとき
  yaku_f[9]=1;
  pl->han+=3;
 }
 }
 //トイトイ
 if(pl->koutu==4){
  yaku_f[11]=1;
 pl->han+=2;
 }
 //ホンイツ＆チンイツ
 for(i=0;i<=13;i++){
  if(pl->line[i]>=marhjang2[31] && pl->line[i]<=marhjang2[37]){
  tin_ji=1;
  break;
  }
 }
 for(i=0;i<=13;i++){
  if ( (pl->line[i]>max) && (pl->line[i]>=marhjang2[1] && pl->line[i]<=marhjang2[29]) ){
  max=pl->line[i];
  }
  if( (pl->line[i]<min) && (pl->line[i]>=marhjang2[1] && pl->line[i]<=marhjang2[29]) ){
  min=pl->line[i];
  }
 }
 if( (min>=marhjang2[1] && max<=marhjang2[9]) || (min>=marhjang2[11] && max<=marhjang2[19]) || (min>=marhjang2[21] && max<=marhjang2[29]) ){
  if(tin_ji==1){//ホンイツのとき
  yaku_f[12]=1;
  pl->han+=3;
  }else{
  yaku_f[13]=1;
  pl->han+=6;
  }
 }
 //イッツー
 if(pl->shuntu>=3){
  for ( j = 0; j < 3; j++ ) {
  for(k=0;k<3;k++){
   n[k]=0;
  }
      for ( i = 0; i <pl->shuntu; i++ ) {//シュンツのループ
        for ( z = 0; z < 3; z++ ) {
          if ( ( pl->shuntu_pai[i][0]) == marhjang[ j * 9 + z * 3 + 0 ]
           || ( pl->shuntu_pai[i][1]) == marhjang[ j * 9 + z * 3 + 1 ]
           || ( pl->shuntu_pai[i][2]) == marhjang[ j * 9 + z * 3 + 2 ] ) {
           n[ z ] = 1;
          }
        }
      }
      if ( n[ 0 ]==1 && n[ 1 ]==1 && n[ 2 ]==1 ) {
        break;
      }
    }
    if ( j != 3 ) {
  yaku_f[14]=1;
  pl->han+=2;
    }
   
 }
 /*//三色同順
 if ( pl->shuntu >= 3 ) {
  for(i=0;i<pl->shuntu;i++){
  for(*/
//七対子
if(cnt==2){
 yaku_f[17]=1;
  pl->han+=2;
 }
 //三暗刻
 //ドラ
 if(pl->ri_ti==1){
  for(i=0;i<=1;i++){
   for(j=0;j<=13;j++){
   if(line_dora[i]==pl->line[j]){
    pl->han+=1;
    pl->dora_num++;
   }
   }
  }
}else{
 for(j=0;j<=13;j++){
  if(line_dora[0]==pl->line[j]){
   pl->han+=1;
   pl->dora_num++;
  }
  }
}
 
}
 void AGA_PRINT(){
  int i,a=0,cnt=0;
    Sleep(2200);
   system("cls");
   printf("\n　　　　　　　　　%s場　第%d局 %d本場\n\n",&ba[ba_num][0],kyoku,kyoutaku);
 PRINT(pl->line,9);
 printf("\n");
 
 if(pl->ri_ti==0){
  PRINT(line_dora,7);
 }else{
  PRINT(line_dora,8);
 }
 printf("\n");
 printf("────────────────────────────────────────\n");
 for(i=0;i<=44;i++){
  if(yaku_f[i]==1){
   printf("%s   %s\n",&yaku_name[i][0],&yaku_han[i][0]);
   printf("\n");
  }
 }
 if(pl->dora_num>=1){
  printf("ドラ   %d翻\n",pl->dora_num);
  printf("\n");
 }
 printf("────────────────────────────────────────\n");
 color(red);
 if(pl->han<=4){
  printf("親 %d符 %d翻  %d点\n",pl->fu,pl->han,ScoreTableLow_Ron[1][pl->han-1][(pl->fu/10)-1]);
  printf("%d",(pl->fu/10)-1);
  pl->tensuu+=ScoreTableLow_Ron[1][pl->han-1][(pl->fu/10)-1];
  (pl+1)->tensuu-=ScoreTableLow_Ron[1][pl->han-1][(pl->fu/10)-1];
 }else{
  printf("親 %d符 %d翻 ",pl->fu,pl->han);
   if(pl->han<8){
    printf("%s",&mangan[1][0]);
   }
   else if(pl->han>=8 && pl->han<11){
    printf("%s",&mangan[2][0]);
   }
   else if(pl->han>=11){
    printf("%s",&mangan[3][0]);
   }
  printf("  %d点\n",ScoreTableHigh_Ron[1][pl->han]);
  pl->tensuu+=ScoreTableHigh_Ron[1][pl->han];
  (pl+1)->tensuu-=ScoreTableHigh_Ron[1][pl->han];
 }
 color(def);
 color(green);
 printf("\n\n\n\n次のラウンドに進む場合は 0 を押してください\n");
 color(def);
 scanf("%d",&a);
 if(a==0){
  system("cls");
  GAME();
 }
 
 }
 void DORA(){
  int i;
  for(i=0;i<=2;i++){
  line_dora[i]=0;
 }
 for(i=0;i<=10;i++){
  print_dora1[i]=0;
  print_dora2[i]=0;
 }
 if(wanpai[2]==0x09 || wanpai[2]==0x19 || wanpai[2]==0x29 ){
  line_dora[0]=wanpai[2]-0x08;
 }
 else if(wanpai[2]==0x37){
  line_dora[0]=wanpai[2]-0x02;
 }
 else if(wanpai[2]==0x34){
  line_dora[0]=wanpai[2]-0x03;
 }else{
  line_dora[0]=wanpai[2]+0x01;
 }
 if(wanpai[9]==0x09 || wanpai[9]==0x19 || wanpai[9]==0x29 ){
  line_dora[1]=wanpai[9]-0x08;
 }
 else if(line_dora[1]==0x37){
  line_dora[1]=wanpai[9]-0x02;
 }
 else if(line_dora[1]==0x34){
  line_dora[1]=wanpai[9]-0x03;
 }else{
  line_dora[1]=wanpai[9]+0x01;
 }
 }
void TENPAI(){//手牌が１４枚のときにテンパイチェック
 int f=0,i,j=0,t_f=0;
 unsigned char cline[15];
 //agaripaiの初期化
 for(i=0;i<=10;i++){
  pl->agaripai[i]=0;
 }
 //kiripaiの初期化
 for(i=0;i<38;i++){
  pl->kiripai[i]=0;
 }
 //cline初期化
 for(i=0;i<=14;i++){
  cline[i]=0;
 }//手牌をclineにコピー
 for(i=0;i<=13;i++){
  cline[i]=pl->line[i];
 }
 //テンパイチェック
 for(i=1;i<38;i++){
  if((i!=0 || i!=10 || i!=20 || i!=30)){  
   cline[14]=marhjang2[i];//１５枚目にダミー牌を入れ全種類まわす
   f=AGARI(1,cline);
   if(f==1 || f==2 || f==3){    //テンパイなら
    pl->agaripai[j]=marhjang2[i];
    j++;
    t_f=1;
    f=0;
   }
  }
 }
 if(t_f==1){
  /*for(i=0;i<38;i++){
   if(pl->kiripai[i]!=1){
    printf("%d,",marhjang2[i]);
   }
  }
  for(i=0;i<38;i++){
   printf("\n%d\n",pl->kiripai[i]);
  }*/
  color(yellow);
  printf("リーチできます\n");
  printf("リーチしますか？Yes 1,NO 0\n");
  scanf("%d",&pl->ri_ti);
  if(pl->ri_ti==1){
   color(red);
   printf("リーチ！\n");
   color(def);
  }
 }
}
void SHUNTU(int *r){
 int j;
 for(j=1;j<30;j++){
  if ( r[j+0] >= 1 && r[j+1] >= 1 && r[j+2] >= 1 ) {
     r[j+0]--; r[j+1]--; r[j+2]--;
       pl->shuntu_pai[pl->shuntu][0]=marhjang2[j];
    pl->shuntu_pai[pl->shuntu][1]=marhjang2[j+1];
    pl->shuntu_pai[pl->shuntu][2]=marhjang2[j+2];
     pl->shuntu++;
     j--;
  }
 }
}
void KOUTU(int *r){
 int i;
 for(i=0;i<38;i++){
  if(r[i]>=3){
   r[i]-=3;
   pl->koutu_pai[pl->koutu][0]=marhjang2[i];
   pl->koutu_pai[pl->koutu][1]=marhjang2[i+1];
   pl->koutu_pai[pl->koutu][2]=marhjang2[i+2];
   pl->koutu++;
  }
 }
}
int AGARI(int nAdd,unsigned char *line){
 int r[38],i,j,z,n,a;
 int m[]={1,9,11,19,21,29,31,32,33,34,35,36,37};
 int f=1;
 //手配の枚数を数える
 if(nAdd==0){//あがり用のとき
  HENKAN(line,0);
 }
 if(nAdd==1){//テンパイのとき
  HENKAN(line,1);
 }
 pl->agari=0;
 //上がりチェック
 for(i=0;i<=38;i++){
  if(pl->table[i]>=2){
   for(z=0;z<2;z++){
 //rにコピー
 for(j=0;j<38;j++){
  r[j]=pl->table[j];
 }
 /*printf("手配枚数コピー");
 for(j=0;j<38;j++){
  printf("%d",r[j]);
 }
 printf("\n");*/
    r[i]-=2;
    pl->atamapai=marhjang2[i];
 for(j=0;j<4;j++){
  for(a=0;a<4;a++){
   pl->shuntu_pai[j][a]=0;
   pl->koutu_pai[j][a]=0;
  }
 }
    pl->shuntu=0;
    pl->koutu=0;
 
    if(z==0){
     KOUTU(r);
     SHUNTU(r);
    }else{
     SHUNTU(r);
     KOUTU(r);
    }
 if(nAdd==1){
  for(j=0;j<38;j++){
   if(r[j]>=1){
    pl->kiripai[j]=1;
   }
  }
 }
    n = 0;
 for(j=0;j<38;j++){
  if(r[j]>=1){
   n++;
  }
 }
 
 /*if(nAdd==1 && n<4){//テンパイ確認用
  printf("手配s");
  for(j=0;j<38;j++){
   printf("%d",r[j]);
  }
  printf("\n");
  printf("nの数%d、nAddの数%d\n",n,nAdd);
 }*/
    if ( n == nAdd ) {
         // あがりの形になった
   if( nAdd==0){
   pl->agari = 1;
   //printf("あがりですおめでとう\n");
   }
         return 1;
    }
   }
  }
 }
 //ちーといつチェック
 //rにコピー
 for(j=0;j<38;j++){
  r[j]=pl->table[j];
 }
 //ちーといつチェック
 for(j=0;j<38;j++){
  if(r[j]>=2){
   r[j]-=2;
  }
 }
 n=0;
 for(j=0;j<38;j++){
  if(r[j]>=1){
   n++;
  }
 }
 if(n==nAdd){
  pl->agari=1;
  //printf("ちーといつあがりです\n");
  return 2;
 }
 //こくしむそうチェック
 for(j=0;j<38;j++){
  r[j]=pl->table[j];
 }
 for(j=0;j<13;j++){
  if(r[m[j]]>=1){
   r[m[j]]--;
  }
  if((r[m[j]]>=1)&&(f==1)){
   r[m[j]]--;
   f=0;
  }
 }
 n=0;
 for(j=0;j<38;j++){
  if(r[j]>=1){
   n++;
  }
 }
 if(n==nAdd){
  pl->agari=1;
  //printf("こくしむそうあがりです\n");
  return 3;
 }
 return 0;
          
}
//n＝１のときはテンパイ、0のときは上がり用
void HENKAN(unsigned char *line, int n){
 int i;
 for(i=0;i<=38;i++){//初期化
  pl->table[i]=0;
 }
 for(i=0;i<14+n;i++){
  if(line[i]==0x01){
   pl->table[1]++;
  }
  else if(line[i]==0x02){
   pl->table[2]++;
  }
  else if(line[i]==0x03){
   pl->table[3]++;
  }
  else if(line[i]==0x04){
  pl->table[4]++;
  }
  else if(line[i]==0x05){
   pl->table[5]++;
  }
  else if(line[i]==0x06){
   pl->table[6]++;
  }
  else if(line[i]==0x07){
   pl->table[7]++;
  }
  else if(line[i]==0x08){
   pl->table[8]++;
  }
  else if(line[i]==0x09){
   pl->table[9]++;
  }
  else if(line[i]==0x11){
   pl->table[11]++;
  }
  else if(line[i]==0x12){
   pl->table[12]++;
  }
  else if(line[i]==0x13){
   pl->table[13]++;
  }
  else if(line[i]==0x14){
   pl->table[14]++;
  }
  else if(line[i]==0x15){
   pl->table[15]++;
  }
  else if(line[i]==0x16){
   pl->table[16]++;
  }
  else if(line[i]==0x17){
   pl->table[17]++;
  }
  else if(line[i]==0x18){
   pl->table[18]++;
  }
  else if(line[i]==0x19){
   pl->table[19]++;
  }
  else if(line[i]==0x21){
   pl->table[21]++;
  }
  else if(line[i]==0x22){
   pl->table[22]++;
  }
  else if(line[i]==0x23){
   pl->table[23]++;
  }
  else if(line[i]==0x24){
   pl->table[24]++;
  }
  else if(line[i]==0x25){
   pl->table[25]++;
  }
  else if(line[i]==0x26){
   pl->table[26]++;
  }
  else if(line[i]==0x27){
   pl->table[27]++;
  }
  else if(line[i]==0x28){
   pl->table[28]++;
  }
  else if(line[i]==0x29){
   pl->table[29]++;
  }
  else if(line[i]==0x31){
   pl->table[31]++;
  }
  else if(line[i]==0x32){
   pl->table[32]++;
  }
  else if(line[i]==0x33){
   pl->table[33]++;
  }
  else if(line[i]==0x34){
   pl->table[34]++;
  }
  else if(line[i]==0x35){
   pl->table[35]++;
  }
  else if(line[i]==0x36){
   pl->table[36]++;
  }
  else if(line[i]==0x37){
   pl->table[37]++;
  }
 }
 /*printf("手配枚数"); 
 for(i=0;i<38;i++){
  printf("%d",pl->table[i]);
 }
 printf("\n");*/
}
void AITE(){
 int ran=0,cnt=0,a=0;
 pl=member;
 pl++;
 PRINT(pl->line,2);   //CPUの手牌表示
 PRINT(pl->sutepai,3);  //CPUの捨て牌表示
 pl=member;
 PRINT(wanpai,4);   //王牌の表示
 SORT(pl->line);
 PRINT(pl->sutepai,1);
 PRINT(pl->line,5);        //とりあえず配牌の表示
 Sleep(200);
 system("cls");
 pl=member;
 pl++;
 TUMO();
 //ran=rand()%(13);
 ran=13;
 pl->sutepai[pl->sutenum]=pl->line[ran];
 pl->line[0]=0x50;
 pl->sutenum++;
  pl=member;
 pl++;
 PRINT(pl->line,6);   //CPUの手牌表示
 PRINT(pl->sutepai,3);  //CPUの捨て牌表示
 pl=member;
 PRINT(wanpai,4);   //王牌の表示
 SORT(pl->line);
 PRINT(pl->sutepai,1);
 PRINT(pl->line,5);        //とりあえず配牌の表示
 /////
 pl->line[13]=(pl+1)->sutepai[pl->sutenum-1];
 cnt=AGARI(0,pl->line);
 if(cnt==1 || cnt==2 || cnt ==3){
  color(green);
  printf("ロンできます。ロンしますか？ YES 1,NO 2\n");
 color(def);
 scanf("%d",&a);
 }
 if(a==1){
  color(red);
   printf("  ロン！\n");
   color(def);
 YAKU(cnt,1);
 SCORE(cnt,1);
 AGA_PRINT();
 kyoutaku++;
 GAME();
 }
 /////
 Sleep(200);
 system("cls");
}
void GAME(){
 int i=0,cnt=0,a,ran=0;
 pl=member;        //ポインタplとmenberの先頭を繋げた
 KYOKU_PRINT();
 INIT_SET();
 
 pl=member;
 SORT(pl->line);
 pl->line[0]=table[t_cnt++];
 SORT(pl->line);
 pl++;
 PRINT(pl->line,2);   //CPUの手牌表示
 PRINT(pl->sutepai,3);  //CPUの捨て牌表示
 pl=member;
 PRINT(wanpai,4);   //王牌の表示
 PRINT(pl->sutepai,1);
 PRINT(pl->line,0);        //とりあえず配牌の表示
 
 cnt=AGARI(0,pl->line);
 TENPAI();
 SELECT();        //最初のツモ切り
 SORT(pl->line);
 system("cls");
 AITE();
 for(i=0;i<TUMO_CNT;i++){  //牌は鳴きなしなら２１枚ツモれる。配牌で１枚ツモってるので２０枚
 
  if(pl->ri_ti==0){//リーチしてないとき
   TUMO();        //ツモる
  pl=member;
    pl++;
    PRINT(pl->line,6);   //CPUの手牌表示
 PRINT(pl->sutepai,3);  //CPUの捨て牌表示
 pl=member;
 PRINT(wanpai,4);   //王牌の表示
    PRINT(pl->sutepai,1);
    PRINT(pl->line,0);

    cnt=AGARI(0,pl->line);
   if(cnt==1 || cnt==2 || cnt==3){//あがったときぬける
    break;
   }
   TENPAI();
   SELECT();       //牌を切る
   system("cls");
     pl=member;
    pl++;
    PRINT(pl->line,6);   //CPUの手牌表示
 PRINT(pl->sutepai,3);  //CPUの捨て牌表示
 pl=member;
 SORT(pl->line);
 PRINT(wanpai,4);   //王牌の表示
    PRINT(pl->sutepai,1);
    PRINT(pl->line,5);
 Sleep(200);
   system("cls");
   AITE();
  }
  
  
  if(pl->ri_ti==1){//リーチしたとき
    TUMO();        //ツモる
  pl=member;
    pl++;
    PRINT(pl->line,6);   //CPUの手牌表示
 PRINT(pl->sutepai,3);  //CPUの捨て牌表示
 pl=member;
 PRINT(wanpai,4);   //王牌の表示
    PRINT(pl->sutepai,1);
    PRINT(pl->line,0);
    cnt=AGARI(0,pl->line);
   if(cnt==1 || cnt==2 || cnt==3){//あがったときぬける
    break;
   }
   //14枚目を自動で切る
   pl->sutepai[pl->sutenum]=pl->line[13];
   pl->line[13]=0x50;
   pl->sutenum++;
   SORT(pl->line);
   Sleep(200);
   system("cls");
   AITE();
  }
  
 }
 if(cnt==1 || cnt==2 || cnt==3 ){
  color(red);
  printf("  ツモ！\n");
  color(def);
  YAKU(cnt,0);
  SCORE(cnt,0);
 AGA_PRINT();
 kyoutaku++;
 }
 if( cnt==0 ){
  RYUUKYOKU();
 kyoutaku++;
 }
 GAME();
}
void INIT_SET(){
 int i,j;
 char y;
 pl=member;
 t_cnt=0;
 for(j=0;j<=1;j++,pl++){
  for(i=0;i<=13;i++){       //手配の配列初期化
   pl->line[i]=0;
  }
  for(i=0;i<=60;i++){       //捨配の配列初期化
   pl->sutepai[i]=0;
  }
  for(i=0;i<=250;i++){       //手配の表示配列初期化
   pl->print_line1[i]=0;
   pl->print_line2[i]=0;
  }
  for(i=0;i<=45;i++){       //役フラグの配列初期化
   yaku_f[i]=0;
  }
 pl->tumokaisuu=0;//ツモ回数初期化
  pl->ri_ti=0;   //リーチ判定初期化
  pl->sutenum=0;         //捨て牌の数初期化
  pl->han=0;
  pl->dora_num=0;
 }
 pl=member;
 for(i=0;i<=MJ_PAI;i++){  //table_num初期化
  table_num[i]=0;
 }
 srand((unsigned)time(NULL));    //乱数初期化
 for(i=0;i<MJ_PAI_FULL;i++){     //山の初期化
   y=rand()%(MJ_PAI);
   if(table_num[y]>3){
  i--;
   }else{
    table[i]=marhjang[y];
  table_num[y]++;
 }
  
 }
  for(j=0;j<=1;j++,pl++){//プレイヤー二人分格納
  for(i=t_cnt;i<=13;i++){      //配牌１４枚
   pl->line[i]=table[t_cnt];
   t_cnt++;
  }
 }
 for(i=0;i<14;i++){//王牌に格納
  wanpai[i]=table[t_cnt];
 t_cnt++;
 }
 DORA();
}
void SORT(unsigned char *line){
//昇順にソート
 int i,j;
 char work;
 for(i=0;i<13;i++){
  for(j=13;j>i;j--){
   if(line[j-1]>line[j]){
    work=line[j];
    line[j]=line[j-1];
    line[j-1]=work;
   }
  }
 }
}
void TUMO(){
 pl->line[13]=table[t_cnt];
 t_cnt++;
 pl->tumokaisuu++;
 if(pl->ri_ti==1){
  pl->tumokaisuu_ri_ti_go++;
 }
 
}
void SELECT(){
 int pai=0;
   color(green);
  printf("１牌ツモりました。\n\n");
 printf("捨てたい牌を選んで下さい。\n");
 color(def);
 scanf("%d",&pai);
 if(pai==1){
  pl->sutepai[pl->sutenum]=pl->line[0];
  pl->line[0]=0x50;
 }
 else if(pai==2){
  pl->sutepai[pl->sutenum]=pl->line[1];
  pl->line[1]=0x50;
 }
 else if(pai==3){
  pl->sutepai[pl->sutenum]=pl->line[2];
  pl->line[2]=0x50;
 }
 else if(pai==4){
  pl->sutepai[pl->sutenum]=pl->line[3];
  pl->line[3]=0x50;
 }
 else if(pai==5){
  pl->sutepai[pl->sutenum]=pl->line[4];
  pl->line[4]=0x50;
 }
 else if(pai==6){
  pl->sutepai[pl->sutenum]=pl->line[5];
  pl->line[5]=0x50;
 }
 else if(pai==7){
  pl->sutepai[pl->sutenum]=pl->line[6];
  pl->line[6]=0x50;
 }
 else if(pai==8){
  pl->sutepai[pl->sutenum]=pl->line[7];
  pl->line[7]=0x50;
 }
 else if(pai==9){
  pl->sutepai[pl->sutenum]=pl->line[8];
  pl->line[8]=0x50;
 }
 else if(pai==10){
  pl->sutepai[pl->sutenum]=pl->line[9];
  pl->line[9]=0x50;
 }
 else if(pai==11){
  pl->sutepai[pl->sutenum]=pl->line[10];
  pl->line[10]=0x50;
 }
 else if(pai==12){
  pl->sutepai[pl->sutenum]=pl->line[11];
  pl->line[11]=0x50;
 } 
 else if(pai==13){
  pl->sutepai[pl->sutenum]=pl->line[12];
  pl->line[12]=0x50;
 }
 else if(pai==0){
  pl->sutepai[pl->sutenum]=pl->line[13];
  pl->line[13]=0x50;
 }
 pl->sutenum++;
}
void KYOKU_PRINT(){
 if(kyoutaku>=1){
  printf("\n\n\n\n\n\n　　　　　　　　　　　　      %s場%d局%d本場",&ba[ba_num][0],kyoku,kyoutaku);
  color(red);
  printf("\n\n　　　　　　　　　　　　      START!!");
  color(def);
   Sleep(3000);
     system("cls");
 }else{
  printf("\n\n\n\n\n\n　　　　　　　　　　　　      %s場%d局",&ba[ba_num][0],kyoku);
  color(red);
  printf("\n\n　　　　　　　　　　　　      START!!");
  color(def);
   Sleep(3000);
     system("cls");
 }
}
void RYUUKYOKU(){
 if(kyoutaku>=1){
  printf("\n\n\n\n\n\n　　　　　　　　　　　　      %s場%d局%d本場\n\n　　　　　　　　　　　　        流局",&ba[ba_num][0],kyoku,kyoutaku);
   Sleep(5200);
     system("cls");
 }else{
  printf("\n\n\n\n\n\n　　　　　　　　　　　　      %s場%d局\n\n　　　　　　　　　　　　        流局",&ba[ba_num][0],kyoku);
   Sleep(5200);
     system("cls");
 }
}
void PRINT(unsigned char *line,unsigned int f){//f==0なら手牌の表示、1は捨て牌、2はCPUの手牌、3はCPUの捨て牌、4は王牌、5は自分の手牌13枚時、6はCPUの手牌13枚時,7はドラ,8は裏ドラ含み,9は上がり時の手牌
//牌の表示
 int i,j,MAX;
 if(f==0 || f==2 || f==9){//ループカウンタの設定
  MAX=13;
 }
 if(f==1 || f==3){
  MAX=30;
 }
 if(f==4){
  MAX=14;
 }
  if(f==5 || f==6){
  MAX=12;
 }
 if(f==7){
  MAX=1;
 }
 if(f==8){
  MAX=2;
 }
 if(f==7 || f==8){//ドラ表示
  for(i=0,j=0;j<MAX;j++){
  if(line_dora[j]==0x01){
   memcpy( &print_dora1[i],"一",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x02){
   memcpy( &print_dora1[i],"二",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x03){
   memcpy( &print_dora1[i],"三",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x04){
   memcpy( &print_dora1[i],"四",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x05){
   memcpy( &print_dora1[i],"五",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x06){
   memcpy( &print_dora1[i],"六",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x07){
   memcpy( &print_dora1[i],"七",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x08){
   memcpy( &print_dora1[i],"八",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x09){
   memcpy( &print_dora1[i],"九",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x11){
   memcpy( &print_dora1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"①",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x12){
   memcpy( &print_dora1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"②",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x13){
   memcpy( &print_dora1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"③",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x14){
   memcpy( &print_dora1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"④",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x15){
   memcpy( &print_dora1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"⑤",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x16){
   memcpy( &print_dora1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"⑥",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x17){
   memcpy( &print_dora1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"⑦",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x18){
   memcpy( &print_dora1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"⑧",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x19){
   memcpy( &print_dora1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"⑨",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x21){
   memcpy( &print_dora1[i],"１",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"策",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x22){
   memcpy( &print_dora1[i],"２",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"策",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x23){
   memcpy( &print_dora1[i],"３",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"索",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x24){
   memcpy( &print_dora1[i],"４",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"索",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x25){
   memcpy( &print_dora1[i],"５",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"索",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x26){
   memcpy( &print_dora1[i],"６",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"索",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x27){
   memcpy( &print_dora1[i],"７",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"索",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x28){
   memcpy( &print_dora1[i],"８",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"索",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x29){
   memcpy( &print_dora1[i],"９",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"索",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x31){
   memcpy( &print_dora1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"東",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x32){
   memcpy( &print_dora1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"南",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x33){
   memcpy( &print_dora1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"西",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x34){
   memcpy( &print_dora1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"北",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x35){
   memcpy( &print_dora1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"白",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x36){
   memcpy( &print_dora1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"發",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x37){
   memcpy( &print_dora1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"中",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line_dora[j]==0x50){
   memcpy( &print_dora1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_dora2[i],"　",2);
   pl->print_line2[i+2]='\0';
  }
  i=i+3;
 }
 }
 if(f==4){
  for(i=0,j=0;j<=MAX;j++){
  if(line[j]==0x01){
   memcpy( &print_wanpai1[i],"一",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x02){
   memcpy( &print_wanpai1[i],"二",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x03){
   memcpy( &print_wanpai1[i],"三",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x04){
   memcpy( &print_wanpai1[i],"四",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x05){
   memcpy( &print_wanpai1[i],"五",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x06){
   memcpy( &print_wanpai1[i],"六",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x07){
   memcpy( &print_wanpai1[i],"七",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x08){
   memcpy( &print_wanpai1[i],"八",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x09){
   memcpy( &print_wanpai1[i],"九",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x11){
   memcpy( &print_wanpai1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"①",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x12){
   memcpy( &print_wanpai1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"②",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x13){
   memcpy( &print_wanpai1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"③",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x14){
   memcpy( &print_wanpai1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"④",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x15){
   memcpy( &print_wanpai1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"⑤",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x16){
   memcpy( &print_wanpai1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"⑥",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x17){
   memcpy( &print_wanpai1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"⑦",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x18){
   memcpy( &print_wanpai1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"⑧",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x19){
   memcpy( &print_wanpai1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"⑨",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x21){
   memcpy( &print_wanpai1[i],"１",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"策",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x22){
   memcpy( &print_wanpai1[i],"２",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"策",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x23){
   memcpy( &print_wanpai1[i],"３",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"索",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x24){
   memcpy( &print_wanpai1[i],"４",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"索",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x25){
   memcpy( &print_wanpai1[i],"５",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"索",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x26){
   memcpy( &print_wanpai1[i],"６",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"索",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x27){
   memcpy( &print_wanpai1[i],"７",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"索",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x28){
   memcpy( &print_wanpai1[i],"８",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"索",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x29){
   memcpy( &print_wanpai1[i],"９",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"索",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x31){
   memcpy( &print_wanpai1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"東",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x32){
   memcpy( &print_wanpai1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"南",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x33){
   memcpy( &print_wanpai1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"西",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x34){
   memcpy( &print_wanpai1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"北",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x35){
   memcpy( &print_wanpai1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"白",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x36){
   memcpy( &print_wanpai1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"發",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x37){
   memcpy( &print_wanpai1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"中",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x50){
   memcpy( &print_wanpai1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &print_wanpai2[i],"　",2);
   pl->print_line2[i+2]='\0';
  }
  i=i+3;
 }
 }
 if(f==0 || f==1 || f==2 || f==3 || f==5 || f==6 || f==9){//王牌以外のとき
 for(i=0,j=0;j<=MAX;j++){
  if(line[j]==0x01){
   memcpy( &pl->print_line1[i],"一",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x02){
   memcpy( &pl->print_line1[i],"二",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x03){
   memcpy( &pl->print_line1[i],"三",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x04){
   memcpy( &pl->print_line1[i],"四",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x05){
   memcpy( &pl->print_line1[i],"五",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x06){
   memcpy( &pl->print_line1[i],"六",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x07){
   memcpy( &pl->print_line1[i],"七",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x08){
   memcpy( &pl->print_line1[i],"八",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x09){
   memcpy( &pl->print_line1[i],"九",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"萬",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x11){
   memcpy( &pl->print_line1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"①",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x12){
   memcpy( &pl->print_line1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"②",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x13){
   memcpy( &pl->print_line1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"③",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x14){
   memcpy( &pl->print_line1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"④",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x15){
   memcpy( &pl->print_line1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"⑤",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x16){
   memcpy( &pl->print_line1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"⑥",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x17){
   memcpy( &pl->print_line1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"⑦",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x18){
   memcpy( &pl->print_line1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"⑧",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x19){
   memcpy( &pl->print_line1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"⑨",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x21){
   memcpy( &pl->print_line1[i],"１",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"策",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x22){
   memcpy( &pl->print_line1[i],"２",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"策",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x23){
   memcpy( &pl->print_line1[i],"３",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"索",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x24){
   memcpy( &pl->print_line1[i],"４",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"索",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x25){
   memcpy( &pl->print_line1[i],"５",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"索",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x26){
   memcpy( &pl->print_line1[i],"６",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"索",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x27){
   memcpy( &pl->print_line1[i],"７",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"索",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x28){
   memcpy( &pl->print_line1[i],"８",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"索",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x29){
   memcpy( &pl->print_line1[i],"９",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"索",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x31){
   memcpy( &pl->print_line1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"東",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x32){
   memcpy( &pl->print_line1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"南",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x33){
   memcpy( &pl->print_line1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"西",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x34){
   memcpy( &pl->print_line1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"北",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x35){
   memcpy( &pl->print_line1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"白",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x36){
   memcpy( &pl->print_line1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"發",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x37){
   memcpy( &pl->print_line1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"中",2);
   pl->print_line2[i+2]='\0';
  }
  else if(line[j]==0x50){
   memcpy( &pl->print_line1[i],"　",2);
   pl->print_line1[i+2]='\0';
   memcpy( &pl->print_line2[i],"　",2);
   pl->print_line2[i+2]='\0';
  }
  i=i+3;
 }
 }
 if(f==9){//上がり時の手牌
  printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓　┏━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃　┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36],&pl->print_line1[39]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃　┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36],&pl->print_line2[39]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛　┗━┛\n");
 }
 if(f==2){//CPUの手牌のとき
   printf("────────────────────────────────────────\n");
   color(bluegreen);
  printf("CPUの手牌　%s家 %d点\n",ba[1],pl->tensuu);
  color(def);
  printf("　　　　　　　　┏━┓　┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("　　　　　　　　┃  ┃　┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃\n");
   printf("　　　　　　　　┃  ┃　┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃\n");
   printf("　　　　　　　　┗━┛　┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
 }
  if(f==5){//手牌のとき（１３枚のとき）
  color(bluegreen);
  printf("YOUの手牌　%s家　%d点\n",ba[0],pl->tensuu);
  color(def);
  color(yellow);
  printf("  1   2   3   4   5   6   7   8   9   10  11  12  13  \n");
  color(def);
  printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
    printf("────────────────────────────────────────\n");
 }
 if(f==6){//CPUの手牌（１３枚時）
   printf("────────────────────────────────────────\n");
   color(bluegreen);
  printf("CPUの手牌　%s家 %d点\n",ba[1],pl->tensuu);
  color(def);
  printf("　　　　　　　　　　　　┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("　　　　　　　　　　　　┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃\n");
   printf("　　　　　　　　　　　　┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃\n");
   printf("　　　　　　　　　　　　┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
 }
 if(f==3){//CPUの捨て牌のとき
  printf("CPUの捨て牌\n");
 if(pl->sutenum==0){
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
 }
 else if(pl->sutenum==1){
    printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┏━┓\n");
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃\n",&pl->print_line1[0]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃\n",&pl->print_line2[0]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┗━┛\n");
   }
  else if(pl->sutenum==2){
    printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┏━┳━┓\n");
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃\n",&pl->print_line1[3],&pl->print_line1[0]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃\n",&pl->print_line2[3],&pl->print_line2[0]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┗━┻━┛\n");
   }
  else if(pl->sutenum==3){
    printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┏━┳━┳━┓\n");
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃\n",&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃\n",&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┗━┻━┻━┛\n");
   }
  else if(pl->sutenum==4){
    printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┏━┳━┳━┳━┓\n");
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┗━┻━┻━┻━┛\n");
   }
  else if(pl->sutenum==5){
    printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　┏━┳━┳━┳━┳━┓\n");
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　┗━┻━┻━┻━┻━┛\n");
   }
  else if(pl->sutenum==6){
    printf("　　　　　　　　　　　　　　　　　　　　　　　　　　┏━┳━┳━┳━┳━┳━┓\n");
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　┗━┻━┻━┻━┻━┻━┛\n");
   }
  else if(pl->sutenum==7){
    printf("　　　　　　　　　　　　　　　　　　　　　　　　┏━┳━┳━┳━┳━┳━┳━┓\n");
   printf("　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　┗━┻━┻━┻━┻━┻━┻━┛\n");
   }
  else if(pl->sutenum==8){
    printf("　　　　　　　　　　　　　　　　　　　　　　┏━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("　　　　　　　　　　　　　　　　　　　　　　┗━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
  else if(pl->sutenum==9){
    printf("　　　　　　　　　　　　　　　　　　　　┏━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("　　　　　　　　　　　　　　　　　　　　┗━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
  else if(pl->sutenum==10){
    printf("　　　　　　　　　　　　　　　　　　┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("　　　　　　　　　　　　　　　　　　┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
  else if(pl->sutenum==11){
    printf("　　　　　　　　　　　　　　　　┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[30],&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[30],&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("　　　　　　　　　　　　　　　　┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
  else if(pl->sutenum==12){
    printf("　　　　　　　　　　　　　　┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[33],&pl->print_line1[30],&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[33],&pl->print_line2[30],&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("　　　　　　　　　　　　　　┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
  else if(pl->sutenum==13){
    printf("　　　　　　　　　　　　┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[36],&pl->print_line1[33],&pl->print_line1[30],&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[36],&pl->print_line2[33],&pl->print_line2[30],&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("　　　　　　　　　　　　┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
  else if(pl->sutenum==14){
    printf("　　　　　　　　　　┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[39],&pl->print_line1[36],&pl->print_line1[33],&pl->print_line1[30],&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[39],&pl->print_line2[36],&pl->print_line2[33],&pl->print_line2[30],&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("　　　　　　　　　　┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
  else if(pl->sutenum==15){
    printf("　　　　　　　　┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[42],&pl->print_line1[39],&pl->print_line1[36],&pl->print_line1[33],&pl->print_line1[30],&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[42],&pl->print_line2[39],&pl->print_line2[36],&pl->print_line2[33],&pl->print_line2[30],&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("　　　　　　　　┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
  else if(pl->sutenum==16){
    printf("　　　　　　┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[45],&pl->print_line1[42],&pl->print_line1[39],&pl->print_line1[36],&pl->print_line1[33],&pl->print_line1[30],&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[45],&pl->print_line2[42],&pl->print_line2[39],&pl->print_line2[36],&pl->print_line2[33],&pl->print_line2[30],&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("　　　　　　┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
  else if(pl->sutenum==17){
    printf("　　　　┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[48],&pl->print_line1[45],&pl->print_line1[42],&pl->print_line1[39],&pl->print_line1[36],&pl->print_line1[33],&pl->print_line1[30],&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[48],&pl->print_line2[45],&pl->print_line2[42],&pl->print_line2[39],&pl->print_line2[36],&pl->print_line2[33],&pl->print_line2[30],&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("　　　　┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
  else if(pl->sutenum==18){
    printf("　　┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[51],&pl->print_line1[48],&pl->print_line1[45],&pl->print_line1[42],&pl->print_line1[39],&pl->print_line1[36],&pl->print_line1[33],&pl->print_line1[30],&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[51],&pl->print_line2[48],&pl->print_line2[45],&pl->print_line2[42],&pl->print_line2[39],&pl->print_line2[36],&pl->print_line2[33],&pl->print_line2[30],&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("　　┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
  else if(pl->sutenum==19){
    printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[54],&pl->print_line1[51],&pl->print_line1[48],&pl->print_line1[45],&pl->print_line1[42],&pl->print_line1[39],&pl->print_line1[36],&pl->print_line1[33],&pl->print_line1[30],&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[54],&pl->print_line2[51],&pl->print_line2[48],&pl->print_line2[45],&pl->print_line2[42],&pl->print_line2[39],&pl->print_line2[36],&pl->print_line2[33],&pl->print_line2[30],&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
   else if(pl->sutenum==20){
    printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┏━┓\n");
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃\n",&pl->print_line1[57]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃\n",&pl->print_line2[57]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┗━┛\n");
    printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[54],&pl->print_line1[51],&pl->print_line1[48],&pl->print_line1[45],&pl->print_line1[42],&pl->print_line1[39],&pl->print_line1[36],&pl->print_line1[33],&pl->print_line1[30],&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[54],&pl->print_line2[51],&pl->print_line2[48],&pl->print_line2[45],&pl->print_line2[42],&pl->print_line2[39],&pl->print_line2[36],&pl->print_line2[33],&pl->print_line2[30],&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
     else if(pl->sutenum==21){
       printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┏━┳━┓\n");
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃\n",&pl->print_line1[60],&pl->print_line1[57]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃\n",&pl->print_line2[60],&pl->print_line2[57]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┗━┻━┛\n");
    printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[54],&pl->print_line1[51],&pl->print_line1[48],&pl->print_line1[45],&pl->print_line1[42],&pl->print_line1[39],&pl->print_line1[36],&pl->print_line1[33],&pl->print_line1[30],&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[54],&pl->print_line2[51],&pl->print_line2[48],&pl->print_line2[45],&pl->print_line2[42],&pl->print_line2[39],&pl->print_line2[36],&pl->print_line2[33],&pl->print_line2[30],&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
   else if(pl->sutenum==22){
     printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┏━┳━┳━┓\n");
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃\n",&pl->print_line1[63],&pl->print_line1[60],&pl->print_line1[57]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃\n",&pl->print_line2[63],&pl->print_line2[60],&pl->print_line2[57]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┗━┻━┻━┛\n");
    printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[54],&pl->print_line1[51],&pl->print_line1[48],&pl->print_line1[45],&pl->print_line1[42],&pl->print_line1[39],&pl->print_line1[36],&pl->print_line1[33],&pl->print_line1[30],&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[54],&pl->print_line2[51],&pl->print_line2[48],&pl->print_line2[45],&pl->print_line2[42],&pl->print_line2[39],&pl->print_line2[36],&pl->print_line2[33],&pl->print_line2[30],&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
   else if(pl->sutenum==23){
    printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┏━┳━┳━┳━┓\n");
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[66],&pl->print_line1[63],&pl->print_line1[60],&pl->print_line1[57]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[66],&pl->print_line2[63],&pl->print_line2[60],&pl->print_line2[57]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　┗━┻━┻━┻━┛\n");
    printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[54],&pl->print_line1[51],&pl->print_line1[48],&pl->print_line1[45],&pl->print_line1[42],&pl->print_line1[39],&pl->print_line1[36],&pl->print_line1[33],&pl->print_line1[30],&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[54],&pl->print_line2[51],&pl->print_line2[48],&pl->print_line2[45],&pl->print_line2[42],&pl->print_line2[39],&pl->print_line2[36],&pl->print_line2[33],&pl->print_line2[30],&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
   else if(pl->sutenum==24){
    printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　┏━┳━┳━┳━┳━┓\n");
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[69],&pl->print_line1[66],&pl->print_line1[63],&pl->print_line1[60],&pl->print_line1[57]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[69],&pl->print_line2[66],&pl->print_line2[63],&pl->print_line2[60],&pl->print_line2[57]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　┗━┻━┻━┻━┻━┛\n");
    printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[54],&pl->print_line1[51],&pl->print_line1[48],&pl->print_line1[45],&pl->print_line1[42],&pl->print_line1[39],&pl->print_line1[36],&pl->print_line1[33],&pl->print_line1[30],&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[54],&pl->print_line2[51],&pl->print_line2[48],&pl->print_line2[45],&pl->print_line2[42],&pl->print_line2[39],&pl->print_line2[36],&pl->print_line2[33],&pl->print_line2[30],&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
   else if(pl->sutenum==25){
    printf("　　　　　　　　　　　　　　　　　　　　　　　　　　┏━┳━┳━┳━┳━┳━┓\n");
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[72],&pl->print_line1[69],&pl->print_line1[66],&pl->print_line1[63],&pl->print_line1[60],&pl->print_line1[57]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[72],&pl->print_line2[69],&pl->print_line2[66],&pl->print_line2[63],&pl->print_line2[60],&pl->print_line2[57]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　　　┗━┻━┻━┻━┻━┻━┛\n");
    printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[54],&pl->print_line1[51],&pl->print_line1[48],&pl->print_line1[45],&pl->print_line1[42],&pl->print_line1[39],&pl->print_line1[36],&pl->print_line1[33],&pl->print_line1[30],&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[54],&pl->print_line2[51],&pl->print_line2[48],&pl->print_line2[45],&pl->print_line2[42],&pl->print_line2[39],&pl->print_line2[36],&pl->print_line2[33],&pl->print_line2[30],&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
   else if(pl->sutenum==26){
    printf("　　　　　　　　　　　　　　　　　　　　　　　　┏━┳━┳━┳━┳━┳━┳━┓\n");
   printf("　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[75],&pl->print_line1[72],&pl->print_line1[69],&pl->print_line1[66],&pl->print_line1[63],&pl->print_line1[60],&pl->print_line1[57]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[75],&pl->print_line2[72],&pl->print_line2[69],&pl->print_line2[66],&pl->print_line2[63],&pl->print_line2[60],&pl->print_line2[57]);
   printf("　　　　　　　　　　　　　　　　　　　　　　　　┗━┻━┻━┻━┻━┻━┻━┛\n");
    printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[54],&pl->print_line1[51],&pl->print_line1[48],&pl->print_line1[45],&pl->print_line1[42],&pl->print_line1[39],&pl->print_line1[36],&pl->print_line1[33],&pl->print_line1[30],&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[54],&pl->print_line2[51],&pl->print_line2[48],&pl->print_line2[45],&pl->print_line2[42],&pl->print_line2[39],&pl->print_line2[36],&pl->print_line2[33],&pl->print_line2[30],&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
   else if(pl->sutenum==27){
    printf("　　　　　　　　　　　　　　　　　　　　　　┏━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[78],&pl->print_line1[75],&pl->print_line1[72],&pl->print_line1[69],&pl->print_line1[66],&pl->print_line1[63],&pl->print_line1[60],&pl->print_line1[57]);
   printf("　　　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[78],&pl->print_line2[75],&pl->print_line2[72],&pl->print_line2[69],&pl->print_line2[66],&pl->print_line2[63],&pl->print_line2[60],&pl->print_line2[57]);
   printf("　　　　　　　　　　　　　　　　　　　　　　┗━┻━┻━┻━┻━┻━┻━┻━┛\n");
    printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[54],&pl->print_line1[51],&pl->print_line1[48],&pl->print_line1[45],&pl->print_line1[42],&pl->print_line1[39],&pl->print_line1[36],&pl->print_line1[33],&pl->print_line1[30],&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[54],&pl->print_line2[51],&pl->print_line2[48],&pl->print_line2[45],&pl->print_line2[42],&pl->print_line2[39],&pl->print_line2[36],&pl->print_line2[33],&pl->print_line2[30],&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
   else if(pl->sutenum==28){
    printf("　　　　　　　　　　　　　　　　　　　　┏━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[81],&pl->print_line1[78],&pl->print_line1[75],&pl->print_line1[72],&pl->print_line1[69],&pl->print_line1[66],&pl->print_line1[63],&pl->print_line1[60],&pl->print_line1[57]);
   printf("　　　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[81],&pl->print_line2[78],&pl->print_line2[75],&pl->print_line2[72],&pl->print_line2[69],&pl->print_line2[66],&pl->print_line2[63],&pl->print_line2[60],&pl->print_line2[57]);
   printf("　　　　　　　　　　　　　　　　　　　　┗━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
    printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[54],&pl->print_line1[51],&pl->print_line1[48],&pl->print_line1[45],&pl->print_line1[42],&pl->print_line1[39],&pl->print_line1[36],&pl->print_line1[33],&pl->print_line1[30],&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[54],&pl->print_line2[51],&pl->print_line2[48],&pl->print_line2[45],&pl->print_line2[42],&pl->print_line2[39],&pl->print_line2[36],&pl->print_line2[33],&pl->print_line2[30],&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
   else if(pl->sutenum==29){
    printf("　　　　　　　　　　　　　　　　　　┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[84],&pl->print_line1[81],&pl->print_line1[78],&pl->print_line1[75],&pl->print_line1[72],&pl->print_line1[69],&pl->print_line1[66],&pl->print_line1[63],&pl->print_line1[60],&pl->print_line1[57]);
   printf("　　　　　　　　　　　　　　　　　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[84],&pl->print_line2[81],&pl->print_line2[78],&pl->print_line2[75],&pl->print_line2[72],&pl->print_line2[69],&pl->print_line2[66],&pl->print_line2[63],&pl->print_line2[60],&pl->print_line2[57]);
   printf("　　　　　　　　　　　　　　　　　　┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
    printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[54],&pl->print_line1[51],&pl->print_line1[48],&pl->print_line1[45],&pl->print_line1[42],&pl->print_line1[39],&pl->print_line1[36],&pl->print_line1[33],&pl->print_line1[30],&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[54],&pl->print_line2[51],&pl->print_line2[48],&pl->print_line2[45],&pl->print_line2[42],&pl->print_line2[39],&pl->print_line2[36],&pl->print_line2[33],&pl->print_line2[30],&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
 /*/////////////
  else if(pl->sutenum==20){
    printf("　　┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[57],&pl->print_line1[54],&pl->print_line1[51],&pl->print_line1[48],&pl->print_line1[45],&pl->print_line1[42],&pl->print_line1[39],&pl->print_line1[36],&pl->print_line1[33],&pl->print_line1[30],&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("　　┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[57],&pl->print_line2[54],&pl->print_line2[51],&pl->print_line2[48],&pl->print_line2[45],&pl->print_line2[42],&pl->print_line2[39],&pl->print_line2[36],&pl->print_line2[33],&pl->print_line2[30],&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("　　┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }
  else if(pl->sutenum==21){
    printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[60],&pl->print_line1[57],&pl->print_line1[54],&pl->print_line1[51],&pl->print_line1[48],&pl->print_line1[45],&pl->print_line1[42],&pl->print_line1[39],&pl->print_line1[36],&pl->print_line1[33],&pl->print_line1[30],&pl->print_line1[27],&pl->print_line1[24],&pl->print_line1[21],&pl->print_line1[18],&pl->print_line1[15],&pl->print_line1[12],&pl->print_line1[9],&pl->print_line1[6],&pl->print_line1[3],&pl->print_line1[0]);
   printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[60],&pl->print_line2[57],&pl->print_line2[54],&pl->print_line2[51],&pl->print_line2[48],&pl->print_line2[45],&pl->print_line2[42],&pl->print_line2[39],&pl->print_line2[36],&pl->print_line2[33],&pl->print_line2[30],&pl->print_line2[27],&pl->print_line2[24],&pl->print_line2[21],&pl->print_line2[18],&pl->print_line2[15],&pl->print_line2[12],&pl->print_line2[9],&pl->print_line2[6],&pl->print_line2[3],&pl->print_line2[0]);
   printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
   }*//////////
 }
 if(f==4){//王牌のとき
 printf("　　　　　　　　　　　　┏━┳━┳━┳━┳━┳━┳━┓%s場%d局\n",&ba[ba_num][0],kyoku);
   printf("　　　　　　　　　　　王┃　┃　┃%s┃　┃　┃　┃　┃%d本場\n",&print_wanpai1[6],kyoutaku);
   printf("　　　　　　　　　　　牌┃　┃　┃%s┃　┃　┃　┃　┃%d巡目\n",&print_wanpai2[6],pl->tumokaisuu+1);
   printf("　　　　　　　　　　　　┗━┻━┻━┻━┻━┻━┻━┛残り%d枚\n",TUMO_CNT-(pl->tumokaisuu));
 }
 if(f==7){//ドラ表示
  printf("┏━┓\n");
  printf("┃%s┃\n",&print_dora1[0]);
  printf("┃%s┃\n",&print_dora2[0]);
  printf("┗━┛\n");
 }
 if(f==8){//裏ドラ
  printf("　┏━┓　　　　　裏┏━┓\n");
  printf("ド┃%s┃　　　　　ド┃%s┃\n",&print_dora1[0],&print_dora1[3]);
  printf("ラ┃%s┃　　　　　ラ┃%s┃\n",&print_dora2[0],&print_dora2[3]);
  printf("　┗━┛　　　　　　┗━┛\n");
 }
 if(f==0){//手牌のとき
 color(bluegreen);
  printf("YOUの手牌　%s家　%d点\n",ba[0],pl->tensuu);
  color(def);
  color(yellow);
  printf("  1   2   3   4   5   6   7   8   9   10  11  12  13      0   \n");
  color(def);
  printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓　┏━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃　┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36],&pl->print_line1[39]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃　┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36],&pl->print_line2[39]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛　┗━┛\n");
    printf("────────────────────────────────────────\n");
 }
 if(f==1){//捨て牌のとき
  printf("YOUの捨て牌\n");
  if(pl->sutenum==0){
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
 }
  else if(pl->sutenum==1){
   printf("┏━┓\n");
  printf("┃%s┃\n",&pl->print_line1[0]);
  printf("┃%s┃\n",&pl->print_line2[0]);
  printf("┗━┛\n");
  }
 else if(pl->sutenum==2){
   printf("┏━┳━┓\n");
  printf("┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3]);
  printf("┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3]);
  printf("┗━┻━┛\n");
  }
 else if(pl->sutenum==3){
   printf("┏━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6]);
  printf("┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6]);
  printf("┗━┻━┻━┛\n");
  }
 else if(pl->sutenum==4){
   printf("┏━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9]);
  printf("┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9]);
  printf("┗━┻━┻━┻━┛\n");
  }
 else if(pl->sutenum==5){
   printf("┏━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12]);
  printf("┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12]);
  printf("┗━┻━┻━┻━┻━┛\n");
  }
 else if(pl->sutenum==6){
   printf("┏━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15]);
  printf("┗━┻━┻━┻━┻━┻━┛\n");
  }
 else if(pl->sutenum==7){
   printf("┏━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18]);
  printf("┗━┻━┻━┻━┻━┻━┻━┛\n");
  }
 else if(pl->sutenum==8){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┛\n");
  }
 else if(pl->sutenum==9){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  }
 else if(pl->sutenum==10){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  }
 else if(pl->sutenum==11){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  }
 else if(pl->sutenum==12){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  }
 else if(pl->sutenum==13){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  }
 else if(pl->sutenum==14){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36],&pl->print_line1[39]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36],&pl->print_line2[39]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  }
 else if(pl->sutenum==15){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36],&pl->print_line1[39],&pl->print_line1[42]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36],&pl->print_line2[39],&pl->print_line2[42]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  }
 else if(pl->sutenum==16){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36],&pl->print_line1[39],&pl->print_line1[42],&pl->print_line1[45]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36],&pl->print_line2[39],&pl->print_line2[42],&pl->print_line2[45]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  }
 else if(pl->sutenum==17){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36],&pl->print_line1[39],&pl->print_line1[42],&pl->print_line1[45],&pl->print_line1[48]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36],&pl->print_line2[39],&pl->print_line2[42],&pl->print_line2[45],&pl->print_line2[48]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  }
 else if(pl->sutenum==18){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36],&pl->print_line1[39],&pl->print_line1[42],&pl->print_line1[45],&pl->print_line1[48],&pl->print_line1[51]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36],&pl->print_line2[39],&pl->print_line2[42],&pl->print_line2[45],&pl->print_line2[48],&pl->print_line2[51]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  }
 else if(pl->sutenum==19){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36],&pl->print_line1[39],&pl->print_line1[42],&pl->print_line1[45],&pl->print_line1[48],&pl->print_line1[51],&pl->print_line1[54]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36],&pl->print_line2[39],&pl->print_line2[42],&pl->print_line2[45],&pl->print_line2[48],&pl->print_line2[51],&pl->print_line2[54]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  }
  else if(pl->sutenum==20){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36],&pl->print_line1[39],&pl->print_line1[42],&pl->print_line1[45],&pl->print_line1[48],&pl->print_line1[51],&pl->print_line1[54]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36],&pl->print_line2[39],&pl->print_line2[42],&pl->print_line2[45],&pl->print_line2[48],&pl->print_line2[51],&pl->print_line2[54]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  printf("┏━┓\n");
  printf("┃%s┃\n",&pl->print_line1[57]);
  printf("┃%s┃\n",&pl->print_line2[57]);
  printf("┗━┛\n");
  }
  else if(pl->sutenum==21){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36],&pl->print_line1[39],&pl->print_line1[42],&pl->print_line1[45],&pl->print_line1[48],&pl->print_line1[51],&pl->print_line1[54]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36],&pl->print_line2[39],&pl->print_line2[42],&pl->print_line2[45],&pl->print_line2[48],&pl->print_line2[51],&pl->print_line2[54]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  printf("┏━┳━┓\n");
  printf("┃%s┃%s┃\n",&pl->print_line1[57],&pl->print_line1[60]);
  printf("┃%s┃%s┃\n",&pl->print_line2[57],&pl->print_line2[60]);
  printf("┗━┻━┛\n");
  }
  else if(pl->sutenum==22){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36],&pl->print_line1[39],&pl->print_line1[42],&pl->print_line1[45],&pl->print_line1[48],&pl->print_line1[51],&pl->print_line1[54]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36],&pl->print_line2[39],&pl->print_line2[42],&pl->print_line2[45],&pl->print_line2[48],&pl->print_line2[51],&pl->print_line2[54]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  printf("┏━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃\n",&pl->print_line1[57],&pl->print_line1[60],&pl->print_line1[63]);
  printf("┃%s┃%s┃%s┃\n",&pl->print_line2[57],&pl->print_line2[60],&pl->print_line2[63]);
  printf("┗━┻━┻━┛\n");
  }
  else if(pl->sutenum==23){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36],&pl->print_line1[39],&pl->print_line1[42],&pl->print_line1[45],&pl->print_line1[48],&pl->print_line1[51],&pl->print_line1[54]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36],&pl->print_line2[39],&pl->print_line2[42],&pl->print_line2[45],&pl->print_line2[48],&pl->print_line2[51],&pl->print_line2[54]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  printf("┏━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[57],&pl->print_line1[60],&pl->print_line1[63],&pl->print_line1[66]);
  printf("┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[57],&pl->print_line2[60],&pl->print_line2[63],&pl->print_line2[66]);
  printf("┗━┻━┻━┻━┛\n");
  }
  else if(pl->sutenum==24){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36],&pl->print_line1[39],&pl->print_line1[42],&pl->print_line1[45],&pl->print_line1[48],&pl->print_line1[51],&pl->print_line1[54]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36],&pl->print_line2[39],&pl->print_line2[42],&pl->print_line2[45],&pl->print_line2[48],&pl->print_line2[51],&pl->print_line2[54]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  printf("┏━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[57],&pl->print_line1[60],&pl->print_line1[63],&pl->print_line1[66],&pl->print_line1[69]);
  printf("┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[57],&pl->print_line2[60],&pl->print_line2[63],&pl->print_line2[66],&pl->print_line2[69]);
  printf("┗━┻━┻━┻━┻━┛\n");
  }
  
  else if(pl->sutenum==25){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36],&pl->print_line1[39],&pl->print_line1[42],&pl->print_line1[45],&pl->print_line1[48],&pl->print_line1[51],&pl->print_line1[54]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36],&pl->print_line2[39],&pl->print_line2[42],&pl->print_line2[45],&pl->print_line2[48],&pl->print_line2[51],&pl->print_line2[54]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  printf("┏━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[57],&pl->print_line1[60],&pl->print_line1[63],&pl->print_line1[66],&pl->print_line1[69],&pl->print_line1[72]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[57],&pl->print_line2[60],&pl->print_line2[63],&pl->print_line2[66],&pl->print_line2[69],&pl->print_line2[72]);
  printf("┗━┻━┻━┻━┻━┻━┛\n");
  }
  else if(pl->sutenum==26){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36],&pl->print_line1[39],&pl->print_line1[42],&pl->print_line1[45],&pl->print_line1[48],&pl->print_line1[51],&pl->print_line1[54]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36],&pl->print_line2[39],&pl->print_line2[42],&pl->print_line2[45],&pl->print_line2[48],&pl->print_line2[51],&pl->print_line2[54]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  printf("┏━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[57],&pl->print_line1[60],&pl->print_line1[63],&pl->print_line1[66],&pl->print_line1[69],&pl->print_line1[72],&pl->print_line1[75]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[57],&pl->print_line2[60],&pl->print_line2[63],&pl->print_line2[66],&pl->print_line2[69],&pl->print_line2[72],&pl->print_line2[75]);
  printf("┗━┻━┻━┻━┻━┻━┻━┛\n");
  }
  else if(pl->sutenum==27){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36],&pl->print_line1[39],&pl->print_line1[42],&pl->print_line1[45],&pl->print_line1[48],&pl->print_line1[51],&pl->print_line1[54]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36],&pl->print_line2[39],&pl->print_line2[42],&pl->print_line2[45],&pl->print_line2[48],&pl->print_line2[51],&pl->print_line2[54]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  printf("┏━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[57],&pl->print_line1[60],&pl->print_line1[63],&pl->print_line1[66],&pl->print_line1[69],&pl->print_line1[72],&pl->print_line1[75],&pl->print_line1[78]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[57],&pl->print_line2[60],&pl->print_line2[63],&pl->print_line2[66],&pl->print_line2[69],&pl->print_line2[72],&pl->print_line2[75],&pl->print_line2[78]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┛\n");
  }
  else if(pl->sutenum==28){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36],&pl->print_line1[39],&pl->print_line1[42],&pl->print_line1[45],&pl->print_line1[48],&pl->print_line1[51],&pl->print_line1[54]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36],&pl->print_line2[39],&pl->print_line2[42],&pl->print_line2[45],&pl->print_line2[48],&pl->print_line2[51],&pl->print_line2[54]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[57],&pl->print_line1[60],&pl->print_line1[63],&pl->print_line1[66],&pl->print_line1[69],&pl->print_line1[72],&pl->print_line1[75],&pl->print_line1[78],&pl->print_line1[81]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[57],&pl->print_line2[60],&pl->print_line2[63],&pl->print_line2[66],&pl->print_line2[69],&pl->print_line2[72],&pl->print_line2[75],&pl->print_line2[78],&pl->print_line2[81]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  }
  else if(pl->sutenum==29){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36],&pl->print_line1[39],&pl->print_line1[42],&pl->print_line1[45],&pl->print_line1[48],&pl->print_line1[51],&pl->print_line1[54]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36],&pl->print_line2[39],&pl->print_line2[42],&pl->print_line2[45],&pl->print_line2[48],&pl->print_line2[51],&pl->print_line2[54]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[57],&pl->print_line1[60],&pl->print_line1[63],&pl->print_line1[66],&pl->print_line1[69],&pl->print_line1[72],&pl->print_line1[75],&pl->print_line1[78],&pl->print_line1[81],&pl->print_line1[84]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[57],&pl->print_line2[60],&pl->print_line2[63],&pl->print_line2[66],&pl->print_line2[69],&pl->print_line2[72],&pl->print_line2[75],&pl->print_line2[78],&pl->print_line2[81],&pl->print_line2[84]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  }
  else if(pl->sutenum==30){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36],&pl->print_line1[39],&pl->print_line1[42],&pl->print_line1[45],&pl->print_line1[48],&pl->print_line1[51],&pl->print_line1[54]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36],&pl->print_line2[39],&pl->print_line2[42],&pl->print_line2[45],&pl->print_line2[48],&pl->print_line2[51],&pl->print_line2[54]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  }
  /*/////////////////////////
 else if(pl->sutenum==20){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36],&pl->print_line1[39],&pl->print_line1[42],&pl->print_line1[45],&pl->print_line1[48],&pl->print_line1[51],&pl->print_line1[54],&pl->print_line1[57]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36],&pl->print_line2[39],&pl->print_line2[42],&pl->print_line2[45],&pl->print_line2[48],&pl->print_line2[51],&pl->print_line2[54],&pl->print_line2[57]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  }
 else if(pl->sutenum==21){
   printf("┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓\n");
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line1[0],&pl->print_line1[3],&pl->print_line1[6],&pl->print_line1[9],&pl->print_line1[12],&pl->print_line1[15],&pl->print_line1[18],&pl->print_line1[21],&pl->print_line1[24],&pl->print_line1[27],&pl->print_line1[30],&pl->print_line1[33],&pl->print_line1[36],&pl->print_line1[39],&pl->print_line1[42],&pl->print_line1[45],&pl->print_line1[48],&pl->print_line1[51],&pl->print_line1[54],&pl->print_line1[57],&pl->print_line1[60]);
  printf("┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃%s┃\n",&pl->print_line2[0],&pl->print_line2[3],&pl->print_line2[6],&pl->print_line2[9],&pl->print_line2[12],&pl->print_line2[15],&pl->print_line2[18],&pl->print_line2[21],&pl->print_line2[24],&pl->print_line2[27],&pl->print_line2[30],&pl->print_line2[33],&pl->print_line2[36],&pl->print_line2[39],&pl->print_line2[42],&pl->print_line2[45],&pl->print_line2[48],&pl->print_line2[51],&pl->print_line2[54],&pl->print_line2[57],&pl->print_line2[60]);
  printf("┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛\n");
  }*/////////////////////////
  }
}
void color(int i)
{
 HANDLE hStdout;
 CONSOLE_SCREEN_BUFFER_INFO csbi;
 hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
 GetConsoleScreenBufferInfo(hStdout, &csbi);
 SetConsoleTextAttribute(hStdout, (WORD)i);
}
void START(){
 int i;
 pl=member;
 printf("\n\n\n\n\n\n　　　　　　　　　　　　   二人打ち麻雀プログラム");
 printf("\n\n\n\n\n\n　　　　　　　　　　　　   画面を最大化してください");
 for(i=0;i<=1;i++,pl++){
  pl->tensuu=25000;
 }
 kyoutaku=0;
 Sleep(5200);
   system("cls");
 
}
///////////////////////////////////////////////////////////////////////////////////////

void main(void)
{
 START();
 GAME();
 
}
/////////////////////////////////////////////////////////////////////////////////////////

 
