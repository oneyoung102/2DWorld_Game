#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <ctime>
#include <string>
#include <cmath>
#include "basic_input.h"
#include "two_dim_world.h"


using namespace std;



int rush_tick=0;
int jump_block=0;
int jump_tick=0;
int attack_tick;
int attacked[MAPY][MAPX];////플레이어가 공격할 때 중복 타격 방지  

extern int character_heal_potion,character_heal_potion_amount,heal_potion_tick;
extern int weapon_damage[6][3],weapon_speed[3],character_weapon,weapon_statedamage[6][3];
extern int character_health, character_maxHealth,tick,character_posx,character_posy,character_direction,character_jump,character_critical_per,character_attack,character_hit,character_moving;
extern int character_level,character_state[6];
extern int poison_level,fire_level,poison_tick,fire_tick,ice_tick,ghost_tick,elecity_tick;
extern double ice_state,ghost_state,character_critical_damage,character_shield[6];
extern int map_type,map_main[MAP_AMOUNT][MAPY][MAPX],mapi,mapj;
extern int character_rush,character_rush_time;
extern int map_monster_size[3][MAPY][MAPX],map_monster_hit[MAPY][MAPX],map_monster_health[MAPY][MAPX], map_monster_stateTick[6][MAPY][MAPX],map_monster_state[6][MAPY][MAPX];
extern double map_monster_shield[6][MAPY][MAPX],map_monster_stateState[2][MAPY][MAPX];
extern int manu_display;






