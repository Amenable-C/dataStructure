class chian; //forward ����
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
	int Delete(); // first�� ����Ű�� ��带 �����ϰ� data�� return
	bool Delete(int); // ���޵� element�� �����ϰ� true�� return, ������ false�� return
	void Insert(int); //���ο� ��带 ����� first ���� ��忡 �߰�
	void InsertSorted(int); //insert ����μ� sorted list�� �ǵ��� ������ �ǽ�
private:
	ChainNode* first;
};