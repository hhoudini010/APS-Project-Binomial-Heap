#include <iostream>
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
		head = reverse_children(head->child) ;
		delete(temp) ;
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
		node *head1 = reverse_children(head->child) ;

		head = head->sibling ;
		head = Binomial_heap_union(head,head1) ;
		delete(temp) ;
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
	node *head1 = reverse_children(x->child) ;

	head = Binomial_heap_union(head,head1) ;
	delete(x) ;
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


int main(int argc, char const *argv[])
{
	node *head,*head1 ;

	// head = insert(head,10) ;
	// head = insert(head,20) ;
	// head = insert(head,30) ;

	// head = insert(head,40) ;
	// head = insert(head,50) ;
	// head = insert(head,60) ;
	// head = insert(head,70) ;
	// head = insert(head,80) ;
	// head = insert(head,90) ;
	// head = insert(head,100) ;
	// head = insert(head,110) ;
	// head = insert(head,120) ;
	// head = insert(head,130) ;

	// head = Binomial_heap_decrease_key(head,head,1234234) ;

//	printree(head) ;


	clock_t t;
	double t1 = 0,t2 = 0,t3 = 0,t4 = 0,t5 = 0;

	

		for(lli i = 0 ; i < 100000; i++)
		{	
		//cin>>value ;
		head = insert(head,i) ;
		head1 = insert(head1,10000000+i+1) ;



		//cout<<i<<"\n" ;
		}

 	t = clock() ;

 	head = Binomial_heap_union(head,head1) ;
 	t =clock() - t ;

 	cout<<"Merge "<<t<<"\n" ;

 	double time= (double) t ;
 	t1+=time ;

 	t = clock() ;
 	head = insert(head,10000000010101) ;
 	t = clock() - t ;

 	cout<<"Insert "<<t<<"\n" ;
	 time = (double) t ;
	 t2+=time ;


	t = clock() ;

	head = Binomial_heap_extract_min(head) ;
	t =clock() - t ;

	cout<<"Extract "<<t<<"\n" ;


	time = (double) t ;
	t3+=time ;


	t = clock() ;

	head = Binomial_heap_delete(head,head) ;
	t =clock() - t ;
	cout<<"Delete "<<t<<"\n" ;

	time = (double) t ;

	t4+=time ;



cout<<"Delete "<<t4<<"\n" ;

// cout<<endl<<endl<<endl ;

	return 0;
}






