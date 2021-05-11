//here is my solve set of concurrency question on leetcode;
//the namespace start with a C,
//just use namespace::test(); to check how it works
//the declare is in file:leetcode.test.cpp from line 2235 to 2252
//for vs code. u just need add this file into your project.
//for gcc u need add this filename and -pthread to ur compile command
//g++7 -std=c++17 leetcodetest.cpp [leetcodeconcurrency.cpp -pthread] -o your_output_binary


namespace Csolution1115 //concurrency
{
	class FooBar {
	private:
		int n;
		volatile bool printyet;
		mutable std::mutex mut;
		//std::mutex mut2;
	public:
		FooBar(int n) {
			this->n = n;
			printyet = false;
		}

		void foo(std::function<void()> printFoo) {

			//cout << "foofunc";
			for (int i = 0; i < n; i++) {

				while (printyet) this_thread::yield();
				// printFoo() outputs "foo". Do not change or remove this line.
				printFoo();
				std::lock_guard<std::mutex> guard(mut);
				printyet = true;
			}

		}

		void bar(std::function<void()> printBar) {
			//std::lock_guard<std::mutex> guard(mut2);
			//cout << "barfunc";
			for (int i = 0; i < n; i++) {

				while (!printyet) this_thread::yield();
				// printBar() outputs "bar". Do not change or remove this line.
				printBar();
				std::lock_guard<std::mutex> guard(mut);
				printyet = false;
			}
		}
	};

	void test()
	{
		FooBar Foo(5);
		auto PrintCB = std::bind(&FooBar::foo, &Foo, std::placeholders::_1);
		auto PrintCcB = std::bind(&FooBar::bar, &Foo, std::placeholders::_1);
		std::thread  thread1(PrintCB, []() {std::cout << "foo"; });
		std::thread thread2(PrintCcB, []() {std::cout << "bar"; });
		thread1.join();
		thread2.join();

	}
}

namespace Csolution1116
{
	class ZeroEvenOdd {
	private:
		bool status;
		bool iseven;
		int n;
		mutable std::mutex mut;

	public:
		ZeroEvenOdd(int n) {
			this->n = n;
			status = false;
			iseven = false;
		}

		// printNumber(x) outputs "x", where x is an integer.
		void zero(function<void(int)> printNumber) {
			for (size_t i = 0; i < n; ++i)
			{
				while (status) this_thread::yield();

				printNumber(0);
				std::lock_guard<std::mutex> guard(mut);
				status = true;

			}
		}

		void even(function<void(int)> printNumber) {
			for (size_t i = 0; i < (n / 2); ++i)
			{
				while (!status || !iseven) this_thread::yield();
				printNumber(2 * (i + 1));
				std::lock_guard<std::mutex> guard(mut);
				status = false;
				iseven = false;
			}
		}

		void odd(function<void(int)> printNumber) {
			for (size_t i = 0; i < ((n + 1) / 2); ++i)
			{
				while (!status || iseven) this_thread::yield();
				printNumber((2 * (i + 1)) - 1);
				std::lock_guard<std::mutex> guard(mut);
				status = false;
				iseven = true;
			}
		}
	};
	void test() //USE this function to test
	{
		ZeroEvenOdd obj(6);
		auto PrintCB = std::bind(&ZeroEvenOdd::zero, &obj, std::placeholders::_1);
		auto PrintOdd = std::bind(&ZeroEvenOdd::odd, &obj, std::placeholders::_1);
		auto PrintEven = std::bind(&ZeroEvenOdd::even, &obj, std::placeholders::_1);
		std::thread  thread1(PrintCB, [](int n) {std::cout << n; });
		std::thread thread2(PrintOdd, [](int n) {std::cout << n; });
		std::thread thread3(PrintEven, [](int n) {std::cout << n; });
		thread1.join();
		thread2.join();
		thread3.join();
	}
}


namespace Csolution1117
{
	class H2O {
		condition_variable cv_H;
		condition_variable cv_O;
		mutable mutex mutexH;
		mutable mutex mutexO;

		int countH;

	public:
		H2O() {
			countH = 0;

		}

		void hydrogen(function<void()> releaseHydrogen) {

			std::unique_lock<std::mutex> lk(mutexH);
			if (0 != countH)
			{
				cv_H.wait(lk, [this]()->bool {
					return 0 != this->countH;
					});
			}

			countH++;
			if (0 == countH % 2)
			{
				//cout << "countH" << countH;
				cv_O.notify_one();
			}
			if (1 == countH % 2)
			{
				cv_H.notify_one();
			}
			releaseHydrogen();
		}

