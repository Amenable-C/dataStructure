//// ChainNode = 데이터랑 링크
//// Chain = *first
//// 여기서 기본은 ChainNode를 포인터로 만들고, 그것을 이용하여 삭제 추가
//// 추가할 때, element를 참조변수로 받고, 그것을 new ChainNode<T>(element) 이렇게 하는거
//
//// Iterator = list와 current
//// Iterator를 맨처음 정의할 때, 어떤 list인지 확인하고, current를 list의 first로 받음
//
//// Circular lists = 마지막 노드가 첫번째 노드를 가르키는 linked list
//// 
//// 
//
//
//class ChainNode {
//private:
//	int data;
//	ChainNode* link;
//};


// iterator를 쓰지 않으면, ChainNode를 포인터로 만들고 그것이 first를 가르키게 해서 그걸로 풀기????