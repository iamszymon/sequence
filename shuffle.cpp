#include <iostream>	
using namespace std;	
template <typename Key, typename Info>

class Sequence
{
private:
	struct element {																																																				//
	Key id;	
	Info data;
	
	element* next;
	};
	element* head;
	void copyAllElements(const Sequence<Key, Info>& sourceSequence); 
	void eraseAllElements();

	//declarations		
	public:
	Sequence();																		//constructor
	Sequence(const Sequence<Key, Info>& sourceSequence); 							//copy constructor (copies the whole sequence)
	~Sequence();																	//destructor
	void addElementFront(const Key& nowKey, const Info& nowInfo); 					//adds new element to the front of the list
	bool addAfter(const Key& nowKey, const Info& nowInfo, const Key& afterId);  	 //adds new element after particular element
	void addElementBack(const Key& nowKey, const Info& nowInfo); 					//adds new element to the bottom of the lis
	bool findElement(const Info& information, const Key& identificator)const; 		//finds desired element
	bool isListEmpty();																//checks if the list is empty 
	void display(); 																//displays the desired sequence
	void copyElements(int howMany, int startPoint, const Sequence<Key, Info>& sourceSeq);//copies desired elements 
	bool eraseElement(const Key& erasedId, const Info& erasedInfo); 			//erases particular element
	void eraseElements() { eraseAllElements(); } 								//erases all elements from sequence 
	void changeInfo(const Info& prevInfo, const Info& nowInfo);				 //changes info
	void changeKey(const Info& prevKey, const Info& nowKey);					 //changes key
	Sequence<Key, Info>& operator=(const Sequence<Key, Info>& rightHS); //operator =
	Sequence<Key, Info> operator+(const Sequence<Key, Info>& rightHS) const; //operator +, returns new object, concatinated two given list
	int countElements() const; //counts number of elements in the list
};


///
template<typename Key, typename Info>
Sequence<Key, Info>::Sequence() 												//constructor
{
	head = NULL;
}

template<typename Key, typename Info>
Sequence<Key, Info>::~Sequence()												//destructor
{
	eraseAllElements();														//erases an object AFTER removing all nodes from the list
}

template<typename Key, typename Info> 											//copy constructor
Sequence<Key, Info>::Sequence(const Sequence<Key, Info>& sourceSequence)
{
	head = NULL;
	copyAllElements(sourceSequence);
}

template<typename Key, typename Info>											 //addFront
void Sequence<Key, Info>::addElementFront(const Key& nowKey, const Info & nowInfo)
{
	element* creator = new element;
	creator->data = nowInfo;
	creator->id = nowKey;
	creator->next = head;
	head = creator;
}

template<typename Key, typename Info>											//addBack
void Sequence<Key, Info>::addElementBack(const Key & nowKey, const Info & nowInfo)
{
	if (head==NULL)
	{
		addElementFront(nowKey, nowInfo);
	}
	else {
		element* temp = head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		element* creator = new element;
		creator->data = nowInfo;
		creator->id = nowKey;
		creator->next = NULL;
		temp->next = creator;
	}
}

