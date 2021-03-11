package theolier_CSCI201L_Assignment2;

import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.time.Instant;
import java.util.HashMap;
import java.util.Locale;
import java.util.concurrent.Semaphore;
//main thread class for each order
public class SalesThread extends Thread{
	//static hashmap to store semaphores
	private static HashMap<String,Semaphore> semaphores = new HashMap<String,Semaphore>();
	//ticker
	private String ticker;
	//number of shares ordered
	private String numOrder;
	//functional start time, static
	private static Instant startTime;
	//printing start time, static
	private static Timestamp fStartTime;
	//date formatter for printing, static
	private static SimpleDateFormat formatter = new SimpleDateFormat("H:mm:ss:SSS",
			new Locale("en","US"));
	
	//constructor
	public SalesThread(String tick, Instant start, String num,Timestamp s)
	{
		//sets ticker, start time, order number
		this.ticker = tick;
		startTime = start;
		this.numOrder = num;
		fStartTime = s;
	}
	
	//standard getters/setters
	public String getNumOrder() {
		return numOrder;
	}



	public void setNumOrder(String numOrder) {
		this.numOrder = numOrder;
	}



	public static HashMap<String, Semaphore> getSemaphores() {
		return semaphores;
	}



	public static void setSemaphores(HashMap<String, Semaphore> semaphores) {
		SalesThread.semaphores = semaphores;
	}
	//function for adding a Semaphore to the map
	public static void addSemaphore(String tick, Semaphore sem)
	{
		semaphores.put(tick,sem);
	}


	//more standard getters/setters
	public String getTicker() {
		return ticker;
	}



	public void setTicker(String ticker) {
		this.ticker = ticker;
	}



	public static Instant getStartTime() {
		return startTime;
	}



	public static void setStartTime(Instant startTime) {
		SalesThread.startTime = startTime;
	}


	//run
	public void run ()
	{
		try
		{
			semaphores.get(this.ticker).acquire();
			//purchase
			if (Integer.valueOf(this.numOrder)>0)
			{
				//get current time
				Timestamp time = new Timestamp(System.currentTimeMillis());
				//find difference
				long temp = time.getTime() - fStartTime.getTime();
				//make timestamp, need to add 28_000_000ms (8 hours) because 
				//my system defaults to 16 hours for some reason
				Timestamp pTime = new Timestamp(temp+ 28_800_000);
				//print start message
				System.out.println(formatter.format(pTime) + " Starting Purchase of " 
						+ this.numOrder + " stocks of " + this.ticker + ".");
				//sleep for 1 second
				Thread.sleep(1000);
				//get new times
				time = new Timestamp(System.currentTimeMillis());
				temp = time.getTime() - fStartTime.getTime();
				pTime.setTime(temp + 28_800_000);
				//print finish message
				System.out.println(formatter.format(pTime) + " Finishing Purchase of " 
						+ this.numOrder + " stocks of " + this.ticker + ".");
			}
			//sale
			else
			{
				//get current time
				Timestamp time = new Timestamp(System.currentTimeMillis());
				//find difference
				long temp = time.getTime() - fStartTime.getTime();
				//make timestamp, need to add 28_000_000ms (8 hours) because 
				//my system defaults to 16 hours for some reason
				Timestamp pTime = new Timestamp(temp+ 28_800_000);
				//print start message
				System.out.println(formatter.format(pTime)+ " Starting Sale of " 
						+ this.numOrder + " stocks of " + this.ticker + ".");
				//sleep for 1 second
				Thread.sleep(1000);
				//get new times
				time = new Timestamp(System.currentTimeMillis());
				temp = time.getTime() - fStartTime.getTime();
				pTime.setTime(temp + 28_800_000);
				//print finish message
				System.out.println(formatter.format(pTime) + " Finishing Sale of " 
						+ this.numOrder + " stocks of " + this.ticker + ".");
			}
		}
		//IE exception
		catch (InterruptedException e)
		{
			System.out.println("Thread Interrupted!");
		}
		//release permit
		finally
		{
			semaphores.get(this.ticker).release();
		}
	}
}
