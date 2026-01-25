#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <string>
#include "two_dim_world.h"
#include "basic_input.h"
#include "basic_input.h"


using namespace std;

extern int inventoryY,UP_control,RIGHT_control,manu_select,map_page,item[100],inven_item[100],item_class[100],item_type,character_manu,manu_display,map_type;
extern std::string item_name[100];
extern std::string map_name[MAP_AMOUNT];
extern int character_heal_potion_amount,character_heal_potion_amountMax,character_fighting;
 
/////////////////////////////////////////인벤토리 
void manu(){
	int i,j,k;
	if(character_manu==DETECT){
//		for(i=1;i<=15;i++){
//				item[i]+=1;
//		}	
		item_type=0;
		for(i=1;i<=RUSHER_FOOT;i++){
			if(item[i]>0)
				item_type+=1;
			inven_item[i]=0;
		}
		
		
		//////////////////////매뉴 선택 
		if(manu_select==INVEN)
			Write(DISPLAY_POSX-manu_display+5+MAPX,4,WHITE,BLACK,"소지품");
		else
			Write(DISPLAY_POSX-manu_display+5+MAPX,4,DARKGRAY,BLACK,"소지품");
		if(manu_select==EQUIP)
			Write(DISPLAY_POSX-manu_display+12+MAPX,4,WHITE,BLACK,"장비");
		else
			Write(DISPLAY_POSX-manu_display+12+MAPX,4,DARKGRAY,BLACK,"장비");
		if(manu_select==MAP)
			Write(DISPLAY_POSX-manu_display+17+MAPX,4,WHITE,BLACK,"멥");
		else
			Write(DISPLAY_POSX-manu_display+17+MAPX,4,DARKGRAY,BLACK,"멥");
		if(manu_select==SAVE)
			Write(DISPLAY_POSX-manu_display+20+MAPX,4,WHITE,BLACK,"저장");
		else
			Write(DISPLAY_POSX-manu_display+20+MAPX,4,DARKGRAY,BLACK,"저장");
		
		
		////////////////////////////인벤토리 
		if(manu_select==INVEN){
			Write(DISPLAY_POSX-manu_display+2+MAPX,4+2,YELLOW,BLACK,"멜즈ⓜ :      ");
			Write_int(DISPLAY_POSX-manu_display+11+MAPX,4+2,WHITE,BLACK,&item[MELZ]);
			Write(DISPLAY_POSX-manu_display+2+MAPX,5+2,LIGHTRED,BLACK,"체력포션ð : ");
			textcolor(WHITE,BLACK);
			cout<<character_heal_potion_amount<<"/"<<character_heal_potion_amountMax; 
			
			Write(DISPLAY_POSX-manu_display+1+MAPX,6+2,LIGHTGRAY,BLACK,"o==========================o");
			if(item_type>0){	
				int word_color[100],back_color[100];
				for(i=MELZ;i<=RUSHER_FOOT;i++){
					word_color[i]=WHITE;
					back_color[i]=BLACK;
				}	
				j=0;
				for(i=POISON_LIQUID;i<=RUSHER_FOOT;i++){
					if(item[i]>0){ 
						inven_item[j]=i;
						j+=1;
					}				
				}		
				word_color[inven_item[UP_control]]=BLACK;
				back_color[inven_item[UP_control]]=WHITE;
				
				j=0;
				for(i=POISON_LIQUID;i<=RUSHER_FOOT;i++){
					if(item[i]>0){
						if(7+2+j-inventoryY>=7+2&&7+2+j-inventoryY<=13+2){         
							Write(DISPLAY_POSX-manu_display+2+MAPX,7+2+j-inventoryY,word_color[i],back_color[i],"                          ");
							
							Gotoxy(DISPLAY_POSX-manu_display+2+MAPX,7+2+j-inventoryY);
							if(item_class[i]==WHITE)
								textcolor(word_color[i],back_color[i]);
							else	
								textcolor(item_class[i],back_color[i]);
							cout<<item_name[i];
							
							textcolor(word_color[i],back_color[i]);
							cout<<" : "<<item[i];
						}
						j+=1;
					}
				}
				
	/////////////////////////아이템 설명 
				if(inven_item[UP_control]==POISON_LIQUID){
					Write(DISPLAY_POSX-manu_display+1+MAPX,16+2,WHITE,BLACK,"독성 액체(일반)            ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,18+2,WHITE,BLACK,"독슬라임, 여왕거미         ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,19+2,DARKGRAY,BLACK,"에게서 획득가능            ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,20+2,WHITE,BLACK,"                           ");		
				}
				else if(inven_item[UP_control]==MAGMA){
					Write(DISPLAY_POSX-manu_display+1+MAPX,16+2,WHITE,BLACK,"마그마(일반)               ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,18+2,WHITE,BLACK,"불꽃슬라임, 화성암 골렘,   ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,19+2,WHITE,BLACK,"파이져*                    ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,20+2,DARKGRAY,BLACK,"에게서 획득가능            ");		
				}
				else if(inven_item[UP_control]==CRYSTAL_ICE){
					Write(DISPLAY_POSX-manu_display+1+MAPX,16+2,WHITE,BLACK,"얼음 결정(일반)            ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,18+2,WHITE,BLACK,"눈꽃슬라임, 얼음 골렘,     ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,19+2,WHITE,BLACK,"프로스트 러셔              ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,20+2,DARKGRAY,BLACK,"에게서 획득가능            ");		
				}
				else if(inven_item[UP_control]==ELECTRONMAGNET){
					Write(DISPLAY_POSX-manu_display+1+MAPX,16+2,WHITE,BLACK,"전자기석(일반)             ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,18+2,WHITE,BLACK,"전격슬라임, 퀵 플로션,     ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,19+2,WHITE,BLACK,"메커닉 파이져              ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,20+2,DARKGRAY,BLACK,"에게서 획득가능            ");		
				}
				else if(inven_item[UP_control]==SOUL_STONE){
					Write(DISPLAY_POSX-manu_display+1+MAPX,16+2,WHITE,BLACK,"영혼석(일반)               ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,18+2,WHITE,BLACK,"골렘*                      ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,19+2,DARKGRAY,BLACK,"에게서 획득가능            ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,20+2,WHITE,BLACK,"                           ");		
				}
				else if(inven_item[UP_control]==SLIME_LIQUID){
					Write(DISPLAY_POSX-manu_display+1+MAPX,16+2,CYAN,BLACK,"슬라임 액체(희귀)          ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,18+2,WHITE,BLACK,"슬라임*                    ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,19+2,DARKGRAY,BLACK,"에게서 획득가능            ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,20+2,WHITE,BLACK,"                           ");		
				}
				else if(inven_item[UP_control]==GROWING_STONE){
					Write(DISPLAY_POSX-manu_display+1+MAPX,16+2,CYAN,BLACK,"빛나는 암석(희귀)          ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,18+2,WHITE,BLACK,"골렘*, 암석 슬라임, 베인*  ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,19+2,DARKGRAY,BLACK,"에게서 획득가능            ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,20+2,WHITE,BLACK,"                           ");	
				}
				else if(inven_item[UP_control]==CREATURE_LEATHER){
					Write(DISPLAY_POSX-manu_display+1+MAPX,16+2,CYAN,BLACK,"크리쳐 가죽(희귀)          ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,18+2,WHITE,BLACK,"플로션*, 러셔*, 베인*      ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,19+2,DARKGRAY,BLACK,"에게서 획득가능            ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,20+2,WHITE,BLACK,"                           ");		
				}
				else if(inven_item[UP_control]==GAS){
					Write(DISPLAY_POSX-manu_display+1+MAPX,16+2,LIGHTMAGENTA,BLACK,"휘발 가스(유일)            ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,18+2,WHITE,BLACK,"파이져*, 플로션*           ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,19+2,DARKGRAY,BLACK,"에게서 획득가능            ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,20+2,WHITE,BLACK,"                           ");		
				}
				else if(inven_item[UP_control]==OBSIDIAN){
					Write(DISPLAY_POSX-manu_display+1+MAPX,16+2,LIGHTMAGENTA,BLACK,"흑요석(유일)               ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,18+2,WHITE,BLACK,"골렘*, 암석 슬라임, 러셔*  ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,19+2,DARKGRAY,BLACK,"에게서 획득가능            ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,20+2,WHITE,BLACK,"                           ");		
				}
				else if(inven_item[UP_control]==METAL_PLYWOOD){
					Write(DISPLAY_POSX-manu_display+1+MAPX,16+2,LIGHTMAGENTA,BLACK,"금속 합판(유일)            ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,18+2,WHITE,BLACK,"골렘*, 암석 슬라임, 파이져*");
					Write(DISPLAY_POSX-manu_display+1+MAPX,19+2,DARKGRAY,BLACK,"에게서 획득가능            ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,20+2,WHITE,BLACK,"                           ");		
				}
				else if(inven_item[UP_control]==CRYSTAL){
					Write(DISPLAY_POSX-manu_display+1+MAPX,16+2,BROWN,BLACK,"수정(전설)                 ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,18+2,WHITE,BLACK,"베인, 정예*                ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,19+2,DARKGRAY,BLACK,"에게서 획득가능            ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,20+2,WHITE,BLACK,"                           ");		
				}
				else if(inven_item[UP_control]==FIZER_HEAD){
					Write(DISPLAY_POSX-manu_display+1+MAPX,16+2,BROWN,BLACK,"파이져 머리(전설)          ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,18+2,WHITE,BLACK,"파이져*                    ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,19+2,DARKGRAY,BLACK,"에게서 획득가능            ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,20+2,WHITE,BLACK,"                           ");		
				}
				else if(inven_item[UP_control]==PLOSION_POCKET){
					Write(DISPLAY_POSX-manu_display+1+MAPX,16+2,BROWN,BLACK,"플로션 주머니(전설)        ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,18+2,WHITE,BLACK,"플로션*                    ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,19+2,DARKGRAY,BLACK,"에게서 획득가능            ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,20+2,WHITE,BLACK,"                           ");		
				}
				else if(inven_item[UP_control]==RUSHER_FOOT){
					Write(DISPLAY_POSX-manu_display+1+MAPX,16+2,BROWN,BLACK,"러셔의 발(전설)            ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,18+2,WHITE,BLACK,"러셔*                      ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,19+2,DARKGRAY,BLACK,"에게서 획득가능            ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,20+2,WHITE,BLACK,"                           ");		
				}
			}
			else{
				Write(DISPLAY_POSX-manu_display+5+MAPX,10+2,LIGHTGRAY,BLACK,"(보유한 아이템 없음)");
				Write(DISPLAY_POSX-manu_display+5+MAPX,18+2,LIGHTGRAY,BLACK,"(선택한 아이템 없음)");
			}
				
			Write(DISPLAY_POSX-manu_display+1+MAPX,14+2,LIGHTGRAY,BLACK,"o==========================o");	
			Write(DISPLAY_POSX-manu_display+1+MAPX,MAPY+2+DISPLAY_POSY,WHITE,0,"w / s : 위 / 아래");
		}	
		////////////////////////////장비 
		else if(manu_select==EQUIP){ 
			
		}
		////////////////////////////지도 
		else if(manu_select==MAP){ 
			if(map_page==0){
//				item[PACKAGE]=10;
				Gotoxy(DISPLAY_POSX-manu_display+2+MAPX,6);
				textcolor(WHITE,BLACK);
				cout<<item_name[PACKAGE]<<" : "<<item[PACKAGE];
				
				Write(DISPLAY_POSX-manu_display+1+MAPX,8,LIGHTGRAY,BLACK,"o==========================o");
				Write(DISPLAY_POSX-manu_display+1+MAPX,12,LIGHTGRAY,BLACK,"o==========================o");
				Write(DISPLAY_POSX-manu_display+1+MAPX,14,LIGHTGRAY,BLACK,"                            ");
				Gotoxy(DISPLAY_POSX-manu_display+2+MAPX,14);
				textcolor(LIGHTGRAY,BLACK);
				cout<<"< ";
				if(RIGHT_control==map_type)
					textcolor(BROWN,BLACK);
				else if(RIGHT_control==START_POINT-8||RIGHT_control==START_POINT-5||RIGHT_control==START_POINT||RIGHT_control==START_POINT+7||RIGHT_control==START_POINT+12)
					textcolor(WHITE,BLACK);
				else 
					textcolor(DARKGRAY,BLACK);
				cout<<map_name[RIGHT_control];
				textcolor(LIGHTGRAY,BLACK);
				cout<<" >";
				Write(DISPLAY_POSX-manu_display+2+MAPX,15,WHITE,BLACK,"으(로) 이동하기");
				Write(DISPLAY_POSX-manu_display+1+MAPX,17,LIGHTGRAY,BLACK,"                            ");	
				if(RIGHT_control!=map_type&&(RIGHT_control==START_POINT-8||RIGHT_control==START_POINT-5||RIGHT_control==START_POINT||RIGHT_control==START_POINT+7||RIGHT_control==START_POINT+12)&&item[PACKAGE]>0&&character_fighting==UNDETECT)
					Write(DISPLAY_POSX-manu_display+2+MAPX,17,LIGHTGREEN,BLACK,"(여행자 팩 1 필요)");
				else if(character_fighting==DETECT)
					Write(DISPLAY_POSX-manu_display+2+MAPX,17,LIGHTRED,BLACK,"(전투 중에는 불가능)");
				else if(item[PACKAGE]==0)
					Write(DISPLAY_POSX-manu_display+2+MAPX,17,LIGHTRED,BLACK,"(여행자 팩 없음)");
				else
					Write(DISPLAY_POSX-manu_display+2+MAPX,17,LIGHTRED,BLACK,"(이동 불가능 지역)");
				Write(DISPLAY_POSX-manu_display+1+MAPX,19,LIGHTGRAY,BLACK,"o==========================o");
				Write(DISPLAY_POSX-manu_display+1+MAPX,MAPY+2+DISPLAY_POSY,WHITE,0,"a / d : 지역 전환");
			}
			else if(map_page==1){
				Write(DISPLAY_POSX-manu_display+1+MAPX,6,LIGHTGRAY,BLACK,"o==========================o");
				Write(DISPLAY_POSX-manu_display+1+MAPX,10,LIGHTGRAY,BLACK,"o==========================o");
				if(UP_control==0){
					Write(DISPLAY_POSX-manu_display+1+MAPX,12,BLACK,WHITE,"          이동하기          ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,14,WHITE,BLACK,"            취소            ");
				}
				else if(UP_control==1){
					Write(DISPLAY_POSX-manu_display+1+MAPX,12,WHITE,BLACK,"          이동하기          ");
					Write(DISPLAY_POSX-manu_display+1+MAPX,14,BLACK,WHITE,"            취소            ");
				}
				Write(DISPLAY_POSX-manu_display+1+MAPX,17,LIGHTRED,BLACK,"       (여행자 팩 -1)       ");
				Write(DISPLAY_POSX-manu_display+1+MAPX,19,LIGHTGRAY,BLACK,"o==========================o");
				Write(DISPLAY_POSX-manu_display+1+MAPX,MAPY+2+DISPLAY_POSY,WHITE,0,"w / s : 위 / 아래");
				Write(DISPLAY_POSX-manu_display+1+MAPX,MAPY+3+DISPLAY_POSY,WHITE,0,"q : 선택");
			}
			
		}
		////////////////////////////저장 
		else if(manu_select== SAVE){ 
		}
		Write(DISPLAY_POSX-manu_display+1+MAPX,DISPLAY_POSY+MAPY-1,LIGHTGRAY,BLACK,"o==========================o");
		Write(DISPLAY_POSX-manu_display+1+MAPX,MAPY+1+DISPLAY_POSY,WHITE,0,"A / D : 텝 전환");
	}
		
} 
