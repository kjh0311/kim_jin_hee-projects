CRITICAL_SECTION Missile_CRT;

struct Missile{
	int x, y;
	struct Missile *next, *back;
};

struct Missile *MissileHead = NULL; // ���� ����
struct Missile *MissileTail = MissileHead; // �߰��� ���� �ʿ�

Missile* CreateMissile(int x,int y){
	struct Missile newMissile;
	newMissile.x=x;
	newMissile.y=y;
	newMissile.next=NULL;
	newMissile.back=NULL;	//�ʱⰪ�� �ݵ�� �־����
	EnterCriticalSection(&Missile_CRT);
	if(MissileHead == NULL)
	{// �� �޸� �Ҵ�
		MissileHead=(Missile*)malloc(sizeof(Missile));
		*MissileHead = newMissile;	// ���� ���� �̻����� �Ҵ�� �޸� �������� ����
		MissileTail = MissileHead;	// Tail�� Head�� ������ ��ġ�� ������Ʈ
	}
	else{//��尡 �ƴ� ���
		// ���ο� ������ �Ҵ��Ͽ� Tail->Next�� ����
		newMissile.back = MissileTail;
		MissileTail->next = (Missile*)malloc(sizeof(Missile));
		MissileTail = MissileTail->next; // �� ������ ���������� ����
		*MissileTail = newMissile;
	}
	LeaveCriticalSection(&Missile_CRT);
	return MissileTail;	// �� ������ ��(���� ���� ��)�� ��ȯ������ ����
}

void DeleteMissile(Missile* usedMissile){//������ ����
	
		if(usedMissile==NULL) return;
	//����ȭ, return�Ǹ� �� ���������Ƿ� ������
	EnterCriticalSection(&Missile_CRT);
	if(usedMissile->back==NULL){
		if(usedMissile->next==NULL){	// ����
			//free(usedMissile);
			MissileHead=NULL;
			MissileTail=NULL;
			//usedMissile=NULL;
		}
		else{					// ����			
			MissileHead=usedMissile->next;			
			//free(usedMissile->back);
			MissileHead->back=NULL;	//��� ����
		}
	}
	else{
		if(usedMissile->next==NULL){	// �ǳ�			
			MissileTail=usedMissile->back;
			MissileTail->next=NULL;
			//free(usedMissile);
			//usedMissile=NULL;
			
		}
		else{								// �߰�
			usedMissile->back->next= usedMissile->next;	//�Ϳ�!
			usedMissile->next->back= usedMissile->back;			
			//free(usedMissile);
			//usedMissile=NULL;		
		}
	}
	
	free(usedMissile);
	LeaveCriticalSection(&Missile_CRT);
	
	/*
//	return;
	if(usedMissile == NULL) return;
	EnterCriticalSection(&Missile_CRT);
	// ���� �Ϲ����� ��찡 �տ� �־�� ȿ������	
	if(usedMissile->back == NULL){ // ����
		//if(usedMissile->next != NULL){
			MissileHead = usedMissile->next;
			if(usedMissile==MissileTail) //������ ���
				MissileTail=NULL;
			free(usedMissile);
			usedMissile=NULL;
	}
	else{	//���� ������ �� (!=NULL�̿�)
		usedMissile->back->next= usedMissile->next;
		if(usedMissile->next != NULL){	//�ڰ� ������ ��
			usedMissile->next->back = usedMissile->back;
		}		
		else{ // Tail�� ���
			MissileTail=usedMissile->back;
			MissileTail->next=NULL;
		}
		free(usedMissile);
		usedMissile=NULL;
	}
	LeaveCriticalSection(&Missile_CRT);
	*/
	
}