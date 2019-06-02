CRITICAL_SECTION crit;	//����ȭ ����(FALSE�� �����ؾ���.)
CRITICAL_SECTION Brick_CRT;
CRITICAL_SECTION Sound_CRT;
int ItemCount=0;

struct DropingItem{
	int x, y;
	HBITMAP *rand;
	struct DropingItem *next;	
	struct DropingItem *back;
};

// ���� ������ ����.
//struct DropingItem DropingItemGlobal; 

struct DropingItem *DropingItemHead = NULL;		//�����ʹϱ� NULL���� ������ ����.
									// NULL ���̶�, 0���� �ּҸ� ����Ű�� ������,
									// ��� ����Ű�� �����Ͱ� ���ٴ� ������ ����.
struct DropingItem *DropingItemTail=DropingItemHead;	// ó������ ������ ���� ����Ŵ.
//�����ͷ� ������ ��� DropingItemHead�� �ּҰ�. *DropingItemHead�� ������.

DropingItem* CreateItem(int x,int y,HBITMAP *rand){
	//����ȭ
	EnterCriticalSection(&crit);
	struct DropingItem Item;	// ����ü ����
	Item.x = x;
	Item.y = y;
	Item.rand=rand;
	Item.next = NULL;
	Item.back = NULL;
	if(DropingItemHead == NULL)		// Head�� �ʱⰪ(NULL) �� ���,
	{
		DropingItemHead=(DropingItem*)malloc(sizeof(DropingItem));
		*DropingItemHead = Item;
		DropingItemTail = DropingItemHead;
	}								// ������ �������� DropingItemHead�� 
									// ����Ű�� ���� ������.(�ּ����� ȣ��)
	//�� �� Tail�� Head�� ����
	else{
		Item.back=DropingItemTail;
		//next���ٰ� ������ ����.
		DropingItemTail->next = (DropingItem*)malloc(sizeof(DropingItem));
		DropingItemTail = DropingItemTail->next;	// Tail�� �� ��������
		*DropingItemTail = Item;	// �� ������ �ڷḦ ����
	}
	ItemCount++;
	LeaveCriticalSection(&crit);
	return DropingItemTail;
}

void DeleteItem(DropingItem *Item){	
	if(Item==NULL) return;
	//����ȭ, return�Ǹ� �� ���������Ƿ� ������
	EnterCriticalSection(&crit);
	if(Item->back==NULL){
		if(Item->next==NULL){	// ����
			DropingItemHead=NULL;
			DropingItemTail=NULL;	// �����͸� ������ν� �ڷᰡ ������ ǥ��
		}
		else{					// ����			
			DropingItemHead=Item->next;			
			DropingItemHead->back=NULL;	//��� ����
		}
	}
	else{
		if(Item->next==NULL){	// �ǳ�			
			DropingItemTail=Item->back;
			DropingItemTail->next=NULL;			
		}
		else{								// �߰�
			Item->back->next= Item->next;	//�Ϳ�!
			Item->next->back= Item->back;			
		}
	}	
	free(Item);	// �� �� ���� ����.
	LeaveCriticalSection(&crit);
}
