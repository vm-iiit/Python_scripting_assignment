#include<iostream>
#include<cstdint>
#include<limits>
using namespace std;

typedef long long ll;
typedef struct AVL_node node;

node *_rotate(node *, string);
node *find_insuc(node *root, ll ele);
node *find_inpred(node *root, ll ele);

struct AVL_node{
	ll val;
	ll height;
	ll bal_fact;
	ll left_c;
	ll right_c;
	struct AVL_node* left = NULL;
	struct AVL_node* right = NULL;
};

node* newAVLnode(ll data)
{
	node* cnode = new struct AVL_node;
	cnode->val = data;
	cnode->height = 0;
	cnode->bal_fact = 0;
	cnode->left_c = 0;
	cnode->right_c = 0;
	return cnode;
}

void _inorder(node *root)
{
	if(root == NULL)
	{
		//cout<<"empty\n";
		return;
	}
	_inorder(root->left);
	cout<<root->val<<" with height "<<root->height<<" leftc and rightc "<<root->left_c<<' '<<root->right_c<<" bal fact :"<<root->bal_fact<<endl;
	_inorder(root->right);
}

node *_delete(node *root, ll ele)
{
	/*if(root)
		//cout<<"at node "<<root->val<<endl;
	else
		//cout<<"at null node\n";*/
	bool impf = false;
	node *temp = NULL;
	ll eval = root->val;
	if(root == NULL)
		return NULL;
	else if(root->val == ele)
	{
		if(root->left == NULL && root->right == NULL)
		{
			//cout<<"no children of "<<root->val<<endl;
			delete root;
			//cout<<"deleted\n";
			return  NULL;
		}
		else if(root->left == NULL && root->right != NULL)
		{
			//cout<<"one right children of "<<root->val<<endl;
			temp = root->right;
			delete root;
			//impf = true;
			root = temp;;
			return root;
		}
		else if(root->left != NULL && root->right == NULL)
		{
			//cout<<"one left children of "<<root->val<<endl;
			temp = root->left;
			//cout<<"deleting "<<root->val<<endl;
			delete root;
			//impf = true;
			root = temp;
			return root;
		}
		else
		{
			//cout<<"both child case\n";
			//cout<<"balancing factor is"<<root->bal_fact<<endl;
			if(root->bal_fact <= 0)
			{
				node *succ = find_insuc(root->right, root->val);
				//cout<<"inorder successor is "<<succ->val<<endl;
				root->val = succ->val;
				//cout<<"updated root's val to "<<root->val<<endl;
				root->right = _delete(root->right, succ->val);
				//return root;
			}
			else
			{
				node *pred = find_inpred(root->left, root->val);
				//cout<<"inorder predecessor is "<<pred->val;
				root->val = pred->val;
				//cout<<"updated root's val to "<<root->val<<endl;
				root->left = _delete(root->left, pred->val);
				//return root;
			}
		}

	}
	else if(root->val < ele)
	{
		//cout<<"moving right\n";
		root->right = _delete(root->right, ele);
	}
	else
	{
		//cout<<"moving left\n";
		root->left = _delete(root->left, ele);	
	}
	
	/*if(root)
		cout<<"updating "<<root->val<<"'s props\n";
	else
		cout<<"updating null's props\n";*/
	int lh, rh;
	lh = (root->left)?(root->left->height):-1;
	rh = (root->right)?(root->right->height):-1;
	root->height = 1 + max(lh, rh);
	root->bal_fact = lh-rh;
	//cout<<"balance factor :"<<lh-rh<<endl;
	int lc, rc;
	lc = (root->left)?(root->left->left_c + root->left->right_c + 1):0;
	rc = (root->right)?(root->right->left_c + root->right->right_c + 1):0;
	//cout<<"calculated count\n";
	root->left_c = lc;
	root->right_c = rc;
	//cout<<"updated count\n";
	/*if(root->right)
		cout<<"right's bal fact is "<<root->right->bal_fact<<endl;*/
	if(abs(lh-rh) > 1)
	{
		string path;
		if(root->bal_fact < 0 && root->right->bal_fact <= 0)
			path.append("RR");
		else if(root->bal_fact < 0 && root->right->bal_fact >= 0)
			path.append("RL");
		else if(root->bal_fact > 0 && root->left->bal_fact >= 0)
			path.append("LL");
		else
			path.append("LR");
		//cout<<"rotation type "<<path<<endl;
		root = _rotate(root, path);
	}
	//cout<<"returning from "<<eval<<"'s func call\n";
	/*if(impf)
		return temp;*/
	//cout<<"updated "<<root->val<<"'s props\n";
	return root;
}

