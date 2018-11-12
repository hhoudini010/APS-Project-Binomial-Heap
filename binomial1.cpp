#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
#define lli long long int

using namespace std ;

struct node
{
	lli key,degree ;
	node *sibling,*child,*parent ;
} ;


void Binomial_link(node *y, node *z)
{
	y->parent = z ;
	y->sibling = z->child ;
	z->child = y ;
	++(z->degree) ;	
}

node *new_node(lli data)
{
	node *h = (node *) malloc(sizeof(node)) ;
	h->sibling = NULL ;
	h->parent = NULL ;
	h->child = NULL ;
	h->key = data ;
	h->degree = 0 ;

	return h ;
}

node *Binomial_merge(node *h1, node *h2)
{
	if(h1 == NULL)
		return h2 ;
	if(h2 == NULL)
		return h1 ;

	node *h = new_node(0) ;
	node *temp = h ;

	while(h1 && h2)
	{
		if(h1->degree > h2->degree)
		{
			temp->sibling = h2 ;
			h2 = h2->sibling ;
		}
		else 
		{
			temp->sibling = h1 ;
			h1 = h1->sibling ;
		}

		temp = temp->sibling ;
	}
	if(h1)
	{
		temp->sibling = h1 ;
	}
	if(h2)
		temp->sibling = h2 ;

	temp = h ;
	h = h->sibling ;
	free(temp) ;
	return h ;
}

node *Binomial_heap_union(node *h1, node *h2)
{
	node *h = Binomial_merge(h1,h2) ;

	if(h == NULL)
		return h ;

	node *curr = h ;
	node *prev = NULL ;
	node *next = curr->sibling ;

	while(next)
	{
		if((curr->degree != next->degree) || (next->sibling != NULL && (next->sibling)->degree == curr->degree) )
		{
			prev = curr ;
			curr = next ;
		}

		else if(curr->key < next->key)
		{
			curr->sibling = next->sibling ;
			Binomial_link(next,curr) ;
		}
		else 
		{
			if(prev)
			{
				prev->sibling = curr->sibling ;
				Binomial_link(curr,next) ;
				curr = prev->sibling ;
			}
			else
			{
				h = curr->sibling ;
				Binomial_link(curr,next) ;
				curr = next ;
			}

		}
		
		next = curr->sibling ;

	}

	return h ;
}

node *insert(node *head, lli data)
{
	node *head1 = new_node(data) ;
	return Binomial_heap_union(head,head1) ;
}

void printree(node *head)
{
	node *temp = head ;

	while(temp)
	{
		cout<<temp->key<<" " ;
		printree(temp->child) ;
		temp = temp->sibling ;
	}

}

node *reverse_children(node *nod)
{
	
	if(nod == NULL)
		return NULL ;
	
	node *curr = nod ;
	node *prev = NULL, *next = NULL ;

	while(curr)
	{
		curr->parent = NULL ;
		next = curr->sibling ;
		curr->sibling = prev ;
		prev = curr ;
		curr = next ;
	}


	return prev ;

}

node *Binomial_heap_extract_min( node *head)
{
	node *temp = head ;


	if(temp == NULL)
		return head ;

	else if(head->sibling == NULL)
	{
		node *temp = head ;
		cout<<"The minimum element extracted is : "<<temp->key<<endl ;
		head = reverse_children(head->child) ;
	//	delete(temp) ;
		return head ;
	}

	lli min_value = temp->key ;
	temp = temp->sibling ;

	while(temp)
	{
		if(temp->key < min_value){
			min_value = temp->key ;
		}

		temp = temp->sibling ;
	}

	if(head->key == min_value)
	{
		node *temp = head ;
		cout<<"The minimum element extracted is : "<<temp->key<<endl ;

		node *head1 = reverse_children(head->child) ;

		head = head->sibling ;
		head = Binomial_heap_union(head,head1) ;
	//	delete(temp) ;
		return head;
	}

	node *prev_x = NULL ;
	node *x = head ;
	node *next_x = x->sibling ;

	

	while(x->key != min_value)
	{
		prev_x = x ;
		x = next_x ;
		next_x = x->sibling ;
	}



	prev_x->sibling = next_x ;
	cout<<"The minimum element extracted is : "<<x->key<<endl ;
	node *head1 = reverse_children(x->child) ;

	head = Binomial_heap_union(head,head1) ;
	
	//delete(x) ;
	return head ;

}

