package ui.gui_controller.specifyRange.dateAndTime;


import java.text.ParseException; import java.util.Calendar;
import java.util.Date; import javax.swing.JFormattedTextField;
import javax.swing.SpinnerDateModel;



class SpinnerCommonDateModel extends SpinnerDateModel
{
	public static final int NULL = 0;	
	private static final int 
	START_YEAR = 2000, END_YEAR = 2100;
	
	
	
	private Calendar calendar;
	//private Date now, start, end;
	private int edited_fields[] = null;
	private JFormattedTextField text_field;
	
	
	
	public SpinnerCommonDateModel()
	{
		super();
		calendar = Calendar.getInstance();
	}	
	
	public Calendar getCalendar()
	{
		return calendar;
	}
	
	
	
	private int getMax(int field)
	{		
		if ( field == Calendar.YEAR )
		{
			return END_YEAR;
		}
		else
		{
			return calendar.getActualMaximum(field);
		}		
	}
	
	
	private int getMin(int field) {
		if ( field == Calendar.YEAR ) {
			return START_YEAR;
		} else {
			return calendar.getActualMinimum(field);
		}
	}
	
	
	
	private boolean condition_of_get_next_or_previous_value(int field, boolean check_next) {
		// 이거 순서 바뀌면 안 됨.
		final int fields[][] = {{
					Calendar.YEAR, Calendar.MONTH, Calendar.DATE
				},{
					Calendar.AM_PM, Calendar.HOUR, Calendar.MINUTE
				}
		};
		
		for (int i=0; i<fields.length; i++) {
			for (int j=0; j<fields[i].length; j++) {
				if ( fields[i][j] == field ) {
					for (; j>=0; j--) {
						int value;
						field = fields[i][j];
						value = calendar.get(field);
						if ( check_next && value < getMax(field) ) {
							return true;
						} else if ( !check_next && value > getMin(field) ) {
							return true;
						}
					}
					return false;
				}
			}
		}
		return false;
	}	
	
	
	private boolean condition_of_getNextValue(int field)
	{
		return condition_of_get_next_or_previous_value(field, true);
	}
	
	
	private boolean condition_of_getPreviousValue(int field)
	{
		return condition_of_get_next_or_previous_value(field, false);
	}
	
	
	
	@Override
    public Object getNextValue() {
		int field;		
		field = getCalendarField();
		if ( condition_of_getNextValue(field) ) {						
			calendar.add(field, 1);
		}		
		
		// 기존의 입력을 모두 반영한 상태서 현재 필드에 대한 처리를 하게 함
		try {
			text_field.commitEdit();
		} catch (ParseException e) {
			e.printStackTrace();
		}		
		edited_fields = new int[]{field};		
		return calendar.getTime();		
	}
	
	@Override
    public Object getPreviousValue()
	{
		int field = getCalendarField();		
		if (condition_of_getPreviousValue(field))
		{			
			calendar.add(field, -1);
		}
		
		
		
		// 기존의 입력을 모두 반영한 상태서 현재 필드에 대한 처리를 하게 함
		try {
			text_field.commitEdit();
		} catch (ParseException e) {
			e.printStackTrace();
		}
		
		// 기존의 입력을 모두 반영한 상태서 현재 필드에 대한 처리를 하게 함 
		edited_fields = new int[]{field};		
		return calendar.getTime();
	}
	
	
	
	public void setFields(int[] fields)
	{
		edited_fields = fields;
	}
	
	
	
	@Override
    public void setValue(Object value)
	{
		//System.out.println("edited_fields != null에 진입하기 전");
		//System.out.println("setValue");
		//System.out.println(value);
		if ( edited_fields != null )
		{
			//System.out.println("edited_fields != null에 진입한 후");
			//System.out.println("edited_fields.length");
			//System.out.println(edited_fields.length);
			for (int i = 0; i < edited_fields.length; i++)
			{				
				int field, field_value, old_field_value, diff;
				Calendar temp_calendar;
				
				
				
				field=edited_fields[i];				
				temp_calendar = Calendar.getInstance();
				temp_calendar.setTime((Date) value);
				field_value = temp_calendar.get(field);
				
				//System.out.println("field_value");
				//System.out.println(field_value);				
				
				if ( field == Calendar.YEAR )
				{
					if ( field_value < START_YEAR || field_value > END_YEAR  )
					{
						// 범위를 벗어난 값이 들어오면, 원래 상태로 되돌림.
						text_field.setValue(calendar.getTime());
						break;
					}
				}				
				old_field_value = calendar.get(field);
				diff = field_value - old_field_value;					
				calendar.add(field, diff);
			}
			edited_fields = null;
			// 아래는 실제로 값을 변경하는 것(이거 안 하면 변경 안 됨)
			// 그리고 이 작업은 시간이 많이 걸리므로 마지막에 해야지 쓰레드 문제가 안 생김
			System.out.println(calendar.getTime());
			super.setValue(calendar.getTime());			
		}
	}
	
	


	public void setTextField(JFormattedTextField text_field)
	{
		this.text_field = text_field;
	}
	
	
	
}
