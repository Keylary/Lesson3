
#include <iostream>
#include <string>
#include <cassert>

 //1. Создать абстрактный класс Figure(фигура).Его наследниками являются классы Parallelogram(параллелограмм) и Circle(круг).
 //Класс Parallelogram — базовый для классов Rectangle(прямоугольник), Square(квадрат), Rhombus(ромб).Для всех классов создать конструкторы.
 //Для класса Figure добавить чисто виртуальную функцию area() (площадь).Во всех остальных классах переопределить эту функцию, 
 //исходя из геометрических формул нахождения площади.

class Figure
{
public:
	Figure() { };
	virtual double area() = 0;
	virtual ~Figure() { };
};

class Circle : public Figure
{
private:
	double m_radius = 0;
public:
	
	Circle() { };
	Circle(double m_radius) : m_radius(m_radius) {};

	void setRadius(double radius) {
		m_radius = radius;
	}
	 double area () override 
	 {
		return  m_radius * m_radius * 3.14; // Число Пи, точность достаточна для теста, я думаю.
	 }
	~Circle() {	};	
};

class Parallelogram : public Figure 
{
protected:
	double m_height = 0; // высота
	double m_lenght = 0; // длина основания

public:
	Parallelogram() {};

	void setHeight(double height) {
		m_height = height;
	}
	void setLenght(double lenght) {
		m_lenght = lenght;
	}
	double area() {
		return m_height * m_lenght;
	};
	~Parallelogram() {};
};

class Rectangle : public Parallelogram
{
public:
	Rectangle() {};
	double area() {
		return m_height * m_lenght;
	};
	~Rectangle() {};
};

class Square : public Parallelogram
{
public:
	Square() {};
	double area() {
		return m_height * m_lenght;
	};
	~Square() {};
};

class Rhombus : public Parallelogram
{
public:
	Rhombus() {};
	double area() {
	return m_height * m_lenght;
	};
	~Rhombus() {};
};


// 2. Создать класс Car(автомобиль) с полями company(компания) и model(модель).Классы - наследники: PassengerCar(легковой автомобиль) и Bus(автобус).
// От этих классов наследует класс Minivan(минивэн).Создать конструкторы для каждого из классов, чтобы они выводили данные о классах.
// Создать объекты для каждого из классов и посмотреть, в какой последовательности выполняются конструкторы. Обратить внимание на проблему «алмаз смерти».
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
//  Продемонстрировать использование перегруженных операторов.

class Fraction
{
private:
	int m_numerator;
	int m_denominator;
	
public:
	Fraction() // конструктор по умолчанию 
	{
		m_numerator = 0;
		m_denominator = 1;
	}
	
	Fraction(int numerator, int denominator) // конструктор с проверкой на ноль
	{
		assert(denominator != 0);
		m_numerator = numerator;
		m_denominator = denominator;
	}

	int getNumerator() { return m_numerator; }
	int getDenominator() { return m_denominator; }
	
	friend Fraction operator_plus(const Fraction& fract1, const Fraction& fract2);
	friend Fraction operator_minus(const Fraction& fract1, const Fraction& fract2);
	friend Fraction operator_multiplication(const Fraction& fract1, const Fraction& fract2);
	friend Fraction operator_division(const Fraction& fract1, const Fraction& fract2);

	friend Fraction operator_minus_unar(const Fraction& fract1);

	friend bool operator_equal(const Fraction& fract1, const Fraction& fract2);
	friend bool operator_nonEqual(bool operator_equal);
	friend bool operator_more(const Fraction& fract1, const Fraction& fract2);
	friend bool operator_less_equal(bool operator_more);
	friend bool operator_less(const Fraction& fract1, const Fraction& fract2);
	friend bool operator_more_equal(bool operator_less);
};

int gcd(int a, int b) {                           //наибольший общий делитель
	while (b > 0) {
		int c = a % b;
		a = b;
		b = c;
	}
	return a;
}

int lcm(int a, int b) {                           // наименьшее общее кратное
	return gcd(a, b) * a * b;
}