void player_potion(){
	/////////////////////////////////////////////////// 체력 포션 
	if(character_heal_potion==DETECT&&character_heal_potion_amount>0){
		heal_potion_tick+=1;
		if(heal_potion_tick%15==0){
			character_health+=character_maxHealth*0.24;
			if(character_health>character_maxHealth)
				character_health=character_maxHealth;
		}				
		if(heal_potion_tick>=41){
			heal_potion_tick=0;
			character_heal_potion_amount-=1;
			character_heal_potion=UNDETECT;
		}				
	}
}
void player_rush(){
	/////////////////////////////////////////////////// 피하기 		
	if(character_rush==DETECT&&character_rush_time<=0&&tick%2==0){
		if(rush_tick<=10){
			if(character_direction==LEFT&&character_posx>0&&(map_main[map_type][character_posy][character_posx-1]>=SLIME||map_main[map_type][character_posy][character_posx-1]==0)&&(map_main[map_type][character_posy-1][character_posx-1]>=SLIME||map_main[map_type][character_posy-1][character_posx-1]==0)){
				character_posx-=1;
			}
			else if(character_direction==RIGHT&&character_posx<MAPX-2&&(map_main[map_type][character_posy][character_posx+2]>=SLIME||map_main[map_type][character_posy][character_posx+2]==0)&&(map_main[map_type][character_posy-1][character_posx+2]>=SLIME||map_main[map_type][character_posy-1][character_posx+2]==0)){
				character_posx+=1;
			}
		}
		else{
			rush_tick=0;
			character_rush=UNDETECT;
			if(map_type!=START_POINT-8&&map_type!=START_POINT-5&&map_type!=START_POINT&&map_type!=START_POINT+7&&map_type!=START_POINT+12)
				character_rush_time=50;
			else
				character_rush_time=30;
		}
		rush_tick+=1;			
	}	
	else if(character_rush==UNDETECT){
		if(character_rush_time>0&&tick%5==0)
			character_rush_time-=1;
	}
}
void player_jump(){
	if(character_jump==DETECT){  
		jump_tick+=1;
		if(jump_tick>=jump_block*1.5+2){
			if(jump_block>=4||map_main[map_type][character_posy-2][character_posx]!=0||map_main[map_type][character_posy-2][character_posx+1]!=0||character_posy-2==0)
				character_jump=UNDETECT;
			if(character_jump==DETECT){
				character_posy-=1;
				jump_block+=1;
				jump_tick=0;	
			}				
		}	
	}
	else if(map_main[map_type][character_posy+1][character_posx]!=0&&map_main[map_type][character_posy+1][character_posx+1]!=0){
		jump_tick=0;
		jump_block=0;
	}
	else if(character_jump==UNDETECT&&(map_main[map_type][character_posy+1][character_posx]==0||map_main[map_type][character_posy+1][character_posx]>=SLIME)&&(map_main[map_type][character_posy+1][character_posx+1]==0||map_main[map_type][character_posy+1][character_posx+1]>=SLIME)){///////////하강  
		jump_tick+=1;		
		if(jump_tick>=7-jump_block*0.6){
			character_posy+=1;
			jump_tick=0;
			jump_block+=1;
		}
	}
} 
void player_model(){
	int i,j,k;
	//////////////////////////////////////////////////플레이어 디스플래이  
	if(character_hit==UNDETECT&&tick%2==0){
		///////////////////////////////////////////////////다리 움직임 	
		if(character_moving==UNDETECT){
			if(character_posx<MAPX-manu_display)
				Write(character_posx+DISPLAY_POSX,character_posy+DISPLAY_POSY,WHITE,BLACK,"]");
			if(character_posx+1<MAPX-manu_display)
				Write(character_posx+1+DISPLAY_POSX,character_posy+DISPLAY_POSY,WHITE,BLACK,"[");
				
		}
		else if(character_moving==DETECT){
			if(character_posx<MAPX-manu_display)
				Write(character_posx+DISPLAY_POSX,character_posy+DISPLAY_POSY,WHITE,BLACK,"[");
			if(character_posx+1<MAPX-manu_display)
				Write(character_posx+1+DISPLAY_POSX,character_posy+DISPLAY_POSY,WHITE,BLACK,"]");
				character_moving=UNDETECT;		
		}
		//////////////////////////////////////////////////머리 움직임  
		if(character_direction==RIGHT){
			if(character_posx<MAPX-manu_display)
				Write(character_posx+DISPLAY_POSX,character_posy-1+DISPLAY_POSY,BLACK,WHITE,"^");
			if(character_posx+1<MAPX-manu_display)
				Write(character_posx+1+DISPLAY_POSX,character_posy-1+DISPLAY_POSY,WHITE,BLACK,"@");	
		}
		else if(character_direction==LEFT){
			if(character_posx<MAPX-manu_display)
				Write(character_posx+1+DISPLAY_POSX,character_posy-1+DISPLAY_POSY,BLACK,WHITE,"^");
			if(character_posx+1<MAPX-manu_display)
				Write(character_posx+DISPLAY_POSX,character_posy-1+DISPLAY_POSY,WHITE,BLACK,"@");	
		}	
	}	
	else if(character_hit==DETECT){
		if(character_posx+1<MAPX-manu_display)
			Write(character_posx+1+DISPLAY_POSX,character_posy-1+DISPLAY_POSY,BLACK,WHITE,"^");
		if(character_posx<MAPX-manu_display)
			Write(character_posx+DISPLAY_POSX,character_posy-1+DISPLAY_POSY,BLACK,WHITE,"@");
		if(character_posx+1<MAPX-manu_display)
			Write(character_posx+1+DISPLAY_POSX,character_posy+DISPLAY_POSY,BLACK,WHITE,"[");
		if(character_posx<MAPX-manu_display)
			Write(character_posx+DISPLAY_POSX,character_posy+DISPLAY_POSY,BLACK,WHITE,"]"); 
		character_hit=UNDETECT;
	}
}
//////////////////////////////////플레이어 공격 
void character_attacking(int x,int y){
	int k;
	if(map_monster_size[SIZE][character_posy+y][character_posx+x]!=MONSTER){
		map_monster_size[SIZE][character_posy+y][character_posx+x]=REMOVE_SIGN;	
		Write(character_posx+x+DISPLAY_POSX,character_posy+y+DISPLAY_POSY,LIGHTGRAY,BLACK,"x");	
	}		
	if(map_monster_size[SIZE][character_posy+y][character_posx+x]==MONSTER){	
		int tempx,tempy;
		tempx=map_monster_size[POSX][character_posy+y][character_posx+x];
		tempy=map_monster_size[POSY][character_posy+y][character_posx+x];
		if(map_main[map_type][tempy][tempx]>=SLIME&&attacked[tempy][tempx]==UNDETECT){
			map_monster_hit[tempy][tempx]=DETECT;
			attacked[tempy][tempx]=DETECT;
			map_monster_health[tempy][tempx]-=weapon_damage[PHYSIC][character_weapon]*map_monster_shield[PHYSIC][tempy][tempx]*map_monster_stateState[GHOST_STATE][tempy][tempx]*ice_state;
			if(rand()%100<=character_critical_per)
				map_monster_health[tempy][tempx]-=weapon_damage[PHYSIC][character_weapon]*map_monster_shield[PHYSIC][tempy][tempx]*map_monster_stateState[GHOST_STATE][tempy][tempx]*ice_state*(character_critical_damage-1);
			for(k=POISON;k<=GHOST;k++){
				if(k==ICE||k==ELECITY||k==GHOST)
					map_monster_health[tempy][tempx]-=weapon_damage[k][character_weapon]*map_monster_shield[k][tempy][tempx]*map_monster_stateState[GHOST_STATE][tempy][tempx]*ice_state;
				if(map_monster_state[k][tempy][tempx]<=99)
					map_monster_state[k][tempy][tempx]+=weapon_statedamage[k][character_weapon]*map_monster_shield[k][tempy][tempx];	
			}	
			
			if(map_monster_health[tempy][tempx]<0)
				map_monster_health[tempy][tempx]=0;	
		}									
	}
}
void player_attacking(){		
	int i,j,k;	
	int axe_count;
			///////////////////////////////////////////////////공격 방식 		
	if(character_attack==DETECT){
		if(character_direction==LEFT){
			if(character_weapon==SWORD){
				if(attack_tick==weapon_speed[SWORD]){
					for(i=1;i<=5&&(map_main[map_type][character_posy-1][character_posx-i]>=SLIME||map_main[map_type][character_posy-1][character_posx-i]==0);i++){
						if((map_main[map_type][character_posy-1][character_posx-i]==0||map_main[map_type][character_posy-1][character_posx-i]>=SLIME)&&character_posx-i>=0)										
							character_attacking(-i,-1);													
					}
				}					
				else if(attack_tick>=weapon_speed[SWORD]*1.6){
					for(i=1;i<=5&&(map_main[map_type][character_posy][character_posx-i]>=SLIME||map_main[map_type][character_posy][character_posx-i]==0);i++){
						if((map_main[map_type][character_posy][character_posx-i]==0||map_main[map_type][character_posy][character_posx-i]>=SLIME)&&character_posx-i>=0)							
							character_attacking(-i,0);									
					}
				character_attack=UNDETECT;
				attack_tick=0;
				}
			}
			else if(character_weapon==AXE){
				if(attack_tick>=weapon_speed[AXE]){
					for(i=1;i<=4+axe_count%2&&(map_main[map_type][character_posy][character_posx-i]>=SLIME||map_main[map_type][character_posy][character_posx-i]==0);i++){
						if((map_main[map_type][character_posy][character_posx-i]==0||map_main[map_type][character_posy][character_posx-i]>=SLIME)&&character_posx-i>=0)										
							character_attacking(-i,0);													
					}
					for(i=1;i<=5+axe_count%2&&(map_main[map_type][character_posy-1][character_posx-i]>=SLIME||map_main[map_type][character_posy-1][character_posx-i]==0);i++){
						if((map_main[map_type][character_posy-1][character_posx-i]==0||map_main[map_type][character_posy-1][character_posx-i]>=SLIME)&&character_posx-i>=0)										
							character_attacking(-i,-1);													
					}	
					for(i=1;i<=2+axe_count%2&&(map_main[map_type][character_posy][character_posx+1+i]>=SLIME||map_main[map_type][character_posy][character_posx+1+i]==0);i++){
						if((map_main[map_type][character_posy][character_posx+1+i]==0||map_main[map_type][character_posy][character_posx+1+i]>=SLIME)&&character_posx+1+i<=MAPX-1)
							character_attacking(1+i,0);							
					}
					for(i=1;i<=3+axe_count%2&&(map_main[map_type][character_posy-1][character_posx+1+i]>=SLIME||map_main[map_type][character_posy-1][character_posx+1+i]==0);i++){
						if((map_main[map_type][character_posy-1][character_posx+1+i]==0||map_main[map_type][character_posy-1][character_posx+1+i]>=SLIME)&&character_posx+1+i<=MAPX-1)
							character_attacking(1+i,-1);							
					}
					character_attack=UNDETECT;
					attack_tick=0;
					axe_count+=1;								
				}										
			}
			else if(character_weapon==HAMMER){
				if(attack_tick>=weapon_speed[HAMMER]){
					j=0;
					for(i=3;i<=8;i++){
						for(j=0;j<=5;j++){
							if((j==5||((map_main[map_type][character_posy+j-3][character_posx-i]==0||map_main[map_type][character_posy+j-3][character_posx-i]>=SLIME)&&map_main[map_type][character_posy+j-3+1][character_posx-i]!=0&&map_main[map_type][character_posy+j-3+1][character_posx-i]<SLIME))&&character_posx-i>=0&&map_main[map_type][character_posy+j-3][character_posx-i]==0||map_main[map_type][character_posy+j-3][character_posx-i]>=SLIME){
								character_attacking(-i,j-3);
								j=6;
							}																			
						}														
					}
					character_attack=UNDETECT;
					attack_tick=0;
				}										
			}
		}
		else if(character_direction==RIGHT){
			if(character_weapon==SWORD){
				if(attack_tick==weapon_speed[SWORD]){
					for(i=1;i<=5&&(map_main[map_type][character_posy-1][character_posx+1+i]>=SLIME||map_main[map_type][character_posy-1][character_posx+1+i]==0);i++){
						if((map_main[map_type][character_posy-1][character_posx+1+i]==0||map_main[map_type][character_posy-1][character_posx+1+i]>=SLIME)&&character_posx+1+i<=MAPX-1)
							character_attacking(1+i,-1);							
					}
				}				
				else if(attack_tick>=weapon_speed[SWORD]*1.6){
					for(i=1;i<=5&&(map_main[map_type][character_posy][character_posx+1+i]>=SLIME||map_main[map_type][character_posy][character_posx+1+i]==0);i++){
						if((map_main[map_type][character_posy][character_posx+1+i]==0||map_main[map_type][character_posy][character_posx+1+i]>=SLIME)&&character_posx+1+i<=MAPX-1)
							character_attacking(1+i,0);									
					}
					character_attack=UNDETECT;
					attack_tick=0;
				}
			}
			else if(character_weapon==AXE){
				if(attack_tick>=weapon_speed[AXE]){
					for(i=1;i<=2+axe_count%2&&(map_main[map_type][character_posy][character_posx-i]>=SLIME||map_main[map_type][character_posy][character_posx-i]==0);i++){
						if((map_main[map_type][character_posy][character_posx-i]==0||map_main[map_type][character_posy][character_posx-i]>=SLIME)&&character_posx-i>=0)										
							character_attacking(-i,0);													
					}
					for(i=1;i<=3+axe_count%2&&(map_main[map_type][character_posy-1][character_posx-i]>=SLIME||map_main[map_type][character_posy-1][character_posx-i]==0);i++){
						if((map_main[map_type][character_posy-1][character_posx-i]==0||map_main[map_type][character_posy-1][character_posx-i]>=SLIME)&&character_posx-i>=0)										
							character_attacking(-i,-1);													
					}	
					for(i=1;i<=4+axe_count%2&&(map_main[map_type][character_posy][character_posx+1+i]>=SLIME||map_main[map_type][character_posy][character_posx+1+i]==0);i++){
						if((map_main[map_type][character_posy][character_posx+1+i]==0||map_main[map_type][character_posy][character_posx+1+i]>=SLIME)&&character_posx+1+i<=MAPX-1)
							character_attacking(1+i,0);							
					}
					for(i=1;i<=5+axe_count%2&&(map_main[map_type][character_posy-1][character_posx+1+i]>=SLIME||map_main[map_type][character_posy-1][character_posx+1+i]==0);i++){
						if((map_main[map_type][character_posy-1][character_posx+1+i]==0||map_main[map_type][character_posy-1][character_posx+1+i]>=SLIME)&&character_posx+1+i<=MAPX-1)
							character_attacking(1+i,-1);							
					}
					character_attack=UNDETECT;
					attack_tick=0;
					axe_count+=1;		
				}
			}
			else if(character_weapon==HAMMER){
				if(attack_tick>=weapon_speed[HAMMER]){
					j=0;
					for(i=3;i<=8;i++){
						for(j=0;j<=5;j++){
							if((j==5||((map_main[map_type][character_posy+j-3][character_posx+1+i]==0||map_main[map_type][character_posy+j-3][character_posx+1+i]>=SLIME)&&map_main[map_type][character_posy+j-3+1][character_posx+1+i]!=0&&map_main[map_type][character_posy+j-3+1][character_posx+1+i]<SLIME))&&character_posx+1+i<=MAPX-1&&(map_main[map_type][character_posy+j-3][character_posx+i+1]==0||map_main[map_type][character_posy+j-3][character_posx+1+i]>=SLIME)){
								character_attacking(1+i,j-3);
								j=6;
							}								
						}														
					}
					character_attack=UNDETECT;
					attack_tick=0;
				}										
			}
		}	
		if(character_attack==DETECT)
			attack_tick+=1;		
		for(j=0;j<=MAPY-1;j++){
			for(i=0;i<=MAPX-1;i++){	
				attacked[j][i]=UNDETECT;
			}
		}		
	}
}
////////////////////////////////////////////
void player_state(){
	int i,j,k;
	//////////////////////////////////바닥 상태이상 
	double pow_num=pow(1.095,character_level-1);
	if(map_main[map_type][character_posy+1][character_posx]==MAGMA_BLOCK&&tick%10==0){
		character_state[FIRE]+=1;
		character_hit=DETECT;
			character_health-=3*pow_num*character_shield[FIRE];
		if(character_health<0)
			character_health=0;
	}		
	else if(map_main[map_type][character_posy+1][character_posx]==WATER&&character_state[ELECITY]>=100-50*character_shield[ELECITY])
		character_state[ELECITY]=100;	
	
	///////////////////////////////////////////////////////////////////////////////원소 축척 
	if(tick%10==0){
		for(i=POISON;i<=GHOST;i++){
			if(character_state[i]<100&&character_state[i]>0)
				character_state[i]-=1;
		}
	}
	else if(character_state[i]>100)
		character_state[i]=100;
	
	pow_num=pow(1.095,poison_level-1);
	double pow_num1=pow(1.095,fire_level-1);
	
	if(character_state[POISON]>=100){
		if(poison_tick==0)
			character_health-=character_maxHealth*0.15*character_shield[POISON];
		poison_tick+=1;
		if(poison_tick%80==4){
			character_health-=pow_num*character_shield[POISON];
			character_hit=DETECT;
		}				
		else if(poison_tick>=400){
			poison_tick=0;
			character_state[POISON]=0;
			character_health+=character_maxHealth*0.1*character_shield[POISON];
			if(character_health>character_maxHealth)
				character_health=character_maxHealth;
		}		
		if(character_health<0)
			character_health=0;
	}
	if(character_state[FIRE]>=100){
		fire_tick+=1;
		if(fire_tick%62==4){
			character_health-=1.2*pow_num1*character_shield[FIRE];
			character_hit=DETECT;
		}				
		else if(fire_tick>=500){
			fire_tick=0;
			character_state[FIRE]=0;
			character_health-=15*pow_num*character_shield[FIRE];
		}
		if(character_health<0)
			character_health=0;
	}
	if(character_state[ICE]>=100){
		ice_tick+=1;
		ice_state=0.5*character_shield[ICE];
		if(ice_tick>=500*character_shield[ICE]){
			ice_tick=0;
			character_state[ICE]=0;
			ice_state=1;
		}
	}
	if(character_state[ELECITY]>=100){
		elecity_tick+=1;
		if(elecity_tick>=300*character_shield[ELECITY]){
			elecity_tick=0;
			character_state[ELECITY]=0;
		}
	}
	if(character_state[GHOST]>=100){
		ghost_tick+=1;
		ghost_state=1.3*character_shield[GHOST];
		if(ghost_tick>=500*character_shield[GHOST]){
			ghost_tick=0;
			character_state[GHOST]=0;
			ghost_state=1;
		}
	}
}

