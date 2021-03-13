
#include <iostream>
#include <string>

// //1. Создать абстрактный класс Figure(фигура).Его наследниками являются классы Parallelogram(параллелограмм) и Circle(круг).
// //Класс Parallelogram — базовый для классов Rectangle(прямоугольник), Square(квадрат), Rhombus(ромб).Для всех классов создать конструкторы.
// //Для класса Figure добавить чисто виртуальную функцию area() (площадь).Во всех остальных классах переопределить эту функцию, 
// //исходя из геометрических формул нахождения площади.
//
//class Figure
//{
//public:
//	Figure() { std::cout << "figure constructor" << std::endl; };
//	virtual double area() = 0;
//	virtual ~Figure() { std::cout << "figure destructor" << std::endl; };
//};
//
//
//
//class Circle : public Figure
//{
//private:
//	double m_radius;
//public:
//	Circle() { std::cout << "Circle constructor" << std::endl; };
//	Circle(double m_radius) : m_radius(m_radius) {
//		std::cout << "Circle constructor" << std::endl;
//	};
//	
//	virtual double area (double m_radius) const override {
//		return  m_radius * m_radius * 3.14;
//	}
//	~Circle() {
//		std::cout << "Circle destructor" << std::endl;
//	};
//};
//
//
//class Parallelogram : public Figure 
//{
//private:
//	double m_height = 0;
//
//public:
//	Parallelogram() {};
//	virtual double area(double m_height, double m_lenght) {
//		return m_height * m_lenght;
//		
//	};
//};
//
//
//class Rectangle : public Parallelogram
//{
//public:
//	Rectangle() {};
//	~Rectangle() {};
//
//private:
//
//};
//
//class Square : public Parallelogram
//{
//public:
//	Square() {};
//	~Square() {};
//
//private:
//
//};
//
//class Rhombus : public Parallelogram
//{
//public:
//	Rhombus() {};
//	~Rhombus() {};
//
//private:
//
//};


// 2. Создать класс Car(автомобиль) с полями company(компания) и model(модель).Классы - наследники: PassengerCar(легковой автомобиль) и Bus(автобус).
// От этих классов наследует класс Minivan(минивэн).Создать конструкторы для каждого из классов, чтобы они выводили данные о классах.
// Создать объекты для каждого из классов и посмотреть, в какой последовательности выполняются конструкторы.Обратить внимание на проблему «алмаз смерти».
// Примечание : если использовать виртуальный базовый класс, то объект самого "верхнего" базового класса создает самый "дочерний" класс.

class Car
{
protected:
	std::string m_company;
	std::string m_model;
public:
	Car() {};
	Car(std::string company, std::string model) : m_company(company), m_model(model)
	{
		std::cout << "constructor Car" << std::endl;
	};
	virtual std::string getCompany() { return m_company; }
	virtual std::string getModel() { return m_model; }
	virtual ~Car() { std::cout << "destructor Car" << std::endl; };
};

class PassengerCar : virtual public Car
{
public:
	PassengerCar() {};
	PassengerCar(std::string company, std::string model) : Car(company, model)
	{
		std::cout << "constructor PassengerCar" << std::endl;
	};
	std::string getCompany() { return m_company;}
	std::string getModel() { return m_model; }
	~PassengerCar() { std::cout << "destructor PassengerCar" << std::endl; };
};

class Bus : virtual public Car
{
public:
	Bus() {};
	Bus(std::string company, std::string model) : Car(company, model)
	{
		std::cout << "constructor Bus" << std::endl;
	};
	std::string getCompany() { return m_company; }
	std::string getModel() { return m_model; }
	~Bus() { std::cout << "destructor Bus" << std::endl; };
};

class Minivan : public PassengerCar, public Bus
{
public:
	Minivan(std::string company, std::string model) :
		Bus(company, model), PassengerCar(company, model), Car(company, model)
	{
		std::cout << "constructor Minivan" << std::endl;
	};
	std::string getCompany() { return m_company; }
	std::string getModel() { return m_model; }
	~Minivan() { std::cout << "destructor Minivan" << std::endl; };
};


// 3. Создать класс : Fraction(дробь).Дробь имеет числитель и знаменатель(например, 3 / 7 или 9 / 2).Предусмотреть, чтобы знаменатель не был равен 0. 
//Перегрузить :
//    математические бинарные операторы(+, -, *, / ) для выполнения действий с дробями
//    унарный оператор(-)
//    логические операторы сравнения двух дробей(== , != , <, >, <= , >= ).
//  Примечание : Поскольку операторы < и >= , > и <= — это логические противоположности, попробуйте перегрузить один через другой.
 //   Продемонстрировать использование перегруженных операторов.




// 4. Создать класс Card, описывающий карту в игре БлэкДжек.У этого класса должно быть три поля : масть, значение карты и положение карты
// (вверх лицом или рубашкой).Сделать поля масть и значение карты типом перечисления(enum).Положение карты - тип bool.
// Также в этом классе должно быть два метода :
// метод Flip(), который переворачивает карту, т.е.если она была рубашкой вверх, то он ее поворачивает лицом вверх, и наоборот.
// метод GetValue(), который возвращает значение карты, пока можно считать, что туз = 1.

// Исходим из того, что играем одной колодой, т.о. 4 масти по 13 карт (от 2 до туза)

class Card
{
public:
	enum suit { hearts, spades, cross, diamonds }; // масти
	enum rank         // значение карт
	{
		RANK_2,	RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_9, RANK_10, RANK_jack, RANK_queen, RANK_king, RANK_ace,
	};
	
	bool faceUp=false;

	Card() {};
	bool Flip(bool faceUp)
	{
		faceUp = !faceUp;
		// проверочный вывод
		std::cout << "faceUp must be 1 - " << faceUp << std::endl;
		return faceUp;
	}


	int GetValue(int cardName)
	{
		switch (cardName)
		{
		case RANK_2: return 2;
			std::cout << "Value - " << "2" << std::endl;
			break
		}
		// проверочный вывод
		std::cout << "Value must be 10 - " << value << std::endl;
		return  value;
	};
	
};



int main()
{

	// Task 1.
	
	/*std::cout << "Enter the radius of circle:" << std::endl;
	std::cin >> radius;
	Circle Circle;
	std::cout << "square of Circle =  " << Circle.area(2) << std::endl;*/


	
	// Task 2. Done. Прописала и конструкторы, и деструкторы, чтобы было видно, что когда создается и удаляется.
	Car Car ("BMV", "X5");
	std::cout << "Car is " << Car.getModel() << " by "<< Car.getCompany() << " company." << std::endl;
	PassengerCar PassengerCar("Hundai", "Solaris");
	std::cout << "PassengerCar is " << PassengerCar.getModel ()<< " by " << PassengerCar.getCompany() << " company." << std::endl;
	Bus Bus("Hundai", "Bus");
	std::cout << "Car is " << Bus.getModel() << " by " << Bus.getCompany() << " company." << std::endl;
	Minivan Minivan("Mersedes", "Minivan");
	std::cout << "Car is " << Minivan.getModel() << " by " << Minivan.getCompany() << " company." << std::endl;





	// Task 4.
	Card card;
	card.Flip(0);
	card.GetValue(Card::RANK_king);

	enum mum {a,b,c};
	std::cout << "MUM - " << mum (a) << std::endl;
}

