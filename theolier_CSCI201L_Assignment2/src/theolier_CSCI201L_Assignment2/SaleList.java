package theolier_CSCI201L_Assignment2;

import java.util.List;

public class SaleList {
	//list of all orders
	private static List<Sales> sales = null;
	//standard getters/setters
	public static List<Sales> getSales() {
		return sales;
	}

	public static void setSales(List<Sales> sales) {
		SaleList.sales = sales;
	}
	//validates each individual order
	public static boolean salesValidate(Stocks stocks)
	{
		for (int i = 0;i<sales.size();i++)
		{
			//if any parameter was not found
			if (sales.get(i).getOrder().equals("") || sales.get(i).getTicker().equals("")
					|| sales.get(i).getTime().equals(""))
			{
				return false;
			}
			//if a ticker doesn't exist or order is for 0 shares
			if (stocks.getNumBrokers().get(sales.get(i).getTicker())==null 
					|| sales.get(i).getOrder().equals("0"))
			{
				return false;
			}
		}
		return true;
	}
	
	
}