node *_rotate(node *target, string rot_type)
{
	node *temp1, *temp2, *stemp2, *stemp3;
	ll count_sub, s2count, s3count;
	//cout<<"rotate case "<<rot_type<<endl;
	if(rot_type == "LL")
	{
		temp2 = target->left;
		temp1 = temp2->right;
		count_sub = (temp1 == NULL)?0:(temp1->left_c + temp1->right_c + 1);
		temp2->right = target;
		target->left = temp1;
		target->left_c = count_sub;
		temp2->right_c = target->left_c + target->right_c + 1;
		//cout<<"done\n";
	}
	else if(rot_type == "RR")
	{
		temp2 = target->right;
		temp1 = temp2->left;
		count_sub = (temp1 == NULL)?0:(temp1->left_c + temp1->right_c + 1);
		temp2->left = target;
		target->right = temp1;
		target->right_c = count_sub;
		temp2->left_c = target->left_c + target->right_c + 1;	
	}
	else if(rot_type == "LR")
	{
		temp1 = target->left;
		temp2 = temp1->right;
		stemp2 = temp2->left;
		stemp3 = temp2->right;
		s2count = (stemp2 == NULL)?0:(stemp2->left_c + stemp2->right_c + 1);
		s3count = (stemp3 == NULL)?0:(stemp3->left_c + stemp3->right_c + 1);
		temp1->right = stemp2;
		target->left = stemp3;
		temp2->left = temp1;
		temp2->right = target;
		target->left_c = s3count;
		temp1->right_c = s2count;
		temp2->left_c = temp1->left_c + temp1->right_c + 1;
		temp2->right_c = target->left_c + target->right_c + 1;
	}
	else
	{
		temp1 = target->right;
		temp2 = temp1->left;
		stemp2 = temp2->left;
		stemp3 = temp2->right;
		s2count = (stemp2 == NULL)?0:(stemp2->left_c + stemp2->right_c + 1);
		s3count = (stemp3 == NULL)?0:(stemp3->left_c + stemp3->right_c + 1);
		temp1->left = stemp3;
		target->right = stemp2;
		temp2->right = temp1;
		temp2->left = target;
		target->right_c = s2count;
		temp1->left_c = s3count;
		temp2->right_c = temp1->left_c + temp1->right_c + 1;
		temp2->left_c = target->left_c + target->right_c + 1;
	}

	ll lh, rh;
	if(temp1)
	{

		lh = (temp1->left)?(temp1->left->height):-1;
		rh = (temp1->right)?(temp1->right->height):-1;
		temp1->height = 1+ max(lh,rh);
		temp1->bal_fact = lh-rh;
	}

	lh = (target->left)?(target->left->height):-1;
	rh = (target->right)?(target->right->height):-1;
	target->height = 1+ max(lh,rh);
	target->bal_fact = lh-rh;

	lh = (temp2->left)?(temp2->left->height):-1;
	rh = (temp2->right)?(temp2->right->height):-1;
	temp2->height = 1+ max(lh,rh);
	temp2->bal_fact = lh-rh;

	return temp2;
}