		void oxygen(function<void()> releaseOxygen) {
			std::unique_lock<std::mutex> lk(mutexO);
			cv_O.wait(lk);
			releaseOxygen();
			if (0 == countH)
			{
				cv_H.notify_one();

			}
			// releaseOxygen() outputs "O". Do not change or remove this line.
		}
	};

	//before i try to write code for this question, i try to use code blow to test OJ's behaver
	//it looks like to generate 3*n thread, 
	/*
class H2O {
	std::mutex mut;
public:
	H2O() {

	}

	void hydrogen(function<void()> releaseHydrogen) {
		std::lock_guard<std::mutex> guard(mut);
		cout<< "H" << this_thread::get_id() << endl;;
		releaseHydrogen();
	}

	void oxygen(function<void()> releaseOxygen) {
		std::lock_guard<std::mutex> guard(mut);
		 cout<< "O" << this_thread::get_id() << endl;;
		releaseOxygen();
	}
};
	*/

	void test()
	{
		constexpr size_t times = 10;//n in the question: Total length of input string will be 3n, where 1 ¡Ü n ¡Ü 20.
		vector<shared_ptr<thread>> threadpool; //you can use vector<thread> as well but the std::thread is NOT copyable, see blow
		H2O obj;
		for (size_t i = 0; i < times; ++i)
		{

			auto PrintHydrogen = std::bind(&H2O::hydrogen, &obj, std::placeholders::_1);
			auto PrintHydrogen1 = std::bind(&H2O::hydrogen, &obj, std::placeholders::_1);
			auto PrintOxygen = std::bind(&H2O::oxygen, &obj, std::placeholders::_1);

			threadpool.push_back(make_shared<thread>(thread(PrintHydrogen, []() {std::cout << "H"; })));
			threadpool.push_back(make_shared<thread>(thread(PrintHydrogen, []() {std::cout << "H"; })));
			threadpool.push_back(make_shared<thread>(thread(PrintOxygen, []() {std::cout << "O"; })));
		}
		for (auto t : threadpool) // for here  if u use vector<thread> you need to change code to for(auto& t : threadpool). the std::thread is moveable. ºÃÒ®
		{
			t->join();
		}
	}


	namespace Csolution1195
	{
		class Semaphore {
		private:
			int n_;
			mutable mutex mu_;
			condition_variable cv_;

		public:
			Semaphore(int n) : n_{ n } {}

		public:
			void wait() {
				unique_lock<mutex> lock(mu_);
				if (!n_) {
					cv_.wait(lock, [this] {return n_; });
				}
				--n_;
			}
			template <class _Predicate>
			void wait(_Predicate pred) {
				unique_lock<mutex> lock(mu_);
				if (!(std::invoke(pred) || n_)) {
					cv_.wait(lock, [&pred, this] {return std::invoke(pred) || n_; });
				}
				--n_;
			}

			void signal() {
				unique_lock<mutex> lock(mu_);
				++n_;
				cv_.notify_one();
			}
			void signalToall() {
				unique_lock<mutex> lock(mu_);
				++n_;
				cv_.notify_all();
			}
		};

		class FizzBuzz {
		private:
			int n;
			int current;
			Semaphore sem;
		public:
			FizzBuzz(int n) :sem(1) {
				this->n = n;
				current = 1;

			}
			void print(function<bool()> check, function<void()> printer)
			{
				while (current <= n)
				{
					while (!std::invoke(check))
					{
						if (current > n) break;
						this_thread::yield();

					}
					sem.wait([&check, this] {return std::invoke(check) || current > n; });
					//cout << current;
					if (current <= n) printer();
					++current;
					sem.signalToall();
					if (current > n) break;
				}
			}
			// printFizz() outputs "fizz".
			void fizz(function<void()> printFizz) {
				print([this]() {return 0 == current % 3 && 0 != current % 5; }, printFizz);
			}

			// printBuzz() outputs "buzz".
			void buzz(function<void()> printBuzz) {
				print([this]() {return 0 != current % 3 && 0 == current % 5; }, printBuzz);
			}

			// printFizzBuzz() outputs "fizzbuzz".
			void fizzbuzz(function<void()> printFizzBuzz) {
				print([this]() {return 0 == current % 3 && 0 == current % 5; }, printFizzBuzz);
			}

			// printNumber(x) outputs "x", where x is an integer.
			void number(function<void(int)> printNumber) {
				print([this]() {return 0 != current % 3 && 0 != current % 5; }, [&printNumber, this]() {return printNumber(current); });
			}
		};

