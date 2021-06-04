// leetcodetest.cpp : here is my personal data structure an algorithm training file
// Author: vihoc
// it contains all my ac code on leetcode. i'm not a specialist of algorithm, but somehow, some of them beat 100% in C++ solutions.
// i'm still study on it. 
// 
// how to use: if u interest at a question, just write code in the main function use solution<question number>::functionname, and pass the paramter.
// some debug case is remain in the main function. if u don't like it, just delete it.
//
//for Csolution, this is a collect for concurrency, use the namespace::test() to test. 
//if u want see the result in leetcode, just copy the class in namespace and click run.

#if defined _MSC_VER
#define NOMINMAX
#include <Windows.h>
#endif
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <stack>
#include <sstream>
#include <unordered_map>

#include <functional>
#include <algorithm>

#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

//few functions may speed up your test for check result
namespace testhelper
{

	//generate a list of node
	//u may use like this :
	//testhelper::printListNode(solution82::deleteDuplicates(testhelper::generateList<solution82::ListNode, vector<int>>({ 1,1 })));
	template <typename Node, typename container>
	Node* generateList(container&& list)
	{
		copy(begin(list), end(list), ostream_iterator<int>(cout, " "));
		cout << endl;
		Node* head = new Node(0);
		Node* next = head;
		for (int& a : list)
		{
			next->next = new Node(a);
			next = next->next;
		}
		next = head->next;
		delete head;
		return next;
	}
	template <typename Node>
	void printListNode(Node* p)
	{
		cout << "start to print List:" << endl;
		std::cout << "[";
		if (nullptr == p) cout << "Empty list";
		while (p)
		{
			std::cout << p->val;
			if (p->next)
				std::cout << ",";
			p = p->next;
		}
		std::cout << "]" << std::endl;
		cout << "end of print." << endl;
	}

	template <typename Node>
	void deleteNodeList(Node* root)
	{
		while (root)
		{
			Node* temp = root;
			root = root->next;
			delete temp;
		}
	}

	//TODO, treenode.

	vector<vector<int>> generateVector(int n)
	{
		vector<vector<int>> ret;
		for (int i = 0; i < n; i++)
		{
			ret.emplace_back(vector<int>(n));
		}
		return ret;
	}
	void fillVector(vector<vector<int>>& res)
	{
		//pass a empty vector like 
		int i = 1;
		for (auto& v : res)
		{
			int j = 1;
			for_each(v.begin(), v.end(), [&i, &j](int& x) {x = i * j++; });
			i++;
		}

	}


	void print90degreeVector(vector<vector<int>>& res)
	{
		size_t maxrow = res.size();
		for (int i = 0; i < maxrow; ++i)
		{
			for (int j = maxrow; j > 0; j--)
			{
				cout << res[j - 1][i] << "  ";
			}
			cout << endl;
		}
	}
	//打印数组,
	//u may use like this:
	//testhelper::printContainerResult<vector>(testhelper::testRvalue<vector<string>, string>(solution93::restoreIpAddresses, "101023"));
	template < template<typename, typename> class Container, typename T, typename Alloc>
	void printContainerResult(Container<T, Alloc>&& res, const string&& delimiter = ", ")
	{
		cout << '[';
		if (0 != res.size())
		{
			copy(res.begin(), res.end() - 1, ostream_iterator<T>(cout, delimiter.c_str()));
			cout << res.back();
		}
		cout << "]";

	}

	template < template<typename, typename> class Container, typename T, typename Alloc>
	void printTreeResultprefix(Container<T*, Alloc>&& res, const string&& delimiter = ", ")
	{
		function<void(T*)> helper;
		vector<T*> que;
		helper = [&helper, &que](T* root)
		{

			if (nullptr != root)
			{
				helper(root->left);
				que.emplace_back(root);
				helper(root->right);
			}
			else
			{
				que.emplace_back(root);
			}
		};
		cout << '[';
		if (0 != res.size())
		{
			for (auto data = res.begin(); data != res.end() - 1; ++data)
			{
				cout << "{";
				helper(*data);
				for (auto itor = que.begin(); itor != que.end() - 1; ++itor)
				{
					if (nullptr != *itor)
					{
						cout << (*itor)->val;
					}
					else cout << "null";
					cout << delimiter;
				}

				if (nullptr != que.back())
				{
					cout << que.back()->val;
				}
				else cout << "null";
				cout << "}" << delimiter;
				que.clear();
			}
			cout << "{";
			helper(res.back());
			cout << "} ";
		}
		cout << "]";
	}

	//打印2d数组, 
	// testhelper::printVectorResult2d(testhelper::testRvalue<vector<vector<int>>, vector<int>>(solution90::subsetsWithDup, { }));
	// easy to check result
	template <typename T>
	void printVectorResult2d(vector<vector<T>>&& res)
	{
		cout << "{";
		if (!res.empty())
		{
			for (auto&& itor = res.begin(); itor != res.end() - 1; ++itor)
			{

				printContainerResult<vector>(std::forward<vector<T>>(*itor));
				cout << ", ";
			}
			printContainerResult<vector>(std::forward<vector<T>>(res.back()));
		}
		cout << "}" << endl;
	}
	template<typename Node>
	void PrintTree(Node* root)
	{
		function<void(Node*, int)> print;
		print = [&print](Node* root, int indent)
		{
			if (nullptr != root->right) print(root->right, indent + 1);
			for (int i = 0; i < indent; ++i)
				std::cout << "    ";
			std::cout << root->val << std::endl;
			if (nullptr != root->left) print(root->left, indent + 1);
		};

		if (nullptr == root)
		{
			cout << "Empty tree" << endl;
			return;
		}
		else
		{
			cout << "start to print Tree:" << endl;
			std::cout << std::endl << std::endl;
			print(root, 0);
			for (int i = 0; i < 80; ++i) {
				std::cout << "-";
			}

			std::cout << std::endl;
			cout << "end of print." << endl;
		}
	}

	template<typename Node>
	void DeleteTree(Node* root)
	{
		if (nullptr != root)
		{
			if (nullptr != root->left) DeleteTree(root->left);
			if (nullptr != root->right) DeleteTree(root->right);
			delete root;
		}
	}


#if _HAS_CXX17
	template <typename T>
	void checkT()
	{
		cout << "testinfo" << endl;
		cout << std::boolalpha << is_pod_v<T> << endl;
		cout << std::boolalpha << is_same_v<T, int> << endl;
		cout << std::boolalpha << is_integral_v<T> << endl;
		cout << "end" << endl;
	}
	//如果確定treenode不為0的話,直接寫數字,但是類型必須為Container<std::optional<int>>
	template <typename Node, template<typename, typename> class Container, typename T, typename Alloc>
	Node* generate_BT(Container<T, Alloc>&& list)
	{
		queue<Node*> que;
		queue<Node*> linkque;
		Node* root = nullptr;

		for (auto& e : list)
		{
			if constexpr (is_pod_v<T>)
			{
				que.push(new Node(e));
			}
			else
			{
				if (e.has_value())
				{
					que.push(new Node(e.value()));
				}
				else que.push(nullptr);
			}
		}

		root = que.front();
		que.pop();
		linkque.push(root);
		while (!linkque.empty())
		{
			int step = linkque.size();
			for (int index = 0; index < step; ++index)
			{
				Node* temp = nullptr;
				if (!linkque.empty())
				{
					temp = linkque.front();
					linkque.pop();
				}
				if (nullptr != temp)
				{
					if (!que.empty())
					{

						temp->left = que.front();
						que.pop();
						linkque.push(temp->left);

					}
					if (!que.empty())
					{

						temp->right = que.front();
						que.pop();
						linkque.push(temp->right);
					}
				}
			}
		}

		return root;
	}

	template <typename Node, typename Container, typename T>
	auto generateBT_helper(T&& arg)
	{
		//cout << type_name<decltype(arg)>() << endl;
		if constexpr (is_same_v<Container, remove_reference_t<decltype(arg)>>)
		{
			Node* root = generate_BT<Node>(std::move(arg));

			return std::make_tuple(root);
		}
		else
		{
			return std::make_tuple(arg);
		}
	}


	template <typename Node, typename Container, typename T>
	auto generateList_helper(T&& arg)
	{
		//cout << type_name<decltype(arg)>() << endl;
		if constexpr (is_same_v<Container, remove_reference_t<decltype(arg)>>)
		{
			Node* root = generateList<Node>(std::move(arg));

			return std::make_tuple(root);
		}
		else
		{
			return std::make_tuple(arg);
		}
	}

	template<typename Node, typename Call, typename T>
	void AlgorithmNcb_helper(Call cb, T root)
	{
		if constexpr (is_same_v<Node, remove_pointer_t<decltype(root)>>)
		{
			cb(root);
		}
	}

	template<typename Node, typename Container, typename Head>
	auto dispatchandcatTree(Head&& head)
	{
		return generateBT_helper<Node, Container>(head);
	}

	template<typename Node, typename Container, typename Head, typename... Tail>
	auto dispatchandcatTree(Head&& head, Tail&&... tail)
	{
		return tuple_cat(generateBT_helper<Node, Container>(head), dispatchandcatTree <Node, Container>(tail...));
	}

	template<typename Node, typename Container, typename Head>
	auto dispatchandcatList(Head&& head)
	{
		return generateList_helper<Node, Container>(head);
	}

	template<typename Node, typename Container, typename Head, typename... Tail>
	auto dispatchandcatList(Head&& head, Tail&&... tail)
	{
		return tuple_cat(generateList_helper<Node, Container>(head), dispatchandcatList <Node, Container>(tail...));
	}

	template <typename Call, class Tuple, size_t... Is>
	constexpr auto  invokecb(Call cb, Tuple t, std::index_sequence<Is...>) {
		cb(get<Is>(t)...);
	}

	template <typename Node, typename Container, typename Call, typename... Arg>
	void TestTreeAlgorithm(Call cb, Arg&&... arg)
	{
		auto argtuple = std::make_tuple(arg...);
		int size = tuple_size<decltype(argtuple)>{};
		auto newArg = std::apply([](auto&&... args)
			{
				return dispatchandcatTree<Node, Container>(args...);
			},
			argtuple);

		invokecb(std::forward<Call>(cb), std::forward<decltype(newArg)>(newArg), std::make_index_sequence < tuple_size<decltype(newArg)>{} > {});
		//TODO 如果invoke中傳入的算法 將樹内元素刪除,將會引起一些内存泄漏, 
		//以下如將全部參數生成的樹各自delete, 將可能引起av.
#if _DEBUG
		cout << "here is debug print" << endl;


		cout << "original data:";
			std::apply([](auto&&... args)
				{
					((AlgorithmNcb_helper<Node>(PrintTree<Node>, args)), ...);
				},
				newArg);

		cout << "end of debug";
#endif
// 		cout << "result data" << endl;
// 		AlgorithmNcb_helper<Node>(PrintTree<Node>, result);
// 		cout << "end of result;" << endl;
// 		AlgorithmNcb_helper<Node>(DeleteTree<Node>, result);
			//所以這裏是delete生成的原數據的代碼, 沒什麽卵用 只要算法中有修改節點指針. 就會出錯
	 		std::apply([](auto&&... args)
				{
					((AlgorithmNcb_helper<Node>(DeleteTree<Node>, args)), ...);
				},
				newArg);
	}

	template <typename Node, typename Container, typename Call, typename... Arg>
	void TestNodeAlgorithmN(Call cb, Arg&&... arg)
	{
		auto argtuple = std::make_tuple(arg...);
		int size = tuple_size<decltype(argtuple)>{};
		auto newArg = std::apply([](auto&&... args)
			{
				return dispatchandcatList<Node, Container>(args...);
			},
			argtuple);

		invokecb(std::forward<Call>(cb), std::forward<decltype(newArg)>(newArg), std::make_index_sequence < tuple_size<decltype(newArg)>{} > {});

#if _DEBUG
		cout << "here is debug print" << endl;


		cout << "original data:";
			std::apply([](auto&&... args)
				{
					((AlgorithmNcb_helper<Node>(printListNode<Node>, args)), ...);
				},
				newArg);

		cout << "end of debug";
#endif
// 		cout << "result data" << endl;
// 		AlgorithmNcb_helper<Node>(printListNode<Node>, result);
// 		cout << "end of result;" << endl;
// 		AlgorithmNcb_helper<Node>(deleteNodeList<Node>, result)
			 		std::apply([](auto&&... args)
			 			{
			 				((AlgorithmNcb_helper<Node>(printListNode<Node>, args)), ...);
			 			},
			 			newArg);
	}


#else
	template <typename Node, template<typename, typename> class Container, typename Alloc>
	Node* generate_BT(Container<int, Alloc>&& list)
	{
		//using value_type = typename T::value_type;
		queue<Node*> que;
		queue<Node*> linkque;
		Node* root = nullptr;
		for (auto& e : list)
		{
			que.push(new Node(e));
		}
		root = que.front();
		que.pop();
		linkque.push(root);
		while (!linkque.empty())
		{
			int step = linkque.size();
			for (int index = 0; index < step; ++index)
			{
				Node* temp = nullptr;
				if (!linkque.empty())
				{
					temp = linkque.front();
					linkque.pop();
				}
				if (nullptr != temp)
				{
					if (!que.empty())
					{

						temp->left = que.front();
						que.pop();
						linkque.push(temp->left);

					}
					if (!que.empty())
					{

						temp->right = que.front();
						que.pop();
						linkque.push(temp->right);
					}
				}
			}
		}
		return root;
	}

	template <typename Node, typename Container, typename Call, typename... Arg>
	void TestTreeAlgorithm(Call cb, Container&& list, Arg... arg)
	{
		Node* root = generate_BT<Node>(std::forward<Container>(list));
		std::invoke(cb, root, arg...);
		PrintTree(root);
		DeleteTree(root);
	}

	template <typename Node, typename container, typename Call, typename... Arg>
	void TestTreeAlgorithm(Call cb, container&& list1, container&& list2, Arg... arg)
	{
		Node* root1 = generate_BT<Node>(std::forward<container>(list1));
		Node* root2 = generate_BT<Node>(std::forward<container>(list1));
		auto result = std::invoke(cb, root1, root2, arg...);
		printListNode(result);
		deleteNodeList(result);

	}


	template <typename Node, typename container, typename Call, typename... Arg>
	void TestTreeAlgorithm(Call cb, container&& list1, container&& list2, container&& list3, Arg... arg)
	{
		Node* root1 = generate_BT<Node>(std::forward<container>(list1));
		Node* root2 = generate_BT<Node>(std::forward<container>(list2));
		Node* root3 = generate_BT<Node>(std::forward<container>(list3));
		auto result = std::invoke(cb, root1, root2, root3, arg...);
		printListNode(result);
		deleteNodeList(result);

	}

	//此處如果cb中刪除元素,則會内存泄漏
	template <typename Node, typename container, typename Call, typename... Arg>
	void TestNodeAlgorithm(Call cb, container&& list, Arg... arg)
	{
		Node* root = generateList<Node>(std::forward<container>(list));
		Node* result = std::invoke(cb, root, arg...);
		printListNode(result);
		deleteNodeList(result);
	}

	template <typename Node, typename container, typename Call, typename... Arg>
	void TestNodeAlgorithmN(Call cb, container&& list1, container&& list2, Arg... arg)
	{
		Node* root1 = generateList<Node>(std::forward<container>(list1));
		Node* root2 = generateList<Node>(std::forward<container>(list1));
		auto result = std::invoke(cb, root1, root2, arg...);
		printListNode(result);
		deleteNodeList(result);

	}


	template <typename Node, typename container, typename Call, typename... Arg>
	void TestNodeAlgorithmN(Call cb, container&& list1, container&& list2, container&& list3, Arg... arg)
	{
		Node* root1 = generateList<Node>(std::forward<container>(list1));
		Node* root2 = generateList<Node>(std::forward<container>(list2));
		Node* root3 = generateList<Node>(std::forward<container>(list3));
		auto result = std::invoke(cb, root1, root2, root3, arg...);
		printListNode(result);
		deleteNodeList(result);

	}


#endif //end of_HAS_CXX17

	// u may use like this
	//testhelper::testRvalue<vector<vector<int>>, vector<int>>(solution90::subsetsWithDup, { });
	//so u don't think the variable name
	template<typename RET, typename SRC, typename CALL, typename... Arg>
	RET testRvalue(CALL callback, SRC&& vec, Arg... arg)
	{
		return callback(vec, arg...);
	}
}

namespace solution15
{
	std::vector<std::vector<int>> threeSum(std::vector<int>& nums)
	{
		if (nums.size() < 3)
			return {};

		std::vector<std::vector<int>> vec;

		std::sort(nums.begin(), nums.end());

		for (size_t i = 0; i < nums.size() - 2; ++i) {
			if (i && nums[i] == nums[i - 1])
				continue;

			size_t low = i + 1;
			size_t high = nums.size() - 1;
			auto target = 0 - nums[i];

			while (low < high) {
				auto sum = nums[low] + nums[high];

				if (sum < target)
					++low;
				else if (target < sum)
					--high;
				else { // target == sum
					vec.push_back({ nums[i], nums[low], nums[high] });

					while (low < high && nums[low] == nums[low + 1])  ++low;
					while (low < high && nums[high] == nums[high - 1]) --high;
					++low;
					--high;
				}
			}
		}

		return vec;
	}
}



