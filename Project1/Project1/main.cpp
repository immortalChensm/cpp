#include <iostream>
#include <string>
#include <ctime>
#include <array>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <functional>


using namespace std;

//void* operator new(size_t size) {
//
//	return malloc(size);
//}
//void* operator new[](size_t size) {
//
//	return malloc(size);
//}
//
//void operator delete(void* p) {
//
//	free(p);
//}
//void operator delete[](void* p) {
//
//	free(p);
//}


namespace test1
{
	class A {
	public:
		static void* operator new(size_t size) {

			A* templink;
			if (buffer == nullptr) {

				size_t s = size * blockSize;
				buffer = reinterpret_cast<A*>(new char[s]);


				templink = buffer;

				for (; templink != &buffer[blockSize - 1]; templink++) {

					templink->next = templink + 1;
				}
				templink->next = nullptr;
				mallocCount++;
			}

			templink = buffer;
			buffer = buffer->next;
			count++;
			return templink;
		}

		static void operator delete(void* p) {

			static_cast<A*>(p)->next = buffer;
			buffer = static_cast<A*>(buffer);
			return;
		}

	public:
		//static A* next;
		A* next;
		static int count;
		static int mallocCount;
		static A* buffer;
		static int blockSize;

	};
	int A::count = 0;
	int A::mallocCount = 0;
	A* A::buffer = nullptr;
	//A* A::next = nullptr;
	int A::blockSize = 50;
	void func()
	{

		clock_t start, end;

		start = clock();
		for (int i = 0; i < 500'0000; i++) {

			A* p = new A();
			//printf("%x\r\n",p);
			delete p;
		}

		end = clock();
		cout << "�������:" << A::count << "mallo������" << A::mallocCount << "����ʱ��" << end - start << endl;
	}
}
namespace test2
{

	class A {
	public:
		int i;
		int j;

		/*void* operator new(size_t size) {

			return malloc(size);
		}
		void* operator new[](size_t size) {

			return malloc(size);
		}

			void operator delete(void* p) {

			free(p);
		}
		void operator delete[](void* p) {

			free(p);
		}*/
		A() {
			cout << "A" << endl;
		}
		~A()
		{
			cout << "~A" << endl;
		}
		void* operator new(size_t size) {

			return malloc(size);
		}

		//���ض�λnew
		void* operator new (size_t size, void* p, int a, int b) {

			cout << "a=" << a << endl;
			cout << "b=" << b << endl;
			cout << "size=" << size << endl;

			return p;
		}
	};

	void func()
	{

		/*	int* a = new int();
			delete a;

			int* b = new int[3];
			delete[]b;*/

			//A* p = new A();
			//delete p;

			//placement new ��λnew  ���Ѿ�����õ��ڴ��ַ�ռ���ö���
		void* my1 = (void*)new char[sizeof(A)];

		A* obj1 = new(my1, 1, 2) A();

		//obj1->~A();

		//delete [](void*)obj1;

		delete obj1;
	}
}
namespace test3
{
	void func()
	{

		array<string, 5> obj = { "china","japanese" };

		obj[2] = "test";
		obj[3] = "lucylucylucylucylucylucylucylucylucylucy";


		obj[4] = "i";

		cout << "string size=" << sizeof(string) << endl;

		for (int i = 0; i < obj.size(); i++) {

			printf("i=%d,obj[%d]=%s,obj[%d]=%p\r\n", i, i, obj[i].c_str(), i, &obj[i]);

			const char* p = obj[i].c_str();

			printf("p=%p,%s\r\n", p, p);
		}
	}
}
namespace test4
{

