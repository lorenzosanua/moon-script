#pragma once

#include <string>
#include <stdio.h>
#include <stdlib.h>

namespace WeaponHelpers {

	
	
	int magSize(int weapon) {
		switch (weapon) {
		case 0:
			return 30; //ak
			
		case 1:
			return 30; //lr300
			
		case 2: 
			return 30; //mp5
			
		case 3: 
			return 20; //thompson
			
		case 4:
			return 24; //csmg
			
		case 5:
			return 100; //m249
			
		}
	}

	Math::Vector2* recoilTable(int weapon) {
		switch (weapon) {
		case 0:
			return RecoilTables::AK; //ak
			
		case 1:
			return RecoilTables::LR; //lr300
			
		case 2:
			return RecoilTables::MP5; //mp5
			
		 case 3:
			return RecoilTables::Thompson; //thompson
			break;
		case 4:
			return RecoilTables::CSMG; //csmg
			break;
		case 5:
			return RecoilTables::M249; //m249
			break;
		}

	}

	double weaponRepeatDelay(int weapon) {
		switch (weapon) {
		case 0:
			return 133.33333; //ak
			
		case 1:
			return 120; //lr300
			
		case 2:
			return 100; //mp5
			
		case 3:
			return 129.7777; //thompson
			
		case 4:
			return 100; //csmg
			
		case 5:
			return 120; //m249
			
		}
	}

	struct Attachment {
		double multiplier = 0.0f;
		double firerate = 0.0f;
		Attachment(double multiplier, double firerate) :
			multiplier(multiplier), firerate(firerate) {}
		
	};

	Attachment getAttachmentValues(int attachment) {
		switch (attachment) {
		case 0: //default
			return Attachment(1, 1);
			
		case 1: //silncer
			return Attachment(0.8, 1);
		}
	}

	double getScopeMulti(int scope) {
		switch (scope) {
		case 0: //default
			return 1;
		
		case 1: //8x
			return 3.83721;
			
		case 2: //16x
			return 7.65116;
			
		case 3: //simple handmade
			return 0.8;
			
		case 4: //holo
			return 1.18605;
			
		}
	}

	double getFov(int weapon, int scope, int fov) {
		
		if(scope == 0)switch (weapon) {
		case 0: //ak
			return fov;

		case 1: //lr
			return fov;

		case 2: //mp5
			return fov * 0.95f;

		case 3: //thompson
			return fov * 1.17f;

		case 4: //smg
			return fov * 1.17f;
		case 5: //m249
			return fov * 1.83f;

		}
		return fov;
	}
	

	



}