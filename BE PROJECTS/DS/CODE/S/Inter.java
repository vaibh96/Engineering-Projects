import java.rmi.*;
public interface Inter extends Remote
{
	public String admit(int choice,int type) throws RemoteException;
	public String discharge(int choice1,int type1) throws RemoteException;
	public String[] hospDetails() throws RemoteException;
	public int[] getgRoom() throws RemoteException;
	public int[] getsplRoom() throws RemoteException;
	public int[] geticuRoom() throws RemoteException;

	
}
