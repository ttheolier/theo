package theolier_CSCI201L_Assignment1;

import java.util.List;

public class Stocks {
	//list of shares
	private List<Share> data = null;
	//standard getters setters
	public List<Share> getData() {
		return data;
	}

	public void setData(List<Share> data) {
		this.data = data;
	}
	//validates list as a whole
	public boolean stocksValidate()
	{
		for (int i =0;i<this.getData().size();i++)
		{
			if (!(this.getData().get(i).shareValidate()))
			{
				return false;
			}
		}
		return true;
	}
	//prints whole list for option 1
	public void printData()
	{
		//loops and prints each share using printShare
		for (int i =0;i<this.getData().size();i++)
		{
			this.getData().get(i).printShare();
		}
		System.out.print("\n");
	}
	//prints all stocks for the remove option
	public int printRemove()
	{ 
		//empty base case
		if (this.getData().size()==0)
		{
			System.out.println("There is no company to remove.");
			return 0;
		}
		int i;
		System.out.print("\n");
		//prints option and corresponding name
		for (i =0;i<this.getData().size();i++)
		{
			System.out.println(i+1 + ") " + this.getData().get(i).getName());
		}
		//returns total number of options for use in main
		return i+1;
	}
	//searches list for specific ticker
	public boolean searchTicker(String tick)
	{
		for (int i =0;i<this.getData().size();i++)
		{
			Share temp = this.getData().get(i);
			//prints info if ticker is found
			if (temp.getTicker().toUpperCase().equals(tick) )
			{
				System.out.println("\n" + temp.name + ", symbol " + temp.ticker + 
						", started on "+ temp.startDate + ", " + "listed on " + temp.exchangeCode 
						+ "\n");
				return true;
			}
		}
		//message if ticker is not found
		System.out.println("\n" + tick + " could not be found.");
		return false;
	}
	//search ticker for adding to list, same as above but no messages
	public boolean searchTickerAdd(String tick)
	{
		for (int i =0;i<this.getData().size();i++)
		{
			Share temp = this.getData().get(i);
			if (temp.getTicker().toUpperCase().equals(tick) )
			{
				return true;
			}
		}
		return false;
	}
	//search for company
	public boolean searchCompany(String company)
	{
		company = company.toUpperCase();
		for (int i =0;i<this.getData().size();i++)
		{
			Share temp = this.getData().get(i);
			//returns true if ticker is found
			if (temp.getName().toUpperCase().equals(company) )
			{
				return true;
			}
		}
		return false;
	}
	//searches for all stocks on an exchange
	public boolean searchExchange(String exchange)
	{
		//initialize
		int indicator = 0;
		String total = "";
		for (int i =0;i<this.getData().size();i++)
		{
			Share temp = this.getData().get(i);
			if (temp.getExchangeCode().toUpperCase().equals(exchange) )
			{
				//if none found yet, mark as found and append to string
				if (indicator == 0)
				{
					total += temp.getTicker();
					indicator = 1;
				}
				//if not first found, append using and
				else
				{
					total += " and ";
					total += temp.getTicker();
				}
				
			}
		}
		//if none were found
		if (indicator == 0)
		{
			System.out.println("\nNo exchange named " + exchange + " found.");
			return false;
		}
		//print appropriate message
		else
		{
			System.out.println("\n"+total + " found on the " + exchange + " exchange.");
			return true;
		}
	}
	
}