bool do_check(int x, int y, std::vector<std::vector<char>>& board, const std::string& word, size_t index)
{
	if (index == word.size())
		return true;
	if (x < 0 || static_cast<size_t>(x) > board[0].size() - 1)
		return false;
	if (y < 0 || static_cast<size_t>(y) > board.size() - 1)
		return false;
	if (board[y][x] == '\0')
		return false;
	if (word[index] != board[y][x])
		return false;

	char temp = board[y][x];
	board[y][x] = '\0';

	bool res = do_check(x - 1, y, board, word, index + 1) ||
		do_check(x + 1, y, board, word, index + 1) ||
		do_check(x, y + 1, board, word, index + 1) ||
		do_check(x, y - 1, board, word, index + 1);

	board[y][x] = temp;

	return res;
}

std::vector<std::string> findWords1(std::vector<std::vector<char>>& board, std::vector<std::string>& words) {
	std::set<std::string> seen;

	for (size_t y = 0; y < board.size(); ++y) {
		for (size_t x = 0; x < board[0].size(); ++x) {
			for (auto& word : words) {
				if (seen.count(word))
					continue;
				if (board[y][x] == word[0]) {
					if (do_check(static_cast<int>(x), static_cast<int>(y), board, word, 0))
						seen.emplace(word);
				}
			}
		}
	}

	std::vector<std::string> ans;
	ans.reserve(seen.size());

	for (auto& word : seen)
		ans.emplace_back(word);

	return ans;
}



bool checknext(const int& x, const int& y, std::vector<std::vector<char> >& board, size_t i, const std::string& word)
{
	bool bfind = false;
	if (i == word.size())
	{
		bfind = true;
		return bfind;
	}
	if (x < 0 || static_cast<size_t>(x) >= board[0].size()) return bfind;
	if (y < 0 || static_cast<size_t>(y) >= board.size()) return bfind;
	const char temp = board[y][x];
	do
	{
		if (i == word.size())
		{
			bfind = true;
			break;
		}

		if ('\0' == temp) break;
		if (word[i] != temp) break;
		board[y][x] = '\0';

		bfind = checknext(x - 1, y, board, i + 1, word)
			|| checknext(x + 1, y , board, i + 1, word)
			|| checknext(x , y - 1, board, i + 1, word)
			|| checknext(x , y + 1, board, i + 1, word);
		board[y][x] = temp;
	}while(false);

	return bfind;
}



vector<string> findWords2(vector<vector<char>>& board, vector<string>& words) {
	std::set<std::string> seen;
	for (int y = 0; y < static_cast<int> (board.size()); ++y)
	{
		for (int x = 0; x < static_cast<int>(board[0].size()); ++x)
		{
			for (auto& word : words)
			{
				// if (1 == word.size() && board[y][x] == word[0])
				// {
				//     bfind = true;
				//     break;
				// }
				//if (word[0] == board[y][x]) continue;
				if (checknext(static_cast<int>(x), static_cast<int>(y), board, 0, word))
				{
					seen.emplace(word);
				}
			}
		}
	}
	std::vector<std::string> ans;
	ans.reserve(seen.size());

	for (auto& word : seen)
	{
		ans.emplace_back(word);
	}
	return ans;
}
struct Trie {
	std::string word;
	Trie* next[26]{};
	int subtrees = 0;
};

void printableTrie(const Trie* root, size_t i = 0)
{
	if (nullptr == root) return;
	for (size_t index = 0; index < 26; ++index)
	{
		if (nullptr != root->next[index])
		{
			auto current = root->next[index];
			if (nullptr != current)
			{
				string s = "=";
				for (size_t in = 0; in < i; ++in) s = s + "=";
				cout << s << i << "=" << index << endl;
				if (!current->word.empty())
				{
					cout << s << "wold not empty:" << current->word << "childrennum" << current->subtrees << endl;
				}
				cout << s << "=" << endl;

				printableTrie(current, index);
			}
			else
			{
				cout << "fuck" << endl;
			}
		}
	}
}

Trie* generate_trie(std::vector<std::string>& words)
{
	Trie* root = new Trie();
	for (auto& word : words)
	{
		auto current = root;
		for (char c : word)
		{
			current->subtrees++;
			if (!current->next[c - 'a'])
			{
				current->next[c - 'a'] = new Trie();
			}
			current = current->next[c - 'a'];
		}
		current->word = std::move(word);
	}
	return root;
}




vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
	std::vector<std::string> ans;
	auto* tries = generate_trie(words);
	//printableTrie(tries);
	for (size_t y = 0; y < board.size(); ++y)
	{
		for (size_t x = 0; x < board[0].size(); ++x)
		{
			if (nullptr != tries->next[board[y][x] - 'a'])
			{
				checkTrie(board, tries, static_cast<int>(x), static_cast<int>(y), ans);

			}
		}
	}
	return ans;

}


Trie* generate_trie1(std::vector<std::string>& words) {
	Trie* root = new Trie();

	for (auto& word : words) {
		auto current = root;

		for (char c : word) {
			current->subtrees++;
			if (!current->next[c - 'a'])
				current->next[c - 'a'] = new Trie();
			current = current->next[c - 'a'];
		}

		current->word = std::move(word);
	}

	return root;
}

void do_check2(int x, int y, std::vector<std::vector<char>>& board, Trie* trie, std::vector<std::string>& answer)
{
	if (x < 0 || x > board[0].size() - 1)
		return;
	if (y < 0 || y > board.size() - 1)
		return;
	if (board[y][x] == '\0')
		return;

	auto* this_node = trie->next[board[y][x] - 'a'];
	if (!this_node)
		return;

	if (!this_node->word.empty()) {
		answer.emplace_back(std::move(this_node->word));
		this_node->word.clear();

		if (this_node->subtrees == 0) {
			Trie* to_delete = nullptr;
			std::swap(trie->next[board[y][x] - 'a'], to_delete);
			trie->subtrees--;
			delete to_delete;
			return;
		}
	}

	char temp = board[y][x];
	board[y][x] = '\0';

	do_check2(x - 1, y, board, this_node, answer);
	do_check2(x + 1, y, board, this_node, answer);
	do_check2(x, y + 1, board, this_node, answer);
	do_check2(x, y - 1, board, this_node, answer);

	board[y][x] = temp;
}

std::vector<std::string> findWords3(std::vector<std::vector<char>>& board, std::vector<std::string>& words) {
	std::vector<std::string> answer;

	auto* trie = generate_trie(words);

	for (size_t y = 0; y < board.size(); ++y) {
		for (size_t x = 0; x < board[0].size(); ++x) {
			if (trie->next[board[y][x] - 'a'])
			{
				do_check2(static_cast<int>(x), static_cast<int>(y), board, trie, answer);
				//checkTrie(board, trie, x, y, answer);
				cout << y << x << answer.back() << endl;
			}
		}
	}

	return answer;
}



//SOLUTION 33
namespace solution33
{
	int search33(vector<int>& nums, int target) {
		if (nums.empty()) return -1;
		int begin = 0;
		int end = static_cast<int>(nums.size() - 1);
		while (begin < end)
		{
			auto middle = begin + (end - begin) / 2;
			if (nums[middle] > nums[end])
			{
				begin = middle + 1;
			}
			else
			{
				end = middle;
			}
		}
		if (target >= nums[begin] && target <= nums[nums.size() - 1])
		{
			end = static_cast<int>(nums.size() - 1);
		}
		else
		{
			begin = 0;
		}
		while (begin <= end)
		{
			auto middle = begin + (end - begin) / 2;
			if (target == nums[middle])
			{
				return middle;
			}
			else if (nums[middle] < target)
			{
				begin = middle + 1;
			}
			else
			{
				end = middle - 1;
			}
		}
		return -1;
	}
}
//solution 34
namespace solution34
{
	vector<int> searchRange34(vector<int>& nums, int target) {
		if (nums.empty()) return { -1, -1 };

		auto lower = std::lower_bound(nums.begin(), nums.end(), target);
		auto upper = --std::upper_bound(nums.begin(), nums.end(), target);

		if (lower == nums.end() || *lower != target) return { -1, -1 };

		auto lowerIndex = static_cast<int>(distance(nums.begin(), lower));
		auto upperIndex = static_cast<int>(distance(nums.begin(), upper));

		return { lowerIndex, upperIndex };
	}
}
//solution 2
namespace solution2
{
	struct ListNode {
		int val;
		ListNode* next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode* next) : val(x), next(next) {}

	};
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* head = nullptr;
		ListNode* prev = nullptr;
		ListNode* l1Temp = l1;
		ListNode* l2Temp = l2;
		bool carry = false;

		while (l1Temp || l2Temp)
		{
			int sum = 0;
			if (l1Temp)
			{
				sum += l1Temp->val;
				l1Temp = l1Temp->next;
			}
			if (l2Temp)
			{
				sum += l2Temp->val;
				l2Temp = l2Temp->next;
			}
			if (carry)
			{
				sum++;
				carry = false;
			}
			if (sum > 9)
			{
				carry = true;
				sum = sum % 10;
			}
			if (nullptr == head)
			{
				head = new ListNode(sum);
				prev = head;
			}
			else
			{
				prev->next = new ListNode(sum);
				prev = prev->next;
			}
		}
		if (carry)
		{
			prev->next = new ListNode(1);
		}
		return head;
	}
}

//solution3
namespace solution3
{
	int lengthOfLongestSubstring(const std::string& s) {
		std::unordered_map<char, int> char_to_last_seem_index;
		int longstsubArray = 0;
		int start = -1;
		for (int i = 0; i < s.size(); ++i)
		{
			char c = s[i];
			if (char_to_last_seem_index.count(c))
			{
				start = std::max(start, char_to_last_seem_index[c]);
			}
			char_to_last_seem_index[c] = i;
			longstsubArray = std::max(longstsubArray, i - start);
		}
		return longstsubArray;

	}
}


//solution 8
namespace solution8
{
	int myAtoi(string s) {
		int ret = 0;
		bool isNagative = false;
		if (s.empty()) return ret;
		size_t i = 0;
		while (i < s.size() && isspace(s[i])) ++i;
		if (i == s.size()) return ret;

		if (s[i] == '-' || s[i] == '+')
		{
			isNagative = s[i++] == '-';//s[i]  == '-' then i += 1
		}
		constexpr auto int_max_devided_by_10 = INT_MAX / 10;
		constexpr auto int_min_devided_by_10 = INT_MIN / 10;

		while (i < s.size() && isdigit(s[i]))
		{
			if (0 == ret && '0' == s[i])
			{
				i++;
				continue;
			}
			auto digit = s[i] - '0';
			if (isNagative) digit *= -1;

			if (ret > int_max_devided_by_10 || (ret == int_max_devided_by_10 && digit > 7)) return INT_MAX;
			if (ret < int_min_devided_by_10 || (ret == int_min_devided_by_10 && digit < -8)) return INT_MIN;
			ret *= 10;
			ret += digit;
			i++;
		}
		return ret;
	}

}
namespace solution102
{
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

	};

	//solution 102
	std::vector<std::vector<int>> levelOrder(TreeNode* root) {
		if (nullptr == root) return {};
		std::queue<TreeNode*> nodes;
		nodes.push(root);
		std::vector<std::vector<int>> out;
		while (!nodes.empty())
		{
			size_t count = nodes.size();
			out.emplace_back();
			while (count-- > 0)
			{
				auto* top = nodes.front();
				nodes.pop();
				out.back().push_back(top->val);
				if (top->left) nodes.push(top->left);
				if (top->right) nodes.push(top->right);
			}
		}
		return out;

	}
}
//solution 103
namespace solution103
{
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

	};

	std::vector<std::vector<int>> levelOrder2(TreeNode* root) {
		if (nullptr == root) return {};
		bool flag = false;
		std::queue<TreeNode*> nodes;
		std::stack<TreeNode*> queuestack;
		nodes.push(root);
		std::vector<std::vector<int>> out;
		while (!nodes.empty())
		{
			size_t count = nodes.size();
			out.emplace_back();
			if (count != 1)
			{
				while (!nodes.empty())
				{
					queuestack.push(nodes.front());
					nodes.pop();
				}
				while (!queuestack.empty())
				{
					nodes.push(queuestack.top());
					queuestack.pop();
				}
			}

			while (count-- > 0)
			{
				auto* top = nodes.front();
				nodes.pop();
				out.back().push_back(top->val);
				if (!flag)
				{
					if (top->left) nodes.push(top->left);
					if (top->right) nodes.push(top->right);
				}
				else
				{
					if (top->right) nodes.push(top->right);
					if (top->left) nodes.push(top->left);

				}
			}
			flag = !flag;
		}
		return out;

	}
}
namespace solution7
{
	//solution 7
	int reverseInteger(int x)
	{
		int ret = 0;
		constexpr auto max_divided_by_10 = INT_MAX / 10;
		constexpr auto min_divided_by_10 = INT_MIN / 10;
		while (x)
		{
			auto p = x % 10;
			if (ret > max_divided_by_10 || (ret == max_divided_by_10 && p > 7)) return 0;
			if (ret < min_divided_by_10 || (ret == min_divided_by_10 && p < -8)) return 0;
			ret *= 10;
			ret += p;
			x /= 10;

		}
		return ret;
	}

}
//solution5
namespace solution5
{
	std::string longestPalindrome(std::string s)
	{
		auto length_of_palindrome = [](const std::string& str, size_t left, size_t right)
		{
			while (left >= 0 && right < str.size() && str[left] == str[right])
			{
				if (0 == left)
				{
					right += 2;
					break;
				}
				right++;
				left--;
			}
			return right - left - 1;
		};

		size_t begin = 0;
		size_t max_length = 0;
		for (size_t i = 0; i < s.size(); ++i)
		{
			auto length = length_of_palindrome(s, i, i);
			auto length2 = length_of_palindrome(s, i, i + 1);
			auto bigger = std::max(length, length2);
			if (bigger > max_length)
			{
				if (bigger % 2) begin = i - bigger / 2;
				else begin = (i + 1) - bigger / 2;
				max_length = bigger;
			}
		}
		return s.substr(begin, max_length);

	}
}


//solution 6
namespace solution6
{
	std::string convert(std::string s, int numRows)
	{
		if (1 == numRows || numRows >= s.size()) return s;
		int step = -1;
		size_t row = 0;
		std::vector<std::string> rows(numRows);
		for (char c : s)
		{
			rows[row] += c;
			if (0 == row || row == static_cast<size_t>(numRows) - 1) step *= -1;
			row += step;
		}

		std::string ans;
		ans.reserve(s.size());
		for (auto& n : rows)
		{
			ans += n;
		}
		return ans;

	}
}

//solution 9
namespace solution9
{
	bool isPalindrome(int x)
	{
		if (x < 0 || (x > 0 && (0 == x % 10)))return false;
		int rhs = 0;
		while (x > rhs)
		{
			rhs *= 10;
			rhs += x % 10;
			x /= 10;
		}
		return rhs == x || rhs / 10 == x;
	}
}

//solution 43
namespace solution43
{
	string multiply(string num1, string num2) {
		//if (num1)
		if ((1 == num1.size() || 1 == num2.size()) && ("0" == num1) || ("0" == num2)) return "0";

		string res(num1.size() + num2.size(), '0');
		string ret;
		for (int index1 = num1.size() - 1; index1 >= 0; --index1)
		{

			int mul = 0;
			int summary = 0;
			for (int index2 = num2.size() - 1; index2 >= 0; --index2)
			{
				
				int sum = 0;

				int n1 = num1[index1] - '0';
				int n2 = num2[index2] - '0';
				int offset = index1 + index2 + 1;
				int c = res[offset] - '0';

				sum = n1 * n2 + mul + c;
				mul = sum / 10;

				res[offset] = sum % 10 + '0';

			}
			if (mul > 0)
			{
				res[index1] = mul + res[index1];
			}

		}
		bool flag = false;
		for (std::string::iterator i = res.begin(); i <= res.end() - 1; ++i)
		{
			if ('0' == *i) continue;
			else
			{
				ret = res.substr(i - res.begin(), res.end() - i);
				break;
			}
		}
		return ret;
	}
}
namespace solution24
{ 
	//solution 24
	struct ListNode24 {
		int val;
		ListNode24* next;
		ListNode24() : val(0), next(nullptr) {}
		ListNode24(int x) : val(x), next(nullptr) {}
		ListNode24(int x, ListNode24* next) : val(x), next(next) {}
	
	};

