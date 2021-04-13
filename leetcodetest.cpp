// leetcodetest.cpp : here is my personal data structure an algorithm training file
// Author: vihoc
// it contains all my ac code on leetcode. i'm not a specialist of algorithm, but somehow, some of them beat 100% in C++ solutions.
// i'm still study on it. 
// 
// how to use: if u interest at a question, just write code in the main function use solution<question number>::functionname, and pass the paramter.
// some debug case is remain in the main function. if u don't like it, just delete it.
//
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

#include <algorithm>


using namespace std;
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

//見鬼代碼
void checkTrie(std::vector<std::vector<char> >& board, Trie* tries,  int x, int y, std::vector<std::string>& ans)
{


	if (x < 0 || x > board[0].size() - 1)
		return;
	if (y < 0 || y > board.size() - 1)
		return;
	if (board[y][x] == '\0')
		return;

	auto* this_node = tries->next[board[y][x] - 'a'];
	if (!this_node)
		return;

	if (!this_node->word.empty()) {
		ans.emplace_back(std::move(this_node->word));
		this_node->word.clear();

		if (this_node->subtrees == 0) {
			Trie* to_delete = nullptr;
			std::swap(tries->next[board[y][x] - 'a'], to_delete);
			tries->subtrees--;
			delete to_delete;
			return;
		}
	}

	char temp = board[y][x];
	board[y][x] = '\0';

	checkTrie(board, this_node, x - 1, y, ans);
	checkTrie(board, this_node, x + 1, y, ans);
	checkTrie(board, this_node, x, y + 1, ans);
	checkTrie(board, this_node, x, y - 1, ans);

	board[y][x] = temp;

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
 ULONGLONG t2 = GetTickCount64();



	cout << "程序执行时间：" << t2 - t1 << endl;
	
// 	auto res = threeSum(v);
// 	auto res2 = threeSum1(v);%
	int Test = 1; // for set breakpoint;
}