Fraction operator_plus(const Fraction& fract1, const Fraction& fract2)
{
	int lcm_tmp = lcm(fract1.m_denominator, fract2.m_denominator);

	int operator_plus_denominator = fract1.m_denominator * (lcm_tmp / fract1.m_denominator);
	int operator_plus_numerator = fract1.m_numerator * (lcm_tmp / fract1.m_denominator) + fract2.m_numerator * (lcm_tmp / fract2.m_denominator);
	
	return Fraction(operator_plus_numerator, operator_plus_denominator);
}

Fraction operator_minus(const Fraction& fract1, const Fraction& fract2)
{
	int lcm_tmp = lcm(fract1.m_denominator, fract2.m_denominator);

	int operator_minus_denominator = fract1.m_denominator * (lcm_tmp / fract1.m_denominator);
	int operator_minus_numerator = fract1.m_numerator * (lcm_tmp / fract1.m_denominator) - fract2.m_numerator * (lcm_tmp / fract2.m_denominator);

	return Fraction(operator_minus_numerator, operator_minus_denominator);
}

Fraction operator_multiplication(const Fraction& fract1, const Fraction& fract2)
{
	int operator_multiplication_denominator = fract1.m_denominator * fract2.m_denominator;
	int operator_multiplication_numerator = fract1.m_numerator * fract2.m_numerator;

	return Fraction(operator_multiplication_numerator, operator_multiplication_denominator);
}

Fraction operator_division(const Fraction& fract1, const Fraction& fract2)
{
	int operator_division_denominator = fract1.m_denominator * fract2.m_numerator;
	int operator_division_numerator = fract1.m_numerator * fract2.m_denominator;

	return Fraction(operator_division_numerator, operator_division_denominator);
}

Fraction operator_minus_unar(const Fraction& fract1) {
	int operator_division_numerator = -fract1.m_numerator;
	int operator_division_denominator = fract1.m_denominator;
	return Fraction(operator_division_numerator, operator_division_denominator);
}


bool operator_equal(const Fraction& fract1, const Fraction& fract2) 
{
	int lcm_tmp = lcm(fract1.m_denominator, fract2.m_denominator);

	int operator_equal_denominator = fract1.m_denominator * (lcm_tmp / fract1.m_denominator);
	int operator_numerator1 = fract1.m_numerator * (lcm_tmp / fract1.m_denominator);
	int operator_numerator2 = fract2.m_numerator * (lcm_tmp / fract2.m_denominator);

	return operator_numerator1 == operator_numerator2;
}

bool operator_nonEqual(bool operator_equal) { return !operator_equal; }

bool operator_more(const Fraction& fract1, const Fraction& fract2)
{
	int lcm_tmp = lcm(fract1.m_denominator, fract2.m_denominator);

	int operator_equal_denominator = fract1.m_denominator * (lcm_tmp / fract1.m_denominator);
	int operator_numerator1 = fract1.m_numerator * (lcm_tmp / fract1.m_denominator);
	int operator_numerator2 = fract2.m_numerator * (lcm_tmp / fract2.m_denominator);

	return operator_numerator1 > operator_numerator2;
}

bool operator_less_equal(bool operator_more) { return !operator_more; }

bool operator_less(const Fraction& fract1, const Fraction& fract2)
{
	int lcm_tmp = lcm(fract1.m_denominator, fract2.m_denominator);

	int operator_equal_denominator = fract1.m_denominator * (lcm_tmp / fract1.m_denominator);
	int operator_numerator1 = fract1.m_numerator * (lcm_tmp / fract1.m_denominator);
	int operator_numerator2 = fract2.m_numerator * (lcm_tmp / fract2.m_denominator);

	return operator_numerator1 < operator_numerator2;
}

bool operator_more_equal(bool operator_less) { return !operator_less; }


// 4. Создать класс Card, описывающий карту в игре БлэкДжек.У этого класса должно быть три поля : масть, значение карты и положение карты
// (вверх лицом или рубашкой).Сделать поля масть и значение карты типом перечисления(enum).Положение карты - тип bool.
// Также в этом классе должно быть два метода :
// метод Flip(), который переворачивает карту, т.е.если она была рубашкой вверх, то он ее поворачивает лицом вверх, и наоборот.
// метод GetValue(), который возвращает значение карты, пока можно считать, что туз = 1.

