import java.rmi.Naming;
import java.util.*;
public class Client
 {
	public static void main(String args[])
	{
		try
		{
			Inter ai=(Inter)Naming.lookup("//localhost:/Implement");
			String name;
			String city;
			int type;
			Scanner s= new Scanner(System.in);
			System.out.println("\n\nPlease provide your details to Login");
			System.out.println("Enter your name:");
			name=s.nextLine();
			System.out.println("Enter city:");
			city=s.nextLine();
			System.out.println("You have successfully logged in. Enjoy shopping");			
			//ArrayList<String> products=new ArrayList<String>();
			String hospital[]=new String[7];
			int getgwRoom[]=new int[10];
			int getspRoom[]=new int[10];
			int geticRoom[]=new int[10];
			String msg1,msg2;
			hospital=ai.hospDetails();
			getspRoom=ai.getsplRoom();
			getgwRoom=ai.getgRoom();
			geticRoom=ai.geticuRoom();
			System.out.println("1.Show List of Hospital:");
			System.out.println("2.Admit");
			System.out.println("3.Discharge");
			System.out.println("4.Show details");
			System.out.println("5.Log Out");
			int ch,c,l=0;
			int bedg[]=new int[10];
			int beds[]=new int[10];
			int bedi[]=new int[10];
			for(l=0;l<hospital.length;l++){
				bedg[l]=0;
				beds[l]=0;
				bedi[l]=0;
			}
			//int d[]=new int[10];
			//for(l=0;l<6;l++){
			//	d[l]=0;
			//}
			//int x[]=new int[10];
			do
			{
				System.out.println("Enter your choice(i.e 1 or 2 or 3 or 4 or 5)");
				ch=s.nextInt();
				switch(ch)
				{
					case 1:
							for(l=0;l<hospital.length;l++){
								System.out.println(l+":"+hospital[l]+"------>    No. of gward----->"+getgwRoom[l]+" No. of special ward----->"+getspRoom[l]+" No. of icu----->"+geticRoom[l]);
							}
							break;
					case 2: System.out.println("Hospital where the patient wants to be admitted(Enter hospital serial no.(i.e 0 or 1 or 2 or 3 or 4 or 5)??");
							c=s.nextInt();
							System.out.println("Enter the type of room (The serial number of room type");
							System.out.println("1.General Ward");
							System.out.println("2.Special Ward");
							System.out.println("3.ICU");
							type=s.nextInt();
							msg1=ai.admit(c,type);
							if(type==1)
							bedg[c]++;
							if(type==2)
							beds[c]++;
							if(type==3)
							bedi[c]++;
							System.out.println(msg1);
							break;
					case 3: System.out.println("Enter the hospital from where the patient has to be discharged(Enter hospital serial no.)...");
							c=s.nextInt();						
							System.out.println("Enter the type of room (The serial number of room type");
							System.out.println("1.General Ward");
							System.out.println("2.Special Ward");
							System.out.println("3.ICU");
							type=s.nextInt();
							msg2=ai.discharge(c,type);
							if(type==1)
							bedg[c]--;
							if(type==2)
							beds[c]--;
							if(type==3)
							bedi[c]--;
							System.out.println(msg2);
							break;
					case 4: 
							//for(l=0;l<hospital.length;l++)
							//{
							//	bed[l]=bed[l]-d[l];
							//}
							System.out.println("Name: "+name);
							System.out.println("City: "+city);
							for(l=0;l<hospital.length;l++)
							{
								if(bedg[l]!=0 && bedg[l]>=0)
								{
								
								getgwRoom[l]--;
							
								System.out.println("Name: "+hospital[l]+"--->Gward "+bedg[l]);
								bedg[l]--;
								}
									if(beds[l]!=0 && beds[l]>=0)
								{
								
								getspRoom[l]--;
							
								System.out.println("Name: "+hospital[l]+"--->Special ward "+beds[l]);
								beds[l]--;
								}
									if(bedi[l]!=0 && bedi[l]>=0)
								{
								
								geticRoom[l]--;
							
								System.out.println("Name: "+hospital[l]+"--->ICU "+bedi[l]);
								bedi[l]--;
								}
							}
							break;
					case 5: System.out.println(name+"Logging out");
							break;
				}
			}while(ch!=5);
		}
		catch(Exception e)
		{
			System.out.println("Client Exception: "+e);
		}
	}
}