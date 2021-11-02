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
		cout << "分配次数:" << A::count << "mallo次数：" << A::mallocCount << "，用时：" << end - start << endl;
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

		//重载定位new
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

			//placement new 定位new  在已经分配好的内存地址空间调用对象
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
			cout << "A构造函数" << endl;
		}
		A(const A& obj) :i(obj.i) {
			cout << "A拷贝构造函数" << endl;
		}
		~A() {
			cout << "A析构函数" << endl;
		}
	};
	void func()
	{

		vector<A> obj;
		//如果不预先分配内存，那么每次插入数据，都会重新分配新的内容，并把旧内存上的数据拷贝到新连续的内存中
		//性能会下降，建议先分配好内存
		obj.reserve(10);
		for (int i = 0; i < 5; i++) {

			cout << "start 时，size" << obj.size() << endl;
			cout << "start 时，capacity" << obj.capacity() << endl;

			obj.push_back(A(i));

			cout << "start 后，size" << obj.size() << endl;
			cout << "start 后，capacity" << obj.capacity() << endl;
		}
		cout << "尝试删除元素" << endl;
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

		cout << "尝试添加元素" << endl;
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
			cout << "A构造函数" << endl;
		}
		A(const A& obj) :i(obj.i) {
			cout << "A拷贝构造函数" << endl;
		}
		~A() {
			cout << "A析构函数" << endl;
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
		//算术运算：minus
		//关系运算：greater less
		//逻辑运算：logic_and
		//位运算：bit
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

		//functor仿函数适配器
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
	//万能引用 可以传递左值，右值
	template<typename T>
	void test(T&& v) {
		cout << v << endl;
	}
	//右值引用，只能给右值
	void test1(int&& v) {
		cout << "test1 v=" << v << endl;
	}
	void func()
	{

		test(100);

		test1(200);
		int j = 10;
		//test1(j);//只能给右值，j是左值，无法将左值绑定到右值引用
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
		cout << "我是左值引用" << endl;
	}
	void printI(int&& v) {
		cout << "我是右值引用" << endl;
	}
	template<typename T>
	void printTemp(T&& v) {
		//这里的万能引用，能接左值，右值，但它本身是左值
		printI(v);
		printI(std::move(v));//强制转换为右值
		printI(std::forward<T>(v));//原本是啥就是啥
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
		//引用 
		//decltype(*p) j = x;

		//j = 101;
		//cout << x << x << endl;

		//引用
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
namespace test16
{
	void pt(int v) {
		cout << "pt " << v << endl;
	}
	class A {
	public:
		A() {
			cout << "A 构造函数" << endl;
		}
		~A() {
			cout << "A析构函数" << endl;
		}

		A(const A& obj) {
			cout << "A拷贝函数" << endl;
		}
		void operator()(int v) {
			cout << "A operator " << v << endl;
		}
		 void tom(int v) {
			m_a = v;
			cout << "jack " << v << endl;
		}
		static void jack(int v) {
			
			cout << "jack " << v << endl;
		}
		int m_a;
	};
	class B {
		using func = void(*)(int v);
	public:
		static void test(int v) {
			cout << "B operator " << v << endl;
		}
		operator func() {
			return test;
		}
	};

	void testffff(int c, std::function<void(int) > f) {

		f(c);
	}
	void func()
	{

		A obj;

		//auto x1 = std::bind(&A::tom,&obj,std::placeholders::_1);
		//x1(4);

		//auto x1 = std::bind(A::jack, std::placeholders::_1);
		//auto x1 = std::bind(A::jack, 888);
		//x1();
		//cout << obj.m_a << endl;

		auto x1 = std::bind(&A::tom,&obj,std::placeholders::_1);
		testffff(100,x1);

		//std::function<int&()> x = std::bind(&A::m_a,&obj);
		//
		//x() = 10;


		//std::function<void(int)> f1 = std::bind(&A::tom,&obj,10);
		//std::function<void(int)> f1 = std::bind(&A::jack,std::placeholders::_1);
		//std::function<void(int)> f1 = &A::tom;//不可以
		std::function<void(int)> f1 = &A::jack;//可以
		f1(2);
		

		//B obj;
		
		//std::function<void(int)> f1 = pt;
		//std::function<void(int)> f1 = A();
		//std::function<void(int)> f1 = B();
		//void(*f1)(int) = B();
		//std::function<void(int)> f1 = &A::jack;
		//f1(22);

		//testffff(1001,B());
		//testffff(1001,A());

		//auto f1 = std::bind(A(),std::placeholders::_1);
		//auto f1 = std::bind(B(),std::placeholders::_1);
		//auto f1 = std::bind(A::jack,std::placeholders::_1);
		//auto f1 = std::bind(&pt,std::placeholders::_1);
		//f1(99999);

		/*void(*f)(int);
		f = pt;
		f(10);


		A obj;
		obj(100);

		B obj1;
		obj1.test(3);

		void(* fl)(int) ;
		fl = A::jack;
		decltype(A::jack) *fl = &A::jack;
		fl(1);*/
	}
}
namespace test17
{
	class A {

	public :
		int x = 10;
		void test(int a, int b) {

			auto f = [this]() {
				x = 101;
			};
			f();
			cout << x << a << b << endl;
		}
	};
	void func()
	{
		/*auto f1 = [](int v) ->int {
		
			return v+100;
		};
		cout << f1(2);*/

		/*auto f2 = [] {
			cout << "100" << endl;
		};

		f2();*/
		/*int x = 10;
		int y = 20;
		auto f3 = [=, &x] {
			return y + x;
		};

		cout << f3()<<endl;*/
		/*int x = 10;
		int y = 20;
		auto f4 = [&, x] {
			y = 100;
			cout << y << x << endl;
		};

		f4();
		cout << x << y << endl;*/

		/*A obj;
		obj.test(1,2);*/
		//int x = 10;
		//std::function<int(int)> f = std::bind([=](int v) {return v; }, std::placeholders::_1);
		//cout << f(x) << endl;

		/*[]() {
			cout << "china" << endl;
		}();*/

		//std::vector<int> l = { 1,2,3,4,5 };

		/*for_each(l.begin(), l.end(), [](int x) {
			cout << "l ," << x << endl;
			});*/

		/*auto z = find_if(l.begin(), l.end(), [](int p) {
				
			cout << p << endl;

			return false;
			});*/

		/*int x = 10;
		auto f = [=]()mutable {
		
			x = 0;
			cout << x << endl;
		};

		f();
		cout << x << endl;*/

	}
} 

std::vector < std::function<bool(int)> >gs;
namespace test18
{
	void myfunc()
	{
		
		srand(unsigned int(time(NULL)));

		int tmp = rand() % 10;

		//auto f = [=](int v)->bool {
		auto f = [=](auto v)->bool {
			
			cout << tmp <<v<< endl;
			return tmp;
		};
		gs.push_back(f);

		tmp++;
	}

	class A {
	public:
		int tmp = 9;
	public:
		void add()
		{

			int copy = tmp;//拷贝一分
			static int x = 101;//静态变量【其实会存放在全局数据区】
			//效果类似引用捕获
			auto f = [copy=tmp](int v) { //这里感觉是按值捕获
				//如果按值捕获应该有备份，但运行时根本没有
				
				cout << "v =" << v << ",copy=" << copy <<"x="<<x<< endl;
				return true;
			};
			x++;
			gs.push_back(f);
			x++;
		}
	};
	void func()
	{
		
		//myfunc();

		//gs[0](2);
		//A obj;
		//obj.add();

		//gs[0](1);

		A* obj = new A;

		obj->add();

		delete obj;

		gs[0](2);

		//delete obj;
	}
}
namespace test19
{
	class A {
	public:
		//char a = 10;
		//int a = 300;
		//static int a;

		void func() {}
		static void t2est() {}

		virtual void test() {}
		virtual void test2() {}
		virtual void test3() {}
	public:
		float x;
		static int y;
	};
	//int A::a = 10;
	void func()
	{

		A obj;
		int i = sizeof(obj);
		cout << i << endl;

		//printf("%p,%p\r\n",&obj,&obj.a);
	}
}
namespace test20{

	class A {
	public:
		int a;
		A() {
			cout << "A::A" << this << endl;
		}
		void funcA() {
			cout << "A::funcA" << this << endl;
		}
	};
	class B {
	public:
		int b;
		B() {
			cout << "B::B" << this << endl;
		}
		void funcB() {
			cout << "B::funcB" << this << endl;
		}
	};
	class C:public A, public B {
	public:
		int c;
		C() {
			cout << "C::C" << this << endl;
		}
		void funcC() {
			cout << "C::funcC" << this << endl;
		}
		void funcB() {
			cout << "C::funcB" << this << endl;
		}
	};
	void func()
	{

		C obj;
		//C类先继承A类，再继承B类  ，所以C的内存结构如下
		/*************************/
		//int a
		//int b
		//int c 
		/*************************/
		//C的起始地址和A类的起始地址是一样的

		//this 指针调整
		obj.funcA();
		obj.funcB();
		obj.B::funcB();
		obj.funcC();

		cout << sizeof(C) << endl;

	}
}
namespace test21
{
	class A {
	public:
		int a;
		A() {
			cout << "A" << endl;
		}
	};

	class C {
	public:
		A obj;
		void func() {
			cout << "func" << endl;
		}
	};
	void func()
	{
		//C被编译器默认合并了构造函数
		C obj;
		obj.func();
	}
}
namespace test22
{

	class Grand {
	public:

	};
	class A:virtual public Grand {
	public:
		A() {
			cout << "编译器合成的默认构造函数调用我" << endl;
		}

	};

	//class B :public A {
	class B :virtual public Grand {
	public:
		void test()
		{
			cout << "test" << endl;
		}
		/*virtual void china() {
			cout << "virtual void china" << endl;
		}*/
	};
	class C :public A, public B {
	public:

	};
	void func()
	{

		//B obj;
		//obj.test();
		//编译器在如下情况会合成（插入）默认构造函数
		//1 类含有类成员变量，且类成员的类有构造函数
		//2 类有虚函数
		//3 继承父类，父类有构造函数
		//4 存在多重继承，如虚继承
		C obj;
		obj.test();
	}
}
namespace test23
{
	class Ason {
	public:
		Ason() {

		}
		Ason(const Ason& obj) {
			cout << "Ason拷贝构造函数" << endl;
		}
	};
	//class A:public Ason {
	class A {
	public:
		int i;
		//Ason son;

		/*void test() {
			cout << "test" << endl;
		}*/
		virtual void test() {

		}
	};


	
	void func() {
		A obj;
		obj.i = 10;
		A obj1 = obj;
	}
}
namespace test24
{
	class A {
	public:
		int i;
		A() {
			cout << "A构造函数" << endl;
		}
		A(const A& obj) {
			i = obj.i;
			cout << "A拷贝构造函数" << i << endl;
		}
		virtual ~A() {
			cout << "析构函数" << endl;
		}

		void test() {
			cout << "A::test" << endl;
		}
	};
	void func()
	{
		/*A obj;
		A x1 = obj;
		A x2 = (obj);
		A x3 = { obj };
		A x4{ obj };
		A x5(obj);*/

		void* p = malloc(sizeof(A));

		A* objx = new (p)A();

		objx->A::A();

		objx->i = 10;
		objx->test();
		objx->A::~A();
		delete objx;

	}
}
namespace test25
{
	class Temp {
	public:
		int x, y;
		Temp(int a, int b) :x(a), y(b) {
			cout << "Temp构造函数" << a << b << endl;
		}
		Temp(const Temp& obj) :x(obj.x), y(obj.y) {
			cout << "Temp拷贝构造函数" << x << y << endl;
		}
		virtual ~Temp() {
			cout << "temp析构函数" << endl;
		}
	};
	Temp createObj(Temp& obj) {

		/*Temp t(1,2);
		t.x = obj.x * 3;
		t.y = obj.y * 3;

		return t;*/
		return Temp::Temp(obj.x,obj.y);
	}
	void func() {


		Temp t(10, 20);

		createObj(t);

	}
}
namespace test26
{
	class A {
	public:
		int i;
		int* m_b;
		A() {
			i = 0;
			m_b = new int(10);
			cout << "A默认构造函数" << endl;
		}
		virtual ~A() {
			if (m_b!=nullptr) {
				delete m_b;
				m_b = nullptr;
			}
			
			cout << "析构函数" << endl;
		}
		A(const A& obj) {
			i = obj.i;
			m_b = new int(100);
			memcpy(m_b,obj.m_b,sizeof(int));
			cout << "拷贝构造函数" << endl;
		}
		A(int v) {

			i = v;
			m_b = new int(10);
			cout << "A(int v) 构造函数" << endl;
		}
	};
	void func() {

		A obj1 = 1;
		obj1.A::A();

		obj1.A::~A();
		//A obj2 = A(1);
		//A obj3 = (1);

		//A obj4 = obj1;
		
	}
}
namespace test27
{
	class B {
	public:
		int x;
		B(int v=0) :x(v) {
			cout << "B构造函数运行了" << x<< "this=" << this << endl;
		}
		B(const B& obj) :x(obj.x) {
			cout << "B拷贝构造函数运行了" << x << "this=" << this << endl;
		}
	};
	//class A:public B {//同样在构造函数初始化列表加
	class A:public B {//同样在构造函数初始化列表加
	public:
		int i;
		int& j;//必须有构造函数初始化列表 ，否则不行
		const int k;//同上，必须要在初始化列表处
		B obj;//同上

		A(int value=0):i(value),j(value),k(value),obj(value) {
		//A(int value=0):i(value),j(value),k(value),B(value) {
		//A(int value=0):i(value),j(value),k(value) {
			//obj = 1;

			cout << "构造函数" << i<<"this="<<this<< endl;
		}
		A(const A& obj) :i(obj.i),j(obj.j),k(obj.k),obj(obj.obj) {
		//A(const A& obj) :i(obj.i),j(obj.j),k(obj.k),B(obj.k) {
			cout << "拷贝构造函数" << i << "this=" << this << endl;
		}
		A&operator=(const A&obj){
			
			i = obj.i;
			cout << "拷贝赋值函数" << i << "this=" << this << endl;
			return *this;
		}
		~A() {
			cout << "析构函数" << i << "this=" << this << endl;
		}

	};
	void func() {


		//A obj(1);
		//A obj
		// obj.A::A(1)

		//A obj2 = obj;
		//A obj2
		//obj2.A::A(obj)
		//A obj3 = 100;
		//A obj3
		//obj3.A::A()
		A obj(2);
	}
}
namespace test28
{
	class A {
	public:
		int i;
		virtual void test() {}
	};
	void func() {

		A obj;

		char* a1 = reinterpret_cast<char*>(&obj);
		char* a2 = reinterpret_cast<char*>(&(obj.i));

		if (a1 == a2) {
			cout << "虚函数表在后" << endl;
		}
		cout << "虚函数表指针在前" << endl;

		cout << sizeof(obj) << endl;
	}
}
namespace test29
{
	class Base {
	public:
		virtual void f() {
			cout << "Base::f" << endl;
		}
		virtual void g() {
			cout << "Base::g" << endl;
		}
		virtual void h() {
			cout << "Base::h" << endl;
		}
	};
	class Derive :public Base {
	public:
		virtual void g() {
			cout << "Derive::g" << endl;
		}
	};
	void func() {


		Derive obj;

		long* p = (long*)&obj;

		long* vptr = (long*)(*p);
		typedef void(*Func)();

		Func f = (Func)(vptr[0]);

		f();

		Base b = obj;
		//Base b ;

		long* bp = (long*)&b;

		long* bvptr = (long*)(*bp);

		//变量名 p
		//变量的值  Dervive内存
		//Derive* p = new Derive();

		//long* pvptr = (long*)p;

		////变量名 vptr
		////变量的值  Dervie的内容的内容

		//long* vptr = (long*)*pvptr;


		//typedef void(*Func)();

		//for (int i = 0; i <= 4; i++) {

		//	printf("vptr[%d]=0x%p\r\n",i,vptr[i]);
		//}

		//Func f = (Func)vptr[0];
		//Func g = (Func)vptr[1];
		//Func h = (Func)vptr[2];
		////Func i = (Func)vptr[3];

		//f();
		//g();
		//h();
		//i();

		/*cout << sizeof(p) << endl;
		cout << sizeof(Derive) << endl;
		cout << sizeof(Base) << endl;*/

		/*Base* base = p;
		long* pvptrb = (long*)base;

		long* bvptr = (long*)*pvptrb;

		Func bf = (Func)bvptr[0];
		Func bg = (Func)bvptr[1];
		Func bh = (Func)bvptr[2];*/


	}
}
namespace test30 {

	class Base1 {
	public:
		virtual void f() {
			cout << "Base1::f" << endl;
		}
		virtual void g() {
			cout << "Base1::g" << endl;
		}
	};
	class Base2 {
	public:
		virtual void h() {
			cout << "Base2::h" << endl;
		}
		virtual void i() {
			cout << "Base2::i" << endl;
		}
	};

	class Dervie:public Base1, public Base2 {
	public:
		virtual void f() {
			cout << "Derive::f" << endl;
		}
		virtual void i() {
			cout << "Derive::i" << endl;
		}

		virtual void mh() {
			cout << "Derive::mh" << endl;
		}
		virtual void mi() {
			cout << "Derive::mi" << endl;
		}
		virtual void mj() {
			cout << "Derive::mj" << endl;
		}
	};
	void func() {


		cout << sizeof(Base1) << endl;
		cout << sizeof(Base2) << endl;
		cout << sizeof(Dervie) << endl;
		//ins===>0x00EFFD58
		//0x00EFFD58存储的内容为：cc 4f 94 00 c4 53 94 00
		//
		Dervie ins;
		Base1& b1 = ins;
		Base2& b2 = ins;

		long* p = (long*)(&ins);
		//cc 4f 94 00==>vptr
		long* vptr = (long*)(*p);

		typedef void(*Func)(void);

		Func f1 = (Func)(vptr[0]);//0x00b35b7b {Project1.exe!test30::Dervie::f(void)}
		Func f2 = (Func)(vptr[1]);//0x00b35b6c {Project1.exe!test30::Base1::g(void)}
		Func f3 = (Func)(vptr[2]);//0x00b35b49 {Project1.exe!test30::Dervie::mh(void)}
		Func f4 = (Func)(vptr[3]);//0x00b35b76 {Project1.exe!test30::Dervie::mi(void)}
		Func f5 = (Func)(vptr[4]);//0x00b35b58 {Project1.exe!test30::Dervie::mj(void)}
		Func f6 = (Func)(vptr[5]);//0x00000000
		Func f7 = (Func)(vptr[6]);
		Func f8 = (Func)(vptr[7]);

		long* p2 = (long*)(p+1);
		//c4 53 94 00==>vptr2
		long* vptr2 = (long*)(*p2);
		Func f11 = (Func)(vptr2[0]);//0x00b35b53 {Project1.exe!test30::Base2::h(void)}
		Func f22 = (Func)(vptr2[1]);//0x00b35b67 {Project1.exe!test30::Dervie::i(void)}
		Func f33 = (Func)(vptr2[2]);

		b1.f();
		b1.g();
		b2.h();
		b2.i();

		ins.mh();
		ins.mi();
		ins.mj();
		ins.f();
		ins.i();

		cout << "------------------------" << endl;
		f1();
		f2();
		f3();
		f4();
		f5();

	}
}
namespace test31
{
	class X {
	public:
		int x;
		int y;
		int z;
		//X():x(0),y(0),z(0) {
		X(){
			//在运行构造函数之前，编译器会先在前面插入一些虚函数指针成员
			//也就是说类对象的内存成员会被编译器修改
			memset(this,0,sizeof(X));
			cout << "x构造函数" << endl;
		}
		//X(const X& obj) :x(obj.x), y(obj.y), z(obj.z) {
		X(const X&obj) {
			memcpy(this,&obj,sizeof(X));
			cout << "x拷贝构造函数" << endl;
		}
		virtual ~X() {
			cout << "x虚析构函数" << endl;
		}
		virtual void virfunc() {
			cout << "x virfunc" << endl;
		}
		void ptfunc() {
			cout << "x ptfunc" << endl;
		}
	};
	void func() {


		/*X obj;
		obj.x = 1;
		obj.y = 2;
		obj.z = 3;

		obj.virfunc();//静态联编  在编译时就已经固定好，不走虚函数表

		X obj1(obj);

		cout << obj.x << obj.y << obj.z << endl;*/

		//它要走虚函数表，而虚函数表已被memset设置为空
		X* obj = new X();
		obj->virfunc();
		delete obj;
	}
}
namespace test32
{
	string myvar="china";

	typedef string types;
	class X {
	public:

		/*int show() {
			return myvar;
		}*/
		//int show(types n);
	private:
		//int myvar = 5;
		types n;
		typedef int types;
	};
	//int X::show(types n) {
		//cout << test32::myvar << endl;
		//cout << n << endl;
		//return 0;
	//}
	string show() {
		return myvar;
	}
	void func() {

		X obj;
		//cout << obj.show("ddd") << endl;
	}
}
namespace test33
{
//#pragma pack(1)
	class A {
	public:
		int i;
		static int is;

		int j;
		static int js;

		int k;
		static int ks;

		char m;
		int n;

		void printMemb() {

		}
		virtual void shows() {

		}
	};
	void func() {

		A obj;
		obj.i = 1;
		obj.j = 2;
		obj.k = 3;
		obj.m = 4;
		obj.n = 5;
		cout << sizeof(obj) << endl;

		printf("A::i=%p\r\n",&obj.i);
		printf("A::j=%p\r\n",&obj.j);
		printf("A::k=%p\r\n",&obj.k);
		printf("A::m=%p\r\n",&obj.m);
		printf("A::n=%p\r\n",&obj.n);

		cout << "----------------------偏移" << endl;
		printf("A::i=%d\r\n", &A::i);
		printf("A::j=%d\r\n", &A::j);
		printf("A::k=%d\r\n", &A::k);
		printf("A::m=%d\r\n", &A::m);
		printf("A::n=%d\r\n", &A::n);


		cout << "=====================" << endl;
		printf("A::i=%p\r\n",&obj.i);
		printf("A=%p\r\n",&obj);


		cout << "-------------------" << endl;
		long* pa = (long*)&obj;

		/*printf("A::i=%d\r\n", *(pa));
		printf("A::j=%d\r\n", *(pa+1));
		printf("A::k=%d\r\n", *(pa+2));
		printf("A::m=%d\r\n", *(pa+3));
		printf("A::n=%d\r\n", *(pa+4));*/


	}
}
namespace test34 {

	class F {
	public:
		int fi;
		int fj;
	};
	class A:public F{
	public:
		int i;
		static int s_i;
		int j;

		void myfunc() {

			this->i = 20;
			this->j = 30;
		}
	};
	int A::s_i = 0;
	void func() {

		//数据成员布局
		cout << sizeof(A) << endl;
		printf("A::i=%d\n",&A::i);
		printf("A::j=%d\n", &A::j);
		printf("A::s_i=%d\n", &A::s_i);

		A obj;
		obj.i = 1;
		obj.j = 2;
		obj.s_i = 3;

		int* data = (int*)(&obj);
		*data = 100;
		*(data + 3) = 200;

		char* data1 = (char*)(&obj);
		*(data1+8) = 'a';
		*(data1 + 12) = 'b';

		printf("A::i=%p\n", &obj.i);
		printf("A::j=%p\n", &obj.j);
		printf("A::s_i=%p\n", &obj.s_i);

		printf("A::i=%c\n", obj.i);
		printf("A::j=%c\n", obj.j);
		printf("A::s_i=%d\n", obj.s_i);


		obj.myfunc();

		printf("A=%p\n", &obj);
		printf("A::fi=%p\n", &obj.fi);
		printf("A::fj=%p\n", &obj.fj);

	}
}
namespace test35 {

	class Base1 {
	public:
		int i;
		//char a;
		//char b;
		//char c;
	};

	class Base2 :public Base1 {
	public:
		char a;
	};
	class Base3 :public Base2 {
	public:
		char b;
	};
	class Base4 :public Base3 {
	public:
		char c;
	};
	void func() {

		/*cout << sizeof(Base1) << endl;

		printf("i=%d\n",&Base1::i);
		printf("a=%d\n",&Base1::a);
		printf("b=%d\n",&Base1::b);
		printf("c=%d\n",&Base1::c);*/

		cout << sizeof(Base1) << endl;
		cout << sizeof(Base2) << endl;
		cout << sizeof(Base3) << endl;
		cout << sizeof(Base4) << endl;

		printf("i=%d\n", &Base4::i);
		printf("a=%d\n", &Base4::a);
		printf("b=%d\n", &Base4::b);
		printf("c=%d\n", &Base4::c);

		//没有继承关系时，是9个字节  继承后是16个字节，浪费了内存
		//在不同的编译器上编译时结果可能不一样

		//总之对象内存布局某位置存放什么数据了解就可以

	}
}
int main()
{

	test35::func();

	
	//cout << (1 >> 1) << endl;

	

	return 0;
}