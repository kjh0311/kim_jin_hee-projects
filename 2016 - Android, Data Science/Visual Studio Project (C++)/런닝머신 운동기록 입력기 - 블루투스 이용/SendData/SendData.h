#include "../ShowContents/Handles.h"


/*
��������� �̿��ؼ� �Է��� ���� ������.
�Է��� ���� SQL �������� ������.
SQL ����
'yyyy-mm-dd', 'HH:MM', 'HH:MM', iiii, ff.ff, ff.f, ff.f
*/


static
const int

YEAR_LEN = 4, MONTH_LEN = 2, DAY_LEN = 2,
// 'yyyy-mm-dd'
DATE_LEN 
= 1
+ YEAR_LEN + 1
+ MONTH_LEN + 1
+ DAY_LEN
+ 1,

HOUR_LEN = 2, MINUTE_LEN = 2,
// 'HH:MM'
TIME_LEN 
= 1
+ HOUR_LEN
+ 1
+ MINUTE_LEN
+ 1,

// iiii
KCAL_LEN = 4,
// ff.ff
KM_LEN = 5,
// ff.f
GRAD_LEN = 4,
// ff.f
SPEED_LEN = 4,

// 'yyyy-mm-dd','HH:MM','HH:MM',iiii,ff.ff,ff.f,ff.f
// + 1 �� �޸� ������ ����
TOTAL_LEN =
DATE_LEN + 1 +
TIME_LEN + 1 +
TIME_LEN + 1 +
KCAL_LEN + 1 +
KM_LEN	 + 1 +
GRAD_LEN + 1 +
SPEED_LEN

// ������ + 1�� ���Ṯ���� ����
+ 1
;
/*
�������� ������ �ҹ��ڿ� _ ��,
ū �ǹ��� ������ �빮�ڿ� �ҹ��ڷ� ���� ���� ��

�������� ����
void get_text_and_fix_length(HWND hwnd, LPTSTR ptr, int len);
������

ū �ǹ��� ����
LPTSTR AppendDate(LPTSTR pointer_of_data);
�� ������
*/

// 'yyyy-mm-dd','HH:MM','HH:MM',iiii,ff.ff,ff.f,ff.f

// 'yyyy-mm-dd'
LPTSTR AppendDate(LPTSTR pointer_of_data);

// 'HH:MM'
LPTSTR AppendStartTime(LPTSTR pointer_of_data);

// 'HH:MM'
LPTSTR AppendEndTime(LPTSTR pointer_of_data);

// iiii
LPTSTR AppendKcal(LPTSTR pointer_of_data);

// ff.ff
LPTSTR AppendKm(LPTSTR pointer_of_data);

// ff.f
LPTSTR AppendGrad(LPTSTR pointer_of_data);

// ff.f
LPTSTR AppendSpeed(LPTSTR pointer_of_data);

// �޸�(,) �߰�
LPTSTR AppendComma(LPTSTR pointer_of_data);


void get_text_and_fix_length(HWND hwnd, LPTSTR ptr, int len);
void get_hour(HWND h_ampm, HWND h_edit_hour, LPTSTR pointer_of_data);
int get_number(HWND hwnd, LPTSTR ptr, int len);


extern 
LPCTSTR
EX_STR_AM,
EX_STR_PM;

extern const int EX_AMPM_LEN;