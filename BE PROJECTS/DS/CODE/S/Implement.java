import java.rmi.*;
import java.rmi.server.*;
import java.util.*;
public class Implement extends UnicastRemoteObject implements Inter
{
	private static int gward[]={20,20,20,20,20,20};
	private static int splward[]={10,10,10,10,10,10};
	private static int icu[]={5,5,5,5,5,5};
	
	//private int k=0;
	public Implement() throws RemoteException
	{
	}
	public String admit(int choice,int type)
	{
		int flag,m;
		int y[]=new int [10];
		flag=choice; 
		for(m=0;m<6;m++)
		{
			if(m==flag && type==1 && gward[m]>=1){
				gward[m]--;
				break;
			}
			if(m==flag && type==2 && splward[m]>=1){
				splward[m]--;
				break;
			}
			if(m==flag && type==3 && icu[m]>=1){
				icu[m]--;
				break;
			}
		}
		if(m==6)
			return "All beds full";
		return "";
	}
	
	public String discharge(int choice1,int type1)
	{
		int flag1,m;
		int can[]=new int [10];
		flag1=choice1;
		for(m=0;m<6;m++)
		{
			if(m==flag1 && type1==1 && gward[m]!=20){
				gward[m]++;			
				break;
			}
			if(m==flag1 && type1==2 && splward[m]!=10){
				splward[m]++;			
				break;
			}
			if(m==flag1 && type1==3 && icu[m]!=5){
				icu[m]++;			
				break;
			}
		}
		if(m==6)
			return "Not admitted";
		return "";
	}
	public String[] hospDetails()
	{
		String hospital[]= new String[] {"Kokilaben Hospital","Nanavati Hospital","Lilavati Hospital","Fortis Hospital"};
		return hospital;
	}
	public int[] getgRoom()
	{
		return gward;
	}
	
	public int[] getsplRoom() 
	{
		return splward;
	}
	public int[] geticuRoom()
	{
		return icu;
	}

}