class Card
{
public:
	enum suit { hearts, spades, cross, diamonds }; // масти
	enum rank         // значение карт
	{
		RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_9, RANK_10, RANK_jack, RANK_queen, RANK_king, RANK_ace,
	};

	bool faceUp = false;

	Card() {};
	bool Flip(bool faceUp)
	{
		faceUp = !faceUp;
		// проверочный вывод
		std::cout << "faceUp  - " << faceUp << std::endl;
		return faceUp;
	}


	int GetValue(Card::rank cardName) // Есть предупреждение, но собирает и работает.
	{

		switch (cardName)
		{
		case RANK_2: 
			std::cout << "Value - " << "2" << std::endl;
			return 2;			
			break;
		case RANK_3: 
			std::cout << "Value - " << "3" << std::endl;
			return 3;
			break;
		case RANK_4: 
			std::cout << "Value - " << "4" << std::endl; 
			return 4;
			break;
		case RANK_5 :
			std::cout << "Value - " << "5" << std::endl;
			return 5;
			break;
		case RANK_6: 
			std::cout << "Value - " << "6" << std::endl;
			return 6;
			break;
		case RANK_7: 
			std::cout << "Value - " << "7" << std::endl;
			return 7;
			break;
		case RANK_8: 
			std::cout << "Value - " << "8" << std::endl;
			return 8;
			break;
		case RANK_9: 
			std::cout << "Value - " << "9" << std::endl;
			return 9;
			break;
		case RANK_10: 
			std::cout << "Value - " << "10" << std::endl;
			return 10;
			break;
		case RANK_jack: 
			std::cout << "Value - " << "10" << std::endl;
			return 10;
			break;
		case RANK_queen: 
			std::cout << "Value - " << "10" << std::endl;
			return 10;
			break;
		case RANK_king: 
			std::cout << "Value - " << "10" << std::endl;
			return 10;
			break;
		case RANK_ace: 
			std::cout << "Value - " << "1" << std::endl;
			return 1;
			break;
		default: return 0;
			break;
		}
		
	};
	
};



