package theolier_CSCI201L_Assignment2;

import java.util.HashMap;
import java.util.List;

//conatins list of shares and hash map of number of brokers per ticker
public class Stocks {
	//list of shares
	private List<Share> data = null;
	//map of shares to stockbroker num
	private HashMap<String, Integer> numBrokers = new HashMap<String,Integer>();
	//standard getters setters
	
	public HashMap<String, Integer> getNumBrokers()
	{
		return this.numBrokers;
	}
	
	public void setNumBrokers()
	{
		for (int i =0;i<this.getData().size();i++)
		{
			Share temp = this.getData().get(i);
			this.numBrokers.put(temp.getTicker(), Integer.valueOf(temp.getStockBrokers()));
		}
	}
	
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
}
