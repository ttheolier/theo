package theolier_CSCI201L_Assignment2;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.sql.Timestamp;
import java.time.Duration;
import java.time.Instant;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Semaphore;

import com.google.gson.Gson;
import com.google.gson.JsonSyntaxException;

import com.opencsv.bean.CsvToBeanBuilder;


public class MainIO {
	//private static SimpleDateFormat formatter = new SimpleDateFormat("H:mm:ss:SSS",new Locale("en","US"));
	
	public static void main(String[] args)
	{
		//vars for filename, loop, scanner, and stocks list
		String fname = null;
		int loop = 1;
		Stocks stocks = new Stocks();
		Scanner sc;
		//loop to read first(json) file
		while (loop == 1)
		{
			System.out.print("\nWhat is the name of the file containing the company information?");
			sc = new Scanner(System.in);
			fname = sc.nextLine();
			//de-serialize
			Gson gson = new Gson();
			try
			{
				stocks = gson.fromJson(new FileReader(fname), Stocks.class);
			}
			//catches if file couldn't be located
			catch (IOException ex)
			{
				System.out.println("The file " + fname + " could not be found.");
				//??
				continue;
			}
			//catches if a non-json file was put in or other potential invalid
			catch (JsonSyntaxException ex)
			{
				System.out.println("The file " + fname + " is not formatted properly.");
				continue;
			}
			//validate that file wasn't missing any parameters
			if (!stocks.stocksValidate())
			{
				System.out.println("The file " + fname + " is not formatted properly.");
				continue;
			}
			//ensures loop does not run again if no exceptions thrown
			loop = 0;
			System.out.println("The file has been properly read\n");
		}
		//set broker map
		stocks.setNumBrokers();
		//loop to read second(csv) file
		loop = 1;
		while (loop == 1)
		{
			//get input
			System.out.print("\nWhat is the name of the file containing the schedule information?");
			sc = new Scanner(System.in);
			fname = sc.nextLine();
			//make sure file is csv, if not prompt again
			if (fname.charAt(fname.length()-1)!= 'v'||fname.charAt(fname.length()-2)!= 's'
					||fname.charAt(fname.length()-3)!= 'c'
					||fname.charAt(fname.length()-4)!= '.')
			{
				System.out.println("The file " + fname + " is not a csv file.");
				continue;
			}
			try
			{
				//build list from csv
				List<Sales> sales = new CsvToBeanBuilder<Sales>(new FileReader(fname))
						.withType(Sales.class)
						.build()
						.parse();
				
				//old code for manually parsing, unfinished
				/*Scanner sc1 = new Scanner(file).useDelimiter("\\s,\\s");
				LinkedList<Sales> sales = new LinkedList<Sales>();
				while (sc1.hasNextLine())
				{
					Sales sale = new Sales();
					System.out.println("b4 first one");
					sale.setTime(sc1.nextInt());
					System.out.println(sale.getTime());
					//sc1.skip(", ");
					sale.setTicker(sc1.next());
					System.out.println(sale.getTicker());
					sale.setOrder(sc1.nextInt());
					System.out.println(sale.getOrder());
					//sc1.next();
					sales.add(sale);
				}*/
				//set sales list
				SaleList.setSales(sales);
				//if file was empty
				if (sales.isEmpty())
				{
					System.out.println("File, was empty, select another.");
					continue;
				}
			}
			//catches if file couldn't be located
			catch (FileNotFoundException ex)
			{
				System.out.println("The file " + fname + " could not be found.");
				continue;
			}
			//validate that file doesn't have any nonsensical parameters
			//such as a ticker that doesnt exist in json or order of 0
			if (!SaleList.salesValidate(stocks))
			{
				System.out.println("The file " + fname + " has either a non-existent ticker, "
						+"an order of size 0,");
				System.out.println("or a missing parameter.");
				System.out.println("Please provide a different file or edit your file.");
				continue;
			}
			//clean up
			System.out.println("The file has been properly read\n");
			sc.close();
			loop= 0;
		}
		//print start message
		System.out.println("Starting execution of program...");
		//get display start time
		Timestamp fStartTime = new Timestamp(System.currentTimeMillis());
		//get functional start time
		Instant startTime = Instant.now();
		//iterate through list
		ExecutorService executor = Executors.newCachedThreadPool();
		while(!SaleList.getSales().isEmpty())
		{
			//instantiate thread pool
			executor = Executors.newCachedThreadPool();
			//calc current runtime
			Instant currentTime = Instant.now();
			Duration runTime = Duration.between(startTime,currentTime);
			//get the execution time of first item
			Sales temp = SaleList.getSales().get(0);
			int execution = Integer.valueOf(temp.getTime());
			//while the next item in the list has the current runTime
			while (execution == runTime.toSeconds())
			{
				//create new sales thread
				SalesThread t1 = 
						new SalesThread(temp.getTicker(),startTime,temp.getOrder(),fStartTime);
				//remove from list
				SaleList.getSales().remove(0);
				//if we havent already made a semaphore, create one and place in map
				if (SalesThread.getSemaphores().get(temp.getTicker())==null)
				{
					Semaphore semaphore = 
							new Semaphore(stocks.getNumBrokers().get(temp.getTicker()));
					SalesThread.addSemaphore(temp.getTicker(), semaphore);
				}
				//execute thread
				executor.execute(t1);
				//as long as the list isnt empty, update temp and exec. time to next sale
				if (!SaleList.getSales().isEmpty())
				{
					//currentTime = Instant.now();
					//runTime = Duration.between(startTime,currentTime);
					temp = SaleList.getSales().get(0);
					execution = Integer.valueOf(temp.getTime());
				}
				//if it is empty, break out
				else 
				{
					break;
				}
			}
			//shutdown executor
			executor.shutdown();
		}
		//ensure threads finsih up before printing final message
		while (!executor.isTerminated())
		{
			Thread.yield();
		}
		System.out.println("All trades completed!");
	}
}
