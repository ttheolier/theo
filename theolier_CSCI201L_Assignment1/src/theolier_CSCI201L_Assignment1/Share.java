package theolier_CSCI201L_Assignment1;


import org.apache.commons.text.WordUtils;

public class Share implements Comparable<Share> {
	//data
	String name;
	String ticker;
	String description;
	String startDate;
	String exchangeCode;
	
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
	//prints entire info for individual share
	public void printShare()
	{
		System.out.println(this.name + ", symbol " + this.ticker + ", started on " 
				+ this.startDate + ", " + "listed on " + this.exchangeCode
				+ ",");
		System.out.print(WordUtils.wrap("\t" + this.description + "\n",65,"\n\t",false));
		//System.out.print("\n\t" + this.description);
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
		return true;
	}
	//compare for sorting
	@Override
	public int compareTo(Share share)
	{
		//String lowerThis = this.getName();
		int last = this.getName().toLowerCase().compareTo(share.getName().toLowerCase());
		return last;
	}
}
