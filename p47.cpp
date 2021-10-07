class chian; //forward 선언
class ChainNode {
	friend class Chain;
private:
	int data;
	ChainNode* link;
};

class Chain {
public:
	//list operations
	Chain() {}
	int Delete(); // first가 가리키는 노드를 삭제하고 data를 return
	bool Delete(int); // 전달된 element를 삭제하고 true를 return, 없으면 false를 return
	void Insert(int); //새로운 노드를 만들고 first 다음 노드에 추가
	void InsertSorted(int); //insert 결과로서 sorted list가 되도록 구현한 실습
private:
	ChainNode* first;
};