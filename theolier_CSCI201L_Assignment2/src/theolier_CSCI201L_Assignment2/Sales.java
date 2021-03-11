package theolier_CSCI201L_Assignment2;

import com.opencsv.bean.CsvBindByPosition;
//Class to store individual orders
public class Sales {
	@CsvBindByPosition(position = 0)
	private String time;
	
	@CsvBindByPosition(position = 1)
	private String ticker;
	
	@CsvBindByPosition(position = 2)
	private String order;
	
	//standard getters and setters
	public String getTime() {
		return time;
	}
	public void setTime(String time) {
		this.time = time;
	}
	public String getTicker() {
		return ticker;
	}
	public void setTicker(String ticker) {
		this.ticker = ticker;
	}
	public String getOrder() {
		return order;
	}
	public void setOrder(String order) {
		this.order = order;
	}
}
