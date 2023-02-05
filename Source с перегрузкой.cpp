#include <iostream>
#include <Windows.h>

using namespace std;

const int M = 10; //������ �������
int C = 1; //��� ���-�������

struct Element {
	int key;
	int occupation;
	char info[200];
	Element() : key(-1), occupation(0), info("no info") {

	}
	Element(int k, int o, const char* i) : key(k), occupation(o), info("") {
		strcpy_s(this->info, i);
	}
};

class Table {
	Element data[M];
	int count = 0;
public:
	Table() = default;
	Table(Element* d, int c) {
		this->count = c;
		for (int i = 0; i < c; i++) {
			data[i] = d[i];
		}
	}

	void Add(Element el) {
		int i = el.key % M;
		int st = i;

		while (data[i].occupation == 1) {
			if (data[i].key == el.key) {
				cout << "������� � ��������� ������ ��� ����������" << endl;
				return;
			}
			i = (i + C) % M;
			if (i == st) {
				cout << "������� �����������" << endl;
				return;
			}
		}

		data[i] = el;
	}

	Element& operator[](int i) {
		return data[i]; //���������� ��������� []
	}

	int GetCount() {
		return count;
	}

	int operator()(int key) {
		int i = key % M;
		int st = i;
		while (data[i].occupation == 1) {
			if (data[i].key == key && data[i].occupation == 1) 
				return i;
			i = (i + C) % M;
			if (i == st)
				break;
		}
		return -1; //���������� ��������� ()
	}
	void Reorg(int key) {
		int pos = key % M;
		for (int i = 0; i < M; i++) {
			if (data[i].key % M == pos) {
				data[pos] = data[i];
				data[i].key = -1;
				data[i].occupation = 0;
				strcpy_s(data[i].info, "no info");
			}
		}
	}
};

istream& operator>>(istream& is, Element& el) {
	is >> el.key >> el.info;
	return is;
}

ostream& operator<<(ostream& os, Element& el) {
	os << el.key << " " << el.occupation << " " << el.info << endl;
	return os;
}

ostream& operator<<(ostream& os, Table& tb) {
	for (int i = 0; i < M; i++) {
		os << tb[i];
	}
	
	return os;
}

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	Table* tb[10] = {nullptr};
	int tb_count = 0;
	int cur = 1;
	int cmd = -1;
	while (cmd != 0) {
		cout << "������� ����������� ��������: \n1 � ������� �������\n2 � �������� ������� � ������� �������\n3 � ������� �������\n4 � ����� �������� �������\n5 � ������� ���������� �� �������\n6 � �������� �������� �������\n7 � ������� ������� �������\n0 � ��������� ������ ���������" << endl;
		cin >> cmd;
		switch (cmd){
			case 1: {
				if (tb_count > 10){
					cout << "���������� ������� ����� �������" << endl;
					break;
				}
				tb_count++;
				cout << "������� �������� ������� �" << tb_count << " � ��������� ����: ����_1 ����������_1 ����_2 ����������_2..." << endl;

				Table* t = new Table();
				tb[tb_count - 1] = t;

				Element el;
				cin >> el;
				el.occupation = 1;
				t->Add(el);
				char st = cin.get();
				while (st != '\n') {
					cin.putback(st);
					cin >> el;
					t->Add(el);
					st = cin.get();
				}
				//1 info1 2 info2 3 info3
				
			}
				break;
			case 2: {
				cout << "������� ������� ������� �" << cur << " � ��������� ����: ���� ����������" << endl;
				Element el;
				cin >> el;
				el.occupation = 1;
				tb[cur - 1]->Add(el);
			}
				break;
			case 3: {
				cout << "������� �" << cur << endl;
				cout << *tb[cur - 1];
			}
				break;
			case 4: {
				int k;
				cout << "������� ����� ��������: ";
				cin >> k;
				if (k > M || k < 0) {
					cout << "�������� �����" << endl;
					break;
				}
				cin >> (*tb[cur - 1])[k - 1];
			}
				break;
			case 5: {
				int k;
				cout << "������� ���� ��������: ";
				cin >> k;
				k = (*tb[cur - 1])(k);
				if (k != -1) 
					cout << (*tb[cur - 1])[k].info << endl;
				else
					cout << "������� �� ������" << endl;
			}
				  break;
			case 6: {
				int k;
				cout << "������� ���� ��������: ";
				cin >> k;
				k = (*tb[cur - 1])(k);
				if (k != -1) {
					Element& el = (*tb[cur - 1])[k];
					el.occupation = 0;
					el.key = -1;
					strcpy_s(el.info, "no info");
					tb[cur - 1]->Reorg(k);
				}
				else
					cout << "������� �� ������" << endl;
			}
				break;
			case 7: {
				cout << "������� ����� ������� �������: ";
				int ch;
				cin >> ch;
				if (ch > tb_count || ch < 0) {
					cout << "�������� ����� �������" << endl;
					break;
				}
				else {
					cur = ch;
				}
			}
				break;
			case 0: {
				return 0;
			}
		}
	}

	//533 info1 247 info2 144 info3 616 info4
}