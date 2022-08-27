#include <iostream>

struct Node {
	int data;    // tarolt adat
	Node * next; // pointer a kovetkezo elemre, vagy nullptr ha nincs tobb
};

void pushFront(Node ** list, int data) // lista elejere szur be elemet
{
	Node * p = new Node {data, *list};
	*list = p;
}

void printList(const Node * list) // kiirja a teljes listat
{
	const Node * p = list;
	while (p != nullptr) {
		std::cout << p->data << "\n";
		p = p->next; // === (*p).next
	}
}

void deleteList(Node * list) // gyakorlo feladat: menjen vegig a listan es minden Node-ra hivjon delete-t
{
	/*...*/
}

int main()
{
	Node * list = new Node {0, nullptr}; // legyen a lista vegen egy nullptr-es Node

	for (int i=10; i<100; i+=10)
		pushFront(&list, i);

	printList(list);

	/* deleteList(list); */ // ezt meg kell majd hivni, hogy deallokaljuk a
	                        // dinamikusan lefoglalt memoriat
}

