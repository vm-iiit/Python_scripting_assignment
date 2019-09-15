#include<iostream>
using namespace std;

typedef float ll;
typedef struct AVL_node node;

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
	cout<<root->val<<" with height "<<root->height<<" and leftc and rightc "<<root->left_c<<' '<<root->right_c<<endl;
	_inorder(root->right);
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
	}

	lh = (target->left)?(target->left->height):-1;
	rh = (target->right)?(target->right->height):-1;
	target->height = 1+ max(lh,rh);

	lh = (temp2->left)?(temp2->left->height):-1;
	rh = (temp2->right)?(temp2->right->height):-1;
	temp2->height = 1+ max(lh,rh);

	return temp2;
}

node *_insert_AVL(node* rnode, node *nnode)
{
	//cout<<"got "<<rnode<<endl;
	ll x = nnode->val;
	//ll bfact;
	//char ch;
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
		if(rnode->right_c >= rnode->left_c)
		{
			rnode->left_c += 1;
			rnode->left = _insert_AVL(rnode->left, nnode);		
		}
		else
		{
			rnode->right_c += 1;
			rnode->right = _insert_AVL(rnode->right, nnode);		
		}
	}
	ll lh, rh;
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

ll _median(node *ptr, int size)
{
	ll nb = ptr->left_c, na = ptr->right_c;
	if(size == 1)
		return ptr->val;
	else if(size == 2)
	{
		ll x = (ptr->left == NULL)?(ptr->right->val):(ptr->left->val);
		return (x + ptr->val)/2;
	}
	else if(size%2)
	{
		ll cnt_des = size/2;
		while(nb != cnt_des && na != cnt_des)
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
	else
	{
		node *p1, *p2;
		p1 = ptr;
		p2 = ptr;
		ll cnt_des1 = size/2 - 1;
		ll cnt_des2 = size/2 ;
		//cout<<"first's desired counts "<<cnt_des1<<' '<<cnt_des2<<endl;
		//cout<<"num b4 "<<nb<<" num aft "<<na<<endl;
		while(nb != cnt_des1 && na != cnt_des2)
		{
			if(nb < cnt_des1)
			{
				p1 = p1->right;
				nb += 1 + p1->left_c;
				na -= 1 + p1->left_c;
			}
			else if(nb > cnt_des1)
			{
				p1 = p1->left;
				nb -= 1 + p1->right_c;
				na += 1 + p1->right_c;
			}
			//cout<<"num b4 "<<nb<<" num aft "<<na<<endl;
		}
		
		cnt_des1 = size/2 ;
		cnt_des2 = size/2 - 1;
		nb = ptr->left_c, na = ptr->right_c;
		//cout<<"second's desired counts "<<cnt_des1<<' '<<cnt_des2<<endl;
		//cout<<"num b4 "<<nb<<" num aft "<<na<<endl;
		while(nb != cnt_des1 && na != cnt_des2)
		{
			if(nb < cnt_des1)
			{
				p2 = p2->right;
				nb += 1 + p2->left_c;
				na -= 1 + p2->left_c;
			}
			else if(nb > cnt_des1)
			{
				p2 = p2->left;
				nb -= 1 + p2->right_c;
				na += 1 + p2->right_c;
			}
			//cout<<"num b4 "<<nb<<" num aft "<<na<<endl;
		}
		//cout<<"p1 "<<p1->val<<" p2 "<<p2->val<<endl;
		return (p1->val + p2->val)/2;
	}
}

int main()
{
	//cout<<"main func\n";
	int n, lv;
	cin>>n;
	node *root = NULL, *ptr;
	ll arr[n];
	ll median;
	for(lv=0;lv<n;lv++)
	{
		cin>>arr[lv];
		ptr = newAVLnode(arr[lv]);
		/*if(ptr == NULL)
			cout<<"node not created\n";
		cout<<"sending "<<root<<endl;*/
		//path[0] = '\0';
		//cout<<"inserting node "<<ptr->val<<endl;
		root = _insert_AVL(root, ptr);
		//cout<<"\n\n";
		//_inorder(root);
		//cout<<"\n\n";
		median = _median(root, lv+1);
		printf("%.1f\n", median);
	}
	//cout<<endl;
	
}