	ListNode24* swapPairs(ListNode24* head) 
	{
		if (!head) return head;
		auto** pre_left_pointer = &head;
		auto* left = head;
		auto* right = head->next;

		while (left && right)
		{
			left->next = right->next;
			right->next = left;

			*pre_left_pointer = right;
			pre_left_pointer = &left->next;

			if (nullptr == left->next) break;
			left = left->next;
			right = left->next;
		}
		return head;
	}
}
namespace solution27
{
	//solution 27
	int removeElement(vector<int>& nums, int val) {
		size_t j = 0;
		for (auto num : nums)
		{
			if (num != val)
			{
				nums[j++] = num;
			}
		}
		nums.resize(j);
		return static_cast<int>(j);
	}
}

namespace solution12
{
	//solution 12
	string intToRoman(int num) {
		string ret = "";
		vector<int> val = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
		vector<string> str = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

		for (int i = 0; i < val.size(); ++i)
		{

			while (num >= val[i])
			{
				num -= val[i];
				ret += str[i];
			}

		}
		return ret;
	}
}
namespace solution273
{
	//solution 273
	string numberToWords(int num) {
		string ret;
		vector<string> threecommastr = { "", "Thousand " , "Million ", "Billion " };
		vector<string> englishhash = { "One ", "Two ", "Three ", "Four ", "Five ", "Six ", "Seven ", "Eight ", "Nine ", "Ten ",
			"Eleven ", "Twelve ", "Thirteen ", "Fourteen ", "Fifteen ", "Sixteen ", "Seventeen ", "Eighteen ", "Nineteen " };
		vector<string> tentimeshash = { "Ten ", "Twenty ", "Thirty ", "Forty ", "Fifty ", "Sixty ", "Seventy ", "Eighty ", "Ninety " };
		int temp = num;
		//"hundred"
		if (0 == num) return "Zero";
		size_t i = 1;
		bool iszero = false;
		bool islastzero = false;
		while (temp)
		{
			int temp1 = temp % 1000;

			string str;
			if (temp1 >= 100)
			{

				str = englishhash[(temp1 / 100) - 1] + "Hundred ";
				temp1 %= 100;
			}
			if (temp1 <= 19)
			{
				if (0 != temp1) str = str + englishhash[temp1 - 1];
			}
			else
			{
				if (0 != (temp1 / 10))	str = str + tentimeshash[(temp1 / 10) - 1];

				if (0 != temp1 % 10) str += englishhash[(temp1 % 10) - 1];
			}


			if (iszero) islastzero = true;
			else islastzero = false;

			temp = temp / 1000;
			if ((i < threecommastr.size()) && ((temp % 1000) > 0)) str = threecommastr[i] + str;
			i++;
			iszero = false;
			ret = str + ret;
		}
		if (' ' == ret[ret.size() - 1]) ret.pop_back();
		return ret;
	}
}

//solution 17
namespace solution17
{
	map<char, string> digit_map = { {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jki"}, {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"} };

	void helper(vector<string>& result, string& digits, int pos, string& current)
	{
		if (pos == digits.size())
		{
			result.push_back(current);
			return;
		}
		for (auto c : digit_map[digits[pos]])
		{
			current.push_back(c);
			helper(result, digits, pos + 1, current);
			current.pop_back();
		}
	}


	vector<string> letterCombinations(string digits) {
		// 	for (char c : digit_map.at(digits[1]))
	// 	{
	// 		cout << c << endl;
	// 	}
		if (digits.empty()) return {};

		vector<string> res;
		string cur = "";
		helper(res, digits, 0, cur);
		return res;

	}
};
namespace solution19
{
	struct ListNode {
		int val;
		ListNode* next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode* next) : val(x), next(next) {}

	};

	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode* first = head;
		ListNode* end = head;
		//ListNode* prev = nullptr;
		if (NULL == head)
		{
			return head;
		}
		if ((1 == n) && (nullptr == head->next))
		{
			return head->next;
		}
		int temp = n;
		while (temp-- > 0)
		{
			if(nullptr != end) end = end->next;
		}
		if (nullptr == end)
		{
			head = head->next;
			return head;
		}
		while (nullptr != end->next)
		{
			end = end->next;
			//prev = first;
			first = first->next;
		}
		if (nullptr != first && nullptr != first->next) first->next = first->next->next;
		return head;
	}
};

namespace solution1721
{
	struct ListNode {
		int val;
		ListNode* next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode* next) : val(x), next(next) {}

	};
	ListNode* swapNodes(ListNode* head, int k) {
		ListNode* first = head;
		ListNode* end = head;
		ListNode* finalfirst = head;
		ListNode* finalend = head;
		if (nullptr == head || nullptr == head->next)
		{
			return head;
		}
		if (nullptr == head->next->next)
		{
			swap(head->val, head->next->val);
			return head;
		}
		int temp = k;
		while (nullptr != finalend->next)
		{
			while (--temp > 0)
			{
				if (nullptr != end) end = end->next;
				if (nullptr != finalend) finalend = finalend->next;
			}
			if (nullptr != finalend->next)
			{
				if (nullptr != finalfirst)finalfirst = finalfirst->next;
			}
			if (nullptr != finalend)finalend = finalend->next;
			if (nullptr == finalend) break;
		}
		if (nullptr != end  && nullptr != finalfirst)
		{
			std::swap(end->val, finalfirst->val);
		}
		return head;
	}
};

namespace solution46
{
	void helper(vector<vector<int>>& out, size_t index, vector<int>& nums)
	{
		if (index == nums.size())
		{
			out.emplace_back(nums);
			return;
		}
		for (size_t i = index; i < nums.size(); ++i)
		{
			swap(nums[i], nums[index]);
			helper(out, index + 1, nums);
			swap(nums[i], nums[index]);
		}
	}

	vector<vector<int>> permute(vector<int>& nums) {
		vector<vector<int>> ret;
		if (1 == nums.size())	ret.emplace_back(nums);

		else helper(ret, 0, nums);
		return ret;
	}

};

namespace solution31
{
	void nextPermutation(vector<int>& nums) {
		if (1 == nums.size()) return;
		auto periter = std::is_sorted_until(nums.rbegin(), nums.rend());
		if (periter != nums.rend())  std::iter_swap(periter, upper_bound(nums.rbegin(), periter, *periter));
		std::reverse(nums.rbegin(), periter);
	}
};

namespace solution47
{
	void helper(vector<vector<int>>& out, size_t index, vector<int>& nums)
	{
		if (index == nums.size())
		{
			out.emplace_back(nums);
			return;
		}
		set<int, greater<int>> lucky;
		for (size_t i = index; i < nums.size(); ++i)
		{
			if (lucky.find(nums[i]) == lucky.end())
			{
				lucky.insert(nums[i]);
			}
			else continue;
			swap(nums[i], nums[index]);
			helper(out, index + 1, nums);
			swap(nums[i], nums[index]);
		}
	}

	vector<vector<int>> permuteUnique(vector<int>& nums) {
		vector<vector<int>> ret;
		if (1 == nums.size())
		{
			ret.emplace_back(nums);
			return ret;
		}
		else
		{
			helper(ret, 0, nums);
		}
		return ret;
	}
};


namespace solution49
{
	std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
		std::unordered_map<std::string, std::vector<std::string>> map;
		std::vector<std::vector<std::string>> ret;
		if (1 == strs.size())  ret.emplace_back(strs);
		
		for (auto& str : strs)
		{
			std::vector<int> table(26);
			for (char c : str)
			{
				table[static_cast<int>(c) - 'a']++;
			}
			string out;
			out.reserve(26);
			for (auto count : table)
			{
				//out += '#';
				out += std::to_string(count + 'a');
			}
			map[out].push_back(str);
		}
		ret.reserve(map.size());
		for (auto& entry : map)
		{
			ret.emplace_back(std::move(entry.second));
		}
		return ret;
	}
	
};


namespace solution374
{
	struct compare
	{
		bool operator()(pair<int, int> a, pair<int, int> b)
		{
			if (a.second == b.second) return a.first < b.first;
			return a.second < b.second;
		}
	};

	vector<int> topKFrequent(vector<int>& nums, int k) {
		vector<int> ret;
		if (1 == nums.size())
		{
			return nums;
		}

		unordered_map<int, int> map;
		for (auto& n : nums)
		{
			map[n]++;
		}
		priority_queue<pair<int, int>, vector<pair<int, int>>, compare> data(map.begin(), map.end());
		for (size_t i = 0; i < k; ++i)
		{
			ret.emplace_back(data.top().first);
			data.pop();
		}
		return ret;
	}
}

namespace solution28
{
	int strStr(string haystack, string needle)
	{
		int ret = -1;
		if (0 == haystack.size())
		{
			if (0 == needle.size()) return 0;
			return ret;
		}
		for (size_t indexs = 0; indexs <= haystack.size() - 1; ++indexs)
		{
			if (haystack.size() - indexs < needle.size()) break;
			size_t indexn = 0;
			while (indexn < needle.size() && haystack[indexs + indexn] == needle[indexn])
			{
				 indexn++;
			}
			if (indexn == needle.size())
			{
				ret = indexs;
				break;
			}
		}
		return ret;
	}
};


namespace solution38
{
	string countAndSay(int n) {
		if (1 == n) return "1";
		string res = "1";
		for (size_t i = 2; i <= n; ++i)
		{
			size_t step = 1;
			string temp;
			for (size_t is = 0; is < res.size(); is += step, step = 1)
			{
				
				while (res[is] == res[is + step++]);
				step--;
				temp += (step + '0');
				temp += res[is];
				//step = 1;
			}
			res = std::move(temp);
		}
		return res;
	}
};

namespace solution443
{
	int compress(vector<char>& chars) {
		if (1 == chars.size()) return 1;
		size_t charsize = chars.size();
		size_t step = 1;
		size_t rebegin = 0;
		
		for (/*auto& ch : chars*/size_t begin = 0; begin < charsize; begin+=step, step = 1)
		{
			
			while (((begin + step) < charsize) && chars[begin] == chars[begin + step++]);
			if (chars[begin] != chars[begin + step - 1])  
			 step--;
			chars[rebegin++] = chars[begin];
			if (step != 1)
			{
				if (step >= 10)
				{
					size_t temp = (step ) / 10;
					while (temp)
					{

						chars[rebegin++] = temp + '0';
						temp /= 10;
					}
				}
				chars[rebegin++] =( ( step) % 10 ) + '0';
			}
			if (begin + step>= charsize)
			{
				break;
			}
		}
		return rebegin;
	}
};


namespace solution136
{
	int singleNumber(vector<int>& nums) {
		int answer = 0;
		for (auto& num : nums)
		{
			answer ^= num;
		}
		return answer;
	}
};


namespace solution137
{
	int singleNumber(std::vector<int>& nums) {
		int ones = 0; 
		int twice = 0;
		for (auto& num : nums)
		{
			ones = (ones ^ num) & ~twice;
			twice = (twice ^ num) & ~ones;
		}
		return ones;

	}
};

namespace solution138
{
	class Node {
	public:
		int val;
		Node* next;
		Node* random;

		Node(int _val) {
			val = _val;
			next = NULL;
			random = NULL;
		}
	};

			Node* copyRandomList(Node* head) {
				if (nullptr == head) return head;
				vector<Node*> orrandomList;
				vector<Node*> oriList;
				vector<Node*> unFinished;
			
				Node* next = head;
				Node* newHead = new Node(0);
				Node* newNext = newHead;
			
				while (nullptr != next)
				{
					newNext->val = next->val;
		
					
					orrandomList.push_back(next);
					oriList.push_back(newNext); 
					if (nullptr != next->next)
					{
						newNext->next = new Node(0);
						
					}
					if (nullptr != next->random)
					{
						auto iter = std::find(orrandomList.begin(), orrandomList.end(), next->random);
						if (orrandomList.end() != iter)
						{
							newNext->random = oriList[distance(orrandomList.begin(), iter)];
						}
						else
						{
							newNext->random = next->random;
							unFinished.push_back(newNext);
						}
					}

					newNext = newNext->next;
					
					next = next->next;
				}

				for (auto p : unFinished)
				{
					auto iter = std::find(orrandomList.begin(), orrandomList.end(), p->random);
					if (orrandomList.end() != iter)
					{
						p->random = oriList[distance(orrandomList.begin(), iter)];
					}
				}
				return newHead;
				
			
	};
};

namespace solution199
{
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
		
	};
	vector<int> rightSideView(TreeNode* root) {
		vector<int> out;
		if (nullptr == root) return out;;
		if (nullptr == root->left && nullptr == root->right)
		{
			out.emplace_back(root->val);
			return out;
		}
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty())
		{
			size_t num = q.size();
			while (num-- > 0)
			{
				auto node = q.front();
				q.pop();
				if (0 == num) out.emplace_back(node->val);
				if (nullptr != node->left) q.push(node->left);
				if (nullptr != node->right) q.push(node->right);

			}
		}
		return out;

	}
};

namespace solution235
{
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		
	};
	
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (nullptr == root) return nullptr;
		if (p->val < root->val && q->val < root->val) return lowestCommonAncestor(root->left, p, q);
		if (p->val > root->val && q->val > root->val) return lowestCommonAncestor(root->right, p, q);
		else return root;
	}
};


namespace solution236
{
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}

	};

	bool find_lca(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode*& answer)
	{
		if (nullptr == root) return false;
		int count = 0;
		count += (root == p) || (root == q);
		count += find_lca(root->left, p, q, answer);
		count += find_lca(root->right, p, q, answer);
		if (count >= 2) answer = root;
		return count;
	}
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (nullptr == root) return root;
		TreeNode* answer = nullptr;
		find_lca(root, p, q, answer);
		return answer;
	}
};

namespace solution300
{
	int lengthOfLIS(std::vector<int>& nums) 
	{
		std::vector<int> res;
		res.reserve(nums.size());
		for (auto num : nums)
		{
			auto lb = std::lower_bound(res.begin(), res.end(), num);
			if (lb == res.end()) res.emplace_back(num);
			else *lb = std::move(num);
		}
		return static_cast<int>(res.size());
	}
};

//mission failed
namespace solution712
{

	int minimumDeleteSum(string s1, string s2) 
	{
		vector<vector<int>> dp(s1.length() + 1, vector<int>(s2.length() + 1));
		for (int j = 0; j < s2.length() - 1; ++j)
		{
			dp[0][j + 1] = dp[0][j] + s2[j];
		}
		for (int i = 0; i < s1.length() - 1; ++i)
		{
			dp[i + 1][0] = dp[i][0] + s2[i];
		}
		for (int i = 0; i < s1.length(); ++i)
		{
			for (int j = 0; j < s2.length(); ++j)
			{
				if (s1[i] == s2[j]) dp[i + 1][j + 1] = dp[i ][j];
				else dp[i + 1][j + 1] = std::min(dp[i ][j + 1] + s1[i], dp[i + 1][j] + s2[j]);
			}
		}
		return /*sum - 2 **/ dp[s1.length()][s2.length()];
	}
	
}

namespace solution56
{
	std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
		if (intervals.size() == 1)
			return intervals;

		std::sort(intervals.begin(), intervals.end(), [](auto& l, auto& r) { return l[0] < r[0]; });

		size_t i = 0;

		for (size_t j = 1; j < intervals.size(); ++j) {
			if (intervals[i][1] >= intervals[j][0]) {
				intervals[i][1] = std::max(intervals[i][1], intervals[j][1]);
				continue;
			}

			intervals[++i] = intervals[j];
		}

		intervals.resize(i + 1);
		return intervals;
	}

}

namespace solution81
{
	bool search(vector<int>& nums, int target) {
		if (nums.empty()) return false;
		int begin = 0;
		int end = static_cast<int>(nums.size() - 1);

		while (begin < end)
		{
			while (begin < end && nums[begin] == nums[static_cast<size_t>(begin) + 1]) begin++;
			while (begin < end && nums[end] == nums[static_cast<size_t>(end) - 1]) end--;

			auto middle = begin + (end - begin) / 2;
			if (nums[middle] > nums[end]) begin = middle + 1;
			else end = middle;
		}
		if (target >= nums[static_cast<int>(begin)] && target <= nums[nums.size() - 1]) end = static_cast<int>(nums.size() - 1);
		else begin = 0;
		while (begin <= end)
		{
			auto middle = begin + (end - begin) / 2;
			if (nums[static_cast<size_t>(middle)] == target) return true;
			else if (nums[static_cast<size_t>(middle)] < target) begin = middle + 1;
			else end = middle - 1;
		}
		return false;
	}


}

namespace solution92
{
	struct ListNode {
		int val;
		ListNode* next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode* next) : val(x), next(next) {}
	
	};
	ListNode* reverseBetween(ListNode* head, int left, int right) {
		if (nullptr == head) return head;
		auto* current1 = head;
		auto* current2 = head;
		for (int indexleft = 1; indexleft < left; indexleft++)
		{
			current1 = current1->next;
			current2 = current2->next;
		}
		while (left < right)
		{
			for (int indexright = 0; indexright < (right - left); indexright++)
			{
				current2 = current2->next;
			}
			std::swap(current1->val, current2->val);
			current1 = current1->next;
			current2 = current1;
			left++; 
			right--;
		}
		return head;
	}
}
namespace solution94
{
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

	};
	void do_travel(TreeNode* root, vector<int>& out)
	{
		if (nullptr == root) return;
		do_travel(root->left, out);
		out.emplace_back(root->val);
		do_travel(root->right, out);

	}
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> ret;
		if (nullptr == root) return ret;
		do_travel(root, ret);
		return ret;
	}
}

