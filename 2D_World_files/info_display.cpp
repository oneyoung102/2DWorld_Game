#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <string>

#include "basic_input.h"
#include "two_dim_world.h"

using namespace std;

extern int character_heal_potion,character_heal_potion_amount,heal_potion_tick;
extern int weapon_damage[6][3],weapon_speed[3],character_weapon,weapon_statedamage[6][3];
extern int character_health, character_maxHealth,tick,character_posx,character_posy,character_level,character_xp,character_maxXp,character_direction;
extern int character_level,character_state[6];

extern double ice_state,ghost_state;
extern int map_type,map_main[MAP_AMOUNT][MAPY][MAPX],mapi,mapj,manu_display;
extern int character_rush,character_rush_time;
extern int map_monster_size[3][MAPY][MAPX],map_monster_hit[MAPY][MAPX],map_monster_health[MAPY][MAPX],map_monster_level[MAPY][MAPX], map_monster_stateTick[6][MAPY][MAPX],map_monster_state[6][MAPY][MAPX],map_monster_Maxhealth[MAPY][MAPX];
extern double map_monster_shield[6][MAPY][MAPX],map_monster_stateState[2][MAPY][MAPX];

extern string map_name[MAP_AMOUNT];
///////////////////////////////////////////////////////////////////////////////////////캐릭터 움직임
/////////////////////////////////////////플레이어 정보 표시
void character_information(){
	int state_color[6]={BROWN,LIGHTGREEN,LIGHTRED,LIGHTCYAN,LIGHTBLUE,LIGHTGRAY};
	int i,j,k;
	
	Gotoxy(DISPLAY_POSX,0);
	textcolor(WHITE,BLACK);
	cout<<"Lv "<<character_level<<" ("<<character_xp<<"/"<<character_maxXp<<")         ";
	
	char text[100];
	int length=0;
	for(i=0;i<=99;i++)
		text[i]=' ';
		
	strcpy(text,map_name[map_type].c_str());
	for(i=0;i<=99;i++){
		if(text[i]==' '&&text[i+1]==' ')
			break;
	}
	length=i-1;
	
	if(map_type!=START_POINT-5&&map_type!=START_POINT&&map_type!=START_POINT+7){
		if(character_level-1>=0&&character_level-1<10)
			length+=1;
		else if(character_level-1>=10&&character_level-1<99)
			length+=2;
		else if(character_level-1>=100&&character_level-1<1000)
			length+=3;
		if(character_level+2>0&&character_level+2<10)
			length+=1;
		else if(character_level+2>=10&&character_level+2<99)
			length+=2;
		else if(character_level+2>=100&&character_level+2<1000)
			length+=3;
		length+=6; //( ~ ) lv
		Gotoxy(DISPLAY_POSX+MAPX-length,0);
		textcolor(WHITE,BLACK);
		cout<<map_name[map_type]<<"( ";		
		if(character_level-1==0)
			cout<<character_level<<"~"<<character_level+2<<"lv )";
		else
			cout<<character_level-1<<"~"<<character_level+2<<"lv )";
	}
	else{
		length+=7;
		Gotoxy(DISPLAY_POSX+MAPX-length,0);
		textcolor(WHITE,BLACK);
		cout<<map_name[map_type]<<"(";		
		cout<<" - lv )";
	}
		
		
	
	//////////////////////////체력바 
	Gotoxy(24+DISPLAY_POSX,1);
	textcolor(12,0);
	cout<<character_health<<"/"<<character_maxHealth<<"                ";
	Write(22+DISPLAY_POSX,1,LIGHTGRAY,WHITE,"}");		
	Write(DISPLAY_POSX,1,LIGHTGRAY,WHITE,"{");
		
	for(i=0;i<=20*character_health/character_maxHealth;i++){
			Write(i+DISPLAY_POSX+1,1,0,12," ");
	}	
	for(i=20*character_health/character_maxHealth+1;i<=20;i++){
		if(i==20*character_health/character_maxHealth+1)
			Write(i+DISPLAY_POSX+1,1,RED,RED," ");
		else
			Write(i+DISPLAY_POSX+1,1,BLACK,BLACK," ");
	}
	
	
	/////////////////////////////////피하기  
	if(character_rush_time==0&&character_state[ELECITY]<100){
		Write(DISPLAY_POSX+44,2,WHITE,BROWN,"[회피]");
	}
	else if(character_state[ELECITY]>=100){
		Write(DISPLAY_POSX+44,2,WHITE,DARKGRAY,"[회피]");
	}
	else{
		Gotoxy(DISPLAY_POSX+44,2);
		textcolor(WHITE,DARKGRAY);
		cout<<"["<<character_rush_time/10<<"."<<character_rush_time%10<<"s]";
	}
	/////////////////////////////////체력 포션  
	if(character_heal_potion_amount>0&&heal_potion_tick==0&&character_state[ELECITY]<100){
		Write(DISPLAY_POSX+52,2,WHITE,LIGHTRED,"[회복]");
	}
	else{
		Write(DISPLAY_POSX+52,2,WHITE,DARKGRAY,"[회복]");
	}
	Write(DISPLAY_POSX,2,WHITE,BLACK,"〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓");
	Write(DISPLAY_POSX+50,2,WHITE,BLACK,"〓");
	Write(DISPLAY_POSX+58,2,WHITE,BLACK,"〓");
	///////////////////////////////////상태이상  
	i=0;
	for(k=POISON;k<=GHOST;k++){
		
		if(character_state[k]>=100){
			Write(i*3+DISPLAY_POSX+1,3,0,BLACK,"   ");	
			Write(i*3+DISPLAY_POSX+1,3,WHITE,state_color[k],"▣");			
			i+=1;
		}
	}
	for(k=POISON;k<=GHOST;k++){
		if(character_state[k]==0)
			Write(i*3+DISPLAY_POSX+1,3,0,BLACK,"   ");		
		else if(character_state[k]>0&&character_state[k]<100){
			Write(i*3+DISPLAY_POSX+1,3,BLACK,state_color[k],"00");		
			j=0;
			if(character_state[k]>0&&character_state[k]<10)
				j=1;
			Write_int(i*3+DISPLAY_POSX+1+j,3,BLACK,state_color[k], &character_state[k]);		
			i+=1;
		}		
	}
	for(j=0;j<=MAPX-manu_display;j++)
		Write(i*3+DISPLAY_POSX+j,3,0,BLACK," ");	
}
///////////////////////////////////////////몬스터 정보 표시  
void monster_information(int i, int j){
	string monster_name[100]={"슬라임","독성 슬라임","불꽃 슬라임","눈꽃 슬라임","전격 슬라임","암석 슬라임","현무암 골렘","화성암 골렘","얼음 골렘","정예 골렘","파이져","메커닉 파이져","베인","정예 베인","거미","여왕 거미","플로션","퀵 플로션","정예 플로션","러셔","프로스트 러셔","정예 러셔" };
	int state_color[6]={BROWN,LIGHTGREEN,LIGHTRED,LIGHTCYAN,LIGHTBLUE,LIGHTGRAY};
	Gotoxy(DISPLAY_POSX,MAPY+DISPLAY_POSY+1);
	textcolor(WHITE,0);
	cout<<monster_name[map_main[map_type][character_posy-j][character_posx-i]-10]<<" (Lv "<<map_monster_level[character_posy-j][character_posx-i]<<")        ";
						
	Gotoxy(25,MAPY+DISPLAY_POSY+2);
	textcolor(LIGHTBLUE,0);
	cout<<map_monster_health[character_posy-j][character_posx-i]<<"/"<<map_monster_Maxhealth[character_posy-j][character_posx-i]<<"   ";
		
	Write(DISPLAY_POSX,MAPY+DISPLAY_POSY+2,LIGHTGRAY,WHITE,"{");
	Write(22+DISPLAY_POSX,MAPY+DISPLAY_POSY+2,LIGHTGRAY,WHITE,"}");
		
	int k;
	for(k=0;k<=20*map_monster_health[character_posy-j][character_posx-i]/map_monster_Maxhealth[character_posy-j][character_posx-i];k++){
		Write(k+DISPLAY_POSX+1,MAPY+DISPLAY_POSY+2,0,LIGHTBLUE," ");
	}
	for(k=20*map_monster_health[character_posy-j][character_posx-i]/map_monster_Maxhealth[character_posy-j][character_posx-i]+1;k<=20;k++){
		if(k==20*map_monster_health[character_posy-j][character_posx-i]/map_monster_Maxhealth[character_posy-j][character_posx-i]+1)
			Write(k+DISPLAY_POSX+1,MAPY+DISPLAY_POSY+2,BLUE,BLUE," ");
		else
			Write(k+DISPLAY_POSX+1,MAPY+DISPLAY_POSY+2,BLACK,BLACK," ");
	}
	Write(DISPLAY_POSX,DISPLAY_POSY+3+MAPY,WHITE,BLACK,"〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓");
	/////////////////////////////////////////////////상태이상  
	int p,q;
	p=0;
	for(k=POISON;k<=GHOST;k++){
		if(map_monster_state[k][character_posy-j][character_posx-i]>=100){
			Write(p*3+DISPLAY_POSX+1,DISPLAY_POSY+4+MAPY,0,BLACK,"   ");
			Write(p*3+DISPLAY_POSX+1,DISPLAY_POSY+4+MAPY,WHITE,state_color[k],"▣");			
			p+=1;
		}
	}
	for(k=POISON;k<=GHOST;k++){
		if(map_monster_state[k][character_posy-j][character_posx-i]==0)
			Write(p*3+DISPLAY_POSX+1,DISPLAY_POSY+4+MAPY,0,BLACK,"   ");		
		else if(map_monster_state[k][character_posy-j][character_posx-i]>0&&map_monster_state[k][character_posy-j][character_posx-i]<100){
			Write(p*3+DISPLAY_POSX+1,DISPLAY_POSY+4+MAPY,BLACK,state_color[k],"00");		
			q=0;
			if(map_monster_state[k][character_posy-j][character_posx-i]>0&&map_monster_state[k][character_posy-j][character_posx-i]<10)
				q=1;
			Write_int(p*3+DISPLAY_POSX+1+q,DISPLAY_POSY+4+MAPY,BLACK,state_color[k], &map_monster_state[k][character_posy-j][character_posx-i]);		
			p+=1;
		}		
	}
	Write(p*3+DISPLAY_POSX+1,DISPLAY_POSY+4+MAPY,0,BLACK,"                            ");
	
	Write(DISPLAY_POSX+42,DISPLAY_POSY+1+MAPY,WHITE,BLACK,"약점 |                           ");
	Write(DISPLAY_POSX+42,DISPLAY_POSY+2+MAPY,WHITE,BLACK,"저항 |                         ");
	p=0;
	for(k=POISON;k<=GHOST;k++){
		if(map_monster_shield[k][character_posy-j][character_posx-i]==VERY_WEAK){
			Write(p*3+DISPLAY_POSX+49,DISPLAY_POSY+1+MAPY,state_color[k],BLACK,"◎");
			p+=1;
		}	
	}
	for(k=POISON;k<=GHOST;k++){
		if(map_monster_shield[k][character_posy-j][character_posx-i]==WEAK){
			Write(p*3+DISPLAY_POSX+49,DISPLAY_POSY+1+MAPY,state_color[k],BLACK,"○");
			p+=1;
		}
	}
	p=0;
	for(k=POISON;k<=GHOST;k++){
		if(map_monster_shield[k][character_posy-j][character_posx-i]==VERY_STRONG){
			Write(p*3+DISPLAY_POSX+49,DISPLAY_POSY+2+MAPY,state_color[k],BLACK,"◈");
			p+=1;
		}	
	}
	for(k=POISON;k<=GHOST;k++){
		if(map_monster_shield[k][character_posy-j][character_posx-i]==STRONG){
			Write(p*3+DISPLAY_POSX+49,DISPLAY_POSY+2+MAPY,state_color[k],BLACK,"◇");
			p+=1;
		}	
	}
} 
void information_display(){
	int i,j,k;
	///////////////////////////////////////////////////////////////////////////////정보 표시 
	character_information();
	
	if(character_xp>=character_maxXp){
		character_xp-=character_maxXp;
		character_level+=1;
		if(character_level%10==0)
			character_maxXp+=30;
		else 
			character_maxXp+=10;
		character_maxHealth+=10;
		character_health=character_maxHealth;
	}
		
	/////////////////////////////////////////////////적의 정보
	if(character_direction==LEFT){
		for(i=-1;i<=10;i++){
			for(j=-5;j<=5;j++){
				if(map_main[map_type][character_posy-j][character_posx-i]<=1000&&map_main[map_type][character_posy-j][character_posx-i]>=SLIME&&character_posx-i>=0&&character_posy-j>=0&&character_posy-j<=MAPY-1){
					monster_information(i,j);
					if(map_monster_health[character_posy-j][character_posx-i]<=0){
						for(i=0;i<=4;i++)
							Write(0,MAPY+i+DISPLAY_POSY, 12,0,"                                                                                  ");
					}
					i=100;
					j=100;
			 	}	
			}	
		}	
	}
	else if(character_direction==RIGHT){
		for(i=0;i>=-11;i--){
			for(j=-5;j<=5;j++){
				if(map_main[map_type][character_posy-j][character_posx-i]<=1000&&map_main[map_type][character_posy-j][character_posx-i]>=SLIME&&character_posx-i<=MAPX-1&&character_posy-j>=0&&character_posy-j<=MAPY-1){
					monster_information(i,j);
					if(map_monster_health[character_posy-j][character_posx-i]<=0){
						for(i=0;i<=4;i++)      
							Write(0,MAPY+i+DISPLAY_POSY, 12,0,"                                                                                   ");
					}    
					i=-100;
					j=100;
				}										
			}
		}
	}
	if(i==11&&j==6){
		for(i=0;i<=4;i++)
			Write(0,MAPY+i+DISPLAY_POSY, 12,0,"                                                                          ");
	}
}
