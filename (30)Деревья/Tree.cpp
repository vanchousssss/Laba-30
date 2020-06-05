#include<stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include<ctype.h>
#include<Windows.h>
#include<math.h>
#include<string.h>
#include<glut.h>
#include <string>
#include <iostream>
using namespace std;
#pragma warning(disable : 4996)
float offset = 0.0;
bool box_clicked = false;
int temp_x, temp_y, temp_item;
bool prev_search = false;
enum color_code { BLACK, GREEN, BLUE };
int i = 0;
int n = 100;
int c = 0;
int n1 = 100;
int pos = 0;
int size1 = 0;

string* prib = new string[n1];
string* prib1 = 0;
#define SCREEN_SIZE_X 1000
#define SCREEN_SIZE_Y 700
#define BG_R 1.0
#define BG_G 1.0
#define BG_B 1.0
#define BG_A 1.0

struct node {
	int data;
	struct node* left;
	struct node* right;
};
node* p = 0;
typedef struct node* NODE;

NODE root = NULL;

char query_string[] = "Enter flight number: ";

char not_found[] = "Not found!";

float node_color[3] = { 1.0, 1.0, 0.1 };
void display();
struct race
{
	int count;
	string name;
	string date;
	string time;
	string pynkt;
};
race* names = new race[n];
race* names1 = 0;
int count_digit(int n) {
	return (n == 0) ? 0 : floor(log10(n) + 1);
}
void to_string(char* s, int num) {
	int r, d;
	d = count_digit(abs(num));
	if (num == 0)
		s[0] = '0';
	if (num < 0) {
		s[0] = '-';
		d++;
	}
	s[d] = '\0';
	num = abs(num);
	while (num != 0) {
		r = num % 10;
		s[--d] = r + '0';
		num /= 10;
	}
}
void display_string(char s[], float x, float y, float z = 0.0) {
	glRasterPos3f(x, y, z);
	for (int i = 0; s[i]; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
	glFlush();
}
void clear_input_region() {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(80, 580);
	glVertex2f(80, 650);
	glVertex2f(580, 650);
	glVertex2f(580, 580);
	glEnd();
	glFlush();
}
class binary_search_tree {

private:
	NODE root;
	int root_centre_x, root_centre_y;
	int node_width;
	float line_color[3];
	NODE get_minimum(NODE temp, NODE* par) {
		if (temp->left == NULL)
			return temp;
		*par = temp;
		return get_minimum(temp->left, par);
	}

public:
	binary_search_tree() {
		root = NULL;
		root_centre_x = 500;
		root_centre_y = 500;
		node_width = 30;
		line_color[BLACK] = 0.0;
		line_color[GREEN] = 0.7;
		line_color[BLUE] = 0.0;
	}
	void draw_node(int item, int centre_x, int centre_y, bool write_value = true) {
		char data_string[10];
		float x1, y1;
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_TRIANGLE_FAN);
		for (int i = 30 - 1; i <= 30; i++) {
			for (int t = 0; t <= 360; t++) {
				x1 = 30 * sin(t) + centre_x - node_width + 25;
				y1 = 30 * cos(t) + centre_y - node_width + 30;
				glVertex2f(x1, y1);
			}
		}
		glEnd();

		if (write_value) {
			to_string(data_string, item);
			glColor3f(0.0, 0.0, 0.0);
			display_string(data_string, centre_x - node_width + 15, centre_y - 5);
		}

	}
	void draw_arrow(int par_x, int par_y, int node_x, int node_y, bool color = true) {
		if (color)
			glColor3f(0.0, 0.0, 0.0);
		else
			glColor3f(BG_R, BG_G, BG_B);
		glBegin(GL_LINES);
		glVertex2f(par_x, par_y - node_width);
		glVertex2f(node_x, node_y + node_width);
		glEnd();
	}
	NODE insert(int item) {
		int k = 0;
		bool f = false;
		string help1;
		for (int z = 0; z < size1; z++)
		{
			if (names[z].count == item)
				f = true;
		}
		if (f == false)
		{
			cout << "Количество заявок для (макс.  " << n << ") рейса №" << item << ": ";
			cin >> k;
			n = n - k;
			cin.ignore();
			for (int l = 0; l < k; l++)
			{
				names[i].count = item;
				cout << "Желательная дата вылета(ДД.ММ.ГГГГ ЧЧ:ММ): ";
				getline(cin, names[i].date);
				cout << "Продолжительность рейса(ЧЧ:ММ): ";
				getline(cin, names[i].time);
				cout << "Ф.И.О.: ";
				getline(cin, names[i].name);
				cout << "Пункт назначения: ";
				getline(cin, names[i].pynkt);
				cout << "Введите время прибытия(Дата вылета: " << names[i].date << ", продолжительность рейса: " << names[i].time << "): ";
				getline(cin, prib[i]);
				i++;
				size1++;
			}
		}
		int num_of_nodes = 1;
		int node_x = root_centre_x, node_y = root_centre_y;
		int par_x, par_y;
		NODE temp, par = NULL, new_node;
		if (root == NULL) {
			root = (NODE)malloc(sizeof(struct node));
			if (root == NULL) {
				printf("Ошибка создания узла\n");
				return NULL;
			}
			root->data = item;
			root->left = root->right = NULL;
			glColor3f(0.0, 1.0, 0.0);
			draw_node(item, node_x, node_y);
			return root;
		}
		temp = root;
		while (temp != NULL) {
			num_of_nodes *= 2;
			par_x = node_x;
			par_y = node_y;
			node_y -= 100;
			par = temp;
			if (item < temp->data) {
				temp = temp->left;
				node_x -= root_centre_x / num_of_nodes;
			}
			else {
				temp = temp->right;
				node_x += root_centre_x / num_of_nodes;
			}
		}
		new_node = (NODE)malloc(sizeof(struct node));
		if (new_node == NULL) {
			printf("Ошибка создания узла\n");
			return NULL;
		}
		new_node->data = item;
		new_node->left = new_node->right = NULL;
		if (item < par->data)
		{
			par->left = new_node;
		}
		else
		{
			par->right = new_node;
		}
		glColor3f(0.0, 1.0, 0.0);
		draw_node(item, node_x, node_y);
		draw_arrow(par_x, par_y, node_x, node_y);
		glFlush();
		return root;

	}
	NODE search(int item) {

		int num_of_nodes = 1;
		int node_x = root_centre_x, node_y = root_centre_y;
		int par_x, par_y;
		NODE temp, par = NULL, new_node;
		if (root == NULL) {
			glColor3f(0.0, 0.0, 0.0);
			display_string(not_found, 100, 600);
			return root;
		}
		temp = root;
		while (temp != NULL) {
			num_of_nodes *= 2;
			par_x = node_x;
			par_y = node_y;
			par = temp;
			if (item == temp->data) {
				int r = 0;
				cout << "1. Вывод заявок для рейса №" << item << " и дате вылета." << endl;
				cout << "2. Вывод всех заявок." << endl;
				cout << "Ваш выбор: ";
				cin >> r;
				string help;
				switch (r)
				{
				case 1:
					cout << "Введите дату вылета: ";
					cin.ignore();
					getline(cin, help);
					for (int z = 0; z < size1; z++)
					{
						if (names[z].count == item && names[z].date == help)
						{
							cout << "Рейс №" << names[z].count << endl;
							cout << "Желательная дата вылета: " << names[z].date << endl;
							cout << "Продолжительность рейса: " << names[z].time << endl;
							cout << "Ф.И.О.: " << names[z].name << endl;
							cout << "Пункт назначения: " << names[z].pynkt << endl;
							cout << "Время прибытия: " << prib[z] << endl;
						}
					}
					cout << endl;
					break;
				case 2:
					for (int z = 0; z < size1; z++)
					{
						cout << "Рейс №" << names[z].count << endl;
						cout << "Желательная дата вылета: " << names[z].date << endl;
						cout << "Продолжительность рейса: " << names[z].time << endl;
						cout << "Ф.И.О.: " << names[z].name << endl;
						cout << "Пункт назначения: " << names[z].pynkt << endl;
					}
					cout << endl;
					break;
				}
				prev_search = true;
				temp_x = node_x;
				temp_y = node_y;
				temp_item = item;
				glColor3f(0.0, 0.0, 0.0);
				draw_node(item, node_x, node_y);
				int j = 0;
				int k = 0;
				glFlush();
				return temp;
			}
			else if (item < temp->data) {
				temp = temp->left;
				node_y -= 100;
				node_x -= root_centre_x / num_of_nodes;
			}
			else {
				temp = temp->right;
				node_y -= 100;
				node_x += root_centre_x / num_of_nodes;
			}
		}
		glColor3f(0.0, 0.0, 0.0);
		display_string(not_found, 100, 600);
		glFlush();
		return temp;
	}
	void pre_order(NODE temp, binary_search_tree temp_tree) {
		if (temp != NULL) {
			temp_tree.insert(temp->data);
			pre_order(temp->left, temp_tree);
			pre_order(temp->right, temp_tree);
		}
	}
	void draw_tree() {
		binary_search_tree temp_tree;
		display();
		pre_order(root, temp_tree);
	}
	NODE remove(int item) {
		int ck = 0;
		int zi = 0;
		names1 = new race[n1];
		prib1 = new string[n1];
		for (int z = 0; z < size1; z++)
		{
			if (names[z].count != item)
			{
				names1[zi].count = names[z].count;
				names1[zi].date = names[z].date;
				names1[zi].time = names[z].time;
				names1[zi].name = names[z].name;
				names1[zi].pynkt = names[z].pynkt;
				prib1[zi] = prib[z];
				zi++;
			}
			else
				ck = ck + 1;
		}
		size1 -= ck;
		n += ck;
		delete[]names;
		delete[]prib;
		names = new race[n1];
		prib = new string[n1];
		zi = 0;
		i = 0;
		for (int z = 0; z < size1; z++)
		{
			names[zi].count = names1[z].count;
			names[zi].date = names1[z].date;
			names[zi].time = names1[z].time;
			names[zi].name = names1[z].name;
			names[zi].pynkt = names1[z].pynkt;
			prib[zi] = prib1[z];
			zi++;
			i++;
		}
		delete[]names1;
		delete[]prib1;
		bool found = false;
		int num_of_nodes = 1;
		int node_x = root_centre_x, node_y = root_centre_y;
		int par_x, par_y;
		NODE temp = root, par = root, new_node;
		if (root == NULL) {
			glColor3f(0.0, 0.0, 0.0);
			display_string(not_found, 100, 600);
			return root;
		}
		while (temp != NULL) {
			if (item == temp->data) {
				found = true;
				if (temp == root) {
					if (temp->left == NULL && temp->right == NULL) {
						root = NULL;
						free(temp);
					}
					if (temp->left != NULL && temp->right != NULL) {
						par = temp;
						NODE min_node = get_minimum(temp->right, &par);
						temp->data = min_node->data;
						temp = min_node;
						item = min_node->data;
						continue;
					}
					if (temp->left != NULL) {
						root = temp->left;
						free(temp);
					}
					if (temp->right != NULL) {
						root = temp->right;
						free(temp);
					}
				}
				else if (temp->left == NULL && temp->right == NULL) {
					if (par->left == temp)
						par->left = NULL;
					else
						par->right = NULL;
					free(temp);
				}
				else if (temp->left != NULL && temp->right != NULL) {
					par = temp;
					NODE min_node = get_minimum(temp->right, &par);
					temp->data = min_node->data;
					temp = min_node;
					item = min_node->data;
					continue;
				}
				else {
					if (temp->left != NULL)
						(par->left == temp) ? (par->left = temp->left) : (par->right = temp->left);
					else
						(par->left == temp) ? (par->left = temp->right) : (par->right = temp->right);
					free(temp);
				}
				break;
			}
			par = temp;
			if (item < temp->data)
				temp = temp->left;
			else
				temp = temp->right;
		}
		if (!found) {
			glColor3f(0.0, 0.0, 0.0);
			display_string(not_found, 100, 600);
		}
		glClear(GL_COLOR_BUFFER_BIT);
		draw_tree();
	}
};
binary_search_tree tree;
NODE(binary_search_tree::* operation)(int) = NULL;
class option_box {

private:
	float bottom_corner_x, bottom_corner_y;
	float bc;
	float height, width;
	float color[3];
	char option_name[20];

public:
	option_box() {
		bottom_corner_x = 0;
		bottom_corner_y = 0;
		width = 0;
		height = 0;
		color[BLACK] = 0.0;
		color[GREEN] = 1.0;
		color[BLUE] = 0.0;
		strcpy(option_name, "");
	}
	option_box(const char name[]) {
		bottom_corner_x = 350;
		bottom_corner_y = 50;
		width = 100;
		height = 50;
		color[BLACK] = 0.0;
		color[GREEN] = 1.0;
		color[BLUE] = 0.0;
		strcpy(option_name, name);
	}
	void draw_box() {
		bottom_corner_x += offset;
		bc = bottom_corner_x;
		glColor3f(color[BLACK], color[GREEN], color[BLUE]);
		glBegin(GL_POLYGON);
		glVertex2f(bottom_corner_x, bottom_corner_y);
		glVertex2f(bottom_corner_x + width, bottom_corner_y);
		glVertex2f(bottom_corner_x + width, bottom_corner_y + height);
		glVertex2f(bottom_corner_x, bottom_corner_y + height);
		glEnd();
		offset += 120.0;
		glColor3f(0.0, 0.0, 0.0);
		display_string(option_name, bottom_corner_x + 22.0, bottom_corner_y + 18.0);
	}
	bool clicked(int x, int y) {
		if (x > bc && x < bc + width)
			if (y > bottom_corner_y && y < bottom_corner_y + height) {
				box_clicked = true;
				return true;
			}
		return false;
	}
};
option_box insert_box, search_box, delete_box;
void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 1000, 0.0, 700);
}
void displayOptions() {
	option_box insert_box("  Add"), search_box("Search"), delete_box("Delete");
	offset = 0.0;
	insert_box.draw_box();
	search_box.draw_box();
	delete_box.draw_box();
	::insert_box = insert_box;
	::search_box = search_box;
	::delete_box = delete_box;
}
void display() {
	displayOptions();
	glFlush();

}
void mouse(int button, int state, int x, int y) {
	y = SCREEN_SIZE_Y - y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (prev_search == true) {
			glColor3f(node_color[BLACK], node_color[GREEN], node_color[BLUE]);
			tree.draw_node(temp_item, temp_x, temp_y);
			prev_search = false;
		}
		if (insert_box.clicked(x, y)) {
			operation = &binary_search_tree::insert;
			clear_input_region();
			glColor3f(0.0, 0.0, 0.0);
			display_string(query_string, 100, 600);
			glFlush();
		}
		if (search_box.clicked(x, y)) {
			operation = &binary_search_tree::search;
			clear_input_region();
			glColor3f(0.0, 0.0, 0.0);
			display_string(query_string, 100, 600);
			glFlush();
		}
		if (delete_box.clicked(x, y)) {
			operation = &binary_search_tree::remove;
			clear_input_region();
			glColor3f(0.0, 0.0, 0.0);
			display_string(query_string, 100, 600);
			glFlush();
		}
	}

}
void keyboard(unsigned char key, int x, int y) {
	char s[2];
	static int digit = 0;
	static int number = 0;
	static int sign = 1;
	if (!box_clicked)
		return;
	if (digit == 0 && key == '-') {
		s[0] = key;
		s[1] = '\0';
		glColor3f(0.0, 0.0, 0.0);
		display_string(s, 420 + (15 * digit), 600);
		glFlush();
		sign = -1;
	}
	else if (key != 13 && isdigit(key)) {
		digit++;
		number = (number * 10) + key - '0';
		c++;
		s[0] = key;
		s[1] = '\0';
		glColor3f(0.0, 0.0, 0.0);
		display_string(s, 420 + (15 * digit), 600);
		glFlush();
	}
	else if (key != 13 && !isdigit(key))
		;
	else {
		digit = 0;
		clear_input_region();
		(tree.*operation)(sign * number);
		number = 0;
		sign = 1;
		box_clicked = false;
	}
}

int main(int argc, char** argv) {
	glGenLists(256);
	setlocale(LC_ALL, "rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int k = 0;
	int r_n = 0;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(0, 0);
	glutSetWindow(glutCreateWindow("Самолётики"));
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	init();
	glutMainLoop();
	return 0;
}