namespace solution144
{
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

	};
	inline void do_travel(TreeNode* root, vector<int>& out)
	{
		//if (nullptr == root) return; delete this line because  fumction calls are too expensive, may be i can try not call this function when pointer is null, so i get 100% beats

		out.emplace_back(root->val);
		if (nullptr != root->left) do_travel(root->left, out);
		if (nullptr != root->right) do_travel(root->right, out);

	}
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> ret;
		if (nullptr == root) return ret;
		do_travel(root, ret);
		return ret;
	}
}
namespace solution145
{
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

	};
	//as i said, function calls are expresive, so this time i don't call any function, just use stack, 100% beats :)
	vector<int> postorderTraversal(TreeNode* root) {
		vector<int> ret;
		stack<TreeNode*> traverstack;
		if (nullptr == root) return ret;
		auto* prev = root;
		traverstack.push(prev);
		while (!traverstack.empty())
		{
			auto* temp = traverstack.top();

			if (temp == prev)
			{
				ret.emplace_back(temp->val);
				traverstack.pop();
			}
			if (nullptr != temp->left)
			{
				traverstack.push(temp->left);
			}
			if (nullptr != temp->right)
			{
				traverstack.push(temp->right);
			}

			if (!traverstack.empty()) prev = traverstack.top();
		}

		std::reverse(ret.begin(), ret.end());


		return ret;
	}
}

namespace solution133
{
	class Node {
	public:
		int val;
		std::vector<Node*> neighbors;

		Node() {
			val = 0;
			neighbors = std::vector<Node*>();
		}

		Node(int _val) {
			val = _val;
			neighbors = std::vector<Node*>();
		}

		Node(int _val, std::vector<Node*> _neighbors) {
			val = _val;
			neighbors = _neighbors;
		}
	};
	Node* cloneGraph(Node* node)
	{
		if (nullptr == node) return node;
		if (node->neighbors.empty()) return new Node(node->val);
		std::queue<Node*> nodes;
		std::unordered_map<Node*, Node*> org_to_clone;
		org_to_clone[node] = new Node(node->val);
		nodes.push(node);
		while (!nodes.empty())
		{
			auto* topnode = nodes.front();
			nodes.pop();
			for (auto neighbor : topnode->neighbors)
			{
				if (!org_to_clone.count(neighbor))
				{
					org_to_clone[neighbor] = new Node(neighbor->val);
					nodes.push(neighbor);
				}
				org_to_clone[topnode]->neighbors.push_back(org_to_clone[neighbor]);
			}
		}
		return org_to_clone[node];
	}
};

	void reorderList(ListNode* head)
	{
		if (nullptr == head) return;
		auto* ptr = head;
		std::deque<ListNode*> list;
		while (nullptr != head)
		{
			list.push_back(head);
			head = head->next;
		}
		vector<ListNode*> finalList;
		finalList.reserve(list.size());
		size_t count = (list.size() + 1) / 2;
		while (!list.empty())
		{
			auto* first = list.front();
			auto* end = list.back();
			finalList.push_back(left);

			if (left != right) {
				finalList.push_back(right);
				list.pop_back();
			}

			list.pop_front();
		}

		for (size_t i = 0; i < finalList.size() - 1; ++i)
			finalList[i]->next = finalList[i + 1];

		finalList.back()->next = nullptr;
		
		return;
	}
}

namespace solution114
{
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

	};

	void flatten(TreeNode* root) {
		if (nullptr == root) return;
		while (nullptr != root)
		{
			if (nullptr != root->left)
			{
				auto* pre = root->left;
				while (nullptr != pre->right) pre = pre->right;
				pre->right = root->right;
				root->right = root->left;
				root->left = nullptr;
			}
			root = root->right;
		}
	}
}

namespace solution429
{
	class Node {
	public:
		int val;
		vector<Node*> children;

		Node() {}

		Node(int _val) {
			val = _val;
		}

		Node(int _val, vector<Node*> _children) {
			val = _val;
			children = _children;
		}
	};
	

	vector<vector<int>> levelOrder(Node* root) {
		vector<vector<int>> ret;
		if (nullptr == root)  return ret;
		queue<Node*> que;
		que.push(root);
		int count = 0;
		int lastcount = 1;
		vector<int> v;
		while (!que.empty())
		{
			auto* temp = que.front();
			que.pop();
			lastcount--;
			v.emplace_back(temp->val);
			for (auto p : temp->children)
			{
				if (nullptr != p)
				{
					que.push(p);
					count++;
				}
			}
			if (0 == lastcount)
			{
				lastcount = count;
				count = 0;
				ret.emplace_back(v);
				v.clear();
				v.reserve(count);

			}
		}
		return ret;
	}
}


namespace solution402
{
	string removeKdigits(string num, int k) {
		if (num.empty()) return "";
		if (num.size() == k) return "0";
		string ret;
		ret.reserve(num.size());
		for (auto c : num)
		{
			
			while (!ret.empty() && ret.back() > c && k > 0)
			{
				ret.pop_back();
				k--;
			}
			
			ret.push_back(c);
		}
		if (k > 0)
		{
			size_t newsize = (ret.size() > k) ? ret.size() - k : ret.size();
			ret.resize(newsize);
			ret.shrink_to_fit();
		}

		if (1 != ret.size())
		{
			size_t index = 0;
			 for (; index != ret.size(); ++index)
			 {
			 	if ('0' != ret[index])break;
			}
			
			if (index == ret.size()) index--;

			return ret.substr(index, ret.size());
		}

		return ret;

	}
}


namespace solution321
{
	vector<int> findmax(vector<int>& vec, int nums)
	{
		vector<int> ret;
		ret.reserve(vec.size());
		if (0 == nums) return std::move(ret);
		if (nums == vec.size())
		{
			ret.assign(vec.begin(), vec.end());
			return std::move(ret);
		}
		int removal = vec.size() - nums;
		for (int i = 0; i < vec.size(); ++i)
		{
			while (!ret.empty() && ret.back() < vec[i] && removal > 0)
			{
				ret.pop_back();
				removal--;
			}
			ret.emplace_back(vec[i]);
		}
		while (removal--) ret.pop_back();

		return std::move(ret);
	}
	vector<int> combine(vector<int>& vec1, vector<int>& vec2)
	{
		vector<int> ret;
		ret.reserve(vec1.size() + vec2.size());
		while (!vec1.empty() && !vec2.empty())
		{
			vector<int>* p = nullptr;
			vector<int>::iterator iter;
			if (*vec1.begin() > *vec2.begin())
			{
				iter = vec1.begin();
				p = &vec1;
			}
			else if (*vec1.begin() < *vec2.begin())
			{
				iter = vec2.begin();
				p = &vec2;
			}
			else //== lookup after element, push the bigger side
			{
				auto iter1 = vec1.begin() + 1;
				auto iter2 = vec2.begin() + 1;
				while (nullptr == p && iter1 != vec1.end() && iter2 != vec2.end())
				{
					if (*iter1 == *iter2)
					{
						iter1++;
						iter2++;
						continue;
					}
					if (*iter1 > *iter2)
					{
						iter = vec1.begin();
						p = &vec1;
					}
					else
					{
						iter = vec2.begin();
						p = &vec2;
					}
					iter1++;
					iter2++;
				}
				if (nullptr == p && iter1 == vec1.end())
				{
					iter = vec2.begin();
					p = &vec2;
				}
				if (nullptr == p && iter2 == vec2.end())
				{
					iter = vec1.begin();
					p = &vec1;
				}
			}
			ret.emplace_back(*iter);
			if (nullptr != p)
				p->erase(iter);
		}
		if (!vec1.empty()) ret.insert(ret.end(), vec1.begin(), vec1.end());
		if (!vec2.empty()) ret.insert(ret.end(), vec2.begin(), vec2.end());
		return std::move(ret);
	}
	bool greatervec(vector<int>& src, vector<int>& vec)
	{
		if (src.empty()) return true;
		if (src.size() != vec.size()) return false;
		auto iter1 = src.begin();
		auto iter2 = vec.begin();
		for (; iter1 != src.end(); ++iter1, ++iter2)
		{
			if (*iter1 < *iter2) return true;
			else if (*iter1 > *iter2) break;
		}
		return false;
	}
	vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
		vector<int> ret;
		if (nums1.empty() && nums2.empty() || k == 0) return std::move(ret);
		int size1 = nums1.size();
		int size2 = nums2.size();
		ret.reserve(k);
		for (int index = std::max(0, k - size2); index <= std::min(size1, k); index++)
		{
			if (index > size1 || (k - index) > size2) continue;
			cout << "=====loop====";
			vector<int> temp1 = findmax(nums1, index);
			cout << "========" << endl;
			for (auto i : temp1)
			{
				cout << " " << i << " ";
			}
			cout << endl;
			vector<int> temp2 = findmax(nums2, k - index);
			cout << "========" << endl;
			for (auto i : temp2)
			{
				cout << " " << i << " ";
			}
			cout << endl;
			vector<int> tempres = combine(temp1, temp2);
			if (greatervec(ret, tempres))
			{
				ret.assign(tempres.begin(), tempres.end());
			}
		}
		return ret;
	}
}

namespace solution11
{
	int maxArea(vector<int>& height) {
		int res = 0;
		int left = 0, right = height.size() - 1;
		while (left < right)
		{
			int vleft = height[left], vright = height[right];
			int tempres = std::min(vleft, vright) * (right - left);
			res = std::max(res, tempres);
			if (vleft > vright)
			{
				do {
					right--;
				} while (left < right && vright >= height[right]);
			}
			else if (vleft < right)
			{
				do
				{
					left++;
				} while (left < right && vleft >= height[left]);

			}
		}
		return res;
	}
}

namespace solution16
{
	int threeSumClosest(vector<int>& nums, int target) {
		if (nums.size() < 3) return 0;
		sort(nums.begin(), nums.end());
		int best_delta = INT_MAX;
		for (size_t index = 0; index < nums.size() - 2; ++index)
		{
			if (index && (nums[index] == nums[index - 1])) continue;
			size_t low = index + 1;
			size_t high = nums.size() - 1;
			while (low < high)
			{
				auto sum = nums[index] + nums[low] + nums[high];
				if (sum == target) return target;
				auto delta = target - sum;
				if (abs(delta) < abs(best_delta))
				{
					best_delta = delta;
				}
				if (sum > target)
				{
					size_t high1 = high - 1;
					while (low < high1 && nums[high] == nums[high1]) high1--;
					high = high1;
				}
				else if (sum < target)
				{
					size_t low1 = low + 1;
					while (low1 < high && nums[low] == nums[low1]) low1++;
					low = low1;
				}
			}
		}
		return target - best_delta;
	}
}

namespace solution75
{
	void sortColors(vector<int>& nums) {
		int end = nums.size() - 1;
		if (end < 1) return;
		int begin = 0, i = 0;
		while (i <= end)
		{
			if (0 == nums[i])
			{
				if (nums[i] != nums[begin])std::swap(nums[i++], nums[begin++]);
				else
				{
					i++, begin++;
				}
			}
			else if (1 == nums[i])
			{
				i++;
			}
			else
			{
				if (nums[i] != nums[end])std::swap(nums[i], nums[end--]);
				else
				{
					end--;
				}
			}
		}
	}
}


namespace solution238
{
	std::vector<int> productExceptSelf(std::vector<int>& nums) {
		vector<int> ret(nums.size());
		ret[0] = 1;
		for (size_t i = 1; i < nums.size(); ++i)
		{
			ret[i] = ret[i - 1] * nums[i - 1];
		}
		int product_on_the_right = 1;
		for (size_t i = nums.size(); i-- > 0; )
		{
			ret[i] = ret[i] * product_on_the_right;
			product_on_the_right *= nums[i];
		}
		return ret;
	}
}

namespace solution313
{
	int nthSuperUglyNumber(int n, vector<int>& primes) {
		if (n <= 0) return 0;
		if (n == 1) return 1;
		vector<int> uglyNumber;
		uglyNumber.reserve(n);
		uglyNumber.emplace_back(1);
		std::vector<int> pointer(primes.size(), 0);

		for (size_t i = 1; i < n; ++i)
		{
			int nextugly = INT_MAX;
			for (size_t j = 0; j < primes.size(); ++j)
				nextugly = min(nextugly, uglyNumber[pointer[j]] * primes[j]);
			uglyNumber.emplace_back(nextugly);
			for (size_t j = 0; j < primes.size(); ++j)
				if (primes[j] * uglyNumber[pointer[j]] == nextugly) pointer[j]++;
		}
		return uglyNumber.back();
	}
}



namespace solution322
{
	using graph_t = std::map<std::string, std::multiset<string>>;

	void route(const string& begin_port, graph_t& graph, std::vector<std::string>& answer)
	{
		auto& destinations = graph[begin_port];
		while (!destinations.empty())
		{
			auto dest = *destinations.begin();
			destinations.erase(destinations.begin());
			route(dest, graph, answer);
		}
		answer.emplace_back(begin_port);
	}


	vector<string> findItinerary(vector<vector<string>>& tickets)
	{
		graph_t fight_graph;
		std::vector<std::string> answer;
		for (auto ticket : tickets)
		{
			fight_graph[ticket[0]].emplace(ticket[1]);
		}
		route("JFK", fight_graph, answer);
		std::reverse(answer.begin(), answer.end());
		return answer;
	}
}

namespace solution343
{
	// 7 = 3 + 4, 3*4 = 12
	// 8 = 3 + 3 + 2, 3*3*2 = 18
	// 9 = 3 + 3 + 3, 3 * 3 * 3 = 27
	// 10 = 3 + 3 + 4,  3 * 3  * 4 =36
	// 11 = 3 + 3 + 3 + 2, 3 * 3 * 3 * 2 = 54   
	int integerBreak(int n)
	{
		if (2 == n || 1 == n) return 1;
		if (3 == n) return 2;
		int result = 1;
		while (n > 4)
		{
			result *= 3; // n times 3
			n -= 3;
		}
		return result * n;
	}
}

//part of concurrency solution has been moved to leetcodeconcurrency.cpp
//here just for those declare
//see  leetcodeconcurrency.cpp
namespace Csolution1115
{
	void test();
}

namespace Csolution1116
{
	void test();
}

namespace Csolution1117
{
	void test();
}

namespace Csolution1195
{
	void test();
}

namespace Csolution1226
{
	void test();
}

//end of declaration
	namespace solution1123
	{
		struct TreeNode {
			int val;
			TreeNode* left;
			TreeNode* right;
			TreeNode() : val(0), left(nullptr), right(nullptr) {}
			TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
			TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

		};

		auto* find(TreeNode* root, int& height)
		{
			if (nullptr == root) return root;
			int heightleft = 0;
			int heightright = 0;
			auto* pLeft = find(root->left, heightleft);
			auto* pRight = find(root->right, heightright);
			height = std::max(heightleft, heightright) + 1;
			if (heightleft == heightright) return root;
			if (heightleft > heightright) return pLeft;
			return pRight;
		}


		TreeNode* lcaDeepestLeaves(TreeNode* root) {
			if (nullptr == root) return root;
			if (nullptr == root->left && nullptr == root->right) return root;
			int height = 0;
			return find(root, height);
		}
	}


namespace solution89
{


		vector<int> greyCode(int n)
		{
			if (0 == n) return { 0 };
			if (1 == n) return { 0, 1 };
			vector<int> ret = { 0, 1 };
			ret.reserve(1 << n);
			for (int i = 1; i < n; ++i)
			{
				vector<int> temp;
				transform(ret.rbegin(), ret.rend(), back_inserter(temp), [&i](int n) {return n | (1 << i); });
				copy(temp.begin(), temp.end(), back_inserter(ret));
			}
			return ret;
		}
	}
//remove repeat string was waste too many time, but i like this way, i don't like recursive way, although that way is simple too.
namespace solution22
{
	vector<string> generateParenthesis(int n) {
		if (0 == n) return {};
		if (1 == n) return { "()" };
		vector<string>  ret = { "()" };
	
		vector<string> tmp;
		for (int i = 2; i <= n; ++i)
		{
			for (auto tep : ret)
			{
				for (int index = 0; index < i; ++index)
				{
					string temp = tep;
					temp.insert(index, "()");
					if (tmp.end() == find(tmp.begin(), tmp.end(), temp))
					{
						tmp.emplace_back(temp);
					}
				}
			}
			ret.clear();
			ret.reserve(tmp.size());
			copy(tmp.begin(), tmp.end(), back_inserter(ret));
			tmp.clear();
		}
		return ret;
	}
}


