#include "stdafx.h"



SOCKET g_client_socket;
extern const int EX_TOTAL_LEN;


extern HWND hWndMain;
// ������ �̿��Ͽ� �����͸� �����Ѵ�.


#ifdef UNICODE
void SendToBluetooth(LPTSTR lptstr_data)
{	
	char* data;


	data = (char*)malloc(EX_TOTAL_LEN*sizeof(char));

	WideCharToMultiByte(CP_ACP, 0, lptstr_data, -1, data, EX_TOTAL_LEN, NULL, NULL);


	send(g_client_socket, data, strlen(data), 0);

	if (data)
	free(data);
}

#else
void SendToBluetooth(LPTSTR lptstr_data)
{	
	send(g_client_socket, lptstr_data, strlen(lptstr_data), 0);
}

#endif

DWORD WINAPI ServerRunThread(LPVOID temp);

// ���⼭ g_client_socket ���� ���´�.

void StartServer(HWND hwnd)
{
	HANDLE h_thread;
	h_thread = CreateThread(NULL, 0, ServerRunThread, hwnd, 0, NULL);
	CloseHandle(h_thread);
}




#include "ReadyInformation.h"
#define CXN_SUCCESS                       0


// accept �ϱ� ���� �ʿ��� ��� ������ �Ѵ�.
ULONG ready_to_accept(ReadyInformation *p_ready_information);
// accept �ϰ�, recv, send �� �޸� �Ҵ� �� ������ �ϰ�, 
// ready_to_accept ���� �Ҵ��� �ڿ��� ��� �ݳ��Ѵ�.
ULONG accept_and_communicate(ReadyInformation ready_information);

DWORD WINAPI ServerRunThread(LPVOID hwnd)
{
	ULONG ulRetCode;
	ReadyInformation ready_information;
	SOCKET LocalSocket;
	int iLengthReceived;
	char buffer[1];


	ulRetCode = ready_to_accept(&ready_information);
	LocalSocket = ready_information.LocalSocket;


	while (ulRetCode == CXN_SUCCESS)
	{
		MessageBox((HWND)hwnd, _T("accept�Ǳ� ��"), _T("accept�Ǳ� ��"), MB_OK);
		g_client_socket = accept(LocalSocket, NULL, NULL);
		MessageBox((HWND)hwnd, _T("accept���"), _T("accept���"), MB_OK);

		do 
		{
			iLengthReceived = recv(g_client_socket, buffer, 1, 0);

			// send(g_client_socket, (char *)buffer, EX_TOTAL_LEN, 0);

		} while (iLengthReceived > 0);

		MessageBox((HWND)hwnd, _T("���� ������ �ްڽ��ϴ�."), _T("������ ����Ǿ����ϴ�."), MB_OK);

	}
	return(DWORD)ulRetCode;
}