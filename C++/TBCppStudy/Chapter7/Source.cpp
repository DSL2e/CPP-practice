#include<iostream>
#include<cmath>
#include<vector>
#include<array>
#include<tuple>
#include<functional>
#include<cassert>
#include<string>
#include<cstdarg>
using namespace std;

double findAverage(int count, ...)
{
	double sum = 0;
	va_list list;

	va_start(list, count);

	// type도 미리 정해둬야함.
	for (int arg = 0; arg < count; arg++)
	{
		sum += va_arg(list, int);
	}
	va_end(list);

	return sum / count;
}

int main(int argc, char* argv[])
{
	array<int, 5> my_array{ 1,2,3,4,5 };

	cout << findAverage(5, my_array) << endl;
}

//값에 의한 인수 전달(Call by value)
 /* 값만 전달하는 것 -> 메인과 함수에서의 주소가 다름
	void doSomething(int y)
	{
		cout << "In func " << y << " " << &y <<endl;
	}
	int main(void)
	{
		int x{6};

		cout << "In main " << x << " " << &y << endl;
	
		doSomething(x); // x : argument (=actual parameters)
		doSomething(x+1);

		return 0;
	}
 */

// 참소에 의한 인수 전달(Call by Reference)
 // 선호하는 방법. 단점?? 리터럴 상수를 넣었을 때 오류 -> const int &x (but, 안에서 수정 불가능)
 // 
 /* 변수 자체를 넘기는 방식 -> 메인과 함수에서의 주소가 같음
	void addOne(int &y)
	{
		cout << "In func " << y << " " << &y << endl;
		y = y + 1;
	}

	int main(void)
	{
		int x{5};

		cout << "In main " << x << " " << &x << endl;
		addOne(x);
		cout << "In main " << x << " " << &x << endl;
		return 0;
	}
 */
/* 포인터 
	void addOne(int* &y)
	{
		(*y)++;
		cout << "In func " << *y << " " << &y << endl;
	}

	int main(void)
	{
		int x{ 5 };
		int* ptr;

		ptr = &x;

		cout << "In main " << *ptr << " " << &ptr << endl;
		addOne(ptr);
		cout << "In main " << *ptr << " " << &ptr << endl;
		return 0;
	}
*/
/* 배열
	void foo(vector<int> &arr)
	{
		for (auto &n : arr)
			n++;
	}
	int main(void)
	{
		vector<int> arr{ 1,2,3,4 };
		for (const int& n : arr)
			cout << n << " ";
		cout << endl;
		foo(arr);
		for (const int& n : arr)
			cout << n << " ";
		cout << endl;
		return 0;
	}
*/

// 주소에 의한 인수 전달(Call by Address)

// 다양한 반환 값을 (값, 참조, 주소, 구조체, 튜플)
 // 1. 값을 받는다 -> 복사해서 들어가므로 속도가 드림

 // 2. 주소를 리턴 -> 함수에선 영역을 넘어가면 사라지므로 정말 위험

 // 3. 레퍼런스를 리턴 -> 메모리 공간은 안전하게 잡아두고 레퍼런스만 보내 작업

 // 4. 여러 개를 리턴
	/* 1. 구조체
		S getStrct()
		{
			S my_s{ 1,2,3,4 };
			return my_s;
		}

		int main(void)
		{
			S my_s = getStrct();
			cout << my_s.a << endl;
		}
	*/

	/*	2. 튜플
		std::tuple<int, double> getTuple()
		{
			int a = 10;
			int d = 3.14;
			return std::make_tuple(a, d);
		}

		int main(void)
		{
			std::tuple<int, double> my_tp = getTuple();
			cout << std::get<0>(my_tp) << endl; // a
			cout << std::get<1>(my_tp) << endl; // d

			// c++ 17
			auto [a, d] = getTuple();
			cout << a << endl;
			cout << d << endl;
			return 0;
		}
	*/

// 안라인 함수
 // cout << (5 > 6 ? 6 : 5) << endl; 처럼 컴파일 단계에서 만들어서 빠르게 처리하게 됨. 
 // 컴파일러한테 해달라고 요청하는 것이고 컴파일러가 inline를 적용할 지 결정
/*
	inline int min(int x, int y)
	{
		return ((x > y) ? y : x);
	}

	int main(void)
	{
		cout << min(5, 6) << endl;
		cout << min(3, 2) << endl;
	}
*/

// 함수 오버로딩
 // 동일한 함수를 여러개 만드는 것
 // 들어오는 매개변수가 다른데 함수 기능이 비슷할 때 주로 사용 
 // 컴파일 할 때, 가장 맞는 어떤 함수를 선택할 지 결정 (return type로는 구별 x. argument와 parameter로 구분)
 /*
	int add(int x, int y)
	{
		return x + y;
	}

	double add(double x, double y)
	{
		return x + y;
	}

	int main(void)
	{
		add(1, 2);
		add(3.0, 4.0);
		return 0;
	}
 */