	class A {
	public:
		int i;
		A(int a) :i(a) {
			cout << "A���캯��" << endl;
		}
		A(const A& obj) :i(obj.i) {
			cout << "A�������캯��" << endl;
		}
		~A() {
			cout << "A��������" << endl;
		}
	};
	void func()
	{

		vector<A> obj;
		//�����Ԥ�ȷ����ڴ棬��ôÿ�β������ݣ��������·����µ����ݣ����Ѿ��ڴ��ϵ����ݿ��������������ڴ���
		//���ܻ��½��������ȷ�����ڴ�
		obj.reserve(10);
		for (int i = 0; i < 5; i++) {

			cout << "start ʱ��size" << obj.size() << endl;
			cout << "start ʱ��capacity" << obj.capacity() << endl;

			obj.push_back(A(i));

			cout << "start ��size" << obj.size() << endl;
			cout << "start ��capacity" << obj.capacity() << endl;
		}
		cout << "����ɾ��Ԫ��" << endl;
		for (int i = 0; i < 5; i++) {

			if (i == 2) {

				auto itr = obj.begin() + 2;
				obj.erase(itr);
				break;
			}
		}

		for (auto itr = obj.begin(); itr != obj.end(); itr++) {

			cout << itr->i << endl;
		}

		cout << "�������Ԫ��" << endl;
		for (int i = 0; i < 5; i++) {

			if (i == 2) {

				//obj.push_back(A(100));
				obj[1] = A(100);
				break;
			}
		}
		for (auto itr = obj.begin(); itr != obj.end(); itr++) {

			cout << itr->i << endl;
		}
	}
}
namespace test5
{
	class A {
	public:
		int i;
		A(int a) :i(a) {
			cout << "A���캯��" << endl;
		}
		A(const A& obj) :i(obj.i) {
			cout << "A�������캯��" << endl;
		}
		~A() {
			cout << "A��������" << endl;
		}
	};
	void func()
	{

		/*stack<A> obj;
		obj.push(A(100));

		cout << obj.size() << endl;

		cout << obj.top().i << endl;*/

		/*list<A> obj;
		obj.push_front(A(101));

		obj.push_back(A(200));

		cout << obj.begin()->i << endl;

		obj.pop_front();*/
		//cout << obj.end()->i << endl;

		/*queue<A> obj;
		obj.push(A(2));
		obj.push(A(3));
		obj.push(A(4));

		cout << obj.front().i << endl;
		obj.pop();
		cout << obj.front().i << endl;
		obj.pop();

		cout << obj.front().i << endl;
		obj.pop();
		cout << obj.front().i << endl;*/

		/*forward_list<A> obj;
		obj.push_front(A(100));
		obj.push_front(A(200));


		cout << obj.front().i << endl;*/

		//map<int,A> obj;


		//obj[1] = A(100);
		//obj[2] = A(200);

		//obj.insert(std::make_pair(1,A(22)));

		//cout << obj[1].i << endl;
		//cout << obj[1].i << endl;

		//int x = obj.at(1).i;

		//cout << x << endl;


		//unordered_set<int, A> obj;
		unordered_set<int> obj;

		for (int i = 0; i < 8; i++) {


			obj.insert(i);
		}

		cout << "bucket size " << obj.bucket_count() << endl;
		cout << "max bucket size " << obj.max_bucket_count() << endl;

		obj.insert(9);

		cout << "bucket size " << obj.bucket_count() << endl;
		cout << "max bucket size " << obj.max_bucket_count() << endl;


		for (int i = 0; i < obj.bucket_count(); i++) {


			cout << i << " bucket size " << obj.bucket_size(i) << endl;
		}
		for (auto itr = obj.begin(); itr != obj.end(); itr++) {


			cout << *itr << endl;
		}

		auto x = obj.find(5);
		if (x != obj.end()) {
			cout << "find " << *x << endl;
		}

		if (find(obj.begin(), obj.end(), 5) != obj.end()) {
			cout << "find " << *x << endl;
		}

	}
}
namespace test6
{
	class A {
	public:
	};
	void func()
	{

		list<int, std::allocator<int>> obj;

		obj.push_back(10);
		obj.push_back(20);
		obj.push_back(30);

		for (auto itr = obj.begin(); itr != obj.end(); itr++) {


			cout << *itr << endl;
			int* p = &(*itr);

			printf("%p\n", p);

		}

		std::allocator<int> ok;
		int* p = ok.allocate(3);

		int* q = p;
		*q = 1; ++q;
		*q = 2; ++q;

		cout << *p << *(p + 1) << endl;

		ok.deallocate(p, 3);


	}
}
namespace test7
{
	void func()
	{
		vector<int> obj = { 1,2,3,4,5 };

		for (vector<int>::iterator itr = obj.begin(); itr != obj.end(); ++itr) {

			cout << *itr << endl;
		}

		cout << typeid(vector<int>::iterator()).name() << endl;
	}
}
namespace test8
{
	void func()
	{

		vector<int> li = { 1,2,3,4,5 };

		for_each(li.begin(), li.end(), [](int v) {

			cout << v << endl;
			});

		auto itr = find(li.begin(), li.begin() + 3, 2);
		if (itr != li.begin() + 3) {
			cout << *itr << endl;
		}
		else {
			cout << "not found" << endl;
		}

		auto result = find_if(li.begin(), li.end(), [](int x) {
			if (x > 3) {
				return true;
			}
			return false;
			});

		if (result != li.end()) {
			cout << "find result=" << *result << endl;
		}

		sort(li.begin(), li.end(), [](int x, int y) {

			return x > y;
			});
		for_each(li.begin(), li.end(), [](int x) {
			cout << "x=" << x << endl;
			});


		list<int> lis = { 43,23,12,5,3 };

		auto i = find(lis.begin(), lis.end(), 12);
		cout << *i << endl;

		lis.sort([](int x, int y) {
			return x > y;
			});

		for_each(lis.begin(), lis.end(), [](int x) {
			cout << x << endl;
			});


		cout << "***************************" << endl;

		map<int, string> mlist;
		mlist[1] = "test";
		mlist.insert(std::make_pair(2, "china"));

		//sort(mlist.begin(),mlist.end());

		/*for_each(mlist.begin(), mlist.end(), [](auto itr) {
			cout << itr->first << endl;
			});*/

		for (auto itr = mlist.begin(); itr != mlist.end(); itr++) {

			cout << itr->first << itr->second << endl;
		}

		mlist.erase(2);
		for (auto itr = mlist.begin(); itr != mlist.end(); itr++) {

			cout << itr->first << itr->second << endl;
		}

		unordered_set<int> p;
		//p[1] = "china";
		//p.insert(std::make_pair(1,"china"));
		//p.insert(1,"b");
		p.insert(3);
		p.insert(4);
		p.insert(5);

		auto ix = p.find(3);
		cout << *ix << endl;

	}
}
namespace test9
{
	class A {
	public:
		bool operator()(int y, int x) {

			return y > x;
		}
	};
	void func()
	{
		//�������㣺minus
		//��ϵ���㣺greater less
		//�߼����㣺logic_and
		//λ���㣺bit
		vector<int> li = { 1,2,3,4,5 };

		for_each(li.begin(), li.end(), [](int v) {

			cout << v << endl;
			});
		sort(li.begin(), li.end(), A());
		for_each(li.begin(), li.end(), [](int v) {

			cout << v << endl;
			});

		auto x = minus<int>()(10, 2);
		cout << x << endl;

		cout << greater<int>()(1, 2) << endl;
		//cout << bitand<int>()(1,2) << endl;


		cout << count(li.begin(), li.end(), 2) << endl;

		//functor�º���������
		cout << count_if(li.begin(), li.end(), bind(less<int>(), 2, std::placeholders::_1));

		cout << logical_and<int>()(1, 2) << endl;

	}
}
namespace test10
{
	class A {
	public:
		int operator()(int x) {

			return x;
		}
	};
	int echo(int y) {
		return y;
	}
	int echo() {
		return 66666;
	}
	void func()
	{

		int (*fp)(int) = echo;
		function<int(int)>f1 = fp;
		function<int(int)>f2 = A();

		cout << f1(200) << endl;
		cout << f2(200) << endl;

		map<string, function<int(int)>> sss = {
			{"f1",fp},
			{"f2",A()}
		};

		cout << sss["f1"](888) << endl;
		cout << sss["f2"](9999) << endl;

	}
}
namespace test11
{
	//�������� ���Դ�����ֵ����ֵ
	template<typename T>
	void test(T&& v) {
		cout << v << endl;
	}
	//��ֵ���ã�ֻ�ܸ���ֵ
	void test1(int&& v) {
		cout << "test1 v=" << v << endl;
	}
	void func()
	{

		test(100);

		test1(200);
		int j = 10;
		//test1(j);//ֻ�ܸ���ֵ��j����ֵ���޷�����ֵ�󶨵���ֵ����
		test(j);
		test1(std::move(j));
	}
}
namespace test12
{
	template<typename F,typename T1 ,typename T2 >
	//void myFuncTemplate(F f, T1 a, T2 b) {
	void myFuncTemplate(F f, T1 &&a, T2 &&b) {
		
		f(a,b);
	}
	void myfunc(int v1, int& v2) {

		v2++;
		cout << v1 << v2 << endl;
	}

	
	void printI(int& v) {
		cout << "������ֵ����" << endl;
	}
	void printI(int&& v) {
		cout << "������ֵ����" << endl;
	}
	template<typename T>
	void printTemp(T&& v) {
		//������������ã��ܽ���ֵ����ֵ��������������ֵ
		printI(v);
		printI(std::move(v));//ǿ��ת��Ϊ��ֵ
		printI(std::forward<T>(v));//ԭ����ɶ����ɶ
	}
	void func() {
		int x = 10;
		//myfunc(1,x);

		//myFuncTemplate(myfunc,10,x);
		//cout << "x=" << x << endl;

		//printTemp(printI,1);
		//printTemp(printI,x);

		printTemp(33);
		printTemp(x);
	}
}
namespace test13{


