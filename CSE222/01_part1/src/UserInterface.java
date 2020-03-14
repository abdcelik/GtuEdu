import cse222.hw1.*;
import java.util.Scanner;

/**
 * UserInterface class for cargo company.
 * @author Abdullah_Celik_171044002
 */
public class UserInterface
{
    public static void main(String[] args)
    {
        CargoCompany company = createCompany();
        mainMenu(company);
    }

    public static void mainMenu(CargoCompany company)
    {
        int choice=0;

        while(choice != -1)
        {
            System.out.println("(1) Show the information of the company");
            System.out.println("(2) Log In as administrator");
            System.out.println("(3) Log In as branch employee");
            System.out.println("(4) Log In as transportation employee");
            System.out.println("(5) Query a shipment");
            System.out.println("(-1) Exit\n");
            choice = getInt("Choice : ");

            switch(choice)
            {
                case 1:
                    printCompanyInformation(company);
                    break;
                case 2:
                    adminMenu(company);
                    break;
                case 3:
                    branchEmployeeMenu(company);
                    break;
                case 4:
                    transportationPersonnelMenu(company);
                    break;
                case 5:
                    queryShip(company);
                    break;
                case -1:
                    System.out.println("Exiting...");
                    break;
                default:
                    System.out.println("Wrong choice! Try again!");
                    break;
            }
        }
    }

    public static void printCompanyInformation(CargoCompany company)
    {
        System.out.println(company);
    }

    public static void queryShip(CargoCompany company)
    {
        Shipment ship = null;

        if((ship = company.queryShipment(getInt("Tracking number : "))) == null)
            System.out.println("Wrong tracking number! Try Again!");
        else
            System.out.println(ship);
    }

    public static void adminMenu(CargoCompany company)
    {
        String name = getStr("Name : ");
        String surname = getStr("Surname : ");
        int id = getInt("ID : ");

        if(!company.getAdministrator().equals(new Administrator(company,name,surname,id)))
        {
            System.out.println("Wrong name,surname or id! Try Again!");
            return;
        }
        else
            System.out.println("Login successful.");

        Administrator admin = company.getAdministrator();
        Branch branch = null;
        int choice=0,var=0;

        while(choice != -1)
        {
            System.out.println("(1) Show my information");
            System.out.println("(2) Show the branches");
            System.out.println("(3) Add new branch");
            System.out.println("(4) Remove a branch");
            System.out.println("(5) Show branch employees at that branch");
            System.out.println("(6) Add new branch employee to the branch");
            System.out.println("(7) Remove a branch employee from the branch");
            System.out.println("(8) Show the transportation personnel");
            System.out.println("(9) Add new transportation personnel");
            System.out.println("(10) Remove a transportation personnel");
            System.out.println("(11) Show the customers");
            System.out.println("(-1) Exit");
            choice = getInt("Choice : ");

            switch(choice) {
                case 1:
                    System.out.println(admin);
                    break;
                case 2:
                    printAllBranches(company);
                    break;
                case 3:
                    if(admin.addBranch(getInt("Branch code : ")))
                        System.out.println("Adding branch is successful.");
                    else
                        System.out.println("The company already has this branch!");
                    break;
                case 4:
                    if(admin.removeBranch(getInt("Branch code : ")))
                        System.out.println("Removing branch is successful.");
                    else
                        System.out.println("The company does not have this branch!");
                    break;
                case 5:
                    branch = new Branch(company,getInt("Branch code : "));
                    if((var = company.getBranch().contains(branch)) != -1)
                        printAllBranchEmployees(company.getBranch().at(var));
                    else
                        System.out.println("Branch could not found!");
                    break;
                case 6:
                    var = getInt("Branch code : ");
                    branch = new Branch(company,var);
                    if(company.getBranch().contains(branch) != -1)
                    {
                        if(admin.addBranchEmployee(var,getStr("Name : "),getStr("Surname : "),getInt("ID : ")))
                            System.out.println("Adding branch employee is successful.");
                        else
                            System.out.println("The branch already has this employee!");
                    }
                    else
                        System.out.println("Branch could not found!");
                    break;
                case 7:
                    var = getInt("Branch code : ");
                    branch = new Branch(company,var);
                    if(company.getBranch().contains(branch) != -1)
                    {
                        if(admin.removeBranchEmployee(var,getStr("Name : "),getStr("Surname : "),getInt("ID : ")))
                            System.out.println("Removing branch employee is successful.");
                        else
                            System.out.println("The branch does not have this employee!");
                    }
                    else
                        System.out.println("Branch could not found!");
                    break;
                case 8:
                    printAllTransportationPersonnel(company);
                    break;
                case 9:
                    if(admin.addTransportationPersonnel(getStr("Name : "),getStr("Surname : "),getInt("ID : ")))
                        System.out.println("Adding transportation personnel is successful.");
                    else
                        System.out.println("The company already has this transportation personnel!");
                    break;
                case 10:
                    if(admin.removeTransportationPersonnel(getStr("Name : "),getStr("Surname : "),getInt("ID : ")))
                        System.out.println("Removing transportation personnel is successful.");
                    else
                        System.out.println("The company does not have this transportation personnel!");
                    break;
                case 11:
                    printAllCustomer(company);
                    break;
                case -1:
                    System.out.println("Exiting...");
                    break;
                default:
                    System.out.println("Wrong choice! Try again!");
                    break;
            }
        }
    }

    public static void printAllBranches(CargoCompany company)
    {
        for(int i=0 ; i < company.getBranch().size() ; ++i)
            System.out.println(company.getBranch().at(i));
    }

