void OnCreate()
{
	InitCS();		
		hMenu=LoadMenu(g_hInst,MAKEINTRESOURCE(IDR_MENU1));
		SetMenu(hWnd,hMenu);
		//Top= GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CYMENU);
		LoadGraphic();			
		
		//���� �ʱ�ȭ
		for(i=0;i<BH;i++) for(j=0;j<BW;j++)
		board[i][j]=' ';
		//���� �б�
		f = fopen("board.txt","r");
		for(i=0;i<BH;i++){
			fgets(board[i],20,f);
		}
		for(i=0;i<BH;i++) for(j=0;j<BW;j++) if(board[i][j]=='#'){
			board[i][j]=(i+j)%4 + '0'; //���ڸ� ���ڷ� ����
		}
		// ���� �� ����(Ŭ���� ���� �˻�)
		for(i=0;i<BH;i++) for(j=0;j<BW;j++) 
		if(board[i][j]>='0' && board[i][j]<='9')
		{	//���ڸ����� �˻簡��
			number+=1;
		}
		for(i=0;i<8;i++)
			crTemp[i]=RGB(255*(i%2),255*(i%4/2),255*(i%8/4));
		for(;i<16;i++)
			crTemp[i]=RGB(127*(i%2),127*(i%4/2),127*(i%8/4));
		
		LoadItemBitmap();
		CreateBall(x,y,dx,dy);
		FirstBall->Grabbed=TRUE;
		GetClientRect(hWnd,&ClientRect);
		//width=ClientRect.right;
		//height=ClientRect.bottom;
		//GetWindowRect(hWnd,&window);
		//width=window.right-window.left;
		//height=window.bottom-window.top;			
		//srand((unsigned)time(NULL));
		//InvalidateRect(hWnd,NULL,TRUE);		
		//Draw(NULL);
		//Draw();
		srand((unsigned)time(NULL));
		
}