#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
#define lli long long int

using namespace std ;



struct node
{
	lli key,degree,nno ;
	node *sibling,*child,*parent ;
} ;

vector<node *> vec ;
vector<pair<lli, node *> >inh[1000] ;

void Binomial_link(node *y, node *z)
{
	y->parent = z ;
	y->sibling = z->child ;
	z->child = y ;
	++(z->degree) ;	
}

node *new_node(lli data, lli nv)
{
	node *h = (node *) malloc(sizeof(node)) ;
	h->sibling = NULL ;
	h->nno = nv ;
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

	node *h = new_node(0,0) ;
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

node *insert(node *head, lli data, lli nn)
{
	node *head1 = new_node(data,nn) ;
	return Binomial_heap_union(head,head1) ;
}

void printree(node *head)
{
	node *temp = head ;

	while(temp)
	{
		cout<<temp->key<<" " ;
		inh[temp->nno].push_back(make_pair(1,temp)) ;
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
		vec.push_back(temp) ;
		//delete(temp) ;
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
		vec.push_back(temp) ;
		//delete(temp) ;
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
	vec.push_back(x);
	//delete(x) ;
	return head ;

}

void ihatethis(node *head)
{
	node *temp = head ;

	while(temp)
	{
		inh[temp->nno].begin()->second = temp ;
		ihatethis(temp->child) ;
		temp = temp->sibling ;
	}


}

node *Binomial_heap_decrease_key(node *head, node *nod, lli k)
{
	

	// cout<<"Gonna Decrease "<<nod->nno<<"'s "<<nod->key<<endl ;//For Debugging
	// cout<<"New val"<<k<<endl ;

	if(k >= nod->key)
		cout<<endl<<"Error : New key is greater than current key"<<endl ;
	else
	{
		nod->key = k ;
		node *y = nod ;
		node *z = nod->parent ;

		while(z && y->key < z->key)
		{
			int temp = y->key ;
			int temp1 = y->nno ;

			y->key = z->key ;
			y->nno = z->nno ;

			z->key = temp ;
			z->nno = temp1 ;

			y = z ;

			z = z->parent ;
		}	
	}

	ihatethis(head) ;
	
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

void addEdge(vector<pair<lli, lli> > adj[], lli e1, lli e2, lli w)
{
	adj[e1].push_back(make_pair(e2,w)) ;
	adj[e2].push_back(make_pair(e1,w)) ;
}

int main(int argc, char const *argv[])
{

	int v,n_edges ;
	lli e1,e2,w ;
	cout<<"\nEnter the number of vertices in the graph (atleast 2): " ;
	cin>>v ;

	node *head = NULL;

	vector<pair<lli, lli> > adj[v] ;
	

    cout<<"\nEnter the number of edges : " ;
    cin>>n_edges ;

    cout<<"\nEnter the edges (Vertices between 0 and "<< v-1<<" ) : "<<endl ;
    cout<<"\nEnter edge details as vertex-1 vertex-2 weight "<<endl ;
    for(int i = 0 ; i < n_edges; i++)
    {
    	cin>>e1>>e2>>w ;
    	if(e1 < 0 || e1 > v-1 || e2 < 0 || e2 > v-1)
    	{
    		cout<<"Invalid input."<<endl ; ;
    		i-- ;
    		continue ;
    	}
    	

    	addEdge(adj,e1,e2,w) ;
    }
  
	head = insert(head,0,0)  ;


	for(int i = 1 ; i < v; i++)
	{
		head = insert(head,INT_MAX,i) ;
	}

	cout<<"\nThe heap created initially with the given input : "<<endl ;
	printree(head) ;

	cout<<"\n" ;
	
	  while(head != NULL)
	  {
		head = Binomial_heap_extract_min(head) ;
		 node *temp = vec[0] ;

		  vec.clear() ;
		  


		 cout<<endl<<"Shortest distance to "<<temp->nno<<" frorm node 0 is :"<<" "<<temp->key<<endl ;
	     inh[temp->nno].begin()->first = 0 ;

	   
	 	   for(auto i : adj[temp->nno])
	 			if(inh[i.first].begin()->first == 1 && (temp->key + i.second) < (inh[i.first].begin()->second)->key )
	 				head = Binomial_heap_decrease_key(head,inh[i.first].begin()->second, temp->key + i.second) ;

	 		
	 	}

	 cout<<"\n" ;
	
	return 0;
}