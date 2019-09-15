import java.rmi.Naming;

public class Serverr
{ 
	public static void main(String args[]) 
	{ 
		try 
		{ 
			Naming.rebind("Implement",new Implement()); 
			System.out.println("Server is connected and waiting for the client"); 
		} 
		catch(Exception e)
		{ 
			System.out.println("Server could not connect: "+e); 
		} 
	} 
}
