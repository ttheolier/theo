package theolier_CSCI201L_Assignment2;

//class to get info from json
public class Share {
	String name;
	String ticker;
	String description;
	String startDate;
	String exchangeCode;
	String stockBrokers;
	
	//standard getters and setters
	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getTicker() {
		return ticker;
	}

	public void setTicker(String ticker) {
		this.ticker = ticker;
	}

	public String getStartDate() {
		return startDate;
	}

	public void setStartDate(String startDate) {
		this.startDate = startDate;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

	public String getExchangeCode() {
		return exchangeCode;
	}

	public void setExchangeCode(String exchangeCode) {
		this.exchangeCode = exchangeCode;
	}
	
	public String getStockBrokers() {
		return stockBrokers;
	}

	public void setStockBrokers(String stockBrokers) {
		this.stockBrokers = stockBrokers;
	}
	
	//Validator for indiv. share
	public boolean shareValidate()
	{
		if (this.name == null)
		{
			return false;
		}
		if (this.ticker == null)
		{
			return false;
		}
		if (this.description == null)
		{
			return false;
		}
		if (this.startDate == null)
		{
			return false;
		}
		if (this.exchangeCode == null)
		{
			return false;
		}
		if (this.stockBrokers == null || this.stockBrokers.equals("0"))
		{
			return false;
		}
		return true;
	}
}
