#include "HashMap.hpp"
#include <iostream>
#include <string>
//#include "Node.hpp"

namespace //helper functions and defaults
{
	unsigned int initBucket=10;
	unsigned int initSize=0;
	
	
	
	//copy buckets
	// create alt copy that takes ref of new list, and copy of old list, just pounits new list to copy of of old, would this work? or is the copy just a copy of pointers, and the nodes stay as the original
	/*void bucketIdentitySteal(int theLength, int theSize, HashMap::Node** TheOld, HashMap::Node** theNew)
	{
		//keep each stage of old list and new lst in pointers, cant write infinite arrows for ever "next" in a each successive node
		for(int x=0; x<theLength;++x)
			{
				Node* elder = TheOld[x];
				Node* younger = theNew[x];
				if(elder!=nullptr)
				{
					younger=new Node;
					while(true)
					{
					younger->next= new Node;
					younger->value =elder->value;
					younger->key =elder->key;
					if(elder->next==nullptr)
						{
							younger->next= nullptr;
							break;
						}
					else
						{
							younger=younger->next;
							elder=elder->next;
						}
					}

				}
			}
	}*/
}
//here starts the real code 
HashMap::HashMap()
	:   bucketNumVariable{initBucket}, OuterArray{new Node*[bucketNumVariable]}, sizeVariable{initSize},  hasher{[](const std::string& x){return 0;} }
	{
		for(int i=0; i<bucketNumVariable;++i)
			{OuterArray[i]=nullptr;}

	}

HashMap::HashMap(HashFunction hasher)
	:   bucketNumVariable{initBucket} ,OuterArray{new Node*[bucketNumVariable]} ,  sizeVariable{initSize},hasher{hasher} 
	{
		for(int i=0; i<bucketNumVariable;++i)
			{OuterArray[i]=nullptr;}

	}
std::string HashMap::value(const std::string& key) const 
{
	std::string result;
	if(contains(key)!=true)
	{	
		return result;}
	else
	{
		int i;
 		 const int x = hasher(key) % bucketNumVariable;
 		i = x;
 		
 		
 			if(OuterArray[i]->key==key)
 				{
 					return OuterArray[i]->value;
 				}
 			else
 			{
 				Node* p = OuterArray[i]; 
 				while(true)
 				{
 					p=p->next;
 					if(p->key==key)
 						{
 							return p->value;
 							break;

 						}

 				}
 			}
 		


	}

}
	//return size
unsigned int HashMap::size() const
{
	return sizeVariable;
}



unsigned int HashMap::bucketCount() const
{
	return bucketNumVariable;
}

double HashMap::loadFactor() const
{
	double x  = sizeVariable/bucketNumVariable;
	return x; 
}




//copy
HashMap::HashMap(const HashMap& hm)
	:  bucketNumVariable{hm.bucketNumVariable}, OuterArray{new Node*[hm.bucketNumVariable]}, sizeVariable{hm.sizeVariable},  hasher{hm.hasher} 
	{

	for(int i=0; i<bucketNumVariable;++i)
			{OuterArray[i]=nullptr;}


		bucketIdentitySteal(bucketNumVariable,sizeVariable, hm.OuterArray, OuterArray);
	}

unsigned int HashMap::maxBucketSize() const
{
	unsigned int bucketDepth[bucketNumVariable]; 
for(int i=0; i<bucketNumVariable;++i)
	{
	unsigned int x = 0;
	if (OuterArray[i]!=nullptr)
		{

			Node* p = OuterArray[i]; 
			while(p!=nullptr)
			{
				x+=1;
				p= p->next;
			}
			bucketDepth[i]=x;

		}
	else
		{
			bucketDepth[i]=x;
		}
	}

unsigned int y=0;
for(int i=0; i<bucketNumVariable;++i)
{
	if (bucketDepth[i] > y)
		{
			y=bucketDepth[i];
		}
}
return y;

}

//death factor
HashMap::~HashMap()
{
	for(int i=0; i<bucketNumVariable;++i)
	{
		Node* p = OuterArray[i];
		if (p!=nullptr)
		{
			if(p->next==nullptr)
			{
				OuterArray[i]=nullptr;
			}
			else
			{
				while(true)
				{
					Node* x=p->next;
					if(x->next==nullptr)
					{
						delete x;
						delete p;
						break;
					}
					else
					{
						delete p;
						p=x;
					}
					//delete *p;
					//p=x;
				}
				OuterArray[i]=nullptr;
			}
		}

	}
	delete[] OuterArray; 
}