	void test()
	{
		cout << "test" << endl;
	}
	class A {
	public:
		//static const auto x = 100;
		//auto y = 101;
	};
	//void bbb(auto x) {}
	class X {
	public:
		static int test() {
			return 10;
		}
	};
	class Y {
	public:
		static double test() {
			return 10.2;
		}
	};
	template<typename t>
	void jack() {

		auto v = t::test();
		cout <<v << endl;
	}
	void func()
	{

		jack<X>();
		jack<Y>();
		//cout<< Y::test();

		/*int x = 10;
		int&& y = std::move(x);
		y = 100;
		cout << x << y << endl;

		int&& z = std::forward<int>(x);
		z = 101;
		cout << x << y << z << endl;*/

		/*auto x = 100;
		auto y = x;
		cout << x << y << endl;*/
		/*auto y = 100;
		auto& z = y;
		z = 101;
		cout << z << y << endl;

		auto* x = &y;
		*x = 200;
		cout << *x << y << z << endl;*/

		/*auto x = 10;
		auto&& y = x;
		y = 90;
		cout << x << y << endl;*/

		/* char x[] = "ssss";
		auto p = x;
		p[0] = 'j';

		cout << p << x << endl;*/

		/*auto f = test;
		f();

		auto& f1 = f;
		f1();*/

		//std::map<int, string> mas;
		//mas.insert({1,"jack"});
		//mas.insert({ 2,"tom" });
		//std::map<int, string>::iterator itr;
		////for (itr = mas.begin(); itr != mas.end(); itr++) {
		//for (auto itr = mas.begin(); itr != mas.end(); itr++) {

		//	cout << itr->first << itr->second << endl;
		//}

		//auto x{ 2 };
		//auto y = { 4 };
		//auto z(199);

		//cout << x << y[0] << z << endl;

		//auto f = test;
	}
}
namespace test14
{
	template<typename T>
	class A {
	public:
		//typename T::iterator itr;
		decltype(T().begin()) itr;
		void getB(T &t) {

			itr = t.begin();
			cout << *itr << endl;
		}
	};
	void test() {
		cout << "tst" << endl;
	}
	void func()
	{
		//int x = 10;
		//int* p = &x;
		//���� 
		//decltype(*p) j = x;

		//j = 101;
		//cout << x << x << endl;

		//����
		int x = 10;
		decltype((x)) k = x;
		k = 99;
		cout << k << x << endl;

		/*using condt = std::vector<int>;
		condt myarr = { 1,2,3 };

		A<condt> obj;
		obj.getB(myarr);*/

		/*decltype(9) i = 10;
		cout << i << endl;

		int x = 10;
		decltype(x) j = x;
		j = 100;
		cout << x << j << endl;*/

		/* int j = 20;
		int* p = &j;
		decltype(p) x = &j;
		*x = 100;
		cout << j << *p << *x << endl;*/

		//const int x = 999;
		//decltype(x) j = x;
		//j = 33;


		//char p[] = "test";
		//decltype(p) m = "tom";

		//cout << p << m << endl;

		/*decltype(test) *f ;
		f = test;
		f();*/
	}
}
namespace test15
{
	int tf(int& v) {
		return v;
	}
	double tf(double& v) {
		return v;
	}

	template<typename T>
	auto myFunc(T& t)->decltype(tf(t)) {
		return tf(t);
	}
	auto myf() {
		return 10;
	}


	decltype(auto) v1() {
		return 10;
	}
	decltype(auto) v2() {
		return (10);
	}
	void func() {

		int x = 10;
		//cout << v1() << endl;
		///v1() x = 10;

		//decltype(v2()) v = 12;
		//cout << v << endl;

		decltype(auto) j = x;

		cout << j << x << endl;

		std::function<decltype(myf)> fu = myf;
		
		cout << "auto "<<fu() << endl;

		//cout << myFunc(x) << endl;
		//cout << myf() << endl;

		/*std::vector<int> my = { 1,2,3 };
		cout << my.size() << endl;

		std::vector<int>::size_type s = my.size();
		cout << s << endl;

		decltype(my)::size_type s1 = my.size();

		cout << s << endl;

		decltype(sizeof(int)) i = 10;
		cout << i << endl;*/
	}
}
int main()
{

	test15::func();
}