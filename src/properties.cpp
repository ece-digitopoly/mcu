#include "Property.h"
#include "global_vars.h"

void setRents(int arr[6], int a, int b, int c, int d, int e, int f){
	arr[0] = a;
	arr[1] = b;
	arr[2] = c;
	arr[3] = d;
	arr[4] = e;
	arr[5] = f;
}
void initProperties(){
	int prop_rents[6] = {0, 0, 0, 0, 0, 0};
	//Go
	PROPERTIES[0] = new Property(0);

	//Mediterranean Avenue
	setRents(prop_rents, 2, 10, 30, 90, 160, 250);
	PROPERTIES[1] = new Property(1, 0, 60, 30, 33, 50, prop_rents, 0);


	//Community Chest
	PROPERTIES[2] = new Property(2);

	//Baltic Avenue
	setRents(prop_rents, 4, 20, 60, 180, 320, 450);
	PROPERTIES[3] = new Property(3, 0, 60, 30, 33, 50, prop_rents, 0);

	//Income Tax
	PROPERTIES[4] = new Property(4);

	//Reading Railroad
	setRents(prop_rents, 0, 0, 0, 0, 0, 0);
	PROPERTIES[5] = new Property(5, 1, 200, 100, 110, 0, prop_rents, 8);

	//Central Avenue
	setRents(prop_rents, 6, 30, 90, 270, 400, 550);
	PROPERTIES[6] = new Property(6, 0, 100, 50, 55, 50, prop_rents, 1);

	//Chance
	PROPERTIES[7] = new Property(7);

	//Vermont Avenue
	setRents(prop_rents, 6, 30, 90, 270, 400, 550);
	PROPERTIES[8] = new Property(8, 0, 100, 50, 55, 50, prop_rents, 1);

	//Connecticut Avenue
	setRents(prop_rents, 8, 40, 100, 300, 450, 600);
	PROPERTIES[9] = new Property(9, 0, 120, 60, 66, 50, prop_rents, 1);

	//Jail
	PROPERTIES[10] = new Property(10);

	//St. Charles Place
	setRents(prop_rents, 10, 50, 150, 450, 620, 750);
	PROPERTIES[11] = new Property(11, 0, 140, 70, 77, 100, prop_rents, 2);

	//Electric Company
	setRents(prop_rents, 0, 0, 0, 0, 0, 0);
	PROPERTIES[12] = new Property(12, 2, 150, 75, 92, 0, prop_rents, 9);

	//States Avenue
	setRents(prop_rents, 10, 50, 150, 450, 620, 750);
	PROPERTIES[13] = new Property(13, 0, 140, 70, 77, 100, prop_rents, 2);

	//Virginia Avenue
	setRents(prop_rents, 12, 60, 180, 500, 700, 900);
	PROPERTIES[14] = new Property(14, 0, 160, 80, 88, 100, prop_rents, 2);

	//Pennsylvania Railroad
	setRents(prop_rents, 0, 0, 0, 0, 0, 0);
	PROPERTIES[15] = new Property(15, 1, 200, 100, 110, 0, prop_rents, 8);

	//St. James Places
	setRents(prop_rents, 14, 70, 200, 550, 750, 950);
	PROPERTIES[16] = new Property(16, 0, 180, 90, 99, 100, prop_rents, 3);

	//Community Chest
	PROPERTIES[17] = new Property(17);

	//Tennessee Avenue
	setRents(prop_rents, 14, 70, 200, 550, 750, 950);
	PROPERTIES[18] = new Property(18, 0, 180, 90, 99, 100, prop_rents, 3);

	//New York Avenue
	setRents(prop_rents, 16, 80, 220, 600, 800, 1000);
	PROPERTIES[19] = new Property(19, 0, 200, 100, 110, 100, prop_rents, 3);

	//Free Parking
	PROPERTIES[20] = new Property(20);

	//Kentucky Avenue
	setRents(prop_rents, 18, 90, 250, 700, 875, 1050);
	PROPERTIES[21] = new Property(21, 0, 220, 110, 121, 150, prop_rents, 4);

	//Chance
	PROPERTIES[22] = new Property(22);

	//Indiana Avenue
	setRents(prop_rents, 18, 90, 250, 700, 875, 1050);
	PROPERTIES[23] = new Property(23, 0, 220, 110, 121, 150, prop_rents, 4);

	//Illinois Avenue
	setRents(prop_rents, 20, 100, 300, 750, 925, 1100);
	PROPERTIES[24] = new Property(24, 0, 240, 120, 132, 150, prop_rents, 4);

	//B&O Railroad
	setRents(prop_rents, 0, 0, 0, 0, 0, 0);
	PROPERTIES[25] = new Property(25, 1, 200, 100, 110, 0, prop_rents, 8);

	//Atlantic Avenue
	setRents(prop_rents, 22, 110, 330, 800, 975, 1150);
	PROPERTIES[26] = new Property(26, 0, 260, 130, 143, 150, prop_rents, 5);

	//Ventnor Avenue
	setRents(prop_rents, 22, 110, 330, 800, 975, 1150);
	PROPERTIES[27] = new Property(27, 0, 260, 130, 143, 150, prop_rents, 5);

	//Water Works
	setRents(prop_rents, 0, 0, 0, 0, 0, 0);
	PROPERTIES[28] = new Property(28, 2, 150, 75, 92, 0, prop_rents, 9);

	//Marvin Gardens
	setRents(prop_rents, 24, 120, 360, 850, 1025, 1200);
	PROPERTIES[29] = new Property(29, 0, 280, 140, 154, 150, prop_rents, 5);

	//Go to Jail
	PROPERTIES[30] = new Property(30);

	//Pacific Avenue
	setRents(prop_rents, 26, 130, 390, 900, 1100, 1275);
	PROPERTIES[31] = new Property(31, 0, 300, 150, 165, 200, prop_rents, 6);

	//North Carolina Avenue
	setRents(prop_rents, 26, 130, 390, 900, 1100, 1275);
	PROPERTIES[32] = new Property(32, 0, 300, 150, 165, 200, prop_rents, 6);

	//Community Chest
	PROPERTIES[33] = new Property(33);

	//Pennsylvania Avenue
	setRents(prop_rents, 28, 150, 450, 1000, 1200, 1400);
	PROPERTIES[34] = new Property(34, 0, 320, 160, 172, 200, prop_rents, 6);

	//Short Line
	setRents(prop_rents, 0, 0, 0, 0, 0, 0);
	PROPERTIES[35] = new Property(35, 1, 200, 100, 110, 0, prop_rents, 8);

	//Chance
	PROPERTIES[36] = new Property(36);

	//Park Place
	setRents(prop_rents, 35, 175, 500, 1100, 1300, 1500);
	PROPERTIES[37] = new Property(37, 0, 350, 175, 192, 200, prop_rents, 7);

	//Luxury Tax
	PROPERTIES[38] = new Property(38);

	//Boardwalk
	setRents(prop_rents, 50, 200, 600, 1400, 1700, 2000);
	PROPERTIES[39] = new Property(39, 0, 40, 200, 210, 200, prop_rents, 7);
}