int main()
{

	// Task 1. Done.  
	
	std::cout << "Task 1" << std::endl;
	Circle Circle;
	Circle.setRadius(10.0);
	std::cout << "square of Circle =  " << Circle.area() << std::endl;

	Parallelogram Parallelogram;
	Parallelogram.setHeight(2);
	Parallelogram.setLenght(3);
	std::cout << "square of Parallelogram =  " << Parallelogram.area() << std::endl;

	Rectangle Rectangle;
	Rectangle.setHeight(4);
	Rectangle.setLenght(4);
	std::cout << "square of Rectangle =  " << Rectangle.area() << std::endl;

	Square Square;
	Square.setHeight(5);
	Square.setLenght(5);
	std::cout << "square of Square =  " << Square.area() << std::endl;

	Rhombus Rhombus;
	Rhombus.setHeight(6);
	Rhombus.setLenght(6);
	std::cout << "square of Rhombus =  " << Rhombus.area() << std::endl;
	

	// Task 2. Done. Прописала и конструкторы, и деструкторы, чтобы было видно, что когда создается и удаляется. Для просмотра остальных заданий это лучше закомментить,
	// ибо мусорит безбожно.
	std::cout << "Task 2" << std::endl;
	Car Car ("BMV", "X5");
	std::cout << "Car is " << Car.getModel() << " by "<< Car.getCompany() << " company." << std::endl;
	PassengerCar PassengerCar("Hundai", "Solaris");
	std::cout << "PassengerCar is " << PassengerCar.getModel ()<< " by " << PassengerCar.getCompany() << " company." << std::endl;
	Bus Bus("Hundai", "Bus");
	std::cout << "Car is " << Bus.getModel() << " by " << Bus.getCompany() << " company." << std::endl;
	Minivan Minivan("Mersedes", "Minivan");
	std::cout << "Car is " << Minivan.getModel() << " by " << Minivan.getCompany() << " company." << std::endl;


	// Task 3. Done. 

	std::cout << "Task 3" << std::endl;
	Fraction fract1(2, 3);
	Fraction fract2(1, 7);

	std::cout << "Arithmetic operators" << std::endl;

	Fraction NewFractionPlus = operator_plus(fract1, fract2);
	std::cout << fract1.getNumerator() << "/" << fract1.getDenominator() << " + " << fract2.getNumerator() << "/" << fract2.getDenominator() << " = " 
		<< NewFractionPlus.getNumerator() << "/" << NewFractionPlus.getDenominator() << std::endl;
	
	Fraction NewFractionMinus = operator_minus(fract1, fract2);
	std::cout << fract1.getNumerator() << "/" << fract1.getDenominator() << " - " << fract2.getNumerator() << "/" << fract2.getDenominator() << " = " 
		<< NewFractionMinus.getNumerator() << "/" << NewFractionMinus.getDenominator() << std::endl;
	
	Fraction NewFractionMultiplication = operator_multiplication(fract1, fract2);
	std::cout << fract1.getNumerator()<<"/"<<fract1.getDenominator()<< " * "<< fract2.getNumerator() << "/" <<fract2.getDenominator()<< " = "
		<< NewFractionMultiplication.getNumerator() << "/" << NewFractionMultiplication.getDenominator() << std::endl;

	Fraction NewFractionDivision = operator_division(fract1, fract2);
	std::cout << fract1.getNumerator() << "/" << fract1.getDenominator() << " / " << fract2.getNumerator() << "/" << fract2.getDenominator() << " = " 
		<< NewFractionDivision.getNumerator() << "/" << NewFractionDivision.getDenominator() << std::endl;

	std::cout << "Unary operator" << std::endl;

	Fraction NewFractionUnar = operator_minus_unar(fract1);
	std::cout << " - " << fract1.getNumerator() << "/" << fract1.getDenominator() << " = " << NewFractionUnar.getNumerator() << "/" 
		<< NewFractionUnar.getDenominator() << std::endl;

	std::cout << "Logical operators" << std::endl;

	// логический оператор ==
	std::cout << fract1.getNumerator() << "/" << fract1.getDenominator() << (operator_equal(fract1, fract2) ? " " : " !")<< "= " << fract2.getNumerator() 
		<< "/" << fract2.getDenominator()<<std::endl;
	
	// логический оператор != через предыдущий
	std::cout << fract1.getNumerator() << "/" << fract1.getDenominator() << (operator_nonEqual(operator_equal(fract1, fract2)) ? " !" : " ") << "= " << fract2.getNumerator() 
		<< "/" << fract2.getDenominator() << std::endl;

	// Логический оператор >
	std::cout << fract1.getNumerator() << "/" << fract1.getDenominator() << (operator_more(fract1, fract2) ? " > " : " <= ") << fract2.getNumerator()
		<< "/" << fract2.getDenominator() << std::endl;

	// Логический оператор <= через предыдущий
	std::cout << fract1.getNumerator() << "/" << fract1.getDenominator() << (operator_less_equal(operator_more(fract1, fract2)) ? " <= " : " > ") << fract2.getNumerator()
		<< "/" << fract2.getDenominator() << std::endl;

	// Логический оператор <
	std::cout << fract1.getNumerator() << "/" << fract1.getDenominator() << (operator_less(fract1, fract2) ? " < " : " >= ") << fract2.getNumerator()
		<< "/" << fract2.getDenominator() << std::endl;

	// Логический оператор >= через предыдущий
	std::cout << fract1.getNumerator() << "/" << fract1.getDenominator() << (operator_more_equal(operator_less(fract1, fract2)) ? " >= " : " < ") << fract2.getNumerator()
		<< "/" << fract2.getDenominator() << std::endl;



	// Task 4. Done. Сделала вывод для проверки - FaceUp и value. Работает, хоть и выводит предупреждение.

	std::cout << "Task 4" << std::endl;
	Card card;
	card.Flip(1);
	card.GetValue(Card::RANK_king);
	

	return 0;

}

