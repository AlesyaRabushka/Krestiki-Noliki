#include "GameMap.h"

GameMap::GameMap()
{
	size.x = 0;
	size.y = 0;

	length = 0;  //длина выигрышной комбинации

	map = new int* [size.x];
	for (int i = 0; i < size.x; i++) {
		map[i] = new int[size.y];
	}
}

GameMap::GameMap(Field2 f_size, int)
{
	size = f_size;
	length = 3; //устанавливаем размер выигрышной цепочки

	map = new int* [size.x];
	for (int i = 0; i < size.x; i++) {
		map[i] = new int[size.y];
	}

	//обнул€ем элементы пол€
	for (int i = 0; i < size.x; i++) {
		for (int j = 0; j < size.y; j++) {
			map[i][j] = 0;
		}
	}
}

GameMap::GameMap(int i, int j, int)
{
	size.x = i;
	size.y = j;
	length = 3; //устанавливаем размер выигрышной цепочки

	map = new int* [size.x];
	for (int i = 0; i < size.x; i++) {
		map[i] = new int[size.y];
	}

	//обнул€ем элементы пол€
	for (int i = 0; i < size.x; i++) {
		for (int j = 0; j < size.y; j++) {
			map[i][j] = 0;
		}
	}
}

GameMap::~GameMap()
{
	//очищаем матрицу
	for (int i = 0; i < size.x; i++) {
		delete[] map[i];
	}
	delete[] map;
}

bool GameMap::SetPosition(Field2 cell, int c)//данные нашей €чейки/ то кем мы ходим
{
	if (IsEmpty(cell)) {  //если свободна
		map[cell.x][cell.y] = c; //запонимаем, что походили
		return true;
	}
	else {
		return false; //если зан€та
	}
}

bool GameMap::IsEmpty(Field2 cell)//узнаем свободна ли €чейка
{
	if (map[cell.x][cell.y] == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool GameMap::IsEmpty(int i, int j) //узнаем свободна ли €чейка через координаты
{
	if (map[i][j] == 0) {
		return true;
	}
	else {
		return false;
	}
}

void GameMap::SetMap(Field2 f_size, int) //задаЄт карту(как конструктор с параметрами)
{
	size = f_size;
	length = 3; //устанавливаем размер выигрышной цепочки

	map = new int* [size.x];
	for (int i = 0; i < size.x; i++) {
		map[i] = new int[size.y];
	}

	for (int i = 0; i < size.x; i++) {
		for (int j = 0; j < size.y; j++) {
			map[i][j] = 0;
		}
	}
}

void GameMap::SetMap(int i, int j, int)
{
	size.x = i;
	size.y = j;
	length = 3; //устанавливаем размер выигрышной цепочки

	map = new int* [size.x];
	for (int i = 0; i < size.x; i++) {
		map[i] = new int[size.y];
	}

	//обнул€ем матрицу
	for (int i = 0; i < size.x; i++) {
		for (int j = 0; j < size.y; j++) {
			map[i][j] = 0;
		}
	}
}

int GameMap::GetValue(int i, int j)
{
	return map[i][j];
}

int GameMap::GetValue(Field2 cell)
{
	return map[cell.x][cell.y];
}

int GameMap::CheckList(vector<int> a)
{
	if (a.size() < length) {
		return 0;
	}

	//флажки победы игроков
	bool winPlayer1 = false;
	bool winPlayer2 = false;

	int count1 = 0, count2 = 0;

	//считаем баллы
	//Ќ≈ ѕќЌяЋј
	for (int i = 0; i < a.size(); i++) {
		for (int j = i; j < i + length; j++) {
			if (j < a.size()) {
				if (a[j] == 1) count1++;
			}
			else break;
		}

		if (count1 == length) {
			winPlayer1 = true;
			break;
		}

		count1 = 0;
	}

	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < i + length; j++) {
			if (j < a.size()) {
				if (a[j] == 2) {
					count2++;
				}
				else break;
			}
		}

		if (count2 == length) {
			winPlayer2 = true;
			break;
		}

		count2 = 0;

	}

	//высчитываем результат
	if (winPlayer1 && winPlayer2) {
		return 3; //ничь€
	}
	else if (!winPlayer1 && winPlayer2) {
		return 2;//выиграл второй игрок
	}
	else if (winPlayer1 && !winPlayer2) {
		return 1; //выиграл первый игрок
	}
	else return 0;
}

int GameMap::CheckWinner()
{
	//проходим по карте в поиске последвательности дл€ выигрыша
	int state = 0;
	vector<int> check;

	/*
	[][][]
	[][][]
	[][][]
	*/

	//1 ----- проходим по всем горизонтал€м
	for (int i = 0; i < size.x; i++) {
		for (int j = 0; j < size.y; j++) {
			check.push_back(map[i][j]);
		}

		//провер€ем
		state = CheckList(check);
		check.clear();

		if (state == 3){
			return 3;//ничь€
		}
		else if (state == 2) {
			return 2;//второй игрок
		}
		else if (state == 1) {
			return 1;//первый игрок
		}
	}

	//2 ----- проходим по всем вертикал€м
	for (int i = 0; i < size.x; i++) {
		for (int j = 0; j < size.y; j++) {
			check.push_back(map[j][i]);
		}

		//провер€ем
		state = CheckList(check);
		check.clear();
		
		if(state == 3) {
			return 3;
		}
		else if (state == 2) {
		return 2;
		}
		else if (state == 1) {
		return 1;
		}
	}

	//3 ------проходим по двум диагонал€м

	//√лавна€ диагональ
	for (int i = 0; i < size.y; i++) {
		check.push_back(map[i][i]);
	}

	state = CheckList(check);
	check.clear();

	if (state == 3) {
		return 3; //ничь€
	}
	else if (state == 2) {
		return 2;//второй
	}
	else if (state == 1) {
		return 1;//первый
	}

	//ѕобочна€
	for (int i = size.x; i > 0; i--) {
		check.push_back(map[i][i]);
	}

	state = CheckList(check);
	check.clear();

	if(state == 3) {
		return 3;
	}
	else if (state == 2) {
		return 2;
	}
	else if (state == 1) {
		return 1;
	}


	if (CanMove()) {
		return 0;
	}
	else return 3;//ничь€
	return 0;
}

bool GameMap::CanMove()
{
	for (int i = 0; i < size.x; i++) {
		for (int j = 0; j < size.y; j++) {
			if (map[i][j] == 0) {
				return true; //€чейка пуста€
			}
		}
	}

	return false; //почему??
}
