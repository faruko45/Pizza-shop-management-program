/*
	Faruk Orak	
	150180058  
*/
#include<iostream>
#include<string>
#include<limits>
using namespace std;

struct ingredient{ //is used to store the ingredients in a linked list structure
	string name;
	ingredient *next;
};
class Pizza
{
	friend class OrderList;
	friend class Order;
  private:
	string name;
	string size;
	ingredient *head; //is used to hold the address of ingredient structure
	string crust_type;
	Pizza *counterpart; //is used to link pizza each other to keep in order
  public:
	Pizza(); //default constructor
	Pizza(string,string ,int); //constructor
	Pizza(const Pizza&); //copy constructor
	~Pizza(); //destructor
	void create(); //initializes the ingedient structure list
	void add_ing(string); //adds the ingredient to pizza
	void remove_ing(string); //removes the ingredient
	void print_ing(); //prints ingredients
	void print_pizza(); //prints pizza
};
class Order
{
	friend class OrderList;
  private:
	string customer;
	Pizza *head_pizza; //keeps the address of head of linked pizzas
	int *drinks; //keeps the address of dynamic array which stores drinks
	Order *next; //is used to link orders each other
  public:
	Order(string,Pizza&,int*); //constructor
	Order(string,Pizza&); //constructor
	~Order(); //destrcutor
	double getPrice(); //calculates price of order
	void printOrder(); //prints details of order
	void add_pizza(Pizza&); //adds a pizza to Order
};
class OrderList
{
	int n; //number of orders stored in orderlist
	Order *head; //keeps the address of head of orders
  public:
	OrderList(); //default constructor
	~OrderList(); //destructor
	void takeOrder(); //creates Order and adds to orderlist
	void listOrders(); //prints orders which is kept in orderlist
	void deliverOrders(); //delivers the order and removes from orderlist
};
Pizza::Pizza()
{
	size = "medium";
	add_ing("mozarella");
	crust_type = "normal";
	counterpart = NULL;
};
Pizza::Pizza(string size_pizza,string crust_type_pizza ,int pizza_type)
{
	switch(pizza_type){
		case 1:
			name = "chicken pizza";
			create();
			add_ing("mozarella");
			add_ing("chicken");
			add_ing("mushroom");
			add_ing("corn");
			add_ing("onion");
			add_ing("tomato");
			break;
		case 2:
			name = "broccoli pizza";
			create();
			add_ing("mozarella");
			add_ing("broccoli");
			add_ing("pepperoni");
			add_ing("olive");
			add_ing("corn");
			add_ing("onion");
			break;
		case 3:
			name = "sausage pizza";
			create();
			add_ing("mozarella");
			add_ing("sausage");
			add_ing("tomato");
			add_ing("olive");
			add_ing("mushroom");
			add_ing("corn");
			break;
	}
	size = size_pizza;
	crust_type = crust_type_pizza;
	counterpart = NULL;
}
Pizza::Pizza(const Pizza &p) //copies all informations 
{
	this->name = p.name;
	this->size = p.size;
	this->crust_type = p.crust_type;
	create();
	ingredient *traverse;
	traverse = p.head;
	while(traverse) //copies ingredients
	{
		add_ing(traverse->name);
		traverse = traverse->next;
	}
	counterpart = NULL;
}
Pizza::~Pizza()
{
	ingredient *traverse;
	traverse = head;
	while(traverse) //deletes ingredients
	{
		head = head->next;
		delete traverse;
		traverse = head;
	}
}
void Pizza::create()
{
	head = NULL;
}
void Pizza::add_ing(string name){
	ingredient *traverse;
	ingredient *ing = new ingredient;
	ing->name = name;
	ing->next = NULL;
	traverse = head;
	if(head == NULL)
	{
		head = ing;
	}
	else
	{
		while(traverse->next != NULL) //reachs the end of list 
		{
			traverse = traverse->next;
		}
		traverse->next = ing; //adds the ingredients to the end of list
	}
	
}
void Pizza::remove_ing(string name)
{
	ingredient *traverse, *tail;
	traverse = head;
	while(traverse && traverse->name != name) //searchs related ingredient
	{
		tail = traverse;
		traverse = traverse->next;
	}
	if(traverse == head)
	{
		tail = traverse;
		traverse = traverse->next;
		delete tail;
		head = traverse;
	}
	else if(traverse)
	{
		tail->next = traverse->next;
		delete traverse;
	}
	else
	{
		cout << "You have already removed that ingredient\n";
	}
}
void Pizza::print_ing()
{
	ingredient *traverse;
	traverse = head;
	cout << "(";
	while(traverse) //goes to ingredients one by one and prints it 
	{
		cout << traverse->name + ", "; //prints ingredients name
		traverse = traverse->next; //shifts to next ingredient
	}
	cout << ")" << endl;
}
void Pizza::print_pizza()
{
	cout << name +": "; //prints pizza's name
	print_ing(); //prints the pizza's ingredients
	cout << "size: " << size << ", crust: "<< crust_type << endl << endl; //prints size and crust type 
}
Order::Order(string new_name, Pizza &p, int* new_drinks) //constructor
{
	customer = new_name; //assigns customer's name
	drinks = new_drinks; //assigns drinks
	next = NULL;
	head_pizza = &p;
}
Order::Order(string new_name, Pizza &p) //constructor 
{
	customer = new_name; //assigns customer's name
	head_pizza = &p;
	drinks = NULL;
	next = NULL;
}
Order::~Order() //destructor
{
	Pizza *traverse;
	traverse = head_pizza;
	while(traverse) //deletes the order's pizzas one by one
	{
		head_pizza = head_pizza->counterpart;
		delete traverse;
		traverse = head_pizza;
	}
	delete[] drinks; //deletes the drinks of order
}
void Order::add_pizza(Pizza &new_p)
{
	Pizza *traverse;
	traverse = head_pizza;
	while(traverse->counterpart != NULL) //goes to the end of the pizza list
	{
		traverse = traverse->counterpart;
	}
	traverse->counterpart = &new_p; //adds the pizza to the end of the pizza list
}
double Order::getPrice() //calculates the price of order
{
	double price = 0.0;
	Pizza* traverse;
	traverse = head_pizza;
	while(traverse) //goes to each pizza and adds its cost to the price
	{
		if(traverse->size == "small")
		{
			price += 15.0;
		}
		else if(traverse->size == "medium")
		{
			price += 20.0;
		}
		else if(traverse->size == "big")
		{
			price += 25.0;
		}
		traverse = traverse->counterpart;
	}
	price += drinks[0]*4.0 + drinks[1]*2.0 + drinks[2]*3.0 + drinks[3]*(3.5); //adds the cost of drinks to the price
	return price;
}
void Order::printOrder() //prints order's details
{
	cout << "------------" << endl;
	cout << "Name: "+ customer + "\n\n"; //prints name of customer
	Pizza* traverse;
	traverse = head_pizza;
	while(traverse) //prints all pizzas in the order
	{
		traverse->print_pizza();
		traverse = traverse->counterpart;
	}
	for(int i = 0; i<4;i++) //prints the drinks if its quantity greater than 0
	{
		if(drinks[i] != 0)
		{
			switch(i)
			{
				case 0:
					cout << drinks[i] << " cola, ";
					break;
				case 1:
					cout << drinks[i] << " soda, ";
					break;
				case 2:
					cout << drinks[i] << " ice tea, ";
					break;
				case 3:
					cout << drinks[i] << " fruit juice, ";
					break;
			}
		}
	}
	cout << "\n-------------\n";
}
OrderList::OrderList() //initializes the orderlist
{
	n = 0;
	head = NULL;
}
OrderList::~OrderList() //destructor
{
	Order *traverse;
	traverse = head;
	while(traverse) //deletes all orders one by one
	{
		head = head->next;
		delete traverse;
		traverse = head;
	}
	n = 0;
	head = NULL;
}
void OrderList::takeOrder()
{
	int choice; //keeps the pizza choice of user
	string size_pizza;
	string crust_type_pizza;
	int amount;
	cout << "Pizza Menu\n1. Chicken Pizza (mozarella, chicken, mushroom, corn, olive, onion, tomato)\n2. Broccoli Pizza (mozarella, broccoli, pepperoni, olive, corn, onion)\n3. Sausage Pizza (mozarella, sausage, tomato, olive, mushroom, corn)\n0. Back to main menu\n";
	cin >> choice;

	while(cin.fail() || (choice != 1 && choice != 2 && choice != 3 && choice != 0)) //checks input
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout << "Please type a valid number." << endl;
		cin >> choice;
	}
	if(choice != 0) //if user selects a pizza
	{
		cout << "Select size: small (15 TL), medium (20 TL), big (25 TL)\n";
		cin >> size_pizza;
		while(size_pizza != "small" && size_pizza != "medium" && size_pizza != "big") //checks input 
		{
			cout << "Please type a valid name." << endl;
			cin >> size_pizza;
		}
		cout << "Select crust type: thin, normal, thick\n";
		cin >> crust_type_pizza;
		while(crust_type_pizza != "thin" && crust_type_pizza != "normal" && crust_type_pizza != "thick")  //checks pizza
		{
			cout << "Please type a valid name." << endl;
			cin >> crust_type_pizza;
		}
		Pizza *p = new Pizza(size_pizza,crust_type_pizza,choice); //creates the default pizza
		cout << "Enter the amount:";
		cin >> amount;
		while(cin.fail()) //checks input
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "Please enter an integer" << endl;
			cin >> amount;
		}
		if(choice == 1) //if pizza is chicken pizza
		{
			Pizza *traverse = p; //is used to link pizzas each other
			while(amount>1) //if user wants to add more than one pizza, it is asked whether they want to remove ingredient
			{
				cout << "Please enter the number of the ingredient you want to remove from your pizza.\n1. mozarella\n2. chicken\n3. mushroom\n4. corn\n5. onion\n6. tomato\nPress 0 to save it.\n";
				int s;
				Pizza *newpizza = new Pizza(*p);
				cin >> s;
				while(cin.fail()) //checks input
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(),'\n');
					cout << "Please enter an integer" << endl;
					cin >> s;
				}
				while(s != 0) //'0' saves the ingredients
				{
					switch(s) //removes the related ingredient until user enters '0'
					{
						case 1:
							newpizza->remove_ing("mozarella");
							break;
						case 2:
							newpizza->remove_ing("chicken");
							break;
						case 3:
							newpizza->remove_ing("mushroom");
							break;
						case 4:
							newpizza->remove_ing("corn");
							break;
						case 5:
							newpizza->remove_ing("onion");
							break;
						case 6:
							newpizza->remove_ing("tomato");
							break;
						default:
							cout << "Please enter a valid number\n";
							break;
					}
					cin >> s;
					while(cin.fail()) //checks input
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(),'\n');
						cout << "Please enter an integer" << endl;
						cin >> s;
					}
				}
				traverse->counterpart = newpizza; //links the pizza to the pizza list
				traverse = traverse->counterpart;
				amount--;
			}
			cout << "Please choose a drink:" << endl;
			cout << "0. no drink\n1. cola 4 TL\n2. soda 2 TL\n3. ice tea 3 TL\n4. fruit juice 3.5 TL\nPress -1 for save your order\n";
			int* new_drinks = new int[4]; //keeps the amount of drinks
			for(int i = 0;i<4;i++) //assigns 0 to whole array 
			{
				new_drinks[i] = 0;
			}
			int choice_drink; //keeps the users drink selection
			do{
				cin >> choice_drink;
				while(cin.fail()) //checks input
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(),'\n');
					cout << "Please enter an integer" << endl;
					cin >> choice_drink;
				}
				switch(choice_drink)
				{
					case 0: //'0' means no drink so, resets the whole array
						for(int j = 0; j<4;j++)
						{
							new_drinks[j] = 0;
						}
						break;
					case 1:
						new_drinks[0]++; //adds 1 cola
						break;
					case 2:
						new_drinks[1]++; //adds 1 soda
						break;
					case 3:
						new_drinks[2]++; //adds 1 ice tea
						break;
					case 4:
						new_drinks[3]++; //adds 1 fruit juice
						break;
					case -1: //saves
						break;
					default:
						cout << "Please type a valid number."<<endl;
				}
			}while(choice_drink !=0 && choice_drink != -1);
			string customer_name;
			cout << "Please enter your name:"<<endl;
			cin >> customer_name;
			
			Order *new_order = new Order(customer_name, *p , new_drinks); //creates an order (p is the head of linked pizzas)
			if(head == NULL) //if orderlist is empty
			{
				head = new_order;
			}
			else //if any order exists
			{
				Order *traverse;
				traverse = head;
				while(traverse->next != NULL) //goes to the end of orderlist
				{
					traverse = traverse->next;
				}
				traverse->next = new_order; //adds the neworder
				n++; //increment of order number
			}
			cout << "\nYour order is saved, it will be delivered when it is ready...\n";
			new_order->printOrder();	
		}
		else if(choice == 2) //if pizza is broccoli pizza
		{
			Pizza *traverse = p;
			while(amount>1) //if user wants to add more than one pizza, it is asked whether they want to remove ingredient
			{
				cout << "Please enter the number of the ingredient you want to remove from your pizza.\n1. mozarella\n2. broccoli\n3. pepperoni\n4. olive\n5. corn\n6. onion\nPress 0 to save it.\n";
				int s;
				Pizza *newpizza = new Pizza(*p);
				cin >> s;
				while(cin.fail()) //checks input
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(),'\n');
					cout << "Please enter an integer" << endl;
					cin >> s;
				}
				while(s != 0) //'0' saves the ingredients
				{
					switch(s) //removes the related ingredient until user enters '0'
					{ 
						case 1:
							newpizza->remove_ing("mozarella");
							break;
						case 2:
							newpizza->remove_ing("broccoli");
							break;
						case 3:
							newpizza->remove_ing("pepperoni");
							break;
						case 4:
							newpizza->remove_ing("olive");
							break;
						case 5:
							newpizza->remove_ing("corn");
							break;
						case 6:
							newpizza->remove_ing("onion");
							break;
						default:
							cout << "Please enter a valid number\n";
							break;
					}
					cin >> s;
					while(cin.fail()) //checks input
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(),'\n');
						cout << "Please enter an integer" << endl;
						cin >> s;
					}
				}
				traverse->counterpart = newpizza; //links the pizza to the pizza list
				traverse = traverse->counterpart;
				amount--;
			}
			cout << "Please choose a drink:" << endl;
			cout << "0. no drink\n1. cola 4 TL\n2. soda 2 TL\n3. ice tea 3 TL\n4. fruit juice 3.5 TL\nPress -1 for save your order\n";
			int* new_drinks = new int[4]; //keeps the amount of drinks
			for(int i = 0;i<4;i++) //assigns 0 to whole array 
			{
				new_drinks[i] = 0;
			}
			int choice_drink;
			do{
				cin >> choice_drink;
				while(cin.fail()) //checks input
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(),'\n');
					cout << "Please enter an integer" << endl;
					cin >> choice_drink;
				}
				switch(choice_drink)
				{
					case 0:
						for(int j = 0; j<4;j++) //'0' means no drink so, resets the whole array
						{
							new_drinks[j] = 0;
						}
						break;
					case 1:
						new_drinks[0]++; //adds 1 cola
						break;
					case 2:
						new_drinks[1]++; //adds 1 soda 
						break;
					case 3:
						new_drinks[2]++; //adds 1 ice tea
						break;
					case 4:
						new_drinks[3]++; //adds 1 fruit juice
						break;
					case -1: //saves the drinks
						break;
					default:
						cout << "Please type a valid number." << endl;
						break;
				}
			}while(choice_drink !=0 && choice_drink != -1);
			string customer_name;
			cout << "Please enter your name:"<<endl;
			cin >> customer_name;
			
			Order *new_order = new Order(customer_name, *p , new_drinks); //creates an order (p is the head of linked pizzas)
			if(head == NULL) //if orderlist is empty
			{
				head = new_order;
			}
			else //if any order exists
			{
				Order *traverse;
				traverse = head;
				while(traverse->next != NULL) //goes to the end of order list 
				{
					traverse = traverse->next;         
				}
				traverse->next = new_order; //adds the order
				n++; //increment of order number
			}
			cout << "\nYour order is saved, it will be delivered when it is ready...\n";
			new_order->printOrder();//prints added order	
		}
		else if(choice == 3) //if pizza is sausage pizza
		{
			Pizza *traverse = p;
			while(amount>1) //if user wants to add more than one pizza, it is asked whether they want to remove ingredient
			{
				cout << "Please enter the number of the ingredient you want to remove from your pizza.\n1. mozarella\n2. sausage\n3. tomato\n4. olive\n5. mushroom\n6. corn\nPress 0 to save it.\n";
				int s;
				Pizza *newpizza = new Pizza(*p);
				cin >> s;
				while(cin.fail()) //checks input
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(),'\n');
					cout << "Please enter an integer" << endl;
					cin >> s;
				}
				while(s != 0) //'0' saves the ingredients
				{
					switch(s) //removes the related ingredient until user enters '0'
					{
						case 1:
							newpizza->remove_ing("mozarella");
							break;
						case 2:
							newpizza->remove_ing("sausage");
							break;
						case 3:
							newpizza->remove_ing("tomato");
							break;
						case 4:
							newpizza->remove_ing("olive");
							break;
						case 5:
							newpizza->remove_ing("mushroom");
							break;
						case 6:
							newpizza->remove_ing("corn");
							break;
						default:
							cout << "Please enter a valid number\n";
							break;
					}
					cin >> s;
					while(cin.fail()) //checks input
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(),'\n');
						cout << "Please enter an integer" << endl;
						cin >> s;
					}
				}
				traverse->counterpart = newpizza; //links the pizza to the pizza list
				traverse = traverse->counterpart;
				amount--;
			}
			cout << "Please choose a drink:" << endl;
			cout << "0. no drink\n1. cola 4 TL\n2. soda 2 TL\n3. ice tea 3 TL\n4. fruit juice 3.5 TL\nPress -1 for save your order\n";
			int* new_drinks = new int[4];
			for(int i = 0;i<4;i++)
			{
				new_drinks[i] = 0;
			}
			int choice_drink;
			do{
				cin >> choice_drink;
				while(cin.fail()) //checks input
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(),'\n');
					cout << "Please enter an integer" << endl;
					cin >> choice_drink;
				}
				switch(choice_drink)
				{
					case 0:
						for(int j = 0; j<4;j++) //'0' means no drink so, resets the whole array
						{
							new_drinks[j] = 0;
						}
						break;
					case 1:
						new_drinks[0]++; //adds 1 cola
						break;
					case 2:
						new_drinks[1]++; //adds 1 soda
						break;
					case 3:
						new_drinks[2]++; //adds 1 icetea
						break;
					case 4:
						new_drinks[3]++; //adds 1 fruit juice
						break;
					case -1: //saves the drinks
						break;
					default:
						cout << "Please type a valid number." << endl;
				}
			}while(choice_drink !=0 && choice_drink != -1);
			string customer_name;
			cout << "Please enter your name:"<<endl;
			cin >> customer_name;
			
			Order *new_order = new Order(customer_name, *p , new_drinks); //creates an order (p is the head of linked pizzas)
			if(head == NULL) //if orderlist is empty
			{
				head = new_order;
			}
			else //if any order exists
			{
				Order *traverse;
				traverse = head;
				while(traverse->next != NULL) //goes to the end of orderlist
				{
					traverse = traverse->next;
				}
				traverse->next = new_order; //adds the new order
				n++; //increment of order number
			}
			cout << "\nYour order is saved, it will be delivered when it is ready...\n";
			new_order->printOrder();	
		}
	}
}
void OrderList::listOrders()
{
	Order *traverse;
	traverse = head;
	int count = 1; 
	if(head == NULL) //if orderlist is emty
	{
		cout << "empty" << endl;
	}
	else
	{
		while(traverse) //goes each order and prints it 
		{
			cout << count << endl;
			traverse->printOrder();
			traverse = traverse->next;
			count++;
		}
	}
}
void OrderList::deliverOrders() 
{
	string delivery_name; //name of the order which will be delivered
	Order *traverse, *tail; //is used to remove delviered order
	double delivery_price; //is used to apply discount
	listOrders(); //prints orders
	char answer; //keeps promotion code answer 'y' or 'n'
	if(head != NULL)
	{
		cout << "Please write the customer name in order to deliver his/her order: ";
		cin >> delivery_name;
		traverse = head;
		while(traverse && (traverse->customer != delivery_name)) //searchs the name
		{
			tail = traverse;
			traverse = traverse->next;
		}
		if(traverse == NULL) //if it does not exist
		{
			cout << "Wrong name" << endl;
		}
		else if(traverse->customer == delivery_name) //if exists
		{
			traverse->printOrder(); //prints related order
			delivery_price = traverse->getPrice(); //prints the price of order
			cout << "Following order is delivering..." << endl;
			cout<<"Total price: "<< delivery_price<<endl;
			bool flag = false; //is used to construct a loop
			do
			{
				cout<<"Do you have a promotion code? (y/n)" << endl;
				cin >> answer;
				if(answer == 'n') //if user does not want to enter a code
				{
					cout << "The order is delivered succesfully!" << endl << endl;
					flag = true;
				}
				else if (answer == 'y') //if user wants to enter a code
				{
					string code; //keeps code
					cout << "Please enter your code: ";
					cin.ignore();
					getline(cin, code); //gets code
					if(code == "I am a student") //if code is correct
					{
						delivery_price = (delivery_price*9.0)/10.0; //applies %10 discount
						cout << "Discounted price: " << delivery_price<<endl;
						cout << "The order is delivered succesfully!"<<endl;
						flag = true; //loop break
					}
					else //loop continues
					{
						cout << "Promotion code is not accepted." << endl;
					}
				}
			}while(!flag);
			if(traverse == head) //if the order is at the head of orderlist
			{
				head = traverse->next;
				delete traverse;
				n--;
			}
			else //if order is not at the head of orderlist
			{
				tail->next = traverse->next;
				delete traverse;
				n--;
			}
		}
	}
}
int main()
{
	int operation; //keeps user's operation 
	OrderList *orders = new OrderList();
	do
	{
		cout << "Welcome to Unicorn Pizza!\n1. Add an order\n2. List orders\n3. Deliver order\n4. Exit\nChoose what to do: ";
		cin >> operation;
		while(cin.fail()) //checks input
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "Please enter an integer" << endl;
			cin >> operation;
		}
		switch(operation)
		{
			case 1: //adds order
				orders->takeOrder();
				break;
			case 2: //lists order
				orders->listOrders();
				break;
			case 3: //delivers order
				orders->deliverOrders();
				break;
			case 4: //closes program
				cout << "Goodbye..." << endl;
				break;
			default:
				cout << "Please type a valid number." << endl;
		}		
	}while(operation != 4);
	delete orders;
	return 0;
}