    public static void printAllBranchEmployees(Branch branch)
    {
        for(int i=0 ; i < branch.getBranchEmployee().size() ; ++i)
            System.out.println(branch.getBranchEmployee().at(i));
    }

    public static void printAllTransportationPersonnel(CargoCompany company)
    {
        for(int i=0 ; i < company.getTransportationPersonnel().size() ; ++i)
            System.out.println(company.getTransportationPersonnel().at(i));
    }

    public static void printAllCustomer(CargoCompany company)
    {
        for(int i=0 ; i < company.getCustomer().size() ; ++i)
            System.out.println(company.getCustomer().at(i));
    }

    public static void branchEmployeeMenu(CargoCompany company)
    {
        int branchCode = getInt("Branch Code : ");
        String name = getStr("Name : ");
        String surname = getStr("Surname : ");
        int id = getInt("ID : ");

        Branch branch = new Branch(company,branchCode);
        BranchEmployee employee = new BranchEmployee(branch,name,surname,id);
        int i=0,j=0;

        if((i = company.getBranch().contains(branch)) == -1)
        {
            System.out.println("Wrong branch code! Try again!");
            return;
        }

        if((j = company.getBranch().at(i).getBranchEmployee().contains(employee)) == -1)
        {
            System.out.println("Wrong name,surname or id! Try Again!");
            return;
        }
        else
            System.out.println("Login successful.");

        employee = company.getBranch().at(i).getBranchEmployee().at(j);
        int choice=0;

        while(choice != -1)
        {
            System.out.println("(1) Show my information");
            System.out.println("(2) Add customer");
            System.out.println("(3) Remove customer");
            System.out.println("(4) Information about shipment");
            System.out.println("(5) Enter a shipment");
            System.out.println("(6) Remove a shipment");
            System.out.println("(7) Update the shipment");
            System.out.println("(-1) Exit");
            choice = getInt("Choice : ");

            switch(choice) {
                case 1:
                    System.out.println(employee);
                    break;
                case 2:
                    if(employee.addUser(getStr("Name : "),getStr("Surname : "),getInt("ID : ")))
                        System.out.println("Adding customer operation is successful.");
                    else
                        System.out.println("The company already has this user!");
                    break;
                case 3:
                    if(employee.removeUser(getStr("Name : "),getStr("Surname : "),getInt("ID : ")))
                        System.out.println("Removing customer operation is successful.");
                    else
                        System.out.println("The company does not have this user!");
                    break;
                case 4:
                    queryShip(company);
                    break;
                case 5:
                    if(employee.enterShipmentInformation(getInt("Tracking number : "),new Person(getStr("Name : "),getStr("Surname : "),getInt("ID : ")),new Person(getStr("Name : "),getStr("Surname : "),getInt("ID : "))))
                        System.out.println("Entering a shipment information operation is successful.");
                    else
                        System.out.println("Company already has this shipment!");
                    break;
                case 6:
                    if(employee.removeShipmentInformation(getInt("Tracking number : ")))
                        System.out.println("Removing a shipment information operation is successful.");
                    else
                        System.out.println("Company does not have this shipment!");
                    break;
                case 7:
                    if(employee.updateShipmentInformation(getInt("Tracking number : "),getStatus("Status : ")))
                        System.out .println("Updating is successful.");
                    else
                        System.out.println("Updating is not successful! Try Again");
                    break;
                case -1:
                    System.out.println("Exiting...");
                    break;
                default:
                    System.out.println("Wrong choice! Try again!");
                    break;
            }
        }
    }

    public static void transportationPersonnelMenu(CargoCompany company)
    {
        String name = getStr("Name : ");
        String surname = getStr("Surname : ");
        int id = getInt("ID : ");

        TransportationPersonnel personnel = new TransportationPersonnel(company,name,surname,id);
        int index=0;

        if((index = company.getTransportationPersonnel().contains(personnel)) == -1)
        {
            System.out.println("Wrong name,surname or id! Try Again!");
            return;
        }
        else
            System.out.println("Login successful.");

        int choice=0;

        while(choice != -1)
        {
            System.out.println("(1) Show my information");
            System.out.println("(2) Update the shipment");
            System.out.println("(-1) Exit");
            choice = getInt("Choice : ");

            switch(choice) {
                case 1:
                    System.out.println(personnel);
                    break;
                case 2:
                    if(personnel.updateShipment(getInt("Tracking number : ")))
                        System.out.println("Update operation is successful.");
                    else
                        System.out.println("Wrong tracking number! Try again!");
                    break;
                case -1:
                    System.out.println("Exiting...");
                    break;
                default:
                    System.out.println("Wrong choice! Try again!");
                    break;
            }
        }
    }

    public static CargoCompany createCompany()
    {
        String cargoName = getStr("Cargo company's name : ");
        String adminName = getStr("Cargo company's administrator's name : ");
        String adminSurname = getStr("Cargo company's administrator's surname : ");
        int adminID = getInt("Cargo company's administrator's ID : ");
        System.out.println("The company was founded.");

        return new CargoCompany(cargoName,adminName,adminSurname,adminID);
    }

    public static int getInt(String str)
    {
        System.out.print(str);
        return (new Scanner(System.in)).nextInt();
    }

    public static String getStr(String str)
    {
        System.out.print(str);
        return (new Scanner(System.in)).nextLine();
    }

    public static Status getStatus(String str)
    {
        System.out.println("(1) AT BRANCH");
        System.out.println("(2) ON WAY");
        int choice = getInt(str);

        if(choice == 1)
            return Status.ATBRANCH;
        if(choice == 2)
            return Status.ONWAY;

        System.out.println("Wrong choice! Set the status AT BRANCH as default!");
        return Status.ATBRANCH;
    }
}