namespace solution48
{
	void rotate(vector<vector<int>>& matrix) {
		if (1 == matrix.size() && 0 == matrix[0].size()) return;
		size_t size = matrix.size();
		for (int i = 0; i < size / 2; i++)
		{
			int low = i, high = size - i - 1;
			for (int j = low; j < high; ++j)
			{
				int posrow = size - j - 1;
				int poscol = size - i - 1;
				swap(matrix[i][j], matrix[posrow][i]);

				swap(matrix[posrow][i], matrix[poscol][posrow]);

				swap(matrix[poscol][posrow], matrix[j][poscol]);

			}
		}

	}

}

namespace solution48
{
	vector<vector<int>> generateVector(int n)
	{
		vector<vector<int>> ret;
		for (int i = 0; i < n; i++)
		{
			ret.emplace_back(vector<int>(n));
		}
		return ret;
	}
	void fillVector(vector<vector<int>>& res)
	{
		//pass a empty vector like 
		int i = 1;
		for (auto& v : res)
		{
			int j = 1;
			for_each(v.begin(), v.end(), [&i, &j](int& x) {x = i * j++; });
			i++;
		}

	}

	void printVector(vector<vector<int>>& res)
	{
		for (auto v : res)
		{
			copy(v.begin(), v.end(), ostream_iterator<int>(cout, "  "));
			cout << endl;
		}
	}


	void print90degreeVector(vector<vector<int>>& res)
	{
		size_t maxrow = res.size();
		for (int i = 0; i < maxrow; ++i)
		{
			for (int j = maxrow; j > 0; j--)
			{
				cout << res[j - 1][i] << "  ";
			}
			cout << endl;
		}
	}
	void rotate(vector<vector<int>>& matrix) {
		if (1 == matrix.size() && 0 == matrix[0].size()) return;
		size_t size = matrix.size();
		for (int i = 0; i < size / 2; i++)
		{
			int low = i, high = size - i - 1;
			for (int j = low; j < high; ++j)
			{
				int posrow = size - j - 1;
				int poscol = size - i - 1;
				swap(matrix[i][j], matrix[posrow][i]);

				swap(matrix[posrow][i], matrix[poscol][posrow]);

				swap(matrix[poscol][posrow], matrix[j][poscol]);

			}
		}

	}

}

namespace solution29
{
	int divide(int dividend, int divisor) {

		constexpr unsigned int max_int = INT_MAX;
		constexpr unsigned int min_int = INT_MIN;
		constexpr size_t bitsize = 33;
		int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
		int dividend_ = dividend > 0 ? dividend : -dividend;
		int divisor_ = divisor > 0 ? divisor : -divisor;
		unsigned int bit_num[bitsize];
		unsigned int i = 0;
		long long d = divisor_;
		bit_num[i] = d;
		while (d <= dividend_) {
			d = d << 1;
			bit_num[++i] = d;
		}
		i--;

		unsigned int result = 0;
		while (dividend_ >= divisor_) {
			if (dividend_ >= bit_num[i]) {
				dividend_ -= bit_num[i];
				result += (1 << i);
			}
			else {
				i--;
			}
		}

		if (result > max_int && sign > 0) {
			return max_int;
		}
		return (int)result * sign;
	}
}

namespace solution39
{
	void helper(vector<int>& candidates, vector<vector<int>>& result, vector<int>& tempresult, const int index, const int target)
	{
		if (target < 0) return;
		if (0 == target)
		{
			result.emplace_back(tempresult);
			return;
		}
		for (int pos = index; pos < candidates.size(); ++pos)
		{
			if ((pos > index) && (candidates[pos] == candidates[pos - 1])) continue;
			if (candidates[pos] > target) return;
			tempresult.push_back(candidates[pos]);
			helper(candidates, result, tempresult, pos, target - candidates[pos]);
			tempresult.pop_back();
		}
	}
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		vector<vector<int>> ret;
		if (0 == candidates.size()) return ret;
		sort(candidates.begin(), candidates.end());
		vector<int> temp;
		helper(candidates, ret, temp, 0, target);
		return ret;
	}
}


namespace solution50
{
	double myPow(double x, int n) {
		bool sign = false;
		long long exp;
		exp = n < 0 ? -static_cast<long long>(n) : static_cast<long long>(n);
		sign = n < 0 ? true : false;
		double result = 1.0;
		while (exp)
		{
			if (exp & 1) result *= x;
			exp >>= 1;
			x *= x;
		}
		return sign ? 1 / result : result;
	}
}



namespace solution54
{
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		vector<int> ret;
		int stepi = 1, stepj = 1;
		int left = 0, right = matrix[0].size();
		int  top = 0, bottum = matrix.size();
		for (int r = 0, c = 0; r <= (bottum + 1) / 2 && c < (right + 1) / 2; ++r, ++c)
		{
			for (int i = c; i < right - c; i++) {
				ret.emplace_back(matrix[r][i]);
			}
			//right
			for (int i = r + 1; i < bottum - r; i++) {
				ret.emplace_back(matrix[i][right - c - 1]);
			}
			//bottom
			for (int i = right - c - 2; bottum - r - 1 > r && i >= c; i--) {
				ret.emplace_back(matrix[bottum - r - 1][i]);
			}
			//left
			for (int i = bottum - r - 2; right - c - 1 > c && i > r; i--) {
				ret.emplace_back(matrix[i][c]);
			}

		}
	}
}

namespace solution55
{
	bool canJump(vector<int>& nums) {
		if (1 == nums.size())
		{
			return true;
		}
		size_t size = nums.size();
		int right = 0;
		for (int index = 0; index < size; ++index)
		{
			if (index <= right)
			{
				right = std::max(right, index + nums[index]);
			}
			else
			{
				return false;
			}
		}
		return true;
	}
}


namespace solution57
{
	vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
		constexpr int NAP = -1;
		vector<vector<int>> ret;
		if (0 == intervals.size())
		{
			ret.emplace_back(newInterval);
			return ret;
		}
		int low = newInterval[0], high = newInterval[1];
		int newintervallow = NAP, newIntervalHigh = NAP;
		bool isinsert = false;

		for (auto& element : intervals)
		{
			if (!isinsert && NAP != newintervallow && element[0] > newIntervalHigh)
			{
				ret.push_back({ newintervallow, newIntervalHigh });
				isinsert = true;
			}
			if (!isinsert && element[0] > high)
			{
				ret.emplace_back(newInterval);
				isinsert = true;
			}
			if (element[1] < low || element[0] > high)
			{
				ret.emplace_back(element);
				continue;
			}
			if (NAP == newintervallow)
			{
				newintervallow = min(element[0], low);
			}
			else
			{
				newintervallow = min(element[0], newintervallow);

			}
			newIntervalHigh = max(element[1], high);
		}
		if (!isinsert)
		{
			if (NAP != newintervallow)ret.push_back({ newintervallow, newIntervalHigh });
			else ret.push_back({ low, high });
		}
		return ret;
	}
	auto testcase()->void
	{
		vector<vector<int>> i1 = { {1,2},{6,9} };
		vector<vector<int>> i2 = { {1,2}, {3,5},{6,7},{8,10},{12,16} };
		vector<vector<int>> i3 = {};
		vector<vector<int>> i4 = { {1,5} };
		vector<vector<int>> i5 = { {1,5} };


		vector<int> ni1 = { 2, 5 };
		vector<int> ni2 = { 4, 8 };
		vector<int> ni3 = { 5, 7 };
		vector<int> ni4 = { 2, 3 };
		vector<int> ni5 = { 2, 7 };
		vector<int> ni6 = { 6, 8 };
		vector<int> ni7 = { 100, 200 };
		vector<int> ni8 = { 0, 0 };
		vector<int> ni9 = { 4, 5 };
		auto test = [](vector<vector<int>>&& data)
		{
			cout << "start print" << endl;
			for (auto& d : data)
			{
				cout << "[";
				for (auto& e : d)
				{
					cout << e << " ";
				}
				cout << "]" << endl;
			}
		};

		test(solution57::insert(i1, ni1));
		test(solution57::insert(i2, ni2));
		test(solution57::insert(i3, ni3));
		test(solution57::insert(i4, ni4));
		test(solution57::insert(i5, ni5));
		test(solution57::insert(i4, ni6));
		test(solution57::insert(i1, ni8));
		test(solution57::insert(i1, ni9));
		test(solution57::insert(i2, ni6));
		test(solution57::insert(i2, ni3));
	}
}

namespace solution59
{
	vector<vector<int>> generateMatrix(int n) {
		if (1 == n) return { {1} };
		vector<vector<int>> ret(n, vector<int>(n, 0));

		int stepi = 1, stepj = 1;
		int left = 0, right = n;
		int  top = 0, bottum = n;
		int count = 1;
		for (int r = 0, c = 0; r <= (bottum + 1) / 2 && c < (right + 1) / 2; ++r, ++c)
		{
			for (int i = c; i < right - c; i++) {
				ret[r][i] = count++;
			}
			//right
			for (int i = r + 1; i < bottum - r; i++) {
				ret[i][right - c - 1] = count++;
			}
			//bottom
			for (int i = right - c - 2; bottum - r - 1 > r && i >= c; i--) {
				ret[bottum - r - 1][i] = count++;
			}
			//left
			for (int i = bottum - r - 2; right - c - 1 > c && i > r; i--) {
				ret[i][c] = count++;
			}

		}
		return ret;

	}
}

namespace solution61
{

	struct ListNode {
		int val;
		ListNode* next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode* next) : val(x), next(next) {}
	};


	ListNode* rotateRight(ListNode* head, int k) {
		if (nullptr == head || nullptr == head->next || 0 == k) return head;

		vector<int> val;
		ListNode* current = head;
		while (nullptr != current)
		{
			val.emplace_back(current->val);
			current = current->next;
		}
		int realk = k;
		if (k > val.size())
		{
			realk = k % val.size();
		}
		realk = val.size() - realk;
		current = head;
		for (int index = realk; nullptr != current; ++index)
		{
			if (index == val.size())
			{
				index = 0;
			}
			current->val = val[index];
			current = current->next;
		}
		return head;
	}
}


namespace solution62
{
	int uniquePaths(int m, int n) {
		vector<vector<int>> ret(m, vector<int>(n, 0));
		int maxindex = max(m, n);
		for (int init = 0; init < maxindex; ++init)
		{
			if (init < m) ret[init][0] = 1;
			if (init < n) ret[0][init] = 1;
		}
		for (int indexm = 1; indexm < m; ++indexm)
		{
			for (int indexn = 1; indexn < n; ++indexn)
			{
				ret[indexm][indexn] = ret[indexm - 1][indexn] + ret[indexm][indexn - 1];
			}
		}
		return ret[m - 1][n - 1];
	}
	/// <summary>
	/// (max(n, m) -1 + 1 *... *(max(n, m) -1) + (min(n, m) -1)) / (min(n, m))!
	/// 
	int uniquePaths2(int m, int n) {
		long long ret = 1;
		int tempm = min(m, n);
		int tempn = max(m, n);
		for (int index = 1; index < tempm; ++index, ++tempn)
		{
			ret = ret * tempn / index;
		}
		return ret;
	}
}


namespace solution63
{
	//worst algorithm,
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		if (0 == obstacleGrid.size()) return 0;
		if (1 == obstacleGrid.size() && 1 == obstacleGrid[0].size()) return !obstacleGrid[0][0];
		if (1 == obstacleGrid[0][0]) return 0;
		int row = obstacleGrid.size();
		int col = obstacleGrid[0].size();

		vector<vector<unsigned int>> ret(row, vector<unsigned int>(col, 0));
		ret[0][0] = 1;

		for (int indexrow = 1; indexrow < row; ++indexrow)
		{
			if (obstacleGrid[indexrow][0]) break;
			ret[indexrow][0] = ret[indexrow - 1][0];
		}

		for (int indexcol = 1; indexcol < col; ++indexcol)
		{
			if (obstacleGrid[0][indexcol]) break;
			ret[0][indexcol] = ret[0][indexcol - 1];
		}
		for (int indexrow = 1; indexrow < row; ++indexrow)
		{
			for (int indexcol = 1; indexcol < col; ++indexcol)
			{
				if (obstacleGrid[indexrow][indexcol]) continue;
				ret[indexrow][indexcol] = ret[indexrow][indexcol - 1] + ret[indexrow - 1][indexcol];
			}
		}
		return ret[row - 1][col - 1];

	}

	//fast than 100% in leetcode.
	int uniquePathsWithObstacles_fast(vector<vector<int>>& obstacleGrid) {
		if (0 == obstacleGrid.size()) return 0;
		if (1 == obstacleGrid.size() && 1 == obstacleGrid[0].size()) return !obstacleGrid[0][0];
		if (1 == obstacleGrid[0][0]) return 0;
		int row = obstacleGrid.size();
		int col = obstacleGrid[0].size();

		vector<vector<unsigned int>> ret(row, vector<unsigned int>(col, 0));
		ret[0][0] = 1;
		int maxlen = std::max(row, col);
		for (int index = 1; index < maxlen; ++index)
		{
			if (index < row)
			{
				if (0 == obstacleGrid[index][0])
					ret[index][0] = ret[index - 1][0];
			}
			if (index < col)
			{
				if (0 == obstacleGrid[0][index])
					ret[0][index] = ret[0][index - 1];
			}
		}
		for (int indexrow = 1; indexrow < row; ++indexrow)
		{
			for (int indexcol = 1; indexcol < col; ++indexcol)
			{
				if (obstacleGrid[indexrow][indexcol]) continue;
				ret[indexrow][indexcol] = ret[indexrow][indexcol - 1] + ret[indexrow - 1][indexcol];
			}
		}
		return ret[row - 1][col - 1];

	}
	//better algorithm on storage. but not that fast
	int uniquePathsWithObstacles2(vector<vector<int>>& obstacleGrid) {
		if (0 == obstacleGrid.size()) return 0;
		if (1 == obstacleGrid.size() && 1 == obstacleGrid[0].size()) return !obstacleGrid[0][0];
		if (1 == obstacleGrid[0][0]) return 0;
		int row = obstacleGrid.size();
		int col = obstacleGrid[0].size();
		vector<int> ret(col);
		ret[0] = 1;
		for (int indexrow = 0; indexrow < row; ++indexrow)
		{
			for (int indexcol = 0; indexcol < col; ++indexcol)
			{
				if (obstacleGrid[indexrow][indexcol])
				{
					ret[indexcol] = 0;
					continue;
				}
				if (0 == indexcol) continue;
				if (1 == obstacleGrid[indexrow][indexcol]) continue;
				ret[indexcol] += ret[indexcol - 1];

			}
		}
		return ret.back();
	}
}

namespace solution64
{
	int minPathSum(vector<vector<int>>& grid) {
		int row = grid.size();
		int col = grid[0].size();
		if (0 == row || 0 == col) return 0;
		if (1 == row && 1 == col) return grid[0][0];
		int maxlenth = std::max(row, col);
		for (int index = 1; index < maxlenth; ++index)
		{
			if (index < col) grid[0][index] += grid[0][index - 1];
			if (index < row) grid[index][0] += grid[index - 1][0];
		}
		for (int indexrow = 1; indexrow < row; ++indexrow)
		{
			for (int indexcol = 1; indexcol < col; ++indexcol)
			{
				grid[indexrow][indexcol] += std::min(grid[indexrow - 1][indexcol], grid[indexrow][indexcol - 1]);
			}
		}
		return grid.back().back();
	}

	int minPathSum2(vector<vector<int>>& grid) {
		int row = grid.size();
		int col = grid[0].size();
		if (0 == row || 0 == col) return 0;
		if (1 == row && 1 == col) return grid[0][0];
		vector<int> ret(col, 0);
		ret[0] = grid[0][0];
		for (int index = 1; index < col; ++index)
		{
			ret[index] = ret[index - 1] + grid[0][index];
		}
		for (int indexrow = 1; indexrow < row; ++indexrow)
		{
			for (int indexcol = 0; indexcol < col; ++indexcol)
			{
				if (0 == indexcol)
				{
					ret[indexcol] += grid[indexrow][0];
					continue;
				}
				ret[indexcol] = grid[indexrow][indexcol] + std::min(ret[indexcol], ret[indexcol - 1]);
			}
		}
		return ret.back();
	}
}

namespace solution71
{
	string simplifyPath(string path) {
		stringstream ss(path);
		string result;
		string tempresult;
		vector<string> tempelem;
		while (std::getline(ss, tempresult, '/'))
		{
			tempelem.emplace_back(tempresult);
		}

		int ignor = 0;
		for (auto&& riter = tempelem.rbegin(); riter != tempelem.rend(); ++riter)
		{
			auto&& elem = *riter;
			if ("" == elem || "." == elem) continue;
			if (".." == elem)
			{
				ignor++;
				continue;
			}
			if (ignor > 0)
			{
				ignor--;
				continue;
			}
			result = "/" + elem + result;
		}
		return result.size() ? result : "/";
	}