node *_insert_AVL(node* rnode, node *nnode)
{
	//cout<<"got "<<rnode<<endl;
	//ll bfact;
	//char ch;
	ll x = nnode->val;
	if(rnode == NULL)
	{
		rnode = nnode;
		return nnode;
	}

	if(x < rnode->val)
	{
		//cout<<"moving left of "<<rnode->val<<endl;
		rnode->left_c += 1;
		rnode->left = _insert_AVL(rnode->left, nnode);
	}
	else if(x > rnode->val)
	{
		//cout<<"moving right of "<<rnode->val<<endl;
		rnode->right_c += 1;
		rnode->right = _insert_AVL(rnode->right, nnode);
	}
	else
	{
		return NULL;
	}
	int lh, rh;
	lh = (rnode->left)?(rnode->left->height):-1;
	rh = (rnode->right)?(rnode->right->height):-1;
	rnode->height = 1 + max(lh, rh);
	//cout<<"updated "<<rnode->val<<"'s height to "<<rnode->height<<endl;
	rnode->bal_fact = lh-rh;

	node *unbalanced = NULL;
	//node *unbalanced_par = NULL;

	if(abs(rnode->bal_fact) >1)
	{
		unbalanced = rnode;
	}
	if(unbalanced)
	{
		string path;
		//cout<<"balancing fact "<<unbalanced->bal_fact<<endl;
		//cout<<"rotn needed at "<<unbalanced->val<<endl;
		if(unbalanced->bal_fact < 0 && unbalanced->right->bal_fact < 0)
			path.append("RR");
		else if(unbalanced->bal_fact < 0 && unbalanced->right->bal_fact > 0)
			path.append("RL");
		else if(unbalanced->bal_fact > 0 && unbalanced->left->bal_fact > 0)
			path.append("LL");
		else
			path.append("LR");
		//cout<<"rotation type "<<path<<endl;
		return _rotate(unbalanced, path);
	}
	//cout<<"inserted node "<<nnode->val<<endl<<endl;
	return rnode;
}

ll _median_modified(node *ptr, int k, int size)
{
	ll nb = ptr->left_c, na = ptr->right_c;
	ll cnt_des = size-k;
	while(nb != cnt_des)
	{
		if(nb < cnt_des)
		{
			ptr = ptr->right;
			nb += 1 + ptr->left_c;
			na -= 1 + ptr->left_c;
		}
		else if(nb > cnt_des)
		{
			ptr = ptr->left;
			nb -= 1 + ptr->right_c;
			na += 1 + ptr->right_c;
		}
	}
	return ptr->val;
}

node *_find(node *ptr, ll x, ll diff)
{	
	//cout<<INT32_MAX<<endl;
	if(ptr == NULL)
		return NULL;
	if(diff == 0)
	{
		while(ptr && ptr->val != x)
		{
			if(ptr->val < x)
				ptr = ptr->right;
			else
				ptr=ptr->left;
		}
		return ptr;
	}
	else
	{
		node *found = ptr;
		ll ldiff, lval=INT32_MAX, gdiff=abs(x - ptr->val)+1;
		while(ptr)
		{
			if(ptr->val == x)
				return ptr;
			else
			{
				//cout<<"not equal\n";
				ldiff = abs(x - ptr->val);
				if(ldiff == gdiff)
				{
					//cout<<"diff equal\n";
					if(ptr->val < lval)
					{
						lval = ptr->val;
						found = ptr;
					}
				}
				else if(ldiff < gdiff)
				{
					//cout<<"less difference\n";
					gdiff = ldiff;
					lval = ptr->val;
					found = ptr;
				}
				if(ptr->val < x)
					ptr=ptr->right;
				else
					ptr=ptr->left;
			}
		}
		return found;
	}
}

node *find_insuc(node *root, ll ele)
{
	node *ptr=NULL;
	ll ldiff, gdiff = INT32_MAX;
	while(root)
	{
		if(root->val == ele)
			return root;
		else if(root->val < ele)
			root = root->right;
		else
		{
			ldiff = root->val - ele;
			if(ldiff < gdiff)
			{
				gdiff = ldiff;
				ptr = root;
			}
			root = root->left;
		}
	}
	return ptr;
}