		void test()
		{
			FizzBuzz obj(6);
			auto PrintFizz = std::bind(&FizzBuzz::fizz, &obj, std::placeholders::_1);
			auto PrintBuzz = std::bind(&FizzBuzz::buzz, &obj, std::placeholders::_1);
			auto PrintFizzBuzz = std::bind(&FizzBuzz::fizzbuzz, &obj, std::placeholders::_1);
			auto PrintNumber = std::bind(&FizzBuzz::number, &obj, std::placeholders::_1);
			std::thread  thread1(PrintFizz, []() {std::cout << "fuzz"; });
			std::thread thread2(PrintBuzz, []() {std::cout << "buzz"; });
			std::thread thread3(PrintFizzBuzz, []() {std::cout << "Fuzzbuzz"; });
			std::thread thread4(PrintNumber, [](int n) {std::cout << n; });
			thread1.join();
			thread2.join();
			thread3.join();
			thread4.join();
		}
	}


	namespace Csolution1226
	{
		struct mutex_wrapper : std::mutex
		{
			mutex_wrapper() = default;
			mutex_wrapper(mutex_wrapper const&) noexcept : std::mutex() {}
			bool operator==(mutex_wrapper const& other) noexcept { return this == &other; }
		};

		constexpr int maxphilosopher = 5;
		class DiningPhilosophers {
		public:
			DiningPhilosophers() :lock_list(5) {

			}

			void wantsToEat(int philosopher,
				function<void()> pickLeftFork,
				function<void()> pickRightFork,
				function<void()> eat,
				function<void()> putLeftFork,
				function<void()> putRightFork)
			{
				int lefthand = philosopher;
				int righthand = (philosopher + 1) % maxphilosopher;
				//std::try_lock(lock_list[lefthand], lock_list[righthand]);
				pickRightFork();
				pickLeftFork();

				eat();
				putLeftFork();
				//lock_list[lefthand].unlock();
				putRightFork();
				//lock_list[righthand].unlock();
			}
		private:
			std::vector<std::mutex> lock_list;

		};

		enum fork
		{
			none,
			left,
			right
		};

		enum move
		{
			nonemove,
			take,
			put,
			eat
		};
		constexpr int eatTimes = 1;
		constexpr int philosopherNum = 5;
		//NOTE: here is a vs's bug 
		//those 5 function :pickleftfork ... will output the same i which is the last index num.  
		// for example:[4,1,1][4,2,1][4,0,3][4,1,2][4,2,2][4,1,1]...  the output alway be 4
		//this code works fine in g++ ( g++-7 try.cpp -std=c++17 -lpthread)
		//so if try to test this code in vs, stay calm.
		//TODO
		void test()
		{

			vector<thread> threadpool;
			std::mutex m;
			for (int index = 0; index < philosopherNum; ++index)
			{
				int i = index;
				auto pickleftfork = [=, &m]()
				{
					std::lock_guard<std::mutex> lk(m);
					std::cout << "[" << i << "," << fork::left << "," << move::take << "]";
				};
				auto pickrightfork = [=, &m]()
				{
					std::lock_guard<std::mutex> lk(m);
					std::cout << "[" << i << "," << fork::right << "," << move::take << "]";
				};
				auto putleftfork = [=, &m]()
				{
					std::lock_guard<std::mutex> lk(m);
					std::cout << "[" << i << "," << fork::left << "," << move::put << "]";
				};
				auto putrightfork = [=, &m]()
				{
					std::lock_guard<std::mutex> lk(m);
					std::cout << "[" << i << "," << fork::right << "," << move::put << "]";
				};
				auto eat = [=, &m]()
				{
					std::lock_guard<std::mutex> lk(m);
					std::cout << "[" << i << "," << fork::none << "," << move::eat << "]";
				};
				DiningPhilosophers Philosopher;
				auto run = [&, i]()
				{
					int temp = eatTimes;
					while (temp-- > 0)
					{
						try {
							Philosopher.wantsToEat(i, pickleftfork, pickrightfork, eat, putleftfork, putrightfork);
						}
						catch (exception& e)
						{
							cout << e.what();
						}
					}
				};
				threadpool.emplace_back(thread(run));
			}
			cout << "[";
			for (auto& t : threadpool)
			{
				try {
					if (t.joinable()) t.join();
				}
				catch (exception& e)
				{
					cout << e.what();
				}
			}
			cout << "]";
		}
	}