// 매개변수의 기본값
 // 매개변수의 기본값을 통해 argument 입력을 생략하는 방법
 // 주로 header에만 기본 설정을 해줌. (둘다는 x)
 /*
	void print(int x = 10, int y =20, int z = 30)
	{
		cout << x << " " << y << " " << z << endl;
	}

	int main(void)
	{
		print(100);
		print(100, 200);
		print(100, 200, 300);
	}
 */

// 함수 포인터
 // 함수도 포인터로 주소를 가지고 있고 해당 내용을 처리하는 것
 /*
	int func()
	{
		return 5;
	}

	int goo()
	{
		return 10;
	}
	int main(void)
	{
		int(*fcnptr)() = func;
		cout << fcnptr() << endl;

		fcnptr = goo;
		cout << fcnptr() << endl;

		// functional 사용
		std::function<bool(const int&)> fcnptr;

		return 0;
	}
 */

//std::vector를 스택처럼 사용하기
 // 내부에 new와 delete를 적게 호출하도록 하는 것이 중요
 /*

	std::vector<int> v{ 1,2,3 };
	std::vector<int> stack;

	v.resize(2);

	// size: 몇개를 사용 , capacity: 가지고 있는 메모리

	for (auto& e : v)
		cout << e << " ";
	cout << endl;

	cout << v.size() << " " << v.capacity() << endl; // 2 ,3으로 출력됨

	// v.reserve(number) - 메모리 공간 미리 확보 >> capacity를 줄이고 늘릴 필요가 없어서 효율이 좋음(공간 남비가 있을 수도)
	stack.push_back(3);
	stack.push_back(5);
	stack.push_back(7);
	stack.pop_back();
	stack.pop_back();
	stack.pop_back();
 */

// 재귀적 함수 호출

// 방어적 프로그래밍의 개념
 // syntax error
 // semantic errors(프로그래머가 신경써야하는 부분)	
 // violated assumption
 /* Runtime 오류 -> 메모리 억세스가 가능한 범위를 지정해준다.
   string hello = "Hello, my name is Jack jack"
   int ix;
   cin >> ix; // 1004 입력
   cout << hello[ix] << endl;
 */

// 단언하기 assert #include<cassert>
 // 컴파일러의 도움을 받는 것
 /*
	void printValue(const array<int, 5> &my_array, const int &ix)
	{
		// Debug mode에서만 실행
		// Runtime error가 발생하긴 하지만, 어디서 오류가 발생했는지 알 수 있음.
		assert(ix >= 0);
		assert(ix <= my_array.size() - 1);
	}

	int main(void)
	{

		array<int, 5> my_array{ 1,2,3,4,5 };
		printValue(my_array, 100);

		// static_assert(변수+조건, "문구") - 컴파일 시, 오류를 발생
	}
 */

// 명령줄 인수
	/*
	int main(int argc, char* argv[])
	{
		for (int count = 0; count < argc; ++count)
		{
			std::string argv_single = argv[count];

			if (count == 1)
			{
				int input_number = std::stoi(argv_single);
				cout << input_number << endl;
			}
			cout << argv_single << endl;
		}
	}
	*/

// 생략부호 Ellipsis (#include<cstdarg>)
 // 갯수가 맞아야하고 va_arg에서 type를 미리 정의해야함 
 // 매개변수의 갯수가 정하지않고 사용
 /*
	double findAverage(int count, ...)
	{
		double sum = 0;
		va_list list;

		va_start(list, count);

		// type도 미리 정해둬야함.
		for (int arg = 0; arg < count ; arg++)
			sum += va_arg(list, int);

		va_end(list);

		return sum / count;
	}

	int main(int argc, char* argv[])
	{
		cout << findAverage(1, 1, 2, 3, "Hello", "c") << endl;
		cout << findAverage(3, 1, 2, 3) << endl;
		cout << findAverage(5, 1, 2, 3, 4 ,5) << endl;
		cout << findAverage(10, 1, 2, 3, 4, 5) << endl; // 갯수가 잘못되어 오류
	}
 */

// tip
// 참소에 의한 인수 전달(Call by Reference)
  // 입력 값은 const로 앞에, 출력 값은 뒤에 적는다. ex. void getSinCos(const double degrees, double &sin_out, double &cos_out) 
  // 계산 하는 값은 const를 쓰는 습관 + 호춯할 때 마다 하용 하는 것은 static으로 재사용 ex. static const double pi = 3.141592;
  // 입력 값은 const int &x로 거의 무조건 사용 (why? 리터럴 상수도 받을 수 있고 메모리 공간 절약 가능)
  // typedef int* pint; -> 이런방식으로 주로 변경해서 사용