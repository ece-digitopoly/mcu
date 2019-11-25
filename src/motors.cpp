#include "../inc/motors.h"
#include "../inc/Util.h"

void init_motors(){
	//Disable both motors to start
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
}

void move_n_steps_x(int n){
	if(n == 0) return;
	if(n < 0){
		n = -n;
		//Change Dir
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	}
	//Enable Motor x
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	for(int i = 0; i < n; i++){
		HAL_Delay(822); //920 for the magnet moving bar, 960 for the wider bar motor
	}
	//Disable Motor x
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
	//Change Dir back to normal
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
}

void move_n_steps_y(int n){
	if(n == 0) return;
	if(n < 0){
		n = -n;
		//Change Dir
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	}
	//Enable Motor y
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
	for(int i = 0; i < n; i++){
		HAL_Delay(920);
	}
	//Disable Motor y
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
	//Change Dir back to normal
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
}


int get_row(int n){
	if(n < 11){
		return n;
	}
	else if(n < 21){
		return 10;
	}
	else if(n < 31){
		return 30 - n;
	}
	else{
		return 0;
	}
}

int get_row_p1(int n){
	if(n < 10){
		return n + 1;
	}
	else if(n < 21){
		return 12;
	}
	else if(n < 30){
		return 31 - n;
	}
	else{
		return 0;
	}
}

int get_col(int n){
	if(n < 11){
		return 0;
	}
	else if(n < 21){
		return n - 10;
	}
	else if(n < 31){
		return 10;
	}
	else{
		return 40 - n;
	}
}
void move_from_to(int a, int b){
	if(Util::current_player_index == 0){
		move_n_steps_x(get_row_p1(b) - get_row_p1(a));
	//	move_n_steps_y(get_col_p1(b) - get_col_p1(a));

	}
	else{
		move_n_steps_x(get_row(b) - get_row(a));
	//	move_n_steps_y(get_col(b) - get_col(a));
	}
}

void move_piece(Profile* player, int a, int b){
	if (Util::current_player_index == 1){
		move_n_steps_x(1);
		HAL_Delay(500);
		move_n_steps_y(1);
		HAL_Delay(500);
	}
	move_from_to(0, a);
	//Enable Electromagnet
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_Delay(500);
	move_from_to(a, b);
	HAL_Delay(500);
	//Disable Electromagnet
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_Delay(1000);
	move_from_to(b, 0);
	HAL_Delay(500);
	if (Util::current_player_index == 1){
		move_n_steps_x(-1);
		HAL_Delay(500);
		move_n_steps_y(-1);
		HAL_Delay(500);
	}
}