node *find_inpred(node *root, ll ele)
{
	node *ptr=NULL;
	ll ldiff, gdiff = INT32_MAX;
	while(root)
	{
		if(root->val == ele)
			return root;
		else if(root->val > ele)
			root = root->left;
		else
		{
			ldiff = ele - root->val ;
			if(ldiff < gdiff)
			{
				gdiff = ldiff;
				ptr = root;
			}
			root = root->right;
		}
	}
	return ptr;
}

int nodes_b4(node *root, node *ptr)
{
	int nb4 = root->left_c;
	while(root->val != ptr->val)
	{
		if(ptr->val < root->val)
		{
			root = root->left;
			nb4 -= 1;
			nb4 -= root->right_c;
		}
		else
		{
			root = root->right;
			nb4 += 1;
			nb4 += root->left_c;
		}
	}
	return nb4;
}

int _range_q(ll lo, ll up, node *root)
{
	node *ptr = root;
	node *in_suc = NULL, *in_pred=NULL;
	in_suc = find_insuc(root, lo);
	in_pred = find_inpred(root, up);
	//cout<<"successor :"<<in_suc->val<<endl;
	//cout<<"predecessor :"<<in_pred->val<<endl;
	if(in_suc == NULL || in_pred == NULL)
		return 0;
	int nbl = nodes_b4(root, in_suc);
	int nbu = nodes_b4(root, in_pred);
	//cout<<"nodes before succ :"<<nbl<<endl;
	//cout<<"nodes before pred :"<<nbu<<endl;
	++nbu;
	return (nbu-nbl);
}

int main()
{
	//cout<<"main func\n";
	int n, lv;
	//cin>>n;
	node *root = NULL, *ptr, *ptr2;
	//ll arr[n];
	ll median_modi;
	int choice, size=0;
	ll ele;
	ll lower, upper;
	while(1)
	{
		cout<<endl<<endl;
		cout<<"1 - insert\n";
		cout<<"2 - delete\n";
		cout<<"3 - find exact element\n";
		cout<<"4 - find closest element\n";
		cout<<"5 - find kth largest element\n";
		cout<<"6 - range query\n";
		cout<<"7 - exit\n\n";
		cin>>choice;
		switch(choice){
			case 1: cin>>ele;
					ptr = _find(root, ele, 0);
					if(ptr == NULL)
					{
						ptr = newAVLnode(ele);
						ptr2 = _insert_AVL(root, ptr);
						root = ptr2;
						cout<<"element "<<ele<<" inserted\n";
						++size;
					}
					else
						cout<<"element already present\n";
					break;
					
			case 2: cin>>ele;
					ptr = _find(root, ele, 0);
					if(ptr != NULL)
					{
						cout<<"element "<<ele<<" deleted\n";
						--size;
						root = _delete(root, ele);
					}
					else
						cout<<"element not present in set or set empty\n";
					break;

			case 3: cin>>ele;
					ptr = _find(root, ele, 0);
					if(ptr == NULL)
						cout<<"element not present in set or set empty\n";
					else
						cout<<"set contains the element\n";
					break;

			case 4: cin>>ele;
					ptr = _find(root, ele, 1);
					if(ptr == NULL)
						cout<<"element not present in set or set empty\n";
					else
						cout<<"closest element is "<<ptr->val<<endl;
					break;

			case 5: cin>>ele;
					if(ele > size || ele <= 0 || size ==0)
					{
						cout<<"Invalid input or empty set\n";
						continue;
					}
					median_modi = _median_modified(root, ele, size);
					cout<<ele<<"'th largest element is "<<median_modi<<endl;
					break;

			case 6: cin>>lower>>upper;
					if(size == 0 || lower > upper)
					{
						cout<<"set is empty or invalid input\n";
						continue;
					}
					cout<<"no. of elements in range is :"<<_range_q(lower, upper, root)<<endl;
					break;
			case 7: exit(0);

			default:cout<<"Wrong i/p, try again\n";
		}
		cout<<endl<<"Tree description :\n";
		_inorder(root);
	}
}
