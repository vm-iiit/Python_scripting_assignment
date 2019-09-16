#include<iostream>
using namespace std;
#define order 5
typedef struct Btree node; 

struct Btree
{
	bool leaf = false;
	struct Btree *children[order+1] = NULL;
	int keys[order];
	int key_count = 1;
	bool ext_ele = false;
	int extra;
}

node *_search(node *root, int x)
{
	int lv=0;
	int kc = root->key_count;
	if(root == NULL)
		return NULL;
	while(lv < kc)
	{
		if(x == root->keys[lv])
			return root;
		else if(x < root-keys[lv])
			return _search(children[lv], x);
		else
			++lv;
	}
	if(lv == kc)
		return _search(children[lv], x);
}

node *_insert(node *root, int x)
{
	node *ptr;
	int lv;
	int temp;
	int kc, ind;
	if(root == NULL)
	{
		ptr = new node;
		ptr->keys[0] = x;
		ptr->leaf = true;
		return ptr;
	}
	else if(root->leaf == true && root->key_count < order)
	{
		lv=0;
		kc = root->key_count;
		while(root->keys[lv] < x && lv < order)
		{
			++lv;
			--kc;
		}
		ind = lv;
		//root->keys[lv] = x;
		while(kc)
		{
			temp = root->keys[lv+1];
			root->keys[lv+1] = root->keys[lv];
			--kc;
		}
		root->keys[ind] = x;
		root->key_count += 1;
		return root;
	}
	else if(root->leaf == true && root->key_count == order)
	{

	}
	else if(root->leaf == false)
	{
		ptr = _search(root, x);

	}
}
int main()
{
	int choice;
	int ele;
	node *root = NULL;
	while(1);
	{
		cout<<endl<<endl;
		cout<<"1 - insert in B-tree\n";
		cout<<"2 - search in B-tree\n";
		cout<<"3 - delete in B-tree\n";
		cin>>choice;
		switch(choice){

			case 1: cin>>ele;
					root = _insert(root, ele);
					break;

			case 2: cin>>ele;
					if(_search(root, ele) == NULL)
					{
						cout<<"not present\n";
					}
					else
						cout<<"present\n";
					break;

			case 3: cin>>ele;

					break;
		}

	}
}