node *Binomial_heap_decrease_key(node *head, node *nod, lli k)
{
	if(k > nod->key)
		cout<<endl<<"Error : New key is greater than current key"<<endl ;
	else
	{
		nod->key = k ;
		node *y = nod ;
		node *z = nod->parent ;

		while(z && y->key < z->key)
		{
			int temp = y->key ;
			y->key = z->key ;
			z->key = temp ;

			y = z ;

			z = z->parent ;
		}	
	}

	return head ;
}


node *Binomial_heap_delete(node *head,node *nod)
{
	if(nod == NULL)
		return head ;
	head = Binomial_heap_decrease_key(head,nod,INT_MIN) ;
	head = Binomial_heap_extract_min(head) ;

	return head ;
}

node *Insert(node *head)
{
	int n_nodes ;
	cout<<"\nEnter the number of nodes to be inserted : ";
	cin>>n_nodes ;

	lli val ;

	for(int i = 0; i < n_nodes; i++){
	cout<<"\nEnter the value to be inserted : ";
	cin>>val ;

	head = insert(head,val) ;
	cout<<"Insert successful."<<endl ;
}

	return head ;
}

node *search(node *head, lli val)
{
	node *temp = head ;

	while(temp)
	{
		if(temp->key == val)
			return temp ;
		node * tp = search(temp->child,val) ;
		if(tp)
			return tp ;
		temp = temp->sibling ;
	}

	return NULL ;
}

node *del(node *head)
{
	lli val ;
	cout<<"Enter the value to be deleted : "<<endl ;
	cin>>val ;

	node *res = search(head,val) ;

	if(res == NULL)
		cout<<"No such node in heap."<<endl ;
	else
	{
		head = Binomial_heap_delete(head,res) ;
		cout<<"Node deleted successfuly"<<endl ;
	}

	return head ;

}

node *Extra(node *head)
{
	head = Binomial_heap_extract_min(head) ;
	return head ;
}

node *Mer(node *head)
{
	node *head1 = NULL ;

	cout<<"\nEnter the heap contents of the heap which is to be merged with the main heap."<<endl ;
	head1 = Insert(head1) ;

	cout<<"\nThe inserted heap is "<<endl ;
	printree(head1) ;

	cout<<"\nMerging the two heaps."<<endl ;
	head = Binomial_heap_union(head,head1) ;

	cout<<"\nThe merged heap is : "<<endl ;
	printree(head) ;
	cout<<"\n" ;

	return head ;

}


node *Dec(node *head)
{
	lli val ;
	cout<<"\nEnter the key of node whose key is to be decreased : " ;
	cin>>val ;

	node *res = search(head,val) ;
	if(res == NULL)
		cout<<"\nNo such node is present in the heap."<<endl ;
	else 
	{
		lli n_key ;

		cout<<"\nEnter the new key for that node : " ;
		cin>>n_key ;
		head = Binomial_heap_decrease_key(head,res,n_key) ;
	}

	return head ;
}


int main(int argc, char const *argv[])
{
	node *head = NULL ;

	int n ;

	do{
		cout<<"\n1.Insert\n2.Delete\n3.Extract minimum\n4.Merge\n5.Decrease key\n6.Print heap\n7.Exit"<<endl ;
		cin>> n ;

		switch(n)
		{
			case 1 : head = Insert(head) ;
					 break ;
			case 2 : head = del(head) ;
					 break ;
			case 3 : head = Extra(head) ;
					 break ;
			case 4 : head = Mer(head) ;
					 break ;
			case 5 : head = Dec(head) ;
					 break ;
			case 6 :cout<<"\nThe heap is :\n" ; 
					printree(head) ;
					cout<<"\n" ;
			case 7 : break ;

			default : cout<<"\nInvalid input."<<endl ;
		}
	  }while(n!= 7) ;



	return 0;
}






