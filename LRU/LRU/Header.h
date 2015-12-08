#include<string>
#include<iostream>
#include<unordered_map>
using namespace std;
class LRUCache{
private:
	struct cacheNode{
		int key;
		int value;
		cacheNode *next, *pre;
		cacheNode(int x, int y) :key(x), value(y), next(NULL), pre(NULL){}
	};
	int count;
	int capacity;
	cacheNode *head, *tail;
	unordered_map<int, cacheNode*> hash;
	void erase_tail()
	{
		int a = tail->key;
		hash.erase(a);
		if (tail == head)
		{
			tail = NULL;
			head = NULL;
		}
		else{
			cacheNode *pt = tail->pre;
			pt->next = NULL;
			tail = pt;
		}
	}
	void insert_head(int key, int value){
		cacheNode *tmp = new cacheNode(key, value);
		if (head == NULL)
		{
			head = tmp;
			tail = tmp;
		}
		else
		{
			head->pre = tmp;
			tmp->next = head;
			head = tmp;
		}
	}
	void move_head(cacheNode *node)
	{
		if (node->pre == NULL)
			return;
		//cacheNode *cur_pre=node->pre,*cur_next=node->next;
		node->pre->next = node->next;
		if (node->next != NULL)
			node->next->pre = node->pre;
		/*cur_pre->next=cur_next;
		if(cur_next!=NULL)
		cur_next->pre=cur_pre;*/
		node->pre = NULL;
		node->next = head;
		head = node;
	}
	//list<cacheNode> cacheList;
	//unordered_map<int,list<cacheNode>::iterator> hash;
public:
	LRUCache(int capacity) {
		count = 0;
		head = NULL;
		tail = NULL;
		this->capacity = capacity;
	}

	int get(int key) {
		if (hash.find(key) == hash.end())
			return -1;
		int result = hash[key]->value;
		move_head(hash[key]);
		hash[key] = head;
		return result;
		/*cacheList.splice(cacheList.begin(),cacheList,hash[key]);
		hash[key]=cacheList.begin();
		return cacheList.begin()->value;*/
	}

	void set(int key, int value) {
		if (hash.find(key) == hash.end())
		{
			if (count == capacity)
			{
				erase_tail();
				--count;
			}
			++count;
			insert_head(key, value);
		}
		else
		{
			hash[key]->value = value;
			move_head(hash[key]);
		}
		hash[key] = head;
		cout << " " << endl;
	}
};