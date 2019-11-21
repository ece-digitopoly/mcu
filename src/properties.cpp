#include "../inc/Property.h"
#include "../inc/Util.h"
#include "../inc/properties.h"

void setRents(int arr[6], int a, int b, int c, int d, int e, int f){
	arr[0] = a;
	arr[1] = b;
	arr[2] = c;
	arr[3] = d;
	arr[4] = e;
	arr[5] = f;
}

void init_properties(){
	int prop_rents[6] = {0, 0, 0, 0, 0, 0};
	//Go
	Util::properties[0] = new Property(0);

	//Mediterranean Avenue
	setRents(prop_rents, 2, 10, 30, 90, 160, 250);
	Util::properties[1] = new Property(1, 0, 60, 30, 33, 50, prop_rents, 0);


	//Community Chest
	Util::properties[2] = new Property(2);

	//Baltic Avenue
	setRents(prop_rents, 4, 20, 60, 180, 320, 450);
	Util::properties[3] = new Property(3, 0, 60, 30, 33, 50, prop_rents, 0);

	//Income Tax
	Util::properties[4] = new Property(4);

	//Reading Railroad
	setRents(prop_rents, 0, 0, 0, 0, 0, 0);
	Util::properties[5] = new Property(5, 1, 200, 100, 110, 0, prop_rents, 8);

	//Central Avenue
	setRents(prop_rents, 6, 30, 90, 270, 400, 550);
	Util::properties[6] = new Property(6, 0, 100, 50, 55, 50, prop_rents, 1);

	//Chance
	Util::properties[7] = new Property(7);

	//Vermont Avenue
	setRents(prop_rents, 6, 30, 90, 270, 400, 550);
	Util::properties[8] = new Property(8, 0, 100, 50, 55, 50, prop_rents, 1);

	//Connecticut Avenue
	setRents(prop_rents, 8, 40, 100, 300, 450, 600);
	Util::properties[9] = new Property(9, 0, 120, 60, 66, 50, prop_rents, 1);

	//Jail
	Util::properties[10] = new Property(10);

	//St. Charles Place
	setRents(prop_rents, 10, 50, 150, 450, 620, 750);
	Util::properties[11] = new Property(11, 0, 140, 70, 77, 100, prop_rents, 2);

	//Electric Company
	setRents(prop_rents, 0, 0, 0, 0, 0, 0);
	Util::properties[12] = new Property(12, 2, 150, 75, 92, 0, prop_rents, 9);

	//States Avenue
	setRents(prop_rents, 10, 50, 150, 450, 620, 750);
	Util::properties[13] = new Property(13, 0, 140, 70, 77, 100, prop_rents, 2);

	//Virginia Avenue
	setRents(prop_rents, 12, 60, 180, 500, 700, 900);
	Util::properties[14] = new Property(14, 0, 160, 80, 88, 100, prop_rents, 2);

	//Pennsylvania Railroad
	setRents(prop_rents, 0, 0, 0, 0, 0, 0);
	Util::properties[15] = new Property(15, 1, 200, 100, 110, 0, prop_rents, 8);

	//St. James Places
	setRents(prop_rents, 14, 70, 200, 550, 750, 950);
	Util::properties[16] = new Property(16, 0, 180, 90, 99, 100, prop_rents, 3);

	//Community Chest
	Util::properties[17] = new Property(17);

	//Tennessee Avenue
	setRents(prop_rents, 14, 70, 200, 550, 750, 950);
	Util::properties[18] = new Property(18, 0, 180, 90, 99, 100, prop_rents, 3);

	//New York Avenue
	setRents(prop_rents, 16, 80, 220, 600, 800, 1000);
	Util::properties[19] = new Property(19, 0, 200, 100, 110, 100, prop_rents, 3);

	//Free Parking
	Util::properties[20] = new Property(20);

	//Kentucky Avenue
	setRents(prop_rents, 18, 90, 250, 700, 875, 1050);
	Util::properties[21] = new Property(21, 0, 220, 110, 121, 150, prop_rents, 4);

	//Chance
	Util::properties[22] = new Property(22);

	//Indiana Avenue
	setRents(prop_rents, 18, 90, 250, 700, 875, 1050);
	Util::properties[23] = new Property(23, 0, 220, 110, 121, 150, prop_rents, 4);

	//Illinois Avenue
	setRents(prop_rents, 20, 100, 300, 750, 925, 1100);
	Util::properties[24] = new Property(24, 0, 240, 120, 132, 150, prop_rents, 4);

	//B&O Railroad
	setRents(prop_rents, 0, 0, 0, 0, 0, 0);
	Util::properties[25] = new Property(25, 1, 200, 100, 110, 0, prop_rents, 8);

	//Atlantic Avenue
	setRents(prop_rents, 22, 110, 330, 800, 975, 1150);
	Util::properties[26] = new Property(26, 0, 260, 130, 143, 150, prop_rents, 5);

	//Ventnor Avenue
	setRents(prop_rents, 22, 110, 330, 800, 975, 1150);
	Util::properties[27] = new Property(27, 0, 260, 130, 143, 150, prop_rents, 5);

	//Water Works
	setRents(prop_rents, 0, 0, 0, 0, 0, 0);
	Util::properties[28] = new Property(28, 2, 150, 75, 92, 0, prop_rents, 9);

	//Marvin Gardens
	setRents(prop_rents, 24, 120, 360, 850, 1025, 1200);
	Util::properties[29] = new Property(29, 0, 280, 140, 154, 150, prop_rents, 5);

	//Go to Jail
	Util::properties[30] = new Property(30);

	//Pacific Avenue
	setRents(prop_rents, 26, 130, 390, 900, 1100, 1275);
	Util::properties[31] = new Property(31, 0, 300, 150, 165, 200, prop_rents, 6);

	//North Carolina Avenue
	setRents(prop_rents, 26, 130, 390, 900, 1100, 1275);
	Util::properties[32] = new Property(32, 0, 300, 150, 165, 200, prop_rents, 6);

	//Community Chest
	Util::properties[33] = new Property(33);

	//Pennsylvania Avenue
	setRents(prop_rents, 28, 150, 450, 1000, 1200, 1400);
	Util::properties[34] = new Property(34, 0, 320, 160, 172, 200, prop_rents, 6);

	//Short Line
	setRents(prop_rents, 0, 0, 0, 0, 0, 0);
	Util::properties[35] = new Property(35, 1, 200, 100, 110, 0, prop_rents, 8);

	//Chance
	Util::properties[36] = new Property(36);

	//Park Place
	setRents(prop_rents, 35, 175, 500, 1100, 1300, 1500);
	Util::properties[37] = new Property(37, 0, 350, 175, 192, 200, prop_rents, 7);

	//Luxury Tax
	Util::properties[38] = new Property(38);

	//Boardwalk
	setRents(prop_rents, 50, 200, 600, 1400, 1700, 2000);
	Util::properties[39] = new Property(39, 0, 40, 200, 210, 200, prop_rents, 7);
}