template<typename Key, typename Info>														//addAfter
bool Sequence<Key, Info>::addAfter(const Key & nowKey, const Info & nowInfo, const Key& afterId)
{
	if (head!=NULL)
	{
		element* finder = head;
		while (finder!=NULL)
		{
			if (finder->id == afterId) //
			{
				element* creator = new element;
				creator->data = nowInfo;
				creator->id = nowKey;
				creator->next = finder->next;
				finder->next = creator;
				return true;
			}
			finder = finder->next;
		}
	}
	return false;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::isListEmpty() {														
		if (head ==NULL)															
			return true;
		else
			return false;
	}

template<typename Key, typename Info>
void Sequence<Key, Info>::display()																//PRINT
{
	if (head== NULL)
		cout << "No elements in the list\n";
	else {
		element* temp = head;
		while (temp!=NULL)
		{
			cout << "Info: " << temp->data << " ;" << "  Key: " << temp->id << endl;
			temp = temp->next;
		}

	}
}

template<typename Key, typename Info>
void Sequence<Key, Info>::changeKey(const Info & prevKey, const Info & nowKey)						//CHANGE KEY
{
	element* finder = head;
	if (head)
	{
		while (finder)
		{
			if (finder->id == prevKey)
				finder->id = nowKey;
			finder = finder->next;

		}
		return;
	}
	else
		return;
}

template<typename Key, typename Info>																//CHANGE INFO
void Sequence<Key, Info>::changeInfo(const Info & prevInfo, const Info & nowInfo)	
{
	element* finder = head;
	if (head)
	{
		while (finder)
		{
			if (finder-> data == prevInfo)
				finder-> data = nowInfo;
			finder = finder->next;

		}
		return;
	}
	else
		return;
}


template<typename Key, typename Info>																//COUNT NUMBER OF ELEMENTS
int Sequence<Key, Info>::countElements() const
{
	int numOfElems = 0;
	element* counter = head;
	while (counter)
	{
		counter = counter->next;
		numOfElems++;
	}
	return numOfElems;
}

template<typename Key, typename Info>
void Sequence<Key, Info>::copyElements(int howMany, int startPoint, const Sequence<Key, Info>& sourceSeq)
{ 
	if (sourceSeq.head == NULL)
	{
		return;
	}
	else
	{
		if (startPoint > sourceSeq.countElements())
		{
			return;
		}

		int position = 1;
		element* tempPos = sourceSeq.head;
		while (position < startPoint && tempPos != NULL)
		{
			tempPos = tempPos->next;
			position++;
		}

		for (int i = 1; i <= howMany; i++)  
		{
			if (tempPos!=NULL)  
			{
				addElementBack(tempPos->id, tempPos->data); 
				
				tempPos = tempPos->next; 
			}
			else
			{ 
				}
		}
	}
}

template<typename Key, typename Info>																	//COPY ALL ELEMENTS
void Sequence<Key, Info>::copyAllElements(const Sequence<Key, Info>& sourceSequence)
{
	eraseAllElements();
	element* temp = head;
	element* creator = sourceSequence.head;
	while (creator)
	{
		element* newElement = new element;
		newElement->data = creator->data;
		newElement->id = creator->id;
		newElement->next = head;
		head = newElement;

		creator = creator->next;
	}
	return;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::eraseElement(const Key & erasedId, const Info& erasedInfo)				//erase ELEMENTS
{
	if (findElement(erasedInfo, erasedId))
	{
		element* eraser = head;
		element* prev = NULL;
		if (head->data == erasedInfo && head->id == erasedId)
		{
			head = head->next;
			delete eraser;
			return true;
		}
		else
		{
			prev = eraser;
			eraser = eraser->next;
			while (eraser)
			{
				if (eraser->data== erasedInfo && eraser->id == erasedId)
				{
					prev->next= eraser->next;
					delete eraser;
					return true;
				}
				else
				{
					prev= eraser;
					eraser= eraser->next;
				}
			}
			return false;
		}

	}
	else
	{
		cout << "Element not found!" << endl;
		return false;
	}
}
template<typename Key, typename Info>
void Sequence<Key, Info>::eraseAllElements()
{																										//erase all elements
	element* eraser = head;
	while (eraser)
	{
		head = eraser->next;
		delete eraser;
		eraser = head;
	}
	return;
}
template<typename Key, typename Info>
Sequence<Key, Info> &Sequence<Key, Info>::operator=(const Sequence<Key, Info>& rightHS)			//OPERATOR =
{
	if (this == &rightHS)
		return *this;
	else {
		eraseAllElements();
		copyAllElements(rightHS);
		return *this;
	}
}

template<typename Key, typename Info>																	//OPERATOR +
Sequence<Key, Info> Sequence<Key, Info>::operator+(const Sequence<Key, Info>& rightHS) const
{
	Sequence<Key, Info> result;
	result.copyAllElements(*this);
	element* creator = rightHS.head;
	while (creator)
	{
		result.addElementBack(creator->id, creator->data);
		creator = creator->next;
	}
	return result;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::findElement(const Info & information, const Key & identificator) const		//FIND ELEMENT
{
	if (head)
	{
		element* finder = head;
		while (finder)
		{
			if (finder->data == information && finder->id == identificator)
				return true;
			finder = finder->next;
		}
	}
	return false;
}

template<typename Key, typename Info>
void shuffle(const Sequence<Key, Info>& aSeq, int start1, int len1, const Sequence<Key, Info>& bSeq, int start2, int len2, int repeat, Sequence<Key, Info>& result) //&result because it returns it to a new sequence
{
	for (int i = 0; i < repeat;i++)
	{
		result.copyElements(len1, start1+i*len1, aSeq);
		result.copyElements(len2, start2 + i*len2, bSeq);
	}
}

int main()
{
	
	Sequence<int, int> a1;
	Sequence<int, int> a2;
	a1.display();
	cout<<endl;
	a1.addElementFront(1, 100);
	a1.addElementFront(2, 200);
	a1.addElementBack(3, 300);
	a1.addAfter(6, 600, 2);
	a1.display();						
	cout<<endl;
	cout<<endl;
	a1.eraseElement(1,100);
	a1.display();						
	cout<<endl;
	cout << a1.isListEmpty();
	cout<<endl;
	a2.addElementBack(9,909);
	a2.addElementFront(10,109);
	Sequence<int, int> a3 = a2 + a1;
	a3.display();
	cout<<endl;
	Sequence<int, int> a4;
	shuffle(a1, 0, 1, a2, 1, 2, 3, a4);
	a4.display();
	cout<<endl;	
	a1.copyElements(2, 1, a2);
	a1.display();
	cout<<endl;
	a2.display();


}