// = function 
HashMap& HashMap::operator=(const HashMap& hm)
{
	if(this!=&hm)
	{
		for(int i=0; i<bucketNumVariable;++i)
		{
			Node* p = OuterArray[i];
			if (p!=nullptr)
			{
				if(p->next==nullptr)
				{
					OuterArray[i]=nullptr;
				}
				else
				{
					while(true)
					{
						Node* x=p->next;
						if(x->next==nullptr)
						{
							delete x;
							delete p;
							break;
						}
						else
						{
							delete p;
							p=x;
						}
						//delete *p;
						//p=x;
					}
					OuterArray[i]=nullptr;
				}
			}

		}
		
		sizeVariable=hm.sizeVariable;
		bucketNumVariable=hm.bucketNumVariable;
		hasher = hm.hasher;
		delete[] OuterArray; 
		OuterArray =new Node*[hm.bucketNumVariable];
		for(int i=0; i<bucketNumVariable;++i)
			{OuterArray[i]=nullptr;}
		bucketIdentitySteal(bucketNumVariable,sizeVariable, hm.OuterArray, OuterArray);




	}
	return *this;
}
 
 bool HashMap::contains(const std::string& key) const
 {
 	int i;
 	const int x = hasher(key) % bucketNumVariable;
 	i = x;
 	if(OuterArray[i]==nullptr)
 	{return false;}
 	else
 	{
 		if(OuterArray[i]->key==key)
 			{return true;}
 		else
 		{
 			if(OuterArray[i]->next!=nullptr)
 			{
 				Node* p = OuterArray[i]->next;
 				while(true)
 				{
 					if(p->key==key)
 					{
 						return true;
 						break;

 					}
 					else
 					{
 						if(p->next!= nullptr)
 							{p=p->next;}
 						else
 						{
 							return false;
 							break;
 						}


 					}

 				}

 			}
 			else
 				{return false;}
 		}
 	} 
 }
 

 void HashMap::Nodetest(Node a)
 {}


    void HashMap::remove(const std::string& key)
    {
    	int y;
    	const int i = hasher(key) % bucketNumVariable;
    	y=i;
    	//std
    	//if(contains(key)!=true)
    	//{
    	//	pass; 
    	//}
    	// this doesnt work here, dont want to do anything if it doesnt work, c++ doesnt have pass?
    	if(contains(key)==true)
    	{
    		if(OuterArray[y]->key == key)
    		{
    			Node* p = OuterArray[y];
    			Node* nexxt = OuterArray[y]->next;
    			OuterArray[i] = nexxt;
    			//delete p->key;
    			//delete p->value;
    			//delete p->next;
    			delete p;
    			sizeVariable-=1;
    		}
    		else
    		{
    		Node* p = OuterArray[y];
    		Node* nexxt = (*p).next;
    			while(true)
    			{
    				
    				if(p->next->key==key)
    				{	Node* theNewNode = nexxt->next;
    					p= theNewNode;
    					//delete nexxt->key;
    					//delete nexxt ->value; 
    					//delete nexxt->next;
    					delete nexxt;
    					sizeVariable-=1;
    					// delete p
    					//nexxt=p
    					break;

    				} 
    				else
    				{
    					if(nexxt ==nullptr)
    					{
    						break;
    					}
    					else
    					{
    					p=nexxt;
    					nexxt=nexxt->next;
    					}
    				}
    			}
    		}
    	}

    	
    }
    void HashMap::bucketIdentitySteal(int theLength, int theSize, Node** TheOld, Node** theNew) const
    {
    	for(int x=0; x<theLength;++x)
    	{
    		if(theNew[x]==nullptr)
    		{
    			Node* p = TheOld[x];
				Node* nexxt = theNew[x];
    			if(TheOld[x]!=nullptr)
    			{
    				theNew[x]=new Node;
    				while(true)
    				{
    				nexxt->next= new Node;
					nexxt->value =p->value;
					nexxt->key =p->key;
					if(p->next==nullptr)
						{
							nexxt->next= nullptr;
							break;
						}
					else
						{
							nexxt=nexxt->next;
							p=p->next;
						}	
    				}

    			}
    			

    		}
    		else
    		{
    			Node* nexxt = theNew[x];
	    			while(true)
	    			{
	    				
	    				nexxt=nexxt->next;
	    				if(nexxt==nullptr)
	    				{
	    				Node* p = TheOld[x];

	    				if(TheOld[x]!=nullptr)
	    				{
	    				nexxt=new Node;
	    				while(true)
	    				{
	    				nexxt->next= new Node;
						nexxt->value =p->value;
						nexxt->key =p->key;
						if(p->next==nullptr)
							{
								nexxt->next= nullptr;
								break;
							}
						else
							{
								nexxt=nexxt->next;
								p=p->next;
							}	
	    				}
	    				break;

	    				}
	    			

	    				}
	    			}


    		}
    	}
    }
    /*{
    	for(int x=0; x<theLength;++x)
			{
				Node* elder = TheOld[x];
				Node* younger = theNew[x];
				if(elder!=nullptr)
				{
					younger=new Node;
					while(true)
					{
					younger->next= new Node;
					younger->value =elder->value;
					younger->key =elder->key;
					if(elder->next==nullptr)
						{
							younger->next= nullptr;
							break;
						}
					else
						{
							younger=younger->next;
							elder=elder->next;
						}
					}

				}
			}
    }*/

	void HashMap::add(const std::string& key, const std::string& value)
{
		int moreBucket= ((bucketNumVariable*2)+1);
		int moreSize =sizeVariable;
		if(contains(key)!=false)
		{
			int i;
	    	const int y = hasher(key) % bucketNumVariable;
	    	i=y;
	    	Node* p = OuterArray[i];
	    	if(p==nullptr)
	    		{
	    		p= new Node();
	    		p->key = key;
	    		p->value = value;
	    		p->next= nullptr;
	    		sizeVariable++;
	    		moreSize=sizeVariable;
	    		}
	    	else
	    	{p = p->next;
	    		while(true)
	    		{
	    			if(p==nullptr)
	    			{
	    				p=new Node();
	    				p->key = key;
	    				p->value = value;
	    				p->next = nullptr;
	    			}
	    			else
	    			{
	    				p = p->next;
	    			}
	    		}
	    	}
		}
		double x = (sizeVariable/bucketNumVariable);
		if(x > .8)
		{
			int newSize = sizeVariable;
			Node** newStuff= new Node*[moreBucket];
		

			for(int face=0; face<moreBucket;++face)
				{newStuff[face]=nullptr;}
			//yo lets rehash this shit
			for(int face=0; face<bucketNumVariable;++face)
			{

				Node* older= OuterArray[face];
				//Node* newer = newStuff[face];
				if(older!=nullptr)
				{
						int NewSpace= hasher(older->key) % moreBucket;
						if(newStuff[NewSpace]==nullptr)
						{
							newStuff[NewSpace]= new Node();
							newStuff[NewSpace]->key=older->key;
							newStuff[NewSpace]->value  = older->key;
							newStuff[NewSpace]->next=nullptr;
							if(older->next==nullptr)
							{
								
								delete older;
							}
							else
							{
								
								older=older->next;
								
								while(true)
								{
									NewSpace=hasher(older->key) % moreBucket;
									Node* newer=newStuff[NewSpace];
									if(newStuff[NewSpace]==nullptr)
									{
										newStuff[NewSpace]= new Node();
										newStuff[NewSpace]->key=older->key;
										newStuff[NewSpace]->value  = older->key;
										newStuff[NewSpace]->next=nullptr;
										if(older->next==nullptr)
											{delete older;
												break;
											}
										else
										{
											older=older->next;
										}

									}
									else
									{
										while(true)
										{
											if(newer->next==nullptr)
											{
												newer->next=new Node();
												newer=newer->next;
												break;
											} 
											else
											{
												newer=newer->next;
											}
										}

										newer->key=older->key;
										newer->value  = older->key;
										newer->next=nullptr;
										if(older->next==nullptr)
											{delete older;
												break;
											}
										else
										{
											older=older->next;
										}
									}

								}
							}

						}
						else
						{
							Node* newest = newStuff[NewSpace];
							newest=newest->next;
							while(true)
							{
								if(newest->next==nullptr)
								{
									newest->next = new Node();
									newest=newest->next;
									break;

									//fill in details of new node, see what do if the old has another next
								}
								else
								{
								newest=newest->next;
								}
							}
							newest->key=older->key;
							newest->value=older->value;
							newest->next=nullptr;
							if(older->next==nullptr)
							{
								delete older;
							}
							else
							{
								older=older->next;
								while(true)
								{
									if(older->next!=nullptr)
									{
										NewSpace= hasher(older->key) % moreBucket;
										newest=newStuff[NewSpace];
									while(true)
									{
										
										if(newest==nullptr)
										{
											newest->key=older->key;
											newest->value=older->value;
											newest->next=nullptr;
											if(older->next==nullptr)
											{
												delete older;
												break;

											}
											else
											{
												older=older->next;


											}
										}
										else
										{
											newest=newest->next;


										}
									}

									}
									else
									{
										delete older;
										break;
									}
								}
							}
						}
				}
				



			}
			delete[] OuterArray;
			OuterArray= newStuff;
			bucketNumVariable=moreBucket;
			sizeVariable=newSize; 


		}

}