	string simplifyPath2(string path) {
		stringstream ss(path);
		string result;
		string tempresult;
		vector<string> tempelem;
		while (std::getline(ss, tempresult, '/'))
		{
			if ("" == tempresult || "." == tempresult) continue;
			if (".." == tempresult && !tempelem.empty()) tempelem.pop_back();
			else if (".." != tempresult) tempelem.emplace_back(tempresult);
		}
		for (auto&& e : tempelem)
		{
			result += "/" + e;
		}
		return result.size() ? result : "/";
	}
}

namespace solution73
{
	void setpos(vector<vector<int>>& matrix, int x, int y, const int& row, const int& col)
	{

		int bound = max(row, col);
		for (int index = 0; index < bound; index++)
		{
			if (index < row)matrix[index][y] = 0;
			if (index < col)matrix[x][index] = 0;

		}
	}
	void setZeroes(vector<vector<int>>&& matrix) {
		int row = matrix.size();
		int col = matrix[0].size();
		if (1 == row && 1 == col) return;
		vector<pair<int, int>> key;
		for (int indexrow = 0; indexrow < row; indexrow++)
		{
			for (int indexcol = 0; indexcol < col; indexcol++)
			{
				if (0 == matrix[indexrow][indexcol]) key.emplace_back(make_pair(indexrow, indexcol));
			}
		}
		for (auto&& e : key)
		{
			setpos(matrix, e.first, e.second, row, col);
		}
		return;
	}
}

namespace solution74
{
	bool searchMatrix(vector<vector<int>>&& matrix, int target) {
		int row = matrix.size();
		int col = matrix[0].size();
		if (row == 1 && col == 1) return target == matrix[0][0];
		if (matrix[0][0] > target || target > matrix.back().back()) return false;
		int begin = 0, end = row;
		int index;

		while (begin != end)
		{
			index = (begin + end) / 2;
			if (target < matrix[index].back()) end = index;
			else if (target > matrix[index].back()) begin = index + 1;
			else return true;
		}
		//for()
		const vector<int>& des = matrix[begin];
		begin = 0; end = col;
		while (begin != end)
		{
			index = (begin + end) / 2;
			if (target < des[index]) end = index;
			else if (target > des[index]) begin = index + 1;
			else return true;
		}
		return false;

	}
}

namespace solution77
{
	void helper(vector<vector<int>>& ret, vector<int>& temp, int n, int k, int count, int pos)
	{
		if (count == k)
		{
			ret.emplace_back(temp);
			return;
		}

		if (pos > n) return;

		temp.emplace_back(pos);
		helper(ret, temp, n, k, count + 1, pos + 1);
		temp.pop_back();
		helper(ret, temp, n, k, count, pos + 1);
	}


	vector<vector<int>> combine(int n, int k) {
		if (1 == k && 1 == n) return { {1} };
		vector<vector<int>> ret;
		vector<int> temp;
		//here is a sample for naive optimize, the code run slower
		// 		if (n == k)
		// 		{
		// 			vector<int> temp;
		// 			
		// 			for (int index = 1; index <= n; ++index) temp.emplace_back(index);
		// 			ret.emplace_back(temp);
		// 			
		// 		}


		ret.reserve(2 * k);

		temp.reserve(k);

		helper(ret, temp, n, k, 0, 1);
		return ret;
	}
}

namespace solution78
{
	vector<vector<int>> subsets(vector<int>&& nums) {
		vector<vector<int>> ret;
		vector<int> temp;
		if (1 == nums.size())
		{
			ret.emplace_back(temp);
			ret.emplace_back(nums);
			return ret;
		}

		function<void(int, int)> helper;
		helper = [&temp, &ret, &nums, &helper](int cur, int length) ->void
		{
			if (cur == length)
			{
				ret.emplace_back(temp);
				return;
			}
			if (cur > length) return;
			temp.emplace_back(nums[cur]);
			helper(cur + 1, length);
			temp.pop_back();
			helper(cur + 1, length);

		};

		helper(0, nums.size());

		return ret;
	}
}

namespace solution80
{
	int removeDuplicates(vector<int>&& nums) {
		int pos = 0;
		int length = nums.size();
		int count = 0;
		int newlenth = 0;
		int last = nums[0];
		for (int index = 0; index < length; ++index)
		{

			if (nums[index] != last)
			{
				count = 1;
				last = nums[index];
			}
			else
			{

				if (++count > 2)
				{
					continue;
				}

			}
			nums[pos++] = nums[index];
			newlenth++;
		}
		//unnecessary
		auto iter = nums.begin();
		std::advance(iter, newlenth);
		nums.erase(iter, nums.end());
		//end of unnecessary
		return newlenth;
	}
}

namespace solution82
{
	struct ListNode {
		int val;
		ListNode* next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode* next) : val(x), next(next) {}

	};

	ListNode* deleteDuplicates(ListNode* head) {
		if (nullptr == head || nullptr == head->next) return head;

		ListNode* cur = head;
		ListNode* pos = head;
		ListNode* prev = NULL;
		ListNode* last = cur;
		bool isduplicate = false;
		while (cur)
		{
			if (last->val != cur->val)
			{

				last = cur;
				if (isduplicate) isduplicate = false;
				else
				{
					prev = pos;
					pos = (pos)->next;
				}

				(pos)->val = cur->val;

				cout << "exchange :" << (pos)->val << " " << cur->val << endl;

			}
			else
				if (cur != last)
					isduplicate = true;

			cur = cur->next;

		}
		if (isduplicate)
		{
			if (nullptr != prev) prev->next = nullptr;
			else head = nullptr;
		}
		if (nullptr != pos && nullptr != (pos)->next) (pos)->next = nullptr;
		return head;
	}
}

namespace solution86
{
	struct ListNode {
		int val;
		ListNode* next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode* next) : val(x), next(next) {}
	};

	ListNode* partition(ListNode* head, int x) {
		if (nullptr == head || nullptr == head->next) return head;
		ListNode* cur = head;
		ListNode* cur2 = head;
		vector<int> data;
		
		while (cur)
		{
			if (cur->val >= x) data.emplace_back(cur->val);
			else
			{
				cur2->val = cur->val;
				cur2 = cur2->next;
			}
			cur = cur->next;
		}
		for (auto& e : data)
		{
			if (cur2)
			{
				cur2->val = e;
				cur2 = cur2->next;
			}
			else
			{
				cout << "opps" << endl;
			}
		}
		return head;
	}

}

namespace solution90
{
	typedef vector<int> srctype;
	typedef vector<vector<int>> rettype;
	vector<vector<int>> subsetsWithDup(vector<int>& nums) {
		vector<vector<int>> ret;
		ret.reserve(nums.size() * 2);
		if (0 == nums.size())
		{
			//ret.emplace_back(vector<int>({}));
			ret = { {} };
		}
		else if (1 == nums.size())
		{
			ret = { {} , nums };
		}
		else
		{
			function<void(int, int)> helper;
			vector<int> temp;
			helper = [&helper, &ret, &nums, &temp](int pos, int length)
			{
				if (pos == length)
				{
					ret.emplace_back(temp);
					return;
				}
				if (pos > length) return;
				temp.emplace_back(nums[pos]);
				helper(pos + 1, length);
				temp.pop_back();
				int index = pos + 1;
				while (index < nums.size() && nums[pos] == nums[index]) index++;
				helper(index, length);

			};
			sort(nums.begin(), nums.end());
			helper(0, nums.size());

		}
		return ret;
	}
}


namespace solution91
{
	int numDecodings(string s) {
		auto checksingle = [](const char& ch)
		{
			return '0' == ch ? 0 : 1;
		};
		auto checkdouble = [](const char& ch1, const char& ch2)
		{
			return ('1' == ch1 || ('2' == ch1 && ch2 < '7')) ? 1 : 0;
		};

		if (0 == s.size()) return 0;
		if (1 == s.size()) return checksingle(s[0]);
		vector<int> result = vector<int>(s.size(), 0);
		result[0] = checksingle(s[0]);
		result[1] = checksingle(s[0]) * checksingle(s[1]) + checkdouble(s[0], s[1]);
		for (int index = 2; index < s.size(); ++index)
		{
			if (checksingle(s[index])) result[index] = result[index - 1];
			if (checkdouble(s[index - 1], s[index])) result[index] += result[index - 2];
		}
		return result.back();
	}
}

namespace solution93
{
	vector<string> restoreIpAddresses(string s) {
		vector<string> ret;
		string temp;
		int length = s.size();
		function<void(int, int, string)> restorehelp;
		restorehelp = [&s, &ret, &length, &restorehelp](int start, int partnum, string ip) ->void
		{
			if ((length - start) < (4 - partnum) || (length - start) > ((4 - partnum) * 3)) return;
			if (4 == partnum && start == length)
			{
				ip.erase(ip.end() - 1);
				ret.emplace_back(ip);
			}
			int num = 0;
			for (int index = start; (index < length) && (index < start + 3); ++index)
			{
				num = num * 10 + s[index] - '0';
				if (num < 256)
				{
					ip += s[index];
					restorehelp(index + 1, partnum + 1, ip + '.');

				}
				if (0 == num) break;

			}
		};
		restorehelp(0, 0, temp);


		return ret;
	}
}

namespace solution95
{


	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
	};


	vector<TreeNode*> generateTrees(int n) {
		if (1 == n)
		{
			return 	{ new TreeNode(n) };
		}
		function<vector<TreeNode*>(int, int)> helper;
		helper = [&helper, &n](int low, int high) ->vector<TreeNode*>
		{
			vector<TreeNode*> vret;

			if (low > high)
			{
				vret.emplace_back(nullptr);
			}
			if (low == high)
			{
				vret.emplace_back(new TreeNode(low));
				return vret;
			}
			for (int index = low; index <= high; ++index)
			{

				vector<TreeNode*> left = helper(low, index - 1);
				vector<TreeNode*> right = helper(index + 1, high);
				for (auto& e1 : left)
				{
					for (auto& e2 : right)
					{
						TreeNode* root = new TreeNode(index);
						root->left = e1;
						root->right = e2;
						vret.emplace_back(root);
					}
				}
			}
			return vret;
		};
		//root
		return helper(1, n);
	}
}


namespace solution96
{
	int numTrees(int n) {
		if (0 == n) return 0;
		if (1 == n) return 1;
		static vector<int> result = { 1, 1 };
		int size = result.size();
		if (size < n + 1)
		{
			result.resize(n + 1);
		}
		else
		{
			return result[n];
		}
		int sum = 0;
		for (int index = size; index <= n; ++index)
		{
			for (int temp = 0; temp < index; ++temp)
			{
				result[index] += result[temp] * result[index - temp - 1];
			}
		}
		return result[n];
	}
}

namespace solution97
{
	bool isInterleave(string s1, string s2, string s3) {
		if (s1.length() + s2.length() != s3.length()) return false;
		if (0 == s1.length() || 0 == s2.length())
		{
			if (0 == s1.length() && 0 == s2.length()) return true;
			else if (0 == s1.length())
			{
				return 0 == s2.compare(s3);
			}
			else if (0 == s2.length())
			{
				return 0 == s1.compare(s3);
			}
		}
		int sizes1 = s1.length();
		int sizes2 = s2.length();
		vector<vector<int>> result(sizes1 + 1, vector<int>(sizes2 + 1, 0));

		result[0][0] = 1;

		for (int indexi = 0; indexi <= sizes1; ++indexi)
		{
			for (int indexj = 0; indexj <= sizes2; ++indexj)
			{
				int pos = indexi + indexj - 1;
				if (indexi > 0 && s1[indexi - 1] == s3[pos])
				{
					result[indexi][indexj] = result[indexi - 1][indexj] || result[indexi][indexj];
				}
				if (indexj > 0 && s2[indexj - 1] == s3[pos])
				{
					result[indexi][indexj] = result[indexi][indexj] || result[indexi][indexj - 1];
				}
			}
		}
		testhelper::printVectorResult2d(std::forward<vector<vector<int>>>(result));
		return result.back().back();
	}
}

namespace solution98
{
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

	};
	bool isValidBST(TreeNode* root)
	{
		if (nullptr == root) return false;
		if (nullptr == root->left && nullptr == root->right) return true;
		function<void(TreeNode*)> helper;
		vector<int> v;
		helper = [&helper, &v](TreeNode* root) -> void
		{
			if (nullptr != root->left)
			{
				helper(root->left);
			}
			v.emplace_back(root->val);
			if (nullptr != root->right)
			{
				helper(root->right);
			}
		};
		helper(root);
		for (int i = 1; i < v.size(); ++i)
		{
			if (v[i] <= v[i - 1])
				return false;
		}
		return true;
	}
}

namespace solution99
{
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

	};
	void recoverTree(TreeNode* root)
	{
		TreeNode* wrong1 = nullptr;
		TreeNode* wrong2 = nullptr;
		TreeNode* prev = nullptr;
		function<void(TreeNode*)> helper;
		helper = [&](TreeNode* root)
		{
			if (root->left) helper(root->left);
			if (nullptr != prev && prev->val > root->val)
			{
				if (nullptr == wrong1) wrong1 = prev;
				/*if (nullptr == wrong2)*/ wrong2 = root;
			}
			prev = root;
			if (root->right) helper(root->right);

		};
		helper(root);
		swap(wrong1->val, wrong2->val);
	}
}

namespace solution105
{
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

	};
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
	{
		assert(preorder.size() == inorder.size());
		int index = 0;
		function<TreeNode* (int, int)> helper;
		helper = [&helper, &index, &preorder, &inorder](int left, int right) ->TreeNode*
		{
			if (left > right) return nullptr;
			TreeNode* root = new TreeNode(preorder[index++]);
			int pos = distance(inorder.begin(), find(inorder.begin(), inorder.end(), root->val));
			if (pos > 0) root->left = helper(left, pos - 1);
			if (pos < inorder.size() - 1) root->right = helper(pos + 1, right);
			return root;
		};
		return helper(0, inorder.size() - 1);
	}
}

namespace solution106
{
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

	};

	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
		assert(postorder.size() == inorder.size());
		int index = postorder.size() - 1;
		function<TreeNode* (int, int)> helper;
		helper = [&helper, &index, &postorder, &inorder](int left, int right) ->TreeNode*
		{
			if (left > right) return nullptr;
			TreeNode* root = new TreeNode(postorder[index--]);
			int pos = distance(inorder.begin(), find(inorder.begin(), inorder.end(), root->val));

			if (pos < inorder.size() - 1) root->right = helper(pos + 1, right);
			if (pos > 0) root->left = helper(left, pos - 1);
			return root;
		};
		return helper(0, inorder.size() - 1);
	}
}

namespace solution107
{
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

	};
	vector<vector<int>> levelOrderBottom(TreeNode* root) {
		if (nullptr == root) return { {} };
		if (nullptr == root->left && nullptr == root->right) return { {root->val} };
		vector<vector<int>> ret;
		vector<int> tempv;
		queue<TreeNode*> que;
		que.push(root);
		int step = que.size();
		while (step-- > 0)
		{
			auto temp = que.front();
			que.pop();
			tempv.emplace_back(temp->val);
			if (nullptr != temp)
			{
				if (nullptr != temp->left) que.push(temp->left);
				if (nullptr != temp->right) que.push(temp->right);
			}
			if (0 == step)
			{
				step = que.size();
				ret.emplace_back(tempv);
				tempv.clear();
			}
		}
		reverse(begin(ret), end(ret));
		return ret;
	}

}

namespace solution109
{
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

	};
	struct ListNode {
		int val;
		ListNode* next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode* next) : val(x), next(next) {}
	};
	TreeNode* sortedListToBST(ListNode* head)
	{
		if (nullptr == head) return nullptr;
		if (nullptr == head->next) return new TreeNode(head->val);
		function<TreeNode* (ListNode*, ListNode*)> helper;
		helper = [&helper](ListNode* begin, ListNode* end)-> TreeNode*
		{
			//if (nullptr == begin) return nullptr;
			auto root{ begin };
			for (auto fast{ begin }; fast != end and fast->next != end; fast = fast->next->next, root = root->next);
			return root != end ? new TreeNode(root->val, nullptr != begin ? helper(begin, root) : nullptr, nullptr != root->next ? helper(root->next, end) : nullptr) : nullptr;
		};

		return helper(head, nullptr);

	}
}

namespace solution113
{
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

	};

	vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
		if (nullptr == root) return{};

		if (nullptr == root->left and nullptr == root->right)
		{
			if (targetSum != root->val) return {};
			else return { {root->val} };
		}
		vector<vector<int>> ret;
		vector<int> temp;
		function<void(TreeNode*, int)> helper;
		helper = [&targetSum, &ret, &temp, &helper](TreeNode* pos, int sum)
		{

			temp.emplace_back(pos->val);
			if (nullptr == pos->left && nullptr == pos->right)
			{
				if (sum + pos->val == targetSum)
				{
					ret.emplace_back(temp);
					temp.pop_back();
					return;
				}
			}
			if (nullptr != pos->left) helper(pos->left, sum + pos->val);

			if (nullptr != pos->right) helper(pos->right, sum + pos->val);
			temp.pop_back();
		};
		helper(root, 0);
		return ret;
	}
}

