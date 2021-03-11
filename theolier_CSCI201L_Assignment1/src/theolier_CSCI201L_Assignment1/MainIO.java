package theolier_CSCI201L_Assignment1;

import java.util.*;


import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonSyntaxException;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;

public class MainIO {
	public static void main(String[] args)
	{
		//vars for filename, loop, and stocks list
		String fname = null;
		int loop = 1;
		Stocks stocks;
		//loop to read file
		while (loop == 1)
		{
			try
			{
				//prompt for input
				System.out.print("\nWhat is the name of the company file?");
				Scanner sc = new Scanner(System.in);
				fname = sc.nextLine();
				//de-serialize
				Gson gson = new Gson();
				stocks = gson.fromJson(new FileReader(fname), Stocks.class);
				//validate that file wasn't missing any parameters
				if (!stocks.stocksValidate())
				{
					System.out.println("The file " + fname + " is not formatted properly.");
					continue;
				}
				//ensures loop does not run again if no exceptions thrown
				loop = 0;
				System.out.println("The file has been properly read\n");
				//inner loop for main menu selection
				while (true)
				{
					System.out.println("\t1) Display all public companies");
					System.out.println("\t2) Search for a stock (by ticker)");
					System.out.println("\t3) Search for all stocks on an exchange");
					System.out.println("\t4) Add a new company/stocks");
					System.out.println("\t5) Remove a company");
					System.out.println("\t6) Sort companies");
					System.out.println("\t7) Exit");
					//catch potential error
					int num = 0;
					//loop until selection valid
					while (num<1 || num>7)
					{
						System.out.print("What would you like to do?");
						try
						{
							num = sc.nextInt();
							if (num <1 || num>7)
							{
								System.out.println("\nThis is not a valid option\n");
							}
						}
						//catch invalid input
						catch (InputMismatchException ex)
						{
							System.out.println("\nThis is not a valid option\n");
							//System.out.print("\nWhat would you like to do?");
							sc.next();
							continue;
						}
					}
					sc.nextLine();
					//print all
					if (num == 1)
					{
						//prints all
						System.out.print("\n");
						stocks.printData();
						continue;
					}
					//find ticker
					if (num == 2)
					{ 
						//loop until company is found
						boolean notFound = true;
						while (notFound)
						{
							System.out.print("\nWhat is the name of the company you would "
									+ "like to search for?");
							//sc.nextLine();
							String tick = sc.nextLine();
							tick = tick.toUpperCase();
							notFound = !(stocks.searchTicker(tick));
						}
					}
					//list exchange
					if (num ==3)
					{
						//loop until exchange found
						boolean notFound = true;
						while (notFound)
						{
							System.out.print("\nWhat Stock Exchange would you like to search"
									+ " for?");
							String exchange = sc.nextLine();
							exchange = exchange.toUpperCase();
							notFound = !(stocks.searchExchange(exchange));
						}
					}
					//add company
					if (num==4)
					{
						//initialize needed vars
						String company = "";
						String ticker = "";
						String date= "";
						String description = "";
						String exchange = "";
						//loop gets a company name until valid
						boolean notFound = true;
						while (notFound)
						{
							System.out.print("\nWhat is the name of the company you would" +
									" like to add?");
							company = sc.nextLine();
							//search for company
							if (stocks.searchCompany(company))
							{
								System.out.print("\nThere is already an entry for " + company +".");
							}
							else
							{
								notFound = false;
							}
						}
						//loop gets a ticker until valid
						notFound = true;
						while (notFound)
						{
							System.out.print("\nWhat is the stock symbol of " + company +"?");
							ticker = sc.nextLine();
							ticker = ticker.toUpperCase();
							//search for ticker
							if (stocks.searchTickerAdd(ticker))
							{
								System.out.print("\nThere is already an entry for " + company +".");
							}
							else
							{
								notFound = false;
							}
						}
						//loop gets a date until valid
						boolean invalidDate = true;
						while (invalidDate)
						{
							System.out.print("\nWhat is the start date of " + company + "?");
							date = sc.nextLine();
							//check date length
							if(date.length()!= 10)
							{
								System.out.println("\nInvalid date format");
								continue;
							}
							//check date makeup
							boolean valid = true;
							for (int i = 0;i<date.length();i++)
							{
								if (i == 4 || i == 7)
								{
									if (date.charAt(i) != '-')
									{
										valid = false;
										System.out.println("\nInvalid date format");
										break;
									}
								}
								else if ((int)date.charAt(i)<48 ||(int)date.charAt(i)>57 )
								{
									valid = false;
									System.out.println("\nInvalid date format");
									break;
								}
							}
							if (valid)
							{
								invalidDate = false;
							}
						}
						//loop gets exchange until valid
						boolean validExchange = false;
						while(!validExchange)
						{
							System.out.print("\nWhat is the exchange where " + company
									+ " is listed?");
							exchange = sc.nextLine();
							exchange = exchange.toUpperCase();
							if (exchange.equals("NASDAQ") || exchange.equals("NYSE"))
							{
								validExchange = true;
							}
							else
							{
								System.out.println("\nNot a valid exchange.");
								continue;
							}
						}
						//get description
						System.out.print("\nWhat is the description of " + company + "?");
						description = sc.nextLine();
						
						//create object and assign, and add to list
						Share temp = new Share();
						temp.setName(company);
						temp.setTicker(ticker);
						temp.setDescription(description);
						temp.setStartDate(date);
						temp.setExchangeCode(exchange);
						stocks.getData().add(temp);	
						System.out.println("\nThere is now an entry for:");
						stocks.getData().get(stocks.getData().size()-1).printShare();
					}
					//remove company
					if (num == 5)
					{
						//holds size of list
						int err = stocks.printRemove();
						//error checking for empty list, removed all
						if (err == 0)
						{
							continue;
						}
						//loops until valid selection and removes
						int selection = 0;
						while (selection<1 || selection>stocks.getData().size())
						{
							System.out.print("\nWhich company would you like to remove?");
							try
							{
								selection = sc.nextInt();
								if (selection <1 ||  selection>stocks.getData().size())
								{
									System.out.println("\nThis is not a valid option");
								}
							}
							catch (InputMismatchException ex)
							{
								System.out.println("\nThis is not a valid option");
								sc.next();
								continue;
							}
						}
						String name = stocks.getData().get(selection-1).getName();
						stocks.getData().remove(selection-1);
						System.out.println("\n" + name + " is now removed.");
					}
					//sort
					if (num == 6)
					{
						//pre-emptively sorts
						Collections.sort(stocks.getData());
						
						System.out.println("\n1) A to Z");
						System.out.println("2) Z to A");
						//loop until valid selection
						int selection = 0;
						while (selection<1 || selection>2)
						{
							System.out.print("\nHow would you like to sort by?");
							try
							{
								selection = sc.nextInt();
								if (selection <1 ||  selection>2)
								{
									System.out.println("\nThis is not a valid option");
								}
							}
							catch (InputMismatchException ex)
							{
								System.out.println("\nThis is not a valid option");
								sc.next();
								continue;
							}
						}
						//for Z to A, reverse original sort
						if (selection == 2)
						{
							Collections.reverse(stocks.getData());
						}
						
					}
					//exit
					if (num == 7)
					{
						System.out.println("\n1) Yes");
						System.out.println("2) No");
						//loop until valid selection
						int selection = 0;
						while (selection<1 || selection>2)
						{
							System.out.print("Would you like to save your edits?");
							try
							{
								selection = sc.nextInt();
								if (selection <1 ||  selection>2)
								{
									System.out.println("\nThis is not a valid option\n");
								}
							}
							catch (InputMismatchException ex)
							{
								System.out.println("\nThis is not a valid option\n");
								//System.out.print("\nWhat would you like to do?");
								sc.next();
								continue;
							}
						}
						//for no save
						if (selection == 2)
						{
							System.out.println("\nThank you for using my program!");
							return;
						}
						//yes save
						else
						{
							//serializes and flushes/closes all variables
							Writer writer = new FileWriter(fname);
							Gson gson1 = new GsonBuilder().disableHtmlEscaping().setPrettyPrinting().create();
							gson1.toJson(stocks,writer);
							System.out.println("\nYour edits have been saved to "+fname+".");
							System.out.println("Thank you for using my program!");
							writer.flush();
							writer.close();
							sc.close();
							return;
						}
					}
					
						
				}
			}
			//catches if file couldn't be located
			catch (IOException ex)
			{
				System.out.println("The file " + fname + " could not be found.");
			}
			//catches if a non-json file was put in or other potential invalid
			catch (JsonSyntaxException ex)
			{
				System.out.println("The file " + fname + " is not formatted properly.");
			}
		}
		
	}
}
