#include <iostream>
#include <string>

using namespace std;

namespace topo {
	class Pair {
	public:
		int vertex, dur;
		Pair() {}
		Pair(int vertex, int dur) : vertex(vertex), dur(dur) {}
	};

	enum Boolean{FALSE, TRUE};
	template <class Type> class List;
	template <class Type> class ListIterator;

	template <class Type>
	class ListNode {
		friend class List<Type>;
		friend class ListIterator<Type>;
	private:
		Type data;
		ListNode* link;
		ListNode(Type);
	};
}