/// try following code to test :
// testhelper::TestTreeAlgorithm<solution116::Node, vector<optional<int>>>([](solution116::Node* root)
// 	{
// 
// 		solution116::print(solution116::connect2(root));
// 	},
// 	vector<optional<int>>{1, 2, 3, 4, 5, 6, 7});
namespace solution116
{
	class Node {
	public:
		int val;
		Node* left;
		Node* right;
		Node* next;

		Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

		Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

		Node(int _val, Node* _left, Node* _right, Node* _next)
			: val(_val), left(_left), right(_right), next(_next) {}
	};
	Node* connect(Node* root) {
		if (nullptr == root) return root;
		if (nullptr == root->left && nullptr == root->right) return root;

		queue<Node*> que;
		que.push(root);
		while (!que.empty())
		{
			int size = que.size();
			for (auto index = 0; index != size - 1; ++index)
			{
				auto ptr = que.front();
				que.pop();

				ptr->next = que.front();

				if (nullptr != ptr->left) que.push(ptr->left);
				if (nullptr != ptr->right) que.push(ptr->right);
			}
			auto ptr = que.front();
			que.pop();
			if (nullptr != ptr->left) que.push(ptr->left);
			if (nullptr != ptr->right) que.push(ptr->right);
		}

		return root;
	}
	//Recursive solution
	Node* connect2(Node* root)
	{
		if (nullptr == root or (nullptr == root->left and nullptr == root->right))
			return root;
		Node* ptrl = root->left;
		Node* ptrr = root->right;
		while (nullptr != ptrl)
		{
			ptrl->next = ptrr;
			ptrl = ptrl->right;
			ptrr = ptrr->left;
		}
		if (nullptr != root->left) root->left = connect2(root->left);
		if (nullptr != root->right) root->right = connect2(root->right);
		return root;
	}


	void print(Node* root)
	{
		cout << "[";
		auto ptr = root;
		while (ptr)
		{
			auto tempp = ptr;
			while (tempp)
			{
				cout << tempp->val << ",";
				tempp = tempp->next;

			}
			ptr = ptr->left;
			cout << "#";
			if (nullptr != ptr)
				cout << ",";
		}
		cout << "]" << endl;
	}

}

/// try following code to test :
/// testhelper::TestTreeAlgorithm<solution117::Node, vector<optional<int>>>([](solution117::Node* root)
// {
// 
// 	solution117::print(solution117::connect2(root));
// },
// vector<optional<int>>{1, 2, 3, 4, 5, {}, 7
// });

namespace solution117
{

	Node* connect(Node* root)
	{

		Node* node = root;
		Node* levelHead = new Node(0);

		while (node) { 
		
			Node* needle = levelHead;

			while (node) {

				if (node->left) {
					needle->next = node->left;
					needle = needle->next;
				}
				if (node->right) {
					needle->next = node->right;
					needle = needle->next;
				}

				node = node->next; 
			}
		
			node = levelHead->next;
			levelHead->next = nullptr;
		}
		return root;

	}


	void print(Node* root)
	{
		cout << "[";
		auto ptr = root;
		while (ptr)
		{
			auto tempp = ptr;
			while (tempp)
			{
				cout << tempp->val << ",";
				tempp = tempp->next;

			}
			ptr = ptr->left;
			cout << "#";
			if (nullptr != ptr)
				cout << ",";
		}
		cout << "]" << endl;
	}

}

namespace solution120
{
	int minimumTotal(vector<vector<int>>& triangle) {
		if (0 == triangle.size()) return 0;
		if (1 == triangle.size()) return triangle.back().back();

		vector<int> ret(std::move(triangle.back()));

		for (int index = triangle.size() - 2; index >= 0; --index)
		{
			auto& temp = triangle[index];
			assert(temp.size() - 1 == index);
			for (int indexcol = 0; indexcol <= index; ++indexcol)
			{
				ret[indexcol] = min(ret[indexcol], ret[indexcol + 1]) + temp[indexcol];
			}
		}
		return ret[0];
	}
}


namespace solution128
{
	int longestConsecutive(vector<int>& nums) {
		int size = nums.size();
		if (size < 2) return size;
		unordered_set<int> set;
		for (auto& e : nums)
		{
			set.emplace(e);
		}
		int ret = 0;
		for (auto& e : set)
		{
			//			//try to use count, but run slow
			// 			if (set.count(e - 1)) continue;
			if (set.end() != set.find(e - 1)) continue;
			int consecutive = e;
			int len = 1;
			// 			while (set.count(++consecutive)) len++;
			while (set.end() != set.find(++consecutive)) len++;
			ret = max(len, ret);
		}
		return ret;
	}
	//this algorithm abit faster
	int longestConsecutive2(vector<int>& nums)
	{
		int size = nums.size();
		if (size < 2) return size;
		sort(nums.begin(), nums.end());
		auto bound = unique(nums.begin(), nums.end());
		int newsize = distance(nums.begin(), bound);
		int len = 1;
		int ret = 0;
		for (auto index = 0; index < newsize - 1; ++index)
		{
			if (nums[index] + 1 == nums[index + 1])
			{
				len++;
			}
			else if (nums[index] == nums[index + 1])
			{
				;
			}
			else
			{
				if (len > ret) ret = len;
				len = 1;
			}
		}
		if (len > ret) ret = len;
		return ret;
	}

}

namespace solution129
{
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

	};
	int sumNumbers(TreeNode* root)
	{
		if (nullptr == root) return 0;
		if (nullptr == root->left and nullptr == root->right) return root->val;
		function<int(TreeNode*, int)> helper;
		helper = [&helper](TreeNode* root, int sum) -> int
		{
			//if (nullptr == root) return sum;
			int total = 0;
			if (nullptr != root->left) total += helper(root->left, (sum + root->val) * 10);
			if (nullptr != root->right) total += helper(root->right, (sum + root->val) * 10);
			if (0 == total) total = sum + root->val;
			return total;
		};
		return helper(root, 0);
	}
}

namespace solution130
{
	void solve(vector<vector<char>>& board) {
		int rowsize = board.size();
		int colsize = board.back().size();
		if (1 > rowsize) return;
		if (1 >= colsize) return;
		constexpr char F = 'F';
		constexpr char X = 'X';
		constexpr char O = 'O';
		function<void(int, int)> helper;

		helper = [&board, &helper, rowsize, colsize, F, O](int temprow, int tempcol) ->void
		{
			if (temprow < 0 or temprow >= rowsize or tempcol < 0 or tempcol >= colsize) {
				return;
			}
			auto& c = board[temprow][tempcol];
			if (O == c)
			{
				c = F;
				helper(temprow - 1, tempcol);
				helper(temprow, tempcol - 1);
				helper(temprow + 1, tempcol);
				helper(temprow, tempcol + 1);
			}
		};

		for (int index = 0; index < rowsize; ++index)
		{
			if (O == board[index][0]) helper(index, 0);
			if (O == board[index][colsize - 1]) helper(index, colsize - 1);
		}

		for (int index = 1; index < colsize - 1; ++index)
		{
			if (O == board[0][index]) helper(0, index);
			if (O == board[rowsize - 1][index]) helper(rowsize - 1, index);
		}
		for (auto& e : board)
		{
			for (auto& c : e)
			{
				if (F == c) c = O;
				else if (O == c) c = X;
			}
		}
	}

	void test(vector<vector<char>>& board)
	{
		solve(std::forward<decltype(board)>(board));
		testhelper::printVectorResult2d(std::move(board));
	}
}


namespace solution125
{
	bool isPalindrome(string s) {
		function<bool(string&&)> Palindrome;
		Palindrome = [](const string&& s) ->bool
		{
			if (0 == s.length()) return true;
			if (1 == s.length()) return true;
			auto end = s.cbegin();
			advance(end, s.length() / 2);
			auto index = s.cbegin();
			auto reversebegin = s.crbegin();
			while (index <= end)
			{
				if (*index++ != *reversebegin++)
				{
					return false;
				}
			}
			return true;
		};
		function<string && (string&&)> eat;
		eat = [](string&& s)->string&&
		{
			int index = 0;
			int pos = 0;
			constexpr char endchar = '\0';
			while (endchar != s[index])
			{
				if (isalpha(s[index]))
				{
					s[pos++] = tolower(s[index]);
				}
				else if (isdigit(s[index]))
				{
					s[pos++] = s[index];
				}
				++index;
			}
			s = s.erase(pos, index - pos);
			return std::move(s);
		};
		return Palindrome(std::move(eat(std::move(s))));
	}
}

namespace solution131
{
	vector<vector<string>> partition(string s) {
		size_t length = s.length();
		if (1 == length) return{ {s} };
		vector<vector<string>> ret;
		vector<string> temp;

		function<void(int)> helper;
		function<bool(const string&&)> isPalindrome;
		isPalindrome = [](const string&& s) ->bool
		{
			if (1 == s.length()) return true;
			auto end = s.cbegin();
			advance(end, s.length() / 2);
			auto index = s.cbegin();
			auto reversebegin = s.crbegin();
			while (index <= end)
			{
				if (*index++ != *reversebegin++)
				{
					return false;
				}
			}
			return true;
		};

		function<bool(int, int)> isPalindrome2;
		isPalindrome2 = [&s](int l, int r) ->bool
		{
			while (l < r)
			{
				if (s[l++] != s[r--]) return false;
			}
			return true;
		};

		helper = [&helper, &isPalindrome2, &ret, &temp, &length, &s](int pos)
		{
			if (pos >= length)
			{
				ret.emplace_back(temp);
				return;
			}
			for (int index = 1; index <= length - pos; ++index)
			{

				if (0 == index) continue;
				//string temps = s.substr(pos, index);
				//if (isPalindrome(temps)
				if (isPalindrome2(pos, pos + index))
				{

					temp.emplace_back(s.substr(pos, index));
					helper(pos + index);
					temp.pop_back();
				}
			}
		};
		helper(0);
		return ret;
	}
}

namespace solution134
{

	constexpr int canottravel = -1;
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost)
	{
		//constexpr int canottravel = -1;
		int length = gas.size();
		assert(length == cost.size());
		int pos = 0;
		for (int index = 0; index < length; index += pos + 1)
		{
			int gassum = 0, costsum = 0;
			pos = 0;
			for (; pos < length; ++pos)
			{
				int realpos = (index + pos) % length;
				gassum += gas[realpos];
				costsum += cost[realpos];
				if (costsum > gassum)
				{
					break;
				}
			}
			if (pos == length) return index;
		}
		return canottravel;
	}


	int canCompleteCircuit2(vector<int>& gas, vector<int>& cost)
	{
		//constexpr int canottravel = -1;
		int length = gas.size();
		assert(length == cost.size());

		int curleftfuel = 0;
		int leftfuelfromstart = 0;
		int pos = 0;
		for (int index = 0; index < length; ++index)
		{
			curleftfuel += gas[index] - cost[index];
			if (curleftfuel < 0)
			{
				leftfuelfromstart += curleftfuel;
				curleftfuel = 0;
				pos = index + 1;
			}
		}
		return (curleftfuel + leftfuelfromstart >= 0) ? pos : canottravel;
	}
}


