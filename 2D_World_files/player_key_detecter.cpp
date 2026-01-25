#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <ctime>
#include <string>
#include <cmath>
#include "basic_input.h"
#include "manu_display.h"
#include "two_dim_world.h"


extern int manu_display,manu_display,character_manu,character_posy,character_posx,character_attack,character_rush,character_jump,character_rush_time,character_direction,character_state[6];
extern int heal_potion_tick,character_health,character_maxHealth,character_heal_potion,character_moving;
extern int inventoryY,UP_control,RIGHT_control,manu_select,map_page,item[100],inven_item[100],item_type;
extern int map_monster_size[3][MAPY][MAPX];
extern int map_type,map_main[MAP_AMOUNT][MAPY][MAPX],mapi,mapj,tick;
extern void item_getting(int type),map_monster_setting();
extern int character_fighting;
extern std::string item_name[100];
extern std::string map_name[MAP_AMOUNT];


void outmanu_key(){
	int i,j,k;
	char but=_getch();
	if(but=='e'){/////////////////////////매뉴 열기 
		manu_display=30;
		for(i=MAPX-manu_display;i<=MAPX-1;i++){
			for(j=0;j<=MAPY-1;j++){
				if(i!=MAPX-manu_display&&i!=MAPX-1)
					Write(i+DISPLAY_POSX,j+DISPLAY_POSY,BLACK,BLACK," ");
				else if(i==MAPX-manu_display)
					Write(i+DISPLAY_POSX,j+DISPLAY_POSY,LIGHTGRAY,BLACK,"[");
				else if(i==MAPX-1)
					Write(i+DISPLAY_POSX,j+DISPLAY_POSY,LIGHTGRAY,BLACK,"]");
			}
		}
		///////////////메뉴 열었을 때 정보 표시 지우기 
		for(i=0;i<=4;i++)
			Write(0,MAPY+i+DISPLAY_POSY, 12,0,"                                                                          ");
		character_manu=DETECT;	
		manu();								
		}
		else if(character_state[ELECITY]<100){
		if(but=='q'){
			k=0;
			for(i=0;i<=4&&k==0;i++){
				for(j=0;j<=3&&k==0;j++){
					if(map_main[map_type][character_posy+1-j][character_posx-2+i]==CHEST){
						k=1;//상자 감지 상수 
						i-=1;
						j-=1;
					}					
				}
			}
			////////////////////////상자 상호작용 
			if(k==1){
//				Write(character_posx-2+i+DISPLAY_POSX,character_posy+1-j+DISPLAY_POSY,WHITE,BLACK,"☆");
				map_main[map_type][character_posy+1-j][character_posx-2+i]=0;
				map_main[map_type][character_posy+1-j][character_posx-1+i]=0;	
				item_getting(CHEST);	
			} 
			else if(k==0){
				//////////////////////////멥 이동 
				if((character_posx==MAPX-2&&map_type<MAP_AMOUNT-1)||(character_posx==0&&map_type>0)){
					if(character_posx==MAPX-2&&map_type<MAP_AMOUNT-1){//
						map_type+=1;
						j=0;
						for(j=MAPY-1;j>=0&&map_main[map_type][j][1]!=0;j--){
							character_posy=j-1;
						}
						character_posx=1;
					}				
					else if(character_posx==0&&map_type>0){
						map_type-=1;
						j=0;
						for(j=MAPY-1;j>=0&&map_main[map_type][j][MAPX-1]!=0;j--){
							character_posy=j-1;
						}
						character_posx=MAPX-3;	
					}
					Write(DISPLAY_POSX,0,WHITE,BLACK,"                                                           ");
					map_monster_setting();
				}
				///////////////////////////공격 
				else if(map_type!=START_POINT-8&&map_type!=START_POINT-5&&map_type!=START_POINT&&map_type!=START_POINT+7&&map_type!=START_POINT+12)
					character_attack=DETECT;
			}									
		}
		else if(but==' '&&character_rush==UNDETECT){
			if((map_main[map_type][character_posy+1][character_posx]!=0||map_main[map_type][character_posy+1][character_posx+1]!=0)&&map_main[map_type][character_posy-2][character_posx]==0&&map_main[map_type][character_posy-2][character_posx+1]==0&&character_posy>1&&character_posy<MAPY-1){
				character_jump=DETECT;		
			}	
		}
		else if((but=='A'||but=='D')&&character_rush_time<=0){
			if(but=='A'&&character_posx>0)
				character_direction=LEFT;
			else if(but=='D'&&character_posx<MAPX-2)
				character_direction=RIGHT;		
			
			character_rush=DETECT;
		}
		else if(tick%1==0){
			if(but=='w'&&heal_potion_tick==0&&character_health<character_maxHealth){
				character_heal_potion=DETECT;		
				heal_potion_tick=0;		
			}
			else if((but=='a'||but=='d')&&character_rush==UNDETECT){
				if(but=='a'&&character_posx>0){
					if((map_main[map_type][character_posy][character_posx-1]==0||map_main[map_type][character_posy][character_posx-1]>=SLIME)&&(map_main[map_type][character_posy-1][character_posx-1]==0||map_main[map_type][character_posy-1][character_posx-1]>=SLIME))
						character_posx-=1;							
					else if(map_main[map_type][character_posy][character_posx-1]>=BLOCK&&map_main[map_type][character_posy][character_posx-1]<SLIME&&map_main[map_type][character_posy-1][character_posx-1]==0&&map_main[map_type][character_posy-2][character_posx-1]==0){
						character_posx-=1;	
						character_posy-=1;	
					}
					character_direction=LEFT;
				}
				else if(but=='d'&&character_posx<MAPX-2){
					if((map_main[map_type][character_posy][character_posx+2]==0||map_main[map_type][character_posy][character_posx+2]>=SLIME)&&(map_main[map_type][character_posy-1][character_posx+2]==0||map_main[map_type][character_posy-1][character_posx+2]>=SLIME))
						character_posx+=1;					
					else if(map_main[map_type][character_posy][character_posx+2]>=BLOCK&&map_main[map_type][character_posy][character_posx+2]<SLIME&&map_main[map_type][character_posy-1][character_posx+2]==0&map_main[map_type][character_posy-2][character_posx+2]==0){
						character_posx+=1;	
						character_posy-=1;	
					}
					character_direction=RIGHT;		
				}
				if(character_moving==UNDETECT)
					character_moving=DETECT;
				else if(character_moving==DETECT)
					character_moving=UNDETECT;
			}
		}		
	}
}
void inmanu_key(){
	int i,j,k;
	char but=_getch();
	if(but=='e'){/////////////////////////매뉴 닫기  
		inventoryY=0;
		UP_control=0;
		RIGHT_control=0;
		manu_select=0;
		map_page=0;
		for(mapj=0;mapj<=MAPY-1;mapj++){
			for(mapi=MAPX-manu_display;mapi<=MAPX-1;mapi++){
				////////////////////////////////////배경 처리 
				if((map_main[map_type][mapj][mapi]==0||map_main[map_type][mapj][mapi]>=SLIME)&&map_monster_size[SIZE][mapj][mapi]==0)
					Write(mapi+DISPLAY_POSX,mapj+DISPLAY_POSY,BLACK,BLACK," ");
				else if(map_main[map_type][mapj][mapi]==BLOCK)
					Write(mapi+DISPLAY_POSX,mapj+DISPLAY_POSY,BLACK,WHITE," ");		
				else if(map_main[map_type][mapj][mapi]==VOID_BLOCK)
					Write(mapi+DISPLAY_POSX,mapj+DISPLAY_POSY,BLACK,BLACK," ");	
				else if(map_main[map_type][mapj][mapi]==CHEST)
					Write(mapi+DISPLAY_POSX,mapj+DISPLAY_POSY,WHITE,BLACK,"☏");
				else if(map_main[map_type][mapj][mapi]==MAGMA_BLOCK)
					Write(mapi+DISPLAY_POSX,mapj+DISPLAY_POSY,BLACK,WHITE,"v");
				else if(map_main[map_type][mapj][mapi]==WATER)
					Write(mapi+DISPLAY_POSX,mapj+DISPLAY_POSY,BLACK,WHITE,"~");	
			}
		}	
		////////////////메뉴 열었을 때 정보 표시 지우기 
		for(i=0;i<=4;i++)
			Write(0,MAPY+i+DISPLAY_POSY, 12,0,"                                                                          ");
		character_manu=UNDETECT;	
		manu_display=0;
	}
	else if(but=='A'||but=='D'){
		inventoryY=0;
		UP_control=0;
		RIGHT_control=0;
		map_page=0;
		for(i=MAPX-manu_display;i<=MAPX-1;i++){
			for(j=0;j<=MAPY-1;j++){
				if(i!=MAPX-manu_display&&i!=MAPX-1)
					Write(i+DISPLAY_POSX,j+DISPLAY_POSY,BLACK,BLACK," ");
				else if(i==MAPX-manu_display)
					Write(i+DISPLAY_POSX,j+DISPLAY_POSY,LIGHTGRAY,BLACK,"[");
				else if(i==MAPX-1)
					Write(i+DISPLAY_POSX,j+DISPLAY_POSY,LIGHTGRAY,BLACK,"]");
			}
		}
		for(i=0;i<=4;i++)
			Write(0,MAPY+i+DISPLAY_POSY, 12,0,"                                                                          ");
		if(but=='A'&&manu_select>0){
			manu_select-=1;
		}
		else if(but=='D'&&manu_select<SAVE){
			manu_select+=1;
		}
		if(manu_select==MAP)
			 RIGHT_control=map_type;
	}
	else if(manu_select==INVEN){			
			if(but=='w'&&UP_control>0){ 
			if(inventoryY>0&&UP_control==inventoryY)
				inventoryY-=1;
			UP_control-=1;
		}
		else if(but=='s'&&UP_control<=item_type-2&&item_type>1){//item_type
			if(inventoryY<item_type-7&&item_type>=7&&UP_control==inventoryY+6)
				inventoryY+=1;
			UP_control+=1;	
		}		
	}
	else if(manu_select==MAP){
		if(map_page==0){
			if(but=='a'&&RIGHT_control>0){ 
				RIGHT_control-=1;
			}
			else if(but=='d'&&RIGHT_control<MAP_AMOUNT-1){//item_type
				RIGHT_control+=1;
			}	
			else if(but=='q'&&RIGHT_control!=map_type&&(RIGHT_control==START_POINT-8||RIGHT_control==START_POINT-5||RIGHT_control==START_POINT||RIGHT_control==START_POINT+7||RIGHT_control==START_POINT+12)&&item[PACKAGE]>0&&character_fighting==UNDETECT){
				UP_control=0;
				map_page=1;
				for(i=MAPX-manu_display;i<=MAPX-1;i++){
					for(j=0;j<=MAPY-1;j++){
						if(i!=MAPX-manu_display&&i!=MAPX-1)
							Write(i+DISPLAY_POSX,j+DISPLAY_POSY,BLACK,BLACK," ");
						else if(i==MAPX-manu_display)
							Write(i+DISPLAY_POSX,j+DISPLAY_POSY,LIGHTGRAY,BLACK,"[");
						else if(i==MAPX-1)
							Write(i+DISPLAY_POSX,j+DISPLAY_POSY,LIGHTGRAY,BLACK,"]");
					}
				}
			}
		}
		else if(map_page==1){
			if(but=='w'&&UP_control>0){ 
				UP_control-=1;
			}
			else if(but=='s'&&UP_control<1){//item_type
				UP_control+=1;	
			}
			else if(but=='q'){
				if(UP_control==1&&but=='q'&&RIGHT_control!=map_type&&(RIGHT_control==START_POINT-8||RIGHT_control==START_POINT-5||RIGHT_control==START_POINT||RIGHT_control==START_POINT+7||RIGHT_control==START_POINT+12)&&item[PACKAGE]>0){
					map_page=0;
					for(i=MAPX-manu_display;i<=MAPX-1;i++){
						for(j=0;j<=MAPY-1;j++){
							if(i!=MAPX-manu_display&&i!=MAPX-1)
								Write(i+DISPLAY_POSX,j+DISPLAY_POSY,BLACK,BLACK," ");
							else if(i==MAPX-manu_display)
								Write(i+DISPLAY_POSX,j+DISPLAY_POSY,LIGHTGRAY,BLACK,"[");
							else if(i==MAPX-1)
								Write(i+DISPLAY_POSX,j+DISPLAY_POSY,LIGHTGRAY,BLACK,"]");
						}
					}
				}
				else if(UP_control==0&&but=='q'&&RIGHT_control!=map_type&&(RIGHT_control==START_POINT-8||RIGHT_control==START_POINT-5||RIGHT_control==START_POINT||RIGHT_control==START_POINT+7||RIGHT_control==START_POINT+12)&&item[PACKAGE]>0){
					//////////////////////////////지역 이동하기 
					map_page=0;
					inventoryY=0;
					UP_control=0;
					map_type=RIGHT_control;
					character_posx=MAPX/2-5+rand()%11;
					for(j=MAPY-1;j>=0&&map_main[map_type][j][character_posx]!=0;j--){
						character_posy=j-1;
					}		
					///////////////지역이동시 지역명 클리어 
					Write(DISPLAY_POSX,0,WHITE,BLACK,"                                                           ");
					map_monster_setting();
					RIGHT_control=0;
					manu_select=0;
					map_page=0;
					for(mapj=0;mapj<=MAPY-1;mapj++){
						for(mapi=MAPX-manu_display;mapi<=MAPX-1;mapi++){
							////////////////////////////////////배경 처리 
							if((map_main[map_type][mapj][mapi]==0||map_main[map_type][mapj][mapi]>=SLIME)&&map_monster_size[SIZE][mapj][mapi]==0)
								Write(mapi+DISPLAY_POSX,mapj+DISPLAY_POSY,BLACK,BLACK," ");
							else if(map_main[map_type][mapj][mapi]==BLOCK)
								Write(mapi+DISPLAY_POSX,mapj+DISPLAY_POSY,BLACK,WHITE," ");		
							else if(map_main[map_type][mapj][mapi]==VOID_BLOCK)
								Write(mapi+DISPLAY_POSX,mapj+DISPLAY_POSY,BLACK,BLACK," ");	
							else if(map_main[map_type][mapj][mapi]==CHEST)
								Write(mapi+DISPLAY_POSX,mapj+DISPLAY_POSY,WHITE,BLACK,"☏");
							else if(map_main[map_type][mapj][mapi]==MAGMA_BLOCK)
								Write(mapi+DISPLAY_POSX,mapj+DISPLAY_POSY,BLACK,WHITE,"v");
							else if(map_main[map_type][mapj][mapi]==WATER)
								Write(mapi+DISPLAY_POSX,mapj+DISPLAY_POSY,BLACK,WHITE,"~");	
						}
					}
					character_manu=UNDETECT;	
					manu_display=0;
					item[PACKAGE]-=1;
				}	
				////////////////메뉴 열었을 때 정보 표시 지우기 
				for(i=0;i<=4;i++)
					Write(0,MAPY+i+DISPLAY_POSY, 12,0,"                                                                          ");
			}
		}
	}
	manu();
}
