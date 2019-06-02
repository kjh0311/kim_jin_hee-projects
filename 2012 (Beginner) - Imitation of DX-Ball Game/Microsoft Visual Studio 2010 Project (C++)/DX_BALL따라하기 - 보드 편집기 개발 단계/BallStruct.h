CRITICAL_SECTION Ball_CRT;
int BallCount=0;

struct BallStruct{
	float x, y, dx, dy;
	BOOL Grabbed;
	struct BallStruct *next, *back;
};

struct BallStruct *FirstBall = NULL; // ���� ����
struct BallStruct *LastBall = FirstBall; // �߰��� ���� �ʿ�

BallStruct* CreateBall(float x,float y,float dx, float dy){		
	EnterCriticalSection(&Ball_CRT);
	struct BallStruct NewBall;
	NewBall.x=x;
	NewBall.y=y;
	NewBall.dx=dx;
	NewBall.dy=dy;
	NewBall.Grabbed=FALSE;
	NewBall.next=NULL;
	NewBall.back=NULL;	//�ʱⰪ�� �ݵ�� �־����	
	BallCount++;
	if(FirstBall == NULL)
	{// �� �޸� �Ҵ�
		FirstBall=(BallStruct*)malloc(sizeof(BallStruct));
		*FirstBall = NewBall;	// ���� ���� �̻����� �Ҵ�� �޸� �������� ����
		LastBall = FirstBall;	// Tail�� Head�� ������ ��ġ�� ������Ʈ
	}
	else{//��尡 �ƴ� ���
		// ���ο� ������ �Ҵ��Ͽ� Tail->Next�� ����
		
		NewBall.back = LastBall;
		LastBall->next = (BallStruct*)malloc(sizeof(BallStruct));
		LastBall = LastBall->next; // �� ������ ���������� ����
		*LastBall = NewBall;
	}
	LeaveCriticalSection(&Ball_CRT);
	return LastBall;	// �� ������ ��(���� ���� ��)�� ��ȯ������ ����
}

void DeleteBall(BallStruct* DeadBall){//������ ����
		if(DeadBall==NULL) return;
	//����ȭ, return�Ǹ� �� ���������Ƿ� ������
	EnterCriticalSection(&Ball_CRT);
	BallCount--;
	if(DeadBall->back==NULL){
		if(DeadBall->next==NULL){	// ����
			//free(DeadBall);
			FirstBall=NULL;
			LastBall=NULL;
			DeadBall=NULL;
		}
		else{					// ����			
			FirstBall=DeadBall->next;	// ���� ����		
			//free(DeadBall->back);
			FirstBall->back=NULL;	//��� ����
		}
	}
	else{
		if(DeadBall->next==NULL){	// �ǳ�
			
			LastBall=DeadBall->back;
			LastBall->next=NULL;
			//free(DeadBall);			
		}
		else{								// �߰�
			DeadBall->back->next= DeadBall->next;	//�Ϳ�!
			DeadBall->next->back= DeadBall->back;			
			//free(DeadBall);			
		}
	}
	free(DeadBall);
	LeaveCriticalSection(&Ball_CRT);
}
