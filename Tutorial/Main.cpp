#pragma once
#include <iostream>
#include <conio.h>

class Stat {
public:
	const int statTypeCount = 4;
	std::string arrStatName[4] = { "HP", "MP", "공격력", "방어력" };		// 스탯 이름 관리 배열
	int arrStatValue[4] = { 50,50,0,0 };		// 스탯 관리 배열
	size_t level = 1;		// 레벨

	void PrintStat(void) {
		std::cout << "----------------- 스텟 정보 ----------------------" << std::endl;
		std::cout << "Level : " << level << std::endl;
		for (int i = 0; i < statTypeCount; ++i) {
			std::cout << arrStatName[i] << " : " << arrStatValue[i] << std::endl;
		}
		std::cout << " --------------------------------------------------" << std::endl;
	}
};

class Inventory {
public:
	const int potionTypeCount = 2;
	std::string arrPotionName[2] = { "HP Potion", "MP Potion" };
	int arrPotionCount[2] = { 5, 5 };

	void PrintInventory(void) {
		std::cout << "--------------- 인벤토리 정보 --------------------" << std::endl;
		for (int i = 0; i < potionTypeCount; ++i) {
			std::cout << arrPotionName[i] << "  " << arrPotionCount[i] << "개" << std::endl;
		}
		std::cout << " --------------------------------------------------" << std::endl;
	}
};

void PrintMenu(const Stat* statInfo) {
	for (int i = 0; i < statInfo->statTypeCount; ++i) {
		std::cout << i + 1 << ". " << statInfo->arrStatName[i] << " UP" << std::endl;
	}
	std::cout << statInfo->statTypeCount + 1 << ". 현재 능력치" << std::endl;
	std::cout << statInfo->statTypeCount + 2 << ". Level UP" << std::endl;
	std::cout << "0. 나가기" << std::endl;
}

void setPotion(int count, int* p_HPPotion, int* p_MPPotion) {
	// check ptr is valid && can subtract by count
	if (p_HPPotion != nullptr && *p_HPPotion >= count) {
		*p_HPPotion -= count;
	}
	// check ptr is valid && can subtract by count
	if (p_MPPotion != nullptr && *p_MPPotion >= count) {
		*p_MPPotion -= count;
	}
}


int main(void) {
	// { HP, MP, 공격력, 방어력 }
	Stat statInfo = Stat();
	Inventory inventoryInfo = Inventory();
	int arrPotion[2] = { 5, 5 };		// 포션 관리 배열

	// get input on each stats
	for (int i = 0; i < statInfo.statTypeCount; ++i) {
		// get input
		int statPoint;
		std::cout << statInfo.arrStatName[i] << "의 값을 입력해 주십시오. : ";
		std::cin >> statPoint;

		// check input error and range of input value
		while ((std::cin.fail() == true) || (statPoint <= statInfo.arrStatValue[i])) {
			// initialize 'std::cin' error flag
			std::cin.clear();
			// clear input buffer by the maximum size or until '\n' appears
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			// print error message
			std::cout << "!!! Error >>" << statInfo.arrStatName[i] << " 값은 " << statInfo.arrStatValue[i] << " 보다 큰 정수이어야 합니다." << std::endl;

			// get input
			std::cout << statInfo.arrStatName[i] << "의 값을 다시 입력하여 주십시오. : ";
			std::cin >> statPoint;
		}

		// set stat as new value
		statInfo.arrStatValue[i] = statPoint;
	}

	bool bIsLoop = true;	// 루프 제어 변수

	while (bIsLoop == true) {
		std::cout << "=======================================" << std::endl;

		// print menu
		PrintMenu(&statInfo);

		// get input
		int menuIndex;
		std::cout << "실행하고자 하는 메뉴 번호를 입력해 주십시오. : ";
		std::cin >> menuIndex;

		// check input error
		while (std::cin.fail() == true) {
			// initialize 'std::cin' error flag
			std::cin.clear();
			// clear input buffer by the maximum size or until '\n' appears
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			// get input
			std::cout << "잘못된 값을 입력하였습니다" << std::endl << " 다시 입력해 주십시오. : ";
			std::cin >> menuIndex;
		}

		switch (menuIndex) {
		case 0:
			bIsLoop = false;
			break;
		case 1:
			// check there is at least one HP Potion
			if (inventoryInfo.arrPotionCount[0] > 0) {
				// modify potion count
				setPotion(1, &inventoryInfo.arrPotionCount[0], NULL);
				// HP UP
				statInfo.arrStatValue[0] += 20;
			}
			break;
		case 2:
			// check there is at least one MP Potion
			if (inventoryInfo.arrPotionCount[1] > 0) {
				// modify potion count
				setPotion(1, NULL, &inventoryInfo.arrPotionCount[1]);
				// MP UP
				statInfo.arrStatValue[1] += 20;
			}
			break;
		case 3:
			statInfo.arrStatValue[2] *= 2;
			break;
		case 4:
			statInfo.arrStatValue[3] *= 2;
			break;
		case 5:
			statInfo.PrintStat();
			inventoryInfo.PrintInventory();
			break;
		case 6:
			++statInfo.level;
			setPotion(-1, &inventoryInfo.arrPotionCount[0], &inventoryInfo.arrPotionCount[1]);
			break;
		default:
			std::cout << "잘못된 값을 입력하였습니다." << std::endl;
			break;
		}

		std::cout << "=======================================" << std::endl;

		if (bIsLoop == true) {
			// pasue Console program until user press any key
			std::cout << "계속 하려면 아무 키나 누르세요....";
			_getch();

			// clear Console Log
			system("cls");
		}
	}

	return 0;
}