

class chain; //forward ����
class ChainNode {
	friend class Chain;
private:
	int data;
	ChainNode* link;
};