int main()
{
	/*
    std::cout << "Hello World!\n";
	std::vector<int> v = { -1, 0, 1, 2, -1, -4 };
	
	std::vector<int> vec1 = { 1, 2 };
	std::vector<int> vec2 = { 3, 4 };
	*/

	//auto res = findMedianSortedArrays(vec1, vec2);
//	std::vector<std::vector<char>> vec = { {'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'},{'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','b'} };
	
	
	ULONGLONG t1 = GetTickCount64();					//开始时间	

 	//std::vector<std::vector<char>> board = { 
// 		{'o', 'a', 'a', 'n'},
// 		{'e', 't', 'a', 'e'},
// 		{'i', 'h', 'k', 'r'}, 
// 		{'i', 'f', 'l', 'v'} 
		/*{'a'}*/
	/*	{{'b','a','b','a','b','a','b','a','b','a'},
		{'a','b','a','b','a','b','a','b','a','b'},
		{'b','a','b','a','b','a','b','a','b','a'},
		{'a','b','a','b','a','b','a','b','a','b'},
		{'b','a','b','a','b','a','b','a','b','a'},
		{'a','b','a','b','a','b','a','b','a','b'},
		{'b','a','b','a','b','a','b','a','b','a'},
		{'a','b','a','b','a','b','a','b','a','b'},
		{'b','a','b','a','b','a','b','a','b','a'},
		{'a','b','a','b','a','b','a','b','a','b'}}



 	};
 	*/
// 	std::vector<std::string> words = {"oath", "pea", "eat", "rain" };
/*	std::vector<std::string> words = { "a" };*/
/*	std::vector<std::string> words = {
			 "ababababaa", "ababababab", "ababababac", "ababababad", "ababababae", "ababababaf", "ababababag", "ababababah", 
			 "ababababai", "ababababaj", "ababababak", "ababababal", "ababababam", "ababababan", "ababababao", "ababababap",
			 "ababababaq", "ababababar", "ababababas", "ababababat", "ababababau", "ababababav", "ababababaw", "ababababax", 
			 "ababababay", "ababababaz", "ababababba", "ababababbb", "ababababbc", "ababababbd", "ababababbe", "ababababbf", 
			 "ababababbg", "ababababbh", "ababababbi", "ababababbj", "ababababbk", "ababababbl", "ababababbm", "ababababbn", 
			 "ababababbo", "ababababbp", "ababababbq", "ababababbr", "ababababbs", "ababababbt", "ababababbu", "ababababbv", 
			 "ababababbw", "ababababbx", "ababababby", "ababababbz", "ababababca", "ababababcb", "ababababcc", "ababababcd", 
			 "ababababce", "ababababcf", "ababababcg", "ababababch", "ababababci", "ababababcj", "ababababck", "ababababcl", 
			 "ababababcm", "ababababcn", "ababababco", "ababababcp", "ababababcq", "ababababcr", "ababababcs", "ababababct", 
			 "ababababcu", "ababababcv", "ababababcw", "ababababcx", "ababababcy", "ababababcz", "ababababda", "ababababdb", 
			 "ababababdc", "ababababdd", "ababababde", "ababababdf", "ababababdg", "ababababdh", "ababababdi", "ababababdj", 
			 "ababababdk", "ababababdl", "ababababdm", "ababababdn", "ababababdo", "ababababdp", "ababababdq", "ababababdr", 
			 "ababababds", "ababababdt", "ababababdu", "ababababdv", "ababababdw", "ababababdx", "ababababdy", "ababababdz", 
			 "ababababea", "ababababeb", "ababababec", "ababababed", "ababababee", "ababababef", "ababababeg", "ababababeh", 
			 "ababababei", "ababababej", "ababababek", "ababababel", "ababababem", "ababababen", "ababababeo", "ababababep", 
			 "ababababeq", "ababababer", "ababababes", "ababababet", "ababababeu", "ababababev", "ababababew", "ababababex", 
			 "ababababey", "ababababez", "ababababfa", "ababababfb", "ababababfc", "ababababfd", "ababababfe", "ababababff", 
			 "ababababfg", "ababababfh", "ababababfi", "ababababfj", "ababababfk", "ababababfl", "ababababfm", "ababababfn", 
			 "ababababfo", "ababababfp", "ababababfq", "ababababfr", "ababababfs", "ababababft", "ababababfu", "ababababfv", 
			 "ababababfw", "ababababfx", "ababababfy", "ababababfz", "ababababga", "ababababgb", "ababababgc", "ababababgd", 
			 "ababababge", "ababababgf", "ababababgg", "ababababgh", "ababababgi", "ababababgj", "ababababgk", "ababababgl", 
			 "ababababgm", "ababababgn", "ababababgo", "ababababgp", "ababababgq", "ababababgr", "ababababgs", "ababababgt",
			 "ababababgu", "ababababgv", "ababababgw", "ababababgx", "ababababgy", "ababababgz", "ababababha", "ababababhb", 
			 "ababababhc", "ababababhd", "ababababhe", "ababababhf", "ababababhg", "ababababhh", "ababababhi", "ababababhj", 
			 "ababababhk", "ababababhl", "ababababhm", "ababababhn", "ababababho", "ababababhp", "ababababhq", "ababababhr", 
			 "ababababhs", "ababababht", "ababababhu", "ababababhv", "ababababhw", "ababababhx", "ababababhy", "ababababhz", 
			 "ababababia", "ababababib", "ababababic", "ababababid", "ababababie", "ababababif", "ababababig", "ababababih",
			 "ababababii", "ababababij", "ababababik", "ababababil", "ababababim", "ababababin", "ababababio", "ababababip", 
			 "ababababiq", "ababababir", "ababababis", "ababababit", "ababababiu", "ababababiv", "ababababiw", "ababababix", 
			 "ababababiy", "ababababiz", "ababababja", "ababababjb", "ababababjc", "ababababjd", "ababababje", "ababababjf", 
			 "ababababjg", "ababababjh", "ababababji", "ababababjj", "ababababjk", "ababababjl", "ababababjm", "ababababjn",
			 "ababababjo", "ababababjp", "ababababjq", "ababababjr", "ababababjs", "ababababjt", "ababababju", "ababababjv", 
			 "ababababjw", "ababababjx", "ababababjy", "ababababjz", "ababababka", "ababababkb", "ababababkc", "ababababkd", 
			 "ababababke", "ababababkf", "ababababkg", "ababababkh", "ababababki", "ababababkj", "ababababkk", "ababababkl",
			 "ababababkm", "ababababkn", "ababababko", "ababababkp", "ababababkq", "ababababkr", "ababababks", "ababababkt",
			 "ababababku", "ababababkv", "ababababkw", "ababababkx", "ababababky", "ababababkz", "ababababla", "abababablb", 
			 "abababablc", "ababababld", "abababable", "abababablf", "abababablg", "abababablh", "ababababli", "abababablj", 
			 "abababablk", "ababababll", "abababablm", "ababababln", "abababablo", "abababablp", "abababablq", "abababablr", 
			 "ababababls", "abababablt", "abababablu", "abababablv", "abababablw", "abababablx", "abababably", "abababablz",
			 "ababababma", "ababababmb", "ababababmc", "ababababmd", "ababababme", "ababababmf", "ababababmg", "ababababmh", 
			 "ababababmi", "ababababmj", "ababababmk", "ababababml", "ababababmm", "ababababmn", "ababababmo", "ababababmp", 
			 "ababababmq", "ababababmr", "ababababms", "ababababmt", "ababababmu", "ababababmv", "ababababmw", "ababababmx", 
			 "ababababmy", "ababababmz", "ababababna", "ababababnb", "ababababnc", "ababababnd", "ababababne", "ababababnf", 
			 "ababababng", "ababababnh", "ababababni", "ababababnj", "ababababnk", "ababababnl", "ababababnm", "ababababnn", 
			 "ababababno", "ababababnp", "ababababnq", "ababababnr", "ababababns", "ababababnt", "ababababnu", "ababababnv", 
			 "ababababnw", "ababababnx", "ababababny", "ababababnz", "ababababoa", "ababababob", "ababababoc", "ababababod", 
			 "ababababoe", "ababababof", "ababababog", "ababababoh", "ababababoi", "ababababoj", "ababababok", "ababababol", 
			 "ababababom", "ababababon", "ababababoo", "ababababop", "ababababoq", "ababababor", "ababababos", "ababababot", 
			 "ababababou", "ababababov", "ababababow", "ababababox", "ababababoy", "ababababoz", "ababababpa", "ababababpb", 
			 "ababababpc", "ababababpd", "ababababpe", "ababababpf", "ababababpg", "ababababph", "ababababpi", "ababababpj", 
			 "ababababpk", "ababababpl", "ababababpm", "ababababpn", "ababababpo", "ababababpp", "ababababpq", "ababababpr", 
			 "ababababps", "ababababpt", "ababababpu", "ababababpv", "ababababpw", "ababababpx", "ababababpy", "ababababpz", 
			 "ababababqa", "ababababqb", "ababababqc", "ababababqd", "ababababqe", "ababababqf", "ababababqg", "ababababqh", 
			 "ababababqi", "ababababqj", "ababababqk", "ababababql", "ababababqm", "ababababqn", "ababababqo", "ababababqp", 
			 "ababababqq", "ababababqr", "ababababqs", "ababababqt", "ababababqu", "ababababqv", "ababababqw", "ababababqx", 
			 "ababababqy", "ababababqz", "ababababra", "ababababrb", "ababababrc", "ababababrd", "ababababre", "ababababrf",
			 "ababababrg", "ababababrh", "ababababri", "ababababrj", "ababababrk", "ababababrl", "ababababrm", "ababababrn", 
			 "ababababro", "ababababrp", "ababababrq", "ababababrr", "ababababrs", "ababababrt", "ababababru", "ababababrv", 
			 "ababababrw", "ababababrx", "ababababry", "ababababrz", "ababababsa", "ababababsb", "ababababsc", "ababababsd", 
			 "ababababse", "ababababsf", "ababababsg", "ababababsh", "ababababsi", "ababababsj", "ababababsk", "ababababsl",
			 "ababababsm", "ababababsn", "ababababso", "ababababsp", "ababababsq", "ababababsr", "ababababss", "ababababst", 
			 "ababababsu", "ababababsv", "ababababsw", "ababababsx", "ababababsy", "ababababsz", "ababababta", "ababababtb", 
			 "ababababtc", "ababababtd", "ababababte", "ababababtf", "ababababtg", "ababababth", "ababababti", "ababababtj",
			 "ababababtk", "ababababtl", "ababababtm", "ababababtn", "ababababto", "ababababtp", "ababababtq", "ababababtr",
			 "ababababts", "ababababtt", "ababababtu", "ababababtv", "ababababtw", "ababababtx", "ababababty", "ababababtz", 
			 "ababababua", "ababababub", "ababababuc", "ababababud", "ababababue", "ababababuf", "ababababug", "ababababuh", 
			 "ababababui", "ababababuj", "ababababuk", "ababababul", "ababababum", "ababababun", "ababababuo", "ababababup", 
			 "ababababuq", "ababababur", "ababababus", "ababababut", "ababababuu", "ababababuv", "ababababuw", "ababababux", 
			 "ababababuy", "ababababuz", "ababababva", "ababababvb", "ababababvc", "ababababvd", "ababababve", "ababababvf", 
			 "ababababvg", "ababababvh", "ababababvi", "ababababvj", "ababababvk", "ababababvl", "ababababvm", "ababababvn", 
			 "ababababvo", "ababababvp", "ababababvq", "ababababvr", "ababababvs", "ababababvt", "ababababvu", "ababababvv", 
			 "ababababvw", "ababababvx", "ababababvy", "ababababvz", "ababababwa", "ababababwb", "ababababwc", "ababababwd", 
			 "ababababwe", "ababababwf", "ababababwg", "ababababwh", "ababababwi", "ababababwj", "ababababwk", "ababababwl", 
			 "ababababwm", "ababababwn", "ababababwo", "ababababwp", "ababababwq", "ababababwr", "ababababws", "ababababwt", 
			 "ababababwu", "ababababwv", "ababababww", "ababababwx", "ababababwy", "ababababwz", "ababababxa", "ababababxb", 
			 "ababababxc", "ababababxd", "ababababxe", "ababababxf", "ababababxg", "ababababxh", "ababababxi", "ababababxj", 
			 "ababababxk", "ababababxl", "ababababxm", "ababababxn", "ababababxo", "ababababxp", "ababababxq", "ababababxr", 
			 "ababababxs", "ababababxt", "ababababxu", "ababababxv", "ababababxw", "ababababxx", "ababababxy", "ababababxz", 
			 "ababababya", "ababababyb", "ababababyc", "ababababyd", "ababababye", "ababababyf", "ababababyg", "ababababyh", 
			 "ababababyi", "ababababyj", "ababababyk", "ababababyl", "ababababym", "ababababyn", "ababababyo", "ababababyp", 
			 "ababababyq", "ababababyr", "ababababys", "ababababyt", "ababababyu", "ababababyv", "ababababyw", "ababababyx", 
			 "ababababyy", "ababababyz", "ababababza", "ababababzb", "ababababzc", "ababababzd", "ababababze", "ababababzf", 
			 "ababababzg", "ababababzh", "ababababzi", "ababababzj", "ababababzk", "ababababzl", "ababababzm", "ababababzn", 
			 "ababababzo", "ababababzp", "ababababzq", "ababababzr", "ababababzs", "ababababzt", "ababababzu", "ababababzv", 
			 "ababababzw", "ababababzx", "ababababzy", "ababababzz" };
			 */
	/*Output: ["eat", "oath"]*/
	//findWords(board, words);
	//findWords1(board, words);
// 	auto res = findWords(board, words);
// 	for (auto s : res)
// 	{
// 		cout << s << endl;
// 	}
// 
// 

// 	vector<int> vec = { 4,5,6,7,0,1,2 };
// 	search33(vec, 5);
// 
// 
// 
	//		 [1, 2, 3, 4, null, null, 5]

// 	 TreeNode* root = new TreeNode(1);
// 	 root->left = new TreeNode(2);
// 	 root->right = new TreeNode(3);
// 	 root->left->left = new TreeNode(4);
// 	 root->right->right = new TreeNode(5);
// 	 TreeNode* root2 = new TreeNode(3);
// 	 root2->left = new TreeNode(2);
// 	 root2->right = new TreeNode(3);
// 	 root2->right->left = new TreeNode(4);
// 	 root2->right->right = new TreeNode(5);
// 	 levelOrder2(root2);
// 
// 
// 
//test for solution43
// 	for (size_t i = 1; i < INT_MAX; ++i)
// 	{
// 		int a = rand(); 
// 		int b = a + 1000;
// 		stringstream s;
// 		s << a;
// 		string sa = s.str();
// 		s.str(string());
// 		s << b;
// 		string sb = s.str();
// 		cout << a << "*" << b << " = " << a * b<< " result use string " << multiply(sa, sb) << endl;
// 		if (0 == i % 100)
// 		{
// 			cout << "fuck" << endl;
// 		}
// 	}
	 //convert("PAYPALISHIRING", 5);
	 //isPalindrome(12321);
	//auto res = exist(vec, "baaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	
	// auto list = make_list({ 1, 2, 3, 4 });
// 			 //test for solution 24
// 	 ListNode24* a = new ListNode24(1);
// 	 a->next = new ListNode24(2);
// 	 ListNode24* p = a->next;
// 	 p->next = new ListNode24(3);
// 	 p = p->next;
// 	 p->next = new ListNode24(4);
// 	auto res = swapPairs(a);
			 //test for solution 273
// 	for (size_t i = 1; i < INT_MAX; i += 100)
// 	{
// 			 cout << i << numberToWords(i) << endl ;
// 		if (0 == (i % 1000))
// 		{
// 			cout << 1;
// 		}
// 	}
// 		auto res = solution17::letterCombinations("6541");
// 		for (auto& s : res)
// 		{
// 			cout << s << endl;
// 		}


		//test for solution 19 and 1721
// 			 solution1721::ListNode* a19 = new solution1721::ListNode(1);
//  		a19->next = new solution1721::ListNode(2);
// 		solution1721::ListNode* p19 = a19->next;
// 		p19->next = new solution1721::ListNode(3);
// 		p19 = p19->next;
// 		p19->next = new solution1721::ListNode(4);
// 		p19 = p19->next;
// 		p19->next = new solution1721::ListNode(5);
// 			 std::vector<int> v1721 = { 100, 24, 24, 36, 18, 52, 95, 61, 54, 88, 86, 79, 11, 1, 31, 26 };
// 		solution1721::ListNode* a19 = nullptr;
// 		for (auto& i : v1721)
// 		{
// 			solution1721::ListNode* p = nullptr;
// 			if (nullptr == a19)
// 			{
// 				a19 = new solution1721::ListNode(i);
// 				p = a19;
// 			}
// 			else
// 				p->next = new solution1721::ListNode(i);
// 				p = p->next;
// 		}
/*		solution1721::swapNodes(a19, 4);*/
// vector<int> x = { 1 };
// 	solution46::permute(x);
// vector<int> x = { 1, 3, 2 };
// solution31::nextPermutation(x);
// vector<string> test = /*{ "eat", "tea", "tan", "ate", "nat", "bat" };*/{ "bdddddddddd","bbbbbbbbbbc" };
// 	auto x = solution49::groupAnagrams(test);


// 
// vector<int> vec = { 1, 1, 1, 2, 2, 3 };
// solution374::topKFrequent(vec, 2);
//cout<<solution28::strStr("", "");
//cout << solution44::isMatch("aa", "a*");

//["a", "a", "b", "b", "c", "c", "c"]
// ["a"]
// ["a", "b", "b", "b", "b", "b", "b", "b", "b", "b", "b", "b", "b"]
// ["a", "a", "a", "b", "b", "a", "a"]
// 
// 	for (size_t index = 1; index <= 30; ++index)
// 	{
//		cout<<solution38::countAndSay(index)<<endl;
/*	}*/
// vector<vector<char>> vc = {
// 	{'a', 'a','a', 'a','a', 'a','a', 'a','a', 'a'},
// 	{'a'},
// 	{'a' , 'a'}, 
// 	{ 'a', 'b', 'c' },
// 	{'a', 'b', 'b', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c' }, 
// 	{'a', 'a', 'a', 'b', 'c','c','c','c'},
// {'a','a','b','b','c','c','c'},
// {'a'},
// {'a','b','b','b','b','b','b','b','b','b','b','b','b'},
// {'a','a','a','b','b','a','a'}
// };
// 	for(auto& s : vc) solution443::compress(s);
// solution138::Node* head = new solution138::Node(0);
// solution138::Node* next = head;
// vector<solution138::Node*> vp;
// vp.push_back(head);
// vector<int> vi = { 7, 13, 11, 10, 1 };
// vector<int> vii = { -1, 0, 4, 2, -1 };
// for (size_t index = 0; index < vi.size(); ++index)
// {
// 	next->next = new solution138::Node(vi[index]);
// 	vp.push_back(next);
// 	next = next->next;
// }
// next = head->next;
// for (size_t index = 0; index < vii.size(); ++index)
// {
// 	if (-1 != index)
// 	{
// 		next->random = vp[index + 1];
// 	}
// 	else next->random = nullptr;
// }
// 
// 



// for (size_t i = 1; i < 100; ++i)
// {
// 
// 	next->next = new solution138::Node(i);
// 	vp.push_back(next->next);
// 	//next->random = (std::rand()%10) ? vp[std::rand() % i] : nullptr;
// 	next = next->next;
// }
// for (auto p : vp)
// {
// 	p->random = vp[std::rand() % 101];
// }
//[[7, null], [13, 0], [11, 4], [10, 2], [1, null]]
//solution138::copyRandomList(head->next);
// next = head;
// while (next->next)
// {
// 	cout << next->val << "       " << next->random << endl;;
// 	next = next->next;
// }


//solution712::minimumDeleteSum("duck", "fucker");
 
//vector<int> vi = { 1, 0, 1, 1,1 };
//solution81::search(vi, 0);
// cout << solution402::removeKdigits("10",
// 	1) << endl;
// cout << solution402::removeKdigits("1432219",
// 	3) << endl;
// cout << solution402::removeKdigits("10200",
// 	1) << endl;
// cout << solution402::removeKdigits("10",
// 	2) << endl;
// cout << solution402::removeKdigits("10001",
// 	4) << endl;
// cout << solution402::removeKdigits("100",
// 	1) << endl;
// 
// vector<int> v1 = { 3, 9 };
// vector<int> v2 = { 8, 9 };
// vector<int> v3 = { 8, 6, 9 };
// vector<int> v4 = { 1, 7, 5 };
// vector<int> v5 = { 9, 1, 2, 5, 8, 3 };
// vector<int> v6 = { 3, 4, 6, 5 };
// vector<int> v7 = { 6, 6, 8 };
// vector<int> v8 = { 5, 0, 9 };
// vector<int> v9 = { 2, 5, 6, 4, 4, 0 };
// vector<int> v10 = { 7, 3, 8, 0, 6, 5, 7, 6, 2 };
// vector<int> v11 = { 6, 7 };
// vector<int> v12 = { 6 , 0, 4 };
// vector<int> v13 = { 5, 6, 8 };
// vector<int> v14 = { 6, 4, 0 };
// 
// vector<int> v15 = { 1, 6, 5, 4, 7, 3, 9, 5, 3, 7, 8, 4, 1, 1, 4 };
// vector<int> v16 = { 4, 3, 1, 3, 5, 9 };
// 
// 
// // 
// solution321::maxNumber(v1, v2, 3);
// solution321::maxNumber(v2, v1, 3);
// solution321::maxNumber(v3, v4, 3);
// solution321::maxNumber(v5, v6, 5);
// solution321::maxNumber(v7, v8, 3);
// solution321::maxNumber(v9, v10, 15);
// solution321::maxNumber(v11, v12, 5);
// solution321::maxNumber(v13, v14, 3);
// solution321::maxNumber(v15, v16, 21);

// vector<vector<int>> res = solution48::generateVector(5);
// solution48::fillVector(res);
// 
// solution48::printVector(res);
// solution48::print90degreeVector(res);
// cout << "============= " << endl;
// solution48::rotate(res);
// solution48::printVector(res);



 ULONGLONG t2 = GetTickCount64();



	cout << "程序执行时间：" << t2 - t1 << endl;
	
// 	auto res = threeSum(v);
// 	auto res2 = threeSum1(v);%
	int Test = 1; // for set breakpoint;
}