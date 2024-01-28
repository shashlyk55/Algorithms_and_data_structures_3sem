#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

/*
1.	Разработать приложение, преобразования текста сообщения с помощью алгоритма Хаффмана.
2.	Пользователь вводит текст произвольной длины (для тестирования можно использовать в качестве текста ФИО студента полностью).
3.	В приложении организовать алгоритм формирования кодовых последовательностей для каждого символа сообщения.
4.	Вывести на экран пользователя следующую информацию:
А) Таблицу встречаемости символов в тексте (можно в количественном или в процентном варианте);
Б) Таблицу соответствия символа и кодовой последовательности;
В) Выходную последовательность.

*/

//Узел дерева
struct Node
{
	char ch;
	int freq;
	Node* left, * right;
};

//Функция для добавления новго узла дерева
Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

//Структура для сравнения, которая используется для сортировки кучи (компоратор)
struct comp
{
	bool operator()(Node* l, Node* r)
	{
		//Элемент с наивысшим приоритетом имеет наименьшую частоту
		return l->freq > r->freq;
	}
};

//Проход по дереву и сохранение кодов элементов в перечень
void encode(Node* root, string str,
	unordered_map<char, string>& huffmanCode)
{
	if (root == nullptr)
		return;

	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

//Проход по дереву и декодирование зашифрованной строки
void decode(Node* root, int& index, string str)
{
	if (root == nullptr) {
		return;
	}

	// found a leaf node
	if (!root->left && !root->right)
	{
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] == '0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}

//Построение дерева Хаффмана и декодирование введенного текста
void buildHuffmanTree(string text)
{
	//Подсчет частоты появления каждого символа и сохранение его в перечень
	unordered_map<char, int> freq;
	for (char ch : text) {
		freq[ch]++;
	}

	//Создание приоритетной очереди для хранения активных узлов дерева Хаффмана
	priority_queue<Node*, vector<Node*>, comp> pq;

	//Создание конечного узла для каждого символа и добавление его в приоритетную очередь
	for (auto pair : freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	// Цикл while идет до тех пор пока в очереди не останется более одного узла
	while (pq.size() != 1)
	{
		//Удвление двух узлов с наивысшим приоритетом (самой низкой частотой из очереди) из очереди
		Node* left = pq.top(); pq.pop();
		Node* right = pq.top();	pq.pop();

		//Создаем новый внутренний узел с этими двумя узлами в качестве дочерних и с частотой равной сумме частот двух узлов.
		//Добавление нового узла в очередь приоритетов
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	// root хранит адрес корень дерева Хаффмана
	Node* root = pq.top();

	//Проход по дереву Хаффмана, сохранение и вывод кодов
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "Huffman Codes are :\n" << '\n';
	for (auto pair : huffmanCode) {
		cout << pair.first << " " << pair.second << '\n';
	}

	cout << "\nOriginal string was :\n" << text << '\n';
	//Выывод зашифрованной строки
	string str = "";
	for (char ch : text) {
		str += huffmanCode[ch];
	}

	cout << "\nEncoded string is :\n" << str << '\n';
	//Проход по дереву Хаффмана и декодирование зашифрованной строки
	int index = -1;
	cout << "\nDecoded string is: \n";
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}
}

//Алгоритм кодирования Хаффмана
int main()
{
	string text;
	text = "Beloded is the best lector in Minsk.";
	/*cout << "Input text: ";
	getline(cin, text);*/

	buildHuffmanTree(text);

	return 0;
}
