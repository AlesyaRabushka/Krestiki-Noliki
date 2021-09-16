#include "GameMap.h"

GameMap::GameMap()
{
	size.x = 0;
	size.y = 0;

	length = 0;  //����� ���������� ����������

	map = new int* [size.x];
	for (int i = 0; i < size.x; i++) {
		map[i] = new int[size.y];
	}
}

GameMap::GameMap(Field2 f_size, int)
{
	size = f_size;
	length = 3; //������������� ������ ���������� �������

	map = new int* [size.x];
	for (int i = 0; i < size.x; i++) {
		map[i] = new int[size.y];
	}

	//�������� �������� ����
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
	length = 3; //������������� ������ ���������� �������

	map = new int* [size.x];
	for (int i = 0; i < size.x; i++) {
		map[i] = new int[size.y];
	}

	//�������� �������� ����
	for (int i = 0; i < size.x; i++) {
		for (int j = 0; j < size.y; j++) {
			map[i][j] = 0;
		}
	}
}

GameMap::~GameMap()
{
	//������� �������
	for (int i = 0; i < size.x; i++) {
		delete[] map[i];
	}
	delete[] map;
}

bool GameMap::SetPosition(Field2 cell, int c)//������ ����� ������/ �� ��� �� �����
{
	if (IsEmpty(cell)) {  //���� ��������
		map[cell.x][cell.y] = c; //����������, ��� ��������
		return true;
	}
	else {
		return false; //���� ������
	}
}

bool GameMap::IsEmpty(Field2 cell)//������ �������� �� ������
{
	if (map[cell.x][cell.y] == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool GameMap::IsEmpty(int i, int j) //������ �������� �� ������ ����� ����������
{
	if (map[i][j] == 0) {
		return true;
	}
	else {
		return false;
	}
}

void GameMap::SetMap(Field2 f_size, int) //����� �����(��� ����������� � �����������)
{
	size = f_size;
	length = 3; //������������� ������ ���������� �������

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
	length = 3; //������������� ������ ���������� �������

	map = new int* [size.x];
	for (int i = 0; i < size.x; i++) {
		map[i] = new int[size.y];
	}

	//�������� �������
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

	//������ ������ �������
	bool winPlayer1 = false;
	bool winPlayer2 = false;

	int count1 = 0, count2 = 0;

	//������� �����
	//�� ������
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

	//����������� ���������
	if (winPlayer1 && winPlayer2) {
		return 3; //�����
	}
	else if (!winPlayer1 && winPlayer2) {
		return 2;//������� ������ �����
	}
	else if (winPlayer1 && !winPlayer2) {
		return 1; //������� ������ �����
	}
	else return 0;
}

int GameMap::CheckWinner()
{
	//�������� �� ����� � ������ ����������������� ��� ��������
	int state = 0;
	vector<int> check;

	/*
	[][][]
	[][][]
	[][][]
	*/

	//1 ----- �������� �� ���� ������������
	for (int i = 0; i < size.x; i++) {
		for (int j = 0; j < size.y; j++) {
			check.push_back(map[i][j]);
		}

		//���������
		state = CheckList(check);
		check.clear();

		if (state == 3){
			return 3;//�����
		}
		else if (state == 2) {
			return 2;//������ �����
		}
		else if (state == 1) {
			return 1;//������ �����
		}
	}

	//2 ----- �������� �� ���� ����������
	for (int i = 0; i < size.x; i++) {
		for (int j = 0; j < size.y; j++) {
			check.push_back(map[j][i]);
		}

		//���������
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

	//3 ------�������� �� ���� ����������

	//������� ���������
	for (int i = 0; i < size.y; i++) {
		check.push_back(map[i][i]);
	}

	state = CheckList(check);
	check.clear();

	if (state == 3) {
		return 3; //�����
	}
	else if (state == 2) {
		return 2;//������
	}
	else if (state == 1) {
		return 1;//������
	}

	//��������
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
	else return 3;//�����
	return 0;
}

bool GameMap::CanMove()
{
	for (int i = 0; i < size.x; i++) {
		for (int j = 0; j < size.y; j++) {
			if (map[i][j] == 0) {
				return true; //������ ������
			}
		}
	}

	return false; //������??
}
