#include <iostream>
#include <Windows.h>

using namespace std;

const int M = 10; //размер таблицы
int C = 1; //шаг хеш-функции

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
				cout << "Ёлемент с указанным ключом уже существует" << endl;
				return;
			}
			i = (i + C) % M;
			if (i == st) {
				cout << "“аблица переполнена" << endl;
				return;
			}
		}

		data[i] = el;
	}

	Element& operator[](int i) {
		return data[i]; //перегрузка оператора []
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
		return -1; //перегрузка оператора ()
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
		cout << "¬ведите необходимое действие: \n1 Ч создать таблицу\n2 Ч добавить элемент в текущую таблицу\n3 Ч вывести таблицу\n4 Ч поиск элемента таблицы\n5 Ч выборка информации из таблицы\n6 Ч удаление элемента таблицы\n7 Ч сменить текущую таблицу\n0 Ч завершить работу программы" << endl;
		cin >> cmd;
		switch (cmd){
			case 1: {
				if (tb_count > 10){
					cout << "Ќевозможно создать новую таблицу" << endl;
					break;
				}
				tb_count++;
				cout << "¬ведите элементы таблицы є" << tb_count << " в следующем виде: ключ_1 информаци€_1 ключ_2 информаци€_2..." << endl;

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
				cout << "¬ведите элемент таблицы є" << cur << " в следующем виде: ключ информаци€" << endl;
				Element el;
				cin >> el;
				el.occupation = 1;
				tb[cur - 1]->Add(el);
			}
				break;
			case 3: {
				cout << "“аблица є" << cur << endl;
				cout << *tb[cur - 1];
			}
				break;
			case 4: {
				int k;
				cout << "¬ведите номер элемента: ";
				cin >> k;
				if (k > M || k < 0) {
					cout << "Ќеверный номер" << endl;
					break;
				}
				cin >> (*tb[cur - 1])[k - 1];
			}
				break;
			case 5: {
				int k;
				cout << "¬ведите ключ элемента: ";
				cin >> k;
				k = (*tb[cur - 1])(k);
				if (k != -1) 
					cout << (*tb[cur - 1])[k].info << endl;
				else
					cout << "Ёлемент не найден" << endl;
			}
				  break;
			case 6: {
				int k;
				cout << "¬ведите ключ элемента: ";
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
					cout << "Ёлемент не найден" << endl;
			}
				break;
			case 7: {
				cout << "¬ведите номер текущей таблицы: ";
				int ch;
				cin >> ch;
				if (ch > tb_count || ch < 0) {
					cout << "Ќеверный номер таблицы" << endl;
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