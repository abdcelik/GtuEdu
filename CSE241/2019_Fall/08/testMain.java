import cse241_hw8.*;

/**
 * Testing GTUSet, GTUVector and GTUIterator classes.
 * @author Abdullah_Celik_171044002
 */
public class testMain
{
	public static void main(String[] args)
	{
		testGTUSet();
		testGTUVector();
		testGTUIterator();
		testGTUContainerException();
	}
	
	/**
	 * Print the information about container
	 * @param <T>
	 * @param container
	 */
	public static <T> void printContainerInformation(GTUContainerDerived<T> container)
	{
		System.out.println("Size : " + container.size());
		System.out.println("Capacity : " + container.getCapacity());
		System.out.println("Max Size : " + container.max_size());
		System.out.println(container);
	}
	
	/**
	 * Testing GTUSet Class
	 */
	@SuppressWarnings("unchecked")
	public static void testGTUSet()
	{
		System.out.println("\n\n--------------------  TESTING GTUSet CLASS  --------------------\n");
		System.out.println("__________________  No parameter constructor  __________________");
		GTUSet<Integer> a1 = new GTUSet<Integer>();
		printContainerInformation(a1);
		
		System.out.println("__________________  One parameter constructor  _________________");
		GTUSet<Integer> a2 = new GTUSet<Integer>(5);
		printContainerInformation(a2);
		
		System.out.println("_________________________ insert method ________________________");
		System.out.println("Before insertion : ");
		printContainerInformation(a2);
		System.out.println("After insertion : ");
		try
		{
			a2.insert(5);
			a2.insert(3);
			a2.insert(2);
			a2.insert(8);
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		printContainerInformation(a2);
		
		System.out.println("______________________  Copy constructor  ______________________");
		GTUSet<Integer> a3 = new GTUSet<Integer>(a2);
		printContainerInformation(a3);
		
		System.out.println("________________________  empty method  ________________________");
		printContainerInformation(a3);
		System.out.println("Is empty : " + a3.empty() + "\n\n");
		printContainerInformation(a1);
		System.out.println("Is empty : " + a1.empty());
		
		System.out.println("________________________  Erase method  ________________________");
		printContainerInformation(a3);
		System.out.println("Delete 2. index");
		try
		{
			a3.erase(2);
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		printContainerInformation(a3);
		
		System.out.println("________________________  clear method  ________________________");
		System.out.println("Before clear method");
		printContainerInformation(a3);
		System.out.println("After clear method");
		a3.clear();
		printContainerInformation(a3);
		
		System.out.println("_______________________  contains method  ______________________");
		printContainerInformation(a2);
		System.out.println("Is 8 exist this contains ? " + a2.contains(8));
		System.out.println("Is 9 exist this contains ? " + a2.contains(9));
		
		System.out.println("_______________________  equals method  ________________________");
		System.out.println("First container : ");
		printContainerInformation(a1);
		System.out.println("Second container : ");
		printContainerInformation(a2);
		System.out.println("Equality : " + a1.equals(a2));
		System.out.println("First container : ");
		try
		{
			a1 = (GTUSet<Integer>)a2.clone();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		printContainerInformation(a1);
		System.out.println("Second container : ");
		printContainerInformation(a2);
		System.out.println("Equality : " + a1.equals(a2));
		a1.clear();
		
		System.out.println("________________________  clone method  ________________________");
		System.out.println("Before clone method");
		printContainerInformation(a1);
		System.out.println("After clone method");
		try
		{
			a1 = (GTUSet<Integer>)a2.clone();
		}
		catch(Exception e)
		{
			e.getMessage();
		}
		printContainerInformation(a1);
		System.out.println("________________________________________________________________");
	}
	
	/**
	 * Testing GTUVector
	 */
	@SuppressWarnings("unchecked")
	public static void testGTUVector()
	{
		System.out.println("\n\n-------------------  TESTING GTUVector CLASS  ------------------\n");
		System.out.println("__________________  No parameter constructor  __________________");
		GTUVector<Double> a1 = new GTUVector<Double>();
		printContainerInformation(a1);
		
		System.out.println("__________________  One parameter constructor  _________________");
		GTUVector<Double> a2 = new GTUVector<Double>(5);
		printContainerInformation(a2);
		
		System.out.println("_________________________ insert method ________________________");
		System.out.println("Before insertion : ");
		printContainerInformation(a2);
		System.out.println("After insertion : ");
		try
		{
			a2.insert(5.);
			a2.insert(3.);
			a2.insert(2.);
			a2.insert(8.);
			printContainerInformation(a2);
			System.out.println("Insert 9 to second index");
			a2.insert(9.,2);
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		printContainerInformation(a2);
		
		
		System.out.println("______________________  Copy constructor  ______________________");
		GTUVector<Double> a3 = new GTUVector<Double>(a2);
		printContainerInformation(a3);
		
		System.out.println("________________________  empty method  ________________________");
		printContainerInformation(a3);
		System.out.println("Is empty : " + a3.empty() + "\n\n");
		printContainerInformation(a1);
		System.out.println("Is empty : " + a1.empty());
		
		System.out.println("________________________  Erase method  ________________________");
		printContainerInformation(a3);
		System.out.println("Delete 1. index");
		try
		{
			a3.erase(1);
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		printContainerInformation(a3);
		
		System.out.println("________________________  clear method  ________________________");
		System.out.println("Before clear method");
		printContainerInformation(a3);
		System.out.println("After clear method");
		a3.clear();
		printContainerInformation(a3);
		
		System.out.println("_______________________  contains method  ______________________");
		printContainerInformation(a2);
		System.out.println("Is 8.0 exist this contains ? " + a2.contains(8.));
		System.out.println("Is 6.0 exist this contains ? " + a2.contains(6.));
		
		System.out.println("_______________________  equals method  ________________________");
		System.out.println("First container : ");
		printContainerInformation(a1);
		System.out.println("Second container : ");
		printContainerInformation(a2);
		System.out.println("Equality : " + a1.equals(a2));
		System.out.println("First container : ");
		try
		{
			a1 = (GTUVector<Double>)a2.clone();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		printContainerInformation(a1);
		System.out.println("Second container : ");
		printContainerInformation(a2);
		System.out.println("Equality : " + a1.equals(a2));
		a1.clear();
		
		System.out.println("________________________  clone method  ________________________");
		System.out.println("Before clone method");
		printContainerInformation(a1);
		System.out.println("After clone method");
		try
		{
			a1 = (GTUVector<Double>)a2.clone();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		printContainerInformation(a1);
		System.out.println("________________________________________________________________");
	}
	
	/**
	 * Testing GTUIterator Class
	 */
	public static void testGTUIterator()
	{
		System.out.println("\n\n---------------  TESTING GTUIterator CLASS  ----------------\n");
		
		GTUVector<Integer> vec = new GTUVector<Integer>(16);
		try
		{
			for(int i=0 ; i < 16 ; ++i)
				vec.insert(i+1);
		}
		catch(Exception e)
		{
			e.getMessage();
		}
		
		System.out.println("___  Testing GTUVector iterator method and GTUIterator class ___");
		for(GTUIterator<Integer> iter= vec.iterator() ; iter.hasNext();)
			System.out.println(iter.next());
		
		
		GTUSet<Character> set = new GTUSet<Character>(16);
		try
		{
			for(char i='A' ; i < 'A'+16 ; ++i)
				set.insert(i);
		}
		catch(Exception e)
		{
			e.getMessage();
		}
		
		System.out.println("____  Testing GTUSet iterator method and GTUIterator class  ____");
		for(GTUIterator<Character> iter= set.iterator() ; iter.hasNext();)
			System.out.println(iter.next());
		
		System.out.println("___________________  Testing hasNext method  ____________________");
		GTUIterator<Character> iter = set.iterator();
		System.out.println("Current iter : " + iter.next() + "  Iter has next : " + iter.hasNext());
		System.out.println("________________________________________________________________");
	}
	
	/**
	 * Testing GTUSet and GTUVector class exceptions
	 */
	public static void testGTUContainerException()
	{
		System.out.println("\n\n---------------  TESTING Exception Handling  ----------------\n");
		System.out.println("__________  Testing insert method's capacity exception  __________");
		GTUVector<Integer> vec = new GTUVector<Integer>();
		
		try
		{
			System.out.println("Inserting elements");
			for(int i=0 ; i < vec.max_size() * 2; ++i)
				vec.insert(i);
		}
		catch(Exception e)
		{
			System.out.println("Exception!");
			System.out.println(e.getMessage());
			System.out.println("Size : " + vec.size() + "  Capacity : " + vec.getCapacity());
		}
		
		vec.clear();
		System.out.println("______  Testing insert method's illegal argument exception  _______");
		try
		{
			vec.insert(1);
			vec.insert(null);
		}
		catch(IllegalArgumentException e)
		{
			System.out.println("Exception!");
			System.out.println(e.getMessage());
		}
		catch(Exception e)
		{
			System.out.println("Exception!");
			System.out.println(e.getMessage());
			System.out.println("Size : " + vec.size() + "  Capacity : " + vec.getCapacity());
		}
		
		System.out.println("________  Testing erase method's invalid index exception  ________");
		try
		{
			System.out.println("Size : " + vec.size());
			System.out.println("Erase 10. index");
			vec.erase(10);
		}
		catch(Exception e)
		{
			System.out.println("Exception!");
			System.out.println(e.getMessage());
		}
		System.out.println("________________________________________________________________");
	}
}